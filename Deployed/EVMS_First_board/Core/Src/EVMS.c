/* while(1) for error action has to be completed
 *
 */
#include "EVMS.h"



/* variables declaration with initializing current and next state with
 * the IDLE state */
Modes_enum currStateM = IDLE;
Modes_enum nextStateM = IDLE;

/* initializing current and next state with No error */
Error_enum currStateE = NOERROR;
Error_enum nextStateE = NOERROR;

Type_Error_enum errorType = ERROR_PrechargeFB;

/***************************************************************************
 *								Global Variables						   *
 ***************************************************************************/

/* Declaring an array to store the brake values from two different sensors
 * ADC_values[0] -> apps1, ADC_values[1]->apps2 , ADC_values[2]->brakes angle sensor
 * */
uint16_t ADC_values[3];

/* Declaring an array to store a massage to be sent by the UART
 * ex: "Value of 0 = 5000 , Value of 1 = 6000"
 * */
char UART_massage[100];
char UART_massage_2[100];
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart3;

/***************************************************************************
 *								Function Definitions  					   *
 ***************************************************************************/
/* Description:
 * This function reads the ADC value of the first pedal 10 times and gets
 * its average to eliminate error in the reading
 */
uint16_t uint16_t_Read_APPS1()
{
	uint16_t apps1_read=0; /* variable to store the sum of the readings */

	/* read the ADC value 10 times*/
	for(int i=0;i<10;i++)
	{
		apps1_read+=ADC_values[APP1];
	}

	/* return the average */
	return (apps1_read/10);

}

/* Description:
 * This function reads the ADC value of the second pedal 10 times and gets
 * its average to eliminate error in the reading
 */
uint16_t uint16_t_Read_APPS2()
{
	uint16_t apps2_read=0;/* variable to store the sum of the readings */

	/* read the ADC value 10 times*/
	for(int i=0;i<10;i++)
	{
		apps2_read+=ADC_values[APP2];
	}

	/* return the average */
	return (apps2_read/10);

}

/* Description:
 * 1. This function compare the ADC value of the first pedal with the second
 * pedal, allowing a difference less than 10% from the reading of either
 * the pedals.
 * 2. If the difference excide this value then there is an error.
 */
void Check_APPS()
{

	uint16_t apps1_read= uint16_t_Read_APPS1(); /* variable to store first pedal reading */
	uint16_t apps2_read= uint16_t_Read_APPS2(); /* variable to store second pedal reading */
	uint16_t difference; /* variable to store the difference between the two readings */

	/* check which reading is greater to subtract from it */
	if(apps1_read>apps2_read)
		difference =apps1_read-apps2_read;
	else
		difference =apps2_read-apps1_read;

	/* handle the error if the difference is greater than 10% */
	if(difference> 0.1* apps2_read || difference> 0.1* apps1_read){
		errorType = ERROR_CheckAPPS;
		//ErrorAction();
	}
}

/* Description:
 * This function to activate the drive mode under the conditions:
 * 1. RTD button has been pressed for 3 seconds
 * 2. The brake angle has a value more than a required one
 */
void Check_Activasion_Logic()
{
	/* get the time when the RTD button is pressed */
	uint32_t time_on_press=HAL_GetTick();

	/* variable to store the difference between when key is pressed and the current time */
	uint32_t time_difference=0;

	/* this while is broken when the rtd button is released before 3 seconds or the brakes
	 * pedal is released before 3 seconds */

	//value of angle brakes might be change
	while( (time_difference<3000) && (HAL_GPIO_ReadPin(RTD_BTN_GPIO_Port,RTD_BTN_Pin)) &&  (ADC_values[BRAKE_ANGLE]>VAL_BRAKE_ANGLE_RTD) )
	{
		time_difference=HAL_GetTick()-time_on_press;
	}

	/* check if the RTD button is pressed with the brakes for 3 seconds to enter the drive mode */
	if(time_difference>=3000)
	{
		/* make the RTD sound for 2 seconds */
		HAL_GPIO_WritePin(RTDS_GPIO_Port,RTDS_Pin,1);
		HAL_Delay(2000);
		HAL_GPIO_WritePin(RTDS_GPIO_Port,RTDS_Pin,0);

		/* wait until the RTD button is released to enter the drive mode */
		while(HAL_GPIO_ReadPin(RTD_BTN_GPIO_Port,RTD_BTN_Pin));

		HAL_Delay(50);

		/* Enter the drive mode */
		nextStateM=DRIVE;
	}
}


/* Description:
 * This function initialize the ADC1 with the ADC values in 3 sequences in DMA
 */
void EVMS_Init()
{
	/* Initialize ADC DMA */
	HAL_ADC_Start_DMA(&hadc1,ADC_values,3);

																										/* HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3); */
}


/* Description:
 * 1. Disable EVMS Relay
 * 2. Check on the start button if pressed so enter pre-charge state
 */
void IDLE_Func()
{
	/* Put 0 volts on the other side of the relay to complete the shutdown circuit
	 * It is normally open and the 0 closes it
	*/
	HAL_GPIO_WritePin(EVMS_RELAY_GPIO_Port,EVMS_RELAY_Pin, 0);

	/*if the start button is not pressed then the next state is still IDLE state */
	if(! HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin))
	{
		/* still in idle state */
		nextStateM=IDLE;
	}
	/* if the start button is pressed then the next state is pre-charge state */
	else if(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin))
	{
		/* wait until the driver releases his hand from the start button */
		while(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin));

		/* wait for button de-bouncing */
		HAL_Delay(50);

		/* enter the pre-charge state */
		nextStateM=PRECHARGE;
	}

	/* store the new state to set the required state in the loop */
	currStateM=nextStateM;

}

/* Description:
 * 1. Enable pre-charge Relay to start charging the battery
 * 2. Check on the start button if pressed so enter pre-charge state
 */
void PRECHARGE_Func()
{
	/* Enable the pre-charge relay of the bamocar */
	HAL_GPIO_WritePin(PRECHARGE_RELAY_GPIO_Port,PRECHARGE_RELAY_Pin,1);

	/* Delay to make sure that the relay had time to act */
	HAL_Delay(50);

	/*read the feedback from the precharge relay to see if it is closed or not  */
	if(HAL_GPIO_ReadPin(PRE_CHARGE_FB_GPIO_Port,PRE_CHARGE_FB_Pin)== 0)
	{
		/* if the pre-charge relay is not closed then the relay or its connection has a problem
		 * so call the ERROR function */
		errorType = ERROR_PrechargeFB;
		//ErrorAction();
	}

	/* Check for the DC90 from bamocar. so that, if it is high then the inverter is pre-charged
	 * and go to neutral state
	 */
	if(HAL_GPIO_ReadPin(DC90_INPUT_GPIO_Port,DC90_INPUT_Pin))
	{
		/* enter the neutral state */
		nextStateM=NEUTRAL;

																    //hnzbtha 3la 7sb ana bigely 95% emta
																	//htt7l mn el inverter nafso
		HAL_Delay(30);

	}

	/* else the inverter is still in the pre-charging to reach 90% */
	else   
	{
		/* still in the pre-charge state */
		nextStateM=PRECHARGE;
	}

	/* store the new state to set the required state in the loop */
	currStateM=nextStateM;
}

/* Description:
 * 1. Disable pre-charge relay to stop charging the battery
 * 2. Enable AIR positive relay
 * 3. Check on the feedback of the pre-charge, AIR positive and AIR negative to avoid errors
 * 4. Check on the difference between pedals sensors to avoid errors
 * 5. Check the activation logic to go to the drive mode if happened
 */
void NEUTRAL_Func()
{
	/* Enable the AIR positive relay */
	HAL_GPIO_WritePin(AIR_POSITIVE_GPIO_Port,AIR_POSITIVE_Pin,1);

	HAL_Delay(50);

	/* Disable the pre-charge relay, as the inverter is charged now */
	HAL_GPIO_WritePin(PRECHARGE_RELAY_GPIO_Port,PRECHARGE_RELAY_Pin,0);

	/* A delay to make sure that the relays had time to act */
	HAL_Delay(50);

	/* if the pre-charge relay is enabled, then the relay or its connection has a problem. So, call ERROR function. */
	if(HAL_GPIO_ReadPin(PRE_CHARGE_FB_GPIO_Port,PRE_CHARGE_FB_Pin)== 1)
	{
		errorType = ERROR_PrechargeFB;
		//ErrorAction();
	}

	/* if the AIR positive relay is disabled then there is a a problem in the relay or its connection. So, call ERROR function. */
	if(HAL_GPIO_ReadPin(AIR_POSITIVE_FB_GPIO_Port,AIR_POSITIVE_FB_Pin)==0)
	{
		errorType = ERROR_AIRposFB;
		//ErrorAction();
	}

	/* if the AIR negative relay is disabled then there is a a problem in the relay or its connection. So, call ERROR function. */
	if(HAL_GPIO_ReadPin(AIR_NEGATIVE_FB_GPIO_Port,AIR_NEGATIVE_FB_Pin)==0)
	{
		errorType = ERROR_AIRnegFB;
		//ErrorAction();
	}

	/* check the difference between the reading of the two pedals that is less than 10% to avoid any error*/
	Check_APPS();

	/* if the start button is pressed go to discharge state */
	if(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin))
	{
		/* wait until the driver release the button */
		while(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin));

		/* delay for button de-bouncing */
		HAL_Delay(50);

		/* enter the discharge state */
		nextStateM=DISCHARGE;
	}

	/* if the RTD button is pressed and the brake angle is more than the required value then go to the activation logic */
	if(HAL_GPIO_ReadPin(RTD_BTN_GPIO_Port,RTD_BTN_Pin) && ADC_values[BRAKE_ANGLE]>VAL_BRAKE_ANGLE_RTD) 										/* w hna hzwd else if */
	{	
		/* go check the RTD button pressed time and the brake angle to enter the drive mode */
		Check_Activasion_Logic();

	}
	else
	{
		/* still in the neutral state */
		nextStateM=NEUTRAL;
	}

	/* store the new state to set the required state in the loop */
	currStateM=nextStateM;
}

/* Description:
 * 1. Enable the motor inverter
 * 2. Check on the difference between pedals sensors to avoid errors
 * 3. Generating PWM signal according to first pedal sensor average read
 * 4. Check on the feedback of the AIR negative to avoid errors
 * 5. Check if the start button is pressed to go to the discharge state
 */
void DRIVE_Func()
{
	/* Enables the motor inverter by enabling the RFE and Drive pins */
	HAL_GPIO_WritePin(RFE_ENABLE_GPIO_Port,RFE_ENABLE_Pin,1);
	HAL_GPIO_WritePin(DRIVE_ENABLE_GPIO_Port,DRIVE_ENABLE_Pin,1);

	/* check the difference between the reading of the two pedals that is less than 10% to avoid any error */
	Check_APPS();

	/* variable to store the average of the first pedal reading */
	uint16_t APPS_READ=uint16_t_Read_APPS1();

	//MAPS The ADC READ TO PWM OUTPUT VALUE
	APPS_READ = map(APPS_READ, APPS_MIN, APPS_MAX, 0, PWM_MAX_OUTPUT);


	/* Output the torque command as PWM
	 * where value in ARR register = 5000*/
	TIM3->CCR3 = APPS_READ;

	/* Store the updated ADC values of the two pedals in a string */
	sprintf(UART_massage, "%c \n", "D");
	/* Transmit the message by the UART*/
	HAL_UART_Transmit(&huart3, UART_massage, sizeof(UART_massage), 1);

	HAL_UART_Transmit(&huart3, APPS_READ, sizeof(APPS_READ), 1);

	/* if the AIR negative relay is disabled then there is a a problem in the relay or its connection. So, call ERROR function. */
	if(HAL_GPIO_ReadPin(AIR_NEGATIVE_FB_GPIO_Port,AIR_NEGATIVE_FB_Pin)==0)
	{
		errorType = ERROR_AIRnegFB;
		//ErrorAction();
	}

	/* if the start button is pressed go to discharge state */
	if(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin))
	{
		/* wait until the driver release the button */
		while(HAL_GPIO_ReadPin(START_BTN_GPIO_Port,START_BTN_Pin));

		/* delay for button de-bouncing */
		HAL_Delay(50);

		/* stop the PWM */
		TIM3->CCR3 = 0;

		/* enter the discharge state */
		nextStateM=DISCHARGE;

	}

	else
	{
		/* still in the drive state */
		nextStateM=DRIVE;
	}

	/* store the new state to set the required state in the loop */
	currStateM=nextStateM;


}

/* Description:
 * 1. Enable EVMS relay to discharge the battery
 * 2. Disable the inverter
 * 3. Disable AIR positive relay
 * 4. Check on the feedback of the AIR positive and AIR negative to avoid errors
 * 5. check on the DC60 signal to whether go IDLE or not
 */
void DISCHARGE_Func()
{
	/* Enable EVMS relay to discharge the battery */
	HAL_GPIO_WritePin(EVMS_RELAY_GPIO_Port,EVMS_RELAY_Pin,1);

	/* Disable the inverter by disable RFE and Drive pins*/
	HAL_GPIO_WritePin(RFE_ENABLE_GPIO_Port,RFE_ENABLE_Pin,0);
	HAL_GPIO_WritePin(DRIVE_ENABLE_GPIO_Port,DRIVE_ENABLE_Pin,0);


	/* Disable the AIR positive relay */
	HAL_GPIO_WritePin(AIR_POSITIVE_GPIO_Port,AIR_POSITIVE_Pin,0);
	/* Delay to make sure that the relay had time to act */
	HAL_Delay(50);

	/* if the AIR positive relay is enabled then there is a a problem in the relay or its connection. So, call ERROR function. */
	if(HAL_GPIO_ReadPin(AIR_POSITIVE_FB_GPIO_Port,AIR_POSITIVE_FB_Pin)==1)
	{
		errorType = ERROR_AIRposFB;
		//ErrorAction();
	}

	/* if the AIR negative relay is enabled then there is a a problem in the relay or its connection. So, call ERROR function. */
	if(HAL_GPIO_ReadPin(AIR_NEGATIVE_FB_GPIO_Port,AIR_NEGATIVE_FB_Pin)==1)
	{
		errorType = ERROR_AIRnegFB;
		//ErrorAction();
	}

	/* if DC60 is high then go to IDLE state */

//	if(HAL_GPIO_ReadPin(DC60_INPUT_GPIO_Port, DC60_INPUT_Pin))																				 /*will be re-configured*/
//	{
//		/* enter the IDLE state */
//		nextStateM=IDLE;
//	}
//	else
//	{
//		/* still in the discharge state */
//		nextStateM=DISCHARGE;
//	}
	HAL_Delay(5000);

	nextStateM = IDLE;


	/* store the new state to set the required state in the loop */
	currStateM=nextStateM;

}


/* Description:
 * 1. Transmit a message with the ADC values by the UART
 * 2. Switch to the required state
 */
void loop()
{
	/* Store the updated ADC values of the two pedals in a string */
	//sprintf(UART_massage, "%d\n", "S");
	/* Transmit the message by the UART*/
	//HAL_UART_Transmit(&huart3, UART_massage, sizeof(UART_massage), 1);
	sprintf(UART_massage, "%d\n", currStateM);
	HAL_UART_Transmit(&huart3, UART_massage, sizeof(UART_massage), 1);


	/* Go to the required state depending on the value in the current state */
	switch(currStateM)
	{
	case IDLE:
		IDLE_Func();
		break;

	case PRECHARGE:
		PRECHARGE_Func();
		break;

	case NEUTRAL:
		NEUTRAL_Func();
		break;

	case DRIVE:
		DRIVE_Func();
		break;

	case DISCHARGE:
		DISCHARGE_Func();
		break;
	}

}


/* Description:
 * 1. Enable EVMS relay to open the shutdown circuit
 */
void ErrorAction()
{
	/* open the shutdown circuit and go in infinite loop */
	HAL_GPIO_WritePin(EVMS_RELAY_GPIO_Port,EVMS_RELAY_Pin, 1);

	/* perform the discharge function without going to discharge state */
	HAL_GPIO_WritePin(EVMS_RELAY_GPIO_Port,EVMS_RELAY_Pin,1);
	HAL_GPIO_WritePin(RFE_ENABLE_GPIO_Port,RFE_ENABLE_Pin,0);
	HAL_GPIO_WritePin(DRIVE_ENABLE_GPIO_Port,DRIVE_ENABLE_Pin,0);
	HAL_GPIO_WritePin(AIR_POSITIVE_GPIO_Port,AIR_POSITIVE_Pin,0);


	/* Store the updated ADC values of the two pedals in a string */
    int buf_len = sprintf(UART_massage, "E");
    HAL_UART_Transmit(&huart3, (char*)UART_massage, buf_len, 100);

    switch (errorType){

    case NO_TYPE_ERROR     :
        buf_len = sprintf(UART_massage,"0");
        HAL_UART_Transmit(&huart3, (char*)UART_massage, buf_len, 100);
    	break;
    case ERROR_CheckAPPS   :
        buf_len = sprintf(UART_massage, "1");
        HAL_UART_Transmit(&huart3, (char*)UART_massage, buf_len, 100);
    	break;
    case ERROR_PrechargeFB :
        buf_len = sprintf(UART_massage, "2");
        HAL_UART_Transmit(&huart3, (char*)UART_massage, buf_len, 100);
    	break;
    case ERROR_AIRposFB    :
        buf_len = sprintf(UART_massage, "3");
        HAL_UART_Transmit(&huart3, (char*)UART_massage, buf_len, 100);
    	break;
    case ERROR_AIRnegFB    :
        buf_len = sprintf(UART_massage, "4");
        HAL_UART_Transmit(&huart3, (char*)UART_massage, buf_len, 100);
    	break;
    }

	while(1);
}
