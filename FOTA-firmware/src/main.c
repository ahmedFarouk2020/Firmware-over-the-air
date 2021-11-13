/*
 * main.c
 *
 *  Created on: Oct 26, 2020
 *      Author: salah
 */

/*Include App Layer*/
#include "BTL_interface.h"


void main (void)
{
	//Bootloader Init
	 ABTL_vidInit(); // connect to server manually

	 // BootLoader Start
	 ABTL_vidStart();
} //END Main*/
