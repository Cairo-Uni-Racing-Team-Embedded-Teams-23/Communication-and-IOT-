#include "main.h"
#include "utility_funcs.h"

#ifndef EVMS_H
#define EVMS_H

#define VAL_BRAKE_ANGLE_RTD		900
#define PWM_MAX_OUTPUT			65535
#define APPS_MIN	(490)
#define APPS_MAX	(3600)
/***************************************************************************
 *							Types Declaration 			                   *
 ***************************************************************************/

typedef enum 
{
IDLE, 
PRECHARGE, 
NEUTRAL, 
DRIVE, 
DISCHARGE
}Modes_enum;

typedef enum
{
	APP1,
	APP2,
	BRAKE_ANGLE
}Adc_Values;

typedef enum 
{
NOERROR, 
FATAL
}Error_enum;

typedef enum
{
	NO_TYPE_ERROR,
	ERROR_CheckAPPS,
	ERROR_PrechargeFB,
	ERROR_AIRposFB,
	ERROR_AIRnegFB
}Type_Error_enum;

/***************************************************************************
 *							Functions prototypes     	                   *
 ***************************************************************************/
/* Description:
 * This function reads the ADC value of the first pedal 10 times and gets
 * its average to eliminate error in the reading
 */
uint16_t uint16_t_Read_APPS1();

/* Description:
 * This function reads the ADC value of the second pedal 10 times and gets
 * its average to eliminate error in the reading
 */
uint16_t uint16_t_Read_APPS2();

/* Description:
 * 1. This function compare the ADC value of the first pedal with the second
 * pedal, allowing a difference less than 10% from the reading of either
 * the pedals.
 * 2. If the difference excide this value then there is an error.
 */
void Check_APPS();

/* Description:
 * This function to activate the drive mode under the conditions:
 * 1. RTD button has been pressed for 3 seconds
 * 2. The brake angle has a value more than a required one
 */
void Check_Activasion_Logic();

/* Description:
 * This function initialize the ADC1 with the ADC values in 3 sequences in DMA
 */
void EVMS_Init();

/* Description:
 * 1. Disable EVMS Relay
 * 2. Check on the start button if pressed so enter pre-charge state
 */
void IDLE_Func();

/* Description:
 * 1. Enable pre-charge Relay to start charging the battery
 * 2. Check on the start button if pressed so enter pre-charge state
 */
void PRECHARGE_Func();

/* Description:
 * 1. Disable pre-charge relay to stop charging the battery
 * 2. Enable AIR positive relay
 * 3. Check on the feedback of the pre-charge, AIR positive and AIR negative to avoid errors
 * 4. Check on the difference between pedals sensors to avoid errors
 * 5. Check the activation logic to go to the drive mode if happened
 */
void NEUTRAL_Func();

/* Description:
 * 1. Enable the motor inverter
 * 2. Check on the difference between pedals sensors to avoid errors
 * 3. Generating PWM signal according to first pedal sensor average read
 * 4. Check on the feedback of the AIR negative to avoid errors
 * 5. Check if the start button is pressed to go to the discharge state
 */
void DRIVE_Func();

/* Description:
 * 1. Enable EVMS relay to discharge the battery
 * 2. Disable the inverter
 * 3. Disable AIR positive relay
 * 4. Check on the feedback of the AIR positive and AIR negative to avoid errors
 * 5. check on the DC60 signal to whether go IDLE or not
 */
void DISCHARGE_Func();


/* Description:
 * 1. Transmit a message with the ADC values by the UART
 * 2. Switch to the required state
 */
void loop();

/* Description:
 * 1. Enable EVMS relay to open the shutdown circuit
 */
void ErrorAction();

#endif
