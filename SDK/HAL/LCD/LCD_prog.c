/*
 * LCD_prog.c
 *
 *  Created on: Sep 6, 2024
 *      Author: abdullahalazhary
 */
#include <util/delay.h>
#include "../../LIB/STDtypes.h"
#include "../../LIB/Error_State.h"
#include "../../LIB/BITMATH.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "LCD_priv.h"
#include "LCD_config.h"

ES_T LCD_enumInit(void)
{
	ES_T Local_enumErrorState=ES_NOK;

    _delay_ms(35);
    Local_enumErrorState=DIO_enumSetPinDirection(LCD_RS_PORT,LCD_RS_PIN,OUTPUT);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinDirection(LCD_RW_PORT,LCD_RW_PIN,OUTPUT);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinDirection(LCD_EN_PORT,LCD_EN_PIN,OUTPUT);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

    Local_enumErrorState=DIO_enumSetPinDirection(LCD_D7_PORT,LCD_D7_PIN,OUTPUT);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinDirection(LCD_D6_PORT,LCD_D6_PIN,OUTPUT);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinDirection(LCD_D5_PORT,LCD_D5_PIN,OUTPUT);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinDirection(LCD_D4_PORT,LCD_D4_PIN,OUTPUT);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

#if LCD_MODE == EIGHT_BIT

    Local_enumErrorState=DIO_enumSetPinDirection(LCD_D3_PORT,LCD_D3_PIN,OUTPUT);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinDirection(LCD_D2_PORT,LCD_D2_PIN,OUTPUT);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinDirection(LCD_D1_PORT,LCD_D1_PIN,OUTPUT);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinDirection(LCD_D0_PORT,LCD_D0_PIN,OUTPUT);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

    Local_enumErrorState=LCD_inlenumSendCommand(0x38);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

#elif LCD_MODE == FOUR_BIT

    Local_enumErrorState=LCD_inlenumSendCommand(0x02);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=LCD_inlenumSendCommand(0x28);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

#else

#error"wrong LCD_MODE"

#endif

    _delay_ms(1);

    Local_enumErrorState=LCD_inlenumSendCommand(0x0D);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

    _delay_ms(1);

    Local_enumErrorState=LCD_inlenumSendCommand(0x01);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

    _delay_ms(3);

    Local_enumErrorState=LCD_inlenumSendCommand(0x06);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

    _delay_ms(1);

    Local_enumErrorState=LCD_inlenumSendCommand(0x80);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

    Local_enumErrorState=ES_OK;

	return Local_enumErrorState;
}

static inline ES_T LCD_inlenumSendCommand(u8 Copy_u8Command)
{
	ES_T Local_enumErrorState=ES_NOK;

    Local_enumErrorState=DIO_enumSetPinValue(LCD_RS_PORT,LCD_RS_PIN,LOW);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_EN_PORT,LCD_EN_PIN,LOW);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_RW_PORT,LCD_RW_PIN,LOW);
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

#if LCD_MODE == EIGHT_BIT

    Local_enumErrorState=DIO_enumSetPinValue(LCD_D7_PORT,LCD_D7_PIN,READ_BIT(Copy_u8Command,7));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_D6_PORT,LCD_D6_PIN,READ_BIT(Copy_u8Command,6));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_D5_PORT,LCD_D5_PIN,READ_BIT(Copy_u8Command,5));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_D4_PORT,LCD_D4_PIN,READ_BIT(Copy_u8Command,4));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_D3_PORT,LCD_D3_PIN,READ_BIT(Copy_u8Command,3));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_D2_PORT,LCD_D2_PIN,READ_BIT(Copy_u8Command,2));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_D1_PORT,LCD_D1_PIN,READ_BIT(Copy_u8Command,1));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_D0_PORT,LCD_D0_PIN,READ_BIT(Copy_u8Command,0));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

    Local_enumErrorState=LCD_inlenumLatch();
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

#elif LCD_MODE == FOUR_BIT

    Local_enumErrorState=DIO_enumSetPinValue(LCD_D7_PORT,LCD_D7_PIN,READ_BIT(Copy_u8Command,7));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_D6_PORT,LCD_D6_PIN,READ_BIT(Copy_u8Command,6));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_D5_PORT,LCD_D5_PIN,READ_BIT(Copy_u8Command,5));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
    Local_enumErrorState=DIO_enumSetPinValue(LCD_D4_PORT,LCD_D4_PIN,READ_BIT(Copy_u8Command,4));
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

    Local_enumErrorState=LCD_inlenumLatch();
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

	Local_enumErrorState=DIO_enumSetPinValue(LCD_D7_PORT,LCD_D7_PIN,READ_BIT(Copy_u8Command,3));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D6_PORT,LCD_D6_PIN,READ_BIT(Copy_u8Command,2));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D5_PORT,LCD_D5_PIN,READ_BIT(Copy_u8Command,1));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D4_PORT,LCD_D4_PIN,READ_BIT(Copy_u8Command,0));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

	Local_enumErrorState=LCD_inlenumLatch();
    if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

#else

#error"wrong LCD_MODE"

#endif

	Local_enumErrorState=ES_OK;

	return Local_enumErrorState;
}

static inline ES_T LCD_inlenumLatch(void)
{
	ES_T Local_enumErrorState=ES_NOK;

	Local_enumErrorState=DIO_enumSetPinValue(LCD_EN_PORT,LCD_EN_PIN,HIGH);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	_delay_ms(2);
	Local_enumErrorState=DIO_enumSetPinValue(LCD_EN_PORT,LCD_EN_PIN,LOW);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	_delay_ms(5);

	Local_enumErrorState=ES_OK;

	return Local_enumErrorState;
}

ES_T LCD_enumSendChar(u8 Copy_u8Char)
{
	ES_T Local_enumErrorState=ES_NOK;

	Local_enumErrorState=LCD_inlenumSendChar(Copy_u8Char);

	return Local_enumErrorState;
}

static inline ES_T LCD_inlenumSendChar(u8 Copy_u8Char)
{
	ES_T Local_enumErrorState=ES_NOK;

	Local_enumErrorState=DIO_enumSetPinValue(LCD_RS_PORT,LCD_RS_PIN,HIGH);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_EN_PORT,LCD_EN_PIN,LOW);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_RW_PORT,LCD_RW_PIN,LOW);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

#if LCD_MODE == EIGHT_BIT

	Local_enumErrorState=DIO_enumSetPinValue(LCD_D7_PORT,LCD_D7_PIN,READ_BIT(Copy_u8Char,7));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D6_PORT,LCD_D6_PIN,READ_BIT(Copy_u8Char,6));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D5_PORT,LCD_D5_PIN,READ_BIT(Copy_u8Char,5));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D4_PORT,LCD_D4_PIN,READ_BIT(Copy_u8Char,4));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D3_PORT,LCD_D3_PIN,READ_BIT(Copy_u8Char,3));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D2_PORT,LCD_D2_PIN,READ_BIT(Copy_u8Char,2));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D1_PORT,LCD_D1_PIN,READ_BIT(Copy_u8Char,1));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D0_PORT,LCD_D0_PIN,READ_BIT(Copy_u8Char,0));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

	Local_enumErrorState=LCD_inlenumLatch();
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

#elif LCD_MODE == FOUR_BIT

	Local_enumErrorState=DIO_enumSetPinValue(LCD_D7_PORT,LCD_D7_PIN,READ_BIT(Copy_u8Char,7));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D6_PORT,LCD_D6_PIN,READ_BIT(Copy_u8Char,6));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D5_PORT,LCD_D5_PIN,READ_BIT(Copy_u8Char,5));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D4_PORT,LCD_D4_PIN,READ_BIT(Copy_u8Char,4));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

	Local_enumErrorState=LCD_inlenumLatch();
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

	Local_enumErrorState=DIO_enumSetPinValue(LCD_D7_PORT,LCD_D7_PIN,READ_BIT(Copy_u8Char,3));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D6_PORT,LCD_D6_PIN,READ_BIT(Copy_u8Char,2));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D5_PORT,LCD_D5_PIN,READ_BIT(Copy_u8Char,1));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=DIO_enumSetPinValue(LCD_D4_PORT,LCD_D4_PIN,READ_BIT(Copy_u8Char,0));
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

	Local_enumErrorState=LCD_inlenumLatch();
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

#else

#error"wrong LCD_MODE"

#endif

	return Local_enumErrorState;
}

ES_T LCD_enumSendCommand(u8 Copy_u8Command)
{
	ES_T Local_enumErrorState=ES_NOK;

	Local_enumErrorState=LCD_inlenumSendCommand(Copy_u8Command);

	return Local_enumErrorState;
}

ES_T LCD_enumSendString(u8* Copy_pu8String)
{
	ES_T Local_enumErrorState=ES_NOK;

	Local_enumErrorState=LCD_inlenumSendString(Copy_pu8String);

	return Local_enumErrorState;
}

static inline ES_T LCD_inlenumSendString(u8* Copy_pu8String)
{
	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_pu8String!=NULL)
	{
		for(;;Copy_pu8String++)
		{
			if(*Copy_pu8String!=0)
			{
				Local_enumErrorState=LCD_inlenumSendChar(*Copy_pu8String);
				if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
			}
			else
			{
				break;
			}
		}
		Local_enumErrorState=ES_OK;
	}
	else
	{
		Local_enumErrorState=ES_NULL_POINTER;
	}

	return Local_enumErrorState;
}

ES_T LCD_enumGoTOPosition(u8 Copy_u8Row,u8 Copy_u8Col)
{
	ES_T Local_enumErrorState=ES_NOK;

	if ((Copy_u8Row<=2&&Copy_u8Row>=1)&&(Copy_u8Col<=16&&Copy_u8Col>=1))
	{
		u8 Local_u8Position=0;
		if(Copy_u8Row==1)
		{
			Local_u8Position=0x80;
			Local_enumErrorState=LCD_inlenumSendCommand(Local_u8Position+Copy_u8Col-1);
			if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
		}
		else if (Copy_u8Row==2)
		{
			Local_u8Position=0xC0;
			Local_enumErrorState=LCD_inlenumSendCommand(Local_u8Position+Copy_u8Col-1);
			if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
		}
	}
	else
	{
		Local_enumErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enumErrorState;
}

ES_T LCD_enumDisplayIntNum(s64 Copy_s64Num)
{
	ES_T Local_enumErrorState=ES_NOK;

	Local_enumErrorState=LCD_inlenumDisplayIntNum(Copy_s64Num);

	return Local_enumErrorState;
}

static inline ES_T LCD_inlenumDisplayIntNum(s32 Copy_s64Num)
{
	ES_T Local_enumErrorState=ES_NOK;

	if(Copy_s64Num < 0)
	{
		Local_enumErrorState=LCD_inlenumSendChar('-');
		if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
		Copy_s64Num *= -1;
	}

	u8 Local_Au8Buffer[10];
	u8 Local_u8Index = 0;

	if(Copy_s64Num == 0)
	{
		Local_enumErrorState=LCD_inlenumSendChar('0');
		if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	}
	else
	{
		while(Copy_s64Num > 0)
		{
			Local_Au8Buffer[Local_u8Index++] = (Copy_s64Num % 10) + '0';
			Copy_s64Num /= 10;
		}

		while(Local_u8Index > 0)
		{
			Local_enumErrorState=LCD_inlenumSendChar(Local_Au8Buffer[--Local_u8Index]);
			if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
		}
	}

	Local_enumErrorState=ES_OK;

	return Local_enumErrorState;
}

ES_T LCD_enumDisplayFloatNum(f32 Copy_f32Num)
{
	ES_T Local_enumErrorState=ES_NOK;

	if(Copy_f32Num<0)
	{
		Local_enumErrorState=LCD_inlenumSendChar('-');
		if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
		Copy_f32Num*=-1;
	}

	u16 Local_u16Left = (u16)Copy_f32Num;

	Local_enumErrorState=LCD_inlenumDisplayIntNum(Local_u16Left);
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
	Local_enumErrorState=LCD_inlenumSendChar('.');
	if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

	f32 Local_f32Fraction=Copy_f32Num-(f32)Local_u16Left+.00005;
	for (int i=0;i<4;i++)
	{
		Local_f32Fraction *= 10;
		u8 Local_u8Digit = (u8)Local_f32Fraction;
		Local_enumErrorState=LCD_inlenumSendChar(Local_u8Digit + '0');
		if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
		Local_f32Fraction -= Local_u8Digit;
	}

	return Local_enumErrorState;
}

ES_T LCD_enumSendCustomChar(u8 Copy_u8Pos,u8* Copy_pu8Char)
{

	ES_T Local_enumErrorState=ES_NOK;

	if (Copy_pu8Char!=NULL)
	{
		if(Copy_u8Pos<=7&&Copy_u8Pos>=0)
		{
			u8 Local_u8Counter=0;

			Local_enumErrorState=LCD_inlenumSendCommand(0x40+Copy_u8Pos*8);
			if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;

			for (Local_u8Counter=0;Local_u8Counter< 8;Local_u8Counter++)
			{
				Local_enumErrorState=LCD_inlenumSendChar(Copy_pu8Char[Local_u8Counter]);
				if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
			}

			Local_enumErrorState=LCD_inlenumSendCommand(0x80);
			if(Local_enumErrorState!=ES_OK)return Local_enumErrorState;
		}
		else
		{
			Local_enumErrorState=ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enumErrorState=ES_NULL_POINTER;
	}

	return Local_enumErrorState;
}

ES_T LCD_enumClear(void)
{
	ES_T Local_enumErrorState=ES_NOK;

	Local_enumErrorState=LCD_inlenumSendCommand(0x01);

	return Local_enumErrorState;
}
