/*
 * LCD_config.h
 *
 *  Created on: Sep 6, 2024
 *      Author: abdullahalazhary
 */

#ifndef INCLUDE_HAL_LED_LCD_CONFIG_H_
#define INCLUDE_HAL_LED_LCD_CONFIG_H_

#define LCD_MODE EIGHT_BIT

#define LCD_RS_PORT     DIO_PORTB
#define LCD_RS_PIN      DIO_PIN6
#define LCD_RW_PORT     DIO_PORTB
#define LCD_RW_PIN      DIO_PIN5
#define LCD_EN_PORT     DIO_PORTB
#define LCD_EN_PIN      DIO_PIN4

#define LCD_D7_PORT     DIO_PORTA
#define LCD_D7_PIN      DIO_PIN0
#define LCD_D6_PORT     DIO_PORTA
#define LCD_D6_PIN      DIO_PIN1
#define LCD_D5_PORT     DIO_PORTA
#define LCD_D5_PIN      DIO_PIN2
#define LCD_D4_PORT     DIO_PORTA
#define LCD_D4_PIN      DIO_PIN3

#if LCD_MODE == EIGHT_BIT

#define LCD_D3_PORT     DIO_PORTA
#define LCD_D3_PIN      DIO_PIN4
#define LCD_D2_PORT     DIO_PORTA
#define LCD_D2_PIN      DIO_PIN5
#define LCD_D1_PORT     DIO_PORTA
#define LCD_D1_PIN      DIO_PIN6
#define LCD_D0_PORT     DIO_PORTA
#define LCD_D0_PIN      DIO_PIN7

#endif

#endif /* INCLUDE_HAL_LED_LCD_CONFIG_H_ */
