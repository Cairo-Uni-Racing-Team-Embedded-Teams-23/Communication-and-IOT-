/*******************************************************************************
 *
 * 	Module			: CAN BUS
 *
 * 	File Name		: CAN_private.h
 *
 * 	Author			:
 *
 *	Date 			:
 *
 *	Version			: v1.0
 *
 *******************************************************************************/
#ifndef CAN_PRIVATE_H
#define CAN_PRIVATE_H

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../CURT_CAN_headers/CAN_interface.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define CAN1_BASE_ADDRESS (0x40006400)
#define CAN2_BASE_ADDRESS (0x40006800)
#define CAN_MAX_DEVICES_COUNT (28U)
/**
 * @struct
 * @brief
 *
 */
typedef struct
{
    volatile u32 TIR;
    volatile u32 TDTR;
    volatile u32 TDLR;
    volatile u32 TDHR;
} CAN_TxMailBox_TypeDef;

/**
 * @struct
 * @brief
 *
 */
typedef struct
{
    volatile u32 RIR;
    volatile u32 RDTR;
    volatile u32 RDLR;
    volatile u32 RDHR;
} CAN_FIFOMailBox_TypeDef;

/**
 * @struct
 * @brief
 *
 */
typedef struct
{
    volatile u32 FR1;
    volatile u32 FR2;
} CAN_FilterRegister_TypeDef;

/**
 * @struct
 * @brief
 *
 */
typedef struct
{
    volatile u32 MCR;
    volatile u32 MSR;
    volatile u32 TSR;
    volatile u32 RF0R;
    volatile u32 RF1R;
    volatile u32 IER;
    volatile u32 ESR;
    volatile u32 BTR;
    u32 RESERVED0[88];
    CAN_TxMailBox_TypeDef sTxMailBox[3];
    CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
    u32 RESERVED1[12];
    volatile u32 FMR;
    volatile u32 FM1R;
    u32 RESERVED2;
    volatile u32 FS1R;
    u32 RESERVED3;
    volatile u32 FFA1R;
    u32 RESERVED4;
    volatile u32 FA1R;
    u32 RESERVED5[8];
    CAN_FilterRegister_TypeDef sFilterRegister[28];

} CAN_TypeDef;

#define CAN1 ((CAN_TypeDef *)(CAN1_BASE_ADDRESS))
#define CAN2 ((CAN_TypeDef *)(CAN2_BASE_ADDRESS))

/**
 * @brief Macro used to assert that the passed pointer is an actual
 *      CAN instance. Used to avoid incorrect memory accessing.
 *
 *      0 -> Not a CAN typedef instance
 *      1 -> Is a CAN typedef instance
 */
#define IS_CAN_INSTANCE(CANx) ((CANx == CAN1) || (CANx == CAN2))

/*******************************************************************************
 *                              Bit Definitions                                *
 *******************************************************************************/

// CAN Master Control Register (MCR) Important Bits
#define MCR_INRQ 0
// Sleep Mode Request
#define MCR_SLEEP 1
// Transmit FIFO Priority
#define MCR_TXFP 2
// Receive FIFO Locked Mode
#define MCR_RFLM 3
// No Automatic Retransmission
#define MCR_NART 4
// Automatic Wake Up Mode
#define MCR_AWUM 5
// Automatic Bus Off Transmission
#define MCR_ABOT 6
// Time Triggered Communication Mode
#define MCR_TTCM 7
// Software master reset, CAN returns to sleep mode
#define MCR_RESET 15
/* CAN master control register bits definition */
/* CAN filter master register bits definition */
typedef enum
{
    FINIT = 0,
    CAN2SB = 8,
} CAN_FMR;

/* CAN master control register bits definition */
typedef enum
{
    INRQ,
    SLEEP,
    TXFP,
    RFLM,
    NART,
    AWUM,
    ABOM,
    TTCM,
    RESET = 15,
    DBF
} CAN_MCR;

//*****************************************************

// CAN Master Status Register (MSR) Important Bits

// Initialization Ack
#define MSR_INAK 0
// Sleep Mode Ack
#define MSR_SLAK 1
// Error interrupt
#define MSR_ERRI 2
// Wake Up interrupt
#define MSR_WKUI 3

// Sleep Mode Interrupt
#define MSR_SLAKI 4

// Current mode detection bits
// Transmit Mode
#define MSR_TXM 8

// Receive Mode
#define MSR_RXM 9
//**********************

// Last sample Point
#define MSR_SAMP 10
// Current value at the RX pin
#define MSR_RX 11

//*****************************************************

// CAN Bit Timing Register  (BTR)

// Silent Mode for Debugging
#define BTR_SILM 31
// Loop Back Mode for Debugging
#define BTR_LBKM 30
// Resync Jump Width
#define BTR_SJW_2BITS 24
// Time Segment 2
#define BTR_TS2_3BITS 20
// Time Segment 1
#define BTR_TS1_4BITS 16
// Baud Rate Prescaler
#define BTR_BRP_10BITS 0

//	CAN Transmit Status Register (TSR)

// Transmission MailBox 0 is empty
#define TSR_TME0 26
// Transmission MailBox 1 is empty
#define TSR_TME1 27
// Transmission MailBox 2 is empty
#define TSR_TME2 28

// CAN TX mailbox Identifier  Register (TIR)

// Transmission Request
#define TIR_TXRQ 0
// Remote Transmission Request
#define TIR_RTR 1
// Identifier Extensions
#define TIR_IDE 2
// Identifier Extension
#define TIR_EXID_17BITS 3
// Standard Identifier
#define TIR_STID_11BITS 21

// CAN Transmitter Data Length and time stamp Register (TDTR)

// Data Length Code Takes values from 0 - 8 Bytes
#define TDTR_DLC_4BITS 0
// Transmit Global Time
#define TDTR_TGT 8
// Message Time Stamp
#define TDTR_TIME_16BITS 16

// CAN RX FIFO Identifier  Register (RIXR) x = {0 , 1} as we have 2 Receive FIFOS

// Remote Transmission Request
#define RIR_RTR 1
// Identifier Extensions
#define RIR_IDE 2
// Identifier Extension
#define RIR_EXID_17BITS 3
// Standard Identifier
#define RIR_STID_11BITS 21

// CAN Receiver Data Length and time stamp Register (RDTR)

// Data Length Code Takes values from 0 - 8 Bytes
#define RDTR_DLC_4BITS 0
// Transmit Global Time
#define RDTR_FMI_8BITS 8
// Message Time Stamp
#define RDTR_TIME_16BITS 16

// CAN Receiver FIFO Release
#define RFR_RFOM 5
#define RFR_FMP 0

// CAN Filter Bank
// Filter Init
#define FMR_FINIT 0

// CAN interrupt enable
// Transmit mailbox empty interrupt enable
#define IER_TMEIE (0U)
// FIFO message pending interrupt enable
#define IER_FMPIE0 (1U)
//  FIFO full interrupt enable
#define IER_FFIE0 (2U)
// FIFO overrun interrupt enable
#define IER_FOVIE0 (3U)
// FIFO message pending interrupt enable
#define IER_FMPIE1 (4U)
// FIFO full interrupt enable
#define IER_FFIE1 (5U)
// FIFO overrun interrupt enable
#define IER_FOVIE1 (6U)
// Error warning interrupt enable
#define IER_EWGIE (8U)
// Error passive interrupt enable
#define IER_EPVIE (9U)
// Bus-off interrupt enable
#define IER_BOFIE (10U)
// Last error code interrupt enable
#define IER_LECIE (11U)
// Error interrupt enable
#define IER_ERRIE (15U)
// Wakeup interrupt enable
#define IER_WKUIE (16U)
// Sleep interrupt enable
#define IER_SLKIE (17U)

#endif
