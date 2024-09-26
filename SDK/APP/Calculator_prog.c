/*
 * Calculator.c
 *
 *  Created on: Sep 24, 2024
 *      Author: abdullahalazhary
 */
#include <util/delay.h>
#include "../LIB/STDtypes.h"
#include "../LIB/Error_State.h"
#include "../LIB/BITMATH.h"
#include "../List/global.h"
#include "../List/list.h"
#include "../MCAL/DIO/DIO_config.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_config.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KEYPAD/KEYPAD_config.h"
#include "../HAL/KEYPAD/KEYPAD_int.h"

void Calculator_voidStart (void)
{
	KEYPAD_enumInit();
	u8 Local_u8OnOff=KEYPAD_NO_KEY_PRESSED;
	do
	{
		KEYPAD_enumGetPressedKey(&Local_u8OnOff);
	}while(Local_u8OnOff!='c');

	LCD_enumInit();
	LCD_enumGoTOPosition(1,4);
	LCD_enumSendString("WELCOME!");
	_delay_ms(1000);
	LCD_enumClear();
}

u8* Calculator_pu8EnterExpression(void)
{
	static u8 Local_Au8Expression[16];
	u8 Local_u8Counter=0;
	while(1)
	{
		u8 Local_u8PressedKey=KEYPAD_NO_KEY_PRESSED;
		do
		{
			KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
		}while(Local_u8PressedKey==KEYPAD_NO_KEY_PRESSED);

		if(Local_u8PressedKey=='=')
		{
			return Local_Au8Expression;
		}

		LCD_enumSendChar(Local_u8PressedKey);

		Local_Au8Expression[Local_u8Counter]=Local_u8PressedKey;
		Local_u8Counter++;

		if(Local_u8Counter==16)
		{
			break;
		}
	}

	while (1)
	{
		u8 Local_u8PressedKey=KEYPAD_NO_KEY_PRESSED;
		do
		{
			KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
		}while(Local_u8PressedKey==KEYPAD_NO_KEY_PRESSED);

		if(Local_u8PressedKey=='=')
		{
			return Local_Au8Expression;
		}
	}
}

void Calculator_pu8SloveExpression(u8* Copy_pu8Expression)
{
	listentry Local_leTerm;
	Local_leTerm.Term=0;
	listentry Local_leOP;
	u8 Local_u8IsNeg=0,Local_u8Counter=0;
	plist Local_listTerms;
	createlist (&Local_listTerms);
	plist Local_listOPs;
	createlist (&Local_listOPs);
	if(*Copy_pu8Expression=='-')
	{
		Local_u8IsNeg=1;
		Copy_pu8Expression++;
	}
	for(;*Copy_pu8Expression!=0;Copy_pu8Expression++)
	{
		if(*Copy_pu8Expression>='0'&&*Copy_pu8Expression<='9')
		{
			Local_leTerm.Term=Local_leTerm.Term*10+(*Copy_pu8Expression-'0');
		}
		if(*Copy_pu8Expression=='-'&&(*(Copy_pu8Expression-1)=='+'||*(Copy_pu8Expression-1)=='-'||*(Copy_pu8Expression-1)=='*'||*(Copy_pu8Expression-1)=='/'))
		{
			Local_u8IsNeg=1;
			Copy_pu8Expression++;
		}
		if(*Copy_pu8Expression=='+'||*Copy_pu8Expression=='-'||*Copy_pu8Expression=='*'||*Copy_pu8Expression=='/')
		{
			if(Local_u8IsNeg)
			{
				Local_leTerm.Term*=-1;
				Local_u8IsNeg=0;
			}
			insertlist (Local_u8Counter,Local_leTerm,Local_listTerms);
			Local_leOP.OP=*Copy_pu8Expression;
			insertlist (Local_u8Counter++,Local_leOP,Local_listOPs);
			Local_leTerm.Term=0;
		}
	}
	for(Local_u8Counter=0;;Local_u8Counter++)
	{
		listentry Local_leOP,Local_leTerm1,Local_leTerm2;
		retrievelist (Local_u8Counter,&Local_leOP,Local_listOPs);
		if(Local_leOP.OP==0)
		{
			break;
		}
		switch(Local_leOP.OP)
		{
		case '*':
			retrievelist (Local_u8Counter,&Local_leTerm1,Local_listTerms);
			retrievelist (Local_u8Counter+1,&Local_leTerm2,Local_listTerms);
			Local_leTerm1.Term=Local_leTerm1.Term*Local_leTerm2.Term;
			replacelist (Local_u8Counter,Local_leTerm1,Local_listTerms);
			deletlist (Local_u8Counter+1,&Local_leTerm1,Local_listTerms);
			deletlist (Local_u8Counter,&Local_leOP,Local_listOPs);
			Local_u8Counter--;
			break;
		case '/':
			retrievelist (Local_u8Counter,&Local_leTerm1,Local_listTerms);
			retrievelist (Local_u8Counter+1,&Local_leTerm2,Local_listTerms);
			Local_leTerm1.Term=Local_leTerm1.Term/Local_leTerm2.Term;
			replacelist (Local_u8Counter,Local_leTerm1,Local_listTerms);
			deletlist (Local_u8Counter+1,&Local_leTerm1,Local_listTerms);
			deletlist (Local_u8Counter,&Local_leOP,Local_listOPs);
			Local_u8Counter--;
			break;
		}
	}
	for(Local_u8Counter=0;;Local_u8Counter++)
	{
		listentry Local_leOP,Local_leTerm1,Local_leTerm2;
		retrievelist (Local_u8Counter,&Local_leOP,Local_listOPs);
		if(Local_leOP.OP==0)
		{
			break;
		}
		switch(Local_leOP.OP)
		{
		case '+':
			retrievelist (Local_u8Counter,&Local_leTerm1,Local_listTerms);
			retrievelist (Local_u8Counter+1,&Local_leTerm2,Local_listTerms);
			Local_leTerm1.Term=Local_leTerm1.Term+Local_leTerm2.Term;
			replacelist (Local_u8Counter,Local_leTerm1,Local_listTerms);
			deletlist (Local_u8Counter+1,&Local_leTerm1,Local_listTerms);
			deletlist (Local_u8Counter,&Local_leOP,Local_listOPs);
			Local_u8Counter--;
			break;
		case '-':
			retrievelist (Local_u8Counter,&Local_leTerm1,Local_listTerms);
			retrievelist (Local_u8Counter+1,&Local_leTerm2,Local_listTerms);
			Local_leTerm1.Term=Local_leTerm1.Term-Local_leTerm2.Term;
			replacelist (Local_u8Counter,Local_leTerm1,Local_listTerms);
			deletlist (Local_u8Counter+1,&Local_leTerm1,Local_listTerms);
			deletlist (Local_u8Counter,&Local_leOP,Local_listOPs);
			Local_u8Counter--;
			break;
		}
	}
	LCD_enumGoTOPosition(2,1);
	listentry Local_leResult;
	retrievelist (0,&Local_leResult,Local_listTerms);
	LCD_enumDisplayIntNum(Local_leResult.Term);
}
