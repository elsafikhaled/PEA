/*
 * ADC.h
 *
 *  Created on: ٢٥‏/٠٢‏/٢٠١٨
 *      Author: El-safi
 */

#ifndef ADC_H_
#define ADC_H_
#include "std_data_types.h"


/* ADC Initialization function */
void ADC_Init(void);

/**************************************
 * ADC Read function
 *  Return  :: 2 bytes in ISR
 *  channel :: 0 to 7
 *************************************/
void  ADC_Read(U8_t channel);

#endif /* ADC_H_ */
