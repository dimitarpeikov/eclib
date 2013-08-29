/*
 * eclib_array.c
 *
 *  Created on: 2008-7-25
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include <eclib/eclib_array.h>

#define ECLIB_ARRAY_VERSION_ID	0x0100

uint32_t eclib_array_version() {
	return ECLIB_ARRAY_VERSION_ID;
}

eclib_status_t	eclib_array_init( eclib_array_t * pArray, void * pBuffer, uint16_t nUnits, uint16_t nSize )
{
	eclib_status_t	eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pArray )
	{
		if ( NULL != pBuffer )
		{
			eStatus = ECLIB_OK;
			pArray->nSize = nSize;
			pArray->nUnits = nUnits;
			pArray->pBuffer = pBuffer;
			pArray->nSignature = ECLIB_SIGNATURE_ARRAY;
		} else {
		}
	} else {
	}

	return eStatus;
}

eclib_status_t	eclib_array_find( eclib_array_ptr_t pArray, void * pData, uint16_t * pIndex) {
	eclib_status_t eStatus = ECLIB_ERROR;
	uint16_t	nIndex;
	uint16_t	nMaxIndex;
	uint8_t		nIdx;
	uint8_t		nBitIndex;
	uint8_t		nMaxBitIndex;

	if (( NULL != pArray ) || (NULL != pData))
	{
		nMaxIndex = ( pArray->nUnits + 7 ) / 8;

		for ( nIndex = 0; nIndex < nMaxIndex; nIndex ++ )
		{
			if ( ECLIB_IDLE_CONST != pArray->pBitmap[ nIndex ] )
			{
				nMaxBitIndex = ((nIndex + 1) * 8 > pArray->nUnits) ? (pArray->nUnits - nIndex * 8) : 8;
				nIdx = pArray->pBitmap[ nIndex ];
				for ( nBitIndex = 0; nBitIndex < nMaxBitIndex; nBitIndex ++ )
				{
					/// check for used item inside the set
					if ( 1 == ( nIdx & ( 1 << nBitIndex )) )
					{
						/// check if the item is the one looked for
						if (0 == memcmp( ((uint8_t *) pArray->pBuffer) + pArray->nSize * ( nIndex * 8 + nBitIndex ), pData, pArray->nSize )) {
							/// item found
							eStatus = ECLIB_OK;
							if (pIndex != 0) {
								*pIndex = nIndex;
							}
							break;
						}
					}
				}
				if (ECLIB_OK == eStatus) {
					break;
				}
			}
		}
	} else {
		eStatus = ECLIB_NULL_POINTER;
	}

	return eStatus;
}

eclib_status_t	eclib_array_add( eclib_array_t * pArray, void * pData, uint16_t * pIndex )
{
	eclib_status_t eStatus = ECLIB_ERROR;
	uint16_t	nIndex;
	uint16_t	nMaxIndex;
	uint8_t		nIdx;
	uint8_t		nBitIndex;
	uint8_t		nMaxBitIndex;

	if (( NULL != pArray ) || (NULL != pData))
	{
		nMaxIndex = ( pArray->nUnits + 7 ) / 8;

		for ( nIndex = 0; nIndex < nMaxIndex; nIndex ++ )
		{
			if ( ECLIB_BUSY_CONST != pArray->pBitmap[ nIndex ] )
			{
				nMaxBitIndex = ((nIndex + 1) * 8 > pArray->nUnits) ? (pArray->nUnits - nIndex * 8) : 8;
				nIdx = pArray->pBitmap[ nIndex ];
				for ( nBitIndex = 0; nBitIndex < nMaxBitIndex; nBitIndex ++ )
				{
					if ( 0 == ( nIdx & ( 1 << nBitIndex )) )
					{
						memcpy( ((uint8_t *) pArray->pBuffer) + pArray->nSize * ( nIndex * 8 + nBitIndex ), pData, pArray->nSize );
						pArray->pBitmap[ nIndex ] |= 1 << nBitIndex;
						if (pIndex != 0) {
							*pIndex = nIndex;
						}
						eStatus = ECLIB_OK;
						break;
					}
				}
				break;
			}
		}
	} else {
		eStatus = ECLIB_NULL_POINTER;
	}

	return eStatus;
}

eclib_status_t	eclib_array_get( eclib_array_t * pArray, uint16_t nIndex, void * pData )
{
	eclib_status_t eStatus = ECLIB_ERROR;
	if (( NULL != pArray ) || (NULL != pData))
	{
		if ( 0 != (pArray->pBitmap[ nIndex / 8 ] & (1 << (nIndex & 7) )) )
		{
			memcpy( pData, ((uint8_t *)pArray->pBuffer) + pArray->nSize * nIndex, pArray->nSize );
			eStatus = ECLIB_OK;
		}
	} else {
		eStatus = ECLIB_NULL_POINTER;
	}

	return eStatus;
}

eclib_status_t	eclib_array_remove( eclib_array_t * pArray, uint16_t nIndex )
{
	eclib_status_t eStatus = ECLIB_ERROR;
	if ( NULL != pArray )
	{
		if ( 0 != (pArray->pBitmap[ nIndex / 8 ] & ( 1 << ( nIndex & 7 )) ) )
		{
			pArray->pBitmap[ nIndex / 8 ] &= ~(1 << ( nIndex & 7 ));
			eStatus = ECLIB_OK;
		}
	} else {
		eStatus = ECLIB_NULL_POINTER;
	}

	return eStatus;
}
