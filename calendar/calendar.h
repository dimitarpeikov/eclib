/*
 * calendar.h
 *
 *  Created on: Feb 2, 2012
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#ifndef CALENDAR_H_
#define CALENDAR_H_

struct calendar_date_t {
	uint8_t		day;
	uint8_t		month;
	uint16_t	year;
};
typedef struct calendar_date_t calendar_date_t;
typedef calendar_date_t * datePtr_t;

struct calendar_time_t {
	uint8_t		second;
	uint8_t		minute;
	uint16_t	hour;
};
typedef struct calendar_time_t calendar_time_t;
typedef calendar_time_t * timePtr_t;

calendar_date_t calendar_get_date();
void calendar_set_date(calendar_date_t);

calendar_time_t calendar_get_time();
void calendar_set_time(calendar_time_t);

uint32_t calendar_get_unix_time();

#endif /* CALENDAR_H_ */
