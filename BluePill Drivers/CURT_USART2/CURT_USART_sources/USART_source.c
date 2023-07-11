#include "../../CURT_GPIO/CURT_GPIO_headers/GPIO_interface.h"
#include "../../CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "../../LIB/BIT_MATH.h"
#include "../CURT_USART_headers/USART_config.h"
#include "../CURT_USART_headers/USART_interface.h"
#include "../CURT_USART_headers/USART_private.h"

static void USART_initPins(USART_Typedef *a_usart) {
  if (a_usart == USART1) {
    RCC_voidEnableClock(USART1_CLK, RCC_APB2_USART1EN);
    GPIO_enablePortClock(USART1_PORT);
    GPIO_setupPinMode(USART1_PORT, USART1_CK_PIN, OUTPUT_SPEED_50MHZ_AFPP);
    GPIO_setupPinMode(USART1_PORT, USART1_TX_PIN, OUTPUT_SPEED_50MHZ_AFPP);
    GPIO_setupPinMode(USART1_PORT, USART1_RX_PIN, OUTPUT_SPEED_50MHZ_AFPP);
    GPIO_setupPinMode(USART1_PORT, USART1_RTS_PIN, OUTPUT_SPEED_50MHZ_AFPP);
    GPIO_setupPinMode(USART1_PORT, USART1_CTS_PIN, OUTPUT_SPEED_50MHZ_AFPP);
  } else if (a_usart == USART2) {

    RCC_voidEnableClock(USART2_CLK, RCC_APB1_USART2EN);
    GPIO_enablePortClock(USART2_PORT);
    GPIO_setupPinMode(USART2_PORT, USART2_CK_PIN, OUTPUT_SPEED_50MHZ_AFPP);
    GPIO_setupPinMode(USART2_PORT, USART2_TX_PIN, OUTPUT_SPEED_2MHZ_AFPP);
    GPIO_setupPinMode(USART2_PORT, USART2_RX_PIN, OUTPUT_SPEED_50MHZ_AFPP);
    GPIO_setupPinMode(USART2_PORT, USART2_RTS_PIN, OUTPUT_SPEED_50MHZ_AFPP);
    GPIO_setupPinMode(USART2_PORT, USART2_CTS_PIN, OUTPUT_SPEED_50MHZ_AFPP);
  } else if (a_usart == USART3) {

    RCC_voidEnableClock(USART3_CLK, RCC_APB1_USART3EN);
    GPIO_enablePortClock(USART3_PORT);
    GPIO_setupPinMode(USART3_PORT, USART3_CK_PIN, OUTPUT_SPEED_50MHZ_AFPP);
    GPIO_setupPinMode(USART3_PORT, USART3_TX_PIN, OUTPUT_SPEED_50MHZ_AFPP);
    GPIO_setupPinMode(USART3_PORT, USART3_RX_PIN, OUTPUT_SPEED_50MHZ_AFPP);
    GPIO_setupPinMode(USART3_PORT, USART3_RTS_PIN, OUTPUT_SPEED_50MHZ_AFPP);
    GPIO_setupPinMode(USART3_PORT, USART3_CTS_PIN, OUTPUT_SPEED_50MHZ_AFPP);
  } else {
    return;
  }
}

USART_Status_Typedef USART_init(USART_Typedef *a_usart,
                                USART_Config_Typedef *a_config) {
  if (a_usart == NULLPTR || a_config == NULLPTR) {
    return USART_ERROR;
  }
  USART_Status_Typedef status = USART_OK;
  USART_initPins(a_usart);
  /* Calculate the baud rate */
  u32 l_USART_Fraction = (F_CPU) / (16UL * (a_config->baud_rate));
  u32 l_USART_Mantissa =
      ((((F_CPU * 100UL) / (16UL * (a_config->baud_rate))) * 100UL) % 100UL) *
      16UL;
  a_usart->USART_BRR = (l_USART_Fraction / 100UL) || (l_USART_Mantissa << 4UL);
  a_usart->USART_SR = 0;

  /* Set the UE bit in USART register to enable UART*/
  SET_BIT(a_usart->USART_CR1, USART_CR1_UE);
  WRITE_BIT(a_usart->USART_CR1, USART_CR1_TE, 1);
  WRITE_BIT(a_usart->USART_CR1, USART_CR1_RE, 1);

  /* Set the word length: 8 or 9 bits */
  WRITE_BIT(a_usart->USART_CR1, USART_CR1_WORD_LENGTH, a_config->word_length);

  /* Set the stopbits length */
  WRITE_BIT(a_usart->USART_CR2, USART_CR2_STOPBITS_LENGTH, a_config->stop_bits);

  /* Set CPHA and CPOL */
  WRITE_BIT(a_usart->USART_CR2, USART_CR2_CPOL, a_config->cpol);
  WRITE_BIT(a_usart->USART_CR2, USART_CR2_CPHA, a_config->cpha);

  /* Set parity control enable if parity is enabled */
  if (a_config->parity == USART_PARITY_NONE) {
    WRITE_BIT(a_usart->USART_CR1, USART_CR1_PCE, 0UL);
  } else {
    WRITE_BIT(a_usart->USART_CR1, USART_CR1_PCE, 1UL);
    WRITE_BIT(a_usart->USART_CR1, USART_CR1_PS, a_config->parity);
  }

  return status;
}

USART_Status_Typedef USART_sendChar(USART_Typedef *a_usart, u16 a_data) {
  a_usart->USART_CR1 |= (1 << USART_CR1_TE);
  a_usart->USART_DR = (a_data & 0x1FFU);
  while (!CHK_BIT(a_usart->USART_SR, USART_SR_TC))
    ;
  CLR_BIT(a_usart->USART_SR, USART_SR_TC);
  return USART_OK;
}
USART_Status_Typedef USART_sendString(USART_Typedef *a_usart, u16 a_data[],
                                      u16 size) {
  USART_Status_Typedef l_status = USART_OK;
  for (u16 idx = 0; idx < size && l_status == USART_OK; idx++) {
    l_status = USART_sendChar(a_usart, a_data[idx]);
  }
  return l_status;
}
u16 USART_receiveChar(USART_Typedef *a_usart) {

  while (!CHK_BIT(a_usart->USART_SR, USART_SR_RXNE))
    ;
  return (a_usart->USART_DR & 0x1FFU);
}

void USART_receiveString(USART_Typedef *a_usart, u16 a_data[], u16 size) {
  for (u16 idx = 0; idx < size; idx++) {
    a_data[idx] = USART_receiveChar(a_usart);
  }
}

void USART_enableInterrupt(USART_Interrupt_Typedef a_interrupt) {

//  switch (a_interrupt) {
//  case USART_Interrupt_TC:
//  case USART_Interrupt_TXE:
//  case USART_Interrupt_FE:
//  case USART_Interrupt_PE:
//  case USART_Interrupt_ORE:
//  case USART_Interrupt_RXNE:
//  case USART_Interrupt_CTS:
//  case USART_Interrupt_LBD:
//  case USART_Interrupt_IDLE:
//  }
}
