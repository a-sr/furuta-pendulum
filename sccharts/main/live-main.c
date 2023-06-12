#include <pthread.h>
#include <time.h>
#include "time-util.h"
#include "live-main.h"
#include "FurutaPendulumLive.h"

// State of the SCChart
TickData model;

// Lock for callbacks from server
pthread_mutex_t lock;
// Conditional variable for signalling tick loop
pthread_cond_t signal;

// Inputs form the UI
char pause_signal = 1;
double disturbance_signal = 0;


/** Server callback for pause. */
void callback_pause(void* _ignore, char pause) {
    pthread_mutex_lock(&lock);
    pause_signal = pause;
    // Wake up tick loop
    pthread_cond_signal(&signal);
    pthread_mutex_unlock(&lock);
}

/** Server callback for disturbance. */
void callback_disturbance(void* _ignore, double disturbance) {
    pthread_mutex_lock(&lock);
    disturbance_signal = disturbance;
    // Wake up tick loop
    pthread_cond_signal(&signal);
    pthread_mutex_unlock(&lock);
}

int main(int argc, const char* argv[]) {
    // Init lock & signal
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&signal, NULL);

    // Init SCChart
    reset(&model);

    // Init time
    time_init();
    clock_time last_tick = time_current();

    // Lock for first tick loop iteration
    pthread_mutex_lock(&lock);

    // Tick loop
    while (1) {
        // Compute passed time
        clock_time tick_start = time_current();
        model.deltaT = tick_start - last_tick;

        // Read UI inputs
        model.pause = pause_signal;
        model.disturbance = disturbance_signal;
        // Reset disturbance to 0 to only affect the pendulum once
        disturbance_signal = 0;

        // Compute tick
        tick(&model);

        // Compute sleep time
        last_tick = tick_start;
        clock_time sleep = model.sleepT - (time_current() - tick_start);

        // Wait
        if (sleep > 0) {
            // Compute absolute sleep target
            struct timespec sleepTarget;
            clock_gettime(CLOCK_REALTIME, &sleepTarget);
            sleepTarget.tv_sec += sleep / SEC(1);
            sleepTarget.tv_nsec += sleep % SEC(1);
            if (sleepTarget.tv_nsec >= SEC(1)) {
                sleepTarget.tv_sec += 1;
                sleepTarget.tv_nsec -= SEC(1);
            }
            // Release lock and wait for an UI event signal or sleep timeout, then lock again
            pthread_cond_timedwait(&signal, &lock, &sleepTarget);
        }
    }
}
