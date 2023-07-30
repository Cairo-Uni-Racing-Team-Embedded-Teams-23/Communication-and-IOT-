#ifndef EVMS2_H
#define EVMS2_H
#include "main.h"

typedef enum
{
	BSPD_flag,BMS_flag,IMD_flag,
}Error_flags;

typedef enum
{
	FAN_relay,PUMP,
}Control_flags;

#define DMA_LENGTH 				2
#define BRAKES_LIGHT_VALUE 		1
#define ERROR					0
#define NOERROR					1
#define SET                     1
#define RESET                   0
#define FAN_THRESHOLD			0
#define PUMP_THRESHOLD			0
#define BRAKE_THRESHOLD			3500
#define TRUE                    1
#define FALSE                   0

void EVMS2_init(void);
uint16_t ADC_uint16ReadBrakes(void);

void Error_action(void);
uint8_t GPIO_uint8CheckIMD();
uint8_t LOGIC_uint8CheckBSPD();
uint8_t LOGIC_uint8CheckBMS();
void LOGIC_voidControlBrakeLight();
void LOGIC_voidControlPump();
void LOGIC_voidControlFan();
uint8_t isError(void); // returns one if one of feedbacks doesn't equal the true value

void Error_Action(void);




#endif
