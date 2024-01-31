/*************************************************************************
Title:    Testing output to a HD44780 based LCD display.
Author:   Peter Fleury  <pfleury@gmx.ch>  http://tinyurl.com/peterfleury
File:     $Id: test_lcd.c,v 1.8 2015/01/31 18:04:08 peter Exp $
Software: AVR-GCC 4.x
Hardware: HD44780 compatible LCD text display
          AVR with external SRAM interface if memory-mapped LCD interface is used
          any AVR with 7 free I/O pins if 4-bit IO port mode is used
**************************************************************************/
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"

// Define keypad layout
char keys[4][4] = {
    {'D', '#', '0', '*'},
    {'C', '9', '8', '7'},
    {'B', '6', '5', '4'},
    {'A', '3', '2', '1'}};

char get_key_input()
{
    // Loop through each column and check for key press
    for (int col = 0; col < 4; col++)
    {
        // Set the current column to LOW
        PORTD &= ~(0b00000001 << col);

        // Loop through each row and check if any key is pressed
        for (int row = 0; row < 4; row++)
        {
            // If a key is pressed, return its value
            if (!(PIND & (0b00010000 << row)))
            {
                // Wait for key debounce
                _delay_ms(50);
                while (!(PIND & (0b00010000 << row)))
                    ;

                // Return the pressed key
                return keys[row][col];
            }
        }

        // Reset the column to HIGH for the next iteration
        PORTD |= (0b00000001 << col);
    }

    // No key is pressed
    return '\0';
}

void EEPROMwrite(unsigned int address, char data)
{
    // wait for completion of previous write
    while (EECR & (1 << EEPE))
        ;

    // set up address and data regs
    EEAR = address;
    EEDR = data;

    // write logical 1 to EEMPE
    EECR |= (1 << EEMPE);

    // start eeprom write
    EECR |= (1 << EEPE);
}

char EEPROMread(unsigned int address)
{
    // wait for completion of writes
    while (EECR & (1 << EEPE))
        ;

    // set up address
    EEAR = address;

    // start eeprom read
    EECR |= (1 << EERE);

    // return data
    return EEDR;
}

void SetKey()
{
    char key = get_key_input();
    lcd_gotoxy(0, 1);

    while (key == '\0')
    {
        key = get_key_input();
    }

    lcd_putc(key);
    EEPROMwrite(0, key);
    _delay_ms(1000);
}

char caesar(char c)
{
    int k = EEPROMread(0);

    return (c + k - 48);
}

void encrypt()
{
    char key = get_key_input();
    lcd_clrscr();
    lcd_puts("String: ");
    lcd_gotoxy(0, 1);
    lcd_puts("Encrypted: ");
    lcd_gotoxy(9, 0);
    int x = 0;

    while (1)
    {
        key = get_key_input();

        while (key == '\0')
        {
            key = get_key_input();
        }
        _delay_ms(400);

        lcd_putc(key);

        lcd_gotoxy(13 + x, 1);
        lcd_putc(caesar(key));
        lcd_gotoxy(10 + x, 0);

        x++;

        if (x == 3)
        {
            break;
        }
    }

    _delay_ms(1000);
}

int main(void)
{
    // Initialize LCD and keypad here

    DDRD = 0b00001111;
    PORTD = 0b11110000;
    lcd_init(LCD_DISP_ON);

    lcd_clrscr();

    lcd_command(LCD_DISP_ON_CURSOR);

    while (1)
    {
        char key = EEPROMread(0);

        if (key == '\0')
        {
            lcd_puts("Key is not set");
            _delay_ms(1000);
            lcd_clrscr();
            SetKey();
            _delay_ms(1000);

            lcd_clrscr();

            lcd_puts("Key is set to :");
            char key = EEPROMread(0);

            lcd_gotoxy(0, 1);
            lcd_putc(key);

            _delay_ms(1000);
        }

        lcd_clrscr();

        lcd_puts("Enter Command :");
        lcd_gotoxy(0, 1);
        lcd_puts("1.Enc 2.Reset");

        _delay_ms(1000);

        char cmd = get_key_input();

        if (cmd == '1')
        {
            encrypt();
            _delay_ms(1000);
        }
        else if (cmd == '2')
        {
            lcd_clrscr();
            lcd_puts("Key is reset");
            _delay_ms(1000);
            lcd_clrscr();
            SetKey();
            _delay_ms(1000);
        }
        _delay_ms(1000);
    }

    return 0;
}