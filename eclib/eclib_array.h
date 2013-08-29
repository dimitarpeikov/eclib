/*
 * eclib_array.h
 *
 *  Created on: 2008-7-24
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#ifndef ECLIB_ARRAY_H_
#define ECLIB_ARRAY_H_

#include <eclib/eclib_types.h>

/*!
 * @struct eclib_array_struct
 */
struct eclib_array_struct
{
	uint16_t	nSignature;	//!< signature
	uint16_t	nUnits;		//!< number of units in the array
	uint16_t	nSize;		//!< size of the single unit
	uint8_t *	pBitmap;	//!< pointer to bitmap usage storage ( nUnits / 8 in bytes )
	void *		pBuffer;	//!< pointer to the data storage
};
/*!
 * @typedef eclib_array_t structure eclib_array_struct
 */
typedef struct eclib_array_struct	eclib_array_t;
typedef eclib_array_t *				eclib_array_ptr_t;

#define ECLIB_ARRAY_BUFFER_DECLARE(name)	name##_buffer
#define ECLIB_ARRAY_BITMAP_DECLARE(name)	name##_bitmap

#define ECLIB_ARRAY_BITMAP_DEF(name, units)					\
	uint8_t	ECLIB_ARRAY_BITMAP_DECLARE(name)[(units + 7) / 8]

#define ECLIB_ARRAY_BUFFER_DEF(name, size, units)			\
		uint8_t	ECLIB_ARRAY_BUFFER_DECLARE(name)[units * size]

#define ECLIB_ARRAY(name, size, units)						\
	ECLIB_ARRAY_BITMAP_DEF(name, units);					\
	ECLIB_ARRAY_BUFFER_DEF(name, size, units);				\
	eclib_array_t	name = { 								\
	ECLIB_SIGNATURE_ARRAY, 									\
	units,													\
	size,													\
	ECLIB_ARRAY_BITMAP_DECLARE(name),						\
	ECLIB_ARRAY_BUFFER_DECLARE(name)						\
	}



/*!
 * @fn eclib_array_version( )
 * @return	Returns library version number
 */
uint32_t eclib_array_version();

/*!
 * @fn eclib_array_init( eclib_array_t * pArray, void * pBuffer, uint16_t nUnits, uint16_t nSize )
 * @brief	initialize array structure in RAM
 * @return	operation status
 */
eclib_status_t	eclib_array_init( eclib_array_t * pArray, void * pBuffer, uint16_t nUnits, uint16_t nSize );

/*!
 * @fn eclib_array_find(eclib_array_t * pArray, void * pData, uint16_t * pIndex)
 * @brief	find data item in array
 * @return	operation status
 */
eclib_status_t	eclib_array_find(eclib_array_t * pArray, void * pData, uint16_t * pIndex);

/*!
 * @fn eclib_array_add(eclib_array_t * pArray, void * pData, uint16_t * pIndex)
 * @brief	add data item to array
 * @return	operation status
 */
eclib_status_t	eclib_array_add(eclib_array_t * pArray, void * pData, uint16_t * pIndex);

/*!
 * @fn eclib_array_get(eclib_array_t * pArray, uint16_t nIndex, void * pData)
 * @brief	get data item from array
 * @return	operation status
 */
eclib_status_t	eclib_array_get(eclib_array_t * pArray, uint16_t nIndex, void * pData);

/*!
 * @fn eclib_array_remove(eclib_array_t * pArray, uint16_t nIndex )
 * @brief	remove data item from array
 * @return	operation status
 */
eclib_status_t	eclib_array_remove(eclib_array_t * pArray, uint16_t nIndex);


#endif /* ECLIB_ARRAY_H_ */
