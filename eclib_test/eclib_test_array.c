/*
 * eclib_test_array.c
 *
 *  Created on: 2008-7-25
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */


#include <eclib/eclib_types.h>
#include <eclib/eclib_array.h>
#include <stdio.h>

#define ECLIB_ARRAY_TEST_UNITS1	10
#define ECLIB_ARRAY_TEST_UNITS2	5

ECLIB_ARRAY(uint16Array, sizeof(uint16_t), ECLIB_ARRAY_TEST_UNITS1);

uint16_t eclib_test_array(void)
{
	uint16_t	nErrors = 0;
	uint16_t	i;
	eclib_status_t	eStatus;
	uint16_t	nErrorsFound;
//	uint16_t	n;
	uint32_t	eclib_array_version_id = eclib_array_version();

	printf("%s: %s\tv.%x\n", __FILE__, __DATE__, eclib_array_version_id);

	nErrorsFound = 0;
	for ( i = 0; i <= ECLIB_ARRAY_TEST_UNITS1; i ++ )
	{
		eStatus = eclib_array_add( &uint16Array, &i, NULL );
		printf("array_add<%d>( %d , %d )\n", i, i, eStatus);
		if ( ECLIB_OK != eStatus )
		{
			nErrorsFound ++;
		}
	}
	if ( 1 != nErrorsFound )
	{
		nErrors ++;
	}
	i = 5;
	eStatus = eclib_array_remove( &uint16Array, i );
	printf("array_remove<%d>( %d )\n", i, eStatus);
	if ( ECLIB_OK != eStatus )
	{
		nErrorsFound ++;
	}
	eStatus = eclib_array_add( &uint16Array, &i, NULL );
	printf("array_add<%d>( %d , %d )\n", i, i, eStatus);
	if ( ECLIB_OK != eStatus )
	{
		nErrorsFound ++;
	}
	eStatus = eclib_array_add( &uint16Array, &i, NULL );
	printf("array_add<%d>( %d , %d )\n", i, i, eStatus);
	if ( ECLIB_OK != eStatus )
	{
		nErrorsFound ++;
	}

	return nErrors;
}
