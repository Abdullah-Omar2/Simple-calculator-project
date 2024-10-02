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

plist Calculator_listTerms,Calculator_listOPs;

int main (void)
{
	Calculator_voidStart ();
	createlist(&Calculator_listTerms);
	createlist(&Calculator_listOPs);
	Calculator_voidRun (Calculator_listTerms,Calculator_listOPs);
	return 0;
}

