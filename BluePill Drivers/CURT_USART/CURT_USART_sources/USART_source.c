/*
 * USART_source.c
 *
 *  Created on: Nov 15, 2022
 *      Author: yasmine
 */

/* USART transmission procedures
 * 1)enable USART by writing UE bit in USART_CR1
 * 2)define word length (in M bit in USART_R1
 * 3)program number of stop bits (in USART_CR2)
 * 4)select the desired baud rate in USART_BRR
 * 5)set the TE bit in USART_CR1 to send an idle frame as first transmission
 * 7)write the data to send in USART_DR (this clears the TXE bit),
 *   wait until TC=1, indicating transmission completed, then it is cleared by:
 *   - a read from the USART_SR register
 *   - a write to the USART_DR register, or by writing 0 to it
 */

/* USART receiving procedures
 * 1)enable USART by writing UE bit in USART_CR1
 * 2)define word length (in M bit in USART_R1
 * 3)program number of stop bits (in USART_CR2)
 * 4)select the desired baud rate in USART_BRR
 * 5)set the RE bit in USART_CR1, this enables the receiver which begins searching for the start bit
 */

#include "USART_ptivate.h"
#include "USART_config.h"
#include "USART_interface.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"

#define F_CPU      36000000/***UNFINISHED, ASSUMED F_CPU = 36 MHz***/

void USART_enableClock(u8 USARTperipheralNumber){

	switch(USARTperipheralNumber)
	{
	case USART1_ID:
		RCC_voidEnableClock(USART1_BUS,USART1_ENABLE_PIN);
		break;

	case USART2_ID:
		RCC_voidEnableClock(USART2_BUS,USART2_ENABLE_PIN);
		break;

	case USART3_ID:
		RCC_voidEnableClock(USART3_BUS,USART3_ENABLE_PIN);
	}
}

void USART_init(USART_configType *configuration){
/* configurations available :
 * -peripheral ID--> (USART1,USART2,USART3)
 * -number of stop Bits
 * -baud rate
 */

	/* set the baud rate value */
	float baudValue = (F_CPU/(16*configuration->baudRate));
	u16 mantissa = (u16)baudValue;
	u8 fraction = 16*( (float)baudValue - (u32)baudValue );
	configuration->USARTx->USART_BRR = (mantissa<<4) | fraction;

	/* adjust number of stop bits */
	configuration->USARTx->USART_CR2 = configuration->stopBit<<12;

	/* enable USART, receiver, transmitter */
	configuration->USARTx->USART_CR1 = (1<<UE) | (1<<RE) | (1<<TE);

	/* reset status register */
	configuration->USARTx->USART_SR = 0;
}

void USART_transmitArray(u8 USARTperID,u8 arr[]){

	int i =0;

	while(arr[i] != '\0')
	{
		/* switch in which peripheral is being used to transmit the message */
		switch(USARTperID)
		{
		case USART1_ID:
			USART1->USART_DR = arr[i];
			while(GET_BIT(USART1->USART_SR,TC));
			break;

		case USART2_ID:
			USART2->USART_DR = arr[i];
			while(GET_BIT(USART2->USART_SR,TC));
			break;

		case USART3_ID:
			USART3->USART_DR = arr[i];
			while(GET_BIT(USART3->USART_SR,TC));
			break;
		}

		i++;
	}
}

u8   USART_receive(u8 USARTperID){

	switch(USARTperID)
	{/* switch in which peripheral is being used to receive the message */
	case USART1_ID:
		while(GET_BIT(USART1->USART_SR,RXNE));
		return (u8)USART1->USART_DR;
		break;

	case USART2_ID:
		while(GET_BIT(USART2->USART_SR,RXNE));
		return (u8)USART2->USART_DR;
		break;

	case USART3_ID:
		while(GET_BIT(USART3->USART_SR,RXNE));
		return (u8)USART3->USART_DR;
		break;
	}

}
