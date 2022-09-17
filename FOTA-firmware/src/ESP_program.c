/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  04-10-2020             **********/
/***********     File      :  ESP_program            **********/
/**************************************************************/

/* Include Library*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <stdio.h>
#include <string.h>
/* Include MCAL */
#include "UART_interface.h"
/* Include COMPONENT*/
#include "ESP_interface.h"
#include "ESP_config.h"
#include "ESP_private.h"



void HESP_vidInit(void)
{
	
	u8 Loc_u8ValidateStatus = 0;
	u8 Loc_u8StopECHOCmd[7]= "ATE0\r\n";
	//u8 Loc_u8StationModeCmd[14]= "AT+CWMODE=1\r\n";
	
	/*Stop ECHO*/
	while (Loc_u8ValidateStatus != 1)
	{
		MUSART1_vidSendTextSynch(Loc_u8StopECHOCmd);
		Loc_u8ValidateStatus = u8ValidateCmd(ECHO_TIMEOUT);
	}
	Loc_u8ValidateStatus=0;
	
	/*Set Section Mode*/
	/*while (Loc_u8ValidateStatus != 1)
	{
		MUSART1_vidSendTextSynch(Loc_u8StationModeCmd);
		Loc_u8ValidateStatus = u8ValidateCmd(MODE_TIMEOUT);
	}
	Loc_u8ValidateStatus=0;*/
}


void HESP_vidConnectAP(u8 Cpy_u8UserName[], u8 Cpy_u8Password[])
{
	u8 Loc_u8ValidateStatus = 0;
	u8 Loc_u8ConnectAPCmd[14]= "AT+CWJAP=";
	u8 Loc_u8DoubleQutation[2]="\"";
	u8 Loc_u8Comma[2]=",";
	u8 Loc_u8EndCmd[3]="\r\n";
	
	while (Loc_u8ValidateStatus != 1)
	{
		MUSART1_vidSendTextSynch(Loc_u8ConnectAPCmd);
		MUSART1_vidSendTextSynch(Loc_u8DoubleQutation);
		MUSART1_vidSendTextSynch(Cpy_u8UserName);
		MUSART1_vidSendTextSynch(Loc_u8DoubleQutation);
		MUSART1_vidSendTextSynch(Loc_u8Comma);
		MUSART1_vidSendTextSynch(Loc_u8DoubleQutation);
		MUSART1_vidSendTextSynch(Cpy_u8Password);
		MUSART1_vidSendTextSynch(Loc_u8DoubleQutation);	
		MUSART1_vidSendTextSynch(Loc_u8EndCmd);			
		
		Loc_u8ValidateStatus = u8ValidateCmd(ROUTER_TIMEOUT);
	}
	Loc_u8ValidateStatus=0;
}

void HESP_vidServerConnect(u8 Cpy_u8ServerIP[])
{
	u8 Loc_u8ValidateStatus = 0;/*
	u8 Loc_u8ServerConnectCmd[19]= "AT+CIPSTART=\"TCP\",";
	u8 Loc_u8Port[3]="8090";
	u8 Loc_u8DoubleQutation[2]="\"";
	u8 Loc_u8Comma[2]=",";
	u8 Loc_u8EndCmd[3]="\r\n";*/
	
	while (Loc_u8ValidateStatus != 1)
	{
	/*	MUSART1_vidSendTextSynch(Loc_u8ServerConnectCmd);
		MUSART1_vidSendTextSynch(Loc_u8DoubleQutation);
		MUSART1_vidSendTextSynch(Cpy_u8ServerIP);
		MUSART1_vidSendTextSynch(Loc_u8DoubleQutation);
		MUSART1_vidSendTextSynch(Loc_u8Comma);
		MUSART1_vidSendTextSynch(Loc_u8Port);
		MUSART1_vidSendTextSynch(Loc_u8EndCmd);	*/
		MUSART1_vidSendTextSynch("AT+CIPSTART=\"TCP\",\"192.168.1.4\",80\r\n");
		
		Loc_u8ValidateStatus = u8ValidateCmd(SERVER_TIMEOUT);
	}
	Loc_u8ValidateStatus=0;
}



u8* HESP_pu8GetRequest(u8 Cpy_u8CommandSize, u8 u8RequestCMD[] )
{
	/*Initialize Some Required Variables*/
	u8 Loc_u8ValidateStatus = 0;
	u8 Loc_u8SendDataCmd[20] = "AT+CIPSEND=";
    u8 Loc_u8EndOfCmd[3]    = "\r\n";
    u8 u8CmdSizeString[5];

	//Concatinatethe CMD End
    //strcat(Loc_u8SendDataCmd , intToStr((u16)Cpy_u8CommandSize) );
	sprintf(u8CmdSizeString, "%d", Cpy_u8CommandSize);    //Convert Int (CommandSize) into Str (CmdSizeString)
	strcat(Loc_u8SendDataCmd , u8CmdSizeString );
    strcat(Loc_u8SendDataCmd , Loc_u8EndOfCmd);
	strcat(u8RequestCMD      , "\n\n");


	//Trasmit Send Data CMD
    /*while (Loc_u8ValidateStatus != 1)
	{
		// Transmit "Send Data" Cmd
		MUSART1_vidSendTextSynch(Loc_u8SendDataCmd);
		Loc_u8ValidateStatus = u8ValidateCmd(PREREQUEST_TIMEOUT);
	}
	Loc_u8ValidateStatus=0;*/


	// Transmit "Get Request" Cmd, Waiting for valid answer
	while (Loc_u8ValidateStatus != 1)
	{
		HESP_vidServerConnect("192.168.1.4");
		MUSART1_vidSendTextSynch(Loc_u8SendDataCmd);
		MUSART1_vidSendTextSynch   (u8RequestCMD);
		Loc_u8ValidateStatus = u8ValidateCmd(REQUEST_TIMEOUT);
	}
	Loc_u8ValidateStatus=0;


	//Retuen with a pointer to the Answer
	return u8ESPResponse;
}




/*****************************************************************/
/******                    Helping Functions                ******/
/*****************************************************************/


/**********************************************************************************************
* Name:         u8ValidateCmd 																  *
* Discription:  it will Read the Received Message from the ESP, In ESP_Response Array,        *
* 				 and, validate the response: return 1 for OK Successful CMD                   *
* 				                             return 0 for Wrong CMD							  *
 *********************************************************************************************/
u8 u8ValidateCmd(u32 Copy_u32timeout)
{
	u8 Loc_u8Result=0;
	u16 Loc_u16ResponseCounter=0;
	u8 Loc_u8ESPRespondDoneFlag=0;     //it will carry the response from (0 to 127), and will set to 255 if respond is done
	
	
	/*Read The Response*/
	while (Loc_u8ESPRespondDoneFlag != 255)   //if it equals 255, that mean the Time is Up without a new message from the ESP
	{
		MUSART1_vidReceiveSynch(&Loc_u8ESPRespondDoneFlag,Copy_u32timeout);
		u8ESPResponse[Loc_u16ResponseCounter] = Loc_u8ESPRespondDoneFlag;
		Loc_u16ResponseCounter++;
		
	}
	
	/*Validate The Response*/
	Loc_u16ResponseCounter=0;
	while (u8ESPResponse[Loc_u16ResponseCounter]  != 255 )
	{
		if ( (u8ESPResponse[Loc_u16ResponseCounter] == 'O'  && u8ESPResponse[Loc_u16ResponseCounter+1] == 'K')
		|| (u8ESPResponse[Loc_u16ResponseCounter] == 'A'  && u8ESPResponse[Loc_u16ResponseCounter+1] == 'L')
		|| (u8ESPResponse[Loc_u16ResponseCounter] == 'n'  && u8ESPResponse[Loc_u16ResponseCounter+1] == 'o' && u8ESPResponse[Loc_u16ResponseCounter+2] == ' ' && u8ESPResponse[Loc_u16ResponseCounter+3] == 'c') )
		{
			Loc_u8Result = 1;
			break;
		}
		Loc_u16ResponseCounter++;
	}
	
	return Loc_u8Result;
}


u8 ESP_IsUpdateExist(void)
{
	u8 counter=0;
	while (counter !=  255 )
	{
		if (u8ESPResponse[counter]==':')
		{
			if(u8ESPResponse[counter+1] == 'y')
				return 1;
			else return 0;
		}
		counter++;
	}
	return 0;
}


