# Direct Memory Access Controller (DMAC)
_What's the purpose of having a DMAC?_
- For ordinary data trasnfers, say from UART, the CPU enters a for-loop and blocks other operations to receive and store data into memory which blocks the CPU from doing other tasks.
- Having a DMAC allows the CPU to keep working in the background on more important tasks while it transfers incoming data into memory (either from memory or from a peripheral).
- DMAC is especially useful for large data transfers or for peripherals which interrupt the CPU very frequently with new data.
- DMAC can be useful for important sensors which must keep sending up-to-date data. but constant interruption to the CPU is resource intensive or not possible.
- The DMA receives interrupts from peripherals to indicate data is available to be transferred.
## DMA in STM32WB55 summary
- DMA has 2 instances (DMA1,DMA2), each instance has multiple channels
- In STM32WB55, both DMA1 and DMA2 have **7** channels
- Each channel can be mapped to either a peripheral or to memory
- The DMA operations are MEM-MEM or PERIPHERAL-MEM
- DMA channels can have programmable priorities according to the user which can be assigned in software in the DMA_CCRx register
	- Priority levels:
		- Very high
		- High
		- Medium
		- Low
- If two DMA requests happen at the same time to the DMA, the one with highest priority is handled first.
- If two DMA requests happen at the same time to the DMA and have same priority levels, the one with the __least__ index is handled first. (e.g Ch2 and Ch6 both have High priority -> Ch2 is handled first)
- If the DMA is currently handling a request from a channel and receives a request with higher priority, it alternates between them.
- The DMA Arbiter is responsible for determining the priorities of incoming requests

## Handling data
### Source size < Destination size
- Data is stored with the LSB bits into the LSB bits of the destination
ex: 
	Source size = 8 bits (B0)
	Destination size = 32bits
	After transfer: destination = (X_X_X_B0)
### Source size > Destination size
- Data is stored with the LSB bits into the LSB bits of the destination, and the source bits that cant fit into destination are truncated.
ex: 
	Source size = 16 bits (B1  B0)
	Destination size = 8bits
	After transfer: destination = (B0)
### DMA Registers

#### DMA_ISR 
- For each channel there are 4 bits
	- TEIFx - Transfer Error Interrupt Flag - Indicates if error happened during transfer
	- HTIFx - Half Transfer Interrupt Flag -  Indicates half of the data has been transferred
	- TCIFx - Transfer Complete Interrupt Flag - Indicates complete and successful data transfer
	- GIFx - Global interrupt flag - Gets set whenever any event happens on the DMA **Set by HW, cleared by SW**

#### DMA_CCRx (x: 1...7)

- MEM2MEM: Needs to be set if the operation is memory to memory; otherwise, peripheral to memory
- PL: Priority level (Very high,high, med...)
- MSize: Memory size __(Destination)__
- PSize: Peripheral size __(Source)
- MINC: Increment memory address pointer enable
- PINC: Increment peripheral address pointer enable (Not always useful because data register for a peripheral (for example UART data register) has a constant address and just reads incoming data in it not into another location)
- CIRC: Circular mode (overwrites data from the beginning when new transfer occurs)
- DIR: Data transfer direction
	- 0: Read from peripheral (peripheral -> memory)
	- 1: Read from memory (memory -> peripheral)
_Here: peripheral can be considered memory_
- TEIE: Interrupt enable for transfer error
- HTIE: Interrupt enable for half complete transfer
- TCIE: Interrupt enable for complete transfer
- EN: Channel enable _(Specific to peripheral)

#### DMA_CNTDRx (x: 1...7)
- Counter register which tells the DMA how much data to transfer
- Resets back to original value if circular mode is enabled

#### DMA_CMARx (x: 1...7)
- Contains the memory address to write data to (Pointer to data structure e.g. array, struct...)

#### DMA_CPARx (x: 1...7)
- Contains the peripheral address to get data from (e.g. Address of the UART RX register)

_Note: The CMAR and CPAR registers do not get updated during transfer, they are just offseted by an internal reg/counter inside the DMA_

#### DMA_IFCR
- Interrupt Flag Clear Register
- This register is global to the DMA module
- Writing 1 to the corresponding bit allows the DMA to automatically clear the interrupt bit in the DMA_ISR