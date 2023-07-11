#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

#include "../../CURT_GPIO/CURT_GPIO_headers/GPIO_interface.h"
#include "../../CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "../../LIB/STD_TYPES.h"
#define USART1_BASE_ADDRESS (0x40013800UL)
#define USART2_BASE_ADDRESS (0x40004400UL)
#define USART3_BASE_ADDRESS (0x40004800UL)
#define UART4_BASE_ADDRESS (0x40004C00UL)
#define UART5_BASE_ADDRESS (0x40005000UL)

typedef struct {
	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_GTPR;
} USART_Typedef;

#define USART1 ((volatile USART_Typedef *)USART1_BASE_ADDRESS)
#define USART2 ((volatile USART_Typedef *)USART2_BASE_ADDRESS)
#define USART3 ((volatile USART_Typedef *)USART3_BASE_ADDRESS)
#define UART4 ((volatile USART_Typedef *)UART4_BASE_ADDRESS)
#define UART5 ((volatile USART_Typedef *)UART5_BASE_ADDRESS)

#define USART1_PORT GPIO_PortA
#define USART1_CLK APB2
#define USART1_CK_PIN PIN8
#define USART1_TX_PIN PIN9
#define USART1_RX_PIN PIN10
#define USART1_CTS_PIN PIN11
#define USART1_RTS_PIN PIN12

#define USART2_PORT GPIO_PortA
#define USART2_CLK APB1
#define USART2_CK_PIN PIN4
#define USART2_TX_PIN PIN2
#define USART2_RX_PIN PIN3
#define USART2_CTS_PIN PIN0
#define USART2_RTS_PIN PIN1

#define USART3_PORT GPIO_PortB
#define USART3_CLK APB1
#define USART3_CK_PIN PIN12
#define USART3_TX_PIN PIN10
#define USART3_RX_PIN PIN11
#define USART3_CTS_PIN PIN13
#define USART3_RTS_PIN PIN14

#define USART_SR_TC (6UL)
#define USART_SR_RXNE (5UL)
#define USART_CR1_UE (13UL)
#define USART_CR1_PCE (10UL)
#define USART_CR1_TE (3UL)
#define USART_CR1_RE (2UL)
#define USART_CR1_PS (9UL)
#define USART_CR1_WORD_LENGTH (12UL)
#define USART_CR2_STOPBITS_LENGTH (12UL)
#define USART_CR2_CPOL (10UL)
#define USART_CR2_CPHA (9UL)

#endif
