/*************************************************************************************************
 * [MODULE_NAME]:  GPIO_INTERFACE.h
 *
 * [DATE CREATED]:  
 *
 * [Author]:        
 *
 * [DESCRIPTION]:  All # Defines to be used by User & Function's prototype
 ************************************************************************************************/
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

#define NUM_OF_PINS_PER_PORT 15
#define NUM_OF_PORTS 3

#define GPIOA_ID   0
#define GPIOB_ID   1
#define GPIOC_ID   2

#define PIN0    0
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7
#define PIN8    8
#define PIN9    9
#define PIN10    10
#define PIN11    11
#define PIN12    12
#define PIN13    13
#define PIN14    14
#define PIN15    15

#define HIGH    1
#define LOW     0

#define HIGH_PORT 0XFFFF
#define LOW_PORT   0

#define LOW_PINS   0
#define HIGH_PINS  1


/**********************************************************************/
/*                                                                    */
/*                        GPIO Peripheral Modes                       */
/*                              0-INPUT_ANLOG                         */
/*                              1-INPUT_FLOATING                      */
/*                              2-INPUT_PULLUP_PULLDOWN               */
/*                              3-OUTPUT_SPEED_10MHZ_PP               */
/*                              4-OUTPUT_SPEED_10MHZ_OD               */
/*                              5-OUTPUT_SPEED_10MHZ_AFPP             */
/*                              6-OUTPUT_SPEED_10MHZ_AFOD             */
/*                              7-OUTPUT_SPEED_2MHZ_PP                */
/*                              8-OUTPUT_SPEED_2MHZ_OD                */
/*                              9-OUTPUT_SPEED_2MHZ_AFPP              */
/*                              10-OUTPUT_SPEED_2MHZ_AFOD             */
/*                              11-OUTPUT_SPEED_50MHZ_PP              */
/*                              12-OUTPUT_SPEED_50MHZ_OD              */
/*                              13-OUTPUT_SPEED_50MHZ_AFPP            */
/*                              14-OUTPUT_SPEED_50MHZ_AFOD            */
/*                                                                    */
/**********************************************************************/

#define INPUT_ANLOG               0b0000
#define INPUT_FLOATING            0b0100
#define INPUT_PULLUP_PULLDOWN     0b1000

//For Speed 10
#define OUTPUT_SPEED_10MHZ_PP     0b0001
#define OUTPUT_SPEED_10MHZ_OD     0b0101
#define OUTPUT_SPEED_10MHZ_AFPP   0b1001
#define OUTPUT_SPEED_10MHZ_AFOD   0b1101

//For Speed 2
#define OUTPUT_SPEED_2MHZ_PP      0b0010
#define OUTPUT_SPEED_2MHZ_OD      0b0110
#define OUTPUT_SPEED_2MHZ_AFPP    0b1010
#define OUTPUT_SPEED_2MHZ_AFOD    0b1110

//For Speed 2
#define OUTPUT_SPEED_50MHZ_PP     0b0011
#define OUTPUT_SPEED_50MHZ_OD     0b0111
#define OUTPUT_SPEED_50MHZ_AFPP   0b1011
#define OUTPUT_SPEED_50MHZ_AFOD   0b1111


/*
 * Description :
 * Setup the Mode & Direction of the required pin from 16 Modes.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinMode(u8 port_num, u8 pin_num,u8 mode);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up/pull-down resistor.
 */
void GPIO_setPinValue(u8 port_num, u8 pin_num, u8 value);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
u8 GPIO_getPinValue(u8 port_num, u8 pin_num);

/*
 * Description :
 * Setup the direction of the required port all pins from 16 modes.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortMode(u8 port_num, u8 mode);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(u8 port_num, u16 value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
u16 GPIO_getPort(u8 port_num);

u8   GPIO_togglePinValue (u8 port_num, u8 pin_num);

void GPIO_enablePortClock (u8 port_num);

/****************************************************************************************************************************************************
*Functions will be added to be used in another drivers

void GPIO_setPortDirection_H_L( u8 Port , u8 Position , u8 Mode );

void GPIO_setPortValue_H_L( u8 Port , u8 Position , u16 Value );
****************************************************************************************************************************************************/

#endif
