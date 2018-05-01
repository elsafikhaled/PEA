/*
 * EXT_INTERRUPT.c
 *
 *  Created on: ٠٩‏/٠٢‏/٢٠١٨
 *      Author: El-safi
 */
#include "EXT_INTERRUPT.h"
#include <avr/io.h>



void EXT_Interrupt_Setup(U8_t number){//!start of external interrupt configuration.

	//close all interrupts.
	EIMSK=0x00;
	//set falling edges pulses mode 0 and 1.
	EICRA=0x00;
	EICRB=0x00;
	//enable interrupts pins.
    EIMSK=number;
}//!End of external interrupt configuration.

