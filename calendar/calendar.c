/*
 * calendar.c
 *
 *  Created on: Feb 2, 2012
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include "calendar/calendar.h"

#define UNIX_TIME_START_YEAR		1970
#define UNIX_TIME_START_MONTH		1
#define UNIX_TIME_START_DAY			1
#define UNIX_TIME_START_WEEKDAY		4

static calendar_date_t calendar_internal_date;
static calendar_time_t calendar_internal_time;
static uint8_t calendar_month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void calendar_init() {
	memset(&calendar_internal_date, 0, sizeof(calendar_internal_date));
	memset(&calendar_internal_time, 0, sizeof(calendar_internal_time));
}

calendar_date_t calendar_get_date(){
	return calendar_internal_date;
}

void calendar_set_date(calendar_date_t new_date) {
	calendar_internal_date = new_date;
}

calendar_time_t calendar_get_time() {
	return calendar_internal_time;
}

void calendar_set_time(calendar_time_t new_time) {
	calendar_internal_time = new_time;
}

uint8_t calendar_get_leap_year(uint16_t year) {
	uint8_t leap = 0;

	if (0 == (year % 4)) {
		leap = 1;

		if (0 == year % 100) {
			leap = 0;
		}
	}

	return leap;
}

uint32_t calendar_get_unix_time() {
	uint32_t unix_time = 0L;
	uint32_t leap_days = 0L;
	uint8_t idx;
	uint8_t leap = calendar_get_leap_year(calendar_internal_date.year);

	unix_time = calendar_internal_date.year;
	if (unix_time >= UNIX_TIME_START_YEAR) {
		unix_time -= UNIX_TIME_START_YEAR;
	}
	/// Unix time in years

	// calculate leap days
	leap_days = (unix_time / 4) - (unix_time / 100);
	unix_time += unix_time * 365 + leap_days;
	for (idx = 0; idx < calendar_internal_date.month; idx ++) {
		unix_time += calendar_month_days[idx];
	}
	if ((calendar_internal_date.month > 1) && (0 != leap)) {
		unix_time ++;
	}
	/// Unix time in days

	unix_time += unix_time * 24 + calendar_internal_time.hour;
	/// Unix time in hours

	unix_time += unix_time * 60 + calendar_internal_time.minute;
	/// Unix time in minutes

	unix_time += unix_time * 60 + calendar_internal_time.second;
	/// Unix time in seconds

	return unix_time;
}

void calendar_increase_date(void) {
	uint8_t is_leap = calendar_get_leap_year(calendar_internal_date.year);

	// increase 1 day
	calendar_internal_date.day ++;
	if (calendar_internal_date.day > calendar_month_days[calendar_internal_date.month] + is_leap) {
		// month overflow
			calendar_internal_date.day = 0;
		calendar_internal_date.month ++;
		if (calendar_internal_date.month > 11) {
			// year overflow
			calendar_internal_date.month = 0;
			calendar_internal_date.year ++;
		}
	}
}

void calendar_increase_time(void) {
	// increase 1 second
	calendar_internal_time.second ++;
	if (calendar_internal_time.second >= 60) {
		// second overflow
		calendar_internal_time.second = 0;
		calendar_internal_time.minute ++;

		if (calendar_internal_time.minute >= 60) {
			// minute overflow
			calendar_internal_time.minute = 0;
			calendar_internal_time.hour ++;

			if (calendar_internal_time.hour >= 24) {
				// hour overflow
				calendar_internal_time.hour = 0;

				calendar_increase_date();
			}
		}
	}
}

/// Function to be registered at 1s periodic activation
void calendar_timer_cb(void) {
	calendar_increase_time();
}


