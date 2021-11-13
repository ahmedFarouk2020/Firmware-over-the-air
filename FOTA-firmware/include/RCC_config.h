/**************************************************************/
/* Author    :  SALAHELDIN                                    */
/* Version   :  V01                                           */
/* Date      :  8-8-2020                                      */
/**************************************************************/
#ifndef _RCC_CONFIG_H
#define _RCC_CONFIG_H


/*System Clock Options:   
                        MRCC_SYS_IN_HSI        
                        MRCC_SYS_IN_HSE_CRYSTAL
                        MRCC_SYS_IN_HSE_RC     
                        MRCC_SYS_IN_PLL        
                                               */
#define MRCC_SYS_CLCK     MRCC_SYS_IN_HSI



/*PLL INPUT Options: MRCC_PLL_IN_HALF_HSI
                     MRCC_PLL_IN_HSE     
                     MRCC_PLL_IN_HALF_HSE */
/*Configure it Only if PLL is used as System Clock*/
#if MRCC_SYS_CLCK == MRCC_SYS_IN_PLL
#define MRCC_PLL_SRC      MRCC_PLL_IN_HALF_HSI
#endif

/*PLL Multipliciation Options: 02 to 16 */
/*Configer it Only if PLL is used as System Clock*/
#if MRCC_SYS_CLCK == MRCC_SYS_IN_PLL
#define MRCC_PLL_MUL      MRCC_PLL_MUL_02X 
#endif








#endif
