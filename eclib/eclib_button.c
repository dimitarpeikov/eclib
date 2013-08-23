/*
 * eclib_button.c
 *
 *  Created on: Sep 6, 2011
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */
#include <eclib/eclib_types.h>
#include <eclib/eclib_timer.h>
#include <eclib/eclib_button.h>

void eclib_button_init(eclib_button_context_ptr_t  buttonsContextPtr) {
	uint16_t idx;
	if (NULL != buttonsContextPtr) {
		/* cleanup the buttons state */
		for (idx = 0; idx < buttonsContextPtr->buttonCount; idx ++) {
			buttonsContextPtr->buttonStatePtr[idx].state = 0;
			buttonsContextPtr->buttonStatePtr[idx].nextTreshold = 0L;
			buttonsContextPtr->buttonStatePtr[idx].lastChange = 0L;
		}
	}
}

void eclib_button_process(eclib_button_context_ptr_t buttonsContextPtr) {
	uint16_t idx;
	uint32_t localTimer = 0L;
	eclib_button_state_ptr_t btnStatePtr;

	eclib_timer_start_timer(&localTimer);

	for (idx = 0; idx < buttonsContextPtr->buttonCount; idx ++) {
		btnStatePtr = &(buttonsContextPtr->buttonStatePtr[idx]);
		if (0 != eclib_timer_is_timer_started(&btnStatePtr->lastChange)) {
			if (eclib_timer_is_elapsed_timeout(&btnStatePtr->lastChange, btnStatePtr->nextTreshold)) {

			}
		}
	}
}

void eclib_button_set(eclib_button_context_ptr_t buttonsContextPtr, uint8_t buttonIndex, uint8_t buttonState) {
	uint32_t timer = 0L;
	eclib_button_state_ptr_t statePtr;

	if (0 != buttonsContextPtr) {
		if (buttonIndex < buttonsContextPtr->buttonCount) {
			statePtr = &(buttonsContextPtr->buttonStatePtr[buttonIndex]);
			if (statePtr->state != buttonState) {
				eclib_timer_start_timer(&timer);
				statePtr->lastChange = timer;
				statePtr->state = buttonState;
			}
		}
	}
}
