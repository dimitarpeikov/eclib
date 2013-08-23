/*
 * eclib_set.c
 *
 *  Created on: 2008-7-25
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include <eclib/eclib_set.h>
#include <stdio.h>

eclib_status_t	eclib_set_init( eclib_set_ptr_t pSet, uint16_t nInitUnitSize, uint16_t nInitCount )
{
	eclib_status_t	eStatus = ECLIB_NULL_POINTER;

	if ( NULL != pSet )
	{
		pSet->nCount = nInitCount;
		pSet->nUnitSize = nInitUnitSize;
		pSet->nUsageCount = 0;
		pSet->nSignature = ECLIB_SIGNATURE_SET;
		eStatus = ECLIB_OK;
	}

	return eStatus;
}

eclib_status_t	eclib_set_clear( eclib_set_ptr_t pSet) {
	eclib_status_t eStatus = ECLIB_NULL_POINTER;
	if (pSet != NULL) {
		pSet->nUsageCount = 0;
		eStatus = ECLIB_OK;
	}
	return eStatus;
}

eclib_status_t	eclib_set_find( eclib_set_ptr_t pSet, void * pData, uint16_t * pIndex) {
	eclib_status_t eStatus = ECLIB_NOT_FOUND;
	uint16_t	nIndex = 0;
	uint16_t	nMaxIndex;
	uint16_t	nLowIndex = 0;
	int			nCmpResult;

	if (( NULL != pSet ) && (NULL != pData))
	{
		nMaxIndex = pSet->nUsageCount;
		nIndex = (nMaxIndex + nLowIndex) / 2;
		while ((nMaxIndex >= nLowIndex) && (nIndex < nMaxIndex)){
			nCmpResult = memcmp( ((uint8_t *) pSet->pBuffer) + (pSet->nUnitSize * nIndex),
									pData,
									pSet->nUnitSize );
			if (nCmpResult == 0) {
				// item found inside the set
				eStatus = ECLIB_FOUND;
				break;
			}
			if (nCmpResult < 0) {
				nLowIndex = ++nIndex;
			} else {
				// possible underflow for nMaxIndex in case nIndex == 0
				if (nIndex == 0) {
					break;
				}
				nMaxIndex = nIndex;
			}
			nIndex = (nMaxIndex + nLowIndex) / 2;
		}
		if (pIndex != 0) {
			*pIndex = nIndex;
		}
	} else {
		eStatus = ECLIB_NULL_POINTER;
	}

	return eStatus;
}

eclib_status_t	eclib_set_add( eclib_set_ptr_t pSet, void * pData )
{
	eclib_status_t eStatus = ECLIB_ERROR;
	uint16_t	nIndex;
	eclib_status_t setContainStatus;

	if (( NULL != pSet ) && (NULL != pData))
	{
		/// try to find if item is already in the set
		setContainStatus = eclib_set_find(pSet, pData, &nIndex);
		if ((setContainStatus == ECLIB_NOT_FOUND) && (pSet->nUsageCount < pSet->nCount)) {
			if (nIndex < pSet->nUsageCount) {
				memcpy( ((uint8_t *) pSet->pBuffer) + (pSet->nUnitSize * (nIndex + 1)),
						((uint8_t *) pSet->pBuffer) + (pSet->nUnitSize * nIndex),
						pSet->nUnitSize * (pSet->nUsageCount - nIndex) );
			}
			memcpy( ((uint8_t *) pSet->pBuffer) + (pSet->nUnitSize * nIndex), pData, pSet->nUnitSize );
			pSet->nUsageCount ++;
			eStatus = ECLIB_OK;
		} else {
			if (setContainStatus == ECLIB_FOUND) {
				eStatus = ECLIB_OK;
			} else {
				eStatus = ECLIB_FULL;
			}
		}
	} else {
		eStatus = ECLIB_NULL_POINTER;
	}

	return eStatus;
}

eclib_status_t	eclib_set_add_set( eclib_set_ptr_t pSet, eclib_set_ptr_t pAddSet ) {
	eclib_status_t	eStatus = ECLIB_ERROR;
	uint16_t		nIndex;
	uint16_t		nMaxIndex;

	if ((NULL != pSet) && (NULL != pAddSet)) {
		if (pSet->nCount > (pSet->nUsageCount + pAddSet->nUsageCount)) {
			nMaxIndex = pAddSet->nUsageCount;
			eStatus = ECLIB_OK;
			for (nIndex = 0; (nIndex < nMaxIndex) && (eStatus == ECLIB_OK); nIndex ++) {
				eStatus = eclib_set_add(pSet, ((uint8_t *) pAddSet->pBuffer) + (pSet->nUnitSize * nIndex));
			}
		} else {
			eStatus = ECLIB_OUT_OF_BOUNDS;
		}
	} else {
		eStatus = ECLIB_NULL_POINTER;
	}

	return eStatus;
}

eclib_status_t	eclib_set_copy( eclib_set_ptr_t pSet, eclib_set_ptr_t pSrcSet ) {
	eclib_status_t	eStatus = ECLIB_ERROR;

	if ((NULL != pSet) && (NULL != pSrcSet)) {
		if ((pSet->nCount * pSet->nUnitSize) == (pSet->nCount * pSet->nUnitSize)) {
			memcpy(	pSet,
					pSrcSet,
					sizeof(eclib_set_t) + (pSet->nUnitSize * pSet->nUsageCount));
			eStatus = ECLIB_OK;
		} else {
			eStatus = ECLIB_OUT_OF_BOUNDS;
		}
	} else {
		eStatus = ECLIB_NULL_POINTER;
	}

	return eStatus;
}

eclib_status_t	eclib_set_get( eclib_set_ptr_t pSet, uint16_t nIndex, void * pData )
{
	eclib_status_t eStatus = ECLIB_ERROR;
	if (( NULL != pSet ) && (NULL != pData))
	{
		if ( nIndex < pSet->nUsageCount )
		{
			memcpy( pData,
					((uint8_t *)pSet->pBuffer) + pSet->nUnitSize * nIndex,
					pSet->nUnitSize );
			eStatus = ECLIB_OK;
		} else {
			eStatus = ECLIB_OUT_OF_BOUNDS;
		}
	} else {
		eStatus = ECLIB_NULL_POINTER;
	}

	return eStatus;
}

eclib_status_t	eclib_set_get_usage(eclib_set_ptr_t pSet, uint16_t * pIndex) {
	eclib_status_t eStatus = ECLIB_NULL_POINTER;

	if ((pSet != NULL) && (pIndex != NULL)) {
		*pIndex = pSet->nUsageCount;
		eStatus = ECLIB_OK;
	}

	return eStatus;
}

eclib_status_t	eclib_set_remove( eclib_set_ptr_t pSet, uint16_t nIndex )
{
	eclib_status_t eStatus = ECLIB_ERROR;
	if ( NULL != pSet )
	{
		if ( nIndex < pSet->nUsageCount )
		{
			memcpy( ((uint8_t *)pSet->pBuffer) + pSet->nUnitSize * nIndex,
					((uint8_t *)pSet->pBuffer) + pSet->nUnitSize * (nIndex + 1),
					pSet->nUnitSize * (pSet->nUsageCount - nIndex - 1));
			pSet->nUsageCount --;
			eStatus = ECLIB_OK;
		} else {
			eStatus = ECLIB_OUT_OF_BOUNDS;
		}
	} else {
		eStatus = ECLIB_NULL_POINTER;
	}

	return eStatus;
}

void eclib_set_dump(eclib_set_ptr_t pSet) {
	printf("eclib_set:%x, %6d, %6d, %6d\n", pSet->nSignature, pSet->nUnitSize, pSet->nCount, pSet->nUsageCount);
}
