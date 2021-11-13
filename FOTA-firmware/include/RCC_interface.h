/**************************************************************/
/* Author    :  SALAHELDIN                                    */
/* Version   :  V01                                           */
/* Date      :  8-8-2020                                      */
/**************************************************************/
#ifndef _RCC_INTERFACE_H
#define _RCC_INTERFACE_H



void MRCC_voidInitSysClock(void);
//void MRCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);
void MRCC_voidEnableClock (u8 Copy_u8BusId, u8 Copy_u8PerId);

#define MRCC_AHB    0
#define MRCC_APB1   1
#define MRCC_APB2   2





#endif
