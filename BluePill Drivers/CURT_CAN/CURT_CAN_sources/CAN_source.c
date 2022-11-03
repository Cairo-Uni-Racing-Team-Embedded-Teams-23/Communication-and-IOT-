 /*******************************************************************************
 *																
 * 	Module			: CAN BUS									
 *																
 * 	File Name		: CAN_source.c										
 *																	
 * 	Author			: 						
 *																
 *	Date 			: 									
 *																
 *	Version			: v1.0										
 * 																
 *******************************************************************************/


#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "CAN_private.h"
#include "CAN_config.h"
#include "CAN_interface.h"
#include "RCC_interface.h"


void CAN_init(CAN_TypeDef* CANx , CAN_TypeDef_Config Copy_enuCANConfig)
{
	
}

void CAN_initFilter(CAN_FilterInitTypeDef *PTR_sFilterInit)
{
		
}

void CAN_setSlaveStartBank(u8 Copy_u8CANBankNumber) 
{
 
}


CAN_Tx_MailBox_TypeDef CAN_transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage)
{
	
}

void CAN_receive(CAN_TypeDef* CANx, u8 FIFONumber, CanRxMsg* RxMessage)
{
	
}
