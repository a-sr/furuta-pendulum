/*
 * Header for communication with the visualization frontend.
 *
 * @author Alexander Schulz-Rosengarten
 */

#include "visualization.h"
#include <pthread.h>
#include "libdump/include/http.h" // Actually ../facil.io/libdump, relativized for LF build infrastructure.

/** Configuration and state of the server. */
struct {
	pthread_t thread_id; // The server thread ID
	void (*set_pause)(void*, char); // Callback for pausing simulation
	void* set_pause_arg; // Physical action for pausing simulation
	void (*set_disturbance)(void*, double);  // Callback for disturbing the pendulum
	void* set_disturbance_arg; // Physical action for disturbing the pendulum
	ws_s* volatile ws; // The websocket instance
	char* port; // Server port
} volatile server_state = {
	.thread_id = 0,
	.set_pause = NULL,
	.set_pause_arg = NULL,
	.set_disturbance = NULL,
	.set_disturbance_arg = NULL,
	.ws = NULL,
	.port = "5555" // Preconfigured port 
};

// WebSocket callbacks

/** Facil.io callback for the websocket. */
static void on_open_websocket(ws_s* ws) {
	server_state.ws = ws;
	printf("Visualization connected\n");
}

/** Facil.io callback for the websocket. */
static void on_close_websocket(intptr_t uuid, void* udata) {
	server_state.ws = NULL;
	printf("Visualization disconnected\n");
}

/** Facil.io callback for the websocket. */
static void handle_websocket_messages(ws_s* ws, fio_str_info_s data, uint8_t is_text) {
	FIOBJ json = FIOBJ_INVALID;
	size_t consumed = fiobj_json2obj(&json, data.data, data.len);
	if (consumed && json) {
		// Detect pause
		FIOBJ key = fiobj_str_new("pause", 5);
		if (FIOBJ_TYPE_IS(json, FIOBJ_T_HASH) && fiobj_hash_get(json, key)) {
			server_state.set_pause(
				server_state.set_pause_arg,
				(size_t)fiobj_obj2num(fiobj_hash_get(json, key)));
		}
		fiobj_free(key);
		// Detect disturbance
		key = fiobj_str_new("disturbance", 11);
		if (FIOBJ_TYPE_IS(json, FIOBJ_T_HASH) && fiobj_hash_get(json, key)) {
			server_state.set_disturbance(
				server_state.set_disturbance_arg,
				fiobj_obj2float(fiobj_hash_get(json, key)));
		}
		fiobj_free(key);
	}
	fiobj_free(json);
}

// HTTP Handling (Upgrading to WebSocket)

/** Facil.io callback for the http server. */
static void answer_http_request(http_s* h) {
	http_set_header(h, HTTP_HEADER_CONTENT_TYPE, http_mimetype_find("txt", 3));
	http_send_body(h, "Pendulum Simulation Server.", 27);
}

/** Facil.io callback for the http server. */
static void answer_http_upgrade(http_s* h, char* target, size_t len) {
	// Test for target protocol name
	if (len != 9 || memcmp(target, "websocket", 9)) {
		http_send_error(h, 400);
		return;
	}

	http_upgrade2ws(h,
		.on_open = on_open_websocket,
		.on_close = on_close_websocket,
		.on_message = handle_websocket_messages,
		.udata = NULL);
}

// Startup

/** Start server. */
static void* start_server(void* _) {
	if (http_listen(server_state.port, NULL,
		.on_request = answer_http_request,
		.on_upgrade = answer_http_upgrade) == -1) {
		perror("Couldn't listen for HTTP / WebSocket connections");
		exit(1);
	}

	printf("Server is running\n");
	fio_start(.threads = 1, .workers = 1); // never returns!
}

/** Register callbacks and start thread for the server. */
void start_server_async(void (*set_pause)(void*, char),
		void* set_pause_arg,
		void (*set_disturbance)(void*, double),
		void* set_disturbance_arg) {
	server_state.set_pause = set_pause;
	server_state.set_pause_arg = set_pause_arg;
	server_state.set_disturbance = set_disturbance;
	server_state.set_disturbance_arg = set_disturbance_arg;
	pthread_create(&(server_state.thread_id), NULL, &start_server, NULL);
}

// Messaging

/** Send the pendulum state to the client. */
void send_status(double time, double ptime,
		char led, char speaker,
		double control, double energy,
		double theta, double d_theta,
		double phi, double d_phi) {
	if (server_state.ws != NULL) {
		FIOBJ msg = fiobj_str_buf(0);
		fiobj_str_printf(msg,
			"{\"time\":%.5f,\"ptime\":%.5f,\"led\":%d,\"speaker\":%d,\"control\":%.4f,\"energy\":%.4f,\"theta\":%.4f,\"dtheta\":%.4f,\"phi\":%.4f,\"dphi\":%.4f}",
			time, ptime, led, speaker, control, energy, theta, d_theta, phi, d_phi);
		int err = websocket_write(server_state.ws, fiobj_obj2cstr(msg), 1);
		if (err != 0) {
			perror("Could not send message via websocket.");
		}
		fiobj_free(msg);
	}
}
