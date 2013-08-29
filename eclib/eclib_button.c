/*
 * eclib_button.c
 *
 *  Created on: Sep 6, 2011
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */
#include <eclib/eclib_types.h>
#include <eclib/eclib_timer.h>
#include <eclib/eclib_button.h>

#define ECLIB_BUTTON_VERSION_ID			0x0100

uint32_t eclib_button_version() {
	return ECLIB_BUTTON_VERSION_ID;
}

eclib_status_t eclib_button_init(eclib_button_context_ptr_t  buttonsContextPtr) {
	uint16_t idx;
	eclib_status_t result = ECLIB_OK;

	if (NULL != buttonsContextPtr) {
		/* cleanup the buttons state */
		for (idx = 0; idx < buttonsContextPtr->buttonCount; idx ++) {
			buttonsContextPtr->buttonStatePtr[idx].state = ECLIB_BUTTON_STATE_INIT;
			buttonsContextPtr->buttonStatePtr[idx].value = ECLIB_BUTTON_STATE_INIT;
			buttonsContextPtr->buttonStatePtr[idx].lastChange = 0L;
			buttonsContextPtr->buttonStatePtr[idx].autoRepeatChange = 0L;
			buttonsContextPtr->buttonStatePtr[idx].eventMask = 0L;
		}
	} else {
		result = ECLIB_ERROR;
	}
	return result;
}

void eclib_button_process(eclib_button_context_ptr_t buttonsContextPtr) {
	uint16_t idx;
	uint32_t localTimer = 0L;
	uint32_t eventButtonMask;
	eclib_button_state_ptr_t btnStatePtr;
	eclib_button_definition_ptr_t btnDefPtr;

	eclib_timer_start_timer(&localTimer);

	for (idx = 0; idx < buttonsContextPtr->buttonCount; idx ++) {
		btnStatePtr = &(buttonsContextPtr->buttonStatePtr[idx]);
		btnDefPtr = &(buttonsContextPtr->buttonsDefPtr[idx]);
		eventButtonMask = btnDefPtr->eventMask;
		if ((0 != eclib_timer_is_timer_started(&btnStatePtr->lastChange)) && !(btnStatePtr->eventMask & ECLIB_BUTTON_MASK_STICK)) {
			/// short press
			if ((eventButtonMask & ECLIB_BUTTON_MASK_SHORT_CLICK) && !(btnStatePtr->eventMask & ECLIB_BUTTON_MASK_SHORT_CLICK)) {
				if (eclib_timer_is_elapsed_timeout(&btnStatePtr->lastChange, btnDefPtr->shortClick)) {
					if (btnDefPtr->callback) {
						btnDefPtr->callback(idx, ECLIB_BUTTON_SHORT_CLICK);
					}
					btnStatePtr->eventMask |= ECLIB_BUTTON_MASK_SHORT_CLICK;
				}
			}

			/// normal press
			if ((eventButtonMask & ECLIB_BUTTON_MASK_NORMAL_CLICK) && !(btnStatePtr->eventMask & ECLIB_BUTTON_MASK_NORMAL_CLICK)) {
				if (eclib_timer_is_elapsed_timeout(&btnStatePtr->lastChange, btnDefPtr->normalClick)) {
					if (btnDefPtr->callback) {
						btnDefPtr->callback(idx, ECLIB_BUTTON_NORMAL_CLICK);
					}
					btnStatePtr->eventMask |= ECLIB_BUTTON_MASK_NORMAL_CLICK;
				}
			}

			/// long press
			if ((eventButtonMask & ECLIB_BUTTON_MASK_LONG_CLICK) && !(btnStatePtr->eventMask & ECLIB_BUTTON_MASK_LONG_CLICK)) {
				if (eclib_timer_is_elapsed_timeout(&btnStatePtr->lastChange, btnDefPtr->longClick)) {
					if (btnDefPtr->callback) {
						btnDefPtr->callback(idx, ECLIB_BUTTON_LONG_CLICK);
					}
					btnStatePtr->eventMask |= ECLIB_BUTTON_MASK_LONG_CLICK;
				}
			}

			/// auto-repeat
			if ((eventButtonMask & ECLIB_BUTTON_MASK_AUTO_CLICK) && (btnStatePtr->eventMask & ECLIB_BUTTON_MASK_AUTO_CLICK)) {
				if (eclib_timer_is_elapsed_timeout(&btnStatePtr->autoRepeatChange, btnDefPtr->autoRepeat)) {
					if (btnDefPtr->callback) {
						btnDefPtr->callback(idx, ECLIB_BUTTON_AUTO_REPEAT);
					}
					btnStatePtr->state = ECLIB_BUTTON_STATE_REPEAT;
					btnStatePtr->eventMask |= ECLIB_BUTTON_MASK_AUTO_CLICK;
					eclib_timer_start_timer(&btnStatePtr->autoRepeatChange);
				}
			}
			if ((eventButtonMask & ECLIB_BUTTON_MASK_AUTO_CLICK) && !(btnStatePtr->eventMask & ECLIB_BUTTON_MASK_AUTO_CLICK)) {
				if (eclib_timer_is_elapsed_timeout(&btnStatePtr->autoRepeatChange, btnDefPtr->normalClick + btnDefPtr->autoRepeat)) {
					if (btnDefPtr->callback) {
						btnDefPtr->callback(idx, ECLIB_BUTTON_AUTO_REPEAT);
					}
					btnStatePtr->state = ECLIB_BUTTON_STATE_REPEAT;
					btnStatePtr->eventMask |= ECLIB_BUTTON_MASK_AUTO_CLICK;
					eclib_timer_start_timer(&btnStatePtr->autoRepeatChange);
				}
			}

			/// button stick
			if (eventButtonMask & ECLIB_BUTTON_MASK_STICK) {
				if (eclib_timer_is_elapsed_timeout(&btnStatePtr->lastChange, btnDefPtr->stick)) {
					if (btnDefPtr->callback) {
						btnDefPtr->callback(idx, ECLIB_BUTTON_STATE_STICK_FAILURE);
					}
					btnStatePtr->eventMask |= ECLIB_BUTTON_MASK_STICK;
				}
			}
		}
	}
}

eclib_status_t eclib_button_set(eclib_button_context_ptr_t buttonsContextPtr, uint8_t buttonIndex, eclib_button_status_t buttonState) {
	uint32_t timer = 0L;
	eclib_button_state_ptr_t statePtr;
	eclib_status_t result = ECLIB_OK;

	if (0 != buttonsContextPtr) {
		if (buttonIndex < buttonsContextPtr->buttonCount) {
			statePtr = &(buttonsContextPtr->buttonStatePtr[buttonIndex]);
			if (statePtr->state != buttonState) {
				if (ECLIB_BUTTON_STATE_PRESSED == buttonState) {
					eclib_timer_start_timer(&timer);
				} else {
					eclib_timer_stop_timer(&timer);
					if (ECLIB_BUTTON_STATE_RELEASED == statePtr->state) {
						if (statePtr->state & ECLIB_BUTTON_MASK_STICK) {
							statePtr->state = ECLIB_BUTTON_STATE_STICK_FAILURE;
						} else {
							if (statePtr->state & ECLIB_BUTTON_MASK_LONG_CLICK) {
								statePtr->state = ECLIB_BUTTON_LONG_CLICK;
							} else {
								if (statePtr->state & ECLIB_BUTTON_MASK_NORMAL_CLICK) {
									statePtr->state = ECLIB_BUTTON_NORMAL_CLICK;
								} else {
									if (statePtr->state & ECLIB_BUTTON_MASK_SHORT_CLICK) {
										statePtr->state = ECLIB_BUTTON_SHORT_CLICK;
									} else {
									}
								}
							}
						}
					}
				}
				eclib_timer_start_timer(&statePtr->lastChange);
				statePtr->autoRepeatChange = statePtr->lastChange;
				statePtr->value = buttonState;
				statePtr->eventMask = 0L;
			}
		}
	} else {
		result = ECLIB_NULL_POINTER;
	}
	return result;
}
