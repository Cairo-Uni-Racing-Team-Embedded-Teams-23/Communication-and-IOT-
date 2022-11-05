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
    GPIO_setupPinMode(GPIOA_ID,PIN11,OUTPUT_SPEED_10MHZ_AFPP);
    GPIO_setupPinMode(GPIOA_ID,PIN12,OUTPUT_SPEED_10MHZ_AFPP);

    switch (Copy_enuCANConfig)
    {
    case CAN_CONFIG_1:

        /* Disable all CAN interrupts */
        CANx->IER = 0;

        /* Set the bits for settings we need in configuration 1*/
        CANx->MCR = ((CAN1_FIFO_PRIORITY << MCR_TXFP) |
                     (CAN1_RECEIVE_FIFO_LOCKED_MODE << MCR_RFLM) |
                     (CAN1_NO_AUTOMATIC_RETRANSMISSION << MCR_NART) |
                     (CAN1_AUTOMATIC_WAKE_UP_MODE << MCR_AWUM) |
                     (CAN1_AUTOMATIC_BUS_OFF << MCR_ABOT) |
                     (CAN1_TIME_TRIGGERED_COMMUNICATION_MODE << MCR_TTCM));

        /* Exit sleep mode */
        CLR_BIT(CANx->MCR, MCR_SLEEP);
        /* Wait until HW is in initialization  mode, so that we can setup timing parameters:
           INAK = 1
           SLAK = 0
        */
        while (
            GET_BIT(CANx->MSR, MSR_INAK) &&
            !GET_BIT(CANx->MSR, MSR_SLAK))
            ;

        /* Set up timing parameters */
        CANx->BTR = ((CAN1_MODE << BTR_LBKM) |
                     (CAN1_RESYNC_JUMP_WIDTH << BTR_SJW_2BITS) |
                     (CAN1_TIME_SEGMENT_1 << BTR_TS1_4BITS) |
                     (CAN1_TIME_SEGMENT_2 << BTR_TS2_3BITS) |
                     (CAN1_BAUD_RATE_PRESCALER << BTR_BRP_10BITS));

        break;
    case CAN_CONFIG_2:

        /* Disable all CAN interrupts */
        CANx->IER = 0;

        /* Set the bits for settings we need in configuration 1*/
        CANx->MCR = ((CAN2_FIFO_PRIORITY << MCR_TXFP) |
                     (CAN2_RECEIVE_FIFO_LOCKED_MODE << MCR_RFLM) |
                     (CAN2_NO_AUTOMATIC_RETRANSMISSION << MCR_NART) |
                     (CAN2_AUTOMATIC_WAKE_UP_MODE << MCR_AWUM) |
                     (CAN2_AUTOMATIC_BUS_OFF << MCR_ABOT) |
                     (CAN2_TIME_TRIGGERED_COMMUNICATION_MODE << MCR_TTCM));

        /* Exit sleep mode */
        CLR_BIT(CANx->MCR, MCR_SLEEP);
        /* Wait until HW is in initialization  mode, so that we can setup timing parameters:
           INAK = 1
           SLAK = 0
        */
        while (
            GET_BIT(CANx->MSR, MSR_INAK) &&
            !GET_BIT(CANx->MSR, MSR_SLAK))
            ;

        /* Set up timing parameters */
        CANx->BTR = ((CAN2_MODE << BTR_LBKM) |
                     (CAN2_RESYNC_JUMP_WIDTH << BTR_SJW_2BITS) |
                     (CAN2_TIME_SEGMENT_1 << BTR_TS1_4BITS) |
                     (CAN2_TIME_SEGMENT_2 << BTR_TS2_3BITS) |
                     (CAN2_BAUD_RATE_PRESCALER << BTR_BRP_10BITS));

        break;
    default:
        break;
    }
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
}
