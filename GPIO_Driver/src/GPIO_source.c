/*************************************************************************************************
 * [MODULE_NAME]:  GPIO_source.c
 *
 * [DATE CREATED]:
 *
 * [Author]:
 *
 * [DESCRIPTION]:  Source Code for GPIO Driver
 ************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_INTERFACE.h"
#include "GPIO_REG.h"
#include "GPIO_PRIVATE.h"
#include "GPIO_CONFIG.h"


/*
 * Description :
 * Setup the Mode & Direction of the required pin from 16 Modes.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinMode(u8 port_num, u8 pin_num,u8 mode)
{

/*Check if the input ports and pin numbers are within range and display a error message if otherwise*/
#if (port_num > NUM_OF_PORTS || pin_num > NUM_OF_PINS_PER_PORT)
#error "INVALID PORT,PIN REGISTIRATION"
#else
	/*Check which port that will be operated on*/
	switch(port_num)
	{
	/*Case of accessing port A*/
	case GPIOA_ID:
		if(pin_num <= 7)
		{
			/*If the entered pin is from 0 to 7 the CRL register will be accessed*/
			GPIOA->CRL =(GPIOA->CRL & ~(0b1111<<pin_num*4)) | (mode<<pin_num*4);
		}
		else
		{
			/*If the entered pin is from 8 to 15 the CRH register will be accessed*/
			GPIOA->CRH =(GPIOA->CRH & ~(0b1111<<(pin_num-8)*4)) | (mode<<(pin_num-8)*4);
		}
		break;
	/*Case of accessing port B*/
	case GPIOB_ID:
		if(pin_num <= 7)
		{
			/*If the entered pin is from 0 to 7 the CRL register will be accessed*/
			GPIOB->CRL =(GPIOB->CRL & ~(0b1111<<pin_num*4)) | (mode<<pin_num*4);
		}
		else
		{
			/*If the entered pin is from 8 to 15 the CRH register will be accessed*/
			GPIOB->CRH =(GPIOB->CRH & ~(0b1111<<(pin_num-8)*4)) | (mode<<(pin_num-8)*4);
		}
		break;
	/*Case of accessing port C*/
	case GPIOC_ID:
		if(pin_num <= 7)
		{
			/*If the entered pin is from 0 to 7 the CRL register will be accessed*/
			GPIOC->CRL =(GPIOC->CRL & ~(0b1111<<pin_num*4)) | (mode<<pin_num*4);
		}
		else
		{
			/*If the entered pin is from 8 to 15 the CRH register will be accessed*/
			GPIOC->CRH =(GPIOC->CRH & ~(0b1111<<(pin_num-8)*4)) | (mode<<(pin_num-8)*4);
		}
		break;
	}
#endif
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up/pull-down resistor.
 */
void GPIO_setPinValue(u8 port_num, u8 pin_num, u8 value)
{

/*Check if the input ports and pin numbers are within range and display a error message if otherwise*/
#if (port_num > NUM_OF_PORTS || pin_num > NUM_OF_PINS_PER_PORT)
#error "INVALID PORT,PIN REGISTIRATION"
#else
	/*Check which port that will be operated on*/
	switch(port_num)
	{
	/*Case of accessing port A*/
	case GPIOA_ID:
		/*Check the entered value if it is high or not*/
		if(value == HIGH)
		{
			/*If the value is high then set bit*/
			SET_BIT(GPIOA->ODR,pin_num);
		}
		else
		{
			/*If the value is low then clear bit*/
			CLR_BIT(GPIOA->ODR,pin_num);
		}
		break;
	/*Case of accessing port B*/
	case GPIOB_ID:
		/*Check the entered value if it is high or not*/
		if(value == HIGH)
		{
			/*If the value is high then set bit*/
			SET_BIT(GPIOB->ODR,pin_num);
		}
		else
		{
			/*If the value is low then clear bit*/
			CLR_BIT(GPIOB->ODR,pin_num);
		}
		break;
	/*Case of accessing port C*/
	case GPIOC_ID:
		/*Check the entered value if it is high or not*/
		if(value == HIGH)
		{
			/*If the value is high then set bit*/
			SET_BIT(GPIOC->ODR,pin_num);
		}
		else
		{
			/*If the value is low then clear bit*/
			CLR_BIT(GPIOC->ODR,pin_num);
		}
		break;
	}
#endif
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
u8 GPIO_getPinValue(u8 port_num, u8 pin_num)
{

/*Check if the input ports and pin numbers are within range and display a error message if otherwise*/
#if (port_num > NUM_OF_PORTS || pin_num > NUM_OF_PINS_PER_PORT)
#error "INVALID PORT,PIN REGISTIRATION"
#else
	/*Local variable to store the pin value*/
	u8 pin_value = LOW;

	/*Check which port that will be operated on*/
	switch(port_num)
	{
	/*Case of accessing port A*/
	case GPIOA_ID:
		/*Read the pin value and store it in the variable*/
		pin_value = GET_BIT(GPIOA->IDR,pin_num);
		break;
	/*Case of accessing port B*/
	case GPIOB_ID:
		/*Read the pin value and store it in the variable*/
		pin_value = GET_BIT(GPIOB->IDR,pin_num);
		break;
	/*Case of accessing port C*/
	case GPIOC_ID:
		/*Read the pin value and store it in the variable*/
		pin_value = GET_BIT(GPIOC->IDR,pin_num);
		break;
	}
	/*Return the pin value*/
	return pin_value;
#endif
}

/*
 * Description :
 * Setup the direction of the required port all pins from 16 modes.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortMode(u8 port_num, u8 mode)
{

/*Check if the input ports and pin numbers are within range and display a error message if otherwise*/
#if (port_num > NUM_OF_PORTS)
#error "INVALID PORT REGISTIRATION"
#else
	/*Check which port that will be operated on*/
	switch(port_num)
	{
	/*Case of accessing port A*/
	case GPIOA_ID:
		/*Clear the CRL and CRH registers then set the whole port with the desired mode*/
		GPIOA->CRL =(GPIOA->CRL & ~(0xFFFFFFF)) | mode;

		GPIOA->CRH =(GPIOA->CRH & ~(0xFFFFFFF)) | mode;
		break;
	/*Case of accessing port B*/
	case GPIOB_ID:
		/*Clear the CRL and CRH registers then set the whole port with the desired mode*/
		GPIOB->CRL =(GPIOB->CRL & ~(0xFFFFFFF)) | mode;

		GPIOB->CRH =(GPIOB->CRH & ~(0xFFFFFFF)) | mode;
		break;
	/*Case of accessing port C*/
	case GPIOC_ID:
		/*Clear the CRL and CRH registers then set the whole port with the desired mode*/
		GPIOC->CRL =(GPIOC->CRL & ~(0xFFFFFFF)) | mode;

		GPIOC->CRH =(GPIOC->CRH & ~(0xFFFFFFF)) | mode;
		break;
	}
#endif
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(u8 port_num, u16 value)
{

/*Check if the input ports numbers are within range and display a error message if otherwise*/
#if (port_num > NUM_OF_PORTS)
#error "INVALID PORT REGISTIRATION"
#else
	/*Check which port that will be operated on*/
	switch(port_num)
	{
	/*Case of accessing port A*/
	case GPIOA_ID:
		/*Write the value entered on the whole port*/
		(u16)GPIOA->ODR = value;
		break;
	/*Case of accessing port B*/
	case GPIOB_ID:
		/*Write the value entered on the whole port*/
		(u16)GPIOA->ODR = value;
		break;
	/*Case of accessing port C*/
	case GPIOC_ID:
		/*Write the value entered on the whole port*/
		(u16)GPIOA->ODR = value;
		break;
	}
#endif
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
u16 GPIO_getPort(u8 port_num)
{

/*Check if the input ports numbers are within range and display a error message if otherwise*/
#if (port_num > NUM_OF_PORTS)
#error "INVALID PORT REGISTIRATION"
#else
	/*Local variable to store the pin value*/
	u16 port_value = LOW;

	/*Check which port that will be operated on*/
	switch(port_num)
	{
	/*Case of accessing port A*/
	case GPIOA_ID:
		/*Read and store the port value in the variable*/
		port_value = (u16)GPIOA->IDR;
		break;
	/*Case of accessing port B*/
	case GPIOB_ID:
		/*Read and store the port value in the variable*/
		port_value = (u16)GPIOB->IDR;
		break;
	/*Case of accessing port C*/
	case GPIOC_ID:
		/*Read and store the port value in the variable*/
		port_value = (u16)GPIOC->IDR;
		break;
	}
	/*Return the port value*/
	return port_value;
#endif
}

u8 GPIO_togglePinValue (u8 port_num, u8 pin_num)
{

/*Check if the input ports and pin numbers are within range and display a error message if otherwise*/
#if (port_num > NUM_OF_PORTS || pin_num > NUM_OF_PINS_PER_PORT)
#error "INVALID PORT,PIN REGISTIRATION"
#else
	/*Local variable to store the pin value*/
	u8 pin_value = LOW;

	/*Check which port that will be operated on*/
	switch(port_num)
	{
	/*Case of accessing port A*/
	case GPIOA_ID:
		/*Toggle the pin value*/
		TOG_BIT(GPIOA->ODR,pin_num);
		/*Read and store the new value in the variable*/
		pin_value = GET_BIT(GPIOA->IDR,pin_num);
		break;
	/*Case of accessing port B*/
	case GPIOB_ID:
		/*Toggle the pin value*/
		TOG_BIT(GPIOB->ODR,pin_num);
		/*Read and store the new value in the variable*/
		pin_value = GET_BIT(GPIOB->IDR,pin_num);
		break;
	/*Case of accessing port C*/
	case GPIOC_ID:
		/*Toggle the pin value*/
		TOG_BIT(GPIOC->ODR,pin_num);
		/*Read and store the new value in the variable*/
		pin_value = GET_BIT(GPIOC->IDR,pin_num);
		break;
	}
	/*Return the new pin value*/
	return pin_value;
#endif
}

void GPIO_enablePortClock (u8 port_num)
{

/*Check if the input ports numbers are within range and display a error message if otherwise*/
#if (port_num > NUM_OF_PORTS)
#error "INVALID PORT REGISTIRATION"
#else
	/*Check which port that will be operated on*/
	switch(port_num)
	{
	/*Case of accessing port A*/
	case GPIOA_ID:
		/*Enable clock on port A*/
		RCC_voidEnableClock(APB2,IOPAEN);
		break;
	/*Case of accessing port B*/
	case GPIOB_ID:
		/*Enable clock on port B*/
		RCC_voidEnableClock(APB2,IOPBEN);
		break;
	/*Case of accessing port C*/
	case GPIOC_ID:
		/*Enable clock on port C*/
		RCC_voidEnableClock(APB2,IOPCEN);
		break;
	}
#endif
}

/****************************************************************************************************************************************************
*Functions will be added to be used in another drivers

void GPIO_setPortDirection_H_L( uint8 Port , uint8 Position , uint8 Mode );

void GPIO_setPortValue_H_L( uint8 Port , uint8 Position , uint16 Value );
****************************************************************************************************************************************************/
