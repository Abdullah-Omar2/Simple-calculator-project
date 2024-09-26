/*
 * DIO_init.h
 *
 *  Created on: Aug 16, 2024
 *      Author: abdullahalazhary
 */

//Copy_u8PortID: DIO_PORTA or DIO_PORTB or DIO_PORTC or DIO_PORTD
//Copy_u8Direction: INPUT or OUTPUT for Pin & from 0 to 255 for Port
//Copy_u8Value: (HIGH or LOW for INPUT & FLOAT or PULL_UP for OUTPUT) for Pin & (from 0 to 255 for INPUT or OUTPUT) for Port
//Copy_u8PinID: DIO_PIN0 or DIO_PIN1 or DIO_PIN2 or DIO_PIN3 or DIO_PIN4 or DIO_PIN5 or DIO_PIN6 or DIO_PIN7
//INPUT=0 ,OUTPUT=1
//LOW=0  ,HIGH=1
//FLOAT=0 ,PULL_UP=1

#ifndef DIO_INIT_H_
#define DIO_INIT_H_

#include "DIO_priv.h"


ES_T DIO_enumPortInit (void);

ES_T DIO_enumSetPortDirection (u8 Copy_u8PortID,u8 Copy_u8Direction);
ES_T DIO_enumSetPortValue (u8 Copy_u8PortID,u8 Copy_u8Value);
ES_T DIO_enumTogglePortDirection (u8 Copy_u8PortID);
ES_T DIO_enumTogglePortValue (u8 Copy_u8PortID);
ES_T DIO_enumGetPortDirection (u8 Copy_u8PortID,u8 *Copy_pu8Direction);
ES_T DIO_enumGetPortValue (u8 Copy_u8PortID,u8 *Copy_pu8Value);

ES_T DIO_enumSetPinDirection (u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8Direction);
ES_T DIO_enumSetPinValue (u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8Value);
ES_T DIO_enumTogglePinDirection (u8 Copy_u8PortID,u8 Copy_u8PinID);
ES_T DIO_enumTogglePinValue (u8 Copy_u8PortID,u8 Copy_u8PinID);
ES_T DIO_enumGetPinDirection (u8 Copy_u8PortID,u8 Copy_u8PinID,u8 *Copy_pu8Direction);
ES_T DIO_enumGetPinValue (u8 Copy_u8PortID,u8 Copy_u8PinID,u8 *Copy_pu8Value);

#endif /* DIO_INIT_H_ */
