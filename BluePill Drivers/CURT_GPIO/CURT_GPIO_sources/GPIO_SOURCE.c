/*************************************************************************************************
 * [MODULE_NAME]:    GPIO_SOURCE.c
 *
 * [DATE CREATED]:  18/10/2022
 *
 * [Author]:        Hazem Montasser
 *
 * [DESCRIPTION]:   GPIO driver source code for API functions.
 ************************************************************************************************/

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/
#include "../CURT_GPIO_headers/GPIO_INTERFACE.h"
#include "../CURT_GPIO_headers/GPIO_PRIVATE.h"
#include "../CURT_GPIO_headers/GPIO_REG.h"
#include "../../LIB/BIT_MATH.h"
#include "../../CURT_RCC/CURT_RCC_headers/RCC_interface.h"

/*******************************************************************************
 *                           Public functions definitions                      *
 *******************************************************************************/

void GPIO_setupPinMode(uint8 port_num, uint8 pin_num, uint8 mode) {

	switch (port_num) {
	case GPIO_PortA:
		/* Check the pin if it's from the lower port pins or higher ones */
		if (pin_num < 8) {
			/*
			 First, clear the 4 bits we need then shift pin number by 2 left to multiply by 4 pin_num<<2,
			 since each pin is separated from the other by 4 bits.
			 Second, shift the 4 mode bits by the bit position into its position so it is aligned.
			 */
			GPIOA->CRL &= ~(0b1111 << (pin_num << 2));
			GPIOA->CRL |= (mode << (pin_num << 2));
		} else if (pin_num < 16) {

			GPIOA->CRH &= ~(0b1111 << ((pin_num - 8) << 2));
			GPIOA->CRH |= (mode << ((pin_num - 8) << 2));
		}

		break;
	case GPIO_PortB:
		/* Check the pin if it's from the lower port pins or higher ones */
		if (pin_num < 8) {

			GPIOB->CRL &= ~(0b1111 << (pin_num << 2));
			GPIOB->CRL |= (mode << (pin_num << 2));
		} else if (pin_num < 16) {
			GPIOB->CRH &= ~(0b1111 << ((pin_num - 8) << 2));
			GPIOB->CRH |= (mode << ((pin_num - 8) << 2));
		}

		break;
	case GPIO_PortC:
		/* Check the pin if it's from the lower port pins or higher ones */
		if (pin_num < 8) {
			/*
			 First, shift pin number by 2 left to multiply by 4 pin_num<<2,
			 since each pin is separated from the other by 4 bits.
			 Second, shift the 4 mode bits by the bit position into its position so it is aligned.
			 */
			GPIOC->CRL &= ~(0b1111 << (pin_num << 2));
			GPIOC->CRL |= (mode << (pin_num << 2));
		} else if (pin_num < 16) {
			GPIOC->CRH &= ~(0b1111 << ((pin_num - 8) << 2));
			GPIOC->CRH |= (mode << ((pin_num - 8) << 2));
		}

		break;
	default:
		break;
	}
}

void GPIO_setPinValue(uint8 port_num, uint8 pin_num, uint8 value) {
	/* Invalid pin number input */
	if (pin_num > NUM_OF_PINS_PER_PORT)
		return;

	switch (port_num) {
	case GPIO_PortA:
		if (value != GPIO_PIN_RESET)
			SET_BIT(GPIOA->BSRR, pin_num);
		else
			SET_BIT(GPIOA->BRR, pin_num);

		break;
	case GPIO_PortB:
		if (value != GPIO_PIN_RESET)
			SET_BIT(GPIOB->BSRR, pin_num);
		else
			SET_BIT(GPIOB->BRR, pin_num);

		break;
	case GPIO_PortC:
		if (value != GPIO_PIN_RESET)
			SET_BIT(GPIOC->BSRR, pin_num);
		else
			SET_BIT(GPIOC->BRR, pin_num);

		break;
	default:
		break;
	}
}

uint8 GPIO_getPinValue(uint8 port_num, uint8 pin_num) {
	/* Invalid pin number input */
	if (pin_num > NUM_OF_PINS_PER_PORT)
		return LOGIC_LOW;

	switch (port_num) {
	case GPIO_PortA:
		if ((GPIOA->IDR & (1 << pin_num)) == 0U)
			return GPIO_PIN_RESET;
		else
			return GPIO_PIN_SET;
		break;
	case GPIO_PortB:
		if ((GPIOB->IDR & (1 << pin_num)) == 0U)
			return GPIO_PIN_RESET;
		else
			return GPIO_PIN_SET;
		break;
	case GPIO_PortC:
		if ((GPIOC->IDR & (1 << pin_num)) == 0U)
			return GPIO_PIN_RESET;
		else
			return GPIO_PIN_SET;
		break;
	default:
		return GPIO_PIN_RESET;
		break;
	}
	return GPIO_PIN_RESET;
}

void GPIO_setupPortMode(uint8 port_num, uint8 mode) {
	/* Copy the mode into all bits of the register for each pin */
	uint32 reg_val = (mode | (mode << 4) | (mode << 8) | (mode << 12)
			| (mode << 16) | (mode << 20) | (mode << 24) | (mode << 28));
	switch (port_num) {
	case GPIO_PortA:

		GPIOA->CRH = GPIOA->CRL = reg_val;
		break;
	case GPIO_PortB:
		GPIOB->CRH = GPIOB->CRL = reg_val;
		break;
	case GPIO_PortC:
		GPIOC->CRH = GPIOC->CRL = reg_val;
		break;
	default:
		break;
	}
}

void GPIO_writePort(uint8 port_num, uint16 value) {

	switch (port_num) {
	case GPIO_PortA:
		GPIOA->ODR = value;
		break;
	case GPIO_PortB:
		GPIOB->ODR = value;
		break;
	case GPIO_PortC:
		GPIOC->ODR = value;
		break;
	default:
		break;
	}
}

uint16 GPIO_getPort(uint8 port_num) {
	switch (port_num) {
	case GPIO_PortA:
		/* Clear last 16 bits as they are reserved */
		return (uint16) (GPIOA->IDR & 0x00FF);

		break;
	case GPIO_PortB:
		/* Clear last 16 bits as they are reserved */
		return (uint16) (GPIOB->IDR & 0x00FF);

		break;
	case GPIO_PortC:
		/* Clear last 16 bits as they are reserved */
		return (uint16) (GPIOC->IDR & 0x00FF);

		break;
	default:
		return 0;
		break;
	}
	return 0;
}

void GPIO_togglePinValue(uint8 port_num, uint8 pin_num) {
	/* Invalid pin number input */
	if (pin_num > NUM_OF_PINS_PER_PORT)
		return;
	switch (port_num) {
	case GPIO_PortA:
		TOG_BIT(GPIOA->ODR, pin_num);
		break;
	case GPIO_PortB:
		TOG_BIT(GPIOB->ODR, pin_num);
		break;
	case GPIO_PortC:
		TOG_BIT(GPIOC->ODR, pin_num);
		break;
	default:
		break;
	}
}

void GPIO_enablePortClock(uint8 port_num) {
	/* Determine the port, and start its clock using GPIO bus and the port ID on the bus */
	switch (port_num) {
	case GPIO_PortA:
		RCC_voidEnableClock(GPIO_BUS, GPIOA_BUS_ID);
		break;
	case GPIO_PortB:
		RCC_voidEnableClock(GPIO_BUS, GPIOB_BUS_ID);
		break;
	case GPIO_PortC:
		RCC_voidEnableClock(GPIO_BUS, GPIOC_BUS_ID);
		break;
	default:
		break;
	}
}

void GPIO_setPortDirection_H_L(uint8 port_num, uint8 position, uint8 mode) {
	/* Copy the mode into all bits of the register for each pin */
	uint32 reg_val = (mode | (mode << 4) | (mode << 8) | (mode << 12)
			| (mode << 16) | (mode << 20) | (mode << 24) | (mode << 28));
	/* Determine port and set the high or low part based on position argument*/
	switch (port_num) {
	case GPIO_PortA:
		if (position == GPIO_LOW_PORT)
			GPIOA->CRL = reg_val;
		else
			GPIOA->CRH = reg_val;
		break;

	case GPIO_PortB:
		if (position == GPIO_LOW_PORT)
			GPIOB->CRL = reg_val;
		else
			GPIOB->CRH = reg_val;
		break;

	case GPIO_PortC:
		if (position == GPIO_LOW_PORT)

			GPIOC->CRL = reg_val;
		else
			GPIOC->CRH = reg_val;
		break;

	default:
		break;
	}
}

void GPIO_setPortValue_H_L(uint8 port_num, uint8 position, uint16 value) {

	/* Determine port and set the high or low part based on position argument*/
	switch (port_num) {
	case GPIO_PortA:
		if (position == GPIO_LOW_PORT)
			GPIOA->ODR |= (value & 0x00FF);
		else
			/* Cast first to 32bit uint then shift 8 bits left to align it to the higher part of the port*/
			GPIOA->ODR |= (((uint32) value) << 8);
		break;

	case GPIO_PortB:
		if (position == GPIO_LOW_PORT)
			GPIOB->ODR |= (value & 0x00FF);
		else
			/* Cast first to 32bit uint then shift 8 bits left to align it to the higher part of the port*/
			GPIOB->ODR |= (((uint32) value) << 8);
		break;

	case GPIO_PortC:
		if (position == GPIO_LOW_PORT)
			GPIOC->ODR |= (value & 0x00FF);
		else
			/* Cast first to 32bit uint then shift 8 bits left to align it to the higher part of the port*/
			GPIOC->ODR |= (((uint32) value) << 8);
		break;

	default:
		break;
	}
}

void GPIO_lockPin(uint8 port_num, uint16 pins) {
	uint32 lock_val = (1 << 16) | pins;
	switch (port_num) {
	case GPIO_PortA:
		WRITE_PORT(GPIOA->LCKR, lock_val);
		WRITE_PORT(GPIOA->LCKR, pins);
		WRITE_PORT(GPIOA->LCKR, lock_val);
		lock_val = GPIOA->LCKR;

		break;

	case GPIO_PortB:
		WRITE_PORT(GPIOB->LCKR, lock_val);
		WRITE_PORT(GPIOB->LCKR, pins);
		WRITE_PORT(GPIOB->LCKR, lock_val);
		lock_val = GPIOB->LCKR;

		break;

	case GPIO_PortC:
		WRITE_PORT(GPIOC->LCKR, lock_val);
		WRITE_PORT(GPIOC->LCKR, pins);
		WRITE_PORT(GPIOC->LCKR, lock_val);
		lock_val = GPIOC->LCKR;

		break;

	default:
		break;
	}
}

void GPIO_lockPort(uint8 port_num) {

	uint32 lock_val = 0x0001FFFF;
	switch (port_num) {
	case GPIO_PortA:
		WRITE_PORT(GPIOA->LCKR, lock_val);
		WRITE_PORT(GPIOA->LCKR, 0x0000FFFF);
		WRITE_PORT(GPIOA->LCKR, lock_val);
		lock_val = GPIOA->LCKR;
		break;
	case GPIO_PortB:
		WRITE_PORT(GPIOB->LCKR, lock_val);
		WRITE_PORT(GPIOB->LCKR, 0x0000FFFF);
		WRITE_PORT(GPIOB->LCKR, lock_val);
		lock_val = GPIOB->LCKR;
		break;
	case GPIO_PortC:
		WRITE_PORT(GPIOC->LCKR, lock_val);
		WRITE_PORT(GPIOC->LCKR, 0x0000FFFF);
		WRITE_PORT(GPIOC->LCKR, lock_val);
		lock_val = GPIOC->LCKR;
		break;
	default:
		break;
	}
}
