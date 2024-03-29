/*******************************************************************************
 *
 * 	Module			: CAN BUS
 *
 * 	File Name		: CAN_interface.h
 *
 * 	Author			:
 *
 *	Date 			:
 *
 *	Version			: v1.0
 *
 *******************************************************************************/

#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../CURT_CAN_headers/CAN_private.h"

/*******************************************************************************
 *                           Type definitions                                  *
 *******************************************************************************/

/**
 * @enum
 * @brief The type of the identifier :
 * Standard  ===> 11 Bits,
 * Extended  ===> 29 Bits
 *
 */
typedef enum
{

  CAN_STANDARD_IDENTIFIER = 0,/**< CAN_STANDARD_IDENTIFIER */
  CAN_EXTENDED_IDENTIFIER = 1 /**< CAN_EXTENDED_IDENTIFIER */

} CAN_Identifier_TypeDef;

/**
 * @enum
 * @brief
 *
 */
typedef enum
{

  CAN_TX_MAILBOX_1,          /**< CAN_TX_MAILBOX_1 */

  CAN_TX_MAILBOX_2,          /**< CAN_TX_MAILBOX_2 */

  CAN_TX_MAILBOX_3,          /**< CAN_TX_MAILBOX_3 */

  CAN_TX_NO_EMPTY_MAILBOX = 4/**< CAN_TX_NO_EMPTY_MAILBOX */

} CAN_Tx_MailBox_TypeDef;

/**
 * @enum
 * @brief
 *
 */
typedef enum
{

  CAN_RX_FIFO_1,/**< CAN_RX_FIFO_1 */

  CAN_RX_FIFO_2,/**< CAN_RX_FIFO_2 */

} CAN_Rx_FIFO_TypeDef;

/**
 * @struct
 * @brief
 *
 */
typedef struct
{
  // Standard Identifier Value between 0 to 0x7FF.
  u32 StdId;

  // Extended Identifier Value between 0 to 0x1FFFFFFF.
  u32 ExtId;

  // Type of Identifier
  u8 IDE;

  // Remote Tansmission Request : Ask another node to send data
  u8 RTR;

  // Data Length Code from 0 --> 7 Bytes
  u8 DLC;

  // Array of Bytes that will be sent
  u8 Data[8];

} CanTxMsg;

/**
 * @struct
 * @brief
 *
 */
typedef struct
{
  // Standard Identifier Value between 0 to 0x7FF.
  u32 StdId;

  // Extended Identifier Value between 0 to 0x1FFFFFFF.
  u32 ExtId;

  // Type of Identifier
  u8 IDE;

  // Remote Tansmission Request : Ask another node to send data
  u8 RTR;

  // Data Length Code from 0 --> 7 Bytes
  u8 DLC;

  // Array of Bytes that will be sent
  u8 Data[8];

  // Filter Match index at the receiver
  u8 FMI;

} CanRxMsg;

/**
 * @struct
 * @brief
 *
 */
typedef struct
{
  u16 FilterIdHigh;
  u16 FilterIdLow;
  u16 FilterMaskIdHigh;
  u16 FilterMaskIdLow;
  u16 FilterFIFOAssignment;
  u8 FilterNumber;
  u8 FilterMode;
  u8 FilterScale;
  u8 FilterActivation;
} CAN_FilterInitTypeDef;

/**
 * @enum
 * @brief The available Configurations for initializations in CAN_config.h
 *
 */
typedef enum
{

  CAN_CONFIG_1,/**< CAN_CONFIG_1 */

  CAN_CONFIG_2 /**< CAN_CONFIG_2 */

} CAN_TypeDef_Config;

/*******************************************************************************
 *                       Public functions prototypes                           *
 *******************************************************************************/

/**
 * @fn void CAN_init(CAN_TypeDef*, CAN_TypeDef_Config)
 * @brief Initializes CAN using the configuration options set in
 * 		CAN_config.h.
 * 		- Sets up the following options in CAN:
 *		  	1. Automatic Bus off
 *		  	2. Automatic retransmission
 *		  	3. Automatic wake-up mode
 *		  	4. Time trigger communication mode
 *		  	5. Receive FIFO locked mode
 *		  	6. Transmit FIFO priority mode
 * 		- Sets up the following bit timing options in CAN:
 * 			1. CAN Mode (Loopback, Silent, or both)
 * 			2. Resync. jump width
 * 			3. Time segment 1
 * 			4. Time segment 2
 * 			5. Baud rate pre-scaler
 * 		Finally, the CAN state will change from **sleep** to **initialization** state.
 *
 * @param CANx				CAN instance to initialize
 * @param Copy_enuCANConfig CAN configuration to use while initializing
 */
void CAN_init(CAN_TypeDef *CANx, CAN_TypeDef_Config Copy_enuCANConfig);

// Yasmine
/**
 * @fn void CAN_initFilter(CAN_FilterInitTypeDef*)
 * @brief
 *
 * @param PTR_u8FilterNumber
 */
void CAN_initFilter(CAN_FilterInitTypeDef *PTR_u8FilterNumber);
/**
 * @fn void CAN_setSlaveStartBank(u8)
 * @brief
 *
 * @param Copy_u8CANBankNumber
 */
void CAN_setSlaveStartBank(u8 Copy_u8CANBankNumber);


// Yousery
/**
 * @fn CAN_Tx_MailBox_TypeDef CAN_transmit(CAN_TypeDef*, CanTxMsg*)
 * @brief
 *
 * @param CANx
 * @param TxMessage
 * @return
 */
CAN_Tx_MailBox_TypeDef CAN_transmit(CAN_TypeDef *CANx, CanTxMsg *TxMessage);

// Assem
/**
 * @fn void CAN_receive(CAN_TypeDef*, CAN_Rx_FIFO_TypeDef, CanRxMsg*)
 * @brief
 *
 * @param CANx
 * @param FIFONumber
 * @param RxMessage
 */
void CAN_receive(CAN_TypeDef *CANx, CAN_Rx_FIFO_TypeDef FIFONumber, CanRxMsg *RxMessage);

#endif
