/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  17-10-2020             **********/
/***********     File      :  FPEC_private           **********/
/**************************************************************/

#ifndef _FPEC_PRIVATE_H
#define _FPEC_PRIVATE_H


/**********************************************************/
/*                 Registers Definition                   */
/**********************************************************/
typedef struct
{
	volatile u32 ACR     ;
	volatile u32 KEYR    ;
	volatile u32 OPTKEYR ;
	volatile u32 SR      ;
	volatile u32 CR      ;
	volatile u32 AR      ;
	volatile u32 Reserved;
	volatile u32 OBR     ;
	volatile u32 WRAPR   ;

} FPEC_t;



#define FPEC  ((volatile FPEC_t *)0x40022000)



/**********************************************************/
/*                           GLOBALS                      */
/**********************************************************/
u16 FlashedRecord[10];


/**********************************************************/
/*                           MACROS                       */
/**********************************************************/

#endif
