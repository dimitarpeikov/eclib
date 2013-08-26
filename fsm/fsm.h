/*
 * stm.h
 *
 *  Created on: May 2, 2011
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#ifndef STM_H_
#define STM_H_

#include <eclib/eclib_types.h>
#include <eclib/eclib_set.h>

typedef uint16_t 		stm_index_t;
typedef uint16_t			stm_event_id_t;

#define STM_INDEX_INVALID (0xFFFF)

typedef void (*stm_action_fn_t)();
typedef void (*stm_error_callback_t)(eclib_status_t);
typedef stm_action_fn_t *	stm_action_fn_ptr_t;

typedef enum stm_state_type {
	STM_INITIAL,		/// Initial state
	STM_STATE,			/// State
	STM_FORK,			/// Fork sync bar
	STM_JOIN,			/// Join sync bar
	STM_CONDITION,		/// Condition connector
	STM_HISTORY,		/// History connector
	STM_TERMINATION,	/// Termination connector
	STM_JUNCTION,		/// Junction connector
	STM_PSEUDO, 		/// Enter Exit point
	STM_NODE_COUNT
} stm_state_type_t;

typedef struct stm_state {
	stm_state_type_t		stateType;
	stm_index_t				transitionStartIndex;
	stm_index_t				transitionCount;
	stm_index_t				enterActionIndex;
	stm_index_t				exitActionIndex;
	stm_index_t				doStartActionIndex;
	stm_index_t				doEndActionIndex;
} stm_state_t;
typedef stm_state_t * stm_state_ptr_t;

#if 1
typedef struct stm_event {
	stm_event_id_t			event;
	void * 					ptr;
} stm_event_t;
#endif
typedef stm_event_t *		stm_event_ptr_t;

/*!
	@struct stm_transition Transition definition
	@brief
*/
typedef struct stm_transition {
	stm_event_t				event;
	stm_index_t				toStateIndex;
	stm_index_t				actionIndex;
} stm_transition_t;
typedef stm_transition_t *	stm_transition_ptr_t;


typedef struct stm_fsm_context {
	stm_transition_ptr_t	transitionListPtr;
	stm_state_ptr_t			stateListPtr;
	stm_action_fn_ptr_t		actionListPtr;
	eclib_set_ptr_t			activeStateIndexListPtr;
	eclib_set_ptr_t			workStateListPtr;
	stm_action_fn_t			errorCallback;
} stm_fsm_context_t;
typedef stm_fsm_context_t *	stm_fsm_context_ptr_t;


void						stm_traversal_start();
void						stm_traversal_start_from_state(stm_index_t startStateIndex);

/*!
 *
 * @param eventPtr
 * @return
 */
stm_index_t					stm_process_event(stm_event_ptr_t eventPtr);


/*!
 * Look for state
 * @param stateIndex
 * @return reference to state
 */
stm_state_ptr_t				stm_find_state(stm_index_t stateIndex);

/*!
 * Look for transition
 * @param transitionIndex
 * @return reference to looked transition
 */
stm_transition_ptr_t		stm_find_transition(stm_index_t transitionIndex);

/*!
 * Look for action function
 * @param stateIndex
 * @param actionIndex
 * @return reference to looked action
 */
stm_action_fn_t				stm_find_action(stm_index_t stateIndex, stm_index_t actionIndex);

/*!
 *
 * @param rootStateList
 */
void						stm_set_state_list(stm_state_ptr_t rootStateList);

/*!
 *
 * @param rootTransitionList
 */
void						stm_set_transition_list(stm_transition_ptr_t rootTransitionList);

/*!
 *
 * @param rootActionList
 */
void						stm_set_action_list(stm_action_fn_ptr_t rootActionList);

/*!
 *
 * @param fsmContextList
 */
void						stm_set_fsmContext(stm_fsm_context_ptr_t fsmContextList);

#endif /* STM_H_ */
