/**
 * @file NVIC_reg.h
 * @author Hazem Montasser
 * @brief Header file which defines registers & addresses used in the driver source
 * @version 0.1
 * @date 2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

/*******************************************************************************
 *                        Includes                                             *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                        Type definitions                                     *
 *******************************************************************************/

/**
 * @struct
 * @brief   Memory map struct used to access NVIC registers
 *
 */
typedef struct
{
    volatile u32 ISER[8U]; /*!<Interrupt Set Enable Register */
    volatile u32 RESERVED0[24U];
    volatile u32 ICER[8U]; /*!< Interrupt Clear Enable Register */
    volatile u32 RESERVED1[24U];
    volatile u32 ISPR[8U]; /*!< Interrupt Set Pending Register */
    volatile u32 RESERVED2[24U];
    volatile u32 ICPR[8U]; /*!< Interrupt Clear Pending Register */
    volatile u32 RESERVED3[24U];
    volatile u32 IABR[8U]; /*!< Interrupt Active bit Register */
    volatile u32 RESERVED4[56U];
    volatile u8 IP[240U]; /*!< Interrupt Priority Register (8Bit wide) */
    volatile u32 RESERVED5[644U];
    volatile u32 STIR; /*!< Software Trigger Interrupt Register */
} NVIC_TypeDef;

/**
 * @struct
 * @brief Memory map struct used to access SCB registers
 *
 */
typedef struct
{
    volatile u32 CPUID;    /*!< CPUID Base Register */
    volatile u32 ICSR;     /*!< Interrupt Control and State Register */
    volatile u32 VTOR;     /*!< Vector Table Offset Register */
    volatile u32 AIRCR;    /*!< Application Interrupt and Reset Control Register */
    volatile u32 SCR;      /*!< System Control Register */
    volatile u32 CCR;      /*!< Configuration Control Register */
    volatile u8 SHP[12U];  /*!< System Handlers Priority Registers (4-7, 8-11, 12-15) */
    volatile u32 SHCSR;    /*!< System Handler Control and State Register */
    volatile u32 CFSR;     /*!< Configurable Fault Status Register */
    volatile u32 HFSR;     /*!< HardFault Status Register */
    volatile u32 DFSR;     /*!< Debug Fault Status Register */
    volatile u32 MMFAR;    /*!< MemManage Fault Address Register */
    volatile u32 BFAR;     /*!< BusFault Address Register */
    volatile u32 AFSR;     /*!< Auxiliary Fault Status Register */
    volatile u32 PFR[2U];  /*!< Processor Feature Register */
    volatile u32 DFR;      /*!< Debug Feature Register */
    volatile u32 ADR;      /*!< Auxiliary Feature Register */
    volatile u32 MMFR[4U]; /*!< Memory Model Feature Register */
    volatile u32 ISAR[5U]; /*!< Instruction Set Attributes Register */
    volatile u32 RESERVED0[5U];
    volatile u32 CPACR; /*!< Coprocessor Access Control Register */
} SCB_TypeDef;

/*******************************************************************************
 *                        Definitions                                          *
 *******************************************************************************/

/**
 * @brief NVIC memory mapped pointer, used to access NVIC registers
 *
 */
#define NVIC ((volatile NVIC_TypeDef *)0xE000E100)

/**
 * @brief SCB memory mapped pointer, used to access SCB registers
 *
 */
#define SCB ((volatile SCB_TypeDef *)0xE000ED00)
