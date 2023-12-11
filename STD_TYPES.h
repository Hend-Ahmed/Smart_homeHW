/*********************************************************
********* File       ; STD_TYPES.H **** Standerd Types
********* created on : 10/9/2023
********* Author     : Feras Osama 
*********************************************************/

/*********************************************************
*    STANDERED TYPES GIDE                                *
*********************************************************/

#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_ 

/*********************************************************
*    STANDERED TYPES FOR UNSIGNED INTEGERS               *
*********************************************************/

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned long int  uint32;

/*********************************************************
*    STANDERED TYPES FOR SIGNED INTEGERS                 *
*********************************************************/

typedef signed char      int8;
typedef signed short int int16;
typedef signed long int  int32;

/*********************************************************
*    STANDERED TYPES FOR FLOAT                           *
*********************************************************/

typedef float   f32;
typedef double  f64;

/*********************************************************
*    MOOLEAN TYPES DEFINES DEFINES                       *
*********************************************************/

#define True  1u
#define False 0u

#define Zero  0u
#define One   1u

#define NULL  0u

#define Max_Num 10u

/*********************************************************
*    MOOLEAN TYPES RETURN TYPES                          *
*********************************************************/

typedef enum 
{
	
	E_NOT_OK,
	E_OK    ,
	E_PINDING
	
}Std_ReturnType;

#endif

/*****************FILE REVISION**************************
********* Auther name ;
********* Abdullatif Aslam      RRW-Q
*********
********* Updated record:
*********
*********  10/9/2023 RRW-Q SY.0 Updated STANDERED TYPES  
*********
*********************************************************/