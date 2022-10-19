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
*                              Includes                                    *
*******************************************************************************/

#include "std_types.h"

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

typedef enum
{
    GPIO_PortA = 0,
    GPIO_PortB = 1,
    GPIO_PortC = 2
} GPIO_PortNameType;

typedef enum
{
    GPIO_PIN_RESET,
    GPIO_PIN_SET
} GPIO_PinStateType;


// typedef enum
// {

//     GPIO_Mode_INPUT_ANLOG = 0b0000,
//     GPIO_Mode_INPUT_FLOATING = 0b0100,
//     GPIO_Mode_INPUT_PULLUP_PULLDOWN = 0b100,

//     GPIO_Mode_OUTPUT_SPEED_10MHZ_PP = 0b0001,
//     GPIO_Mode_OUTPUT_SPEED_10MHZ_OD = 0b0101,
//     GPIO_Mode_OUTPUT_SPEED_10MHZ_AFPP = 0b1001,
//     GPIO_Mode_OUTPUT_SPEED_10MHZ_AFOD = 0b110,
//     GPIO_Mode_OUTPUT_SPEED_2MHZ_PP =  0b0010,
//     GPIO_Mode_OUTPUT_SPEED_2MHZ_OD = 0b0110,
//     GPIO_Mode_OUTPUT_SPEED_2MHZ_AFPP = 0b1010,
//     GPIO_Mode_OUTPUT_SPEED_2MHZ_AFOD = 0b111,
//     GPIO_Mode_OUTPUT_SPEED_50MHZ_PP = 0b0011,
//     GPIO_Mode_OUTPUT_SPEED_50MHZ_OD = 0b0111,
//     GPIO_Mode_OUTPUT_SPEED_50MHZ_AFPP = 0b1011,
//     GPIO_Mode_OUTPUT_SPEED_50MHZ_AFOD = 0b1111
// }GPIO_ModeType2;

/******************************************************************************
*                              Function Prototypes                            *
*******************************************************************************/

/*
 * Description :
 * Setup the Mode & Direction of the required pin from 16 Modes.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */

void GPIO_setupPinMode(uint8 port_num, uint8 pin_num, uint8 mode);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up/pull-down resistor.
 */
void GPIO_setPinValue(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_getPinValue(uint8 port_num, uint8 pin_num);

/*
 * Description :
 * Setup the direction of the required port all pins from 16 modes.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortMode(uint8 port_num, uint8 mode);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint16 value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint16 GPIO_getPort(uint8 port_num);

void GPIO_togglePinValue(uint8 port_num, uint8 pin_num);

void GPIO_enablePortClock(uint8 port_num);

void GPIO_setPortDirection_H_L( uint8 Port , uint8 Position , uint8 Mode );

void GPIO_setPortValue_H_L( uint8 Port , uint8 Position , uint16 Value );

#endif
