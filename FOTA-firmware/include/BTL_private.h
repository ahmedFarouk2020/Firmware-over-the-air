/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  26-10-2020             **********/
/***********     File      :  BTL_private            **********/
/**************************************************************/

#ifndef _BTL_PRIVATE_H
#define _BTL_PRIVATE_H



/*************************************/
/*      Private Helping Functions    */
/*************************************/

/*****************************************************************
* Name:          vidGetPageOfRecordsUseingESP                    *
*                Private for the Bootloader Component Only       *
* 				                                                 *
* Description:   -Using WiFi, this Function will Ask the server  *
*                for The Records of the Hex File.				 *
*                -The Hex File will be divided into pages,		 *
*                The numb. of records in one page can be	     *
*                defined by the user of this func.				 *
* 																 *
* I/P:          1-The Numb of the page that has the next         *
* 				  records to be burnt							 *
* 			    2-the Required number of records at that page    *
*   															 *
* O/P:          1-an address of the array which contains         *
* 				  the Page Records                               *
*                                                                *
* Notes:    -the final form of the GET Request Must Be           *
* 		    Like This:                                           *
* GET http://khaledmohsen1400-001-site1.gtempurl.com/api/receive *
*           BankNum/PageNum/NumOfRec/USER/PASSWORD\r\n          *
*****************************************************************/
u8* vidGetPageOfRecordsUseingESP(u8 Cpy_u8Bank,u8 Cpy_u8PageNum, u8 Cpy_u8NumbOfRecords);


/**************************************************** Parser*******************************************************/
/* Parser Function: it Takes The Page Of Records as I/P. and Then Parse it*/
void vidParseRecord(u8* Cpy_u8BufData);
void vidToggleOptionalAndJumpToApp(void);
/* Used By The Parser: it divides the Page into single records to be parsed */
u8  pu8GetSingleRecord(u8* Cpy_pu8ManyRecords);
u16 u16SkipIPD(u8* Cpy_pu8ManyRecords, u16 Cpy_u16CharCounter ); //used to help the previous func.
/* Used By the Parser Func: it Takes The Data Bytes from the record, and Flash it to the correct address*/
void vidFlashDataRecord(u8* Copy_u8BufData);
u8 AsciToHex(u8 Copy_u8Asci);                                    //used to help the previous func.
/******************************************************************************************************************/

/*  This Function is Used To Jump to any Page of the Flash, and Starts to Execute its code
 *     Options:  From 0 To 63
 */
void vidJumpToApp(u8 Cpy_u8PageNum);


/*************************************/
/*                MACROS             */
/*************************************/
#define ABTL_BANKA_PAGE  10
#define ABTL_BANKB_PAGE  37


/****************************************/
/*         User Defined Variables       */
/****************************************/
typedef void (*Function_t)(void);


/****************************************/
/*         Global Variables             */
/****************************************/
Function_t addr_to_call = 0;    //used to jump to the app area
u32 u32RecordAddressForParser= 0x08000000;  //The parser uses it to store the Address from the record, to be sent to the FPEC
u16 Data[20];    //The parser uses it to store the data from the record, to be sent to the FPEC
u8  u8SingleRecord[50];
u8  u8SuccessfullyUpdatedBank;


#endif
