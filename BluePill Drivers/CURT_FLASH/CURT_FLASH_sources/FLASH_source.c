/**
 * @file FLASH_source.c
 * @author Hazem Montasser (h4z3m.private@gmail.com)
 * @brief  Source file for the FLASH driver
 * @version 0.1
 * @date 2023-08-18
 *
 * @copyright Copyright (c) 2023
 *
 */

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../LIB/BIT_MATH.h"
#include "../CURT_FLASH_headers/FLASH_interface.h"
#include "../CURT_FLASH_headers/FLASH_private.h"

/*******************************************************************************
 *                         Private Functions Prototypes                        *
 *******************************************************************************/

/**
 * @fn FLASH_Status_t FLASH_CheckStatus(void)
 * @brief Checks the status of the FLASH
 *
 * @return  FLASH_Status_t
 */
static FLASH_Status_t FLASH_CheckStatus(void);

/**
 * @fn void FLASH_WaitOnBusFree(void)
 * @brief Waits until the FLASH is free
 *
 */
static void FLASH_WaitOnBusFree(void);

/**
 * @fn void FLASH_ProgramHalfWord(u32, u16)
 * @brief   Programs a half word at the given address
 *
 * @param Address   Address to be programmed
 * @param Data      Data to be programmed
 */
static void FLASH_ProgramHalfWord(u32 Address, u16 Data);

/*******************************************************************************
 *                         Private Functions                                   *
 *******************************************************************************/

static FLASH_Status_t FLASH_CheckStatus(void)
{

  if (CHK_BIT(FLASH->SR, FLASH_SR_PGERR) || CHK_BIT(FLASH->SR, FLASH_SR_WRPRTERR))
    return FLASH_Status_Error;
  else
    return FLASH_Status_OK;
}

static void FLASH_WaitOnBusFree(void)
{
  while (GET_BIT(FLASH->SR, FLASH_SR_BSY))
    ;
}

static void FLASH_ProgramHalfWord(u32 Address, u16 Data)
{
  *(u16 *)Address = Data;
  FLASH_WaitOnBusFree();
}

/*******************************************************************************
 *                         Public Functions                                    *
 *******************************************************************************/

FLASH_Status_t FLASH_Unlock(void)
{
  /* Check if flash is already unlocked */
  if (!CHK_BIT(FLASH->CR, FLASH_CR_LOCK))
    return FLASH_Status_Error;

  /* Perform key writes to flash */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;

  return FLASH_Status_OK;
}

FLASH_Status_t FLASH_Program(FLASH_TypeProgram_t typeProgram, u32 Address, u64 Data)
{
  /* Check address */
  if (!IS_FLASH_PROGRAM_ADDRESS(Address))
    return FLASH_Status_Error;

  /* If flash is locked, exit */
  if (CHK_BIT(FLASH->CR, 7))
    return FLASH_Status_Error;

  u8 iterations = 0;

  /* Write the data */
  if (typeProgram == FLASH_TypeProgram_HalfWord)
  {
    iterations = 1;
  }
  else if (typeProgram == FLASH_TypeProgram_Word)
  {
    iterations = 2;
  }
  else if (typeProgram == Flash_TypeProgram_DoubleWord)
  {
    iterations = 4;
  }
  else
  {
    return FLASH_Status_Error;
  }

  for (u8 i = 0; i < iterations; i++)
  {
    /* Set program bit */
    SET_BIT(FLASH->CR, FLASH_CR_PG);

    /* Write one word per iteration, extract one word at a time */
    FLASH_ProgramHalfWord(Address + 2U * i, (u16)(Data >> (i * 16U)));

    /* Clear program bit to proceed to next word */
    CLR_BIT(FLASH->CR, FLASH_CR_PG);

    /* If there's an error, abort */
    if (FLASH_CheckStatus() != FLASH_Status_OK)
      return FLASH_Status_Error;
  }

  return FLASH_Status_OK;
}

FLASH_Status_t FLASH_PageErase(u32 pageAddress, u8 pageCount)
{
  /* Check page */
  if (!IS_FLASH_PROGRAM_ADDRESS(pageAddress) && !IS_FLASH_PROGRAM_ADDRESS(pageAddress + pageCount * FLASH_PAGE_SIZE))
    return FLASH_Status_Error;

  /* If flash is locked, exit */
  if (CHK_BIT(FLASH->CR, FLASH_CR_LOCK))
    return FLASH_Status_Error;

  for (u32 address = pageAddress;
       address < ((pageCount * FLASH_PAGE_SIZE) + pageAddress);
       address += FLASH_PAGE_SIZE)
  {
    /* Set page erase bit */
    SET_BIT(FLASH->CR, FLASH_CR_PER);

    /* Select the page to erase */
    FLASH->AR = address;

    /* Start erasure */
    SET_BIT(FLASH->CR, FLASH_CR_STRT);

    FLASH_WaitOnBusFree();

    /* Clear page erase bit */
    CLR_BIT(FLASH->CR, FLASH_CR_PER);

    /* If there's an error, abort */
    if (FLASH_CheckStatus() != FLASH_Status_OK)
      return FLASH_Status_Error;
  }
  return FLASH_Status_OK;
}

FLASH_Status_t FLASH_MassErase(void)
{
  /* If flash is locked, exit */
  if (CHK_BIT(FLASH->CR, FLASH_CR_LOCK))
    return FLASH_Status_Error;

  /* Set mass erase bit */
  SET_BIT(FLASH->CR, FLASH_CR_MER);

  /* Start erasure */
  SET_BIT(FLASH->CR, FLASH_CR_STRT);
  FLASH_WaitOnBusFree();

  /* Clear mass erase bit */
  CLR_BIT(FLASH->CR, FLASH_CR_MER);

  return FLASH_CheckStatus();
}

FLASH_Status_t FLASH_Lock(void)
{
  if (!CHK_BIT(FLASH->CR, FLASH_CR_LOCK))
  {
    SET_BIT(FLASH->CR, FLASH_CR_LOCK);
    return FLASH_Status_OK;
  }
  else
    return FLASH_Status_Error;
}
