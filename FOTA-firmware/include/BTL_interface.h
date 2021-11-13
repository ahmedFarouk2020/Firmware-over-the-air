/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  26-10-2020             **********/
/***********     File      :  BTL_interface          **********/
/**************************************************************/

#ifndef _BTL_INTERFACE_H
#define _BTL_INTERFACE_H



/**************************************************************************/
/******                           Functions                          ******/
/**************************************************************************/

/*****************************************************************
* Name:          ABTL_vidInit                                    *
*                (App Layer Bootloader Init)                     *
*				                                                 *
* Description:   1-Init RCC:									 *
*                   ,enable CLK for UART, FPEC, PORTA            *
*			     2-Init UART: 									 *
*                   ,and configure relevant GBIO Pins		     *
*			     3-Init ESP                          			 *
*				 4-Init SysTick                           		 *
*				                                                 *
* Notes:         You Must:  									 *
* 				  1-Configure RCC SRC Clk To HSI				 *
* 				  2-Configure UART BaudRate to 115200            *
*****************************************************************/
void ABTL_vidInit(void);



void ABTL_vidStart(void);








/*****************************************************************/
/******                 Function's Parameters               ******/
/*****************************************************************/






#endif
