/**
 * @file FLASH_interface.h
 * @author Hazem Montasser (h4z3m.private@gmail.com)
 * @brief  Header file for the FLASH driver
 * @version 0.1
 * @date 2023-08-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef FLASH_INTERFACE_H_
#define FLASH_INTERFACE_H_

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                              Type definitions                               *
 *******************************************************************************/

/**
 * @enum    FLASH_TypeProgram_t
 * @brief   Type of programming
 *
 */
typedef enum
{
    FLASH_TypeProgram_HalfWord,  /**< FLASH_TypeProgram_HalfWord */
    FLASH_TypeProgram_Word,      /**< FLASH_TypeProgram_Word */
    Flash_TypeProgram_DoubleWord /**< Flash_TypeProgram_DoubleWord */
} FLASH_TypeProgram_t;

/**
 * @enum    FLASH_Status_t
 * @brief   Status of the FLASH
 *
 */
typedef enum
{
    FLASH_Status_OK,   /**< FLASH_Status_OK */
    FLASH_Status_Error /**< FLASH_Status_Error */
} FLASH_Status_t;

/*******************************************************************************
 *                         Public functions prototypes                         *
 *******************************************************************************/

/**
 * @fn FLASH_Status_t FLASH_Unlock(void)
 * @brief   Unlocks the flash before programming or erasing
 *
 * @return  FLASH_Status_t
 */
FLASH_Status_t FLASH_Unlock(void);

/**
 * @fn FLASH_Status_t FLASH_Program(FLASH_TypeProgram_t, u32, u64)
 * @brief   Programs the given data in the given address
 *
 * @param typeProgram   Type of program data, must be of type @ref FLASH_TypeProgram_t
 * @param Address       Address to be programmed
 * @param Data          Data to be programmed
 * @return
 */
FLASH_Status_t FLASH_Program(FLASH_TypeProgram_t typeProgram, u32 Address, u64 Data);

/**
 * @fn FLASH_Status_t FLASH_PageErase(u32, u8)
 * @brief   Erases a page
 *
 * @param pageAddress   Address of the page
 * @param pageCount     Number of pages to erase starting from the given address
 * @return  FLASH_Status_t
 */
FLASH_Status_t FLASH_PageErase(u32 pageAddress, u8 pageCount);

/**
 * @fn FLASH_Status_t FLASH_MassErase(void)
 * @brief   Erases all the user pages
 *
 * @return  FLASH_Status_t
 */
FLASH_Status_t FLASH_MassErase(void);

/**
 * @fn FLASH_Status_t FLASH_Lock(void)
 * @brief   Locks the flash
 *
 * @return  FLASH_Status_t
 */
FLASH_Status_t FLASH_Lock(void);

#endif
