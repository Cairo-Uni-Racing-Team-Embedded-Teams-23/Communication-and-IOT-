 /*******************************************************************************
 *																				*
 * 	Module			: Utils														*
 *																				*
 * 	File Name		: BIT_MATH.h												*		
 *																				*	
 * 	Author			: AbdElRahman Sabry											*
 *																				*
 *	Date 			: 23/9/2021													*
 *																				*
 *	Version			: v1														*
 * 																				*
 *******************************************************************************/

#ifndef UTILS_H_
#define UTILS_H_

//MACROS FOR PIN

#define WRITE_BIT(reg , bit , data)	(  reg  =  (reg& ~(1<<bit))  | (data<<bit)  )
#define GET_BIT(reg , bit)		( ((reg)&(1<<bit))>>bit  )
#define CHK_BIT(reg , bit)		((reg) & (1<<bit) )
#define TOG_BIT(reg , bit)		(  reg  ^= (1<<bit)  )
#define SET_BIT(reg , bit)		(  reg  |= (1<<bit)  )
#define CLR_BIT(reg , bit)		(  reg  &=~(1<<bit)  )

//MACROS FOR PORTS AND REGISTERS

#define WRITE_PORT(reg , data)		(  reg = data        )
#define PORT_SET_MASK(reg , mask)	(  reg |= (mask)     )
#define PORT_CLEAR_MASK(reg ,mask)	(  reg &=~(mask)     )



#define PORT_MASK(reg , clr , set)  (  reg = (reg&~(clr))|(set))



#define SET_REG(reg)				(  reg = 0xffffffff    	)
#define CLEAR_REG(reg)				(  reg = 0x00000000    	)
#define TOGGLE_REG(reg)				(  reg ^=0xffffffff	)

//LOWER NIBBLE MACROS	(0 - 3)

#define GET_LOWER(reg)				(  reg &   0x0000ffff      )
#define SET_LOWER_NIBBLE(reg)			(  reg | = 0x0000ffff		 )
#define CLEAR_LOWER_NIBBLE(reg)			(  reg & = 0xffff0000      )


#define LOWER_NIBBLE_DATA(reg , data) ( reg = (reg&0xffff0000)|data ) 

//HIGHER NIBBLE MACROS	(4 - 7)

#define GET_HIGHER(reg)				(  (reg&0xffff0000)>>4    )
#define SET_HIGHER_NIBBLE(reg)		(  reg | =0xffff0000		)
#define CLEAR_HIGHER_NIBBLE(reg)	(  reg & = 0x0000ffff     )

#define HIGHER_NIBBLE_DATA(reg , data)	(	reg = (reg&0x0000ffff) | (data<<4) )



#endif /* UTILS_H_ */