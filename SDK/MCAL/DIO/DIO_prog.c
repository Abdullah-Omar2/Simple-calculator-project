/*
 * DIO_prog.c
 *
 *  Created on: Aug 16, 2024
 *      Author: abdullahalazhary
 */
#include "../../LIB/STDtypes.h"
#include "../../LIB/Error_State.h"
#include "../../LIB/BITMATH.h"
#include "DIO_priv.h"
#include "DIO_config.h"



ES_T DIO_enumPortInit (void)
{
	ES_T Local_enumErrorState=ES_NOK;

	DDRA=CONC(PA_PIN7_DIR,PA_PIN6_DIR,PA_PIN5_DIR,PA_PIN4_DIR,PA_PIN3_DIR,PA_PIN2_DIR,PA_PIN1_DIR,PA_PIN0_DIR);
	DDRB=CONC(PB_PIN7_DIR,PB_PIN6_DIR,PB_PIN5_DIR,PB_PIN4_DIR,PB_PIN3_DIR,PB_PIN2_DIR,PB_PIN1_DIR,PB_PIN0_DIR);
	DDRC=CONC(PC_PIN7_DIR,PC_PIN6_DIR,PC_PIN5_DIR,PC_PIN4_DIR,PC_PIN3_DIR,PC_PIN2_DIR,PC_PIN1_DIR,PC_PIN0_DIR);
	DDRD=CONC(PD_PIN7_DIR,PD_PIN6_DIR,PD_PIN5_DIR,PD_PIN4_DIR,PD_PIN3_DIR,PD_PIN2_DIR,PD_PIN1_DIR,PD_PIN0_DIR);

	PORTA=CONC(PA_PIN7_VAL,PA_PIN6_VAL,PA_PIN5_VAL,PA_PIN4_VAL,PA_PIN3_VAL,PA_PIN2_VAL,PA_PIN1_VAL,PA_PIN0_VAL);
	PORTB=CONC(PB_PIN7_VAL,PB_PIN6_VAL,PB_PIN5_VAL,PB_PIN4_VAL,PB_PIN3_VAL,PB_PIN2_VAL,PB_PIN1_VAL,PB_PIN0_VAL);
	PORTC=CONC(PC_PIN7_VAL,PC_PIN6_VAL,PC_PIN5_VAL,PC_PIN4_VAL,PC_PIN3_VAL,PC_PIN2_VAL,PC_PIN1_VAL,PC_PIN0_VAL);
	PORTD=CONC(PD_PIN7_VAL,PD_PIN6_VAL,PD_PIN5_VAL,PD_PIN4_VAL,PD_PIN3_VAL,PD_PIN2_VAL,PD_PIN1_VAL,PD_PIN0_VAL);

	Local_enumErrorState=ES_OK;

	return Local_enumErrorState;
}

ES_T DIO_enumSetPortDirection (u8 Copy_u8PortID,u8 Copy_u8Direction)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD)
	{
		switch(Copy_u8PortID)
		{
			case DIO_PORTA:
				DDRA=Copy_u8Direction;
				break;
			case DIO_PORTB:
				DDRB=Copy_u8Direction;
				break;
			case DIO_PORTC:
				DDRC=Copy_u8Direction;
				break;
			case DIO_PORTD:
				DDRD=Copy_u8Direction;
				break;
		}
		Local_enumErrorState=ES_OK;
	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}
ES_T DIO_enumSetPortValue (u8 Copy_u8PortID,u8 Copy_u8Value)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD)
	{
		switch(Copy_u8PortID)
		{
			case DIO_PORTA:
				PORTA=Copy_u8Value;
				break;
			case DIO_PORTB:
				PORTB=Copy_u8Value;
				break;
			case DIO_PORTC:
				PORTC=Copy_u8Value;
				break;
			case DIO_PORTD:
				PORTD=Copy_u8Value;
				break;
		}
		Local_enumErrorState=ES_OK;
	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}
ES_T DIO_enumTogglePortDirection (u8 Copy_u8PortID)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD)
	{
		switch(Copy_u8PortID)
		{
			case DIO_PORTA:
				DDRA=~DDRA;
				break;
			case DIO_PORTB:
				DDRB=~DDRB;
				break;
			case DIO_PORTC:
				DDRC=~DDRC;
				break;
			case DIO_PORTD:
				DDRD=~DDRD;
				break;
		}
		Local_enumErrorState=ES_OK;
	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}
ES_T DIO_enumTogglePortValue (u8 Copy_u8PortID)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD)
	{
		switch(Copy_u8PortID)
		{
			case DIO_PORTA:
				PORTA=~PORTA;
				break;
			case DIO_PORTB:
				PORTB=~PORTB;
				break;
			case DIO_PORTC:
				PORTC=~PORTC;
				break;
			case DIO_PORTD:
				PORTD=~PORTD;
				break;
		}
		Local_enumErrorState=ES_OK;
	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}
ES_T DIO_enumGetPortDirection (u8 Copy_u8PortID,u8 *Copy_pu8Direction)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD)
	{
		if (Copy_pu8Direction!=NULL)
		{
			switch(Copy_u8PortID)
			{
				case DIO_PORTA:
					*Copy_pu8Direction=DDRA;
					break;
				case DIO_PORTB:
					*Copy_pu8Direction=DDRB;
					break;
				case DIO_PORTC:
					*Copy_pu8Direction=DDRC;
					break;
				case DIO_PORTD:
					*Copy_pu8Direction=DDRD;
					break;
			}
			Local_enumErrorState=ES_OK;
		}
		else
		{
			Local_enumErrorState=ES_NULL_POINTER;
		}

	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}
ES_T DIO_enumGetPortValue (u8 Copy_u8PortID,u8 *Copy_pu8Value)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD)
	{
		if (Copy_pu8Value!=NULL)
		{
			switch(Copy_u8PortID)
			{
				case DIO_PORTA:
					*Copy_pu8Value=PINA;
					break;
				case DIO_PORTB:
					*Copy_pu8Value=PINB;
					break;
				case DIO_PORTC:
					*Copy_pu8Value=PINC;
					break;
				case DIO_PORTD:
					*Copy_pu8Value=PIND;
					break;
			}
			Local_enumErrorState=ES_OK;
		}
		else
		{
			Local_enumErrorState=ES_NULL_POINTER;
		}

	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}

ES_T DIO_enumSetPinDirection (u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8Direction)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD&& Copy_u8PinID <= DIO_PIN7 && Copy_u8Direction <= OUTPUT)
	{
		switch(Copy_u8PortID)
		{
			case DIO_PORTA:
				CLEAR_BIT(DDRA,Copy_u8PinID);
				DDRA |= (Copy_u8Direction << Copy_u8PinID);
				break;
			case DIO_PORTB:
				CLEAR_BIT(DDRB,Copy_u8PinID);
				DDRB |= (Copy_u8Direction << Copy_u8PinID);
				break;
			case DIO_PORTC:
				CLEAR_BIT(DDRC,Copy_u8PinID);
				DDRC |= (Copy_u8Direction << Copy_u8PinID);
				break;
			case DIO_PORTD:
				CLEAR_BIT(DDRD,Copy_u8PinID);
				DDRD |= (Copy_u8Direction << Copy_u8PinID);
				break;
		}
		Local_enumErrorState=ES_OK;
	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}
ES_T DIO_enumSetPinValue (u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8Value)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD&&Copy_u8PinID<=DIO_PIN7&&Copy_u8Value<=OUTPUT)
	{
		switch(Copy_u8PortID)
		{
			case DIO_PORTA:
				CLEAR_BIT(PORTA,Copy_u8PinID);
				PORTA |= (Copy_u8Value << Copy_u8PinID);
				break;
			case DIO_PORTB:
				CLEAR_BIT(PORTB,Copy_u8PinID);
				PORTB |= (Copy_u8Value << Copy_u8PinID);
				break;
			case DIO_PORTC:
				CLEAR_BIT(PORTC,Copy_u8PinID);
				PORTC |= (Copy_u8Value << Copy_u8PinID);
				break;
			case DIO_PORTD:
				CLEAR_BIT(PORTD,Copy_u8PinID);
				PORTD |= (Copy_u8Value << Copy_u8PinID);
				break;
		}
		Local_enumErrorState=ES_OK;
	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}
ES_T DIO_enumTogglePinDirection (u8 Copy_u8PortID,u8 Copy_u8PinID)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD&&Copy_u8PinID<=DIO_PIN7)
	{
		switch(Copy_u8PortID)
		{
			case DIO_PORTA:
				TOGGLE_BIT(DDRA,Copy_u8PinID);
				break;
			case DIO_PORTB:
				TOGGLE_BIT(DDRB,Copy_u8PinID);
				break;
			case DIO_PORTC:
				TOGGLE_BIT(DDRC,Copy_u8PinID);
				break;
			case DIO_PORTD:
				TOGGLE_BIT(DDRD,Copy_u8PinID);
				break;
		}
		Local_enumErrorState=ES_OK;
	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}
ES_T DIO_enumTogglePinValue (u8 Copy_u8PortID,u8 Copy_u8PinID)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD&&Copy_u8PinID<=DIO_PIN7)
	{
		switch(Copy_u8PortID)
		{
			case DIO_PORTA:
				TOGGLE_BIT(PORTA,Copy_u8PinID);
				break;
			case DIO_PORTB:
				TOGGLE_BIT(PORTB,Copy_u8PinID);
				break;
			case DIO_PORTC:
				TOGGLE_BIT(PORTC,Copy_u8PinID);
				break;
			case DIO_PORTD:
				TOGGLE_BIT(PORTD,Copy_u8PinID);
				break;
		}
		Local_enumErrorState=ES_OK;
	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}
ES_T DIO_enumGetPinDirection (u8 Copy_u8PortID,u8 Copy_u8PinID,u8 *Copy_pu8Direction)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD&&Copy_u8PinID<=DIO_PIN7)
		{
			if (Copy_pu8Direction!=NULL)
			{
				switch(Copy_u8PortID)
				{
					case DIO_PORTA:
						*Copy_pu8Direction=READ_BIT(DDRA,Copy_u8PinID);
						break;
					case DIO_PORTB:
						*Copy_pu8Direction=READ_BIT(DDRB,Copy_u8PinID);
						break;
					case DIO_PORTC:
						*Copy_pu8Direction=READ_BIT(DDRC,Copy_u8PinID);
						break;
					case DIO_PORTD:
						*Copy_pu8Direction=READ_BIT(DDRD,Copy_u8PinID);
						break;
				}
				Local_enumErrorState=ES_OK;
			}
			else
			{
				Local_enumErrorState=ES_NULL_POINTER;
			}
		}
		else
		{
			Local_enumErrorState=ES_OUT_OF_RANGE;
		}

	return Local_enumErrorState;
}
ES_T DIO_enumGetPinValue (u8 Copy_u8PortID,u8 Copy_u8PinID,u8 *Copy_pu8Value)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_u8PortID<=DIO_PORTD&&Copy_u8PinID<=DIO_PIN7)
	{
		if (Copy_pu8Value!=NULL)
		{
			switch(Copy_u8PortID)
			{
				case DIO_PORTA:
					*Copy_pu8Value=READ_BIT(PINA,Copy_u8PinID);
					break;
				case DIO_PORTB:
					*Copy_pu8Value=READ_BIT(PINB,Copy_u8PinID);
					break;
				case DIO_PORTC:
					*Copy_pu8Value=READ_BIT(PINC,Copy_u8PinID);
					break;
				case DIO_PORTD:
					*Copy_pu8Value=READ_BIT(PIND,Copy_u8PinID);
					break;
			}
			Local_enumErrorState=ES_OK;
		}
		else
		{
			Local_enumErrorState=ES_NULL_POINTER;
		}
	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}
