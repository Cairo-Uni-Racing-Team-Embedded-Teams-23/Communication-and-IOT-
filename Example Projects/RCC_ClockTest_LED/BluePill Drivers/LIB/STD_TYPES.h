 /*******************************************************************************
 *																				*
 * 	Module			: Standard Types										    *
 *																				*
 * 	File Name		: STD_TYPES.h												*		
 *																				*	
 * 	Author			: AbdElRahman Sabry											*
 *																				*
 *	Date 			: 23/9/2021													*
 *																				*
 *	Version			: v1														*
 * 																				*
 *******************************************************************************/

#ifndef STDTYPES_H_
#define STDTYPES_H_


//Standard Data Types 
typedef		unsigned char			u8;
typedef		char					s8;
typedef		unsigned short			u16;
typedef		short					s16;
typedef		unsigned int			u32;
typedef		int						s32;
typedef		unsigned long long		u64;
typedef		long long				s64;
typedef		float					f32;
typedef		double					f64;



//Booleans 
typedef		unsigned char			bool;
#define		TRUE					(1u)
#define		FALSE					(0u)
		
#define		HIGH					(1u)
#define		LOW						(0u)

#define		ONE						(1u)
#define		ZERO					(0u)


//Pointers 
#define		NULLPTR					((void*)0)

#define DISABLE (0U)
#define ENABLE (1U)


#endif /* STDTYPES_H_ */
