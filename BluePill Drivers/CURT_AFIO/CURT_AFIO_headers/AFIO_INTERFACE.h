/*************************************************************************************************
 * [MODULE_NAME]:  AFIO_INTERFACE.h
 *
 * [DATE CREATED]: 
 *
 * [Author]:      
 *
 * [DESCRIPTION]:  All # Defines to be used by User & Function's prototype
 ************************************************************************************************/
#ifndef AFIO_INTERFACE_H_
#define AFIO_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"


#define AFIO_FSMC_NADV              30
#define AFIO_TIM14_REMAP            29
#define AFIO_TIM13_REMAP            28
#define AFIO_TIM11_REMAP            27
#define AFIO_TIM10_REMAP            26
#define AFIO_TIM9_REMAP             25
#define AFIO_SWJ_CFG                24
#define AFIO_ADC2_ETRGREG_REMAP     20
#define ADC2_ETRGINJ_REMAP          19
#define ADC1_ETRGREG_REMAP          18
#define AFIO_ADC1_ETRGINJ_REMAP     17
#define AFIO_TIM5CH4_IREMAP         16
#define AFIO_PD01_REMAP             15
#define AFIO_CAN_REMAP              13
#define AFIO_TIM4_REMAP             12
#define AFIO_TIM3_REMAP             10
#define AFIO_TIM2_REMAP             8
#define AFIO_TIM1_REMAP             6
#define AFIO_USART3_REMAP           4
#define AFIO_USART2_REMAP           3
#define AFIO_USART1_REMAP           2
#define AFIO_I2C1_REMAP             1
#define AFIO_SPI1_REMAP             0

//---------------------------------------------- EXTERNAL Lines ------------------------------------------------//

#define AFIO_EXTI_LINE0             0
#define AFIO_EXTI_LINE1             1
#define AFIO_EXTI_LINE2             2
#define AFIO_EXTI_LINE3             3

#define AFIO_EXTI_LINE4             4
#define AFIO_EXTI_LINE5             5
#define AFIO_EXTI_LINE6             6
#define AFIO_EXTI_LINE7             7

#define AFIO_EXTI_LINE8             8
#define AFIO_EXTI_LINE9             9
#define AFIO_EXTI_LINE10            10
#define AFIO_EXTI_LINE11            11

#define AFIO_EXTI_LINE12            12
#define AFIO_EXTI_LINE13            13
#define AFIO_EXTI_LINE14            14
#define AFIO_EXTI_LINE15            15


#define AFIO_PORTA    0
#define AFIO_PORTB    1
#define AFIO_PORTC    2

void AFIO_setEXTIConfiguration( u8 EXTI_Line , u8 PortMap );

void AFIO_enableClock (void);



#endif
