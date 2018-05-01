/*
 * EXT_INTERRUPT.h
 *
 *  Created on: ٠٩‏/٠٢‏/٢٠١٨
 *      Author: El-safi
 */

#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_
#include "std_data_types.h"

void EXT_Interrupt_Setup(U8_t number);
/*
 * Function   :: setup external interrupt registers - LOW PULSE more  than 50 ns to request it.
 * parameters :: number <<number of pins for low interrupt (1 to 4) >>
 **************************************************************************************************/

#endif /* EXT_INTERRUPT_H_ */
