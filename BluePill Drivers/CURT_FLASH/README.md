# CURT Communications & IoT 2023

## FLASH Driver by Hazem Montasser

## Overview

This is a Flash driver implementation for the STM32F103C8 based on ARM Cortex-M3. It contains a function to erase & program the embedded flash memory.

## FLASH Driver documentation

### File information

- In CURT_FLASH_headers

1. **FLASH_interface.h**: Contains API functions for using the FLASH driver

2. **FLASH_private.h**: Contains some definitions and registers used internally within the source

- In CURT_FLASH_sources

1. **FLASH_source.c**: Source code for the FLASH driver

### How to use this driver

#### Steps

1. Call ```FLASH_Unlock()``` function before performing any flash operation.

2. To program a certain address, call the following function specifying the data size, valid flash address, and the data.

```C
uint32_t address = 0x08004000;
uint64_t data = 0xAABBCCDD11223344;

FLASH_Unlock();
Flash_Status_t status = FLASH_Program(Flash_TypeProgram_DoubleWord, address, data);
FLASH_Lock();

if(status != FLASH_Status_OK)
{
	/* Handle error */
}
```

3. To erase a certain page, call the following function specifying the page address, and the page count you want to erase starting from that page.

```C
uint32_t page_4_address = 0x08001000;

FLASH_Unlock();
Flash_Status_t status = FLASH_PageErase(page_4_address, 1);
FLASH_Lock();

if(status != FLASH_Status_OK)
{
	/* Handle error */
}

```

4. For mass flash erasure, call the mass erase function. Note that this function erases all user flash pages. The ST bootloader in system memory is untouched.

```C

FLASH_Unlock();
Flash_Status_t status = FLASH_MassErase();
FLASH_Lock();

if(status != FLASH_Status_OK)
{
	/* Handle error */
}

```

### Notes

1. Before doing any flash operation, you must call ```FLASH_Unlock()```. Otherwise, any flash operation will not be possible
2. After finishing any flash operation, you must call ```FLASH_Lock()``` to make sure no accidental writes occur to the flash memory.
