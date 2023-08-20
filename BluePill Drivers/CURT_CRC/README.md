# CURT Communications & IoT 2023

## CRC Driver by Hazem Montasser

## Overview

This is a CRC driver implementation for the STM32F103C8 based on ARM Cortex-M3. It contains a function to initialize the CRC and a function to calculate a CRC.

## CRC Driver documentation

### File information

- In CURT_CRC_headers

1. **CRC_interface.h**: Contains API functions for using the CRC driver

2. **CRC_private.h**: Contains some definitions and registers used internally within the source

- In CURT_CRC_sources

1. **CRC_SOURCE.c**: Source code for the CRC driver

### How to use this driver

#### Steps

1. Call the CRC_init() function to initialize the CRC

```c
CRC_init();
```

2. Call the CRC_calculate() function to calculate a CRC

```c
uint8_t data[4] = {1, 2, 3, 4};
uint32_t CRC_value = CRC_calculate(data, 4);
```

### Notes

Due to STM32's implementation and very limited CRC hardware features, the CRC module cannot calculate compliant CRC32 if the number of bytes is not divisible by 4. This is why I chose to implement the size of the buffer to be in words rather than in bytes.

The way hardware CRC actually works if you modify a single byte inside the DR register is that the data is padded with zeros, so you're implicitly calculating CRC for an additional (4 - no_of_bytes%4) bytes.

Example:
	If the number of bytes was 6:
		- 1 word -> Fits into DR
		- 2 bytes -> 2 more bytes of value '0' are padded to them before CRC calculation
		
I would advise to use software CRC calculation if the data is not all complete words.