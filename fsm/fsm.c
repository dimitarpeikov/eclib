/*
 * stm.c
 *
 *  Created on: May 2, 2011
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <fsm/fsm.h>
#include <eclib/eclib_set.h>
#include <stdlib.h>

static stm_fsm_context_ptr_t fsmContext = 0;
static stm_event_t __stm_null_event = {STM_INDEX_INVALID, 0};

void stm_set_fsmContext(stm_fsm_context_ptr_t fsmContextList) {
	fsmContext = fsmContextList;
}

int stm_transition_compare(const void * a, const void * b) {
	stm_transition_ptr_t	transPtr = (stm_transition_ptr_t) b;
	stm_event_ptr_t			event = (stm_event_ptr_t) a;
	if ((0 != event)  && (event->event == transPtr->event.event)) {
		return 0;
	}
    if(event->event > transPtr->event.event) {
    	return -1;
	}
    return 1;
}

void stm_traversal_start() {

}

void stm_traversal_start_from_state(stm_index_t startStateIndex) {
}

stm_index_t stm_process_event(stm_event_ptr_t eventPtr) {
	stm_index_t 			result = -1;
	stm_transition_ptr_t	transitionPtr;
	stm_state_ptr_t		statePtr;
	stm_state_ptr_t		newStatePtr;
	stm_transition_ptr_t	lookupTransitionPtr;
	stm_action_fn_t		action;
	eclib_status_t			eStatus = ECLIB_ERROR;
	stm_index_t			activeStateCount, activeStateIndex;
	stm_index_t			index;
	eclib_set_ptr_t		activeStateSetPtr;
	eclib_set_ptr_t		workingStateSetPtr;
	int							transitionDetectionFlag = 0;

	workingStateSetPtr = fsmContext->workStateListPtr;
	eStatus = eclib_set_clear(workingStateSetPtr);
	if (eStatus != ECLIB_OK) {
		if (fsmContext->errorCallback != NULL) {
			fsmContext->errorCallback(ECLIB_EMPTY);
		}
	}
	activeStateSetPtr = fsmContext->activeStateIndexListPtr;
	eStatus = eclib_set_get_usage(activeStateSetPtr, &activeStateCount);
	if (ECLIB_OK != eStatus) {
		if (fsmContext->errorCallback != NULL) {
			fsmContext->errorCallback(ECLIB_ERROR);
		}
	}
	for (index = 0; index < activeStateCount; index ++) {
		eStatus = eclib_set_get(activeStateSetPtr, index, &activeStateIndex);
		if (ECLIB_OK != eStatus) {
			break;
		}
		statePtr = stm_find_state(activeStateIndex);
		transitionPtr = stm_find_transition(statePtr->transitionStartIndex);

		/// lookup for normal event to trigger transition
		lookupTransitionPtr = bsearch(	eventPtr,
										transitionPtr,
										statePtr->transitionCount,
										sizeof(stm_transition_t),
										stm_transition_compare);

		/// in case of no event transition, try null event
		if (0 == lookupTransitionPtr) {
			/// check for NULL event
			lookupTransitionPtr = bsearch( &__stm_null_event,
										transitionPtr,
										statePtr->transitionCount,
										sizeof(stm_transition_t),
										stm_transition_compare);
		}

		/// finally do the event transition action
		if (0 != lookupTransitionPtr) {
			transitionDetectionFlag = 1;
			/// state end DO activity
			action = stm_find_action(activeStateIndex, statePtr->doEndActionIndex);
			if (0 != action) {
				action();
			}

			/// state exit action
			action = stm_find_action(activeStateIndex, statePtr->exitActionIndex);
			if (0 != action) {
				action();
			}

			/// transition action
			action = stm_find_action(activeStateIndex, lookupTransitionPtr->actionIndex);
			if (0 != action) {
				action();
			}

			newStatePtr = stm_find_state(lookupTransitionPtr->toStateIndex);

			if (0 != newStatePtr) {
				eStatus = eclib_set_add(workingStateSetPtr, &lookupTransitionPtr->toStateIndex);
				if (ECLIB_OK != eStatus) {
					break;
				}

				/// new state entry action
				action = stm_find_action(activeStateIndex, newStatePtr->enterActionIndex);
				if (0 != action) {
					action();
				}

				/// new state start DO activity
				action = stm_find_action(activeStateIndex, newStatePtr->doStartActionIndex);
				if (0 != action) {
					action();
				}
			}
		}
	}

	if (0 != transitionDetectionFlag) {
		eclib_set_copy(activeStateSetPtr, workingStateSetPtr);
	}
	return result;
}

stm_state_ptr_t	stm_find_state(stm_index_t nodeIndex) {
	stm_state_ptr_t result = (stm_state_ptr_t) 0;
	if ((0 != fsmContext) && (0 != fsmContext->stateListPtr) && (STM_INDEX_INVALID != nodeIndex)) {
			return &fsmContext->stateListPtr[nodeIndex];
	}
	return result;
}

void stm_set_state_list(stm_state_ptr_t rootNode) {
	if (0 != fsmContext) {
		fsmContext->stateListPtr = rootNode;
	}
}

stm_transition_ptr_t	stm_find_transition(stm_index_t transitionIndex) {
	stm_transition_ptr_t result = (stm_transition_ptr_t) 0;
	if ((0 != fsmContext) && (0 != fsmContext->transitionListPtr) && (STM_INDEX_INVALID != transitionIndex)) {
		return &fsmContext->transitionListPtr[transitionIndex];
	}
	return result;
}

void stm_set_transition_list(stm_transition_ptr_t rootTransition) {
	if (0 != fsmContext) {
		fsmContext->transitionListPtr = rootTransition;
	}
}

void stm_set_action_list(stm_action_fn_ptr_t rootActionList) {
	if (0 != fsmContext) {
		fsmContext->actionListPtr = rootActionList;
	}
}

stm_action_fn_t stm_find_action(stm_index_t stateIndex, stm_index_t actionIndex) {
	stm_action_fn_t result = (stm_action_fn_t) 0;
	if ((0 != fsmContext) && (0 != fsmContext->actionListPtr) && (STM_INDEX_INVALID != actionIndex)) {
		result = fsmContext->actionListPtr[actionIndex];
	}
	return result;
}
