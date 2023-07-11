#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#include "USART_private.h"

extern u8 USART1_u8RxBuffer[];
extern u8 USART1_u8Count;
extern u8 USART2_u8RxBuffer[];
extern u8 USART2_u8Count;
extern u8 USART3_u8RxBuffer[];
extern u8 USART3_u8Count;

/* USARTx ID:	USART1
 * 				USART2
 * 				USART3
 * 				UART4
 * 				UART5
 */

/* Function to Initialize USART1 with configurations */
void MUSART_voidInit(USART_Regs *USARTx);

/* Function to send a character */
void MUSART_voidSendChar(USART_Regs *USARTx, u8 copy_u8Char);

/* Function to receive a character */
u8 MUSART_voidReceiveChar(USART_Regs *USARTx);

/* Function to Send a String */
void MUSART_voidSendString(USART_Regs *USARTx, const u8 *copy_u8String);

/* Function to Receive a String
 * It is required to create an empty array in your app
 * and pass it to this function
 */
void MUSART_voidReceiveString(USART_Regs *USARTx, u8 *copy_u8String);

/* Function to Receive an Integer
 * It converts the array from ReceiveString
 * into an integer
 */
u32 MUSART_u32ReceiveInteger(USART_Regs *USARTx, u8 *copy_u8String);

#endif /* USART_INTERFACE_H_ */