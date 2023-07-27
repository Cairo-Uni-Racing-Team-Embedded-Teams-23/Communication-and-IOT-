/*******************************************************************************
 *																				*
 * 	Module			: RCC														*
 *																				*
 * 	File Name		: RCC_interface.h											*
 *																				*
 * 	Author			: Hazem Montasser   										*
 *																				*
 *	Date 			: 12/10/2022												*
 *																				*
 *	Version			: v1.0														*
 * 																				*
 *******************************************************************************/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#include "../../LIB/STD_TYPES.h"
/**
 *
 */
typedef enum
{
	AHB,  //!< AHB
	APB1, //!< APB1
	APB2  //!< APB2
} RCC_Bus;

/**
 * @brief The available peripheral ID's on APB1
 */
typedef enum
{
	RCC_APB1_TIM2EN = 0,	//!< RCC_APB1_TIM2EN	Timer 2 clock enable
	RCC_APB1_TIM3EN = 1,	//!< RCC_APB1_TIM3EN Timer 3 clock enable
	RCC_APB1_TIM4EN = 2,	//!< RCC_APB1_TIM4EN Timer 4 clock enable
	RCC_APB1_TIM5EN = 3,	//!< RCC_APB1_TIM5EN Timer 5 clock enable
	RCC_APB1_TIM6EN = 4,	//!< RCC_APB1_TIM6EN Timer 6 clock enable
	RCC_APB1_TIM7EN = 5,	//!< RCC_APB1_TIM7EN Timer 7 clock enable
	RCC_APB1_TIM12EN = 6,	//!< RCC_APB1_TIM12EN Timer 12 clock enable
	RCC_APB1_TIM13EN = 7,	//!< RCC_APB1_TIM13EN Timer 13 clock enable
	RCC_APB1_TIM14EN = 8,	//!< RCC_APB1_TIM14EN Timer 14 clock enable
	RCC_APB1_WWDGEN = 11,	//!< RCC_APB1_WWDGEN Window Watchdog clock enable
	RCC_APB1_SPI2EN = 14,	//!< RCC_APB1_SPI2EN SPI 2 clock enable
	RCC_APB1_SPI3EN = 15,	//!< RCC_APB1_SPI3EN SPI 3 clock enable
	RCC_APB1_USART2EN = 17, //!< RCC_APB1_USART2EN USART 2 clock enable
	RCC_APB1_USART3EN = 18, //!< RCC_APB1_USART3EN USART 3 clock enable
	RCC_APB1_USART4EN = 19, //!< RCC_APB1_USART4EN USART 4 clock enable
	RCC_APB1_USART5EN = 20, //!< RCC_APB1_USART5EN USART 5 clock enable
	RCC_APB1_I2C1EN = 21,	//!< RCC_APB1_I2C1EN I2C 1 clock enable
	RCC_APB1_I2C2EN = 22,	//!< RCC_APB1_I2C2EN I2C 2 clock enable
	RCC_APB1_USBEN = 23,	//!< RCC_APB1_USBEN USB clock enable
	RCC_APB1_CANEN = 25,	//!< RCC_APB1_CANEN CAN clock enable
	RCC_APB1_BKPEN = 27,	//!< RCC_APB1_BKPEN Backup clock enable
	RCC_APB1_PWREN = 28,	//!< RCC_APB1_PWREN Power clock enable
	RCC_APB1_DACEN = 29		//!< RCC_APB1_DACEN DAC clock enable
} RCC_APB1;
/**
 * @brief The available peripheral ID's on APB2
 */
typedef enum
{
	RCC_APB2_AFIOEN = 0,	//!< RCC_APB2_AFIOEN Alternate Function clock enable
	RCC_APB2_IOPAEN = 2,	//!< RCC_APB2_IOPAEN GPIO Port A clock enable
	RCC_APB2_IOPBEN = 3,	//!< RCC_APB2_IOPBEN GPIO Port B clock enable
	RCC_APB2_IOPCEN = 4,	//!< RCC_APB2_IOPCEN GPIO Port C clock enable
	RCC_APB2_IOPDEN = 5,	//!< RCC_APB2_IOPDEN GPIO Port D clock enable
	RCC_APB2_IOPEEN = 6,	//!< RCC_APB2_IOPEEN GPIO Port E clock enable
	RCC_APB2_IOPFEN = 7,	//!< RCC_APB2_IOPFEN GPIO Port F clock enable
	RCC_APB2_IOPGEN = 8,	//!< RCC_APB2_IOPGEN GPIO Port G clock enable
	RCC_APB2_ADC1EN = 9,	//!< RCC_APB2_ADC1EN ADC 1 clock enable
	RCC_APB2_ADC2EN = 10,	//!< RCC_APB2_ADC2EN ADC 2 clock enable
	RCC_APB2_TIM1EN = 11,	//!< RCC_APB2_TIM1EN Timer 1 clock enable
	RCC_APB2_SPI1EN = 12,	//!< RCC_APB2_SPI1EN SPI 1 clock enable
	RCC_APB2_TIM8EN = 13,	//!< RCC_APB2_TIM8EN Timer 8 clock enable
	RCC_APB2_USART1EN = 14, //!< RCC_APB2_USART1EN USART 1 clock enable
	RCC_APB2_ADC3EN = 15,	//!< RCC_APB2_ADC3EN ADC 3 clock enable
	RCC_APB2_TIM9EN = 19,	//!< RCC_APB2_TIM9EN Timer 9 clock enable
	RCC_APB2_TIM10EN = 20,	//!< RCC_APB2_TIM10EN Timer 10 clock enable
	RCC_APB2_TIM11EN = 21,	//!< RCC_APB2_TIM11EN Timer 11 clock enable

} RCC_APB2;

/**
 * @brief MCO clock source
 */
typedef enum
{
	RCC_MCO_Src_SYSCLK = (0x4),	   //!< RCC_MCO_Src_SYSCLK System clock
	RCC_MCO_Src_HSI = (0x5),	   //!< RCC_MCO_Src_HSI 	   High Speed Internal clock
	RCC_MCO_Src_HSE = (0x6),	   //!< RCC_MCO_Src_HSE	   High Speed External clock
	RCC_MCO_Src_PLL_DIV_2 = (0x7), //!< RCC_MCO_Src_PLL_DIV_2 PLL clock divided by 2
	RCC_MCO_Src_Disable = (0x0)	   //!< RCC_MCO_Src_Disable   Disabled (no o/p on pin)
} RCC_MCOOutput;
/**
 * @enum RCC_SystemClockSource_t
 * @brief Defines the system clock source
 *
 */
typedef enum
{
	RCC_SystemClockSource_HSI = 0b00, /**< RCC_SystemClockSource_HSI */
	RCC_SystemClockSource_HSE = 0b01, /**< RCC_SystemClockSource_HSE */
	RCC_SystemClockSource_PLL = 0b10, /**< RCC_SystemClockSource_PLL */
	RCC_SystemClockSource_NA = 0b11	  /**< RCC_SystemClockSource_NA */
} RCC_SystemClockSource_t;

/**
 * @brief Initializes the system clock according to the selected system clock in RCC_config.h
 * @note  Selected clock sources must be from the available options/values
 */
void RCC_voidInitSysClock(void);

/**
 * @brief Enables the specified peripheral clock on the bus.
 *
 *
 * @param Copy_u8BusId Bus ID, selected from RCC_Bus enum
 * @param Copy_u8PerId Peripheral ID, selected from RCC_APBx enums
 *
 * @note If the bus ID's are not within the enum values, the function does nothing.
 * @note If the peripheral ID is greater than 31, the function does nothing.
 */
void RCC_voidEnableClock(RCC_Bus Copy_u8BusId, u8 Copy_u8PerId);

/**
 * @brief Disables the specified peripheral clock on the bus.
 *
 * @param Copy_u8BusId Bus ID, selected from RCC_Bus enum
 * @param Copy_u8PerId Peripheral ID, selected from RCC_APBx enums
 *
 * @note If the bus ID's are not within the enum values, the function does nothing.
 * @note If the peripheral ID is greater than 31, the function does nothing.
 */
void RCC_voidDisableClock(RCC_Bus Copy_u8BusId, u8 Copy_u8PerId);

/**
 * @brief Enables clock output on MCO pin according to the selected mode.
 *
 * @param mco_mode MCO selected clock. Can be selected from RCC_MCOOutput enum.
 */
void RCC_configMCO(RCC_MCOOutput mco_mode);

/**
 * @fn u32 RCC_getSystemCoreSource()
 * @brief Returns the system core clock source.
 *
 * @return	RCC_SystemClockSource_t
 */
RCC_SystemClockSource_t RCC_getSystemCoreSource();

/**
 * @fn u32 RCC_getSystemCoreClock()
 * @brief Returns the system core clock that is currently configured in hertz.
 *
 * @return	System core clock
 */
u32 RCC_getSystemCoreClock();

#endif
