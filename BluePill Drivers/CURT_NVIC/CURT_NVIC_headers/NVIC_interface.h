/**
 * @file NVIC_interface.h
 * @author Hazem Montasser
 * @brief Interface file for NVIC functions.
 * @note See NVIC_config.h to correctly setup the driver.
 * @version 0.1
 * @date 2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

/*******************************************************************************
 *                       Includes                                              *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                       Type definitions                                      *
 *******************************************************************************/

/**
 * @enum
 * @brief	Defines all interrupt numbers in STM32F10x
 *
 */
typedef enum
{
	IRQ_NMI = -14,			 /**< IRQ_NMI */
	IRQ_Hard_Fault = -13,	 /**< IRQ_Hard_Fault */
	IRQ_MemManage = -12,	 /**< IRQ_MemManage */
	IRQ_Bus_Fault = -11,	 /**< IRQ_Bus_Fault */
	IRQ_Usage_Fault = -10,	 /**< IRQ_Usage_Fault */
	IRQ_SVCall = -5,		 /**< IRQ_SVCall */
	IRQ_PendSV = -2,		 /**< IRQ_PendSV */
	IRQ_Systick = -1,		 /**< IRQ_Systick */
	IRQ_WWDG = 0,			 /**< IRQ_WWDG */
	IRQ_PVD = 1,			 /**< IRQ_PVD */
	IRQ_TAMPER = 2,			 /**< IRQ_TAMPER */
	IRQ_RTC = 3,			 /**< IRQ_RTC */
	IRQ_FLASH = 4,			 /**< IRQ_FLASH */
	IRQ_RCC = 5,			 /**< IRQ_RCC */
	IRQ_EXTI0 = 6,			 /**< IRQ_EXTI0 */
	IRQ_EXTI1 = 7,			 /**< IRQ_EXTI1 */
	IRQ_EXTI2 = 8,			 /**< IRQ_EXTI2 */
	IRQ_EXTI3 = 9,			 /**< IRQ_EXTI3 */
	IRQ_EXTI4 = 10,			 /**< IRQ_EXTI4 */
	IRQ_DMA1_Channel1 = 11,	 /**< IRQ_DMA1_Channel1 */
	IRQ_DMA1_Channel2 = 12,	 /**< IRQ_DMA1_Channel2 */
	IRQ_DMA1_Channel3 = 13,	 /**< IRQ_DMA1_Channel3 */
	IRQ_DMA1_Channel4 = 14,	 /**< IRQ_DMA1_Channel4 */
	IRQ_DMA1_Channel5 = 15,	 /**< IRQ_DMA1_Channel5 */
	IRQ_DMA1_Channel6 = 16,	 /**< IRQ_DMA1_Channel6 */
	IRQ_DMA1_Channel7 = 17,	 /**< IRQ_DMA1_Channel7 */
	IRQ_ADC1_2 = 18,		 /**< IRQ_ADC1_2 */
	IRQ_USB_HP_CAN_TX = 19,	 /**< IRQ_USB_HP_CAN_TX */
	IRQ_USB_LP_CAN_RX0 = 20, /**< IRQ_USB_LP_CAN_RX0 */
	IRQ_CAN_RX1 = 21,		 /**< IRQ_CAN_RX1 */
	IRQ_CAN_SCE = 22,		 /**< IRQ_CAN_SCE */
	IRQ_EXTI9_5 = 23,		 /**< IRQ_EXTI9_5 */
	IRQ_TIM1_BRK = 24,		 /**< IRQ_TIM1_BRK */
	IRQ_TIM1_UP = 25,		 /**< IRQ_TIM1_UP */
	IRQ_TIM1_TRG_COM = 26,	 /**< IRQ_TIM1_TRG_COM */
	IRQ_TIM1_CC = 27,		 /**< IRQ_TIM1_CC */
	IRQ_TIM2 = 28,			 /**< IRQ_TIM2 */
	IRQ_TIM3 = 29,			 /**< IRQ_TIM3 */
	IRQ_TIM4 = 30,			 /**< IRQ_TIM4 */
	IRQ_I2C1_EV = 31,		 /**< IRQ_I2C1_EV */
	IRQ_I2C1_ER = 32,		 /**< IRQ_I2C1_ER */
	IRQ_I2C2_EV = 33,		 /**< IRQ_I2C2_EV */
	IRQ_I2C2_ER = 34,		 /**< IRQ_I2C2_ER */
	IRQ_SPI1 = 35,			 /**< IRQ_SPI1 */
	IRQ_SPI2 = 36,			 /**< IRQ_SPI2 */
	IRQ_USART1 = 37,		 /**< IRQ_USART1 */
	IRQ_USART2 = 38,		 /**< IRQ_USART2 */
	IRQ_USART3 = 39,		 /**< IRQ_USART3 */
	IRQ_EXTI15_10 = 40,		 /**< IRQ_EXTI15_10 */
	IRQ_RTCAlarm = 41,		 /**< IRQ_RTCAlarm */
	IRQ_TIM8_BRK = 42,		 /**< IRQ_TIM8_BRK */
	IRQ_TIM8_UP = 43,		 /**< IRQ_TIM8_UP */
	IRQ_TIM8_TRG_COM = 44,	 /**< IRQ_TIM8_TRG_COM */
	IRQ_TIM8_CC = 45,		 /**< IRQ_TIM8_CC */
	IRQ_ADC3 = 46,			 /**< IRQ_ADC3 */
	IRQ_FSMC = 47,			 /**< IRQ_FSMC */
	IRQ_SDIO = 48,			 /**< IRQ_SDIO */
	IRQ_TIM5 = 49,			 /**< IRQ_TIM5 */
	IRQ_SPI3 = 50,			 /**< IRQ_SPI3 */
	IRQ_UART4 = 51,			 /**< IRQ_UART4 */
	IRQ_UART5 = 52,			 /**< IRQ_UART5 */
	IRQ_TIM6 = 53,			 /**< IRQ_TIM6 */
	IRQ_TIM7 = 54,			 /**< IRQ_TIM7 */
	IRQ_DMA2_Channel1 = 55,	 /**< IRQ_DMA2_Channel1 */
	IRQ_DMA2_Channel2 = 56,	 /**< IRQ_DMA2_Channel2 */
	IRQ_DMA2_Channel3 = 57,	 /**< IRQ_DMA2_Channel3 */
	IRQ_DMA2_Channel4_5 = 58 /**< IRQ_DMA2_Channel4_5 */

} IRQn_t;

/**
 * @enum
 * @brief	Defines priority groups available in STM32F10x
 *
 */
typedef enum
{
	IRQPGroup_3 = 0b011, /**< IRQPGroup_3 */
	IRQPGroup_4 = 0b100, /**< IRQPGroup_4 */
	IRQPGroup_5 = 0b101, /**< IRQPGroup_5 */
	IRQPGroup_6 = 0b110, /**< IRQPGroup_6 */
	IRQPGroup_7 = 0b111	 /**< IRQPGroup_7 */
} IRQPgroup_t;

/*******************************************************************************
 *                       Public functions declarations                         *
 *******************************************************************************/

/************* Global interrupts functions  *************/

/**
 * @fn void NVIC_enableInterrupts()
 * @brief	Enables interrupts globally by resetting the PRIMASK register.
 *
 *
 */
void NVIC_enableInterrupts();

/**
 * @fn void NVIC_disableInterrupts()
 * @brief	Disables interrupts globally by setting the PRIMASK register.
 *			Hard faults & NMIs are not disabled.
 */
void NVIC_disableInterrupts();

/**
 * @fn void NVIC_init()
 * @brief	Initializes the interrupt vector table by setting its offset and
 * 		specifying its location (code/SRAM)
 *
 */
void NVIC_init();

/************* Priority grouping *************/

/**
 * @fn void NVIC_setPriorityGrouping(IRQPgroup_t)
 * @brief	Sets the priority grouping.
 *
 * @param priorityGroup	Priority group to set
 */
void NVIC_setPriorityGrouping(IRQPgroup_t priorityGroup);

/************* Specific IRQ functions *************/

/**
 * @fn void NVIC_enableIRQ(IRQn_t)
 * @brief	Enables the given interrupt
 * @note If its not a valid interrupt, the function does nothing.
 *
 * @param IRQn	Number of the interrupt to enable
 */
void NVIC_enableIRQ(IRQn_t IRQn);

/**
 * @fn void NVIC_disableIRQ(IRQn_t)
 * @brief	Disables the given interrupt
 * @note If its not a valid interrupt, the function does nothing.
 *
 * @param IRQn	Number of the interrupt to disable
 */
void NVIC_disableIRQ(IRQn_t IRQn);

/**
 * @fn u32 getEnableIRQ(IRQn_t)
 * @brief	Returns whether or not the given interrupt is enabled or not
 *
 * @param IRQn	Number of interrupt
 * @return 0 If interrupt is disabled or invalid IRQn
 * @return 1 If interrupt is enabled
 */
u32 getEnableIRQ(IRQn_t IRQn);
/**
 * @fn u32 getActiveIRQ(IRQn_t)
 * @brief	Returns whether or not the given interrupt is pending/active
 *
 * @param IRQn	Number of interrupt
 * @return	0 If the interrupt is not active/pending or invaldi IRQn
 * @return	1 If the interrupt is active/pending
 *
 */
u32 getActiveIRQ(IRQn_t IRQn);

/************* Priority functions *************/
/**
 * @fn void NVIC_setPriority(IRQn_t, u32)
 * @brief	Sets the priority for the given interrupt
 *
 * @param IRQn	Interrupt number
 * @param priority	Priority of the interrupt to set
 */
void NVIC_setPriority(IRQn_t IRQn, u32 priority);

/**
 * @fn u32 NVIC_getPriority(IRQn_t)
 * @brief	Returns the priority of the given interrupt
 *
 * @param IRQn	Interrupt number
 * @return	u32 Interrupt priority
 */
u32 NVIC_getPriority(IRQn_t IRQn);

/**
 * @fn void NVIC_setPendingIRQ(IRQn_t)
 * @brief	Sets the given interrupt as pending in the NVIC.
 * @note 	The given interrupt is added to pending interrupts in the NVIC,
 * 	and it will be executed once NVIC queues it depending on its priority.
 *
 * @param IRQn	Interrupt number
 */
void NVIC_setPendingIRQ(IRQn_t IRQn);

/**
 * @fn u32 NVIC_getPendingIRQ(IRQn_t)
 * @brief	Returns whether or not an interrupt is pending
 *
 * @param IRQn	Interrupt number
 * @return	0 Interrupt is not pending
 * @return	1 Interrupt is pending
 *
 */
u32 NVIC_getPendingIRQ(IRQn_t IRQn);

/**
 * @fn void NVIC_clearPendingIRQ(IRQn_t)
 * @brief	Removes the given interrupt from the pending queue in NVIC
 *
 * @param IRQn	Interrupt number
 */
void NVIC_clearPendingIRQ(IRQn_t IRQn);
