# CURT Communications & IoT 2023 

# CAN Driver documentation by Hazem Montasser
## Overview

This is a CAN driver implementation for the STM32F103C8 based on ARM Cortex-M3. It supports the basic CAN functions for transmitting and receiving messages and an API which simplifies CAN operation for handling filtering & messages. Basic pre-build configuration is available by changing the settings in CAN_config.h file.

## CAN Driver documentation

### File information
- In CURT_CAN_headers
	1. **CAN_interface.h**: Contains all functions for using the CAN driver, both elementary & API functions
	2. **CAN_private.h**: Contains some definitions and registers used internally within the source
	3. **CAN_config.h**: Pre-build configuration file
- In CURT_CAN_sources
	1. **CAN_source.c**: Source code for the CAN driver
---

### How to use this driver

#### Steps

0. Setting up pre-build configuration:
	- In CAN_config.h, the bit timings should be set accordingly. In these definitions we define this configuration for CAN_CONFIG_1. Everything is disabled except automatic bus off.
	```c
	#define CAN1_FIFO_PRIORITY DISABLE
	#define CAN1_RECEIVE_FIFO_LOCKED_MODE DISABLE
	#define CAN1_NO_AUTOMATIC_RETRANSMISSION DISABLE
	#define CAN1_AUTOMATIC_WAKE_UP_MODE DISABLE
	#define CAN1_AUTOMATIC_BUS_OFF ENABLE
	#define CAN1_TIME_TRIGGERED_COMMUNICATION_MODE DISABLE
	```

	- Select the mode to be normal mode.
	```c
	#define CAN1_MODE CAN_NORMAL_MODE
	```

	- Set bit timings. It must be noted that these values are from calculations not literal values. For example to get time segment 1  = 6000ns and time segment 2 = 5500ns : 
			Assume BRP = 17
			PCLK freq = 36MHz, PCLK period = 27.77 ns
			Sync jump width = 500 ns

$$\displaylines{ t_q = (BRP[9:0] + 1) * t_{PCLK}\\
t_q = (17 +1)*(27.77*10^{-9}) = 500ns\\\\
\because\ t_{BS1} = t_q * (TS1[3:0] + 1),\\
t_{BS2} = t_q * (TS2[3:0] + 1)\\
t_{RJW} = tq * (SJW[1:0] + 1)\\\\
\therefore\ TS1[3:0] = \frac{t_{BS1}}{t_q} -1,\\
TS2[3:0] = \frac{t_{BS2}}{t_q} - 1,\\\
RJW[1:0] = \frac{t_{RJW}}{t_q} - 1\\\
TS1 = \frac{6000ns}{500ns} -1  = 11\\\\
TS2 = \frac{5500ns}{500ns} - 1 = 10 \\\\
RJW = \frac{500ns}{500ns} -1 = 0
}
$$

```c
#define CAN1_RESYNC_JUMP_WIDTH 0x00
#define CAN1_TIME_SEGMENT_1 0x0B
#define CAN1_TIME_SEGMENT_2 0x0A
#define CAN1_BAUD_RATE_PRESCALER (17UL)
```

These settings yield a baud rate of 125kbit/s.

---

1. Initialize the required CAN (1 or 2) with the desired settings. There are 2 configurations available to pre-select when initializing which should be set-up as desired in CAN_config.h:
	- CAN_CONFIG_1
	- CAN_CONFIG_2
	*Note: After initialization, the CAN is in initialization mode.
```c
/* Initialize CAN1 with config 1 */
CAN_init(CAN1, CAN_CONFIG_1);
```

2. Initialize the filter as desired.
	1. Using basic functions:
	```c
	/* Filter configuartion struct*/
	CAN_FilterInitTypeDef filter_config = { 0 };
	/* Enable this filter */
	filter_config.FilterActivation = ENABLE;
	/* Filter scale, either single 32 bits or double 16 bits */
	filter_config.FilterScale = SINGLE_32;
	/* Assign this filter to RX FIFO 1/2 */
	filter_config.FilterFIFOAssignment = CAN_RX_FIFO_1;
	/* Use masking mode to filter for specific range of ID's */
	filter_config.FilterMode = MASK;

	/* Specific ID to filter on */
	filter_config.FilterIdHighR1 = 0x52;
	filter_config.FilterIdLowR1 = 0xAB;
	/* Mask which tells the filter which bits of the ID to check */
	filter_config.FilterMaskIdHigh = 0b11110000; /* Checks most significant 4 bits of the ID*/
	filter_config.FilterMaskIdLow = 0b10100000;
	
	/* Assign these settings to filter #5 */
	filter_config.FilterNumber = 5; 
	/* Initialize the filter */
	CAN_initFilter(&filter_config);
	/* Set slave(CAN2) filters to start from #14, and filters 0-13 belong to CAN1*/
	CAN_setSlaveStartBank(14);
	```
	
	*Note: The ID's and Masks assigned to the registers do not exactly map to the required device ID. For example, assigning FilterIdLowR1 and FilterIdHighR1 to 0x33 and 0x4A respectively does NOT mean that the CAN filter an ID of 0x4A33 because the mapping of these registers are not 1-1 to the bits of the ID. Therefore, it is highly recommended to use the API functions to filter for specific ID's.
	
	2. Using API functions to filter specific ID's:

```c
	/* Filter for ID's:
		0x7CD, 0x7BD,0x792 as STD identifiers
		0x3C7A2, 0x299A2 as EXT identifiers
	*/
	CAN_appendDeviceToBus(0x7CD, CAN_STANDARD_IDENTIFIER);
	CAN_appendDeviceToBus(0x7BD, CAN_STANDARD_IDENTIFIER);
	CAN_appendDeviceToBus(0x792, CAN_STANDARD_IDENTIFIER);
	CAN_appendDeviceToBus(0x3C7A2, CAN_EXTENDED_IDENTIFIER);
	CAN_appendDeviceToBus(0x299A2, CAN_EXTENDED_IDENTIFIER);
	/* Set slave(CAN2) filters to start from #14, and filters 0-13 belong to CAN1 */
	CAN_setSlaveStartBank(14);
```
*Note: Slave start bank MUST be set to use filters. *

3. Start CAN in normal mode to start reception and transmitting. The CAN needs to sense an idle state on the bus to synchronize with it before participating in it. CAN needs to see exactly 11 recessive bits on the bus.
```c
CAN_setMode(CAN1, CAN_Mode_Normal);
```
*Note: This function busy-waits until CAN is in normal mode.*

4. Send a message on CAN bus
	1. Using basic functions:
	```c
	/* Return variable which tells us which mailbox the message was inserted in */
	CAN_Tx_MailBox_TypeDef msg_mailbox = CAN_TX_NO_EMPTY_MAILBOX;
	CanTxMsg msg = {0};
	/* Data length is 5 bytes */
	msg.DLC=5;
	msg.Data[0]='A';
	msg.Data[1]='B';
	msg.Data[2]='C';
	msg.Data[3]='D';
	msg.Data[4]='E';
	/* Not a remote frame */
	msg.RTR = 0;
	/* Identifier type is extended ID */
	msg.IDE = CAN_EXTENDED_IDENTIFIER;
	/* Extended ID is 0xABCD */
	msg.ExtId = 0xABCD;
	/* Transmit message, return is the mailbox in which the message was put in*/
	msg_mailbox = CAN_transmit(CAN1, &msg);
	```

	2. Using API functions:
	```c
	/* Sends msg1 of length = 4 bytes with extended ID = 0xFCD and standard ID = 0x03F */
	u8 msg1[4] = { 0xAC, 0xF4, 0x22, 0x31 };
	CAN_sendMessage(msg1, 4, CAN_EXTENDED_IDENTIFIER, 0xFCD);
	CAN_sendMessage(msg1, 4, CAN_STANDARD_IDENTIFIER, 0x03F);
	```

5. Receive a message on CAN bus
	1. Using basic functions:
	
	```c
	CanRxMsg new_msg = {0};
	/* Receive a message from FIFO 1 */
	CAN_receive(CAN1, CAN_RX_FIFO_1, new_msg);
	/* DLC */
	u8 msg_len = new_msg.DLC;
	/* Get message ID */
	u8 msg_id = (new_msg.IDE = CAN_STANDARD_IDENTIFIER)?
			new_msg.StdId:
			new_msg.ExtId;
	/* RTR flag */
	u8 msg_rtr = new_msg.RTR;
	/* Copy message to buffer */
	u8 buffer[8] = {0};
	for(u8 i = 0; i < msg.DLC ; i++){
		buffer[i]=new_msg.Data[i];
	}
	```
	2. Using API functions:
	
	```c
	u8 CAN_Status_Typedef result = 0;
	u8 buffer[8] = 0;
	u8 msg_len = 0;
	u32 msg_id = 0;
	/* Receive message */
	result = CAN_receiveMessage(buffer, &msg_len, &msg_id);
	/* Result can be multiple errors at once which are OR'd, so we can check on individual errors*/
	if(result!=CAN_Status_OK){
		/* Handle error*/
		if(result&CAN_Status_NoMessage){
			/* Do something */
		}
	}else{
		/* Process message */
	}
	```

#### Notes
1. In low and medium density devices, where there is only CAN1, there are only 14 filter banks, so setting the slave start bank to 14 assigns all filter banks to CAN1.
2. There is a helper function to format the required ID into the filter registers:
	```c 
	u32 CAN_formatIdentifierIntoFRx(u32 a_STDID, u32 a_EXTID, CAN_Identifier_TypeDef a_idType, CAN_FilterScale a_scale, u8 a_RTR);
	```

	- Usage:

	```c
	CAN_FilterInitTypeDef filter_config = { 0 };
	/* If using EXTID: */
	u32 my_id = 0xABCD;
	u32 FRx_val = CAN_formatIdentifierIntoFRx(my_id>>18,my_id&0x3FFFF,CAN_EXTENDED_IDENTIFIER, SINGLE_32, 0);

	/* If using STID: */
	u32 my_id = 0x7A;
	u32 FRx_val = CAN_formatIdentifierIntoFRx(my_id,0,CAN_STANDARD_IDENTIFIER, SINGLE_32, 0);

	filter_config.FilterIdHighR1 = FRx_val>>16;
	filter_config.FilterIdLowR1 = FRx_val&0x0000FFFF;
	```
	
*Note: For the masking of specific bits of the ID, please refer to the datasheet.*


### TODO 
1. Make the CAN API functions work with both CAN interfaces
2. Add a return value in CAN_receive to tell if there was a message received or not instead of void return
3. Make slave select bank function modify max devices filter variable
4. API functions for masking instead of list ID's
5. Add RTR flag as return by reference in CAN_receiveMessage
