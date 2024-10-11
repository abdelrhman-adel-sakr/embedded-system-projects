/*
 * std_types.h
 *
 *  Created on: Sep 24, 2024
 *      Author: Abdelrhman Adel Sakr
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif
typedef unsigned char boolean;
#define LOGIC_HIGH  (1u)
#define LOGIC_LOW  (0u)
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned long uint32;
typedef signed long sint32;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned long long uint64;
typedef signed long long sint64;
typedef float                 float32;
typedef double                float64;

typedef volatile unsigned char vuint8;
typedef volatile signed char vsint8;
typedef volatile unsigned long vuint32;
typedef volatile signed long vsint32;
typedef volatile unsigned short vuint16;
typedef volatile signed short vsint16;
typedef volatile unsigned long long vuint64;
typedef volatile signed long long vsint64;
typedef volatile float         vfloat32;
typedef volatile double        vfloat64;
#endif /* STD_TYPES_H_ */
