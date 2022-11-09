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
	CLR_BIT(CAN1->FA1R,PTR_sFilterInit->FilterNumber);


	/* adjust CAN filter mode : */
	CAN1->FM1R = (CAN1->FM1R & ~(1<<PTR_sFilterInit->FilterNumber)) | (PTR_sFilterInit->FilterMode<<PTR_sFilterInit->FilterNumber);
	/* adjust CAN scale mode : */
	CAN1->FS1R = (CAN1->FS1R & ~(1<<PTR_sFilterInit->FilterNumber)) | (PTR_sFilterInit->FilterScale<<PTR_sFilterInit->FilterNumber);
	/* state if the message passed to the filterNumber will be stored in FIFO 0 or  FIFO 1 */
	CAN1->FFA1R = (CAN1->FFA1R & ~(1<<PTR_sFilterInit->FilterNumber)) | (PTR_sFilterInit->FilterFIFOAssignment<<PTR_sFilterInit->FilterNumber);
	/* adjust filter activation mode */
	CAN1->FA1R = (PTR_sFilterInit->FilterActivation)<<(PTR_sFilterInit->FilterNumber);

	/* copy identifier into filter bank */
	switch(PTR_sFilterInit->FilterScale)
	{
	case SINGLE_32:
	{
		switch(PTR_sFilterInit->FilterMode)
		{

		case MASK:
		{
			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR2 = 0;
			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR1 = 0;

			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR2 = (PTR_sFilterInit->FilterMaskIdHigh)<<16 | (PTR_sFilterInit->FilterMaskIdLow);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterMode].FR1 = (PTR_sFilterInit->FilterIdHighR1)<<16 | (PTR_sFilterInit->FilterIdLowR1);
		}
		break;


		case LIST:
		{
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 = (PTR_sFilterInit->FilterIdHighR1)<<16 | (PTR_sFilterInit->FilterIdLowR1);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 = (PTR_sFilterInit->FilterIdHighR2)<<16 | (PTR_sFilterInit->FilterIdLowR2);
		}
		break;
		}
	}
	break;

	case DOUBLE_16:
	{
		switch(PTR_sFilterInit->FilterMode)
		{
		case MASK:
		{
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 = (PTR_sFilterInit->FilterIdLowR1);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 = (PTR_sFilterInit->FilterIdLowR2);
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 |= (PTR_sFilterInit->FilterMaskIdLow)<<16;
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR2 |= (PTR_sFilterInit->FilterMaskIdHigh)<<16;

		}
		break;

		case LIST:
		{
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 = (PTR_sFilterInit->FilterIdLowR1) | (PTR_sFilterInit->FilterIdHighR1)<<16;
			CAN1->sFilterRegister[PTR_sFilterInit->FilterNumber].FR1 = (PTR_sFilterInit->FilterIdLowR2) | (PTR_sFilterInit->FilterIdHighR2)<<16;
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

	CAN1->FMR |=  (Copy_u8CANBankNumber & 0x3F)<<CAN2SB;

	CLR_BIT(CAN1->FMR,FINIT); /* active filter mode enabled */

}


CAN_Tx_MailBox_TypeDef CAN_transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage)
{

}

void CAN_receive(CAN_TypeDef* CANx, u8 FIFONumber, CanRxMsg* RxMessage)
{

}
