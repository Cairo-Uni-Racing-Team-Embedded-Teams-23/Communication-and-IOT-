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

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../CURT_CAN_headers/CAN_private.h"
#include "../CURT_CAN_headers/CAN_config.h"
#include "../CURT_CAN_headers/CAN_interface.h"
#include "../../CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "../../CURT_GPIO/CURT_GPIO_headers/GPIO_interface.h"

/*******************************************************************************
 *                        Public functions definitions                         *
 *******************************************************************************/

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

	switch (Copy_enuCANConfig)
	{
	case CAN_CONFIG_1:

		/* Disable all CAN interrupts */
		CANx->IER = 0;

		/* Set the bits for settings we need in configuration 1*/
		CANx->MCR = ((CAN1_FIFO_PRIORITY << MCR_TXFP) | (CAN1_RECEIVE_FIFO_LOCKED_MODE << MCR_RFLM) | (CAN1_NO_AUTOMATIC_RETRANSMISSION << MCR_NART) | (CAN1_AUTOMATIC_WAKE_UP_MODE << MCR_AWUM) | (CAN1_AUTOMATIC_BUS_OFF << MCR_ABOT) | (CAN1_TIME_TRIGGERED_COMMUNICATION_MODE << MCR_TTCM));

		/* Exit sleep mode to init mode */
		SET_BIT(CANx->MCR, MCR_INRQ);
		/* Wait until HW is in initialization  mode, so that we can setup timing parameters:
		 INAK = 1
		 SLAK = 0
		 */
		while (!GET_BIT(CANx->MSR, MSR_INAK) && GET_BIT(CANx->MSR, MSR_SLAK))
			;

		/* Set up timing parameters */
		CANx->BTR = ((CAN1_MODE << BTR_LBKM) | (CAN1_RESYNC_JUMP_WIDTH << BTR_SJW_2BITS) | (CAN1_TIME_SEGMENT_1 << BTR_TS1_4BITS) | (CAN1_TIME_SEGMENT_2 << BTR_TS2_3BITS) | (CAN1_BAUD_RATE_PRESCALER << BTR_BRP_10BITS));

		break;
	case CAN_CONFIG_2:

		/* Disable all CAN interrupts */
		CANx->IER = 0;

		/* Set the bits for settings we need in configuration 1*/
		CANx->MCR = ((CAN2_FIFO_PRIORITY << MCR_TXFP) | (CAN2_RECEIVE_FIFO_LOCKED_MODE << MCR_RFLM) | (CAN2_NO_AUTOMATIC_RETRANSMISSION << MCR_NART) | (CAN2_AUTOMATIC_WAKE_UP_MODE << MCR_AWUM) | (CAN2_AUTOMATIC_BUS_OFF << MCR_ABOT) | (CAN2_TIME_TRIGGERED_COMMUNICATION_MODE << MCR_TTCM));

		/* Exit sleep mode to init mode */
		SET_BIT(CANx->MCR, MCR_INRQ);
		/* Wait until HW is in initialization  mode, so that we can setup timing parameters:
		 INAK = 1
		 SLAK = 0
		 */
		while (!GET_BIT(CANx->MSR, MSR_INAK) && GET_BIT(CANx->MSR, MSR_SLAK))
			;

		/* Set up timing parameters */
		CANx->BTR = ((CAN2_MODE << BTR_LBKM) | (CAN2_RESYNC_JUMP_WIDTH << BTR_SJW_2BITS) | (CAN2_TIME_SEGMENT_1 << BTR_TS1_4BITS) | (CAN2_TIME_SEGMENT_2 << BTR_TS2_3BITS) | (CAN2_BAUD_RATE_PRESCALER << BTR_BRP_10BITS));

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
	CAN1->FFA1R = (CAN1->FFA1R & ~(1 << PTR_sFilterInit->FilterNumber)) | (PTR_sFilterInit->FilterFIFOAssignment << PTR_sFilterInit->FilterNumber);
	/* adjust filter activation mode */
	CAN1->FA1R = (PTR_sFilterInit->FilterActivation) << (PTR_sFilterInit->FilterNumber);

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

			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR2 = (PTR_sFilterInit->FilterMaskIdHigh) << 16 | (PTR_sFilterInit->FilterMaskIdLow);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR1 = (PTR_sFilterInit->FilterIdHighR1) << 16 | (PTR_sFilterInit->FilterIdLowR1);
		}
		break;

		case LIST:
		{
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 = (PTR_sFilterInit->FilterIdHighR1) << 16 | (PTR_sFilterInit->FilterIdLowR1);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 = (PTR_sFilterInit->FilterIdHighR2) << 16 | (PTR_sFilterInit->FilterIdLowR2);
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
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 = (PTR_sFilterInit->FilterIdLowR1);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 = (PTR_sFilterInit->FilterIdLowR2);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 |= (PTR_sFilterInit->FilterMaskIdLow) << 16;
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 |= (PTR_sFilterInit->FilterMaskIdHigh) << 16;
		}
		break;

		case LIST:
		{
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 = (PTR_sFilterInit->FilterIdLowR1) | (PTR_sFilterInit->FilterIdHighR1) << 16;
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 = (PTR_sFilterInit->FilterIdLowR2) | (PTR_sFilterInit->FilterIdHighR2) << 16;
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
}

void CAN_receive(CAN_TypeDef *CANx, u8 FIFONumber, CanRxMsg *RxMessage)
{
}
