/*
 * eclib_button.h
 *
 *  Created on: Sep 6, 2011
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#ifndef ECLIB_BUTTON_H_
#define ECLIB_BUTTON_H_

typedef struct eclib_button_definition_t {
	uint16_t 										shortClick;
	uint16_t 										middleClick;
	uint16_t 										longClick;
	uint16_t											autoRepeat;
} eclib_button_definition_t;
typedef eclib_button_definition_t * 		eclib_button_definition_ptr_t;

typedef struct eclib_button_state_t {
	uint32_t											lastChange;
	uint32_t											nextTreshold;
	uint8_t											state;
} eclib_button_state_t;
typedef eclib_button_state_t *				eclib_button_state_ptr_t;

typedef struct eclib_button_context_t {
	eclib_button_definition_ptr_t 				buttonsDefPtr;
	eclib_button_state_ptr_t					buttonStatePtr;
	uint32_t											lastProcess;
	uint8_t											buttonCount;
} eclib_button_context_t;
typedef eclib_button_context_t * 			eclib_button_context_ptr_t;

void eclib_button_init(eclib_button_context_ptr_t  buttonsContextPtr);
void eclib_button_process(eclib_button_context_ptr_t buttonsContextPtr);
void eclib_button_set(eclib_button_context_ptr_t buttonsContextPtr, uint8_t buttonIndex, uint8_t buttonState);

#endif /* ECLIB_BUTTON_H_ */
