/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  14-8-2020              **********/
/***********     File      :  GBIO_program           **********/
/**************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GBIO_interface.h"
#include "GBIO_private.h"
#include "GBIO_config.h"


/* Choose a specific Pin to Set its Mode */
void MGBIO_vidSetPinDir    (u8 cpy_u8PortX ,u8 cpy_u8PinX  ,u8  cpy_u8Mode )
{
  switch (cpy_u8PortX)                                                          /* CHECK the Choosed Port  */
  {
     case MGBIOA :                                                               /* if POERTA is choosed    */
                if (cpy_u8PinX <= 7)                                            /* CHECK the Choosed PIN   */
                {
                    MGBIOA_CRL  &= ~((0b1111)      << (cpy_u8PinX * 4));         /* Clear  Control Bits of this pin to be able to write on it */
                    MGBIOA_CRL  |=  ((cpy_u8Mode)  << (cpy_u8PinX * 4));         /* Write the Choosed Mode & Config to the Control BITS       */
                }
                else if (cpy_u8PinX <= 15)
                {
                    cpy_u8PinX -= 8;                                            /* to Shift Correctly at the new Register(CRH) you have to start counting pin form zero */
                    MGBIOA_CRH  &= ~((0b1111)      << (cpy_u8PinX * 4));
                    MGBIOA_CRH  |=  ((cpy_u8Mode)  << (cpy_u8PinX * 4));
                }
                break;
     case MGBIOB :                                                               /* if POERTB is choosed    */
                if (cpy_u8PinX <= 7)                                            /* CHECK the Choosed PIN   */
                {
                    MGBIOB_CRL  &= ~((0b1111)      << (cpy_u8PinX * 4));         /* Clear  Control Bits of this pin to be able to write on it */
                    MGBIOB_CRL  |=  ((cpy_u8Mode)  << (cpy_u8PinX * 4));         /* Write the Choosed Mode & Config to the Control BITS       */
                }
                else if (cpy_u8PinX <= 15)
                {
                    cpy_u8PinX -= 8;                                            /* to Shift Correctly at the new Register(CRH) you have to start counting pin form zero */
                    MGBIOB_CRH  &= ~((0b1111)      << (cpy_u8PinX * 4));
                    MGBIOB_CRH  |=  ((cpy_u8Mode)  << (cpy_u8PinX * 4));
                }
                break;
     case MGBIOC :
                if (cpy_u8PinX <= 7)
                {
                    MGBIOC_CRL  &= ~((0b1111)      << (cpy_u8PinX * 4));
                    MGBIOC_CRL  |=  ((cpy_u8Mode)  << (cpy_u8PinX * 4));
                }
                else if (cpy_u8PinX <= 15)
                {
                    cpy_u8PinX -= 8;
                    MGBIOC_CRH  &= ~((0b1111)      << (cpy_u8PinX * 4));
                    MGBIOC_CRH  |=  ((cpy_u8Mode)  << (cpy_u8PinX * 4));
                }
                break;
  }

}



/* Put a Value (HIGH/LOW) on a specific output pin */
/*
void MGBIO_vidSetPinValue  (u8 cpy_u8PortX , u8 cpy_u8PinX  , u8 cpy_u8Value)
{
    switch (cpy_u8PortX)                                                           // CHECK the Choosed Port
    {
        case MGBIOA :                                                               // if POERTA is choosed
                    switch (cpy_u8Value)                                           //CHECK The Value
                    {
                    case MGBIO_HIGH :     SET_BIT(MGBIOA_ODR, cpy_u8PinX); break;    //If it High set the pin
                    case MGBIO_LOW  :     CLR_BIT(MGBIOA_ODR, cpy_u8PinX); break;    //if it Low Clean The pin
                    case MGBIO_TOG  :     TGL_BIT(MGBIOA_ODR, cpy_u8PinX); break;    //if it Toggle toggle The pin
                    }
                    break;
        case MGBIOB :                                                               
                    switch (cpy_u8Value)
                    {
                    case MGBIO_HIGH :     SET_BIT(MGBIOB_ODR, cpy_u8PinX); break;
                    case MGBIO_LOW  :     CLR_BIT(MGBIOB_ODR, cpy_u8PinX); break;
                    case MGBIO_TOG  :     TGL_BIT(MGBIOB_ODR, cpy_u8PinX); break;
                    }
                    break;
        case MGBIOC :                                                             
                    switch (cpy_u8Value)
                    {
                    case MGBIO_HIGH :     SET_BIT(MGBIOC_ODR, cpy_u8PinX); break;
                    case MGBIO_LOW  :     CLR_BIT(MGBIOC_ODR, cpy_u8PinX); break;
                    case MGBIO_TOG  :     TGL_BIT(MGBIOB_ODR, cpy_u8PinX); break;
                    }
                    break;

    }
}
*/



/* Put a Value (HIGH/LOW) on a specific output port */
/*
void MGBIO_vidSetPortValue  (u8 cpy_u8PortX  , u16 cpy_u16Value)
{
    switch (cpy_u8PortX)                                                           
    {
        case MGBIOA :                                                              
                    MGBIOA_ODR = cpy_u16Value ;
                    break;
        case MGBIOB :                                                               
                  MGBIOB_ODR = cpy_u16Value ;
                    break;
                    
        case MGBIOC :                                                             
                    MGBIOC_ODR = cpy_u16Value ;
                    break;

    }

}
*/




/* Read a Value (HIGH/LOW) From a specific input pin */
/*
u8   MGBIO_u8GetPinValue   (u8 cpy_u8PortX , u8 cpy_u8PinX                )
{
    u8 LOC_u8Result =0 ;
    switch (cpy_u8PortX)                                                   // CHECK the Choosed Port
    {
        case MGBIOA :                                                       // if POERTA is choosed
                    LOC_u8Result = GET_BIT(MGBIOA_IDR, cpy_u8PinX);         // Get The value from the pin and store it at LOC_u8Result
                    break;
        case MGBIOB :                                                               
                    LOC_u8Result = GET_BIT(MGBIOB_IDR, cpy_u8PinX);
                    break;
        case MGBIOC :                                                             
                    LOC_u8Result = GET_BIT(MGBIOC_IDR, cpy_u8PinX);
                    break;

    }
    return LOC_u8Result ;
}
*/
