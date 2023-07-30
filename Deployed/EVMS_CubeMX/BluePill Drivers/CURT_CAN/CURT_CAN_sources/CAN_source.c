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
#include "../CURT_CAN_headers/CAN_config.h"
#include "../CURT_CAN_headers/CAN_interface.h"
#include "../CURT_CAN_headers/CAN_private.h"
#include "../../CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "../../CURT_GPIO/CURT_GPIO_headers/GPIO_interface.h"
#include "../../CURT_NVIC/CURT_NVIC_headers/NVIC_interface.h"

/*******************************************************************************
 *                           Private global variables                          *
 *******************************************************************************/

/* Number of devices whose ID is currently allowed to be received*/
static volatile u8 CAN_devicesCount = 0;
static volatile CAN_TypeDef *CAN_in_use = CAN1;
static volatile CanTxMsg p_CANTxMsg = { 0 };
static volatile u8 *CAN_RxBuffer = NULLPTR;
static volatile u8 *CAN_RxSize = NULLPTR;
static volatile u32 *CAN_RxID = NULLPTR;

/* Callback functions pointers*/
static void (*CAN_transmit_CallbackPtr)(void) = NULLPTR;
static void (*CAN_FIFO0_CallbackPtr)(void) = NULLPTR;
static void (*CAN_FIFO1_CallbackPtr)(void) = NULLPTR;
static void (*CAN_Status_CallbackPtr)(void) = NULLPTR;

/*******************************************************************************
 *                       Public functions definitions                          *
 *******************************************************************************/

void CAN_init(CAN_TypeDef *CANx, CAN_TypeDef_Config Copy_enuCANConfig) {

	/* Instance check */
	if (!IS_CAN_INSTANCE(CANx))
		return;

	/* Enable CAN clock */
	RCC_voidEnableClock(APB1, RCC_APB1_CANEN);

	/* Set up GPIO pins as Alternate function mode for CAN pins */
	GPIO_enablePortClock(GPIOA_ID);
	/* Setup CAN Rx (PIN11) as input */
	GPIO_setupPinMode(GPIOA_ID, PIN11, INPUT_PULLUP_PULLDOWN);
	/* Setup CAN Tx (PIN12) as output alternate function*/
	GPIO_setupPinMode(GPIOA_ID, PIN12, OUTPUT_SPEED_50MHZ_AFPP);

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
	 *		Maximum time quanta that CAN can lengthen/shorten a bit to resynchronize
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
	switch (Copy_enuCANConfig) {
	case CAN_CONFIG_1:
		/* Exit sleep mode to init mode */
		SET_BIT(CANx->MCR, MCR_INRQ);

		/* Wait until HW is in initialization  mode, so we can setup timing parameters:
		 INAK = 1
		 SLAK = 0
		 */
		while (GET_BIT(CANx->MSR, MSR_INAK) == 0U)
			;

		CLR_BIT(CANx->MCR, MCR_SLEEP);
		while (GET_BIT(CANx->MSR, MSR_SLAK) != 0U)
			;
		/* Disable all CAN interrupts */
		CANx->IER = 0;

		/* Set the bits for settings we need in configuration 1 */
		WRITE_BIT(CANx->MCR, MCR_TXFP, CAN1_FIFO_PRIORITY);
		WRITE_BIT(CANx->MCR, MCR_RFLM, CAN1_RECEIVE_FIFO_LOCKED_MODE);
		WRITE_BIT(CANx->MCR, MCR_NART, CAN1_NO_AUTOMATIC_RETRANSMISSION);
		WRITE_BIT(CANx->MCR, MCR_AWUM, CAN1_AUTOMATIC_WAKE_UP_MODE);
		WRITE_BIT(CANx->MCR, MCR_ABOT, CAN1_AUTOMATIC_BUS_OFF);
		WRITE_BIT(CANx->MCR, MCR_TTCM, CAN1_TIME_TRIGGERED_COMMUNICATION_MODE);

		/* Set up timing parameters */
		CANx->BTR = (u32) ((CAN1_MODE << BTR_LBKM)
				| (CAN1_RESYNC_JUMP_WIDTH << BTR_SJW_2BITS)
				| (CAN1_TIME_SEGMENT_1 << BTR_TS1_4BITS)
				| (CAN1_TIME_SEGMENT_2 << BTR_TS2_3BITS)
				| ((CAN1_BAUD_RATE_PRESCALER - 1) << BTR_BRP_10BITS));
		break;
	case CAN_CONFIG_2:

		/* Exit sleep mode to init mode */
		SET_BIT(CANx->MCR, MCR_INRQ);

		/* Wait until HW is in initialization  mode, so we can setup timing parameters:
		 INAK = 1
		 SLAK = 0
		 */
		while (GET_BIT(CANx->MSR, MSR_INAK) == 0U)
			;

		CLR_BIT(CANx->MCR, MCR_SLEEP);
		while (GET_BIT(CANx->MSR, MSR_SLAK) != 0U)
			;

		/* Disable all CAN interrupts */
		CANx->IER = 0;

		/* Set the bits for settings we need in configuration 2*/
		WRITE_BIT(CANx->MCR, MCR_TXFP, CAN2_FIFO_PRIORITY);
		WRITE_BIT(CANx->MCR, MCR_RFLM, CAN2_RECEIVE_FIFO_LOCKED_MODE);
		WRITE_BIT(CANx->MCR, MCR_NART, CAN2_NO_AUTOMATIC_RETRANSMISSION);
		WRITE_BIT(CANx->MCR, MCR_AWUM, CAN2_AUTOMATIC_WAKE_UP_MODE);
		WRITE_BIT(CANx->MCR, MCR_ABOT, CAN2_AUTOMATIC_BUS_OFF);
		WRITE_BIT(CANx->MCR, MCR_TTCM, CAN2_TIME_TRIGGERED_COMMUNICATION_MODE);

		/* Set up timing parameters */
		CANx->BTR = ((CAN2_MODE << BTR_LBKM)
				| (CAN2_RESYNC_JUMP_WIDTH << BTR_SJW_2BITS)
				| (CAN2_TIME_SEGMENT_1 << BTR_TS1_4BITS)
				| (CAN2_TIME_SEGMENT_2 << BTR_TS2_3BITS)
				| ((CAN2_BAUD_RATE_PRESCALER - 1) << BTR_BRP_10BITS));
		break;
	default:
		break;
	}
}

void CAN_setMode(CAN_TypeDef *CANx, CAN_Mode a_mode) {
	/* Instance check */
	if (!IS_CAN_INSTANCE(CANx))
		return;

	switch (a_mode) {
	case CAN_Mode_Sleep:
		SET_BIT(CANx->MCR, SLEEP);
		CLR_BIT(CANx->MCR, INRQ);
		/* Wait until HW is in sleep  mode
		 INAK = 0
		 SLAK = 1
		 */
		while (GET_BIT(CANx->MSR, MSR_SLAK) == 0U)
			;

		break;
	case CAN_Mode_Init:
		SET_BIT(CANx->MCR, INRQ);
		CLR_BIT(CANx->MCR, SLEEP);
		/* Wait until HW is in sleep  mode
		 INAK = 0
		 SLAK = 1
		 */
		while (GET_BIT(CANx->MSR, MSR_INAK) == 0U)
			;
		break;
	case CAN_Mode_Normal:
//		CLR_BIT(CANx->MCR, 3);
//		CLR_BIT(CANx->MCR, SLEEP);
//		CLR_BIT(CANx->MCR, INRQ);
		CANx->MCR &= ~(1 << 0);
		/* Wait until HW is in sleep  mode
		 INAK = 0
		 SLAK = 1
		 */
		while (GET_BIT(CANx->MSR, MSR_INAK) == 0U)
			;
		break;
	}
}

void CAN_initFilter(CAN_FilterInitTypeDef *PTR_sFilterInit) {
	/* The initialization of the filter values  is independent from initialization mode,
	 * but must be done when the filter is not active (corresponding FACTx bit in CAN_FAR cleared).
	 * The filter scale and mode of configuration must be done before entering the
	 * normal mode.
	 */

	/* 28 filter banks (0 --> 27),
	 * Each filter bank x consists of two 32-bit registers, CAN_FxR0 , CAN_FxR1*/

	/*********SCALE*********/
	/* Each filter bank can be scaled independently:
	 *   one 32-bit  filter, for STDID[10:0], EXTID[17:0], IDE and RTR bits
	 *   two  16-bit filter, for STDID[10:0], EXTID[17:15], IDE and RTR bits
	 *
	 *   Scale is configured using FSCx bit in CAN_FSxR
	 */

	/**********MODE***********/
	/* MASK mode       --> specify which bit is "must match" or "don't care"
	 * Mask mode can be used to specify a range of IDs
	 *
	 * IDENTIFIER mode --> all bits of the incoming identifier must match the bits specified in the filter registers
	 * IDENTIFIER mode is used when we want to receive a specific ID rather than the whole range
	 *
	 * Mask/identifier mode is configured in FBMxbits in CAN_FMxR
	 */

	/* set filter to initialize mode */
	SET_BIT(CAN1->FMR, FINIT);

	/* de-activate the filter before initialization */
	CLR_BIT(CAN1->FA1R, PTR_sFilterInit->FilterNumber);

	/* adjust CAN filter mode : */
	CAN1->FM1R = (CAN1->FM1R & ~(1 << PTR_sFilterInit->FilterNumber))
			| (PTR_sFilterInit->FilterMode << PTR_sFilterInit->FilterNumber);

	/* adjust CAN scale mode : */
	CAN1->FS1R = (CAN1->FS1R & ~(1 << PTR_sFilterInit->FilterNumber))
			| (PTR_sFilterInit->FilterScale << PTR_sFilterInit->FilterNumber);

	/* state if the message passed to the filterNumber will be stored in FIFO 0 or  FIFO 1 */
	CAN1->FFA1R = (CAN1->FFA1R & ~(1 << PTR_sFilterInit->FilterNumber))
			| (PTR_sFilterInit->FilterFIFOAssignment
					<< PTR_sFilterInit->FilterNumber);

	/* adjust filter activation mode */
	CAN1->FA1R = (CAN1->FA1R & ~(1 << PTR_sFilterInit->FilterNumber))
			| ((PTR_sFilterInit->FilterActivation)
					<< (PTR_sFilterInit->FilterNumber));

	/* copy identifier into filter bank */
	switch (PTR_sFilterInit->FilterScale) {
	case SINGLE_32: {
		switch (PTR_sFilterInit->FilterMode) {

		case MASK: {
			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR2 = 0;
			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR1 = 0;

			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR2 =
					(((u32) PTR_sFilterInit->FilterMaskIdHigh) << 16)
							| (PTR_sFilterInit->FilterMaskIdLow);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR1 =
					(((u32) PTR_sFilterInit->FilterIdHighR1) << 16)
							| (PTR_sFilterInit->FilterIdLowR1);
		}
			break;

		case LIST: {
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 =
					(((u32) PTR_sFilterInit->FilterIdHighR1) << 16)
							| (PTR_sFilterInit->FilterIdLowR1);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 =
					(((u32) PTR_sFilterInit->FilterIdHighR2) << 16)
							| (PTR_sFilterInit->FilterIdLowR2);
		}
			break;
		}
	}
		break;

	case DOUBLE_16: {
		switch (PTR_sFilterInit->FilterMode) {
		case MASK: {
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 =
					(PTR_sFilterInit->FilterIdLowR1);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 =
					(PTR_sFilterInit->FilterIdLowR2);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 |=
					(((u32) PTR_sFilterInit->FilterMaskIdLow) << 16);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 |=
					(((u32) PTR_sFilterInit->FilterMaskIdHigh) << 16);
		}
			break;

		case LIST: {
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 =
					(PTR_sFilterInit->FilterIdLowR1)
							| (((u32) PTR_sFilterInit->FilterIdHighR1) << 16);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 =
					(PTR_sFilterInit->FilterIdLowR2)
							| (((u32) PTR_sFilterInit->FilterIdHighR2) << 16);
		}
			break;
		}
	}
		break;
	}
	CLR_BIT(CAN1->FMR, FMR_FINIT);
}

void CAN_setSlaveStartBank(u8 Copy_u8CANBankNumber) {
	/* define the start bank for the CAN2 interface in range from ( 0 to 27 ) */
	/* assign 0 to CAN2SB[5:0] == no filters are assigned to CAN1
	 * assign 28 to CAN2SB[5:0] == all filters are assigned to CAN1
	 */

	CAN1->FMR = 0x2A1C0E01; /* register RESET value */

	CAN1->FMR |= (Copy_u8CANBankNumber & 0x3F) << CAN2SB;

	CLR_BIT(CAN1->FMR, FINIT); /* active filter mode enabled */
}

CAN_Tx_MailBox_TypeDef CAN_transmit(CAN_TypeDef *CANx, CanTxMsg *TxMessage) {

	/* Transmisson Handling Function */

	/* First Step: Select an Empty Mailbox to Use for Transmission */

	CAN_Tx_MailBox_TypeDef Local_CAN_TxMailBox_TypeDef_CurrentMailBox; // variable to save the used MailBox in

	/* Check Which MailBox is Empty to use */
	if (GET_BIT(CANx->TSR, TSR_TME0)) {
		Local_CAN_TxMailBox_TypeDef_CurrentMailBox = CAN_TX_MAILBOX_1;
	} else if (GET_BIT(CANx->TSR, TSR_TME1)) {
		Local_CAN_TxMailBox_TypeDef_CurrentMailBox = CAN_TX_MAILBOX_2;
	} else if (GET_BIT(CANx->TSR, TSR_TME2)) {
		Local_CAN_TxMailBox_TypeDef_CurrentMailBox = CAN_TX_MAILBOX_3;
	} else {
		/* All MAILBOXES Are Currently In Use */
		Local_CAN_TxMailBox_TypeDef_CurrentMailBox = CAN_TX_NO_EMPTY_MAILBOX;
		return Local_CAN_TxMailBox_TypeDef_CurrentMailBox;
	}

	/* Second Step: Setup the Identifier
	 * 				Setup The RTR
	 * 				Setup the DLC
	 * 				Put the Data
	 */

	/* Setup The Identifier */

	// Standard Identifier is 11 Bits
	if (TxMessage->IDE == CAN_STANDARD_IDENTIFIER) {
		CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR =
				(((TxMessage->StdId & 0x7FF) << TIR_STID_11BITS)
						| (TxMessage->RTR << TIR_RTR));
	}
	// Extended Identifier is 29 Bits
	else if (TxMessage->IDE == CAN_EXTENDED_IDENTIFIER) {
		CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR =
				(((TxMessage->ExtId & 0x1FFFFFFF) << TIR_EXID_17BITS)
						| (TxMessage->IDE << TIR_IDE)
						| (TxMessage->RTR << TIR_RTR));
	}

	/* Setting The DLC*/
	/* Choose Data length 8 Bytes */

	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDTR &=
			0xFFFFFFF0;
	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDTR |=
			(TxMessage->DLC & 0xFUL);

	// Setting the Data in the Message

	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDHR =
			(((u32) TxMessage->Data[7] << 24) | ((u32) TxMessage->Data[6] << 16)
					| ((u32) TxMessage->Data[5] << 8)
					| ((u32) TxMessage->Data[4]));

	CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TDLR =
			(((u32) TxMessage->Data[3] << 24) | ((u32) TxMessage->Data[2] << 16)
					| ((u32) TxMessage->Data[1] << 8)
					| ((u32) TxMessage->Data[0]));

	/* Final Step: Request The Transmission*/
	SET_BIT(CANx->sTxMailBox[Local_CAN_TxMailBox_TypeDef_CurrentMailBox].TIR,
			TIR_TXRQ);

	/* Return The used MailBox*/
	return Local_CAN_TxMailBox_TypeDef_CurrentMailBox;
}

void CAN_receive(CAN_TypeDef *CANx, CAN_Rx_FIFO_TypeDef FIFONumber,
		CanRxMsg *RxMessage) {

	/* Check if the selected mailbox is empty */
	switch (FIFONumber) {
	/*If the first FIFO mailbox is selected*/
	case (CAN_RX_FIFO_1): {
		if ((CANx->RF0R & 0x3) == 0U) {
			return;
		}
		break;
	}
		/*If the second FIFO mailbox is selected*/
	case (CAN_RX_FIFO_2): {
		if ((CANx->RF1R & 0x3) == 0U) {
			return;
		}
		break;
	}
	}

	/*Getting the identifier type either Standard or Extended from received message*/
	RxMessage->IDE = (u8) GET_BIT(CANx->sFIFOMailBox[FIFONumber].RIR, RIR_IDE);

	/*Operating depending on the received identifier type*/
	switch (RxMessage->IDE) {
	/*Standard Identifier*/
	case (CAN_STANDARD_IDENTIFIER): {
		/*Get the value of the Standard Identifier*/
		RxMessage->StdId = (u16) ((CANx->sFIFOMailBox[FIFONumber].RIR
				>> RIR_STID_11BITS) & 0x000007FF);
		break;
	}
		/*Extended Identifier*/
	case (CAN_EXTENDED_IDENTIFIER): {
		/*Get the value of the Extended Identifier*/
		RxMessage->ExtId = (u32) ((CANx->sFIFOMailBox[FIFONumber].RIR
				>> RIR_EXID_17BITS) & 0x1FFFFFFF);
		break;
	}
	}

	/*Get the value of the frame either it is data or remote*/
	RxMessage->RTR = GET_BIT(CANx->sFIFOMailBox[FIFONumber].RIR, RIR_RTR);

	/*Get the value of the data length code*/
	RxMessage->DLC = (u8) (0x0F & (CANx->sFIFOMailBox[FIFONumber].RDTR));

	/*Read the index of the filter message*/
	RxMessage->FMI = (u8) (0x0F
			& (CANx->sFIFOMailBox[FIFONumber].RDTR >> RDTR_FMI_8BITS));

	/*Read the data received*/
	/*Reading the data from the RDLR register*/
	RxMessage->Data[0] = (u8) (0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR));
	RxMessage->Data[1] =
			(u8) (0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 8));
	RxMessage->Data[2] = (u8) (0xFF
			& (CANx->sFIFOMailBox[FIFONumber].RDLR >> 16));
	RxMessage->Data[3] = (u8) (0xFF
			& (CANx->sFIFOMailBox[FIFONumber].RDLR >> 24));
	/*Reading the data from the RDHR register*/
	RxMessage->Data[4] = (u8) (0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR));
	RxMessage->Data[5] =
			(u8) (0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 8));
	RxMessage->Data[6] = (u8) (0xFF
			& (CANx->sFIFOMailBox[FIFONumber].RDHR >> 16));
	RxMessage->Data[7] = (u8) (0xFF
			& (CANx->sFIFOMailBox[FIFONumber].RDHR >> 24));
	/*Checking on the entered FIFO number to know which mailbox to work with*/
	switch (FIFONumber) {
	/*If the first FIFO mailbox is selected*/
	case (CAN_RX_FIFO_1): {
		/*Setting the RFOM bit to release output from mailbox*/
		SET_BIT(CANx->RF0R, RFR_RFOM);
		break;
	}
		/*If the second FIFO mailbox is selected*/
	case (CAN_RX_FIFO_2): {
		/*Setting the RFOM bit to release output from mailbox*/
		SET_BIT(CANx->RF1R, RFR_RFOM);
		break;
	}
	}
}

u32 CAN_formatIdentifierIntoFRx(u32 STDID, u32 EXTID,
		CAN_Identifier_TypeDef a_idType, CAN_FilterScale scale, u8 RTR) {

	CAN_FilterRegisterUnion_Single32 FRx_union32 = { 0 };

	CAN_FilterRegisterUnion_Double16 FRx_union16 = { 0 };

	RTR &= 0x1;
	/* Union used to set the identifier bits as the mapping in actual FRx register */

	switch (a_idType) {
	case CAN_STANDARD_IDENTIFIER:

		/* Sanitize input: Mask the first 11 bits */
		STDID &= 0x7FF;
		switch (scale) {
		case SINGLE_32:

			/* Set IDE bit */
			FRx_union32.Bits.IDE = a_idType;
			/* Set RTR bit */
			FRx_union32.Bits.RTR = RTR;
			/* Set all 11 bits of STID */
			FRx_union32.Bits.STID = STDID;

			return FRx_union32.FRx;

			// FRx_Low = (RTR << 1);
			// FRx_High = (STDID << 5);
			// FRx = (FRx_High << 16) | FRx_Low;
			break;

		case DOUBLE_16:

			/* Set IDE bit */
			FRx_union32.Bits.IDE = a_idType;
			/* Set RTR bit */
			FRx_union32.Bits.RTR = RTR;
			/* Set 1st 3 bits of STID */
			FRx_union16.Bits.STID_0_2 = STDID & 0x7UL;
			/* Set rest of the bits of STID */
			FRx_union16.Bits.STID_3_10 = ((STDID >> 3) & 0xFFUL);

			return FRx_union16.FRx;

			// FRx_Low = (STDID << 5) | (RTR << 5);
			// FRx_High = (STDID >> 3);
			// FRx = (FRx_High << 16) | FRx_Low;
			break;
		}

		break;
	case CAN_EXTENDED_IDENTIFIER:

		/* Sanitize input: Mask the first 11 bits */
		STDID &= 0x7FF;
		/* Sanitize input: Mask the first 18 bits */
		EXTID &= 0x3FFFF;

		switch (scale) {
		case SINGLE_32:

			/* Set IDE bit */
			FRx_union32.Bits.IDE = a_idType;
			/* Set RTR bit */
			FRx_union32.Bits.RTR = RTR;
			/* Set all 11 bits of STID */
			FRx_union32.Bits.STID = STDID;
			/* Get 1st 13 bits from EXTID */
			FRx_union32.Bits.EXID_0_12 = (EXTID & 0x1FFF);
			/* Get last 5 bits from EXTID */
			FRx_union32.Bits.EXID_13_17 = (EXTID >> 13) & 0x1FULL;

			return FRx_union32.FRx;
			// FRx_Low = ((EXTID & 0x1FFF) << 3) | (0b100) | (RTR << 1);
			// FRx_High = (EXTID >> 13) | (STDID << 5);
			// FRx = (FRx_High << 16) | FRx_Low;

			break;
		case DOUBLE_16:

			/* Set IDE bit */
			FRx_union16.Bits.IDE = a_idType;
			/* Set RTR bit */
			FRx_union16.Bits.RTR = RTR;
			/* Set 1st 3 bits of STID */
			FRx_union16.Bits.STID_0_2 = STDID & 0x7UL;
			/* Set rest of the bits of STID */
			FRx_union16.Bits.STID_3_10 = ((STDID >> 3) & 0xFFUL);
			/* Get last 3 bits from EXTID */
			FRx_union16.Bits.EXID_15_17 = ((EXTID >> 15) & 0x7UL);

			return FRx_union16.FRx;

			// FRx_Low = (EXTID >> 15) | (STDID << 5) | (RTR << 5) | (1 << 4);
			// FRx_High = (STDID >> 3);
			// FRx = (FRx_High << 16) | FRx_Low;
			break;
		}
		break;
	}
	return 0;
}

CAN_Status_Typedef CAN_appendDeviceToBus(u32 devID,
		CAN_Identifier_TypeDef a_idType) {

	if (CAN_devicesCount == CAN_MAX_DEVICES_COUNT)
		return CAN_Status_MaxDevicesReached;

	CAN_Status_Typedef localStatus = CAN_Status_OK;
	u32 FRx_val = 0;
	switch (a_idType) {
	case CAN_STANDARD_IDENTIFIER:
		FRx_val = CAN_formatIdentifierIntoFRx(devID, 0, a_idType, SINGLE_32, 0);
		break;
	case CAN_EXTENDED_IDENTIFIER:
		FRx_val = CAN_formatIdentifierIntoFRx(devID >> 18, devID & 0x3FFFF,
				a_idType, SINGLE_32, 0);
		break;
	}
	do {
		/* Index of the first empty filter found (de-activated filter)*/
		u8 emptyFilterIdx = 0;
		/* Assume FR1 is empty */
		u8 emptyRegisterIdx = 1;

		for (; emptyFilterIdx < CAN_MAX_DEVICES_COUNT; ++emptyFilterIdx) {
			/* Find de-activated filter which is unused OR find FRx registers with zero value*/
			if (!GET_BIT(CAN1->FA1R, emptyFilterIdx)) {
				/* Both empty as the filter was de-activated */
				emptyRegisterIdx = 0;
				++CAN_devicesCount;
				break;
			} else if (
			CAN1->sFilterRegister[emptyFilterIdx].FR1 == 0U ||
			CAN1->sFilterRegister[emptyFilterIdx].FR2 == 0U) {
				/* One of them is empty */
				emptyRegisterIdx =
				CAN1->sFilterRegister[emptyFilterIdx].FR1 == 0U ? 1 : 2;
				++CAN_devicesCount;
				break;
			}
		}

		/* No empty filter banks are found, exit*/
		if (emptyFilterIdx == CAN_MAX_DEVICES_COUNT) {
			localStatus |= CAN_Status_MaxDevicesReached;
			break;
		}
		/* Found an empty filter bank to use */
		CAN_FilterInitTypeDef localFilterConfig = { 0 };
		/**
		 * Filter mode -> List identifier for multiple ID's
		 * Filter FIFO assignment = FIFO 1
		 * Filter Activation = Enabled
		 * Filter scale = Single 32 bit filter ID
		 */
		localFilterConfig.FilterMode = LIST;
		// TODO alternate bet. fifo 1 & 2?
		localFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO_1;
		localFilterConfig.FilterActivation = ENABLE;

		localFilterConfig.FilterScale = SINGLE_32;
		localFilterConfig.FilterNumber = emptyFilterIdx;
		/* Choose an empty register whether both FR1, FR2 or only one of them*/
		switch (emptyRegisterIdx) {
		/* Both registers are empty, insert into R1, zero R2 for future insertions*/
		case 0:

			localFilterConfig.FilterIdLowR1 = FRx_val & 0xFFFF;
			localFilterConfig.FilterIdHighR1 = FRx_val >> 16;

			localFilterConfig.FilterIdLowR2 = 0;
			localFilterConfig.FilterIdHighR2 = 0;
			break;
			/* Only FR1 is empty, use FR1  only, keep FR2 old value */
		case 1:
			localFilterConfig.FilterIdLowR1 = FRx_val & 0xFFFF;
			localFilterConfig.FilterIdHighR1 = FRx_val >> 16;
			/* Get old value of FR2*/
			localFilterConfig.FilterIdLowR2 =
			CAN1->sFilterRegister[emptyFilterIdx].FR2 & 0x0000FFFF;
			localFilterConfig.FilterIdHighR2 =
					(CAN1->sFilterRegister[emptyFilterIdx].FR2 >> 16);
			break;
			/* Only FR2 is empty, use FR2  only, keep FR1 old value */
		case 2:
			localFilterConfig.FilterIdLowR2 = FRx_val & 0xFFFF;
			localFilterConfig.FilterIdHighR2 = FRx_val >> 16;
			/* Get old value of FR1*/
			localFilterConfig.FilterIdLowR1 =
			CAN1->sFilterRegister[emptyFilterIdx].FR1 & 0x0000FFFF;
			localFilterConfig.FilterIdHighR1 =
					(CAN1->sFilterRegister[emptyFilterIdx].FR1 >> 16);
			break;
		default:
			break;
		}

		/* Initialize selected filter */
		CAN_initFilter(&localFilterConfig);

		break;
	} while (0);

	return localStatus;
}

CAN_Status_Typedef CAN_removeDeviceFromBus(u32 a_devID,
		CAN_Identifier_TypeDef a_idType) {

	CAN_Status_Typedef localStatus = CAN_Status_OK;

	do {
		/* Index of the filter found which contains this device ID*/
		u8 deviceFilterIdx = 0;
		/* Adjust the device ID to be like the mapped format in FRx register*/
		// u32 FRx_checkVal = (((devID >> 13)) << 16) | ((((u16)devID) << 3) | (1 << 2));
		u32 FRx_checkVal = 0;
		switch (a_idType) {
		case CAN_STANDARD_IDENTIFIER:
			FRx_checkVal = CAN_formatIdentifierIntoFRx(a_devID, 0, a_idType,
					SINGLE_32, 0);
			break;
		case CAN_EXTENDED_IDENTIFIER:
			FRx_checkVal = CAN_formatIdentifierIntoFRx(a_devID >> 18,
					a_devID & 0x3FFFF, a_idType, SINGLE_32, 0);
			break;
		}
		for (; deviceFilterIdx < CAN_MAX_DEVICES_COUNT; ++deviceFilterIdx) {
			if (GET_BIT(CAN1->FA1R, deviceFilterIdx)) {

				if (CAN1->sFilterRegister[deviceFilterIdx].FR1
						== FRx_checkVal) {

					/* Deactivate filter to modify FiRx registers*/
					CLR_BIT(CAN1->FA1R, deviceFilterIdx);
					/* Set FR1 to zero to know it is unused in the future*/
					CAN1->sFilterRegister[deviceFilterIdx].FR1 = 0;
					--CAN_devicesCount;
					/* If FR2 is also zero, keep the filter deactivated */
					if (CAN1->sFilterRegister[deviceFilterIdx].FR2 == 0) {
						break;
					} else {
						/* Activate filter if FR2 is non zero*/
						SET_BIT(CAN1->FA1R, deviceFilterIdx);
						break;
					}
					break;
				} else if (CAN1->sFilterRegister[deviceFilterIdx].FR2
						== FRx_checkVal) {
					/* Deactivate filter to modift FiRx registers*/
					CLR_BIT(CAN1->FA1R, deviceFilterIdx);
					/* Set FR2 to zero to know it is unused in the future*/
					CAN1->sFilterRegister[deviceFilterIdx].FR2 = 0;
					--CAN_devicesCount;
					/* If FR1 is also zero, keep the filter deactivated */
					if (CAN1->sFilterRegister[deviceFilterIdx].FR1 == 0) {
						break;
					} else {
						/* Activate filter if FR1 is non zero*/
						SET_BIT(CAN1->FA1R, deviceFilterIdx);
						break;
					}
				}
			}
		}
		/* If device was not found*/
		if (deviceFilterIdx == CAN_MAX_DEVICES_COUNT) {
			localStatus |= CAN_Status_DeviceIDInvalid;
		}
		break;
	} while (0);

	return localStatus;
}

CAN_Status_Typedef CAN_sendMessage_Interrupt(const u8 *a_data, u8 a_len,
		CAN_Identifier_TypeDef a_idType, u32 a_devID) {

	/* null check */
	if (a_data == NULLPTR)
		return CAN_Status_NullError;

	/* Return if data length is greater than max CAN data bytes */
	if (a_len > 8) {
		return CAN_Status_OverMaxLength;
	}

	p_CANTxMsg.DLC = a_len;

	for (u8 i = 0; i < a_len; i++) {
		p_CANTxMsg.Data[i] = a_data[i];
	}

	/* Decide identifier type */
	p_CANTxMsg.ExtId = p_CANTxMsg.StdId = a_devID;
	p_CANTxMsg.IDE = a_idType == CAN_STANDARD_IDENTIFIER ? 0 : 1;

	p_CANTxMsg.RTR = 0;

	return CAN_Status_OK;
}

CAN_Status_Typedef CAN_receiveMessage_Interrupt(u8 **a_data, u8 *a_len,
		u32 *a_devID) {

	/* null check */
	if (a_data == NULLPTR || a_len == NULLPTR)
		return CAN_Status_NullError;

	CAN_RxSize = a_len;
	CAN_RxBuffer = a_data;
	CAN_RxID = a_devID;

	/* Return status code */
	return CAN_Status_OK;
}

CAN_Status_Typedef CAN_sendMessage(const u8 *a_data, u8 a_len,
		CAN_Identifier_TypeDef a_idType, u32 a_devID) {

	/* null check */
	if (a_data == NULLPTR)
		return CAN_Status_NullError;

	/* Status code */
	CAN_Status_Typedef localStatus = CAN_Status_OK;

	do {
		/* Return if data length is greater than max CAN data bytes */
		if (a_len > 8) {
			localStatus |= CAN_Status_OverMaxLength;
			break;
		}

		/* Create a new tx frame */
		CanTxMsg localTxMsg = { 0 };

		/* Copy DLC byte */
		localTxMsg.DLC = a_len;

		/* Copy data from buffer to frame */
		for (int i = 0; i < a_len; i++) {
			localTxMsg.Data[i] = a_data[i];
		}

		/* Decide identifier type */
		localTxMsg.ExtId = localTxMsg.StdId = a_devID;
		localTxMsg.IDE =
				(a_idType == CAN_STANDARD_IDENTIFIER) ?
						CAN_STANDARD_IDENTIFIER : CAN_EXTENDED_IDENTIFIER;

		CAN_Tx_MailBox_TypeDef mailbox_used = CAN_transmit(CAN1, &localTxMsg);

		/* No empty mailboxes, return */
		if (mailbox_used == CAN_TX_NO_EMPTY_MAILBOX) {
			localStatus |= CAN_Status_FullMailboxes;
			break;
		}

	} while (0);

	/* Return status code */
	return localStatus;
}

CAN_Status_Typedef CAN_receiveMessage(u8 *a_data, u8 *a_len, u32 *a_devID) {

	/* null check */
	if (a_data == NULLPTR || a_len == NULLPTR)
		return CAN_Status_NullError;

	/* Status code */
	CAN_Status_Typedef localStatus = CAN_Status_OK;

	do {

		CanRxMsg localRxMsg = { 0 };
		/* Check if there are new messages on either FIFO's, if not break */
		if ((CAN1->RF0R & 0x3) != 0) {
			CAN_receive(CAN1, CAN_RX_FIFO_1, &localRxMsg);
		} else if ((CAN1->RF1R & 0x3) != 0) {
			CAN_receive(CAN1, CAN_RX_FIFO_2, &localRxMsg);
		} else {
			localStatus |= CAN_Status_Error;
			break;
		}
		/* Set the received message length*/
		*a_len = localRxMsg.DLC;
		/* Copy data into buffer array */
		for (u8 i = 0; i < localRxMsg.DLC; ++i) {
			a_data[i] = localRxMsg.Data[i];
		}
		*a_devID = (((u32) localRxMsg.ExtId) << 11) | localRxMsg.StdId;

	} while (0);

	/* Return status code */
	return localStatus;
}

CAN_Status_Typedef CAN_attachCallback(CAN_Interrupt_TypeDef a_interruptType,
		void (*a_callbackPtr)()) {
	if (a_callbackPtr == NULLPTR)
		return CAN_Status_NullError;

	switch (a_interruptType) {
	case CAN_Interrupt_Transmit:

		/* Set user callback pointer */
		CAN_transmit_CallbackPtr = a_callbackPtr;

		/* Enable IRQ in NVIC */
		NVIC_enableIRQ(IRQ_USB_HP_CAN_TX);

		break;
	case CAN_Interrupt_FIFO0:
		/* Set user callback pointer */
		CAN_FIFO0_CallbackPtr = a_callbackPtr;

		/* Enable IRQ in NVIC */
		NVIC_enableIRQ(IRQ_USB_LP_CAN_RX0);

		break;
	case CAN_Interrupt_FIFO1:
		/* Set user callback pointer */
		CAN_FIFO1_CallbackPtr = a_callbackPtr;

		/* Enable IRQ in NVIC */
		NVIC_enableIRQ(IRQ_CAN_RX1);

		break;
	case CAN_Interrupt_Status:

		/* Set user callback pointer */
		CAN_Status_CallbackPtr = a_callbackPtr;

		/* Enable IRQ in NVIC */
		NVIC_enableIRQ(IRQ_CAN_SCE);

		break;
	default:
		return CAN_Status_Error;
		break;
	}
	/* Return OK on operation success */
	return CAN_Status_OK;
}

CAN_Status_Typedef CAN_detachCallback(CAN_Interrupt_TypeDef a_interruptType) {

	switch (a_interruptType) {
	case CAN_Interrupt_Transmit:
		/* Disable IRQ in NVIC */
		NVIC_disableIRQ(IRQ_USB_HP_CAN_TX);

		/* Reset callback pointer to null */
		CAN_transmit_CallbackPtr = NULLPTR;

		break;
	case CAN_Interrupt_FIFO0:
		/* Disable IRQ in NVIC */
		NVIC_disableIRQ(IRQ_USB_LP_CAN_RX0);

		/* Reset callback pointer to null */
		CAN_FIFO0_CallbackPtr = NULLPTR;

		break;

	case CAN_Interrupt_FIFO1:
		/* Disable IRQ in NVIC */
		NVIC_disableIRQ(IRQ_CAN_RX1);

		/* Reset callback pointer to null */
		CAN_FIFO1_CallbackPtr = NULLPTR;

		break;

	case CAN_Interrupt_Status:
		/* Disable IRQ in NVIC */
		NVIC_disableIRQ(IRQ_CAN_SCE);

		/* Reset callback pointer to null */
		CAN_Status_CallbackPtr = NULLPTR;

		break;
	default:
		return CAN_Status_Error;
		break;
	}
	/* Return OK on operation success */
	return CAN_Status_OK;
}

CAN_Status_Typedef CAN_activateInterrupt(CAN_TypeDef *CANx,
		CAN_Interrupt_TypeDef a_interruptType) {
	switch (a_interruptType) {
	case CAN_Interrupt_Transmit:
		/* Enable interrupts for transmit event */
		SET_BIT(CANx->IER, IER_TMEIE);
		break;
	case CAN_Interrupt_FIFO0:
		/* Enable interrupts for new message reception event */
		SET_BIT(CANx->IER, IER_FMPIE0);
		break;
	case CAN_Interrupt_FIFO1:
		/* Enable interrupts for new message reception event */
		SET_BIT(CANx->IER, IER_FMPIE1);
		break;
	case CAN_Interrupt_Status:
		/* Enable interrupts for errors or status changes */
		SET_BIT(CANx->IER, IER_ERRIE);
		SET_BIT(CANx->IER, IER_EWGIE);
		SET_BIT(CANx->IER, IER_EPVIE);
		SET_BIT(CANx->IER, IER_BOFIE);
		SET_BIT(CANx->IER, IER_LECIE);
		// SET_BIT(CANx->IER, IER_WKUIE);
		// SET_BIT(CANx->IER, IER_SLKIE);
		break;
	default:
		return CAN_Status_Error;
		break;
	}
	/* Return OK on operation success */
	return CAN_Status_OK;
}

CAN_Status_Typedef CAN_deactivateInterrupt(CAN_TypeDef *CANx,
		CAN_Interrupt_TypeDef a_interruptType) {
	switch (a_interruptType) {
	case CAN_Interrupt_Transmit:
		/* Disable interrupts for transmit event */
		CLR_BIT(CANx->IER, IER_TMEIE);
		break;
	case CAN_Interrupt_FIFO0:
		/* Disable interrupts for new message reception event */
		CLR_BIT(CANx->IER, IER_FMPIE0);
		break;
	case CAN_Interrupt_FIFO1:
		/* Disable interrupts for new message reception event */
		CLR_BIT(CANx->IER, IER_FMPIE1);
		break;
	case CAN_Interrupt_Status:
		/* Disable interrupts for errors or status changes */
		CLR_BIT(CANx->IER, IER_ERRIE);
		CLR_BIT(CANx->IER, IER_EWGIE);
		CLR_BIT(CANx->IER, IER_EPVIE);
		CLR_BIT(CANx->IER, IER_BOFIE);
		CLR_BIT(CANx->IER, IER_LECIE);
		// CLR_BIT(CANx->IER, IER_WKUIE);
		// CLR_BIT(CANx->IER, IER_SLKIE);
		break;
	default:
		return CAN_Status_Error;
		break;
	}
	/* Return OK on operation success */
	return CAN_Status_OK;
}

/* Interrupt handlers */

void USB_HP_CAN_TX_IRQHandler(void) {
	/* A mailbox is empty, transmit now */
	CAN_transmit(CAN1, (CanTxMsg*) &p_CANTxMsg);

	/* Disable interrupts for transmit event */
	CLR_BIT(CAN1->IER, IER_TMEIE);

	/* Call user callback function if not null*/
	if (CAN_transmit_CallbackPtr != NULLPTR)
		(*CAN_transmit_CallbackPtr)();
}

void USB_LP_CAN_RX0_IRQHandler(void) {
	CanRxMsg localRxMsg = { 0 };

	CAN_receive(CAN1, CAN_RX_FIFO_1, &localRxMsg);
	*CAN_RxSize = localRxMsg.DLC;

	/* Copy data into buffer array */
	for (u8 i = 0; i < localRxMsg.DLC; i++) {
		CAN_RxBuffer[i] = localRxMsg.Data[i];
	}

	/* Decide identifier type to save the ID */
	*CAN_RxID =
			localRxMsg.IDE == CAN_EXTENDED_IDENTIFIER ?
					localRxMsg.ExtId : localRxMsg.StdId;

	/* Call user callback function if not null*/
	if (CAN_FIFO0_CallbackPtr != NULLPTR)
		(*CAN_FIFO0_CallbackPtr)();
}

void CAN_RX1_IRQHandler(void) {
	CanRxMsg localRxMsg = { 0 };

	CAN_receive(CAN1, CAN_RX_FIFO_2, &localRxMsg);
	*CAN_RxSize = localRxMsg.DLC;

	/* Copy data into buffer array */
	for (u8 i = 0; i < localRxMsg.DLC; i++) {
		CAN_RxBuffer[i] = localRxMsg.Data[i];
	}

	/* Decide identifier type to save the ID */
	*CAN_RxID =
			localRxMsg.IDE == CAN_EXTENDED_IDENTIFIER ?
					localRxMsg.ExtId : localRxMsg.StdId;

	/* Disable interrupts for new message reception event */
	CLR_BIT(CAN1->IER, IER_FMPIE1);

	/* Call user callback function if not null*/
	if (CAN_FIFO1_CallbackPtr != NULLPTR)
		(*CAN_FIFO1_CallbackPtr)();
}

void CAN_SCE_IRQHandler(void) {
	/* Call user callback function if not null*/
	if (CAN_Status_CallbackPtr != NULLPTR)
		(*CAN_Status_CallbackPtr)();
}
