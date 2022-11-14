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

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../CURT_CAN_headers/CAN_private.h"
#include "../CURT_CAN_headers/CAN_config.h"
#include "../CURT_CAN_headers/CAN_interface.h"
#include "../../CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "../../CURT_GPIO/CURT_GPIO_headers/GPIO_interface.h"

void CAN_init(CAN_TypeDef *CANx, CAN_TypeDef_Config Copy_enuCANConfig)
{

	/* Instance check */
	if (!IS_CAN_INSTANCE(CANx))
		return;

	/* Enable CAN clock */
	RCC_voidEnableClock(APB1, 25);

	/* Set up GPIO pins as Alternate function mode for CAN pins */
	GPIO_enablePortClock(GPIOA_ID);
	GPIO_setupPinMode(GPIOA_ID, PIN11, OUTPUT_SPEED_10MHZ_AFPP);
	GPIO_setupPinMode(GPIOA_ID, PIN12, OUTPUT_SPEED_10MHZ_AFPP);

	/* Configuration parameters in CAN_MCR register:
	 *
	 * CANx_RECEIVE_FIFO_LOCKED_MODE
	 * 	0: Receive FIFO is unlocked & incoming messages will overwrite previous ones.
	 * 	1: Receive FIFO is locked when it's full to prevent message overwriting if more
	 * 		messages are received. Additional messages are discarded.
	 *
	 * CANx_NO_AUTOMATIC_RETRANSMISSION
	 * 	0:	CAN will automatically re-transmit unacknowledged or error'd messages until success.
	 * 	1:	CAN will only send the message once whether or not it was transmitted successfully.
	 *
	 * CANx_AUTOMATIC_WAKE_UP_MODE
	 *	0:	Sleep mode stays in sleep as long as SLEEP bit is set
	 *	1:	Sleep mode exited once a message is received
	 *
	 * CANx_AUTOMATIC_BUS_OFF
	 * 	0:	CAN will leave BUS OFF mode if and only if software requests it AND CAN reads
	 * 		consecutive occurrences of 11 recessive bits on the bus.
	 * 	1:	CAN leaves BUS OFF once it reads 128 consecutive occurrences of 11 recessive bits
	 * 		on the bus.
	 *
	 * CANx_TIME_TRIGGERED_COMMUNICATION_MODE
	 * 	0:	Time Triggered Communication mode disabled
	 * 	1:	Time Triggered Communication mode enabled
	 *
	 *	---
	 *
	 *	Configuration parameters in CAN_BTR:
	 *	CAN1_RESYNC_JUMP_WIDTH
	 *		Maximum time quanta that CAN can lengthen/shorten a bitto resynchronize
	 *		with the bus
	 *		tRJW = tq x (SJW[1:0] + 1)
	 *
	 *	CAN1_TIME_SEGMENT_1
	 *		Time quanta in time segment 1
	 *		tBS1 = tq x (TS1[3:0] + 1)
	 *
	 *	CAN1_TIME_SEGMENT_2
	 *		Time quanta in time segment 2
	 *		tBS2 = tq x (TS2[2:0] + 1)
	 *
	 *	CAN1_BAUD_RATE_PRESCALER
	 *		CAN baud rate which defines the time quantum unit.
	 *		tq = (BRP[9:0]+1) x tPCLK
	 *
	 * */
	switch (Copy_enuCANConfig)
	{
	case CAN_CONFIG_1:

		/* Disable all CAN interrupts */
		CANx->IER = 0;
		/* Set the bits for settings we need in configuration 1 */
		CANx->MCR = ((CAN1_FIFO_PRIORITY << MCR_TXFP) | (CAN1_RECEIVE_FIFO_LOCKED_MODE << MCR_RFLM) | (CAN1_NO_AUTOMATIC_RETRANSMISSION << MCR_NART) | (CAN1_AUTOMATIC_WAKE_UP_MODE << MCR_AWUM) | (CAN1_AUTOMATIC_BUS_OFF << MCR_ABOT) | (CAN1_TIME_TRIGGERED_COMMUNICATION_MODE << MCR_TTCM));

		/* Exit sleep mode to init mode */
		SET_BIT(CANx->MCR, MCR_INRQ);
		/* Wait until HW is in initialization  mode, so we can setup timing parameters:
		 INAK = 1
		 SLAK = 0
		 */
		while (!GET_BIT(CANx->MSR, MSR_INAK) && GET_BIT(CANx->MSR, MSR_SLAK))
			;

		/* Set up timing parameters */
		CANx->BTR = ((CAN1_MODE << BTR_LBKM) | (CAN1_RESYNC_JUMP_WIDTH << BTR_SJW_2BITS) | (CAN1_TIME_SEGMENT_1 << BTR_TS1_4BITS) | (CAN1_TIME_SEGMENT_2 << BTR_TS2_3BITS) | (CAN1_BAUD_RATE_PRESCALER << BTR_BRP_10BITS));
		/* Go to normal mode */
		CLR_BIT(CANx->MCR, MCR_INRQ);
		break;
	case CAN_CONFIG_2:

		/* Disable all CAN interrupts */
		CANx->IER = 0;

		/* Set the bits for settings we need in configuration 1*/
		CANx->MCR = ((CAN2_FIFO_PRIORITY << MCR_TXFP) | (CAN2_RECEIVE_FIFO_LOCKED_MODE << MCR_RFLM) | (CAN2_NO_AUTOMATIC_RETRANSMISSION << MCR_NART) | (CAN2_AUTOMATIC_WAKE_UP_MODE << MCR_AWUM) | (CAN2_AUTOMATIC_BUS_OFF << MCR_ABOT) | (CAN2_TIME_TRIGGERED_COMMUNICATION_MODE << MCR_TTCM));

		/* Exit sleep mode to init mode */
		SET_BIT(CANx->MCR, MCR_INRQ);
		/* Wait until HW is in initialization  mode, so we can setup timing parameters:
		 INAK = 1
		 SLAK = 0
		 */
		while (!GET_BIT(CANx->MSR, MSR_INAK) && GET_BIT(CANx->MSR, MSR_SLAK))
			;

		/* Set up timing parameters */
		CANx->BTR = ((CAN2_MODE << BTR_LBKM) | (CAN2_RESYNC_JUMP_WIDTH << BTR_SJW_2BITS) | (CAN2_TIME_SEGMENT_1 << BTR_TS1_4BITS) | (CAN2_TIME_SEGMENT_2 << BTR_TS2_3BITS) | (CAN2_BAUD_RATE_PRESCALER << BTR_BRP_10BITS));
		/* Go to normal mode */
		CLR_BIT(CANx->MCR, MCR_INRQ);
		break;
	default:
		break;
	}
}

void CAN_initFilter(CAN_FilterInitTypeDef *PTR_sFilterInit)
{
	/* the initialization of the filter values  is independent from initialization Mode,
	 * but must be done when the filter is not active (corresponding FACTx bit in CAN_FAR cleared).
	 * the filter scale and mode of configuration must be done before entering the
	 * normal mode.
	 */

	/*  28 filter banks (0 --> 27),
	 * each filter bank x consists of two 32-bit registers, CAN_FxR0 , CAN_FxR1*/

	/*********SACLE*********/
	/* each filter bank can be scaled independently:
	 *   one 32-bit  filter, for STDID[10:0], EXTID[17:0], IDE and RTR bits
	 *   two  16-bit filter, for STDID[10:0], EXTID[17:15], IDE and RTR bits
	 *
	 *   scale is configured using FSCx bit in CAN_FSxR
	 */

	/**********MODE***********/
	/* MASK mode       --> specify which bit is "must match" or "don't care"
	 * mask mode can be used to specify a range of IDs
	 *
	 * IDENTIFIER mode --> all bits of the incoming identifier must match the bits specified in the filter registers
	 * identifier mode is used when we to receive a specific ID rather than the whole range
	 *
	 * Mask/identifier mode is configured in FBMxbits in CAN_FMxR
	 */

	/* set filter to initialize mode */
	SET_BIT(CAN1->FMR, FINIT);
	/* de-activate the filter before initialization */
	CLR_BIT(CAN1->FA1R, PTR_sFilterInit->FilterNumber);

	/* adjust CAN filter mode : */
	CAN1->FM1R = (CAN1->FM1R & ~(1 << PTR_sFilterInit->FilterNumber)) | (PTR_sFilterInit->FilterMode << PTR_sFilterInit->FilterNumber);
	/* adjust CAN scale mode : */
	CAN1->FS1R = (CAN1->FS1R & ~(1 << PTR_sFilterInit->FilterNumber)) | (PTR_sFilterInit->FilterScale << PTR_sFilterInit->FilterNumber);
	/* state if the message passed to the filterNumber will be stored in FIFO 0 or  FIFO 1 */
	CAN1->FFA1R = (CAN1->FFA1R & ~(1 << PTR_sFilterInit->FilterNumber)) | (PTR_sFilterInit->FilterFIFOAssignment
																		   << PTR_sFilterInit->FilterNumber);
	/* adjust filter activation mode */
	CAN1->FA1R = (PTR_sFilterInit->FilterActivation)
				 << (PTR_sFilterInit->FilterNumber);

	/* copy identifier into filter bank */
	switch (PTR_sFilterInit->FilterScale)
	{
	case SINGLE_32:
	{
		switch (PTR_sFilterInit->FilterMode)
		{

		case MASK:
		{
			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR2 = 0;
			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR1 = 0;

			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR2 =
				(PTR_sFilterInit->FilterMaskIdHigh) << 16 | (PTR_sFilterInit->FilterMaskIdLow);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR1 =
				(PTR_sFilterInit->FilterIdHighR1) << 16 | (PTR_sFilterInit->FilterIdLowR1);
		}
		break;

		case LIST:
		{
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 =
				(PTR_sFilterInit->FilterIdHighR1) << 16 | (PTR_sFilterInit->FilterIdLowR1);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 =
				(PTR_sFilterInit->FilterIdHighR2) << 16 | (PTR_sFilterInit->FilterIdLowR2);
		}
		break;
		}
	}
	break;

	case DOUBLE_16:
	{
		switch (PTR_sFilterInit->FilterMode)
		{
		case MASK:
		{
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 =
				(PTR_sFilterInit->FilterIdLowR1);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 =
				(PTR_sFilterInit->FilterIdLowR2);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 |=
				(PTR_sFilterInit->FilterMaskIdLow) << 16;
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 |=
				(PTR_sFilterInit->FilterMaskIdHigh) << 16;
		}
		break;

		case LIST:
		{
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 =
				(PTR_sFilterInit->FilterIdLowR1) | (PTR_sFilterInit->FilterIdHighR1) << 16;
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 =
				(PTR_sFilterInit->FilterIdLowR2) | (PTR_sFilterInit->FilterIdHighR2) << 16;
		}
		break;
		}
	}
	break;
	}

	/* disable filter initialize mode */
	CLR_BIT(CAN1->FMR, FINIT);
}

void CAN_setSlaveStartBank(u8 Copy_u8CANBankNumber)
{
	/* define the start bank for the CAN2 interface in range from ( 0 to 27 ) */
	/* assign 0 to CAN2SB[5:0] == no filters are assigned to CAN1
	 * assign 28 to CAN2SB[5:0] == all filters are assigned to CAN1
	 */

	CAN1->FMR = 0x2A1C0E01; /* register RESET value */

	CAN1->FMR |= (Copy_u8CANBankNumber & 0x3F) << CAN2SB;

	CLR_BIT(CAN1->FMR, FINIT); /* active filter mode enabled */
}

CAN_Tx_MailBox_TypeDef CAN_transmit(CAN_TypeDef *CANx, CanTxMsg *TxMessage)
{

	/* Transmisson Handling Function */

	/* First Step: Select an Empty Mailbox to Use for Transmission */

	CAN_Tx_MailBox_TypeDef Local_CAN_TxMailBox_TypeDef_CurrentMailBox; // variable to save the used MailBox in

	/* Check Which MailBox is Empty to use */
	if (GET_BIT(CANx->TSR, TSR_TME0))
	{
		Local_CAN_TxMailBox_TypeDef_CurrentMailBox = CAN_TX_MAILBOX_1;
	}
	else if (GET_BIT(CANx->TSR, TSR_TME1))
	{
		Local_CAN_TxMailBox_TypeDef_CurrentMailBox = CAN_TX_MAILBOX_2;
	}
	else if (GET_BIT(CANx->TSR, TSR_TME2))
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
	WRITE_BIT(CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR, TIR_IDE, TxMessage->IDE);

	/*Choose Whether Its Remote Frame or No */
	WRITE_BIT(CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR, TIR_RTR, TxMessage->RTR);

	/* Setup The Identifier */

	// Standard Identifier is 11 Bits
	if (TxMessage->IDE == CAN_STANDARD_IDENTIFIER)
	{
		CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR |= ((TxMessage->StdId & 0x7FF) << TIR_STID_11BITS);
	}
	// Extended Identifier is 29 Bits
	else if (TxMessage->IDE == CAN_EXTENDED_IDENTIFIER)
	{
		CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR |= ((TxMessage->ExtId & 0x1FFFFFFF) << TIR_EXID_17BITS);
	}

	/* Setting The DLC*/
	/* Choose Data length 8 Bytes */

	u8 Local_u8DLC = 0b1111;
	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDTR &= 0xFFFFFFF0;
	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDTR |= TxMessage->DLC;

	// Setting the Data in the Message

	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDHR = (((u32)TxMessage->Data[7] << 24) |
																		 ((u32)TxMessage->Data[6] << 16) |
																		 ((u32)TxMessage->Data[5] << 8) |
																		 ((u32)TxMessage->Data[4]));

	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDLR = (((u32)TxMessage->Data[3] << 24) |
																		 ((u32)TxMessage->Data[2] << 16) |
																		 ((u32)TxMessage->Data[1] << 8) |
																		 ((u32)TxMessage->Data[0]));

	/* Final Step: Request The Transmission*/
	SET_BIT(CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR, TIR_TXRQ);

	/* Return The used MailBox*/
	return Local_CAN_TxMailBox_TypeDef_CurrentMailBox;
}

void CAN_receive(CAN_TypeDef *CANx, u8 FIFONumber, CanRxMsg *RxMessage)
{

	/*Getting the identifier type either Standard or Extended from received message*/
	RxMessage->IDE = (u8)GET_BIT(CANx->sFIFOMailBox[FIFONumber].RIR, RIR_IDE);

	/*Operating depending on the received identifier type*/
	switch (RxMessage->IDE)
	{
	/*Standard Identifier*/
	case (CAN_STANDARD_IDENTIFIER):
	{
		/*Get the value of the Standard Identifier*/
		RxMessage->StdId = (u16)((CANx->sFIFOMailBox[FIFONumber].RIR
								  << RIR_STID_11BITS) &
								 0x000007FF);
		break;
	}
		/*Extended Identifier*/
	case (CAN_EXTENDED_IDENTIFIER):
	{
		/*Get the value of the Extended Identifier*/
		RxMessage->ExtId = (u32)((CANx->sFIFOMailBox[FIFONumber].RIR
								  << RIR_EXID_17BITS) &
								 0x1FFFFFFF);
		break;
	}
	}

	/*Get the value of the frame either it is data or remote*/
	RxMessage->RTR = GET_BIT(CANx->sFIFOMailBox[FIFONumber].RIR, RIR_RTR);

	/*Get the value of the data length code*/
	RxMessage->DLC = (u8)(0x0F & (CANx->sFIFOMailBox[FIFONumber].RDTR));

	/*Read the index of the filter message*/
	RxMessage->FMI = (u8)(0x0F & (CANx->sFIFOMailBox[FIFONumber].RDTR >> RDTR_FMI_8BITS));

	/*Read the data received*/
	/*Reading the data from the RDLR register*/
	RxMessage->Data[0] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR));
	RxMessage->Data[1] =
		(u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 8));
	RxMessage->Data[2] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 16));
	RxMessage->Data[3] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 24));
	/*Reading the data from the RDHR register*/
	RxMessage->Data[4] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR));
	RxMessage->Data[5] =
		(u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 8));
	RxMessage->Data[6] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 16));
	RxMessage->Data[7] = (u8)(0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 24));
	/*Checking on the entered FIFO number to know which mailbox to work with*/
	switch (FIFONumber)
	{
	/*If the first FIFO mailbox is selected*/
	case (CAN_RX_FIFO_1):
	{
		/*Setting the RFOM bit to release output from mailbox*/
		SET_BIT(CANx->RF0R, RFR_RFOM);
		break;
	}
		/*If the second FIFO mailbox is selected*/
	case (CAN_RX_FIFO_2):
	{
		/*Setting the RFOM bit to release output from mailbox*/
		SET_BIT(CANx->RF1R, RFR_RFOM);
		break;
	}
	}
}
