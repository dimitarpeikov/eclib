/*
 * eclib_types.h
 *
 *  Created on: 2008-7-24
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#ifndef ECLIB_TYPES_H_
#define ECLIB_TYPES_H_

typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;

typedef signed char		int8_t;
typedef signed short	int16_t;
typedef signed int		int32_t;

typedef uint8_t *       uint8_ptr_t;
typedef uint16_t *      uint16_ptr_t;
typedef uint32_t *      uint32_ptr_t;

typedef int8_t *        int8_ptr_t;
typedef int16_t *       int16_ptr_t;
typedef int32_t *       int32_ptr_t;

/*!
 * @enum eclib_signature_enum
 */
enum eclib_signature_enum
{
	ECLIB_SIGNATURE_EMPTY	= 0,		//!< no signature
	ECLIB_SIGNATURE_QUEUE	= 0x1234,	//!< QUEUE signature
	ECLIB_SIGNATURE_ARRAY	= 0x2345,	//!< ARRAY signature
	ECLIB_SIGNATURE_SET		= 0x3456,	//!< SET signature
	ECLIB_SIGNATURE_BUTTON	= 0x4567	//!< BUTTON signature
};
/*!
 * @typedef eclib_signature_t
 */
typedef enum eclib_signature_enum eclib_signature_t;

#define ECLIB_BUSY_CONST	0xFF
#define ECLIB_IDLE_CONST	0x00

/*!
 * @enum eclib_status_enum
 * @details status
 */
enum eclib_status_enum
{
	ECLIB_OK = 0,        //!< OK
	ECLIB_INITIALIZED,   //!< ECLIB INITIALIZED
	ECLIB_ERROR,         //!< ECLIB ERROR
	ECLIB_NULL_POINTER,  //!< ECLIB NULL POINTER
	ECLIB_NOT_FULL,      //!< ECLIB NOT FULL
	ECLIB_FULL,          //!< ECLIB FULL
	ECLIB_EMPTY,         //!< ECLIB EMPTY
	ECLIB_FOUND,		 //!< ECLIB ENTRY FOUND
	ECLIB_NOT_FOUND,	 //!< ECLIB ENTRY NOT FOUND
	ECLIB_OUT_OF_BOUNDS, //!< ECLIB OUT OF BOUNDS
	ECLIB_NOT_IMPLEMENTED//!< ECLIB NOT IMPLEMENTED
};

/*!
 * \typedef enum eclib_status_t
 */
typedef enum eclib_status_enum eclib_status_t;

#ifndef NULL
#define NULL ((void *)0L)
#endif

typedef struct eclib_threshold_t {
	uint16_t		a;
	uint16_t		b;
} eclib_uint16pair_t;
typedef eclib_uint16pair_t eclib_uint16pair_ptr_t_t;

// #include <memory.h>
#include <string.h>
/*
#define eclib_malloc	malloc
#define eclib_realloc	realloc
#define eclib_free		free
*/

#define eclib_memcpy	memcpy


#endif /* ECLIB_TYPES_H_ */
