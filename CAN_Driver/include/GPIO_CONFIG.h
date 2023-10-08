/*************************************************************************************************
 * [MODULE_NAME]:  GPIO_CONFIG.h
 *
 * [DATE CREATED]: 
 *
 * [Author]:        
 *
 * [DESCRIPTION]:  Configurations for GPIO
 ************************************************************************************************/
#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_


#define NUM_OF_PINS_PER_PORT 15
#define NUM_OF_PORTS 3

#define GPIOA_ID   0
#define GPIOB_ID   1
#define GPIOC_ID   2

#define PIN0    0
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7
#define PIN8    8
#define PIN9    9
#define PIN10    10
#define PIN11    11
#define PIN12    12
#define PIN13    13
#define PIN14    14
#define PIN15    15

#define HIGH    1
#define LOW     0

#define HIGH_PORT 0XFFFF
#define LOW_PORT   0

#define LOW_PINS   0
#define HIGH_PINS  1


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

#define INPUT_ANLOG               0b0000
#define INPUT_FLOATING            0b0100
#define INPUT_PULLUP_PULLDOWN     0b1000

//For Speed 10
#define OUTPUT_SPEED_10MHZ_PP     0b0001
#define OUTPUT_SPEED_10MHZ_OD     0b0101
#define OUTPUT_SPEED_10MHZ_AFPP   0b1001
#define OUTPUT_SPEED_10MHZ_AFOD   0b1101

//For Speed 2
#define OUTPUT_SPEED_2MHZ_PP      0b0010
#define OUTPUT_SPEED_2MHZ_OD      0b0110
#define OUTPUT_SPEED_2MHZ_AFPP    0b1010
#define OUTPUT_SPEED_2MHZ_AFOD    0b1110

//For Speed 50
#define OUTPUT_SPEED_50MHZ_PP     0b0011
#define OUTPUT_SPEED_50MHZ_OD     0b0111
#define OUTPUT_SPEED_50MHZ_AFPP   0b1011
#define OUTPUT_SPEED_50MHZ_AFOD   0b1111


//Input Port
#define INPUT_PORT_ANLOG               0x00000000
#define INPUT_PORT_FLOATING            0x44444444
#define INPUT_PORT_PULLUP_PULLDOWN     0x88888888


//Output Port For Speed 10
#define OUTPUT_PORT_SPEED_10MHZ_PP     0x11111111
#define OUTPUT_PORT_SPEED_10MHZ_OD     0x55555555
#define OUTPUT_PORT_SPEED_10MHZ_AFPP   0x99999999
#define OUTPUT_PORT_SPEED_10MHZ_AFOD   0xDDDDDDDD

//Output Port For Speed 2
#define OUTPUT_PORT_SPEED_2MHZ_PP      0x22222222
#define OUTPUT_PORT_SPEED_2MHZ_OD      0x66666666
#define OUTPUT_PORT_SPEED_2MHZ_AFPP    0xAAAAAAAA
#define OUTPUT_PORT_SPEED_2MHZ_AFOD    0xEEEEEEEE

//Output Port For Speed 50
#define OUTPUT_PORT_SPEED_50MHZ_PP     0x33333333
#define OUTPUT_PORT_SPEED_50MHZ_OD     0x77777777
#define OUTPUT_PORT_SPEED_50MHZ_AFPP   0xBBBBBBBB
#define OUTPUT_PORT_SPEED_50MHZ_AFOD   0xFFFFFFFF



#endif
