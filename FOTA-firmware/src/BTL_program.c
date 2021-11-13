/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  26-10-2020             **********/
/***********     File      :  BTL_program            **********/
/**************************************************************/

/*Include Lib Layer*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*Include MCAL Layer*/
#include "RCC_interface.h"
#include "UART_interface.h"
#include "FPEC_interface.h"
#include "GBIO_interface.h"
/*Include HAL Layer*/
#include "ESP_interface.h"
/*Include Component Files*/
#include "BTL_interface.h"
#include "BTL_config.h"
#include "BTL_private.h"



/*****************************************************************/
/******                    Main Functions                   ******/
/*****************************************************************/
void ABTL_vidInit(void)
{
	/* RCC Init*/
	MRCC_voidInitSysClock();
	MRCC_voidEnableClock(MRCC_APB2,14);  //UART1
	MRCC_voidEnableClock(MRCC_APB2,2);   //GBIOA
	MRCC_voidEnableClock(MRCC_AHB,4);    //FPEC

	/*UART Init*/
	MGBIO_vidSetPinDir(MGBIOA,MGBIO_PIN09,MGBIO_MODE_10MHZ_OUT_AF_PP);  //Tx
	MGBIO_vidSetPinDir(MGBIOA,MGBIO_PIN10,MGBIO_MODE_IN_FLOATING);      //Rx
	MUSART1_vidInit();

	/*ESP Init*/
	HESP_vidInit();
	HESP_vidConnectAP((u8*)"your_wifi_name",(u8*)"Your_password");

}


void ABTL_vidStart(void)
{
	/* Declare Reqiured variables */
	u8* Loc_pu8ServerAnswer=0;
	u8 Loc_u8PageNumCounter=1;
	u8 Loc_u8ServerIP[18]= "192.168.1.4";
	u8 Loc_u8CheckUpdateReq[86]= "GET https://192.168.1.4/api/hasUpdate/";


	/*Read Optional byte To know the Last Updated Bank*/
	u8SuccessfullyUpdatedBank = MFPEC_vidReadOptionalData(1);  //1 For the first Optional Data Byte

	if(u8SuccessfullyUpdatedBank != 0xAA && u8SuccessfullyUpdatedBank != 0xBB)
	{
		/* Assign optional byte to 0xBB */
		MFPEC_vidProgramOptional(1,0xBB);
		/* Assign u8SuccessfullyUpdatedBank to BB */
		u8SuccessfullyUpdatedBank = 0xBB;
	}

	/*Check New File*/
	HESP_vidServerConnect(Loc_u8ServerIP);
	Loc_pu8ServerAnswer = HESP_pu8GetRequest(40,Loc_u8CheckUpdateReq);


	/*if an Update is Found */
	if (ESP_IsUpdateExist()) //Loc_pu8ServerAnswer[37]=='y'
	{

		/*Erase the other Bank To Download the update on it*/
		if (u8SuccessfullyUpdatedBank == 0xAA)
		{
			/*Erase BankB*/
			MFPEC_voidEraseAppArea(ABTL_BANKB_PAGE,63);  //From Page 37 to 63
		}
		else if (u8SuccessfullyUpdatedBank == 0xBB)
		{
			/*Erase BankA*/
			MFPEC_voidEraseAppArea(ABTL_BANKA_PAGE,36);  //From Page 10 to 36
		}
		else
		{

		}


		/*Keep reading records and flash it until the end of the Hex File*/
		while (1)
		{
			HESP_vidServerConnect(Loc_u8ServerIP);
			switch (u8SuccessfullyUpdatedBank)
			{
				// BankB = 1	BankA = 0
			case 0xAA:Loc_pu8ServerAnswer = vidGetPageOfRecordsUseingESP(1,Loc_u8PageNumCounter, 80); break; //100 is the number of records at a page //1 for bankb
			case 0xBB:Loc_pu8ServerAnswer = vidGetPageOfRecordsUseingESP(0,Loc_u8PageNumCounter, 80); break;//100 is the number of records at a page
			}
			vidParseRecord(Loc_pu8ServerAnswer);
			Loc_u8PageNumCounter++;
		}

	}
	/*if No Update is Found */
	else
	{
		/* Jump to the Up-To-Date Bank */
		if (u8SuccessfullyUpdatedBank == 0xAA)
		{
			vidJumpToApp(ABTL_BANKA_PAGE);
		}
		else if (u8SuccessfullyUpdatedBank == 0xBB)
		{
			vidJumpToApp(ABTL_BANKB_PAGE);
		}


	}

}  //END Func





/***************************************************************************/
/******                           Helping Functions                   ******/
/***************************************************************************/
/*************************************************************************************************************************/
void vidParseRecord(u8* Cpy_u8BufData)
{
	/*Declare Necessary Variables */
	u8 Loc_u8FinishFlag=0;     //is Flag is Set When The Last Record Of The Page is programmed successfully

	/*Get Each record and parse it, until the last record*/
	while (Loc_u8FinishFlag !=1 )
	{
		/*Get only one single record from the page. the Flag will be Set Only After the last record*/
		Loc_u8FinishFlag = pu8GetSingleRecord(Cpy_u8BufData);

		/*Parse the Record*/
		if (Loc_u8FinishFlag !=1 )
		{
			switch (u8SingleRecord[8])
			{
				case '0':   vidFlashDataRecord(u8SingleRecord);   break;
				case '1': 	vidToggleOptionalAndJumpToApp();      break;
			} //END Switch
		} //END if
	} //END While

}  //Func END


/*************************************************************************************************************************/
void vidFlashDataRecord(u8* Copy_u8BufData)
{
	u8 DigitLow,DigitHigh,CC,i;
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	u8 DataCounter = 0;
	u8 ValidateCorrectFlashing=0;
	u16* PointerToFlashedRecord;

	/* Get Character Count */
	DigitHigh = AsciToHex (Copy_u8BufData[1]);
	DigitLow  = AsciToHex (Copy_u8BufData[2]);
	CC        = (DigitHigh<<4) | DigitLow ;

	/* Get Address */
	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
	DataDigit3 = AsciToHex (Copy_u8BufData[6]);

	/* Modify To the desired address */
	u32RecordAddressForParser = u32RecordAddressForParser & 0xFFFF0000;
	u32RecordAddressForParser = u32RecordAddressForParser | (DataDigit3) | (DataDigit2 << 4) | (DataDigit1 << 8) | (DataDigit0<<12);



	for (i=0;i<CC/2; i++)
	{
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+9 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+10]);
		DataDigit2 = AsciToHex (Copy_u8BufData[4*i+11]);
		DataDigit3 = AsciToHex (Copy_u8BufData[4*i+12]);

		Data[DataCounter] = (DataDigit3 << 8) | (DataDigit2 << 12) | (DataDigit1) | (DataDigit0<<4);
		DataCounter++;
	}

	/*Start Flashing*/
	while (ValidateCorrectFlashing != 1)
	{
		MFPEC_voidFlashWrite(u32RecordAddressForParser, Data , CC/2);
		PointerToFlashedRecord = MFPEC_vidReadFlashRecord(u32RecordAddressForParser,CC/2);


		if ( (PointerToFlashedRecord[0]!= 0xffff) && (PointerToFlashedRecord[1]!= 0xffff) && (PointerToFlashedRecord[7]!= 0xffff) )
	    {
			ValidateCorrectFlashing=1;
		}

	}
	ValidateCorrectFlashing=0;

}

/*************************************************************************************************************************/
void vidJumpToApp(u8 Cpy_u8PageNum)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)


	SCB_VTOR = 0x08000000+(1024*Cpy_u8PageNum) ;

	addr_to_call = *(Function_t*)(0x08000004+(1024*Cpy_u8PageNum));
	addr_to_call();
}

u8 AsciToHex(u8 Copy_u8Asci)
{
	u8 Result;
	if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
	{
		Result = Copy_u8Asci - 48;
	}

	else
	{
		Result = Copy_u8Asci - 55;
	}

	return Result;
}


/*************************************************************************************************************************/
/******   pu8GetSingleRecord V1.0 (Works)  ******/
/*
u8  pu8GetSingleRecord(u8* Cpy_pu8ManyRecords)
{

	static u32 Loc_u32CharCounter=0;  //it will be initialized by Zero, then it will keep its last value when i call the func. again
	u8 Loc_u8TempCounter=0;

	//As Long as the file hasn't' finished yet
	while (Cpy_pu8ManyRecords[Loc_u32CharCounter] != ']'  )
	{
		//if this is a first of a record
		if (Cpy_pu8ManyRecords[Loc_u32CharCounter] == ':' && Cpy_pu8ManyRecords[Loc_u32CharCounter-1] < '0'    )
		{
			//Store The Whole Record
			while ( Cpy_pu8ManyRecords[Loc_u32CharCounter+1] != ':' && Cpy_pu8ManyRecords[Loc_u32CharCounter+1] != ']'  )
			{

				u8SingleRecord[Loc_u8TempCounter]= Cpy_pu8ManyRecords[Loc_u32CharCounter];
				Loc_u8TempCounter++;
				Loc_u32CharCounter++;
			}
			//Return with that record. (Zero bc, it isn't the last record yet)
			return 0;
		}

		//As long as this char isn't a record start, check the next char
		Loc_u32CharCounter++;
	}

	//if the file has been finished
	 //Clr The CharCounter for the coming file
	Loc_u32CharCounter=0;
	 //infrom that the file has been finished
	return 1;
}
*/


/******   pu8GetSingleRecord V2.0  (Works)  ******/
u8  pu8GetSingleRecord(u8* Cpy_pu8ManyRecords)
{

	static u16 Loc_u16CharCounter=0;  //it will be initialized by Zero, then it will keep its last value when i call the func. again
	u8 Loc_u8TempCounter=0;

	/*As Long as the file hasn't' finished yet*/
	while (Cpy_pu8ManyRecords[Loc_u16CharCounter] != ']'  )
	{
		/*if this is a first of a record*/
		if (Cpy_pu8ManyRecords[Loc_u16CharCounter] == ':' && Cpy_pu8ManyRecords[Loc_u16CharCounter-1] < '0'    )
		{
			/*Store The Whole Record*/
			while ( Cpy_pu8ManyRecords[Loc_u16CharCounter+1] != ':' && Cpy_pu8ManyRecords[Loc_u16CharCounter+1] != ']'  )
			{

				/*skip   "+IPD,NUM :" if found   */
				if (Cpy_pu8ManyRecords[Loc_u16CharCounter] == '+')
				{
					Loc_u16CharCounter= u16SkipIPD(Cpy_pu8ManyRecords, Loc_u16CharCounter);
				}

				u8SingleRecord[Loc_u8TempCounter]= Cpy_pu8ManyRecords[Loc_u16CharCounter];
				Loc_u8TempCounter++;
				Loc_u16CharCounter++;
			}
			/*Return with that record. (Zero bc, it isn't the last record yet)*/
			return 0;
		}

		/*As long as this char isn't a record start, check the next char*/
		Loc_u16CharCounter++;
	}

	/*if the file has been finished*/
	 /*Clr The CharCounter for the next coming Page*/
	Loc_u16CharCounter=0;
	 /*Infrom that the file has been finished */
	return 1;
}



/*************************************************************************************************************************/
u16 u16SkipIPD(u8* Cpy_pu8ManyRecords, u16 Cpy_u16CharCounter )
{

	while(Cpy_pu8ManyRecords[Cpy_u16CharCounter] != ':')
	{
		Cpy_u16CharCounter++;
	}
	Cpy_u16CharCounter++;
	return Cpy_u16CharCounter;
}

/*************************************************************************************************************************/

u8* vidGetPageOfRecordsUseingESP(u8 Cpy_u8Bank, u8 Cpy_u8PageNum, u8 Cpy_u8NumbOfRecords)
{
	/*Declare some necessary Variables*/
	u8  Loc_u8GETcommand[100]  = "GET https://192.168.1.4/api/receive/";
	//u8 Loc_u8UserAndPswd[19]  ="/khaled/cd3r4wcl52";
	u8  Loc_u8Slash[2]="/";
// GET https://192.168.1.7/api/receive/banknum/pagenum/100/\n\n
	u8  Loc_u8CharCount=42;// character count in record without pageNum and NumofRecord

	u8  Loc_u8TempString[4]={0};
	u8* Loc_pu8ESPResponseAddress=0;


	//Calculate Command Size to Update "Loc_u8CharCount"
	/* Count the digits of the Page Num*/
	if(Cpy_u8PageNum <10)// 1 digit
	{
		Loc_u8CharCount+=1;
	}
	else if(Cpy_u8PageNum <100)// 2 digits
	{
		Loc_u8CharCount+=2;
	}
	/* Count the digits of the Num Of Records*/
	if(Cpy_u8NumbOfRecords <10)// 1 digit
	{
		Loc_u8CharCount+=1;
	}
	else if(Cpy_u8NumbOfRecords <100)// 2 digits
	{
		Loc_u8CharCount+=2;
	}
	else if(Cpy_u8NumbOfRecords <255)// 3 digits
	{
		Loc_u8CharCount+=3;
	}


	/*Concatinate The Command*/
	/* the final form of the GET Request Must Be Like This:
	 * GET http://khaledmohsen1400-001-site1.gtempurl.com/api/receive/PageNum/NumOfRec/USER/PASSWORD\r\n
	 * GET http://khaledmohsen1400-001-site1.gtempurl.com/api/receive/BankNum/PageNum/NumOfRec/USER/PASSWORD\r\n
	 */
	/*Add Bank Num to the CMD*/
	sprintf(Loc_u8TempString, "%d", Cpy_u8Bank);           //Convert (Cpy_u8Bank) into String (Loc_u8TempString)
	strcat(Loc_u8GETcommand   , Loc_u8TempString );        //Concatinate (Loc_u8TempString) with the (Loc_u8GETcommand)
	strcat(Loc_u8GETcommand   , Loc_u8Slash);              //Add Slash to the (Loc_u8GETcommand)
	/*Add Page Number to the CMD*/
	sprintf(Loc_u8TempString, "%d", Cpy_u8PageNum);        //Convert (Cpy_u8PageOfRecNum) into String (Loc_u8TempString)
	strcat(Loc_u8GETcommand   , Loc_u8TempString );        //Concatinate (Loc_u8TempString) with the (Loc_u8GETcommand)
	strcat(Loc_u8GETcommand   , Loc_u8Slash);              //Add Slash to the (Loc_u8GETcommand)
	/*Add Numb of Records the CMD*/
	sprintf(Loc_u8TempString, "%d", Cpy_u8NumbOfRecords);  //Convert (Cpy_u8NumbOfRecords) into String (Loc_u8TempString)
	strcat(Loc_u8GETcommand   , Loc_u8TempString );		   //Concatinate (Loc_u8TempString)  with the (Loc_u8GETcommand)
	//strcat(Loc_u8GETcommand   , Loc_u8UserAndPswd );       //Concatinate (Loc_u8UserAndPswd) with the (Loc_u8GETcommand)
	strcat(Loc_u8GETcommand   , Loc_u8Slash );

	/*Send The Request To The Server and Get the Respnse*/
	/*HESP_GetReq will add the \r\n */
	Loc_pu8ESPResponseAddress = HESP_pu8GetRequest(Loc_u8CharCount,Loc_u8GETcommand );

	/*Return The Response*/
	return Loc_pu8ESPResponseAddress;
}
/*******************************************************************************************************************************/
void vidToggleOptionalAndJumpToApp(void)
{
	switch (u8SuccessfullyUpdatedBank)
	{
	case 0xAA:
		MFPEC_vidEraseOptional();
		MFPEC_vidProgramOptional(1,0xBB);
		vidJumpToApp(ABTL_BANKB_PAGE);
		break;

	case 0xBB:
		MFPEC_vidEraseOptional();
		MFPEC_vidProgramOptional(1,0xAA);
		vidJumpToApp(ABTL_BANKA_PAGE);
		break;

	}

}


