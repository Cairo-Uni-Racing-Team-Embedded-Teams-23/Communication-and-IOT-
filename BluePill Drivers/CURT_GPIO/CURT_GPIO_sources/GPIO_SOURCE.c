#include "../CURT_GPIO_headers/GPIO_INTERFACE.h"
#include "../CURT_GPIO_headers/GPIO_PRIVATE.h"
#include "../CURT_GPIO_headers/GPIO_REG.h"
#include "../../LIB/BIT_MATH.h"
#include "../../CURT_RCC/CURT_RCC_headers/RCC_interface.h"
/*
 * Description :
 * Setup the Mode & Direction of the required pin from 16 Modes.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinMode(uint8 port_num, uint8 pin_num, uint8 mode)
{

    switch (port_num)
    {
    case GPIO_PortA:
        /* Check the pin if it's from the lower port pins or higher ones */
        if (pin_num < 8)
        {
            /*
               First, shift pin number by 2 left to multiply by 4 pin_num<<2,
               since each pin is separated from the other by 4 bits.
               Second, shift the 4 mode bits by the bit position into its position so it is aligned.
            */
            GPIOA->CRL &= ~(0b1111 << (pin_num << 2));
            GPIOA->CRL |= (mode << (pin_num << 2));
        }
        else if (pin_num < 16)
        {

            GPIOA->CRH &= ~(0b1111 << ((pin_num - 8) << 2));
            GPIOA->CRH |= (mode << ((pin_num - 8) << 2));
        }

        break;
    case GPIO_PortB:
        /* Check the pin if it's from the lower port pins or higher ones */
        if (pin_num < 8)
        {
            /*
               First, shift pin number by 2 left to multiply by 4 pin_num<<2,
               since each pin is separated from the other by 4 bits.
               Second, shift the 4 mode bits by the bit position into its position so it is aligned.
            */
            GPIOB->CRL &= ~(0b1111 << (pin_num << 2));
            GPIOB->CRL |= (mode << (pin_num << 2));
        }
        else if (pin_num < 16)
        {
            GPIOB->CRH &= ~(0b1111 << ((pin_num - 8) << 2));
            GPIOB->CRH |= (mode << ((pin_num - 8) << 2));
        }

        break;
    case GPIO_PortC:
        /* Check the pin if it's from the lower port pins or higher ones */
        if (pin_num < 8)
        {
            /*
               First, shift pin number by 2 left to multiply by 4 pin_num<<2,
               since each pin is separated from the other by 4 bits.
               Second, shift the 4 mode bits by the bit position into its position so it is aligned.
            */
            GPIOC->CRL &= ~(0b1111 << (pin_num << 2));
            GPIOC->CRL |= (mode << (pin_num << 2));
        }
        else if (pin_num < 16)
        {
            GPIOC->CRH &= ~(0b1111 << ((pin_num - 8) << 2));
            GPIOC->CRH |= (mode << ((pin_num - 8) << 2));
        }

        break;
    default:
        break;
    }
}
/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up/pull-down resistor.
 */
void GPIO_setPinValue(uint8 port_num, uint8 pin_num, uint8 value)
{
    switch (port_num)
    {
    case GPIO_PortA:

        /* Invalid pin number input */
        if (pin_num > GPIOA_MAX_PINS)
            return;
        WRITE_BIT(GPIOA->ODR, pin_num, value);

        break;
    case GPIO_PortB:

        /* Invalid pin number input */
        if (pin_num > GPIOB_MAX_PINS)
            return;
        WRITE_BIT(GPIOB->ODR, pin_num, value);

        break;
    case GPIO_PortC:

        /* Invalid pin number input */
        if (pin_num > GPIOC_MAX_PINS)
            return;
        WRITE_BIT(GPIOC->ODR, pin_num, value);

        break;
    default:
        break;
    }
}
/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_getPinValue(uint8 port_num, uint8 pin_num)
{
    switch (port_num)
    {
    case GPIO_PortA:
        /* Invalid pin number input */
        if (pin_num > GPIOC_MAX_PINS)
            return LOGIC_LOW;

        return GET_BIT(GPIOA->ODR, pin_num);
        break;
    case GPIO_PortB:
        /* Invalid pin number input */
        if (pin_num > GPIOC_MAX_PINS)
            return LOGIC_LOW;

        return GET_BIT(GPIOB->ODR, pin_num);
        break;
    case GPIO_PortC:
        /* Invalid pin number input */
        if (pin_num > GPIOC_MAX_PINS)
            return LOGIC_LOW;

        return GET_BIT(GPIOC->ODR, pin_num);
        break;
    default:
        return LOGIC_LOW;
        break;
    }
    return LOGIC_LOW;
}

/*
 * Description :
 * Setup the direction of the required port all pins from 16 modes.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortMode(uint8 port_num, uint8 mode)
{

    switch (port_num)
    {
    case GPIO_PortA:

        GPIOA->CRH = GPIOA->CRL = (mode |
                                   (mode << 4) |
                                   (mode << 8) |
                                   (mode << 12) |
                                   (mode << 16) |
                                   (mode << 20) |
                                   (mode << 24) |
                                   (mode << 28));
        break;
    case GPIO_PortB:
        GPIOB->CRH = GPIOB->CRL = (mode |
                                   (mode << 4) |
                                   (mode << 8) |
                                   (mode << 12) |
                                   (mode << 16) |
                                   (mode << 20) |
                                   (mode << 24) |
                                   (mode << 28));
        break;
    case GPIO_PortC:
        GPIOC->CRH = GPIOC->CRL = (mode |
                                   (mode << 4) |
                                   (mode << 8) |
                                   (mode << 12) |
                                   (mode << 16) |
                                   (mode << 20) |
                                   (mode << 24) |
                                   (mode << 28));
        break;
    default:
        break;
    }
}
/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * xxxxx - If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint16 value)
{
    /* xxxxxxxxUse BSRR since it is atomic */
    /*value = ((((uint32)(~value)) << 16) | (uint32)(value));*/
    switch (port_num)
    {
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

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint16 GPIO_getPort(uint8 port_num)
{
    switch (port_num)
    {
    case GPIO_PortA:
        /* Clear last 16 bits as they are reserved */
        return (uint16)(GPIOA->IDR & 0x00FF);

        break;
    case GPIO_PortB:
        /* Clear last 16 bits as they are reserved */
        return (uint16)(GPIOB->IDR & 0x00FF);

        break;
    case GPIO_PortC:
        /* Clear last 16 bits as they are reserved */
        return (uint16)(GPIOC->IDR & 0x00FF);

        break;
    default:
        return 0;
        break;
    }
    return 0;
}

void GPIO_togglePinValue(uint8 port_num, uint8 pin_num)
{

    switch (port_num)

    {
    case GPIO_PortA:
        /* Invalid pin number input */
        if (pin_num > GPIOC_MAX_PINS)
            return;
        TOG_BIT(GPIOA->ODR, pin_num);
        break;
    case GPIO_PortB:
        /* Invalid pin number input */
        if (pin_num > GPIOC_MAX_PINS)
            return;
        TOG_BIT(GPIOA->ODR, pin_num);

        break;
    case GPIO_PortC:
        /* Invalid pin number input */
        if (pin_num > GPIOC_MAX_PINS)
            return;
        TOG_BIT(GPIOA->ODR, pin_num);

        break;
    default:
        break;
    }
}

void GPIO_enablePortClock(uint8 port_num)
{
    /* Determine the port, and start its clock using GPIO bus and the port ID on the bus */
    switch (port_num)
    {
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

/****************************************************************************************************************************************************
*Functions will be added to be used in another drivers

void GPIO_setPortDirection_H_L( uint8 Port , uint8 Position , uint8 Mode );

void GPIO_setPortValue_H_L( uint8 Port , uint8 Position , uint16 Value );
****************************************************************************************************************************************************/
