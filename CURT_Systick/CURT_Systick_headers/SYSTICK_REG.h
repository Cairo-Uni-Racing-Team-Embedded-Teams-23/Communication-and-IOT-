/*************************************************************************************************
 * [MODULE_NAME]:  SYSTICK_REG.h
 *
 * [DATE CREATED]: 
 *
 * [Author]:        
 *
 * [DESCRIPTION]:  Registers of SYSTICK
 ************************************************************************************************/
#ifndef SYSTICK_REG_H_
#define SYSTICK_REG_H_

#include "STD_TYPES.h"

typedef struct {

	volatile u32 CTRL ;
	volatile u32 LOAD ;
	volatile u32 VAL  ;
	volatile u32 CALIB;

}SYSTICK_R;

#define SYSTICK ((volatile SYSTICK_R*) 0xE000E010)

#endif
