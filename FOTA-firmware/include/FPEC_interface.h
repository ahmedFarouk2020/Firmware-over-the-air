/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  17-10-2020             **********/
/***********     File      :  FPEC_interface         **********/
/**************************************************************/

#ifndef _FPEC_INTERFACE_H
#define _FPEC_INTERFACE_H


/*****************************************************************/
/******                        Functions                    ******/
/*****************************************************************/
void MFPEC_vidFlashPageErase(u8 Cpy_u8PageNum);
void MFPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length); /*Lenth= number of elemnts in the Data Array*/
u16* MFPEC_vidReadFlashRecord(u32 Copy_u32Address,u8 Copy_u8Length);
/*****************************************************************
* Name:          MFPEC_voidEraseAppArea                          *
*				                                                 *
*				                                                 *
* Parameters:    1-Start Page From 0 to 255 					 *
* 	             2-End Page (will be erased) From 0 to 255       *
* 	             												 *
* Description:   It will erase the Flash memory from the Start   *
*                page, until it clear the last page 			 *
*																 *
*																 *
* Notes:         -The Last Page in the STM32F103 is 63           *
*****************************************************************/
void MFPEC_voidEraseAppArea(u8 Cpy_u8AppStart,u8 Cpy_u8AppEnd);
void MFPEC_vidEraseOptional(void);
void MFPEC_vidProgramOptional(u8 Cpy_u8ByteNum, u8 Copy_u8Data );
u8 MFPEC_vidReadOptionalData(u8 Cpy_u8ByteNum);


/*****************************************************************/
/******                Function's parameters                ******/
/*****************************************************************/


#endif
