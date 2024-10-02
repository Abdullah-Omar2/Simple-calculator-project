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
#include "../List/list.h"
#include "../MCAL/DIO/DIO_config.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_config.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KEYPAD/KEYPAD_config.h"
#include "../HAL/KEYPAD/KEYPAD_int.h"

void Calculator_voidStart (void)
{
	u8 Local_u8PressedKey;
	KEYPAD_enumInit();
	do
	{
		KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
	}while(Local_u8PressedKey!='c');
	LCD_enumInit();
	LCD_enumGoTOPosition(1,5);
	LCD_enumSendString((u8*)"WELCOME!");
	_delay_ms(1000);
	LCD_enumClear();
	LCD_enumCursorEnable();
}

void Calculator_voidRun (plist Copy_listTerms,plist Copy_listOPs)
{
	u8 Local_Au8Nums[15];
	u8 Local_u8Counter1=0,Local_u8Counter2=0,Local_u8Counter3=0,Local_u8Counter4=0;
	s32 Local_s32IsNeg=1;
	u8 Local_u8PressedKey=KEYPAD_NO_KEY_PRESSED;
	l:
	while(1)
	{
		do
		{
			KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
		}while(Local_u8PressedKey==KEYPAD_NO_KEY_PRESSED);
		if(Local_u8Counter4==15&&Local_u8PressedKey!='=')
		{
			continue;
		}
		LCD_enumSendChar(Local_u8PressedKey);
		Local_u8Counter4++;
		switch(Local_u8PressedKey)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			Local_Au8Nums[Local_u8Counter1++]=Local_u8PressedKey;
			break;
		case '-':
			if (Local_u8Counter1 == 0 || Local_Au8Nums[Local_u8Counter1 - 1] == ' ')
			{
				Local_Au8Nums[Local_u8Counter1++]=Local_u8PressedKey;
			}
			else if(Local_Au8Nums[Local_u8Counter1 - 1] == '-')
			{
				insertlist(Local_u8Counter2++,Local_u8PressedKey,Copy_listOPs);
			}
			else
			{
				Local_Au8Nums[Local_u8Counter1++]=' ';
				insertlist(Local_u8Counter2++,Local_u8PressedKey,Copy_listOPs);
			}
			break;
		case '+':
		case '*':
		case '/':
			Local_Au8Nums[Local_u8Counter1++]=' ';
			insertlist(Local_u8Counter2++,Local_u8PressedKey,Copy_listOPs);
			break;
		case '=':
			Local_Au8Nums[Local_u8Counter1] = '\0';
			Local_u8Counter1=0,Local_u8Counter2=0;
			while(Local_Au8Nums[Local_u8Counter1]!='\0')
			{
				s32 Local_s32Term=0;
				if(Local_Au8Nums[Local_u8Counter1]=='-')
				{
					Local_s32IsNeg*=-1;
					Local_u8Counter1++;
				}
				while(Local_Au8Nums[Local_u8Counter1]>='0'&&Local_Au8Nums[Local_u8Counter1]<='9')
				{
					Local_s32Term=Local_s32Term*10+(Local_Au8Nums[Local_u8Counter1++]-'0');
				}
				if(Local_Au8Nums[Local_u8Counter1-1]!=' ')
				{
					insertlist(Local_u8Counter3++,Local_s32Term*Local_s32IsNeg,Copy_listTerms);
				}
				Local_s32IsNeg=1;
				if(Local_Au8Nums[Local_u8Counter1]==' ')
				{
					Local_u8Counter1++;
				}
			}
			LCD_enumGoTOPosition(2,1);

			if(listsize(Copy_listTerms)!=listsize(Copy_listOPs)+1)
			{
				LCD_enumSendString((u8*)"Wrong expression");
				LCD_enumSendCommand(0x0C);
				do
				{
					KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
				}while(Local_u8PressedKey==KEYPAD_NO_KEY_PRESSED);
				Local_u8Counter4=0,Local_u8Counter1=0,Local_u8Counter2=0,Local_u8Counter3=0;
				LCD_enumClear();
				destroylist (&Copy_listOPs);
				destroylist (&Copy_listTerms);
				for(u8 i=0;i<10;i++)
				{
					Local_Au8Nums[i]=0;
				}
				LCD_enumCursorEnable();
				break;
			}

			u8 Local_u8Counter5=0;
			while(1)//[+-*/-+]
			{
				listentry op;
				retrievelist (Local_u8Counter5,&op,Copy_listOPs);
				if(op=='*')
				{
					listentry t1,t2;
					retrievelist (Local_u8Counter5,&t1,Copy_listTerms);
					retrievelist (Local_u8Counter5+1,&t2,Copy_listTerms);
					t1=t1*t2;
					replacelist (Local_u8Counter5,t1,Copy_listTerms);
					deletlist (Local_u8Counter5+1,&t2,Copy_listTerms);
					deletlist (Local_u8Counter5,&op,Copy_listOPs);
				}
				else if(op=='/')
				{
					listentry t1,t2;
					retrievelist (Local_u8Counter5,&t1,Copy_listTerms);
					retrievelist (Local_u8Counter5+1,&t2,Copy_listTerms);
					if(t2==0)
					{
						LCD_enumSendString((u8*)"Math error");
						LCD_enumSendCommand(0x0C);
						do
						{
							KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
						}while(Local_u8PressedKey==KEYPAD_NO_KEY_PRESSED);
						Local_u8Counter4=0,Local_u8Counter1=0,Local_u8Counter2=0,Local_u8Counter3=0;
						LCD_enumClear();
						destroylist (&Copy_listOPs);
						destroylist (&Copy_listTerms);
						for(u8 i=0;i<10;i++)
						{
							Local_Au8Nums[i]=0;
						}
						LCD_enumCursorEnable();
						goto l;
					}
					t1=t1/t2;
					replacelist (Local_u8Counter5,t1,Copy_listTerms);
					deletlist (Local_u8Counter5+1,&t2,Copy_listTerms);
					deletlist (Local_u8Counter5,&op,Copy_listOPs);
				}
				else
				{
					Local_u8Counter5++;
				}
				u8 Local_u8HasMulDiv = 0;
				for (u8 i = 0; i < listsize(Copy_listOPs); i++)
				{
					retrievelist(i, &op, Copy_listOPs);
					if (op == '*' || op == '/')
					{
						Local_u8HasMulDiv = 1;
						break;
					}
				}
				if (!Local_u8HasMulDiv)
				{
					break;
				}
			}

			Local_u8Counter5=0;
			while(1)
			{
				listentry op;
				retrievelist(Local_u8Counter5,&op,Copy_listOPs);
				if(op=='+')
				{
					listentry t1,t2;
					retrievelist (Local_u8Counter5,&t1,Copy_listTerms);
					retrievelist (Local_u8Counter5+1,&t2,Copy_listTerms);
					t1=t1+t2;
					replacelist (Local_u8Counter5,t1,Copy_listTerms);
					deletlist (Local_u8Counter5+1,&t2,Copy_listTerms);
					deletlist (Local_u8Counter5,&op,Copy_listOPs);
				}
				else if(op=='-')
				{
					listentry t1,t2;
					retrievelist (Local_u8Counter5,&t1,Copy_listTerms);
					retrievelist (Local_u8Counter5+1,&t2,Copy_listTerms);
					t1=t1-t2;
					replacelist (Local_u8Counter5,t1,Copy_listTerms);
					deletlist (Local_u8Counter5+1,&t2,Copy_listTerms);
					deletlist (Local_u8Counter5,&op,Copy_listOPs);
				}
				else
				{
					Local_u8Counter5++;
				}
				if(listsize(Copy_listOPs)==0)
				{
					break;
				}
			}

			listentry Local_leResult;
			retrievelist (0,&Local_leResult,Copy_listTerms);
			if(Local_leResult<=65535)
			{
				s32 Local_u16Left = (s32)Local_leResult;
				f32 Local_f32Fraction=Local_leResult-(f32)Local_u16Left;
				s32 Local_s32TempResult = Local_leResult;
				u8 Local_u8ResultLength = 0;

				if (Local_s32TempResult == 0) {
					Local_u8ResultLength = 1;  // Local_leResult is zero, which takes one digit
				} else {
					while (Local_s32TempResult != 0) {
						Local_s32TempResult /= 10;
						Local_u8ResultLength++;
					}
				}
				if(Local_f32Fraction==0)
				{
					if(Local_leResult<0)
					{
						LCD_enumGoTOPosition(2,16-Local_u8ResultLength);
					}
					else
					{
						LCD_enumGoTOPosition(2,16-Local_u8ResultLength+1);
					}
				}
				else
				{
					if(Local_leResult<0)
					{
						LCD_enumGoTOPosition(2,16-Local_u8ResultLength-5);
					}
					else
					{
						LCD_enumGoTOPosition(2,16-Local_u8ResultLength-4);
					}
				}
				LCD_enumDisplayFloatNum(Local_leResult);
				LCD_enumSendCommand(0x0C);
				do
				{
					KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
				}while(Local_u8PressedKey==KEYPAD_NO_KEY_PRESSED);
				Local_u8Counter4=0,Local_u8Counter1=0,Local_u8Counter2=0,Local_u8Counter3=0;
				LCD_enumClear();
				destroylist (&Copy_listOPs);
				destroylist (&Copy_listTerms);
				for(u8 i=0;i<10;i++)
				{
					Local_Au8Nums[i]=0;
				}
				if(Local_u8PressedKey=='+'||Local_u8PressedKey=='-'||Local_u8PressedKey=='*'||Local_u8PressedKey=='/')
				{
					insertlist(Local_u8Counter3++,Local_leResult,Copy_listTerms);
					insertlist(Local_u8Counter2++,Local_u8PressedKey,Copy_listOPs);
					LCD_enumDisplayFloatNum(Local_leResult);
					LCD_enumSendChar(Local_u8PressedKey);
				}
				LCD_enumCursorEnable();
				break;
			}
			else
			{
				LCD_enumSendString((u8*)"Out of range");
				LCD_enumSendCommand(0x0C);
				do
				{
					KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
				}while(Local_u8PressedKey==KEYPAD_NO_KEY_PRESSED);
				Local_u8Counter4=0,Local_u8Counter1=0,Local_u8Counter2=0,Local_u8Counter3=0;
				LCD_enumClear();
				destroylist (&Copy_listOPs);
				destroylist (&Copy_listTerms);
				for(u8 i=0;i<10;i++)
				{
					Local_Au8Nums[i]=0;
				}
				LCD_enumCursorEnable();
				break;
			}
			break;
		case 'c':
			Local_u8Counter4=0,Local_u8Counter1=0,Local_u8Counter2=0,Local_u8Counter3=0,Local_s32IsNeg=1;
			LCD_enumClear();
			destroylist (&Copy_listOPs);
			destroylist (&Copy_listTerms);
			for(u8 i=0;i<10;i++)
			{
				Local_Au8Nums[i]=0;
			}
			LCD_enumCursorEnable();
			break;
		}
	}
}
