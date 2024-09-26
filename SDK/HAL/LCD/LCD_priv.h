/*
 * LCD_priv.h
 *
 *  Created on: Sep 6, 2024
 *      Author: abdullahalazhary
 */

#ifndef INCLUDE_HAL_LCD_LCD_PRIV_H_
#define INCLUDE_HAL_LCD_LCD_PRIV_H_

#define EIGHT_BIT 0
#define FOUR_BIT 1

static inline ES_T LCD_inlenumSendCommand(u8 Copy_u8Command);

static inline ES_T LCD_inlenumLatch(void);

static inline ES_T LCD_inlenumSendChar(u8 Copy_u8Char);

static inline ES_T LCD_inlenumSendString(u8* Copy_pu8String);

static inline ES_T LCD_inlenumDisplayIntNum(s32 Copy_s64Num);

#endif /* INCLUDE_HAL_LCD_LCD_PRIV_H_ */
