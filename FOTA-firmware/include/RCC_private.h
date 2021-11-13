/**************************************************************/
/* Author    :  SALAHELDIN                                    */
/* Version   :  V01                                           */
/* Date      :  8-8-2020                                      */
/**************************************************************/
#ifndef _RCC_PRIVATE_H
#define _RCC_PRIVATE_H


/*  Register Definitions  */
#define MRCC_CR                  *((u32*)0x40021000)
#define MRCC_CFGR                *((u32*)0x40021004)
#define MRCC_CIR                 *((u32*)0x40021008)
#define MRCC_APB2RSTR            *((u32*)0x4002100C)
#define MRCC_APB1RSTR            *((u32*)0x40021010)
#define MRCC_AHBENR              *((u32*)0x40021014)
#define MRCC_APB2ENR             *((u32*)0x40021018)
#define MRCC_APB1ENR             *((u32*)0x4002101C)
#define MRCC_CSR                 *((u32*)0x40021024)

/* SYS CLK OPTIONS*/
#define MRCC_SYS_IN_HSI          0
#define MRCC_SYS_IN_HSE_CRYSTAL  1
#define MRCC_SYS_IN_HSE_RC       2
#define MRCC_SYS_IN_PLL          3

/*PLL SRC Options*/
#define MRCC_PLL_IN_HALF_HSI     0
#define MRCC_PLL_IN_HSE          1
#define MRCC_PLL_IN_HALF_HSE     2

/*PLL MULTIPLICATION Options*/
#define MRCC_PLL_MUL_02X         2
#define MRCC_PLL_MUL_03X         3
#define MRCC_PLL_MUL_04X         4
#define MRCC_PLL_MUL_05X         5
#define MRCC_PLL_MUL_06X         6
#define MRCC_PLL_MUL_07X         7
#define MRCC_PLL_MUL_08X         8
#define MRCC_PLL_MUL_09X         9 
#define MRCC_PLL_MUL_10X         10 
#define MRCC_PLL_MUL_11X         11
#define MRCC_PLL_MUL_12X         12 
#define MRCC_PLL_MUL_13X         13
#define MRCC_PLL_MUL_14X         14
#define MRCC_PLL_MUL_15X         15
#define MRCC_PLL_MUL_16X         16
        

#define MRCC_MAX_NUMB_OF_PER     31

#endif