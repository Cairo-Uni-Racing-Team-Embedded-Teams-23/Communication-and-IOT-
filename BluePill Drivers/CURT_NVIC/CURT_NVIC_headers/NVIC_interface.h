#include "../../LIB/STD_TYPES.h"

typedef enum
{
	IRQ_NMI = -14,
	IRQ_Hard_Fault = -13,
	IRQ_MemManage = -12,
	IRQ_Bus_Fault = -11,
	IRQ_Usage_Fault = -10,
	IRQ_SVCall = -5,
	IRQ_PendSV = -2,
	IRQ_Systick = -1,
	IRQ_WWDG = 0,
	IRQ_PVD = 1,
	IRQ_TAMPER = 2,
	IRQ_RTC = 3,
	IRQ_FLASH = 4,
	IRQ_RCC = 5,
	IRQ_EXTI0 = 6,
	IRQ_EXTI1 = 7,
	IRQ_EXTI2 = 8,
	IRQ_EXTI3 = 9,
	IRQ_EXTI4 = 10,
	IRQ_DMA1_Channel1 = 11,
	IRQ_DMA1_Channel2 = 12,
	IRQ_DMA1_Channel3 = 13,
	IRQ_DMA1_Channel4 = 14,
	IRQ_DMA1_Channel5 = 15,
	IRQ_DMA1_Channel6 = 16,
	IRQ_DMA1_Channel7 = 17,
	IRQ_ADC1_2 = 18,
	IRQ_USB_HP_CAN_TX = 19,
	IRQ_USB_LP_CAN_RX0 = 20,
	IRQ_CAN_RX1 = 21,
	IRQ_CAN_SCE = 22,
	IRQ_EXTI9_5 = 23,
	IRQ_TIM1_BRK = 24,
	IRQ_TIM1_UP = 25,
	IRQ_TIM1_TRG_COM = 26,
	IRQ_TIM1_CC = 27,
	IRQ_TIM2 = 28,
	IRQ_TIM3 = 29,
	IRQ_TIM4 = 30,
	IRQ_I2C1_EV = 31,
	IRQ_I2C1_ER = 32,
	IRQ_I2C2_EV = 33,
	IRQ_I2C2_ER = 34,
	IRQ_SPI1 = 35,
	IRQ_SPI2 = 36,
	IRQ_USART1 = 37,
	IRQ_USART2 = 38,
	IRQ_USART3 = 39,
	IRQ_EXTI15_10 = 40,
	IRQ_RTCAlarm = 41,
	IRQ_TIM8_BRK = 42,
	IRQ_TIM8_UP = 43,
	IRQ_TIM8_TRG_COM = 44,
	IRQ_TIM8_CC = 45,
	IRQ_ADC3 = 46,
	IRQ_FSMC = 47,
	IRQ_SDIO = 48,
	IRQ_TIM5 = 49,
	IRQ_SPI3 = 50,
	IRQ_UART4 = 51,
	IRQ_UART5 = 52,
	IRQ_TIM6 = 53,
	IRQ_TIM7 = 54,
	IRQ_DMA2_Channel1 = 55,
	IRQ_DMA2_Channel2 = 56,
	IRQ_DMA2_Channel3 = 57,
	IRQ_DMA2_Channel4_5 = 58

} IRQn_t;

typedef enum
{
	IRQPGroup_3 = 0b011,
	IRQPGroup_4 = 0b100,
	IRQPGroup_5 = 0b101,
	IRQPGroup_6 = 0b110,
	IRQPGroup_7 = 0b111
} IRQPgroup_t;

inline void NVIC_enableInterrupts();
inline void NVIC_disableInterrupts();

inline void NVIC_init();
inline void NVIC_setPriorityGrouping(IRQPgroup_t priorityGroup);

inline void NVIC_enableIRQ(IRQn_t IRQn);
inline void NVIC_disableIRQ(IRQn_t IRQn);
inline u32 getEnableIRQ(IRQn_t IRQn);
inline u32 getActiveIRQ(IRQn_t IRQn);

inline void NVIC_setPriority(IRQn_t IRQn, u32 priority);
inline u32 NVIC_getPriority(IRQn_t IRQn);

inline void NVIC_setPendingIRQ(IRQn_t IRQn);
inline u32 NVIC_getPendingIRQ(IRQn_t IRQn);
inline void NVIC_clearPendingIRQ(IRQn_t IRQn);
