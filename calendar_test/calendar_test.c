/*
 * calendar_test.c
 *
 *  Created on: Feb 19, 2012
 *      Author: Administrator
 */

#include <eclib/eclib_types.h>
#include <calendar/calendar.h>
#include <calendar/calendar_cb.h>
#include <stdio.h>

uint32_t _ticks = 0L;

typedef enum {
	TEST_OK,
	TEST_FAIL,
	TEST_INVALID_VALUE,
	TEST_NULL_POINTER
} test_status_t;

const char * test_status_t_names[] = {
	"TEST_OK",
	"TEST_FAIL",
	"TEST_INVALID_VALUE",
	"TEST_NULL_POINTER"
};

test_status_t seconds_tick_test() {
	calendar_time_t	start_time;
	calendar_time_t	end_time;
	test_status_t	result = TEST_OK;

	start_time = calendar_get_time();
	do {
		calendar_timer_cb();
		end_time = calendar_get_time();
	} while (end_time.second != 0);

	if (end_time.minute != (start_time.minute + 1)) {
		if (!((end_time.second == 0) && (start_time.second == 59))) {
			result = TEST_FAIL;
		}
	} else {
		if (start_time.hour != end_time.hour) {
			result = TEST_FAIL;
		}
	}

	if (end_time.hour != start_time.hour) {
		if (!((end_time.minute == 0) && (start_time.minute == 59))) {
			if (end_time.minute > 0) {
				if (end_time.minute != (start_time.minute + 1)) {
					result = TEST_FAIL;
				}
			} else {
				if (end_time.minute != 59) {
					result = TEST_FAIL;
				}
			}
			result = TEST_FAIL;
		}
	} else {
		if (end_time.minute == 0) {
			result = TEST_FAIL;
		}
	}

	return result;
}

int main() {
	test_status_t	test_result;
	test_result = seconds_tick_test();
	printf("seconds_tick_test() = [%s]\n", test_status_t_names[test_result]);
	return 0;
}

