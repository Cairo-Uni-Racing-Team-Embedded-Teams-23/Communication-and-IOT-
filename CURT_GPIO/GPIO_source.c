/*
 * first,  know the bus related to this peripheral :
 * second, know the base address:
 * then define the driver functions
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"
#include "GPIO_REG.h"
#include "RCC_interface.h"

void GPIO_setupPinMode(u8 port_num, u8 pin_num,u8 mode){

	switch(port_num){

	case GPIOA_ID:
		if(pin_num <= 7) /* CONFIG IN GPIOA_CRL */
		{
			GPIOA->CRL = (GPIOA->CRL & ~(0b1111<<pin_num*4)) | (mode<<pin_num*4) ;
		}
		else if(pin_num > 7 && pin_num <= 15) /* CONFIG IN GPIOA_CRH */
		{
			GPIOA->CRH = (GPIOA->CRH & ~(0b1111<<(pin_num - 8)*4)) | (mode<<(pin_num - 8)*4) ;
		}
		break;

	case GPIOB_ID:
		if(pin_num <= 7) /* CONFIG IN GPIOB_CRL */
		{
			GPIOB->CRL = (GPIOB->CRL & ~(0b1111<<pin_num*4)) | (mode<<pin_num*4) ;
		}
		else if(pin_num > 7 && pin_num <= 15) /* CONFIG IN GPIOA_CRH */
		{
			GPIOB->CRH = (GPIOB->CRH & ~(0b1111<<(pin_num - 8)*4)) | (mode<<(pin_num - 8)*4) ;
		}
		break;

	case GPIOC_ID:
		if(pin_num <= 7) /* CONFIG IN GPIOC_CRL */
		{
			GPIOC->CRL = (GPIOC->CRL & ~(0b1111<<pin_num*4)) | (mode<<pin_num*4) ;
		}
		else if(pin_num > 7 && pin_num <= 15) /* CONFIG IN GPIOC_CRH */
		{
			GPIOC->CRH = (GPIOB->CRH & ~(0b1111<<(pin_num - 8)*4)) | (mode<<(pin_num - 8)*4) ;
		}
	}

}

void GPIO_setupPortMode(u8 port_num, u8 mode){

	switch(port_num){

	case GPIOA_ID:
		for(int counter=0; counter<= 15; counter++) /* loop over the port bits and configure all of them with the same mode */
		{
			if(counter <= 7)
			{
				GPIOA->CRL = (GPIOA->CRL & ~(0b1111<<counter*4)) | (mode<<counter*4) ;
			}
			else
			{
				GPIOA->CRH = (GPIOA->CRH & ~(0b1111<<counter*4)) | (mode<<counter*4) ;
			}
		}
		break;

	case GPIOB_ID:
		for(int counter=0; counter<= 15; counter++) /* loop over the port bits and configure all of them with the same mode */
		{
			if(counter <= 7)
			{
				GPIOB->CRL = (GPIOB->CRL & ~(0b1111<<counter*4)) | (mode<<counter*4) ;
			}
			else
			{
				GPIOB->CRH = (GPIOB->CRH & ~(0b1111<<counter*4)) | (mode<<counter*4) ;
			}
		}
		break;

	case GPIOC_ID:
		for(int counter=0; counter<= 15; counter++) /* loop over the port bits and configure all of them with the same mode */
		{
			if(counter <= 7)
			{
				GPIOC->CRL = (GPIOC->CRL & ~(0b1111<<counter*4)) | (mode<<counter*4) ;
			}
			else
			{
				GPIOC->CRH = (GPIOC->CRH & ~(0b1111<<counter*4)) | (mode<<counter*4) ;
			}
		}
	}

}


void GPIO_setPinValue(u8 port_num, u8 pin_num, u8 value){

	switch(port_num){

	case GPIOA_ID:
		if(pin_num <= NUM_OF_PINS_PER_PORT)
		{
			if(value == LOW)
				CLR_BIT(GPIOA->ODR, pin_num); /* write logic low '0' */
			else if(value == HIGH)
				SET_BIT(GPIOA->ODR, pin_num); /* write logic high '1' */
		}
		break;

	case GPIOB_ID:
		if(pin_num <= NUM_OF_PINS_PER_PORT)
		{
			if(value == LOW)
				CLR_BIT(GPIOB->ODR, pin_num); /* write logic low '0' */
			else if(value == HIGH)
				SET_BIT(GPIOB->ODR, pin_num); /* write logic high '1' */

		}
		break;

	case GPIOC_ID:
		if(pin_num <= NUM_OF_PINS_PER_PORT)
		{
			if(value == LOW)
				CLR_BIT(GPIOC->ODR, pin_num); /* write logic low '0' */
			else if(value == HIGH)
				SET_BIT(GPIOC->ODR, pin_num); /* write logic high '1' */

		}

	}
}

void GPIO_writePort(u8 port_num, u16 value){

	switch(port_num){

	case GPIOA_ID:
		GPIOA->ODR = (GPIOA->ODR & 0xFFFF0000) | value; /* write the value in 16 bits at one time */
		break;

	case GPIOB_ID:
		GPIOB->ODR = (GPIOB->ODR & 0xFFFF0000) | value;	/* write the value in 16 bits at one time */
		break;

	case GPIOC_ID:
		GPIOC->ODR = (GPIOC->ODR & 0xFFFF0000) | value; /* write the value in 16 bits at one time */
	}

}

u8 GPIO_getPinValue(u8 port_num, u8 pin_num){

	u8 LOCAL_u8Result; /* variable to save the pin value */

	switch(port_num){

	case GPIOA_ID:
		if(pin_num <= NUM_OF_PINS_PER_PORT)
		{
			LOCAL_u8Result = GET_BIT(GPIOA->IDR, pin_num);
		}
		break;

	case GPIOB_ID:
		if(pin_num <= NUM_OF_PINS_PER_PORT)
		{
			LOCAL_u8Result = GET_BIT(GPIOB->IDR, pin_num);
		}
		break;

	case GPIOC_ID:
		if(pin_num <= NUM_OF_PINS_PER_PORT)
		{
			LOCAL_u8Result = GET_BIT(GPIOC->IDR, pin_num);
		}

	}
	return LOCAL_u8Result;
}

u16 GPIO_getPort(u8 port_num){

	u16 Result; /* variable to save the pin value */

	switch(port_num){

	case GPIOA_ID:
		Result = (u16)GPIOA->IDR;
		break;

	case GPIOB_ID:
		Result = (u16)GPIOB->IDR;
		break;

	case GPIOC_ID:
		Result = (u16)GPIOC->IDR;
		break;

	default:
		Result = 0;

	}

	return Result;

}

u8   GPIO_togglePinValue (u8 port_num, u8 pin_num){

	u8 Result;
	switch(port_num){

	case GPIOA_ID:
		if(pin_num <= NUM_OF_PINS_PER_PORT)
		{
			TOG_BIT(GPIOA->ODR, pin_num);
			Result = GET_BIT(GPIOA->ODR, pin_num);
		}
		break;

	case GPIOB_ID:
		if(pin_num <= NUM_OF_PINS_PER_PORT)
		{
			TOG_BIT(GPIOB->ODR, pin_num);
			Result = GET_BIT(GPIOB->ODR, pin_num);
		}
		break;

	case GPIOC_ID:
		if(pin_num <= NUM_OF_PINS_PER_PORT)
		{
			TOG_BIT(GPIOC->ODR, pin_num);
			Result = GET_BIT(GPIOC->ODR, pin_num);
		}

	}

	return Result;

}

void GPIO_enablePortClock (u8 port_num){

	switch(port_num)
	{
	case GPIOA_ID:
		RCC_voidEnableClock(GPIOA_BUS, GPIOA_EN_BIT);
		break;

	case GPIOB_ID:
		RCC_voidEnableClock(GPIOB_BUS, GPIOB_EN_BIT);
		break;

	case GPIOC_ID:
		RCC_voidEnableClock(GPIOC_BUS, GPIOC_EN_BIT);
		break;

	}
}


