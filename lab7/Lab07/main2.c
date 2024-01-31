#include <stdlib.h>
#include <avr/io.h>
#include "lcd.h"
#include "keypad_driver.h"


int main() {
    keypad_vInit();
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();
    lcd_puts("Press a key");

    while (1) {
        char key = keypad_u8check_press();
        if (key != 0xfffd) {
            lcd_clrscr();
            lcd_putc(key);
        }
    }

    return 0;
}
