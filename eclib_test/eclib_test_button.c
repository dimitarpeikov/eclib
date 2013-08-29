/*
 * eclib_test_button.h
 *
 *  Created on: Sep 6, 2011
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include <eclib/eclib_timer.h>
#include <eclib/eclib_button.h>

#include <stdio.h>

void button_callback_fn(uint8_t buttonId, eclib_button_reason_t reason) {
	eclib_timer_t t;
	eclib_timer_start_timer(&t);
	printf("%08d: %d %d\n", t, buttonId, reason);
}

static eclib_button_definition_t buttonDefs[] = {
		{ /* button 0 */
				500,       	// short click
				1500,      	// normal click
				3000,      	// long click
				500,       	// auto-repeat
				60000,     	// 3s to detect stick
				0x1f,      	// event mask
				button_callback_fn       	// callback
		},
		{ /* button 1 */
				200,     	// short click
				1000,    	// normal click
				2000,    	// long click
				250,     	// auto-repeat
				60000,   	// 3s to detect stick
				0x1f,     	// event mask
				button_callback_fn     	// callback
		},
		{ /* button 2 */
				300,		// short click
				1000,		// normal click
				2000,		// long click
				250,		// auto-repeat
				3000,		// 3s to detect stick
				0x1f,		// event mask
				button_callback_fn		// callback
		},
};

static eclib_button_state_t buttonStates[] = {
		{
				0, /* button 0 last changed time */
				0, /* button 0 auto-repeat time */
				ECLIB_BUTTON_STATE_UNINIT,  /* button 0 state uninit */
				ECLIB_BUTTON_STATE_UNINIT,  /* button 0 value state uninit */
				0
		},
		{
				0, /* button 1 last changed time */
				0, /* button 1 auto-repeat time */
				ECLIB_BUTTON_STATE_UNINIT,  /* button 1 state uninit */
				ECLIB_BUTTON_STATE_UNINIT,  /* button 1 value state uninit */
				0
		},
		{
				0, /* button 2 last changed time */
				0, /* button 2 auto-repeat time */
				ECLIB_BUTTON_STATE_UNINIT,  /* button 2 state uninit */
				ECLIB_BUTTON_STATE_UNINIT,  /* button 2 value state uninit */
				0
		}
};

static eclib_button_context_t buttonContext = {
		buttonDefs,
		buttonStates,
		0,
		sizeof(buttonDefs) / sizeof(buttonDefs[0])
};

extern volatile uint32_t __counter_1ms;

typedef struct time_simulation_t {
	eclib_timer_t			time;
	uint8_t					button;
	uint8_t					value;
	eclib_button_status_t	expState;
} time_simulation_t;

time_simulation_t timeSimulation[] = {
		// time 0ms, buttons = state 1
		{1, 0, ECLIB_BUTTON_STATE_PRESSED, ECLIB_BUTTON_STATE_PRESSED},
		{1, 1, ECLIB_BUTTON_STATE_PRESSED, ECLIB_BUTTON_STATE_PRESSED},
		{1, 2, ECLIB_BUTTON_STATE_PRESSED, ECLIB_BUTTON_STATE_PRESSED},

		// time 250ms, button 0 = state 0; no button press to be detected
		{ 250, 0, ECLIB_BUTTON_STATE_RELEASED, ECLIB_BUTTON_STATE_RELEASED},

		// time 500ms, button 0 = state 1
		{ 500, 0, ECLIB_BUTTON_STATE_PRESSED, ECLIB_BUTTON_STATE_PRESSED},
		// time 500ms, button 1 = state 0; short press to be detected
		{ 500, 1, ECLIB_BUTTON_STATE_RELEASED, ECLIB_BUTTON_STATE_RELEASED},

		// time 1000ms, button 1 = state 1
		{1000, 1, ECLIB_BUTTON_STATE_PRESSED, ECLIB_BUTTON_STATE_PRESSED},

		// time 1200ms, button 2 = state 0; normal press to be detected
		{1200, 1, ECLIB_BUTTON_STATE_RELEASED, ECLIB_BUTTON_STATE_RELEASED},

		// button 1 have to initiate first normal click
		{3250, 1, ECLIB_BUTTON_STATE_PRESSED, ECLIB_BUTTON_STATE_PRESSED},

		// time 3500ms, button 0 = state 0; long press to be detected
		{3500, 0, ECLIB_BUTTON_STATE_RELEASED, ECLIB_BUTTON_STATE_RELEASED},
		// button 1 have to initiate repeat normal click
		{3250, 1, ECLIB_BUTTON_STATE_PRESSED, ECLIB_BUTTON_STATE_PRESSED},

		// time 5000ms, end of the simulation
		{5000, 0, ECLIB_BUTTON_STATE_RELEASED, ECLIB_BUTTON_STATE_RELEASED}
};

uint16_t eclib_test_button() {
	uint16_t idx = 0;
	uint16_t errors = 0;
	uint32_t eclib_timer_version_id = eclib_timer_version();

	printf("%s: %s\tv.%x\n", __FILE__, __DATE__, eclib_timer_version_id);

	__counter_1ms = 1;
	eclib_button_init(&buttonContext);

	/* simulate the time, and simulate different button press for each button */
	for (; __counter_1ms < timeSimulation[sizeof(timeSimulation) / sizeof(timeSimulation[0]) - 1].time; __counter_1ms ++) {
		idx = 0;
		// check for simulation events
		while (idx < (sizeof(timeSimulation) / sizeof(timeSimulation[0]))) {
			if (timeSimulation[idx].time == __counter_1ms) {
				eclib_button_set(&buttonContext, timeSimulation[idx].button, timeSimulation[idx].value);

				// check button context state
				if (timeSimulation[idx].expState != buttonContext.buttonStatePtr[timeSimulation[idx].button].value) {
					errors ++;
				}
			}
			idx ++;

		}

		// process button contexts
		eclib_button_process(&buttonContext);

	}

	printf("%s: %s\terrors detected: %d\n", __FILE__, __DATE__, errors);

	return errors;
}
