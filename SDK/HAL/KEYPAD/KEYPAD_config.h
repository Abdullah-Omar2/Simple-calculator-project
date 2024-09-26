/*
 * KEYPAD_config.h
 *
 *  Created on: Sep 22, 2024
 *      Author: abdullahalazhary
 */

#ifndef INCLUDE_HAL_KEYPAD_KEYPAD_CONFIG_H_
#define INCLUDE_HAL_KEYPAD_KEYPAD_CONFIG_H_

#define KEYPAD_KEYS_VAL		{ {'7','8','9','/'},\
    						  {'4','5','6','*'},\
							  {'1','2','3','-'},\
							  {'c','0','=','+'} }

#define KEYPAD_NO_KEY_PRESSED	0xFF

#define KEYPAD_C0_PORT		DIO_PORTD
#define KEYPAD_C0_PIN 		DIO_PIN0
#define KEYPAD_C1_PORT 		DIO_PORTD
#define KEYPAD_C1_PIN 		DIO_PIN1
#define KEYPAD_C2_PORT 		DIO_PORTD
#define KEYPAD_C2_PIN 		DIO_PIN2
#define KEYPAD_C3_PORT 		DIO_PORTD
#define KEYPAD_C3_PIN 		DIO_PIN3
#define KEYPAD_R0_PORT 		DIO_PORTC
#define KEYPAD_R0_PIN 		DIO_PIN0
#define KEYPAD_R1_PORT 		DIO_PORTC
#define KEYPAD_R1_PIN 		DIO_PIN1
#define KEYPAD_R2_PORT 		DIO_PORTC
#define KEYPAD_R2_PIN 		DIO_PIN2
#define KEYPAD_R3_PORT 		DIO_PORTC
#define KEYPAD_R3_PIN 		DIO_PIN3

#endif /* INCLUDE_HAL_KEYPAD_KEYPAD_CONFIG_H_ */
