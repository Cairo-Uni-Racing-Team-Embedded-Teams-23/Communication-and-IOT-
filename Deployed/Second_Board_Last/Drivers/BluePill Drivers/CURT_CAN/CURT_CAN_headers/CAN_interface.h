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
#include "../../../CMSIS/Device/ST/STM32F1xx/Include/stm32f103xb.h"

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
typedef enum {

	CAN_STANDARD_IDENTIFIER = 0, /**< CAN_STANDARD_IDENTIFIER */
	CAN_EXTENDED_IDENTIFIER = 1 /**< CAN_EXTENDED_IDENTIFIER */

} CAN_Identifier_TypeDef;

/**
 * @enum
 * @brief
 *
 */
typedef enum {
	CAN_Status_OK = 0, /**< CAN_Status_OK */
	CAN_Status_OverMaxLength = 1 << 0, /**< CAN_Status_OverMaxLength */
	CAN_Status_FullMailboxes = 1 << 1, /**< CAN_Status_FullMailboxes */
	CAN_Status_NullError = 1 << 2, /**< CAN_Status_NullError */
	CAN_Status_MaxDevicesReached = 1 << 3, /**< CAN_Status_MaxDevicesReached */
	CAN_Status_DeviceIDInvalid = 1 << 4, /**< CAN_Status_DeviceIDInvalid */
	CAN_Status_Error = 1 << 5, /**< CAN_Status_Error */
	CAN_Status_NoMessage = 1 << 6 /**< CAN_Status_NoMessage */
} CAN_Status_Typedef;

/**
 * @enum
 * @brief Defines the interrupt types available for CAN interface
 *
 */
typedef enum {
	CAN_Interrupt_Transmit, /**< CAN_Interrupt_Transmit */
	CAN_Interrupt_FIFO0, /**< CAN_Interrupt_FIFO0 */
	CAN_Interrupt_FIFO1, /**< CAN_Interrupt_FIFO1 */
	CAN_Interrupt_Status /**< CAN_Interrupt_Status */

} CAN_Interrupt_TypeDef;

/**
 * @enum
 * @brief Defines CAN operational modes
 *
 */
typedef enum {
	CAN_Mode_Normal, /**< CAN_Mode_Normal */
	CAN_Mode_Sleep, /**< CAN_Mode_Sleep */
	CAN_Mode_Init /**< CAN_Mode_Init */

} CAN_Mode;

/**
 * @enum
 * @brief
 *
 */
typedef enum {

	CAN_TX_MAILBOX_1, /**< CAN_TX_MAILBOX_1 */

	CAN_TX_MAILBOX_2, /**< CAN_TX_MAILBOX_2 */

	CAN_TX_MAILBOX_3, /**< CAN_TX_MAILBOX_3 */

	CAN_TX_NO_EMPTY_MAILBOX = 4 /**< CAN_TX_NO_EMPTY_MAILBOX */

} CAN_Tx_MailBox_TypeDef;

/**
 * @enum
 * @brief
 *
 */
typedef enum {

	CAN_RX_FIFO_1, /**< CAN_RX_FIFO_1 */

	CAN_RX_FIFO_2, /**< CAN_RX_FIFO_2 */

} CAN_Rx_FIFO_TypeDef;

/**
 * @struct
 * @brief
 *
 */
typedef struct {
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
typedef struct {
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
typedef struct {
	u16 FilterIdLowR1;
	u16 FilterIdHighR1;

	u16 FilterIdLowR2;
	u16 FilterIdHighR2;

	/* for mask mode */
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
typedef enum {

	CAN_CONFIG_1, /**< CAN_CONFIG_1 */

	CAN_CONFIG_2 /**< CAN_CONFIG_2 */

} CAN_TypeDef_Config;

/*CAN filter configuration */
/**
 * @enum
 * @brief
 *
 */
typedef enum {
	MASK, /**< MASK */
	LIST /**< LIST */
} CAN_FilterMode;

/**
 * @enum
 * @brief
 *
 */
typedef enum {
	DOUBLE_16, /**< DOUBLE_16 */
	SINGLE_32 /**< SINGLE_32 */
} CAN_FilterScale;

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

/**
 * @fn void CAN_setMode(CAN_TypeDef*, CAN_Mode)
 * @brief   Sets the mode for the given CAN interface.
 * @note    Busy-waits until the mode is set
 *
 * @param CANx    CAN instance
 * @param a_mode  Mode to set the CAN
 */
void CAN_setMode(CAN_TypeDef *CANx, CAN_Mode a_mode);

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
void CAN_receive(CAN_TypeDef *CANx, CAN_Rx_FIFO_TypeDef FIFONumber,
		CanRxMsg *RxMessage);

/* High level CAN wrapper functions */

/**
 * @fn u32 CAN_formatIdentifierIntoFRx(u32, u32, CAN_Identifier_TypeDef, CAN_FilterScale, u8)
 * @brief
 *
 * @param a_STDID   Standard identifier 11 bits
 * @param a_EXTID   Extended identifier 18 bits
 * @param a_idType  Identifier type passed, whether standard or extended
 * @param a_scale   Scale to format the identifiers as, single 32 bit or double 16 bit
 * @param a_RTR     a_RTR bit: Decides to filter a_RTR frames or not
 * @return        FRx value aligned correectly to be set in the register directly
 */
u32 CAN_formatIdentifierIntoFRx(u32 a_STDID, u32 a_EXTID,
		CAN_Identifier_TypeDef a_idType, CAN_FilterScale a_scale, u8 a_RTR);

/**
 * @fn CAN_Status_Typedef CAN_appendDeviceToBus(u32, CAN_Identifier_TypeDef)
 * @brief
 *
 * @param a_devID   Device Identifier (11 bits a_STDID (MSb)   + 18 bits a_EXTID (LSb))
 * @param a_idType  Identifier type
 * @note  Identifiers are masked according to the type to be no greater than 11 or 29 bits.
 * @return  @see CAN_Status_MaxDevicesReached if there are not available slots
 * @return  @see CAN_Status_OK Device ID appended to filters correctly
 */
CAN_Status_Typedef CAN_appendDeviceToBus(u32 a_devID,
		CAN_Identifier_TypeDef a_idType);

/**
 * @fn CAN_Status_Typedef CAN_removeDeviceFromBus(u32, CAN_Identifier_TypeDef)
 * @brief   Removes the given ID from the filter.
 * @note    Must provide the same identifier type that the ID was appended with, otherwise the
 *        ID will not be removed.
 * @param a_devID   Device ID to remove
 *      Ex. STID = 0x1FC -> a_devID = 0x1FC
 *      Ex. STID = 0x1FC, a_EXTID = 0xA39 -> a_devID = (0x1FC<<11)| (0xA39)
 * @param a_idType  Identifier type
 * @return  @see CAN_Status_DeviceIDInvalid if the ID is not present in the filters
 * @return  @see CAN_Status_OK Device ID removed from filters successfully
 */
CAN_Status_Typedef CAN_removeDeviceFromBus(u32 a_devID,
		CAN_Identifier_TypeDef a_idType);

/**
 * @fn CAN_Status_Typedef CAN_sendMessage_Interrupt(const u8*, u8, CAN_Identifier_TypeDef, u32)
 * @brief   Sends a CAN frame containing a_data of length a_len bytes to the specified ID as soon
 *      as a transmit mailbox is empty. (Does not send immediately.)
 *
 * @param a_data  Array which contains the data, minimum size MUST be a_len
 * @param a_len   Number of bytes to send from a_data array.
 * @param a_idType  Identifier type
 * @param a_devID Device ID
 * @return  @see CAN_Status_NullError     a_data was null pointer
 * @return  @see CAN_Status_OverMaxLength a_len was greater than 8
 * @return  @see CAN_Status_OK            Success
 */
CAN_Status_Typedef CAN_sendMessage_Interrupt(const u8 *a_data, u8 a_len,
		CAN_Identifier_TypeDef a_idType, u32 a_devID);

/**
 * @fn CAN_Status_Typedef CAN_receiveMessage_Interrupt(u8*, u8*, u32*)
 * @brief Receives a CAN frame into a_data, received bytes length is stored into a_len,
 *      and identifier into a_devID as soon as a message is received into one of the FIFO's
 *      (Does not receive immediately.)
 *
 * @param a_data Array which will contain the data, minimum size MUST be a_len
 * @param a_len  Number of bytes received into a_data array.
 * @param a_devID Frame identifier.
 * @return  @see CAN_Status_NullError     a_data was null pointer
 * @return  @see CAN_Status_OK            Success
 */
CAN_Status_Typedef CAN_receiveMessage_Interrupt(u8 **a_data, u8 *a_len,
		u32 *a_devID);

/**
 * @fn CAN_Status_Typedef CAN_sendMessage(const u8*, u8, CAN_Identifier_TypeDef, u32)
 * @brief   Sends a CAN frame containing a_data of length a_len bytes to the specified ID.
 *
 * @param a_data  Array which contains the data, minimum size MUST be a_len
 * @param a_len   Number of bytes to send from a_data array.
 * @param a_idType  Identifier type
 * @param a_devID Device ID
 * @return  @see CAN_Status_NullError     a_data was null pointer
 * @return  @see CAN_Status_OverMaxLength a_len was greater than 8
 * @return  @see CAN_Status_FullMailboxes No mailbox available in CAN to transmit from
 * @return  @see CAN_Status_OK            Success
 */
CAN_Status_Typedef CAN_sendMessage(const u8 *a_data, u8 a_len,
		CAN_Identifier_TypeDef a_idType, u32 a_devID);

/**
 * @fn CAN_Status_Typedef CAN_receiveMessage(u8*, u8*, u32)
 * @brief   Receives a CAN frame into a_data, received bytes length is stored into a_len,
 *      and identifier into a_devID if there is a pending message in a mailbox.
 *
 * @param a_data Array which will contain the data, minimum size MUST be a_len
 * @param a_len  Number of bytes received into a_data array.
 * @param a_devID Frame identifier
 * @return  @see CAN_Status_NullError     a_data was null pointer
 * @return  @see CAN_Status_Error         No pending messages to receive
 * @return  @see CAN_Status_OK            Success
 */
CAN_Status_Typedef CAN_receiveMessage(u8 *a_data, u8 *a_len, u32 *a_devID);

/**
 * @fn CAN_Status_Typedef CAN_attachCallback(CAN_Interrupt_TypeDef, void(*)())
 * @brief   Attaches a callback function to the given interrupt. Should be used before
 *      calling CAN_receiveMessage_Interrupt or CAN_sendMessage_Interrupt.
 *
 * @param a_interruptType   Interrupt type to attach the function to.
 * @param a_callbackPtr     Function pointer for the callback
 * @return @see CAN_Status_Error   Interrupt type given is invalid
 * @return @see CAN_Status_OK      Success
 */
CAN_Status_Typedef CAN_attachCallback(CAN_Interrupt_TypeDef a_interruptType,
		void (*a_callbackPtr)());

/**
 * @fn CAN_Status_Typedef CAN_detachCallback(CAN_Interrupt_TypeDef)
 * @brief   Detaches a callback from the interrupt time given.
 * @note    This disables the NVIC IRQ for the given interrupt as well
 *
 * @param a_interruptType   Interrupt type to detach.
 * @return @see CAN_Status_Error   Interrupt type given is invalid
 * @return @see CAN_Status_OK      Success
 */
CAN_Status_Typedef CAN_detachCallback(CAN_Interrupt_TypeDef a_interruptType);

/**
 * @fn CAN_Status_Typedef CAN_activateInterrupt(CAN_TypeDef CANx, CAN_Interrupt_TypeDef)
 * @brief Activates the interrupt notification for the specified type.
 *
 * @param CANx
 * @param a_interruptType
 * @return
 */
CAN_Status_Typedef CAN_activateInterrupt(CAN_TypeDef* CANx,
		CAN_Interrupt_TypeDef a_interruptType);

/**
 * @fn CAN_Status_Typedef CAN_deactivateInterrupt(CAN_Interrupt_TypeDef)
 * @brief De-activates the interrupt notification for the specified type.
 *
 * @param CANx
 * @param a_interruptType
 * @return
 */
CAN_Status_Typedef CAN_deactivateInterrupt(CAN_TypeDef* CANx,
		CAN_Interrupt_TypeDef a_interruptType);

/* Interrupt handlers */

/**
 * @fn void USB_HP_CAN_TX_IRQHandler(void)
 * @brief   Interrupt handler for transmit event on CAN
 * @note    Called when a transmit mailbox is empty.
 *
 */
void USB_HP_CAN_TX_IRQHandler(void);

/**
 * @fn void USB_LP_CAN_RX0_IRQHandler(void)
 * @brief   Interrupt handler for reception event on CAN
 * @note    Called when FIFO0 contains a new message
 *
 */
void USB_LP_CAN_RX0_IRQHandler(void);

/**
 * @fn void CAN_RX1_IRQHandler(void)
 * @brief   Interrupt handler for reception event on CAN
 * @note    Called when FIFO1 contains a new message *
 */
void CAN_RX1_IRQHandler(void);

/**
 * @fn void CAN_SCE_IRQHandler(void)
 * @brief   Interrupt handler for status change event on CAN
 * @note    Called when CAN status changes (errors, mode change, etc...)
 */
void CAN_SCE_IRQHandler(void);

#endif
