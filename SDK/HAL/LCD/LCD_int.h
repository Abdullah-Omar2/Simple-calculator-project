/*
 * LCD_int.h
 *
 *  Created on: Sep 6, 2024
 *      Author: abdullahalazhary
 */

#ifndef INCLUDE_HAL_LCD_LCD_INT_H_
#define INCLUDE_HAL_LCD_LCD_INT_H_

#include "LCD_priv.h"

ES_T LCD_enumInit(void);

ES_T LCD_enumSendChar(u8 Copy_u8Char);

ES_T LCD_enumSendCommand(u8 Copy_u8Command);

ES_T LCD_enumSendString(u8* Copy_pu8String);

ES_T LCD_enumGoTOPosition(u8 Copy_u8Row,u8 Copy_u8Col);

ES_T LCD_enumDisplayIntNum(s64 Copy_s64Num);

ES_T LCD_enumDisplayFloatNum(f32 Copy_u8Num);

ES_T LCD_enumSendCustomChar(u8 Copy_u8Pos,u8* Copy_pu8Char);

ES_T LCD_enumClear(void);

#endif /* INCLUDE_HAL_LCD_LCD_INT_H_ */
