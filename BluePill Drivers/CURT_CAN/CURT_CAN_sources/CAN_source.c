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
	
	/* Transmisson Handling Function */

	/* First Step: Select an Empty Mailbox to Use for Transmission */

	CAN_TxMailBox_TypeDef Local_CAN_TxMailBox_TypeDef_CurrentMailBox;  // variable to save the used MailBox in

	/* Check Which MailBox is Empty to use */
	if (GET_BIT(CANx->TSR , TSR_TME0))
	{
		Local_CAN_TxMailBox_TypeDef_CurrentMailBox = CAN_TX_MAILBOX_1;
	}
	else if (GET_BIT(CANx->TSR , TSR_TME1))
	{
		Local_CAN_TxMailBox_TypeDef_CurrentMailBox = CAN_TX_MAILBOX_2;
	}
	else if (GET_BIT(CANx->TSR , TSR_TME2))
	{
		Local_CAN_TxMailBox_TypeDef_CurrentMailBox = CAN_TX_MAILBOX_3;
	}
	else
	{
		/* All MAILBOXES Are Currently In Use */
		Local_CAN_TxMailBox_TypeDef_CurrentMailBox = CAN_TX_NO_EMPTY_MAILBOX;
		return Local_CAN_TxMailBox_TypeDef_CurrentMailBox;
	}

	/* Second Step: Setup the Identifier
	 * 				Setup The RTR
	 * 				Setup the DLC
	 * 				Put the Data
	 */

	/* Choose Whether Its Standard or Extended Frame */
	WRITE_BIT(CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR , TIR_IDE , TxMessage->IDE);

	/*Choose Whether Its Remote Frame or No */
	WRITE_BIT(CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR , TIR_RTR , TxMessage->RTR);

	/* Setup The Identifier */

	//Standard Identifier is 11 Bits
	if(TxMessage->IDE  == CAN_STANDARD_IDENTIFIER)
	{
		CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR |= ((TxMessage->StdId&0x7FF)<< TIR_STID_11BITS);
	}
	//Extended Identifier is 29 Bits
	else if(TxMessage->IDE  == CAN_EXTENDED_IDENTIFIER)
	{
		CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR |= ((TxMessage->ExtId&0x1FFFFFFF)<< TIR_EXID_17BITS);
	}

	/* Setting The DLC*/
	/* Choose Data length 8 Bytes */

	u8 Local_u8DLC = 0b1111;
	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDTR &= 0xFFFFFFF0;
	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDTR |= TxMessage->DLC;


	//Setting the Data in the Message


	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDHR = (	((u32)TxMessage->Data[7] << 24) |
																			((u32)TxMessage->Data[6] << 16) |
																			((u32)TxMessage->Data[5] << 8)  |
																			((u32)TxMessage->Data[4]));

	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDLR = (	((u32)TxMessage->Data[3] << 24) |
																		((u32)TxMessage->Data[2] << 16) |
																		((u32)TxMessage->Data[1] << 8)  |
																		((u32)TxMessage->Data[0]));





	/* Final Step: Request The Transmission*/
	SET_BIT(CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR , TIR_TXRQ);


	/* Return The used MailBox*/
	return Local_CAN_TxMailBox_TypeDef_CurrentMailBox;





}

void CAN_receive(CAN_TypeDef* CANx, u8 FIFONumber, CanRxMsg* RxMessage)
{
	
}
