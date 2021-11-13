/*******************************************************/
/*  Author  : Salaheldin                               */
/*  Date    : 29-July 2020                             */
/*  Version : V01                                      */
/*******************************************************/
#ifndef BIT_MATH_H                                       
#define BIT_MATH_H                                       
                                                         
#define SET_BIT(VAR,BIT) (VAR |= (1<<BIT))               
#define CLR_BIT(VAR,BIT) (VAR &= ~(1<<BIT))              
#define TGL_BIT(VAR,BIT) (VAR ^= (1<<BIT))               
#define GET_BIT(VAR,BIT) ((VAR>>BIT)&1)                  
                                                         
#define NULL     0



                                                         
#endif                                                   
                                                         
