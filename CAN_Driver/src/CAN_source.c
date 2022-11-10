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

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "CAN_private.h"
#include "CAN_config.h"
#include "CAN_interface.h"
#include "RCC_interface.h"
#include "GPIO_INTERFACE.h"
#include "GPIO_CONFIG.h"



/*******************************************************************************
 *                        Public functions definitions                         *
 *******************************************************************************/

void CAN_init(CAN_TypeDef *CANx, CAN_TypeDef_Config Copy_enuCANConfig)
{
}

void CAN_initFilter(CAN_FilterInitTypeDef *PTR_sFilterInit)
{
}

void CAN_setSlaveStartBank(u8 Copy_u8CANBankNumber)
{
}

CAN_Tx_MailBox_TypeDef CAN_transmit(CAN_TypeDef *CANx, CanTxMsg *TxMessage)
{
}

void CAN_receive(CAN_TypeDef *CANx, u8 FIFONumber, CanRxMsg *RxMessage)
{
	/*Checking on the entered FIFO number to know which mailbox to work with*/
	switch(FIFONumber)
	{
	/*If the first FIFO mailbox is selected*/
	case(CAN_RX_FIFO_1):
	{
		/*Setting the RFOM bit to release output from mailbox*/
		SET_BIT(CANx->RF0R,RFR_RFOM);
		break;
	}
	/*If the second FIFO mailbox is selected*/
	case(CAN_RX_FIFO_2):
    {
		/*Setting the RFOM bit to release output from mailbox*/
		SET_BIT(CANx->RF1R,RFR_RFOM);
		break;
	}
	}

	/*Getting the identifier type either Standard or Extended from received message*/
	RxMessage->IDE = (u8)GET_BIT(CANx->sFIFOMailBox[FIFONumber].RIR,RIR_IDE);

	/*Operating depending on the received identifier type*/
	switch(RxMessage->IDE)
	{
	/*Standard Identifier*/
	case(CAN_STANDARD_IDENTIFIER):
	{
		/*Get the value of the Standard Identifier*/
		RxMessage->StdId = (u16)((CANx->sFIFOMailBox[FIFONumber].RIR << RIR_STID_11BITS) & 0x000007FF);
		break;
	}
	/*Extended Identifier*/
	case(CAN_EXTENDED_IDENTIFIER):
	{
		/*Get the value of the Extended Identifier*/
		RxMessage->ExtId = (u32)((CANx->sFIFOMailBox[FIFONumber].RIR << RIR_EXID_17BITS) & 0x1FFFFFFF);
	    break;
	}
	}

	/*Get the value of the frame either it is data or remote*/
	RxMessage->RTR = GET_BIT(CANx->sFIFOMailBox[FIFONumber].RIR,RIR_RTR);

	/*Get the value of the data length code*/
	RxMessage->DLC = (u8)(0x0F & (CANx->sFIFOMailBox[FIFONumber].RDTR));

	/*Read the index of the filter message*/
	RxMessage->FMI = (u8)(0x0F & (CANx->sFIFOMailBox[FIFONumber].RDTR >> RDTR_FMI_8BITS));

	/*Read the data received*/
	/*Reading the data from the RDLR register*/
	RxMessage->Data[0] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR));
	RxMessage->Data[1] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 8));
	RxMessage->Data[2] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 16));
	RxMessage->Data[3] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 24));
	/*Reading the data from the RDHR register*/
	RxMessage->Data[4] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR));
	RxMessage->Data[5] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 8));
	RxMessage->Data[6] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 16));
	RxMessage->Data[7] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 24));
}
