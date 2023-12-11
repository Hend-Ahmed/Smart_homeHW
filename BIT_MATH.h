/*********************************************************
********* File       ; BIT_MATH.H **** BITMATH
********* created on : 10/9/2023
********* Author     : Abdullatif Aslam
*********************************************************/

/*********************************************************
*    BIT MATH GIDE                                       *
*********************************************************/

#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_

/*********************************************************
*    BIT MATH EQUATION                                   *
*********************************************************/

/*!Comment : Set Function */

#define SET_BIT(var, bit) var |=  (1 << bit) 

/*!Comment : Clear Function */

#define CLR_BIT(var, bit) var &= ~(1 << bit)

/*!Comment : Toggle Function */

#define TOG_BIT(var, bit) var ^= (1 << bit)

/*!Comment : GET Function */

#define GET_BIT(var, bit) ((var >> bit) & 1)

#endif

/*****************FILE REVISION**************************
********* Auther name ;
********* Abdullatif Aslam      RRW-Q
*********
********* Updated record:
*********
*********  10/9/2023 RRW-Q SY.0 Updated BIT MATH  
*********
*********************************************************/