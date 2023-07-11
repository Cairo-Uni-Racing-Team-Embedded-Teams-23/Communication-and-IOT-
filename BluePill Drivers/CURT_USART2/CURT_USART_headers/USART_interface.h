/**
 * @file
 * @brief
 */

#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H
#include "../../LIB/STD_TYPES.h"
#include "./USART_private.h"

typedef enum { USART_OK, USART_ERROR } USART_Status_Typedef;
typedef enum {
  USART_PARITY_NONE = 0,
  USART_PARITY_EVEN = 1,
  USART_PARITY_ODD = 2
} USART_Parity_Typedef;

typedef enum {
  USART_STOPBITS_1 = 0b00,
  USART_STOPBITS_0_5 = 0b01,
  USART_STOPBITS_2 = 0b10,
  USART_STOPBITS_1_5 = 0b11,
} USART_StopBits_Typedef;

typedef enum {
  USART_WORDLENGTH_8BIT = 0,
  USART_WORDLENGTH_9BIT = 1
} USART_WordLength_Typedef;

typedef enum { USART_CPOL_LOW, USART_CPOL_HIGH } USART_CPOL_Typedef;

typedef enum { USART_CPHA_FIRST, USART_CPHA_SECOND } USART_CPHA_Typedef;

typedef enum {
  USART_Interrupt_TXE,
  USART_Interrupt_CTS,
  USART_Interrupt_TC,
  USART_Interrupt_RXNE,
  USART_Interrupt_ORE,
  USART_Interrupt_IDLE,
  USART_Interrupt_PE,
  USART_Interrupt_LBD,
} USART_Interrupt_Typedef;

typedef struct {
  u32 baud_rate;
  u32 prescaler;
  USART_Parity_Typedef parity;
  USART_StopBits_Typedef stop_bits;
  USART_WordLength_Typedef word_length;
  USART_CPHA_Typedef cpha;
  USART_CPOL_Typedef cpol;

} USART_Config_Typedef;
/**
 * @brief
 *
 * @param a_usart
 * @param a_config
 * @return
 */
USART_Status_Typedef USART_init(USART_Typedef *a_usart,
                                USART_Config_Typedef *a_config);

/**
 * @brief
 *
 * @param a_usart
 * @param a_data
 * @return
 */
USART_Status_Typedef USART_sendChar(USART_Typedef *a_usart, u16 a_data);

/**
 * @brief
 *
 * @param a_usart
 * @param a_data
 * @param size
 * @return
 */
USART_Status_Typedef USART_sendString(USART_Typedef *a_usart, u16 a_data[],
                                      u16 size);

/**
 * @brief
 *
 * @param a_usart
 * @return
 */
u16 USART_receiveChar(USART_Typedef *a_usart);

/**
 * @brief
 *
 * @param a_usart
 * @param a_data
 * @param size
 */
void USART_receiveString(USART_Typedef *a_usart, u16 a_data[], u16 size);

/**
 * @brief
 *
 * @param a_interrupt
 */
void USART_enableInterrupt(USART_Interrupt_Typedef a_interrupt);

/**
 * @brief
 *
 * @param a_interrupt
 */
void USART_disableInterrupt(USART_Interrupt_Typedef a_interrupt);

#endif
