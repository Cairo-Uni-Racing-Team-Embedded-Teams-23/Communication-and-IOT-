/*************************************************************************************************
 * [MODULE_NAME]:    GPIO_INTERFACE.h
 *
 * [DATE CREATED]:  18/10/2022
 *
 * [Author]:        Hazem Montasser
 *
 * [DESCRIPTION]:   All # Defines to be used by User & Function's prototype
 ************************************************************************************************/
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"

/******************************************************************************
 *                              Definitions                                    *
 *******************************************************************************/

#define NUM_OF_PINS_PER_PORT  (15U)
#define NUM_OF_PORTS          (3U)

#define GPIOA_ID              (0U)
#define GPIOB_ID              (1U)
#define GPIOC_ID              (2U)
#define PIN0                  (0U)
#define PIN1                  (1U)
#define PIN2                  (2U)
#define PIN3                  (3U)
#define PIN4                  (4U)
#define PIN5                  (5U)
#define PIN6                  (6U)
#define PIN7                  (7U)
#define PIN8                  (8U)
#define PIN9                  (9U)
#define PIN10                 (10U)
#define PIN11                 (11U)
#define PIN12                 (12U)
#define PIN13                 (13U)
#define PIN14                 (14U)
#define PIN15                 (15U)

#define GPIO_HIGH_PORT        (0xFFFFU)
#define GPIO_LOW_PORT         (0x0000U)

#define LOW_PINS              (0U)
#define HIGH_PINS             (1U)

/**********************************************************************/
/*                                                                    */
/*                        GPIO Peripheral Modes                       */
/*                              0-INPUT_ANLOG                         */
/*                              1-INPUT_FLOATING                      */
/*                              2-INPUT_PULLUP_PULLDOWN               */
/*                              3-OUTPUT_SPEED_10MHZ_PP               */
/*                              4-OUTPUT_SPEED_10MHZ_OD               */
/*                              5-OUTPUT_SPEED_10MHZ_AFPP             */
/*                              6-OUTPUT_SPEED_10MHZ_AFOD             */
/*                              7-OUTPUT_SPEED_2MHZ_PP                */
/*                              8-OUTPUT_SPEED_2MHZ_OD                */
/*                              9-OUTPUT_SPEED_2MHZ_AFPP              */
/*                              10-OUTPUT_SPEED_2MHZ_AFOD             */
/*                              11-OUTPUT_SPEED_50MHZ_PP              */
/*                              12-OUTPUT_SPEED_50MHZ_OD              */
/*                              13-OUTPUT_SPEED_50MHZ_AFPP            */
/*                              14-OUTPUT_SPEED_50MHZ_AFOD            */
/*                                                                    */
/**********************************************************************/

#define INPUT_ANLOG             (0b0000U)   /*< Input analog */
#define INPUT_FLOATING          (0b0100U)   /*< Input floating */
#define INPUT_PULLUP_PULLDOWN   (0b1000U)   /*< Input pull-up or pull-down */

// For Speed 10
#define OUTPUT_SPEED_10MHZ_PP   (0b0001U)   /*< Output Push-Pull 10MHz */
#define OUTPUT_SPEED_10MHZ_OD   (0b0101U)   /*< Output Open-drain 10MHz */
#define OUTPUT_SPEED_10MHZ_AFPP (0b1001U)   /*< Output Alternate function Push-Pull 10MHz */
#define OUTPUT_SPEED_10MHZ_AFOD (0b1101U)   /*< Output Alternate function Open-drain 10MHz */

// For Speed 2
#define OUTPUT_SPEED_2MHZ_PP    (0b0010U)   /*< Output Push-Pull 2MHz */
#define OUTPUT_SPEED_2MHZ_OD    (0b0110U)   /*< Output Open-drain 2MHz */
#define OUTPUT_SPEED_2MHZ_AFPP  (0b1010U)   /*< Output Alternate function Push-Pull 2MHz */
#define OUTPUT_SPEED_2MHZ_AFOD  (0b1110U)   /*< Output Alternate function Open-drain 2MHz */

// For Speed 50
#define OUTPUT_SPEED_50MHZ_PP   (0b0011U)   /*< Output Push-Pull 50MHz */
#define OUTPUT_SPEED_50MHZ_OD   (0b0111U)   /*< Output Open-drain 50MHz */
#define OUTPUT_SPEED_50MHZ_AFPP (0b1011U)   /*< Output Alternate function Push-Pull 50MHz */
#define OUTPUT_SPEED_50MHZ_AFOD (0b1111U)   /*< Output Alternate function Open-drain 50MHz */

/******************************************************************************
 *                              Type definitions                               *
 *******************************************************************************/

typedef enum {
	GPIO_PortA = 0, GPIO_PortB = 1, GPIO_PortC = 2
} GPIO_PortNameType;

typedef enum {
	GPIO_PIN_RESET, GPIO_PIN_SET
} GPIO_PinStateType;

/******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @fn void GPIO_setupPinMode(u8, u8, u8)
 * @brief Setup the Mode & Direction of the required pin from 16 Modes.
 * 		If the input port number or pin number are not correct, The function will not handle the request.
 *
 * @pre port_num and pin_num are valid
 * @post Pin is setup using the mode value selected.
 * @param port_num Port number
 * @param pin_num  Pin number
 * @param mode	   Mode used to set the pin
 */
void GPIO_setupPinMode(u8 port_num, u8 pin_num, u8 mode);

/**
 * @fn void GPIO_setPinValue(u8, u8, u8)
 * @brief Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up/pull-down resistor.
 * @pre port_num and pin_num are valid
 * @post If value is non-zero, then logic high is written to the pin.
 * @param port_num Port number
 * @param pin_num  Pin number
 * @param value	   Value to set the pin state
 */
void GPIO_setPinValue(u8 port_num, u8 pin_num, u8 value);

/**
 * @fn u8 GPIO_getPinValue(u8, u8)
 * @brief  Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 * @pre port_num and pin_num are valid
 * @post Pin value whether it is logic high or low
 * @param port_num Port number
 * @param pin_num  Pin number
 * @return Pin value
 */
u8 GPIO_getPinValue(u8 port_num, u8 pin_num);

/**
 * @fn void GPIO_setupPortMode(u8, u8)
 * @brief Setup the direction of the required port all pins from 16 modes.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 * @pre port_num is valid
 * @post All pins on the selected port are setup using the specified mode.
 * @param port_num Port number
 * @param mode     Mode used to set all pins on the port
 */
void GPIO_setupPortMode(u8 port_num, u8 mode);

/**
 * @fn void GPIO_writePort(u8, u16)
 * @brief  Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 *
 * @pre port_num is valid
 * @post The value on the port becomes the value variable
 * @param port_num Port number
 * @param value	   Value used to write to the port
 */
void GPIO_writePort(u8 port_num, u16 value);

/**
 * @fn u16 GPIO_getPort(u8)
 * @brief  Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 *
 * @pre port_num is valid
 * @post Value on the port
 * @param port_num Port number
 * @return Value on the port
 */
u16 GPIO_getPort(u8 port_num);

/**
 * @fn void GPIO_togglePinValue(u8, u8)
 * @brief Toggles the pin value.
 *
 * @pre port_num must be a valid port, and pin_num must be less than or equal to NUM_OF_PINS_PER_PORT
 * @post Pin value is toggled
 * @param port_num Port number
 * @param pin_num  Pin number
 */
void GPIO_togglePinValue(u8 port_num, u8 pin_num);

/**
 * @fn void GPIO_enablePortClock(u8)
 * @brief Enables the clock for a specified port
 *
 * @pre port_num must be a valid port from the available enum
 * @post Clock for the specified port is started
 * @param port_num	Port on which to enable the clock
 */
void GPIO_enablePortClock(u8 port_num);

/**
 * @fn void GPIO_setPortDirection_H_L(u8, u8, u8)
 * @brief Sets up half of the port with a specified mode. If the position is GPIO_LOW_PORT, then
 * 		the lower part of the port (pins 0-7) are setup. Otherwise, the higher part of the port (pins 8-15)
 * 		are setup
 * 	**Note: The user is responsible for selecting a correct mode and position.
 * @pre   port_num must be valid
 * @post  Half of the selected port is setup using the specified mode.
 * @param port_num Port number
 * @param position Lower or higher part of the port
 * @param mode	   Mode used to setup the port half
 */
void GPIO_setPortDirection_H_L(u8 port_num, u8 position, u8 mode);

/**
 * @fn void GPIO_setPortValue_H_L(u8, u8, u16)
 * @brief Sets up half of the port with the passed value. If the position is GPIO_LOW_PORT, then
 * 		the lower part of the port (pins 0-7) are set. Otherwise, the higher part of the port (pins 8-15)
 * 		are set
 *
 * @pre   port_num must be valid
 * @post  Half of the selected port contains the LOWER NIBBLE of value variable.
 * @param port_num Port number
 * @param position Lower or higher part of the port
 * @param value	   Value to set
 */
void GPIO_setPortValue_H_L(u8 port_num, u8 position, u16 value);

/**
 * @fn void GPIO_lockPin(u8, u16)
 * @brief Locks the pin selected. Any modification on the pin mode or value will not take
 * 		effect until next reset.
 *
 * @pre port_num must be valid. Pins is the bit-wise OR'ing of the bits to lock.
 * 		Ex. : pin 0, pin 4, pin13 -> pins=(1<<0)|(1<<4)|(1<<13);
 * @post The pins specified are locked till next reset.
 * @param port_num	Port number
 * @param pins		Bit-wise OR'ed pins needed to be locked
 */
void GPIO_lockPin(u8 port_num, u16 pins);

/**
 * @fn void GPIO_lockPort(u8)
 * @brief Locks the port selected. Any modification on the port mode or value will not take
 * 		effect until next reset.
 *
 * @pre port_num must be valid.
 * @post All of the port pins are locked till next reset.
 * @param port_num Port number
 */
void GPIO_lockPort(u8 port_num);

#endif
