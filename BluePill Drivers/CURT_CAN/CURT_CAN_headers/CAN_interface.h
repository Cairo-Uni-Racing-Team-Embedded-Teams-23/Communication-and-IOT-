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

#include "STD_TYPES.h"
#include "CAN_private.h"

/*

  The type of the identifier :
    Standard  ===> 11 Bits ,
    Extended  ===> 29 Bits

*/

typedef enum
{

  CAN_STANDARD_IDENTIFIER = 0,
  CAN_EXTENDED_IDENTIFIER = 1

} CAN_Identifier_TypeDef;

typedef enum
{

  CAN_TX_MAILBOX_1,

  CAN_TX_MAILBOX_2,

  CAN_TX_MAILBOX_3,

  CAN_TX_NO_EMPTY_MAILBOX = 4

} CAN_Tx_MailBox_TypeDef;

typedef enum
{

  CAN_RX_FIFO_1,

  CAN_RX_FIFO_2,

} CAN_Rx_FIFO_TypeDef;

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

/*

  The available Configurations for initializations in CAN_config.h
*/

typedef enum
{

  CAN_CONFIG_1,

  CAN_CONFIG_2

} CAN_TypeDef_Config;

// Hazem
void CAN_init(CAN_TypeDef *CANx, CAN_TypeDef_Config Copy_enuCANConfig);

// Yasmine
void CAN_initFilter(CAN_FilterInitTypeDef *PTR_u8FilterNumber);
void CAN_setSlaveStartBank(u8 Copy_u8CANBankNumber);

// Yousery
CAN_Tx_MailBox_TypeDef CAN_transmit(CAN_TypeDef *CANx, CanTxMsg *TxMessage);

// Assem
void CAN_receive(CAN_TypeDef *CANx, CAN_Rx_FIFO_TypeDef FIFONumber, CanRxMsg *RxMessage);

#endif
