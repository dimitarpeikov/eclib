/*
 * eclib_test_set.c
 *
 *  Created on: May 5, 2011
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include <eclib/eclib_set.h>
#include <stdio.h>

const char *set_error_msg[] = {
	"ECLIB_OK",
	"ECLIB_INITIALIZED",
	"ECLIB_ERROR",
	"ECLIB_NULL_POINTER",
	"ECLIB_NOT_FULL",
	"ECLIB_FULL",
	"ECLIB_EMPTY",
	"ECLIB_FOUND",
	"ECLIB_NOT_FOUND",
	"ECLIB_OUT_OF_BOUNDS",
	"ECLIB_NOT_IMPLEMENTED"
};

ECLIB_SET(u16Set, sizeof(uint16_t), 10);
ECLIB_SET(u16Set2, sizeof(uint16_t), 10);
ECLIB_SET(u16Set3, sizeof(uint16_t), 20);

uint16_t eclib_test_set(void) {
	uint16_t		nErrors = 0;
	uint16_t		i = 0;
	eclib_status_t	eStatus = ECLIB_OK;

	eclib_set_init(u16Set, sizeof(uint16_t), 10);
	eclib_set_init(u16Set2, sizeof(uint16_t), 10);
	eclib_set_init(u16Set3, sizeof(uint16_t), 20);
	eclib_set_dump(u16Set);
	eclib_set_dump(u16Set2);
	eclib_set_dump(u16Set3);

	printf("%s: %s\n", __FILE__, __DATE__);

 	for (i = 0; i < 10; i ++) {
		eStatus = eclib_set_add(u16Set, &i);
		printf("set_add( %d ), %d\n", i, eStatus);
		if ( ECLIB_OK != eStatus )
		{
			nErrors ++;
		}
	}
	eclib_set_dump(u16Set);
	eclib_set_dump(u16Set2);
	eclib_set_dump(u16Set3);

	eStatus = eclib_set_remove(u16Set, 1);
	printf("set_remove( 1, %d ), %d\n", 1, eStatus);
	if ( ECLIB_OK != eStatus )
	{
		nErrors ++;
	}
	eStatus = eclib_set_remove(u16Set, 3);
	printf("set_remove( 1, %d ), %d\n", 3, eStatus);
	if ( ECLIB_OK != eStatus )
	{
		nErrors ++;
	}
	eStatus = eclib_set_remove(u16Set, 5);
	printf("set_remove( 1, %d ), %d\n", 5, eStatus);
	if ( ECLIB_OK != eStatus )
	{
		nErrors ++;
	}
	eclib_set_dump(u16Set);
	eclib_set_dump(u16Set2);
	eclib_set_dump(u16Set3);

	for (i = 0; i < 3; i ++) {
		eStatus = eclib_set_add(u16Set2, &i);
		printf("set_add( %d ), %d\n", i, eStatus);
		if ( ECLIB_OK != eStatus )
		{
			nErrors ++;
		}
	}
	eclib_set_dump(u16Set);
	eclib_set_dump(u16Set2);
	eclib_set_dump(u16Set3);

	eStatus = eclib_set_add_set(u16Set2, u16Set);
	printf("set_add_set( 2, 1 ), %d\n", eStatus);
	if ( ECLIB_OK != eStatus )
	{
		nErrors ++;
	}
	eclib_set_dump(u16Set);
	eclib_set_dump(u16Set2);
	eclib_set_dump(u16Set3);

	eStatus = eclib_set_add_set(u16Set3, u16Set2);
	printf("set_add_set( 3, 2 ), %d\n", eStatus);
	if ( ECLIB_OK != eStatus )
	{
		nErrors ++;
	}
	eclib_set_dump(u16Set);
	eclib_set_dump(u16Set2);
	eclib_set_dump(u16Set3);

	return nErrors;
}


ECLIB_SET(container, sizeof(uint16_t), 10);

uint16_t eclib_test_set_2(void) {
	uint16_t nErrors = 0;
	uint16_t data = 1;
	uint16_t index = 0;
	eclib_status_t status;

	eclib_set_init(container, sizeof(uint16_t), 10);

	// add some data 1 and 2
	data = 1;
	status = eclib_set_add(container, &data);
	printf("eclib_set_add(1): %s\n", set_error_msg[status]);
	data = 2;
	status = eclib_set_add(container, &data);
	printf("eclib_set_add(2): %s\n", set_error_msg[status]);

	// now find the data 1 and 2
	data = 2;
	status = eclib_set_find(container, &data, &index);
	printf("eclib_set_find(2): %s, %d\n", set_error_msg[status], index);
	data = 1;
	status = eclib_set_find(container, &data, &index);
	printf("eclib_set_find(1): %s, %d\n", set_error_msg[status], index);

	// now remove some data -> error expected
	status = eclib_set_remove(container, 2);
	printf("eclib_set_remove(2): %s - error expected\n", set_error_msg[status]);

	// now remove some data -> last item
	status = eclib_set_remove(container, 1);
	printf("eclib_set_remove(1): %s\n", set_error_msg[status]);

	// now find the data 1 and 2
	data = 2;
	status = eclib_set_find(container, &data, &index);
	printf("eclib_set_find(2): %s, %d - error expected\n", set_error_msg[status], index);
	data = 1;
	status = eclib_set_find(container, &data, &index);
	printf("eclib_set_find(1): %s, %d\n", set_error_msg[status], index);

	// add removed data
	data = 2;
	status = eclib_set_add(container, &data);
	printf("eclib_set_add(2): %s\n", set_error_msg[status]);

	// now remove some data -> first item
	status = eclib_set_remove(container, 0);
	printf("eclib_set_remove(0): %s\n", set_error_msg[status]);

	// now find the data 1 and 2
	status = eclib_set_find(container, &data, &index);
	printf("eclib_set_find(2): %s, %d\n", set_error_msg[status], index);
	data --;
	status = eclib_set_find(container, &data, &index);
	printf("eclib_set_find(1): %s, %d - error expected\n", set_error_msg[status], index);

	return nErrors;
}
