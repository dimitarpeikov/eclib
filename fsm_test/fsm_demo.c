/*
 * fsm_demo.c
 *
 *  Created on: May 2, 2011
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_set.h>
#include <fsm/fsm.h>
#include "fsm_demo_actions.h"

#include <stdio.h>

enum MyEvent {
	ZERO_EVENT,
	SINGLE_EVENT,
	SECOND_EVENT
};

stm_state_t	nodeList[] = {
	/* 		TYPE, transitionListStartIndex, indexCount, 		onEnterIndex, 				onExitIndex, 			doStartIndex, 				doEndIndex */
	{STM_INITIAL, 							0, 				1, STM_INDEX_INVALID, 						5, STM_INDEX_INVALID, STM_INDEX_INVALID},
	{STM_STATE, 								1, 				1, 							4, STM_INDEX_INVALID, 							6, 							7},
	{STM_STATE, 								2, 				1, STM_INDEX_INVALID, STM_INDEX_INVALID, STM_INDEX_INVALID, STM_INDEX_INVALID}
};

stm_transition_t	transitionList[] = {
	/* {eventIndex, ptr},	toStateIndex, actionIndex */
	{{ZERO_EVENT, 0},		1, 		0},
	{{ZERO_EVENT, 0},		2, 		1},
	{{SINGLE_EVENT, 0},	1, 		3}
};

stm_action_fn_t actionList[] = {
	action_one,
	action_two,
	action_three,
	action_four,
	action_onEnter,
	action_onExit,
	action_doStart,
	action_doEnd
};

ECLIB_SET(fsmStateIndexList, sizeof(stm_index_t), 10);
ECLIB_SET(fsmWorkSet, sizeof(stm_index_t), 10);

stm_fsm_context_t fsmContext = {
	transitionList,
	nodeList,
	actionList,
	(eclib_set_ptr_t)&fsmStateIndexList_buffer,
	(eclib_set_ptr_t)&fsmWorkSet_buffer,
	NULL
};


int main() {
	stm_index_t	initIndex = 0;
	stm_event_t	event;

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	eclib_set_init(fsmStateIndexList, sizeof(stm_index_t), 10);
	eclib_set_init(fsmWorkSet, sizeof(stm_index_t), 10);

	/// set 0 state index as initial state for state machine
	eclib_set_add(fsmStateIndexList, &initIndex);
	stm_set_fsmContext(&fsmContext);

	event.event = ZERO_EVENT;
	event.ptr = NULL;
	stm_process_event(&event);

	event.event = SINGLE_EVENT;
	stm_process_event(&event);

	event.event = SINGLE_EVENT;
	stm_process_event(&event);

	event.event = ZERO_EVENT;
	stm_process_event(&event);

	event.event = SINGLE_EVENT;
	stm_process_event(&event);

	printf("done.\n");
	return 0;
}
