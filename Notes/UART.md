# USART
## Transfer modes
### 1. Blocking mode
Transmitter sends and transmission is considered to end when an expected number of bytes is received or IDLE event occurs.
### 2. Non-blocking mode
### 2.1 with end of transmission detection
Transmitter sends data and __optionally__ sends a break or idle character
	1. Idle character: A frame of 1's
		- Example: UART frame consists of 
			- Start bit (1)
			- Word bits (7-9 bits)
			- Parity bit (1)
			- Stop bit (0-2)
			-
			So for 1 start bit, 1 parity, and 1 stop bit: a frame of 1's would be 
			1_1111 1111_1_1
			s_word_parity_stop
	2. Break character: A frame period which contains zeroes and the transmitter __MUST__ send 2 stop bits
		- Example: 
			0_000 0000_0_0
		
		![[Pasted image 20220905125035.png]]

### 2.2 with ISR 
When the transmitter detects idle state for too long, UARTEx_ReceiveToIdle_IT() ISR is called


![[Pasted image 20220906133700.png]]