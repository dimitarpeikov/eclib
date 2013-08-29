/*
 * eclib_button.h
 *
 *  Created on: Sep 6, 2011
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#ifndef ECLIB_BUTTON_H_
#define ECLIB_BUTTON_H_

#include <eclib/eclib_timer.h>

#define ECLIB_BUTTON_MASK_SHORT_CLICK		0x01
#define ECLIB_BUTTON_MASK_NORMAL_CLICK		0x02
#define ECLIB_BUTTON_MASK_LONG_CLICK		0x04
#define ECLIB_BUTTON_MASK_AUTO_CLICK		0x08
#define ECLIB_BUTTON_MASK_STICK				0x10

typedef enum eclib_button_status {
	ECLIB_BUTTON_STATE_UNINIT,				//!< not initialized
	ECLIB_BUTTON_STATE_INIT,				//!< initialized, but not identified which state
	ECLIB_BUTTON_STATE_RELEASED,			//!< released
	ECLIB_BUTTON_STATE_PRESSED,				//!< pressed
	ECLIB_BUTTON_STATE_REPEAT,				//!< in repeating mode
	ECLIB_BUTTON_STATE_STICK_FAILURE		//!< stick failure
} eclib_button_status_t;

typedef enum eclib_button_reason {
	ECLIB_BUTTON_NONE,						//!< none
	ECLIB_BUTTON_SHORT_CLICK,				//!< short click
	ECLIB_BUTTON_NORMAL_CLICK,				//!< normal click
	ECLIB_BUTTON_LONG_CLICK,				//!< long click
	ECLIB_BUTTON_AUTO_REPEAT,				//!< auto repeat
	ECLIB_BUTTON_STICK						//!< stick
} eclib_button_reason_t;

typedef void (*eclib_button_callback_ptr_t)(uint8_t buttonId, eclib_button_reason_t reason);

typedef struct eclib_button_definition_t {
	eclib_timer_t 								shortClick;
	eclib_timer_t 								normalClick;
	eclib_timer_t 								longClick;
	eclib_timer_t								autoRepeat;
	eclib_timer_t								stick;
	uint32_t									eventMask;
	eclib_button_callback_ptr_t					callback;
} eclib_button_definition_t;
typedef eclib_button_definition_t * 		eclib_button_definition_ptr_t;

typedef struct eclib_button_state_t {
	eclib_timer_t								lastChange;
	eclib_timer_t								autoRepeatChange;
	eclib_button_status_t						state;
	eclib_button_status_t						value;
	uint32_t									eventMask;
} eclib_button_state_t;
typedef eclib_button_state_t *				eclib_button_state_ptr_t;

typedef struct eclib_button_context_t {
	eclib_button_definition_ptr_t 				buttonsDefPtr;
	eclib_button_state_ptr_t					buttonStatePtr;
	eclib_timer_t								lastProcess;
	uint8_t										buttonCount;
} eclib_button_context_t;
typedef eclib_button_context_t * 			eclib_button_context_ptr_t;

/*!
 * @fn eclib_button_version( )
 * @return	Returns library version number
 */
uint32_t eclib_button_version();

/*!
 * @fn eclib_button_init( eclib_button_context_ptr_t buttonsContextPtr )
 * @brief initialize structure for button management
 * @return	Returns status of performed operation
 */
eclib_status_t eclib_button_init(eclib_button_context_ptr_t  buttonsContextPtr);

/*!
 * @fn eclib_button_provess( eclib_button_context_ptr_t buttonsContextPtr )
 * @brief process button structure for updates
 */
void eclib_button_process(eclib_button_context_ptr_t buttonsContextPtr);

/*!
 * @fn eclib_button_init( eclib_button_context_ptr_t buttonsContextPtr, uint8_t buttonIndex, uint8_t buttonState )
 * @brief set state of given button
 * @return	Returns status of performed operation
 */
eclib_status_t eclib_button_set(eclib_button_context_ptr_t buttonsContextPtr, uint8_t buttonIndex, eclib_button_status_t buttonState);

#endif /* ECLIB_BUTTON_H_ */
