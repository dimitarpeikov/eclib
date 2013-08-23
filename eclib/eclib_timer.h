/*
 * eclib_types.h
 *
 *  Created on: 2008-7-24
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#ifndef __ECLIB_TIMER_H__
#define __ECLIB_TIMER_H__

void      eclib_timer_start_timer(uint32_ptr_t pTimer);
void      eclib_timer_stop_timer(uint32_ptr_t pTimer);
uint32_t  eclib_timer_get_elapsed_time(uint32_ptr_t pTimer);
uint32_t  eclib_timer_is_elapsed_timeout(uint32_ptr_t pTtimer, uint32_t msTimeout);
uint32_t  eclib_timer_is_timer_started(uint32_ptr_t pTimer);
uint32_t  eclib_timer_add_delta(uint32_ptr_t pTimer, uint32_t delta);

#endif
