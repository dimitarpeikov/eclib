/*
 * eclib_types.h
 *
 *  Created on: 2008-7-24
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include <eclib/eclib_timer.h>

#define ECLIB_TIMER_VERSION_ID	0x0100

uint32_t eclib_timer_version() {
	return ECLIB_TIMER_VERSION_ID;
}


/* rolling [ms] timer counter. 0ms is illegal value. */
volatile eclib_timer_t __counter_1ms = 1L;

eclib_status_t eclib_timer_start_timer(eclib_timer_ptr_t pTimer) {
	eclib_status_t result = ECLIB_OK;
	if (NULL != pTimer) {
		(*pTimer) = __counter_1ms;
	} else {
		result = ECLIB_NULL_POINTER;
	}
	return result;
}

eclib_status_t eclib_timer_stop_timer(eclib_timer_ptr_t pTimer) {
	eclib_status_t result = ECLIB_OK;
	if (NULL != pTimer) {
		/* 0ms means timer is stopped */
		(*pTimer) = 0L;
	} else {
		result = ECLIB_NULL_POINTER;
	}
	return result;
}

eclib_timer_t eclib_timer_get_elapsed_time(eclib_timer_ptr_t pTimer) {
	eclib_timer_t _time = 0L;
	if ((NULL != pTimer) && (0 != *pTimer)) {
		_time = __counter_1ms;
		if (_time < (*pTimer)) {
			_time --;
		}
		_time -= (*pTimer);
	}
	return _time;
}

uint8_t eclib_timer_is_elapsed_timeout(eclib_timer_ptr_t pTimer, eclib_timer_t msTimeout) {
  uint8_t result = 0L;
  eclib_timer_t _time = 0L;
  if ((NULL != pTimer) && (0 != *pTimer)) {
    _time = eclib_timer_get_elapsed_time(pTimer);
    if (_time >= msTimeout) {
      result = 1;
    }
  }
  return result;
}

uint8_t eclib_timer_is_timer_started(eclib_timer_ptr_t pTimer) {
  uint8_t result = 0L;
  if (NULL != pTimer) {
    result = (0 != (*pTimer));
  }
  return result;
}

eclib_timer_t eclib_timer_add_delta(eclib_timer_ptr_t pTimer, eclib_timer_t delta) {
	eclib_timer_t result = 0L;
	if ((NULL != pTimer) && (0L != *pTimer)) {
		*pTimer += delta;
		if (*pTimer < delta) {
			(*pTimer) ++;
		}
		result = *pTimer;
	}
	return result;
}
