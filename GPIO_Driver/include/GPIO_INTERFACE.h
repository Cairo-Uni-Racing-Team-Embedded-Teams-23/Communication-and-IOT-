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

#include "STD_TYPES.h"


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

void GPIO_setPortDirection_H_L( uint8 Port , uint8 Position , uint8 Mode );

void GPIO_setPortValue_H_L( uint8 Port , uint8 Position , uint16 Value );
****************************************************************************************************************************************************/

#endif
