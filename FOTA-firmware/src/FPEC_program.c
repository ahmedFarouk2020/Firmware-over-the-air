/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  17-10-2020             **********/
/***********     File      :  FPEC_program           **********/
/**************************************************************/


/*****************************************************************
*  Description: Flash (Program) and (Erase) Controller           *
*																 *
*  Rules      : 1-Flash Memory must be cleared first to be able  *
*               to program it.                                   *
*               if not, the flash operation will be skipped      *
*				and, an error flag will be set (page14)          * 
*                                                                *
*               2-HSI Crystal Must Be Enabled (page10)           *
* 															     *
*  Note       : Only Half word can be written at once            *
*****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"


/**********************************************************/
/*         Implementations of the Functions               */
/**********************************************************/
void MFPEC_vidFlashPageErase(u8 Cpy_u8PageNum)
{
	//Wait the Bsy Flag
	while ( GET_BIT(FPEC->SR,0)==1);
	
	//Check if FPEC is Locked, if true, unlock it.
	if (GET_BIT(FPEC->CR,7)==1)
	{
	FPEC->KEYR=0x45670123;
	FPEC->KEYR=0xCDEF89AB;
	}
	
	//Choose Page Erase Operation
	SET_BIT(FPEC->CR,1);
	
	//Set the Page Address
	FPEC->AR= (u32)(Cpy_u8PageNum * 1024) + 0x08000000 ;
	
	//Start Erase
	SET_BIT(FPEC->CR,6);
	
	//Wait the Bsy Flag
	while ( GET_BIT(FPEC->SR,0)==1);
	
	/*Back To Default setings, to be ready for the coming operation*/
	//Clear End of Operation(EOP) flag
	SET_BIT(FPEC->SR,5);
	//Cancel Erase Page operation
	CLR_BIT(FPEC->CR,1);
	
	
}



void MFPEC_vidEraseOptional(void)
{

	//Wait the Bsy Flag
	while ( GET_BIT(FPEC->SR,0)==1);

	//Check if FPEC is Locked, if true, unlock it.
	if (GET_BIT(FPEC->CR,7)==1)
	{
	FPEC->KEYR=0x45670123;
	FPEC->KEYR=0xCDEF89AB;
	}


	//Check if OPTION Write ENABLE is Locked, if true, unlock it.
	if (GET_BIT(FPEC->CR,9)!=1)
	{
	FPEC->OPTKEYR=0x45670123;
	FPEC->OPTKEYR=0xCDEF89AB;
	}

	//Choose Option Byte Erasing Operation
	SET_BIT(FPEC->CR,5);
	//Start Erase
	SET_BIT(FPEC->CR,6);

	//Wait the Bsy Flag
	while ( GET_BIT(FPEC->SR,0)==1);


	/*Back To Default setings, to be ready for the coming operation*/
	//Clear End of Operation(EOP) flag
	SET_BIT(FPEC->SR,5);
	//Cancel Option Byte Erasing operation
	CLR_BIT(FPEC->CR,5);


	/*Write the RDP to the Default Value Again*/
	//Choose Option Byte Programming(OPTPG) Operation
	SET_BIT(FPEC->CR,4);
	*((volatile u16*)0x1FFFF800) = 0xA5;
	//Wait the Bsy Flag
	while ( GET_BIT(FPEC->SR,0)==1);

	/*Back To Default setings, to be ready for the coming operation*/
	//Clear End of Operation(EOP) flag
	SET_BIT(FPEC->SR,5);
	//Cancel Option Byte Programming(OPTPG) operation
	CLR_BIT(FPEC->CR,4);

}


void MFPEC_vidProgramOptional(u8 Cpy_u8ByteNum, u8 Copy_u8Data )
{
	/*Range Check*/
	if (Cpy_u8ByteNum <=2 )
	{
		//Wait the Bsy Flag
		while ( GET_BIT(FPEC->SR,0)==1);

		//Check if FPEC is Locked, if true, unlock it.
		if (GET_BIT(FPEC->CR,7)==1)
		{
			FPEC->KEYR=0x45670123;
			FPEC->KEYR=0xCDEF89AB;
		}


		//Check if OPTION Write ENABLE is Locked, if true, unlock it.
		if (GET_BIT(FPEC->CR,9)!=1)
		{
			FPEC->OPTKEYR=0x45670123;
			FPEC->OPTKEYR=0xCDEF89AB;
		}

		//Choose Option Byte Programming(OPTPG) Operation
		SET_BIT(FPEC->CR,4);


		/*Write The Data To the OPT Address*/
		Cpy_u8ByteNum = Cpy_u8ByteNum-1;
		*((volatile u16*)0x1FFFF804 + Cpy_u8ByteNum) = (u16)Copy_u8Data;


		//Wait the Bsy Flag
		while ( GET_BIT(FPEC->SR,0)==1);


		/*Back To Default setings, to be ready for the coming operation*/
		//Clear End of Operation(EOP) flag
		SET_BIT(FPEC->SR,5);
		//Cancel Option Byte Programming(OPTPG) operation
		CLR_BIT(FPEC->CR,4);
	}
	else
	{

	}

}



void MFPEC_voidEraseAppArea(u8 Cpy_u8AppStart,u8 Cpy_u8AppEnd)
{
	while (Cpy_u8AppStart<=Cpy_u8AppEnd)
	{
		MFPEC_vidFlashPageErase(Cpy_u8AppStart);
		Cpy_u8AppStart++;
	}
}

void MFPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length)
{
	u8 Loc_u8DataCounter=0;
	
	//Wait the Bsy Flag
	while ( GET_BIT(FPEC->SR,0)==1);
	
	//Check if FPEC is Locked, if true, unlock it.
	if (GET_BIT(FPEC->CR,7)==1)
	{
	FPEC->KEYR=0x45670123;
	FPEC->KEYR=0xCDEF89AB;
	}
	

	//Program Data to Flash, half-word by half-word
	for (Loc_u8DataCounter=0; Loc_u8DataCounter<Copy_u8Length; Loc_u8DataCounter++ )
	{

		//Choose Programming Operation
		SET_BIT(FPEC->CR,0);

		//Write the half word data to the desired address
		*((volatile u16*)Copy_u32Address)  =  Copy_u16Data[Loc_u8DataCounter];   //Address is casted into a pointer to a half-word
		Copy_u32Address+=2;
		//Wait the Bsy Flag
	    while (GET_BIT(FPEC->SR,0)==1);
	
	    //Clear End of Operation(EOP) flag, to be ready for the coming Half-word
		SET_BIT(FPEC->SR,5);
		//Cancel Programming operation
		CLR_BIT(FPEC->CR,0);
	}
	


}

u16* MFPEC_vidReadFlashRecord(u32 Copy_u32Address,u8 Copy_u8Length)
{

	for (u8 i=0 ; i<Copy_u8Length;i++)
	{
	FlashedRecord[i]=  *((volatile u16*)(Copy_u32Address + 2*i));
	}

	return FlashedRecord;

}


u8 MFPEC_vidReadOptionalData(u8 Cpy_u8ByteNum)
{

	if (Cpy_u8ByteNum==1)
	{

		return  (u8)(FPEC->OBR>>10);
	}
	else if (Cpy_u8ByteNum==2)
	{
		return  (u8)(FPEC->OBR>>18);
	}
	else
	{


	}
	return 0;

}




