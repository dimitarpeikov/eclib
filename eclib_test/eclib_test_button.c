/*
 * eclib_test_button.h
 *
 *  Created on: Sep 6, 2011
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include <eclib/eclib_timer.h>
#include <eclib/eclib_button.h>

static eclib_button_definition_t buttonDefs[] = {
		{ /* button 0 */
				500,
				1500,
				3000,
				500
		},
		{ /* button 1 */
				200,
				1000,
				2000,
				250
		},
		{ /* button 2 */
				300,
				1000,
				2000,
				250
		},
};

static eclib_button_state_t buttonStates[] = {
		{
				0, /* button 0 state 0 */
				0	/* timer not started */
		},
		{
				0, /* button 1 state 0 */
				0	/* timer not started */
		},
		{
				0, /* button 2 state 0 */
				0	/* timer not started */
		}
};

static eclib_button_context_t buttonContext = {
		buttonDefs,
		buttonStates,
		sizeof(buttonDefs) / sizeof(buttonDefs[0])
};

extern volatile uint32_t __counter_1ms;

typedef struct time_simulation_t {
	uint32_t		time;
	uint8_t		button;
	uint8_t		value;
} time_simulation_t;

time_simulation_t timeSimulation[] = {
		// time 0ms, buttons = state 1
		{0, 0, 1},
		{0, 1, 1},
		{0, 2, 1},

		// time 250ms, button 0 = state 0; no button press to be detected
		{ 250, 0, 0},

		// time 500ms, button 0 = state 1
		{ 500, 0, 1},
		// time 500ms, button 1 = state 0; short press to be detected
		{ 500, 1, 0},

		// time 1000ms, button 1 = state 1
		{1000, 1, 1},

		// time 1200ms, button 2 = state 0; normal press to be detected
		{1200, 2, 0},

		// button 1 have to initiate first normal click
		{3250, 1, 1},

		// time 3500ms, button 0 = state 0; long press to be detected
		{3500, 0, 0},
		// button 1 have to initiate repeat normal click
		{3250, 1, 1},

		// time 5000ms, end of the simulation
		{5000, 0, 0}
};

uint16_t eclib_test_button() {
	uint16_t result = 0;
	uint16_t idx = 0;

	__counter_1ms = 0;
	eclib_button_init(&buttonContext);

	/* simulate the time, and simulate different button press for each button */
	for (; __counter_1ms < 1000000000; __counter_1ms ++) {
		// check for simulation events
		while ((idx < (sizeof(timeSimulation) / sizeof(timeSimulation[0]))) && (timeSimulation[idx].time == __counter_1ms)) {
			eclib_button_set(&buttonContext, timeSimulation[idx].button, timeSimulation[idx].value);
			idx ++;
		}

		// process button contexts
		eclib_button_process(&buttonContext);

		// close the simulation when hit end of the simulation configuration
		if (idx >= (sizeof(timeSimulation) / sizeof(timeSimulation[0]))) {
			break;
		}
	}

	return result;
}
