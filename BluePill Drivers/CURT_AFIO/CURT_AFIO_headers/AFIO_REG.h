/*************************************************************************************************
 * [MODULE_NAME]:  AFIO_REG.h
 *
 * [DATE CREATED]: 
 *
 * [Author]:       
 *
 * [DESCRIPTION]:  All AFIO's Registers
 ************************************************************************************************/
#ifndef AFIO_REG_H_
#define AFIO_REG_H_

#include "../../LIB/STD_TYPES.h"
typedef struct {

	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICR[4];
	volatile u32 MAPR2;

}AFIO_R;

#define AFIO ((volatile AFIO_R*) 0x40010000) /*Base Address of AFIO */

#endif
