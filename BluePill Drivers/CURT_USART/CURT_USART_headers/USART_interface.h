/*
 * USART_interface.h
 *
 *  Created on: Nov 15, 2022
 *      Author: yasmi
 */
#include "USART_ptivate.h"

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

/* number of USART peripherals in STM */
#define USART1_ID		1
#define USART2_ID		2
#define USART3_ID		3


typedef enum{
	STOP_1,STOP_HALF,STOP_2,STOP_1_HALF
}USART_stopBits;

typedef enum{
	NONE,PARITY
}USART_parityBits;

typedef struct{

	USART_typedef* USARTx;  //USART1,USART2,USART3
	USART_stopBits stopBit;
	u32 baudRate;




}USART_configType;

/****************function prototypes********************/
void USART_enableClock(u8 USARTperipheralNumber);

void USART_init(USART_configType *configuration); //initialize USART with required configurations
void USART_transmitArray(u8 USARTperID,u8 arr[]); //send array using USART of given peripheral ID
u8   USART_receive(u8 USARTperID);                //receive message from USART of given peripheral ID

#endif /* USART_INTERFACE_H_ */
