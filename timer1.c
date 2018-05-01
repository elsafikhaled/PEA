/*
 * timer1.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: El-safi
 */
#include "timer1.h"
#include <avr/io.h>

void Timer1_Setup(U8_t sec){//!Start setup

//CTC mode but disconnect OCNX  pins
	TCCR1A=0x00;
//PRESCALER 1024.so Tick F=7812.5HZ, 1_Tick=128uSec,
    TCCR1B=(1<<CS12)|(1<<CS10)|(1<<WGM12);
//Force Output Compare for Channel A
    TCCR1C=(1<<FOC1A);
//clear Tick counter register.
    TCNT1=0x00;
//load CTC register to be matched with TCNT
         if(sec==1)OCR1A=7896;
    else if(sec==2)OCR1A=15792;
    else if(sec==3)OCR1A=23688;
    else if(sec==4)OCR1A=31583;
    else if(sec==5)OCR1A=39479;
    else if(sec==6)OCR1A=47375;
    else if(sec==7)OCR1A=55270;
    else if(sec==8)OCR1A=63166;

}//! End of setup.


void Timer1_OFF(void){//!Start setup

//Disable Output Compare A Match Interrupt.
    TIMSK=0;

}//! End of setup.


void Timer1_ON(void){//!Start setup

//ENable Output Compare A Match Interrupt.
    TIMSK=(1<<OCIE1A);

}//! End of setup.
