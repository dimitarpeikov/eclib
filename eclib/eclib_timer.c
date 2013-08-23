/*
 * eclib_types.h
 *
 *  Created on: 2008-7-24
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include <eclib/eclib_timer.h>

/* rolling ms timer counter. 0ms is illegal value. */
volatile uint32_t __counter_1ms = 1L;

void eclib_timer_start_timer(uint32_ptr_t pTimer) {
  if (NULL != pTimer) {
    (*pTimer) = __counter_1ms;
  }
}

void eclib_timer_stop_timer(uint32_ptr_t pTimer) {
  if (NULL != pTimer) {
    /* 0ms means timer is stopped */
    (*pTimer) = 0L;
  }
}

uint32_t eclib_timer_get_elapsed_time(uint32_ptr_t pTimer) {
  uint32_t _time = 0L;
  if ((NULL != pTimer) && (0 != *pTimer)) {
    _time = __counter_1ms;
    if (_time < (*pTimer)) {
      _time --;
    }
    _time -= (*pTimer);
  }
  return _time;
}

uint32_t eclib_timer_is_elapsed_timeout(uint32_ptr_t pTimer, uint32_t msTimeout) {
  uint32_t result = 0L;
  uint32_t _time = 0L;
  if ((NULL != pTimer) && (0 != *pTimer)) {
    _time = eclib_timer_get_elapsed_time(pTimer);
    if (_time >= msTimeout) {
      result = 1;
    }
  }
  return result;
}

uint32_t eclib_timer_is_timer_started(uint32_ptr_t pTimer) {
  uint32_t result = 0L;
  if (NULL != pTimer) {
    result = (0 != (*pTimer));
  }
  return result;
}

uint32_t eclib_timer_add_delta(uint32_ptr_t pTimer, uint32_t delta) {
	uint32_t result = 0L;
	if ((NULL != pTimer) && (0L != *pTimer)) {
		*pTimer += delta;
		if (*pTimer < delta) {
			(*pTimer) ++;
		}
		result = *pTimer;
	}
	return result;
}
