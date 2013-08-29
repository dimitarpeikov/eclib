/*
 * eclib_types.h
 *
 *  Created on: 2008-7-24
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#ifndef __ECLIB_TIMER_H__
#define __ECLIB_TIMER_H__

typedef uint32_t		eclib_timer_t;
typedef uint32_ptr_t	eclib_timer_ptr_t;

/*!
 * @fn eclib_timer_version( )
 * @return	Returns library version number
 */
uint32_t eclib_timer_version();

eclib_status_t      eclib_timer_start_timer(eclib_timer_ptr_t pTimer);
eclib_status_t      eclib_timer_stop_timer(eclib_timer_ptr_t pTimer);
eclib_timer_t  eclib_timer_get_elapsed_time(eclib_timer_ptr_t pTimer);
uint8_t  eclib_timer_is_elapsed_timeout(eclib_timer_ptr_t pTtimer, eclib_timer_t msTimeout);
uint8_t  eclib_timer_is_timer_started(eclib_timer_ptr_t pTimer);
eclib_timer_t  eclib_timer_add_delta(eclib_timer_ptr_t pTimer, eclib_timer_t delta);

#endif
