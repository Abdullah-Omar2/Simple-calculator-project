/*
 * KEYPAD_prog.c
 *
 *  Created on: Sep 22, 2024
 *      Author: abdullahalazhary
 */
#include "../../LIB/BITMATH.h"
#include "../../LIB/Error_State.h"
#include "../../LIB/STDtypes.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "KEYPAD_priv.h"
#include "KEYPAD_config.h"

ES_T KEYPAD_enumInit(void)
{
	ES_T Local_enumErrorState=ES_NOK;

	Local_enumErrorState=DIO_enumSetPinDirection(KEYPAD_C0_PORT,KEYPAD_C0_PIN,OUTPUT);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinDirection(KEYPAD_C1_PORT,KEYPAD_C1_PIN,OUTPUT);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinDirection(KEYPAD_C2_PORT,KEYPAD_C2_PIN,OUTPUT);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinDirection(KEYPAD_C3_PORT,KEYPAD_C3_PIN,OUTPUT);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

	Local_enumErrorState=DIO_enumSetPinValue(KEYPAD_C0_PORT,KEYPAD_C0_PIN,HIGH);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(KEYPAD_C1_PORT,KEYPAD_C1_PIN,HIGH);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(KEYPAD_C2_PORT,KEYPAD_C2_PIN,HIGH);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(KEYPAD_C3_PORT,KEYPAD_C3_PIN,HIGH);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

	Local_enumErrorState=DIO_enumSetPinDirection(KEYPAD_R0_PORT,KEYPAD_R0_PIN,INPUT);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinDirection(KEYPAD_R1_PORT,KEYPAD_R1_PIN,INPUT);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinDirection(KEYPAD_R2_PORT,KEYPAD_R2_PIN,INPUT);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinDirection(KEYPAD_R3_PORT,KEYPAD_R3_PIN,INPUT);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

	Local_enumErrorState=DIO_enumSetPinValue(KEYPAD_R0_PORT,KEYPAD_R0_PIN,PULL_UP);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(KEYPAD_R1_PORT,KEYPAD_R1_PIN,PULL_UP);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(KEYPAD_R2_PORT,KEYPAD_R2_PIN,PULL_UP);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(KEYPAD_R3_PORT,KEYPAD_R3_PIN,PULL_UP);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

	return Local_enumErrorState;
}

ES_T KEYPAD_enumGetPressedKey(u8* Copy_pu8PressedKey)
{
	ES_T Local_enumErrorState=ES_NOK;

	static u8 Local_Au8ColPorts[KEYPAD_COL_NUM]={KEYPAD_C0_PORT,KEYPAD_C1_PORT,KEYPAD_C2_PORT,KEYPAD_C3_PORT};
	static u8 Local_Au8ColPins[KEYPAD_COL_NUM]={KEYPAD_C0_PIN,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN};

	static u8 Local_Au8RowPorts[KEYPAD_ROW_NUM]={KEYPAD_R0_PORT,KEYPAD_R1_PORT,KEYPAD_R2_PORT,KEYPAD_R3_PORT};
	static u8 Local_Au8RowPins[KEYPAD_ROW_NUM]={KEYPAD_R0_PIN,KEYPAD_R1_PIN,KEYPAD_R2_PIN,KEYPAD_R3_PIN};

	static u8 Local_Au8KeysVal[KEYPAD_ROW_NUM][KEYPAD_COL_NUM]=KEYPAD_KEYS_VAL;

	*Copy_pu8PressedKey=KEYPAD_NO_KEY_PRESSED;

	u8 Local_u8ColCounter=0,Local_u8RowCounter=0,Local_u8PinVal;

	for(Local_u8ColCounter=0;Local_u8ColCounter<KEYPAD_COL_NUM;Local_u8ColCounter++)
	{
		Local_enumErrorState=DIO_enumSetPinValue (Local_Au8ColPorts[Local_u8ColCounter],Local_Au8ColPins[Local_u8ColCounter],LOW);
		if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

		for(Local_u8RowCounter=0;Local_u8RowCounter<KEYPAD_ROW_NUM;Local_u8RowCounter++)
		{
			Local_enumErrorState=DIO_enumGetPinValue (Local_Au8RowPorts[Local_u8RowCounter],Local_Au8RowPins[Local_u8RowCounter],&Local_u8PinVal);
			if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

			if(LOW==Local_u8PinVal)
			{
				*Copy_pu8PressedKey=Local_Au8KeysVal[Local_u8RowCounter][Local_u8ColCounter];

				while(LOW==Local_u8PinVal)
				{
					Local_enumErrorState=DIO_enumGetPinValue (Local_Au8RowPorts[Local_u8RowCounter],Local_Au8RowPins[Local_u8RowCounter],&Local_u8PinVal);
					if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
				}

				return Local_enumErrorState;
			}
		}

		Local_enumErrorState=DIO_enumSetPinValue (Local_Au8ColPorts[Local_u8ColCounter],Local_Au8ColPins[Local_u8ColCounter],HIGH);
		if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	}

	return Local_enumErrorState;
}

