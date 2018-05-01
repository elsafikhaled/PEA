/*
 * main.c
 *
 *  Created on: ٠٩‏/٠٣‏/٢٠١٨
 *      Author: El-safi
 */
#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"
#include "UASRT.h"
#include "timer1.h"
#include "EXT_INTERRUPT.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

//driving mode
#define MANUAL       0
#define ACCELERATOR  1
#define PEDAL_ASSIST 2
U8_t MODE=MANUAL;
/****************************************************************/
volatile U16_t counts=0,rev=0,rotations=0,digital=0,counter=0;
char buff[50],FLAG=0;
volatile U16_t pwm_val=0;
volatile U16_t PEA_PWM=0;

int main(void){

//enable pull up resistor in pins D0 D1.
DDRD&=~(1<<PD0)|(1<<PD1)|(1<<PD2);
DDRF=0x00;
PORTD|=(1<<PD0)|(1<<PD1);
//System initialization.
UASRT_Setup(0,0,0);
Timer1_Setup(3);
ADC_Init();
//enable global interrupt for ADC,CTC,HW service routine.
sei();
memset(buff, 0, 50);
MODE=MANUAL;

	while(1){
		        if(!(PIND&(1<<PD0))){//Choose mode::
		        	_delay_ms(500);
		        	counter++;

		        	  if(counter==1){
		        		  MODE=ACCELERATOR;
		        		 // USART_Write_String(0,(U8_t*)"ACCELERATOR:\n");
		        	  }
		        	  else if(counter==2){
		        		  MODE=PEDAL_ASSIST;
		        		 // USART_Write_String(0,(U8_t*)"PEA:\n");
		        	  }
		        	  else{
		        		    MODE=MANUAL;
		        		    counter=0;
		        	      }

		        }//Choose mode.

            //Choose mode::
		        switch(MODE){//!MODE SELECT.

		        case ACCELERATOR:
		        	Timer1_OFF();
		        	ADC_Read(5);
		        	break;
		        case PEDAL_ASSIST:
		        	Timer1_ON();
		        	ADC_Read(0);
		            break;
		        case MANUAL:
		        	Timer1_OFF();
		        	ADCSRA &=~ (1<<ADSC);
		        	USART_Write_byte(0,0);
		        	break;
		        default:
		        	break;

		        }//!MODE SELECT.


	        }

	return 0;
}



/* ***************************** CTC interrupt ***************************************/
ISR(TIMER1_COMPA_vect){//!CTC ISR

//get PWM
  rotations=counts;
  if(rotations>4)rotations=4;
  counts=0;
  PEA_PWM=rotations*10;
  USART_Write_byte(0,(10+PEA_PWM));
  //USART_Write_String(0,(U8_t*)"REVOLUTION:\n");
 // sprintf(buff,"%d",PEA_PWM+10);
  //USART_Write_String(0,(U8_t*)buff);
 // memset(buff, 0, 50);
  rotations=0;
  PEA_PWM=0;
  //USART_Write_byte(0,'\n');


}//!CTC ISR
/* ************************** ADC interrupt ***************************************/
ISR(ADC_vect){//!ADC ISR

//DIGITAL VALUES--COMMON USAGE.
digital=ADC;
//Choose mode to ACCESS it.
if(MODE==PEDAL_ASSIST){//!PEDAL ASSIST.

	if(digital>600){
		FLAG=TRUE;

	}
	if(digital<600){
	  if(FLAG==TRUE){
		  FLAG=FALSE;
		  counts++;
	  }
	}
}//!PEDAL ASSIST.
else if(MODE==ACCELERATOR){
	// memset(buff, 0, 50);
	 if(digital>204){
     pwm_val=(float)(0.0746)*(digital-204);
	 }
	  //sprintf(buff,"%d",pwm_val);
	  // USART_Write_String(0,(U8_t*)buff);
	  // memset(buff, 0, 50);
	  // USART_Write_byte(0,'\n');
	  USART_Write_byte(0,pwm_val);
	  pwm_val=0;
}
// Clear interrupt flag
   ADCSRA |= (1<<ADIF);


}//!ADC ISR


