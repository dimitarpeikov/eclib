/*
 * eclib_set.h
 *
 *  Created on: 2008-7-24
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#ifndef ECLIB_SET_H_
#define ECLIB_SET_H_

#include <eclib/eclib_types.h>

/*!
 * @struct eclib_set_struct
 */
struct eclib_set_struct
{
	uint16_t	nSignature;	//!< signature
	uint16_t	nUnitSize;		//!< number of units in the set
	uint16_t	nCount;		//!< size of the single unit
	uint16_t	nUsageCount;//!< usage utilization
	uint8_t		pBuffer[0];	//!< pointer to the data storage
};
/*!
 * @typedef eclib_set_t structure eclib_set_struct
 */
typedef struct eclib_set_struct		eclib_set_t;
typedef eclib_set_t *				eclib_set_ptr_t;

#define ECLIB_SET_BUFFER_DECLARE(name)	name##_buffer

#define ECLIB_SET_BUFFER_DEF(name, size, units)				\
		uint8_t	ECLIB_SET_BUFFER_DECLARE(name)[units * size + sizeof(eclib_set_t)]

#define ECLIB_SET(name, size, units)						\
	ECLIB_SET_BUFFER_DEF(name, size, units);				\
	eclib_set_ptr_t name = (eclib_set_ptr_t) &ECLIB_SET_BUFFER_DECLARE(name);

/*!
 * @fn eclib_set_init( eclib_set_ptr_t pSet, uint16_t nInitUnitSize, uint16_t nInitCount )
 * @brief	initialize set structure in RAM
 * @param	nInitUnitSize number of items in the set
 * @param	nInitCount size of the element
 * @return	operation status
 */
eclib_status_t	eclib_set_init( eclib_set_ptr_t pSet, uint16_t nInitUnitSize, uint16_t nInitCount );

/*!
 * @fn eclib_set_clear( eclib_set_ptr_t pSet )
 * @brief	initialize set structure in RAM
 * @return	operation status
 */
eclib_status_t	eclib_set_clear( eclib_set_ptr_t pSet);

/*!
 * @fn eclib_set_find(eclib_set_ptr_t pSet, void * pData, uint16_t * pIndex)
 * @brief	add data to the set
 * @param	pSet reference to set structure
 * @param	pData reference to data to add
 * @param	pIndex reference where to store index of item to add
 * @return	operation status
 */
eclib_status_t	eclib_set_find(eclib_set_ptr_t pSet, void * pData, uint16_t * pIndex);

/*!
 * @fn eclib_set_add(eclib_set_ptr_t pSet, void * pData)
 * @brief	add data to the set
 * @param	pSet reference to set structure
 * @param	pData reference to data to add
 * @return	operation status
 */
eclib_status_t	eclib_set_add(eclib_set_ptr_t pSet, void * pData);

/*!
 * @fn eclib_set_add_set(eclib_set_ptr_t pSet, eclib_set_t * pAddSet)
 * @brief	add data to the set
 * @param	pSet reference to set structure
 * @param	pAddSet reference to set to add
 * @return	operation status
 */
eclib_status_t	eclib_set_add_set(eclib_set_ptr_t pSet, eclib_set_ptr_t pAddSet);

/*!
 * @fn eclib_set_add_set(eclib_set_ptr_t pSet, eclib_set_t * pSrcSet)
 * @brief	copy pSrcSet to the set. Both sets have to be with the same size.
 * @param	pSet reference to set structure
 * @param	pSrcSet reference to source set to copy
 * @return	operation status
 */
eclib_status_t	eclib_set_copy(eclib_set_ptr_t pSet, eclib_set_ptr_t pSrcSet);

/*!
 * @fn eclib_set_get(eclib_set_ptr_t pSet, uint16_t nIndex, void * pData)
 * @brief	get data from the set
 * @return	operation status
 */
eclib_status_t	eclib_set_get(eclib_set_ptr_t pSet, uint16_t nIndex, void * pData);

/*!
 * @fn eclib_set_get_usage(eclib_set_ptr_t pSet, uint16_t * pIndex)
 * @brief	get data from the set
 * @param	pSet reference to set
 * @param	pIndex valid object to return count
 * @return	operation status
 */
eclib_status_t	eclib_set_get_usage(eclib_set_ptr_t pSet, uint16_t * pIndex);

/*!
 * @fn eclib_set_remove(eclib_set_ptr_t pSet, uint16_t nIndex )
 * @brief	remove element from the set
 * @return	operation status
 */
eclib_status_t	eclib_set_remove(eclib_set_ptr_t pSet, uint16_t nIndex);

void eclib_set_dump(eclib_set_ptr_t pSet);

#endif /* ECLIB_ARRAY_H_ */
