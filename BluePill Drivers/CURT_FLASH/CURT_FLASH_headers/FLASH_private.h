/**
 * @file FLASH_private.h
 * @author Hazem Montasser (h4z3m.private@gmail.com)
 * @brief  Header file which defines private macros & definitions used in the driver source
 * @version 0.1
 * @date 2023-08-18
 *
 * @copyright Copyright (c) 2023
 *
 */

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define FLASH_RDPRT (0x00A5) /* Read protection */
#define FLASH_KEY1 (0x45670123)
#define FLASH_KEY2 (0xCDEF89AB)

#define FLASH_CR_PG (0)
#define FLASH_CR_PER (1)
#define FLASH_CR_MER (2)
#define FLASH_CR_STRT (6)
#define FLASH_CR_LOCK (7)

#define FLASH_SR_BSY (0)
#define FLASH_SR_PGERR (2)
#define FLASH_SR_WRPRTERR (4)

#define FLASH_BASE_ADDRESS (0x40022000)
#define FLASH_PAGE_SIZE (0x400)
#define FLASH_BASE 0x08000000UL /*!< FLASH base address in the alias region */
#define FLASH_SIZE_DATA_REGISTER 0x1FFFF7E0U
#define FLASH_BANK1_END 0x08007FFFUL /*!< FLASH END address of bank1 */

#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= FLASH_BASE) && (((*((u16 *)FLASH_SIZE_DATA_REGISTER)) == 0x20U) ? ((ADDRESS) <= FLASH_BANK1_END) : ((ADDRESS) <= 0x08003FFFU)))
#define IS_FLASH_PAGE(PAGE) (PAGE >= 0 && PAGE < 128)

#define FLASH ((FLASH_TypeDef *)FLASH_BASE_ADDRESS)

/*******************************************************************************
 *                              Type definitions                               *
 *******************************************************************************/

typedef struct
{
  volatile u32 ACR;
  volatile u32 KEYR;
  volatile u32 OPTKEYR;
  volatile u32 SR;
  volatile u32 CR;
  volatile u32 AR;
  volatile u32 RESERVED;
  volatile u32 OBR;
  volatile u32 WRPR;
} FLASH_TypeDef;
