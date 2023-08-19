/**
 * @file USART_source.c
 * @author Hazem Montasser (h4z3m.private@gmail.com)
 * @brief Source file for the USART driver
 * @version 0.1
 * @date 2023-07-26
 *
 * @copyright Copyright (c) 2023
 *
 */

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../CURT_GPIO/CURT_GPIO_headers/GPIO_interface.h"
#include "../../CURT_NVIC/CURT_NVIC_headers/NVIC_interface.h"
#include "../../CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "../../LIB/BIT_MATH.h"
#include "../CURT_USART_headers/USART_config.h"
#include "../CURT_USART_headers/USART_interface.h"
#include "../CURT_USART_headers/USART_private.h"
/*******************************************************************************
 *                         Private global variables                            *
 *******************************************************************************/

static u8 **usart_tx_data = NULLPTR;
static u16 usart_tx_data_len = 0;

static void (*usart1_rxne_callback)(u8) = NULLPTR;
static void (*usart2_rxne_callback)(u8) = NULLPTR;
static void (*usart3_rxne_callback)(u8) = NULLPTR;

/*******************************************************************************
 *                         Private Functions                                   *
 *******************************************************************************/

static void USART_initPins(USART_Typedef *a_usart)
{
	if (a_usart == USART1)
	{
		RCC_voidEnableClock(USART1_CLK, RCC_APB2_USART1EN);
		GPIO_enablePortClock(USART1_PORT);
		GPIO_setupPinMode(USART1_PORT, USART1_CK_PIN, OUTPUT_SPEED_50MHZ_AFPP);
		GPIO_setupPinMode(USART1_PORT, USART1_TX_PIN, OUTPUT_SPEED_50MHZ_AFPP);
		GPIO_setupPinMode(USART1_PORT, USART1_RX_PIN, INPUT_FLOATING);
		GPIO_setupPinMode(USART1_PORT, USART1_RTS_PIN, INPUT_FLOATING);
		GPIO_setupPinMode(USART1_PORT, USART1_CTS_PIN, OUTPUT_SPEED_50MHZ_AFPP);
	}
	else if (a_usart == USART2)
	{
		RCC_voidEnableClock(USART2_CLK, RCC_APB1_USART2EN);
		GPIO_enablePortClock(USART2_PORT);
		GPIO_setupPinMode(USART2_PORT, USART2_CK_PIN, OUTPUT_SPEED_50MHZ_AFPP);
		GPIO_setupPinMode(USART2_PORT, USART2_TX_PIN, OUTPUT_SPEED_50MHZ_AFPP);
		GPIO_setupPinMode(USART2_PORT, USART2_RX_PIN, INPUT_FLOATING);
		GPIO_setupPinMode(USART2_PORT, USART2_RTS_PIN, INPUT_FLOATING);
		GPIO_setupPinMode(USART2_PORT, USART2_CTS_PIN, OUTPUT_SPEED_50MHZ_AFPP);
	}
	else if (a_usart == USART3)
	{
		RCC_voidEnableClock(USART3_CLK, RCC_APB1_USART3EN);
		GPIO_enablePortClock(USART3_PORT);
		GPIO_setupPinMode(USART3_PORT, USART3_CK_PIN, OUTPUT_SPEED_50MHZ_AFPP);
		GPIO_setupPinMode(USART3_PORT, USART3_TX_PIN, OUTPUT_SPEED_50MHZ_AFPP);
		GPIO_setupPinMode(USART3_PORT, USART3_RX_PIN, INPUT_FLOATING);
		GPIO_setupPinMode(USART3_PORT, USART3_RTS_PIN, INPUT_FLOATING);
		GPIO_setupPinMode(USART3_PORT, USART3_CTS_PIN, OUTPUT_SPEED_50MHZ_AFPP);
	}
	else
	{
		return;
	}
}

static void USART_enableIRQ(USART_Typedef *a_usart)
{

	if (a_usart == USART1)
	{
		NVIC_enableIRQ(IRQ_USART1);
		NVIC_setPriority(IRQ_USART1, 0);
	}
	else if (a_usart == USART2)
	{
		NVIC_enableIRQ(IRQ_USART2);
		NVIC_setPriority(IRQ_USART2, 0);
	}
	else if (a_usart == USART3)
	{
		NVIC_enableIRQ(IRQ_USART3);
		NVIC_setPriority(IRQ_USART3, 0);
	}
	else
	{
		return;
	}
}

static void USART_disableIRQ(USART_Typedef *a_usart)
{

	if (a_usart == USART1)
	{
		NVIC_disableIRQ(IRQ_USART1);
	}
	else if (a_usart == USART2)
	{
		NVIC_disableIRQ(IRQ_USART2);
	}
	else if (a_usart == USART3)
	{
		NVIC_disableIRQ(IRQ_USART3);
	}
	else
	{
		return;
	}
}

/*******************************************************************************
 *                         Public functions definitions                        *
 *******************************************************************************/

USART_Status_t USART_init(USART_Typedef *a_usart, USART_Config_t *a_config)
{

	if (a_usart == NULLPTR || a_config == NULLPTR)
	{
		return USART_ERROR;
	}
	USART_Status_t status = USART_OK;
	USART_initPins(a_usart);

	/* Calculate the baud rate */
	u32 l_core_clock = F_CPU;
	u32 l_USART_DIV = l_core_clock / (16 * a_config->baud_rate);

	u32 l_USART_Mantissa = l_USART_DIV;
	u32 l_USART_Fraction = ((l_core_clock % (16 * a_config->baud_rate)) * 16 + (16 * a_config->baud_rate) / 2) / (16 * a_config->baud_rate);

	a_usart->USART_BRR = (l_USART_Fraction) | (l_USART_Mantissa << 4);
	a_usart->USART_SR = 0;

	/* Set the UE bit in USART register to enable UART*/
	SET_BIT(a_usart->USART_CR1, USART_CR1_UE);
	WRITE_BIT(a_usart->USART_CR1, USART_CR1_TE, 1);
	WRITE_BIT(a_usart->USART_CR1, USART_CR1_RE, 1);

	/* Set the word length: 8 or 9 bits */
	WRITE_BIT(a_usart->USART_CR1, USART_CR1_WORD_LENGTH, a_config->word_length);

	/* Set the stopbits length */
	WRITE_BIT(a_usart->USART_CR2, USART_CR2_STOPBITS_LENGTH,
			  a_config->stop_bits);

	/* Set CPHA and CPOL */
	WRITE_BIT(a_usart->USART_CR2, USART_CR2_CPOL, a_config->cpol);
	WRITE_BIT(a_usart->USART_CR2, USART_CR2_CPHA, a_config->cpha);

	/* Set parity control enable if parity is enabled */
	if (a_config->parity == USART_PARITY_NONE)
	{
		WRITE_BIT(a_usart->USART_CR1, USART_CR1_PCE, 0UL);
	}
	else
	{
		WRITE_BIT(a_usart->USART_CR1, USART_CR1_PCE, 1UL);
		WRITE_BIT(a_usart->USART_CR1, USART_CR1_PS, a_config->parity);
	}

	return status;
}

USART_Status_t USART_sendChar(USART_Typedef *a_usart, u8 a_data)
{
	a_usart->USART_CR1 |= (1 << USART_CR1_TE);
	a_usart->USART_DR = (a_data & 0xFFU);
	while (!CHK_BIT(a_usart->USART_SR, USART_SR_TC))
		;
	CLR_BIT(a_usart->USART_SR, USART_SR_TC);
	return USART_OK;
}

USART_Status_t USART_sendString(USART_Typedef *a_usart, u8 a_data[], u16 size)
{
	USART_Status_t l_status = USART_OK;
	for (u16 idx = 0; idx < size && l_status == USART_OK; idx++)
	{
		l_status = USART_sendChar(a_usart, a_data[idx]);
	}
	return l_status;
}

USART_Status_t USART_sendString_Interrupt(USART_Typedef *a_usart, u8 a_data[],
										  u16 size)
{
	USART_Status_t l_status = USART_OK;
	USART_enableInterrupt(a_usart, USART_Interrupt_TXE);
	/* Set size and data array */
	usart_tx_data = &a_data;
	usart_tx_data_len = size;

	return l_status;
}

USART_Status_t USART_receiveChar(USART_Typedef *a_usart, u8 *data)
{
	while (!CHK_BIT(a_usart->USART_SR, USART_SR_RXNE))
		;
	if (data)
		*data = (a_usart->USART_DR & 0xFFU);
	return USART_OK;
}

USART_Status_t USART_receiveString(USART_Typedef *a_usart, u8 a_data[],
								   u16 size)
{
	for (u16 idx = 0; idx < size; idx++)
	{
		USART_Status_t status = USART_receiveChar(a_usart, &a_data[idx]);
		if (status == USART_NO_DATA)
		{
			// No data received
			return USART_NO_DATA;
		}
	}
	return USART_OK;
}

void USART_receiveString_Interrupt(USART_Typedef *a_usart, void (*callback)(u8))
{
	if (callback)
	{
		if (a_usart == USART1)
			usart1_rxne_callback = callback;
		else if (a_usart == USART2)
			usart2_rxne_callback = callback;
		else if (a_usart == USART3)
			usart3_rxne_callback = callback;
		else
			return;
	}

	/* Enable the RXNE interrupt for reception */
	USART_enableInterrupt(a_usart, USART_Interrupt_RXNE);
}

USART_Status_t USART_enableInterrupt(USART_Typedef *a_usart,
									 USART_Interrupt_t a_interrupt)
{

	USART_Status_t l_status = USART_OK;

	USART_enableIRQ(a_usart);

	switch (a_interrupt)
	{
	case USART_Interrupt_TC:
		SET_BIT(a_usart->USART_CR1, USART_CR1_TCIE);
		break;
	case USART_Interrupt_TXE:
		SET_BIT(a_usart->USART_CR1, USART_CR1_TXEIE);
		break;
	case USART_Interrupt_PE:
		SET_BIT(a_usart->USART_CR1, USART_CR1_PEIE);
		break;
	case USART_Interrupt_RXNE:
		SET_BIT(a_usart->USART_CR1, USART_CR1_RXNEIE);
		break;
	case USART_Interrupt_IDLE:
		SET_BIT(a_usart->USART_CR1, USART_CR1_IDLEIE);
		break;
	case USART_Interrupt_LBD:
		SET_BIT(a_usart->USART_CR2, USART_CR2_LBDIE);
		break;
	case USART_Interrupt_CTS:
		if (!GET_BIT(a_usart->USART_CR3, USART_CR3_CTSE))
			return USART_ERROR;
		SET_BIT(a_usart->USART_CR3, USART_CR3_CTSIE);
		break;
	case USART_Interrupt_ORE:
	case USART_Interrupt_FE:
		break;
	}

	return l_status;
}

USART_Status_t USART_disableInterrupt(USART_Typedef *a_usart,
									  USART_Interrupt_t a_interrupt)
{
	USART_Status_t l_status = USART_OK;

	switch (a_interrupt)
	{
	case USART_Interrupt_TC:
		CLR_BIT(a_usart->USART_CR1, USART_CR1_TCIE);
		break;
	case USART_Interrupt_TXE:
		CLR_BIT(a_usart->USART_CR1, USART_CR1_TXEIE);
		break;
	case USART_Interrupt_PE:
		CLR_BIT(a_usart->USART_CR1, USART_CR1_PEIE);
		break;
	case USART_Interrupt_RXNE:
		CLR_BIT(a_usart->USART_CR1, USART_CR1_RXNEIE);
		break;
	case USART_Interrupt_IDLE:
		CLR_BIT(a_usart->USART_CR1, USART_CR1_IDLEIE);
		break;
	case USART_Interrupt_LBD:
		CLR_BIT(a_usart->USART_CR2, USART_CR2_LBDIE);
		break;
	case USART_Interrupt_CTS:
		if (!GET_BIT(a_usart->USART_CR3, USART_CR3_CTSE))
			return USART_ERROR;
		CLR_BIT(a_usart->USART_CR3, USART_CR3_CTSIE);
		break;
	case USART_Interrupt_ORE:
	case USART_Interrupt_FE:
		break;
	}

	USART_disableIRQ(a_usart);

	return l_status;
}

__attribute((__weak__)) void USART1_IRQHandler(void)
{
	USART_disableIRQ(USART1);
	if (usart1_rxne_callback)
	{
		u8 byte = 0;
		USART_receiveChar(USART1, &byte);
		(*usart1_rxne_callback)(byte);
	}
}

__attribute((__weak__)) void USART2_IRQHandler(void)
{
	USART_disableIRQ(USART2);
	if (usart2_rxne_callback)
	{
		u8 byte = 0;
		USART_receiveChar(USART2, &byte);
		(*usart2_rxne_callback)(byte);
	}
}

__attribute((__weak__)) void USART3_IRQHandler(void)
{
	USART_disableIRQ(USART3);
	if (usart3_rxne_callback)
	{
		u8 byte = 0;
		USART_receiveChar(USART3, &byte);
		(*usart3_rxne_callback)(byte);
	}
}
