/*
 * Header for communication with the visualization frontend.
 *
 * @author Alexander Schulz-Rosengarten
 */

#ifndef VISUALIZATION_H
#define VISUALIZATION_H

/** Start the server and register callbacks. */
void start_server_async(void (*set_pause)(void*, char),
	void* set_pause_arg,
	void (*set_disturbance)(void*, double),
	void* set_disturbance_arg);

/** Send the pendulum state to the client. */
void send_status(double time, double ptime,
	char led, char speaker,
	double control, double energy,
	double theta, double d_theta,
	double phi, double d_phi);

#endif
