/**
 * @file USART_interface.h
 * @author Hazem Montasser (h4z3m.private@gmail.com)
 * @brief Interface file for the USART driver
 * @version 0.1
 * @date 2023-07-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "./USART_private.h"

/*******************************************************************************
 *                              Type definitions                               *
 *******************************************************************************/

/**
 * @enum  USART_Status_Typedef
 * @brief USART status enum
 *
 */
typedef enum
{
  USART_OK,   /**< USART_OK */
  USART_ERROR /**< USART_ERROR */
} USART_Status_Typedef;

/**
 * @enum
 * @brief Parity type
 *
 */
typedef enum
{
  USART_PARITY_NONE = 0, /**< USART_PARITY_NONE */
  USART_PARITY_EVEN = 1, /**< USART_PARITY_EVEN */
  USART_PARITY_ODD = 2   /**< USART_PARITY_ODD */
} USART_Parity_Typedef;

/**
 * @enum
 * @brief Number of stop bits
 *
 */
typedef enum
{
  USART_STOPBITS_1 = 0b00,   /**< USART_STOPBITS_1 */
  USART_STOPBITS_0_5 = 0b01, /**< USART_STOPBITS_0_5 */
  USART_STOPBITS_2 = 0b10,   /**< USART_STOPBITS_2 */
  USART_STOPBITS_1_5 = 0b11, /**< USART_STOPBITS_1_5 */
} USART_StopBits_Typedef;

/**
 * @enum
 * @brief USART word length
 *
 */
typedef enum
{
  USART_WORDLENGTH_8BIT = 0, /**< USART_WORDLENGTH_8BIT */
  USART_WORDLENGTH_9BIT = 1  /**< USART_WORDLENGTH_9BIT */
} USART_WordLength_Typedef;

/**
 * @enum
 * @brief USART CPOL
 *
 */
typedef enum
{
  USART_CPOL_LOW, /**< USART_CPOL_LOW */
  USART_CPOL_HIGH /**< USART_CPOL_HIGH */
} USART_CPOL_Typedef;

/**
 * @enum
 * @brief USART CPHA
 *
 */
typedef enum
{
  USART_CPHA_FIRST, /**< USART_CPHA_FIRST */
  USART_CPHA_SECOND /**< USART_CPHA_SECOND */
} USART_CPHA_Typedef;

/**
 * @enum
 * @brief USART Interrupt types
 */
typedef enum
{
  USART_Interrupt_TXE,  /**< USART_Interrupt_TXE */
  USART_Interrupt_CTS,  /**< USART_Interrupt_CTS */
  USART_Interrupt_TC,   /**< USART_Interrupt_TC */
  USART_Interrupt_RXNE, /**< USART_Interrupt_RXNE */
  USART_Interrupt_ORE,  /**< USART_Interrupt_ORE */
  USART_Interrupt_IDLE, /**< USART_Interrupt_IDLE */
  USART_Interrupt_PE,   /**< USART_Interrupt_PE */
  USART_Interrupt_FE,   /**< USART_Interrupt_FE */
  USART_Interrupt_LBD,  /**< USART_Interrupt_LBD */
} USART_Interrupt_Typedef;

/**
 * @struct
 * @brief USART configuration struct
 */
typedef struct
{
  u32 baud_rate;
  u32 prescaler;
  USART_Parity_Typedef parity;
  USART_StopBits_Typedef stop_bits;
  USART_WordLength_Typedef word_length;
  USART_CPHA_Typedef cpha;
  USART_CPOL_Typedef cpol;
} USART_Config_Typedef;

/*******************************************************************************
 *                         Public functions prototypes                         *
 *******************************************************************************/

/**
 * @brief Initializes the USART according to the configuration and initializes clocks and GPIO
 *  pins
 *
 * @param a_usart USART interface on which to perform the operation
 * @param a_config
 * @return
 */
USART_Status_Typedef USART_init(USART_Typedef *a_usart,
                                USART_Config_Typedef *a_config);

/**
 * @brief Sends a single character over USART
 *
 * @param a_usart USART interface on which to perform the operation
 * @param a_data Data buffer
 * @return
 */
USART_Status_Typedef USART_sendChar(USART_Typedef *a_usart, u16 a_data);

/**
 * @brief Sends a string over USART
 *
 * @param a_usart USART interface on which to perform the operation
 * @param a_data Data buffer
 * @param size Size of the data buffer
 * @return
 */
USART_Status_Typedef USART_sendString(USART_Typedef *a_usart, u16 a_data[],
                                      u16 size);

/**
 * @brief Receives a single character over USART
 *
 * @param a_usart USART interface on which to perform the operation
 * @return
 */
u16 USART_receiveChar(USART_Typedef *a_usart);

/**
 * @brief Receives a string over USART using interrupt
 *
 * @param a_usart USART interface on which to perform the operation
 * @param a_data Data buffer
 * @param size Size of the data buffer
 * @return
 */
void USART_receiveString_Interrupt(USART_Typedef *a_usart, u16 a_data[], u16 size);

/**
 * @brief Receives a string over USART
 *
 * @param a_usart USART interface on which to perform the operation
 * @param a_data Data buffer
 * @param size Size of the data buffer
 */
void USART_receiveString(USART_Typedef *a_usart, u16 a_data[], u16 size);

/**
 * @brief Enables the given interrupt
 *
 * @param a_interrupt Interrupt type
 */
USART_Status_Typedef USART_enableInterrupt(USART_Typedef *a_usart, USART_Interrupt_Typedef a_interrupt);

/**
 * @brief Disables the given interrupt
 *
 * @param a_interrupt Interrupt type
 */
USART_Status_Typedef USART_disableInterrupt(USART_Typedef *a_usart, USART_Interrupt_Typedef a_interrupt);

#endif
