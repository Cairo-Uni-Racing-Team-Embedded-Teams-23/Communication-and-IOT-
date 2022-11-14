/*******************************************************************************
 *
 * 	Module			: CAN BUS
 *
 * 	File Name		: CAN_config.h
 *
 * 	Author			:
 *
 *	Date 			:
 *
 *	Version			: v1.0
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define CAN_OLD_VECTORS 1
#define CAN_NEW_VECTORS 0
/**
 * ______ CAN interrupt handlers _______ 
 * 	Available options:
 * 				CAN_OLD_VECTORS
 * 				CAN_NEW_VECTORS
 */

#define CAN_VECTORS CAN_NEW_VECTORS


#define CAN_NORMAL_MODE 0b00
#define CAN_LOOP_BACK_MODE 0b01
#define CAN_SILENT_MODE 0b10
#define CAN_LOOP_BACK_SILENT_MODE 0b11

/*
	_________ CAN 1 Configurations _______________


*/

#define CAN1_FIFO_PRIORITY DISABLE
#define CAN1_RECEIVE_FIFO_LOCKED_MODE DISABLE
#define CAN1_NO_AUTOMATIC_RETRANSMISSION DISABLE
#define CAN1_AUTOMATIC_WAKE_UP_MODE DISABLE
#define CAN1_AUTOMATIC_BUS_OFF DISABLE
#define CAN1_TIME_TRIGGERED_COMMUNICATION_MODE DISABLE

//          Timing Parameters

/*

			CAN_MODE :
			Values 	 :
				CAN_NORMAL_MODE
				CAN_SILENT_MODE 			(DEBUGGING)
				CAN_LOOP_BACK_MODE 			(DEBUGGING)
				CAN_LOOP_BACK_SILENT_MODE	(DEBUGGING)
*/

#define CAN1_MODE CAN_LOOP_BACK_SILENT_MODE

#define CAN1_RESYNC_JUMP_WIDTH 0x01
#define CAN1_TIME_SEGMENT_1 0x0D
#define CAN1_TIME_SEGMENT_2 0x02
#define CAN1_BAUD_RATE_PRESCALER 1

/*
	_________ CAN 2 Configurations _______________


*/
/*
	The CAN Bus Parameters
		Values :
				ENABLE
				DISABLE

*/
#define CAN2_FIFO_PRIORITY ENABLE
#define CAN2_RECEIVE_FIFO_LOCKED_MODE ENABLE
#define CAN2_NO_AUTOMATIC_RETRANSMISSION DISABLE
#define CAN2_AUTOMATIC_WAKE_UP_MODE ENABLE
#define CAN2_AUTOMATIC_BUS_OFF DISABLE
#define CAN2_TIME_TRIGGERED_COMMUNICATION_MODE ENABLE

//          Timing Parameters

/*

			CAN_MODE :
			Values 	 :
				CAN_NORMAL_MODE
				CAN_SILENT_MODE 			(DEBUGGING)
				CAN_LOOP_BACK_MODE 			(DEBUGGING)
				CAN_LOOP_BACK_SILENT_MODE	(DEBUGGING)
*/

#define CAN2_MODE CAN_NORMAL_MODE

#define CAN2_RESYNC_JUMP_WIDTH 0x01
#define CAN2_TIME_SEGMENT_1 0x0D
#define CAN2_TIME_SEGMENT_2 0x02
#define CAN2_BAUD_RATE_PRESCALER 1

/*

		Filter Configurations


*/
