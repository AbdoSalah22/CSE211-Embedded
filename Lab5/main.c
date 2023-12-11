#include "LCD.h"
#include "DIO.h"
#include "KEYPAD.h"
#include <string.h>
#include <stdlib.h>

int main() {
    lcd_init();
    keypad_init();

    char operand1[10] = "";  // Assuming operands are integers and fit in 10 characters
    char operand2[10] = "";
    char operator;

    // Display instructions on the LCD
    lcd_command(0x01);  // Clear display
    lcd_data('N');
    lcd_data('u');
    lcd_data('m');
    lcd_data(':');
    lcd_data(' ');


    while (1) {
        // Get the first operand
        lcd_command(0xC0);  // Move cursor to the second line
        lcd_data('E');
        lcd_data(':');
        lcd_data(' ');

        int i = 0;
        while (1) {
            uint8 key = keypad_readkey();
            if (key != 0) {
                lcd_data(key);
                operand1[i++] = key;

                if (key == '=') {
                    operand1[i - 1] = '\0';
                    break;
                }
            }
        }

        // Get the operator
        while (1) {
            lcd_data(' ');

            uint8 key = keypad_readkey();
            if (key != 0 && strchr("+-*/", key) != NULL) {
                lcd_data(key);
                operator = key;
                break;
            }
        }

        // Get the second operand
        lcd_data(' ');

        i = 0;
        while (1) {
            uint8 key = keypad_readkey();
            if (key != 0) {
                lcd_data(key);
                operand2[i++] = key;

                if (key == '=') {
                    operand2[i - 1] = '\0';
                    break;
                }
            }
        }

        // Convert operands to integers
        int num1 = atoi(operand1);
        int num2 = atoi(operand2);

        // Perform the calculation and display the result
        int result;
        switch (operator) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 != 0) {
                    result = num1 / num2;
                } else {
                    // Handle divide-by-zero case
                    lcd_command(0xC0);  // Move cursor to the second line
                    lcd_data('E');
                    lcd_data('r');
                    lcd_data('r');
                    lcd_data('o');
                    lcd_data('r');
                    lcd_data('!');
                    continue;  // Restart the loop
                }
                break;
            default:
                // Invalid operator
                continue;  // Restart the loop
        }

        // Display the result
        lcd_command(0xC0);  // Move cursor to the second line
        lcd_data('=');
        lcd_data(' ');
        lcd_data(' ');
        lcd_data(' ');
        lcd_data(' ');

        if (result < 0) {
            lcd_data('-');
            result = -result;
        }

        // Display each digit of the result
        int divisor = 10000;
        int leadingZeros = 1;

        while (divisor > 0) {
            int digit = result / divisor;
            if (digit > 0 || !leadingZeros || divisor == 1) {
                lcd_data(digit + '0');
                leadingZeros = 0;
            }
            result %= divisor;
            divisor /= 10;
        }
    }

}
