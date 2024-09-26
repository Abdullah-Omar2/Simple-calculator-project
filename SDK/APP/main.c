/*
 * main.c
 *
 *  Created on: Aug 26, 2024
 *      Author: abdullahalazhary
 */
#include <util/delay.h>
#include <stdlib.h>
#include "../LIB/STDtypes.h"
#include "../LIB/Error_State.h"
#include "../LIB/BITMATH.h"
#include "../MCAL/DIO/DIO_config.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_config.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KEYPAD/KEYPAD_config.h"
#include "../HAL/KEYPAD/KEYPAD_int.h"
#include "../APP/Calculator_int.h"

int main() {
    char input[16];
    char operator;
    int num1 = 0, num2 = 0, result = 0;
    int index = 0;

    LCD_enumInit();
    KEYPAD_enumInit();
    LCD_enumClear();
    LCD_enumSendString("Simple Calc");

    while (1)
    {
        char key;
        KEYPAD_enumGetPressedKey(&key);

        // If a number is pressed
        if (key >= '0' && key <= '9') {
            if (index < 16 - 1) {
                input[index++] = key;
                input[index] = '\0'; // Null-terminate the string
                LCD_enumClear();
                LCD_enumSendString(input);
            }
        }

        // If an operator is pressed
        else if (key == '+' || key == '-' || key == '*' || key == '/') {
            num1 = atoi(input);
            operator = key;
            index = 0; // Reset input for second number
            input[0] = '\0'; // Clear input string
        }

        // If '=' is pressed
        else if (key == '=') {
            num2 = atoi(input);
            switch (operator) {
                case '+': result = num1 + num2; break;
                case '-': result = num1 - num2; break;
                case '*': result = num1 * num2; break;
                case '/': result = (num2 != 0) ? num1 / num2 : 0; break;
            }
            LCD_enumClear();
            sprintf(input, "Result: %d", result);
            LCD_enumSendString(input);
            _delay_ms(2000); // Display result for a while
            LCD_enumClear();
            LCD_enumSendString("Simple Calc");
            index = 0; // Reset input for new calculation
            input[0] = '\0'; // Clear input string
        }
    }
    return 0;
}

