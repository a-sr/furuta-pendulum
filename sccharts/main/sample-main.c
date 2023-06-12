#include "time-util.h"
#include "FurutaPendulumSample.h"

// State of the SCChart
TickData model;

int main(int argc, const char* argv[]) {
    // Init SCChart
    reset(&model);
    
    // Init time
	time_init();
	clock_time last_tick = time_current();

    // Tick loop
    while (!model.finished) {
        // Compute passed time
    	clock_time tick_start = time_current();
	    model.deltaT = tick_start - last_tick;

    	// Compute tick
        tick(&model);

        // Compute sleep time
        last_tick = tick_start;
        clock_time sleep = model.sleepT - (time_current() - tick_start);

        // Wait
        if (sleep > 0) {
            time_nanosleep(sleep);
        }
    }
}
