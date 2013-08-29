/*
 * eclib_queue.c
 *
 *  Created on: 2008-7-24
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include <eclib/eclib_queue.h>

#define ECLIB_QUEUE_VERSION_ID	0x0100

uint32_t eclib_queue_version() {
	return ECLIB_QUEUE_VERSION_ID;
}


eclib_status_t eclib_queue_init( eclib_queue_t * pQueue, void * pBuffer, uint16_t nSize, uint16_t nUnits )
{
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pQueue )
	{
		if ( NULL != pBuffer )
		{
			pQueue->nHeadIndex = 0;
			pQueue->nTailIndex = 0;
			pQueue->nUnits = nUnits;
			pQueue->nSize = nSize;
			pQueue->pBuffer = pBuffer;
			pQueue->nIsFull = 0;
			pQueue->eSignature = ECLIB_SIGNATURE_QUEUE;

			eStatus = ECLIB_OK;
		} else {
			pQueue->eSignature = ECLIB_SIGNATURE_EMPTY;
		}
	} else {
	}

	return eStatus;
}

eclib_status_t eclib_queue_clear( eclib_queue_t * pQueue )
{
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pQueue )
	{
		pQueue->nHeadIndex = 0;
		pQueue->nTailIndex = 0;
		pQueue->nIsFull = 0;

		eStatus = ECLIB_OK;
	}
	return eStatus;
}

eclib_status_t eclib_queue_full( eclib_queue_t * pQueue )
{
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pQueue )
	{
		pQueue->nHeadIndex = 0;
		pQueue->nTailIndex = 0;
		pQueue->nIsFull = ECLIB_FULL;

		eStatus = ECLIB_OK;
	}
	return eStatus;
}

eclib_status_t eclib_queue_is_empty( eclib_queue_t * pQueue )
{
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pQueue )
	{
		if ( 0 == pQueue->nIsFull )
		{
			eStatus = (pQueue->nHeadIndex == pQueue->nTailIndex) ? ECLIB_EMPTY : ECLIB_OK ;
		} else {
			eStatus = ECLIB_OK;
		}
	}

	return eStatus;
}

eclib_status_t eclib_queue_is_full( eclib_queue_t * pQueue )
{
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pQueue )
	{
		eStatus = ( 0 == pQueue->nIsFull ) ? ECLIB_OK : ECLIB_FULL;
	}

	return eStatus;
}

static void eclib_queue_head_inc( eclib_queue_t * pQueue )
{
	pQueue->nHeadIndex ++;
	pQueue->nHeadIndex %= pQueue->nUnits;
}

static void eclib_queue_tail_inc( eclib_queue_t * pQueue )
{
	pQueue->nTailIndex ++;
	pQueue->nTailIndex %= pQueue->nUnits;
}

eclib_status_t eclib_queue_push( eclib_queue_t * pQueue, void * pData )
{
	eclib_status_t eStatus;

	eStatus = eclib_queue_is_full( pQueue );
	if ( ECLIB_FULL != eStatus )
	{
		if ( NULL != pData )
		{
			eclib_memcpy( ((uint8_t *)pQueue->pBuffer) + pQueue->nSize * pQueue->nHeadIndex, pData, pQueue->nSize );
			eclib_queue_head_inc( pQueue );
			if ( pQueue->nHeadIndex ==  pQueue->nTailIndex )
			{
				pQueue->nIsFull = ECLIB_FULL;
			}
			eStatus = ECLIB_OK;
		} else {
			eStatus = ECLIB_NULL_POINTER;
		}
	}

	return eStatus;
}

eclib_status_t eclib_queue_pop( eclib_queue_t * pQueue, void * pData )
{
	eclib_status_t eStatus;

	eStatus = eclib_queue_is_empty( pQueue );
	if ( ECLIB_EMPTY != eStatus )
	{
		if ( NULL != pData )
		{
			eclib_memcpy( pData, ((uint8_t *)pQueue->pBuffer) + pQueue->nSize * pQueue->nTailIndex, pQueue->nSize );
			eclib_queue_tail_inc( pQueue );
			if ( 0 != pQueue->nIsFull )
			{
				pQueue->nIsFull = 0;
			}
		} else {
			eStatus = ECLIB_NULL_POINTER;
		}
	}

	return eStatus;
}

eclib_status_t eclib_queue_peek( eclib_queue_t * pQueue, void * pData )
{
	eclib_status_t eStatus;

	eStatus = eclib_queue_is_empty( pQueue );
	if ( ECLIB_EMPTY != eStatus )
	{
		if ( NULL != pData )
		{
			eclib_memcpy( pData, ((uint8_t *)pQueue->pBuffer) + pQueue->nSize * pQueue->nTailIndex, pQueue->nSize );
			if ( 0 != pQueue->nIsFull )
			{
				pQueue->nIsFull = 0;
			}
		} else {
			eStatus = ECLIB_NULL_POINTER;
		}
	}

	return eStatus;
}

uint16_t eclib_queue_get_queue_size(eclib_queue_ptr_t pQueue) {
  return pQueue->nUnits;
}

uint16_t eclib_queue_get_usage(eclib_queue_ptr_t pQueue) {
  int16_t size = pQueue->nHeadIndex - pQueue->nTailIndex;
  if (size < 0) {
    size += pQueue->nUnits;
  }
  return size;
}

uint16_t eclib_queue_get_head_index(eclib_queue_ptr_t pQueue) {
  return pQueue->nHeadIndex;
}

uint16_t eclib_queue_get_tail_index(eclib_queue_ptr_t pQueue) {
  return pQueue->nTailIndex;
}
