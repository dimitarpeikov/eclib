/*
 * eclib_queue2.c
 *
 *  Created on: 2008-7-24
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include <eclib/eclib_queue2.h>

eclib_status_t eclib_queue2_init( eclib_queue2_t * pQueue, void * pBuffer, uint16_t nSize, uint16_t nUnits )
{
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pQueue )
	{
		if ( NULL != pBuffer )
		{
			pQueue->nHeadIndex = 0;
			pQueue->nUsedUnits = 0;
			pQueue->nTotalUnits = nUnits;
			pQueue->nSize = nSize;
			pQueue->pBuffer = pBuffer;
			pQueue->eSignature = ECLIB_SIGNATURE_QUEUE;

			eStatus = ECLIB_OK;
		} else {
			pQueue->eSignature = ECLIB_SIGNATURE_EMPTY;
		}
	} else {
	}

	return eStatus;
}

eclib_status_t eclib_queue2_clear( eclib_queue2_t * pQueue )
{
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pQueue )
	{
		pQueue->nHeadIndex = 0;
		pQueue->nUsedUnits = 0;
#ifdef ECLIB_PROFILING
		pQueue->nMaxUsage = 0;
#endif

		eStatus = ECLIB_OK;
	}
	return eStatus;
}

eclib_status_t eclib_queue2_full( eclib_queue2_t * pQueue )
{
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pQueue )
	{
		pQueue->nHeadIndex = 0;
		pQueue->nUsedUnits = pQueue->nTotalUnits;
#ifdef ECLIB_PROFILING
		pQueue->nMaxUsage = pQueue->nTotalUnits;
#endif

		eStatus = ECLIB_OK;
	}
	return eStatus;
}

eclib_status_t eclib_queue2_is_empty( eclib_queue2_t * pQueue )
{
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pQueue )
	{
		eStatus = ( 0 == pQueue->nUsedUnits ) ? ECLIB_EMPTY : ECLIB_OK ;
	}

	return eStatus;
}

eclib_status_t eclib_queue2_is_full( eclib_queue2_t * pQueue )
{
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pQueue )
	{
		eStatus = ( pQueue->nTotalUnits == pQueue->nUsedUnits) ? ECLIB_FULL : ECLIB_OK ;
	}

	return eStatus;
}

eclib_status_t eclib_queue2_push( eclib_queue2_t * pQueue, void * pData )
{
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	eStatus = eclib_queue2_is_full( pQueue );
	if ( ECLIB_OK == eStatus )
	{
		if ( NULL != pData )
		{
			eclib_memcpy( ((uint8_t *)pQueue->pBuffer) + pQueue->nSize * pQueue->nHeadIndex, pData, pQueue->nSize );
			pQueue->nHeadIndex ++;
			if ( pQueue->nHeadIndex >= pQueue->nTotalUnits )
			{
				pQueue->nHeadIndex -= pQueue->nTotalUnits;
			}
			pQueue->nUsedUnits ++;
#ifdef ECLIB_PROFILING
			if (pQueue->nUsedUnits > pQueue->nMaxUsage) {
				pQueue->nMaxUsage = pQueue->nUsedUnits;
			}
#endif
		}
	}

	return eStatus;
}

eclib_status_t eclib_queue2_pop( eclib_queue2_t * pQueue, void * pData )
{
	eclib_status_t eStatus;
	int16_t		nIndex;

	eStatus = eclib_queue2_is_empty( pQueue );
	if ( ECLIB_OK == eStatus )
	{
		if ( NULL != pData )
		{
			nIndex = pQueue->nHeadIndex - pQueue->nUsedUnits;
			if ( nIndex < 0 )
			{
				nIndex += pQueue->nTotalUnits;
			}
			eclib_memcpy( pData, ((uint8_t *)pQueue->pBuffer) + pQueue->nSize * nIndex, pQueue->nSize );
			pQueue->nUsedUnits --;
		} else {
			eStatus = ECLIB_NULL_POINTER;
		}
	}

	return eStatus;
}

eclib_status_t eclib_queue2_peek( eclib_queue2_t * pQueue, void * pData )
{
	eclib_status_t eStatus;
	int16_t		nIndex;

	eStatus = eclib_queue2_is_empty( pQueue );
	if ( ECLIB_OK == eStatus )
	{
		if ( NULL != pData )
		{
			nIndex = pQueue->nHeadIndex - pQueue->nUsedUnits;
			if ( nIndex < 0 )
			{
				nIndex += pQueue->nTotalUnits;
			}
			eclib_memcpy( pData, ((uint8_t *)pQueue->pBuffer) + pQueue->nSize * nIndex, pQueue->nSize );
		} else {
			eStatus = ECLIB_NULL_POINTER;
		}
	}

	return eStatus;
}

uint16_t eclib_queue2_get_usage( eclib_queue2_ptr_t pQueue ) {
	return pQueue->nUsedUnits;
}

#ifdef ECLIB_PROFILING
uint16_t eclib_queue2_get_max_usage( eclib_queue2_ptr_t pQueue ) {
	return pQueue->nMaxUsage;
}
#endif

uint16_t eclib_queue2_get_tail_index( eclib_queue2_ptr_t pQueue ) {
	int16_t		nIndex;
	nIndex = pQueue->nHeadIndex - pQueue->nUsedUnits;
	if ( nIndex < 0 )
	{
		nIndex += pQueue->nTotalUnits;
	}
	return nIndex;
}

uint16_t eclib_queue2_get_head_index( eclib_queue2_ptr_t pQueue ) {
	return pQueue->nHeadIndex;
}

uint16_t eclib_queue2_get_queue_size( eclib_queue2_ptr_t pQueue ) {
	return pQueue->nTotalUnits;
}
