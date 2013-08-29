/*
 * eclib_queue.h
 *
 *  Created on: 2008-7-24
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#ifndef ECLIB_QUEUE_H_
#define ECLIB_QUEUE_H_


#include <eclib/eclib_types.h>

/*!
 * @struct eclib_queue_struct queue structure
 */
struct eclib_queue_struct
{
	eclib_signature_t		eSignature;	//!< signature
	uint16_t				nHeadIndex;	//!< head index
	uint16_t				nTailIndex;	//!< tail index
	uint16_t				nSize;		//!< unit size
	uint16_t				nUnits;		//!< number of units
	void *					pBuffer;	//!< pointer to storage buffer
	uint8_t					nIsFull;	//!< full flag
};
/*!
 * \typedef eclib_queue_t
 */
typedef struct eclib_queue_struct	eclib_queue_t;
typedef eclib_queue_t *				eclib_queue_ptr_t;

#define ECLIB_QUEUE_BUFFER(name, size, units)	\
	uint8_t	name##_buffer[units * size]

#define ECLIB_QUEUE(name, size, units) \
	ECLIB_QUEUE_BUFFER(name, size, units); \
	eclib_queue_t	name = { \
	ECLIB_SIGNATURE_QUEUE, \
	0, \
	0, \
	size,	\
	units,	\
	name##_buffer \
	}

/*!
 * @fn eclib_queue_version( )
 * @return	Returns library version number
 */
uint32_t eclib_queue_version();


/*!
 * \fn eclib_queue_init(eclib_queue_t * pQueue, void * pBuffer, uint16_t nSize, uint16_t nUnits)
 * \brief initialize queue buffer in RAM
 * \param pQueue pointer to eclib_queue_t structure
 * \param pBuffer pointer to storage with minimum [nUnits * nSize] bytes
 * \param nSize number of bytes per element
 * \param nUnits maximum number of units in the queue
 * \return operation status
 */
eclib_status_t eclib_queue_init( eclib_queue_t * pQueue, void * pBuffer, uint16_t nSize, uint16_t nUnits);

/*!
 * \fn eclib_queue_clear( eclib_queue_t * pQueue )
 * \brief initialize queue buffer in RAM
 * \param pQueue pointer to eclib_queue_t structure
 * \return operation status
 */
eclib_status_t eclib_queue_clear( eclib_queue_t * pQueue );

/*!
 * \fn eclib_queue_full( eclib_queue_t * pQueue )
 * \brief initialize queue buffer in RAM
 * \param pQueue pointer to eclib_queue_t structure
 * \return operation status
 */
eclib_status_t eclib_queue_full( eclib_queue_t * pQueue );

/*!
 * \fn eclib_queue_push( eclib_queue_t * pQueue, void * pData )
 * \brief push element in queue
 * \param pQueue pointer to eclib_queue_t structure
 * \param pData pointer to data to be stored in the queue
 * \return operation status
 */
eclib_status_t eclib_queue_push( eclib_queue_t * pQueue, void * pData );

/*!
 * @fn eclib_queue_pop( eclib_queue_t * pQueue, void * pData )
 * \brief pop element from queue
 * \param pQueue pointer to eclib_queue_t structure
 * \param pData pointer to data to be stored in the queue
 * \return operation status
 */
eclib_status_t eclib_queue_pop( eclib_queue_t * pQueue, void * pData );


#endif /* ECLIB_QUEUE_H_ */
