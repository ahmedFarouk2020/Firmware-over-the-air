/**************************************************************/
/* Author    :  SALAHELDIN                                    */
/* Version   :  V01                                           */
/* Date      :  8-8-2020                                      */
/**************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"



void MRCC_voidInitSysClock(void)
{
#if MRCC_SYS_CLCK == MRCC_SYS_HSI
MRCC_CR   = 0x00000081;              /*ENABLE HSI with No Triming  */
MRCC_CFGR = 0x00000000;              /*Clock System is the HSI     */

#elif  MRCC_SYS_CLCK == MRCC_SYS_IN_HSE_CRYSTAL
MRCC_CR   = 0x00010000;              /*ENABLE HSE with No Bypass   */ 
MRCC_CFGR = 0x00000001;              /*Clock System is the HSE     */

#elif MRCC_SYS_CLCK == MRCC_SYS_IN_HSE_RC
MRCC_CR   = 0x00050000;              /*ENABLE HSI with Bypass      */
MRCC_CFGR = 0x00000001;              /*Clock System is the HSE     */

#elif MRCC_SYS_CLCK == MRCC_SYS_IN_PLL

    
    #if  MRCC_PLL_SRC == MRCC_PLL_IN_HALF_HSI
    MRCC_CFGR = 0x00000000;  
    MRCC_CR   = 0x00000081;

    #elif  MRCC_PLL_SRC == MRCC_PLL_IN_HSE 
    
    MRCC_CFGR = 0x00000000;

    #elif  MRCC_PLL_SRC == MRCC_PLL_IN_HALF_HSE
   
    MRCC_CFGR = 0x00000000;

    #endif


#else   
   #error("You've Chossen a Wrong CLK Type")
#endif



}  //END FUNCTIONS







void MRCC_voidPllConfigInit(void)
{

#if       MRCC_PLL_MUL  ==    MRCC_PLL_MUL_02X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_03X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_04X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_05X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_06X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_07X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_08X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_09X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_10X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_11X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_12X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_13X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_14X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_15X
MRCC_CFGR = 0x00000000; 
#elif     MRCC_PLL_MUL  ==    MRCC_PLL_MUL_16X
MRCC_CFGR = 0x00000000; 

#endif

}




void MRCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
                      
    if (Copy_u8PerId <=MRCC_MAX_NUMB_OF_PER)   //Input Validation
    {
        switch (Copy_u8BusId)
        {
            case MRCC_AHB  : SET_BIT(MRCC_AHBENR ,Copy_u8PerId);   break;
            case MRCC_APB1 : SET_BIT(MRCC_APB1ENR,Copy_u8PerId);   break;
            case MRCC_APB2 : SET_BIT(MRCC_APB2ENR,Copy_u8PerId);   break;
            //default       :  /*Return Error*/                    break;       //some compilers dont support to make an empty defult
        }
    }
    else
    {
        /*Return ERROR*/
    }

}

/*
void MRCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
                      
    if (Copy_u8PerId <=MRCC_MAX_NUMB_OF_PER)   //Input Validation
    {
        switch (Copy_u8BusId)
        {
            case MRCC_AHB  : CLR_BIT(MRCC_AHBENR ,Copy_u8PerId);   break;
            case MRCC_APB1 : CLR_BIT(MRCC_APB1ENR,Copy_u8PerId);   break;
            case MRCC_APB2 : CLR_BIT(MRCC_APB2ENR,Copy_u8PerId);   break;
            //default       :  //Return Error                    break;       //some compilers dont support to make an empty defult
        }
    }
    else
    {
        //Return ERROR
    }

}
*/
