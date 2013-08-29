/*
 * eclib_queue2.h
 *
 *  Created on: 2008-10-21
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#ifndef ECLIB_QUEUE2_H_
#define ECLIB_QUEUE2_H_


#include <eclib/eclib_types.h>

/*!
 * @struct eclib_queue2_struct
 */
struct eclib_queue2_struct
{
	eclib_signature_t		eSignature;		//!< signature
	volatile uint16_t		nHeadIndex;		//!< head index
	volatile uint16_t		nUsedUnits;		//!< tail index
	uint16_t				nSize;			//!< unit size
	volatile uint16_t		nTotalUnits;	//!< number of units
	void *					pBuffer;		//!< pointer to storage buffer
#ifdef ECLIB_PROFILING
	volatile uint16_t		nMaxUsage;		//!< max items kept in queue
#endif
};
/*!
 * \typedef eclib_queue2_t
 */
typedef struct eclib_queue2_struct 	eclib_queue2_t;
typedef eclib_queue2_t *			eclib_queue2_ptr_t;

#define ECLIB_QUEUE2_BUFFER(name, size, units)	\
	uint8_t	name##_buffer[units * size]

#define ECLIB_QUEUE2(name, size, units) \
	ECLIB_QUEUE2_BUFFER(name, size, units); \
	eclib_queue2_t	name = { \
	ECLIB_SIGNATURE_QUEUE, \
	0, \
	0, \
	size,	\
	units,	\
	name##_buffer \
	}

/*!
 * @fn eclib_queue2_version( )
 * @return	Returns library version number
 */
uint32_t eclib_queue2_version();


/*!
 * \fn eclib_queue2_init(eclib_queue2_ptr_t pQueue, void * pBuffer, uint16_t nSize, uint16_t nUnits)
 * \brief initialize queue buffer in RAM
 * \param pQueue pointer to eclib_queue2_t structure
 * \param pBuffer pointer to storage with minimum [nUnits * nSize] bytes
 * \param nSize number of bytes per element
 * \param nUnits maximum number of units in the queue
 * \return operation status
 */
eclib_status_t eclib_queue2_init( eclib_queue2_ptr_t pQueue, void * pBuffer, uint16_t nSize, uint16_t nUnits);

/*!
 * \fn eclib_queue2_clear( eclib_queue2_ptr_t pQueue )
 * \brief initialize queue buffer in RAM
 * \param pQueue pointer to eclib_queue2_t structure
 * \return operation status
 */
eclib_status_t eclib_queue2_clear( eclib_queue2_ptr_t pQueue);

/*!
 * \fn eclib_queue2_clear( eclib_queue2_ptr_t pQueue )
 * \brief initialize queue buffer in RAM
 * \param pQueue pointer to eclib_queue2_t structure
 * \return operation status
 */
eclib_status_t eclib_queue2_full( eclib_queue2_ptr_t pQueue);

/*!
 * \fn eclib_queue2_push( eclib_queue2_ptr_t pQueue, void * pData )
 * \brief push element in queue
 * \param pQueue pointer to eclib_queue2_t structure
 * \param pData pointer to data to be stored in the queue
 * \return operation status
 */
eclib_status_t eclib_queue2_push( eclib_queue2_ptr_t pQueue, void * pData );

/*!
 * @fn eclib_queue2_pop( eclib_queue2_ptr_t pQueue, void * pData )
 * \brief pop element from queue
 * \param pQueue pointer to eclib_queue2_t structure
 * \param pData pointer to data to be stored in the queue
 * \return operation status
 */
eclib_status_t eclib_queue2_pop( eclib_queue2_ptr_t pQueue, void * pData );

/*!
 * @fn eclib_queue2_peek( eclib_queue2_ptr_t pQueue, void * pData )
 * \brief returns next element from queue, without moving to next element
 * \param pQueue pointer to eclib_queue2_t structure
 * \param pData pointer to data to be stored in the queue
 * \return operation status
 */
eclib_status_t eclib_queue2_peek( eclib_queue2_ptr_t pQueue, void * pData );

/*!
 * @fn eclib_queue2_get_usage( eclib_queue2_ptr_t pQueue )
 * \brief returns the current queue usage
 * \param pQueue pointer to eclib_queue2_t structure
 * \return number of items in the queue
 */
uint16_t eclib_queue2_get_usage( eclib_queue2_ptr_t pQueue );

/*!
 * @fn eclib_queue2_get_head_index( eclib_queue2_ptr_t pQueue )
 * \brief returns the current queue head index
 * \param pQueue pointer to eclib_queue2_t structure
 * \return returns the current queue head index
 */
uint16_t eclib_queue2_get_head_index( eclib_queue2_ptr_t pQueue );

/*!
 * @fn eclib_queue2_get_tail_index( eclib_queue2_ptr_t pQueue )
 * \brief returns the current queue tail index
 * \param pQueue pointer to eclib_queue2_t structure
 * \return returns the current queue tail index
 */
uint16_t eclib_queue2_get_tail_index( eclib_queue2_ptr_t pQueue );

/*!
 * @fn eclib_queue2_get_queue_size( eclib_queue2_ptr_t pQueue )
 * \brief returns the maximum number of elements in the queue
 * \param pQueue pointer to eclib_queue2_t structure
 * \return returns the maximum number of elements in the queue
 */
uint16_t eclib_queue2_get_queue_size( eclib_queue2_ptr_t pQueue );

eclib_status_t eclib_queue2_is_empty( eclib_queue2_ptr_t pQueue );

#ifdef ECLIB_PROFILING
uint16_t eclib_queue2_get_max_usage(eclib_queue2_ptr_t pQueue);
#endif

#endif /* ECLIB_QUEUE2_H_ */
