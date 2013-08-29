/*
 * eclib_test_queue.c
 *
 *  Created on: 2008-7-25
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include <eclib/eclib_queue.h>
#include <stdio.h>
#include <time.h>

#define ECLIB_QUEUE_TEST_UNITS1			10
#define ECLIB_QUEUE_TEST_UNITS2			5
#define ECLIB_QUEUE_TEST_UNITS3			5000UL
#define ECLIB_QUEUE_TEST_ITERATIONS		1000
#define ECLIB_QUEUE_TEST_ITERATIONS2	100

ECLIB_QUEUE(uint16Queue11 , sizeof(uint16_t), ECLIB_QUEUE_TEST_UNITS1);

ECLIB_QUEUE(uint16Queue13 , sizeof(uint16_t), ECLIB_QUEUE_TEST_UNITS3);

uint16_t eclib_test_queue(void)
{
	uint16_t	nErrors = 0;
	uint16_t	nErrorsFound;
	uint16_t	i, i2;
	uint16_t	n, nn;
	uint32_t	start_time = 0L;
	uint32_t	end_time = 0L;
	eclib_status_t	eStatus;
	uint32_t	eclib_queue_version_id = eclib_queue_version();

	printf("%s: %s\tv.%x\n", __FILE__, __DATE__, eclib_queue_version_id);
	/* check for push properly data into queue */
	nErrorsFound = 0;
	for ( i = 0; i <= ECLIB_QUEUE_TEST_UNITS1; i ++)
	{
		eStatus = eclib_queue_push(&uint16Queue11, &i);
//		printf("push<%d>( %d , %d )\n", i, i, eStatus);
		if ( ECLIB_OK != eStatus )
		{
			nErrorsFound ++;
		}
	}
	if ( nErrorsFound > 1 )
	{
		nErrors ++;
	}

	nErrorsFound = 0;
	/* check for pop properly data from queue */
	for ( i = 0; i <= ECLIB_QUEUE_TEST_UNITS1; i ++)
	{
		eStatus = eclib_queue_pop(&uint16Queue11, &i2);
//		printf("pop<%d>( %d , %d )\n", i, n, eStatus);
		if ( ECLIB_OK != eStatus )
		{
			nErrorsFound ++;
		}
	}
	if ( nErrorsFound > 1 )
	{
		nErrors ++;
	}

	/* check for push properly data into queue */
	eclib_queue_init(&uint16Queue11, uint16Queue11_buffer, sizeof(uint16_t), ECLIB_QUEUE_TEST_UNITS2);
//	printf("uint16Queue: %d\nuint16Queue_buffer: %d\n", sizeof(uint16Queue), sizeof(uint16Queue_buffer));
	nErrorsFound = 0;
	for ( i = 0; i <= ECLIB_QUEUE_TEST_UNITS2; i ++)
	{
		eStatus = eclib_queue_push(&uint16Queue11, &i);
//		printf("push<%d>( %d , %d )\n", i, i, eStatus);
		if ( ECLIB_OK != eStatus )
		{
			nErrorsFound ++;
		}
	}
	if ( nErrorsFound > ( 1 + ECLIB_QUEUE_TEST_UNITS1 - ECLIB_QUEUE_TEST_UNITS2 ) )
	{
		nErrors ++;
	}

	nErrorsFound = 0;
	/* check for pop properly data from queue */
	for ( i = 0; i <= ECLIB_QUEUE_TEST_UNITS2; i ++)
	{
		eStatus = eclib_queue_pop(&uint16Queue11, &i2);
//		printf("pop<%d>( %d , %d )\n", i, n, eStatus);
		if ( ECLIB_OK != eStatus )
		{
			nErrorsFound ++;
		}
	}
	if ( nErrorsFound > ( 1 + ECLIB_QUEUE_TEST_UNITS1 - ECLIB_QUEUE_TEST_UNITS2 ) )
	{
		nErrors ++;
	}

	nErrorsFound = 0;
	start_time = clock();
	/* check queue push performance */
	for ( nn = 0; nn < ECLIB_QUEUE_TEST_ITERATIONS2; nn ++ )
	{
		for ( n = 0; n < ECLIB_QUEUE_TEST_ITERATIONS; n ++ )
		{
			eStatus = eclib_queue_clear( &uint16Queue13 );
			for ( i = 0; i < ECLIB_QUEUE_TEST_UNITS3; i ++)
			{
				eStatus = eclib_queue_push(&uint16Queue13, &i);
				if ( ECLIB_OK != eStatus )
				{
					nErrorsFound ++;
				}
			}
		}
	}
	end_time = clock();
	printf("push<%d>( %d , %d )\t%d\n", i, n, eStatus, end_time-start_time);

	nErrorsFound = 0;
	start_time = clock();
	/* check queue pop performance */
	for ( nn = 0; nn < ECLIB_QUEUE_TEST_ITERATIONS2; nn ++ )
	{
		for ( n = 0; n < ECLIB_QUEUE_TEST_ITERATIONS; n ++ )
		{
			eStatus = eclib_queue_full( &uint16Queue13 );
			for ( i = 0; i < ECLIB_QUEUE_TEST_UNITS3; i ++ )
			{
				eStatus = eclib_queue_pop( &uint16Queue13, &i2 );
				if ( ECLIB_OK != eStatus )
				{
					nErrorsFound ++;
				}
			}
		}
	}
	end_time = clock();
	printf("pop<%d>( %d , %d )\t%d\n", i, n, eStatus, end_time-start_time);

	return nErrors;
}
