/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  14-8-2020              **********/
/***********     File      :  GBIO_private           **********/
/**************************************************************/

#ifndef _GBIO_PRIVATE_H
#define _GBIO_PRIVATE_H


/***************        Registers Definition      **************/
/*   Base Address For Each Port */
#define BASE_ADRESS_PORTA    0x40010800
#define BASE_ADRESS_PORTB    0x40010C00
#define BASE_ADRESS_PORTC    0x40011000

/*   PORTA Register Definition */
#define MGBIOA_CRL          *((u32 *)(BASE_ADRESS_PORTA + 0x00))          
#define MGBIOA_CRH          *((u32 *)(BASE_ADRESS_PORTA + 0x04))
#define MGBIOA_IDR          *((u32 *)(BASE_ADRESS_PORTA + 0x08))
#define MGBIOA_ODR          *((u32 *)(BASE_ADRESS_PORTA + 0x0C))
#define MGBIOA_BSRR         *((u32 *)(BASE_ADRESS_PORTA + 0x10))
#define MGBIOA_BRR          *((u32 *)(BASE_ADRESS_PORTA + 0x14))
#define MGBIOA_LCKR         *((u32 *)(BASE_ADRESS_PORTA + 0x18))

/*   PORTC Register Definition */
#define MGBIOB_CRL          *((u32 *)(BASE_ADRESS_PORTB + 0x00))          
#define MGBIOB_CRH          *((u32 *)(BASE_ADRESS_PORTB + 0x04))
#define MGBIOB_IDR          *((u32 *)(BASE_ADRESS_PORTB + 0x08))
#define MGBIOB_ODR          *((u32 *)(BASE_ADRESS_PORTB + 0x0C))
#define MGBIOB_BSRR         *((u32 *)(BASE_ADRESS_PORTB + 0x10))
#define MGBIOB_BRR          *((u32 *)(BASE_ADRESS_PORTB + 0x14))
#define MGBIOB_LCKR         *((u32 *)(BASE_ADRESS_PORTB + 0x18))
 
/*   PORTC Register Definition */
#define MGBIOC_CRL          *((u32 *)(BASE_ADRESS_PORTC + 0x00))          
#define MGBIOC_CRH          *((u32 *)(BASE_ADRESS_PORTC + 0x04))
#define MGBIOC_IDR          *((u32 *)(BASE_ADRESS_PORTC + 0x08))
#define MGBIOC_ODR          *((u32 *)(BASE_ADRESS_PORTC + 0x0C))
#define MGBIOC_BSRR         *((u32 *)(BASE_ADRESS_PORTC + 0x10))
#define MGBIOC_BRR          *((u32 *)(BASE_ADRESS_PORTC + 0x14))
#define MGBIOC_LCKR         *((u32 *)(BASE_ADRESS_PORTC + 0x18))
 






#endif