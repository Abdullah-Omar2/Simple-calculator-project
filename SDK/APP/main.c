/*
 * main.c
 *
 *  Created on: Aug 26, 2024
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
#include "../APP/Calculator_int.h"

u8 Calculator_Au8Nums[15];
u8 Calculator_u8Counter1=0,Calculator_u8Counter2=0,Calculator_u8Counter3=0,Calculator_u8Counter4=0,Local_u8PressedKey;
s32 Calculator_s32IsNeg=1;
plist Calculator_listTerms,Calculator_listOPs;

int main (void)
{
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
	createlist(&Calculator_listTerms);
	createlist(&Calculator_listOPs);

	l:
	while(1)
	{
		Local_u8PressedKey=KEYPAD_NO_KEY_PRESSED;
		do
		{
			KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
		}while(Local_u8PressedKey==KEYPAD_NO_KEY_PRESSED);
		if(Calculator_u8Counter4==15&&Local_u8PressedKey!='=')
		{
			continue;
		}
		LCD_enumSendChar(Local_u8PressedKey);
		Calculator_u8Counter4++;
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
			Calculator_Au8Nums[Calculator_u8Counter1++]=Local_u8PressedKey;
			break;
		case '-':
			if (Calculator_u8Counter1 == 0 || Calculator_Au8Nums[Calculator_u8Counter1 - 1] == ' ')			//9---8
			{										    //9 -
				Calculator_Au8Nums[Calculator_u8Counter1++]=Local_u8PressedKey;			//--
			}
			else if(Calculator_Au8Nums[Calculator_u8Counter1 - 1] == '-')
			{
				insertlist(Calculator_u8Counter2++,Local_u8PressedKey,Calculator_listOPs);
			}
			else
			{
				Calculator_Au8Nums[Calculator_u8Counter1++]=' ';
				insertlist(Calculator_u8Counter2++,Local_u8PressedKey,Calculator_listOPs);
			}
			break;
		case '+':
		case '*':
		case '/':
			Calculator_Au8Nums[Calculator_u8Counter1++]=' ';
			insertlist(Calculator_u8Counter2++,Local_u8PressedKey,Calculator_listOPs);
			break;
		case '=':
			Calculator_Au8Nums[Calculator_u8Counter1] = '\0';
			Calculator_u8Counter1=0,Calculator_u8Counter2=0;
			while(Calculator_Au8Nums[Calculator_u8Counter1]!='\0')
			{
				s32 Local_s32Term=0;
				if(Calculator_Au8Nums[Calculator_u8Counter1]=='-')
				{
					Calculator_s32IsNeg*=-1;
					Calculator_u8Counter1++;
				}
				while(Calculator_Au8Nums[Calculator_u8Counter1]>='0'&&Calculator_Au8Nums[Calculator_u8Counter1]<='9')
				{
					Local_s32Term=Local_s32Term*10+(Calculator_Au8Nums[Calculator_u8Counter1++]-'0');
				}
				if(Calculator_Au8Nums[Calculator_u8Counter1-1]!=' ')
				{
					insertlist(Calculator_u8Counter3++,Local_s32Term*Calculator_s32IsNeg,Calculator_listTerms);
				}
				Calculator_s32IsNeg=1;
				if(Calculator_Au8Nums[Calculator_u8Counter1]==' ')
				{
					Calculator_u8Counter1++;
				}
			}
			LCD_enumGoTOPosition(2,1);

			if(listsize(Calculator_listTerms)!=listsize(Calculator_listOPs)+1)
			{
				LCD_enumSendString((u8*)"Wrong expression");
				LCD_enumSendCommand(0x0C);
				do
				{
					KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
				}while(Local_u8PressedKey==KEYPAD_NO_KEY_PRESSED);
				Calculator_u8Counter4=0,Calculator_u8Counter1=0,Calculator_u8Counter2=0,Calculator_u8Counter3=0;
				LCD_enumClear();
				destroylist (&Calculator_listOPs);
				destroylist (&Calculator_listTerms);
				for(u8 i=0;i<10;i++)
				{
					Calculator_Au8Nums[i]=0;
				}
				LCD_enumCursorEnable();
				break;
			}

			u8 a=0;
			while(1)//[+-*/-+]
			{
				listentry op;
				retrievelist (a,&op,Calculator_listOPs);
				if(op=='*')
				{
					listentry t1,t2;
					retrievelist (a,&t1,Calculator_listTerms);
					retrievelist (a+1,&t2,Calculator_listTerms);
					t1=t1*t2;
					replacelist (a,t1,Calculator_listTerms);
					deletlist (a+1,&t2,Calculator_listTerms);
					deletlist (a,&op,Calculator_listOPs);
				}
				else if(op=='/')
				{
					listentry t1,t2;
					retrievelist (a,&t1,Calculator_listTerms);
					retrievelist (a+1,&t2,Calculator_listTerms);
					if(t2==0)
					{
						LCD_enumSendString((u8*)"Math error");
						LCD_enumSendCommand(0x0C);
						do
						{
							KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
						}while(Local_u8PressedKey==KEYPAD_NO_KEY_PRESSED);
						Calculator_u8Counter4=0,Calculator_u8Counter1=0,Calculator_u8Counter2=0,Calculator_u8Counter3=0;
						LCD_enumClear();
						destroylist (&Calculator_listOPs);
						destroylist (&Calculator_listTerms);
						for(u8 i=0;i<10;i++)
						{
							Calculator_Au8Nums[i]=0;
						}
						LCD_enumCursorEnable();
						goto l;
					}
					t1=t1/t2;
					replacelist (a,t1,Calculator_listTerms);
					deletlist (a+1,&t2,Calculator_listTerms);
					deletlist (a,&op,Calculator_listOPs);
				}
				else
				{
					a++;
				}
				u8 hasMulDiv = 0;
				for (u8 i = 0; i < listsize(Calculator_listOPs); i++)
				{
					retrievelist(i, &op, Calculator_listOPs);
					if (op == '*' || op == '/')
					{
						hasMulDiv = 1;
						break;
					}
				}
				if (!hasMulDiv)
				{
					break;
				}
			}

			a=0;
			while(1)
			{
				listentry op;
				retrievelist(a,&op,Calculator_listOPs);
				if(op=='+')
				{
					listentry t1,t2;
					retrievelist (a,&t1,Calculator_listTerms);
					retrievelist (a+1,&t2,Calculator_listTerms);
					t1=t1+t2;
					replacelist (a,t1,Calculator_listTerms);
					deletlist (a+1,&t2,Calculator_listTerms);
					deletlist (a,&op,Calculator_listOPs);
				}
				else if(op=='-')
				{
					listentry t1,t2;
					retrievelist (a,&t1,Calculator_listTerms);
					retrievelist (a+1,&t2,Calculator_listTerms);
					t1=t1-t2;
					replacelist (a,t1,Calculator_listTerms);
					deletlist (a+1,&t2,Calculator_listTerms);
					deletlist (a,&op,Calculator_listOPs);
				}
				else
				{
					a++;
				}
				if(listsize(Calculator_listOPs)==0)
				{
					break;
				}
			}

			listentry result;
			retrievelist (0,&result,Calculator_listTerms);
			if(result<=65535)
			{
				s32 Local_u16Left = (s32)result;
				f32 Local_f32Fraction=result-(f32)Local_u16Left;
				s32 tempResult = result;
				u8 resultLength = 0;

				if (tempResult == 0) {
					resultLength = 1;  // Result is zero, which takes one digit
				} else {
					while (tempResult != 0) {
						tempResult /= 10;
						resultLength++;
					}
				}
				if(Local_f32Fraction==0)
				{
					if(result<0)
					{
						LCD_enumGoTOPosition(2,16-resultLength);
					}
					else
					{
						LCD_enumGoTOPosition(2,16-resultLength+1);
					}
				}
				else
				{
					if(result<0)
					{
						LCD_enumGoTOPosition(2,16-resultLength-5);
					}
					else
					{
						LCD_enumGoTOPosition(2,16-resultLength-4);
					}
				}
				LCD_enumDisplayFloatNum(result);
				LCD_enumSendCommand(0x0C);
				do
				{
					KEYPAD_enumGetPressedKey(&Local_u8PressedKey);
				}while(Local_u8PressedKey==KEYPAD_NO_KEY_PRESSED);
				Calculator_u8Counter4=0,Calculator_u8Counter1=0,Calculator_u8Counter2=0,Calculator_u8Counter3=0;
				LCD_enumClear();
				destroylist (&Calculator_listOPs);
				destroylist (&Calculator_listTerms);
				for(u8 i=0;i<10;i++)
				{
					Calculator_Au8Nums[i]=0;
				}
				if(Local_u8PressedKey=='+'||Local_u8PressedKey=='-'||Local_u8PressedKey=='*'||Local_u8PressedKey=='/')
				{
					insertlist(Calculator_u8Counter3++,result,Calculator_listTerms);
					insertlist(Calculator_u8Counter2++,Local_u8PressedKey,Calculator_listOPs);
					LCD_enumDisplayFloatNum(result);
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
				Calculator_u8Counter4=0,Calculator_u8Counter1=0,Calculator_u8Counter2=0,Calculator_u8Counter3=0;
				LCD_enumClear();
				destroylist (&Calculator_listOPs);
				destroylist (&Calculator_listTerms);
				for(u8 i=0;i<10;i++)
				{
					Calculator_Au8Nums[i]=0;
				}
				LCD_enumCursorEnable();
				break;
			}
			break;
		case 'c':
			Calculator_u8Counter4=0,Calculator_u8Counter1=0,Calculator_u8Counter2=0,Calculator_u8Counter3=0,Calculator_s32IsNeg=1;
			LCD_enumClear();
			destroylist (&Calculator_listOPs);
			destroylist (&Calculator_listTerms);
			for(u8 i=0;i<10;i++)
			{
				Calculator_Au8Nums[i]=0;
			}
			LCD_enumCursorEnable();
			break;
		}
	}
	return 0;
}

