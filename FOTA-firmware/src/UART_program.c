/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  21-9-2020              **********/
/***********     File      :  USART_program          **********/
/**************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
//#include "MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"


/**********************************************************/
/*         Implementations of the Functions               */
/**********************************************************/
 void MUSART1_vidInit(void)
 {
	 /*
	//Initialize Baud Rate
		//1-Declare Used Variables
		u16 Loc_u16DIVMatissa=0, Loc_u16DIVFraction    =0;
		f32 Loc_f32USARTDIV  =0, Loc_f32FactionDivTemp =0;
	
		//2-Calc MANTISSA DIV and FRACTION DIV
		Loc_f32USARTDIV = (MUSART1_APB2_CLK/(16.*MUSART1_BAUD_RATE));    //USARTYDIV = CLK/(16*Baud Rate)  //i put "." for (float division operation), if it is removed the divison result will be integer
		MATH_vidConvertFloatToMantissaAndFraction(&Loc_f32USARTDIV, &Loc_u16DIVMatissa, &Loc_u16DIVFraction, 2 );
		
		
		//3-the FractionDIV must be multiplied by 16, then Approximated to the nearest ONE *
		Loc_f32FactionDivTemp = (Loc_u16DIVFraction*16)/100.;
		Loc_u16DIVFraction = MATH_u16AppoximateToNearestOne(Loc_f32FactionDivTemp);

		//4-for each fraction overflow, +1 to Mantissa
		while (Loc_u16DIVFraction>15)
		{
			Loc_u16DIVMatissa++;
			Loc_u16DIVFraction -= 16;
		}

		//5-Put The Value to the BRR
		MUSART1 -> BRR = 0;
		MUSART1 -> BRR |= (  0xf&Loc_u16DIVFraction);
		MUSART1 -> BRR |= ( (0xff&Loc_u16DIVMatissa) << 4);
		*/
		MUSART1 -> BRR = 0x341;// 0x45;




	/* Initialize Transmitter,Receiver, and Parity  Status */
	switch (MUSART1_TRANSMITTER_STATUS)
	{
		case MUSART1_ENABLE :  SET_BIT(MUSART1 -> CR1, 3 );     break;
		case MUSART1_DISABLE:  CLR_BIT(MUSART1 -> CR1, 3 );     break;
	}
	switch (MUSART1_RECEIVER_STATUS)
	{
		case MUSART1_ENABLE :  SET_BIT(MUSART1 -> CR1, 2 );     break;
		case MUSART1_DISABLE:  CLR_BIT(MUSART1 -> CR1, 2 );     break;
	}
	switch (MUSART1_PARITY_STATUS)
	{
		case MUSART1_ENABLE :  SET_BIT(MUSART1 -> CR1, 10);     break;
		case MUSART1_DISABLE:  CLR_BIT(MUSART1 -> CR1, 10);     break;
	}


	/* Parity Selection Init*/
	#if  MUSART1_PARITY_STATUS	==    MUSART1_ENABLE

	switch (MUSART1_PARITY_SELECTION)
	{
		case MUSART1_ODD :   SET_BIT(MUSART1 -> CR1, 9);    break;
		case MUSART1_EVEN:   CLR_BIT(MUSART1 -> CR1, 9);    break;
	}

	#endif



	/*Enable USART1*/
	SET_BIT(MUSART1 -> CR1, 13);
	MUSART1 -> SR = 0;

 }


void MUSART1_vidSendSynch     (u8 * pu8DatatoSend)
{
	/*Write the Data To the Transmit Buffer*/
	MUSART1 -> DR = *pu8DatatoSend; 
	/*wait until the trnsission complete*/
	while ( GET_BIT( MUSART1 -> SR,6) ==0  );          
}


void MUSART1_vidSendTextSynch   (u8 * pu8TextDataToSend)
{
	u8 Loc_u8Counter=0;
	
	while (pu8TextDataToSend[Loc_u8Counter] != '\0')
	{
		MUSART1_vidSendSynch(&pu8TextDataToSend[Loc_u8Counter]);
		Loc_u8Counter++;
	}
}


void MUSART1_vidReceiveSynch(u8 * pu8ReceivedData,u32 Copy_u32timeout)
{
	u32 Loc_u8TimeOut=0;
	
	/* Make Sure that the Content is Received Buffer*/
	while (GET_BIT(MUSART1 -> SR,5)==0)		 //This flag is set when receive buffer is not empty(valid data is received)
	{
		Loc_u8TimeOut++;
		if (Loc_u8TimeOut == Copy_u32timeout)
		{
			*pu8ReceivedData = 255;         //the max. value at ASCI table is 127, so if it returned with 255, that mean the time is up without an answer
			break;
		}				
	}
	if (Loc_u8TimeOut != Copy_u32timeout)
	{
		*pu8ReceivedData= MUSART1 -> DR;
	}
}





