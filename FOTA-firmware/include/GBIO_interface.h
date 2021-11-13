/**************************************************************/
/***********     Author    :  SALAHELDIN             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  14-8-2020              **********/
/***********     File      :  GBIO_interface         **********/
/**************************************************************/

#ifndef _GBIO_INTERFACE_H
#define _GBIO_INTERFACE_H


/*****************************************************************/
/******                        Functions                    ******/
/*****************************************************************/

/* Choose a specific Pin to Set its Mode */
void MGBIO_vidSetPinDir    (u8 cpy_u8PortX ,u8 cpy_u8PinX  , u8 cpy_u8Mode );

/* Put a Value (HIGH/LOW) on a specific output pin */
//void MGBIO_vidSetPinValue  (u8 cpy_u8PortX , u8 cpy_u8PinX  , u8 cpy_u8Value);

/* Put a Value (HIGH/LOW) on a specific output PORT */
//void MGBIO_vidSetPortValue  (u8 cpy_u8PortX  , u16 cpy_u8Value);

/* Read a Value (HIGH/LOW) From a specific input pin */
//u8   MGBIO_u8GetPinValue   (u8 cpy_u8PortX , u8 cpy_u8PinX                );




/*****************************************************************/
/******                Function's parameters                ******/
/*****************************************************************/

/* Choose Port   */
#define MGBIOA             0
#define MGBIOB             1
#define MGBIOC             2

/* Choose Pin Number  */ 
#define MGBIO_PIN00        0
#define MGBIO_PIN01        1
#define MGBIO_PIN02        2
#define MGBIO_PIN03        3
#define MGBIO_PIN04        4
#define MGBIO_PIN05        5
#define MGBIO_PIN06        6
#define MGBIO_PIN07        7
#define MGBIO_PIN08        8
#define MGBIO_PIN09        9
#define MGBIO_PIN10        10
#define MGBIO_PIN11        11
#define MGBIO_PIN12        12
#define MGBIO_PIN13        13
#define MGBIO_PIN14        14
#define MGBIO_PIN15        15

/* Choose Value*/
#define MGBIO_LOW          0
#define MGBIO_HIGH         1
#define MGBIO_TOG          2



/****    choose  Pin Config & Modes      ****/
/* INPUT Config */
#define MGBIO_MODE_IN_ANALOG     0b0000
#define MGBIO_MODE_IN_FLOATING   0b0100
#define MGBIO_MODE_IN_PULL       0b1000


/* OUTPUT 10 MHZ  Mode Configurations */
#define MGBIO_MODE_10MHZ_OUT_PP        0b0001
#define MGBIO_MODE_10MHZ_OUT_OD        0b0101
#define MGBIO_MODE_10MHZ_OUT_AF_PP     0b1001
#define MGBIO_MODE_10MHZ_OUT_AF_OD     0b1101

/* OUTPUT 50 MHZ  Mode Configurations */
#define MGBIO_MODE_50MHz_OUT_PP        0b0011
#define MGBIO_MODE_50MHz_OUT_OD        0b0111
#define MGBIO_MODE_50MHz_OUT_AF_PP     0b1011
#define MGBIO_MODE_50MHz_OUT_AF_OD     0b1111

/* OUTPUT 2  MHZ  Mode Configurations */
#define MGBIO_MODE_2MHz_OUT_PP        0b0010
#define MGBIO_MODE_2MHz_OUT_OD        0b0110
#define MGBIO_MODE_2MHz_OUT_AF_PP     0b1010
#define MGBIO_MODE_2MHz_OUT_AF_OD     0b1110








#endif
