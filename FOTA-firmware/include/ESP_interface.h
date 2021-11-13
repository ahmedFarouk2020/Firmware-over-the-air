/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  04-10-2020             **********/
/***********     File      :  ESP         **********/
/**************************************************************/

#ifndef _ESP_INTERFACE_H
#define _ESP_INTERFACE_H


/*****************************************************************/
/******                        Functions                    ******/
/*****************************************************************/
void HESP_vidInit(void);
void HESP_vidConnectAP(u8 Cpy_u8UserName[], u8 Cpy_u8Password[]);
void HESP_vidServerConnect(u8 Cpy_u8ServerIP[]);
u8 ESP_IsUpdateExist(void);

/*****************************************************************
* Name:          HESP_pu8GetRequest                              *
*				                                                 *
*				                                                 *				                                                 *
* Parameters:    1-CMD Size = (Numb. of Req. Char. +2) 			 *
* 	             2-Array of the Get Req. Cmd                     *
* 	             												 *
* Description:   This Function sends a Get Request to the        *
*                Server, and then, Back with the Valid answer    *
*                  												 *
* Note:          this Function will add \n\r to end of the rec.  *
* 				 by default										 *
*																 *
*****************************************************************/
u8* HESP_pu8GetRequest(u8 Cpy_u8CommandSize, u8 u8RequestCMD[] );

/*****************************************************************/
/******                        Symbols                    ******/
/*****************************************************************/




#endif
