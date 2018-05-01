/*
 * ADC.c
 *
 *  Created on: ٢٥‏/٠٢‏/٢٠١٨
 *      Author: El-safi
 */
#include "ADC.h"
#include <avr/io.h>
#include <util/delay.h>

void ADC_Init(void){//!Start setup function.

	ADCSRA |= 0x87;			// Enable ADC, with F/128
	ADCSRA|=(1<<ADIE);
	ADMUX = 0x40;			// VREF: AVCC, ADC channel: 0 Default.

}//! End of setup function.


void ADC_Read(U8_t channel){//!Start Read function.

ADMUX = 0x40 | (channel & 0x07); // set input channel to read
ADCSRA |= (1<<ADSC);		     //Start ADC conversion

}//! End of Read function.


