#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define USART1_BASE_ADDRESS	0x40013800
#define USART2_BASE_ADDRESS	0x40004400
#define USART3_BASE_ADDRESS	0x40004800
#define UART4_BASE_ADDRESS	0x40004C00
#define UART5_BASE_ADDRESS	0x40005000

typedef struct {
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
} USART_Regs;

#define	USART1	((volatile USART_Regs*)USART1_BASE_ADDRESS)
#define	USART2	((volatile USART_Regs*)USART2_BASE_ADDRESS)
#define	USART3	((volatile USART_Regs*)USART3_BASE_ADDRESS)
#define	UART4	((volatile USART_Regs*)UART4_BASE_ADDRESS)
#define	UART5	((volatile USART_Regs*)UART5_BASE_ADDRESS)

/* Parity Options */
#define PARITY_DISABLE          0
#define EVEN_PARITY             1
#define ODD_PARITY              2

/* Data Length options */
#define DATA_8_BITS      		0
#define DATA_9_BITS      		1

/* Stop bit options */
#define ONE_STOP_BIT            0
#define HALF_STOP_BIT           1
#define TWO_STOP_BIT            2
#define ONE_AND_HALF_STOP_BIT   3

#endif /* USART_PRIVATE_H_ */
