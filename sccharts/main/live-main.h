#ifndef LIVE_MAIN_H
#define LIVE_MAIN_H

/** Server callback for pause. */
void callback_pause(void*, char);

/** Server callback for disturbance. */
void callback_disturbance(void*, double);

#endif