#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>

// Define rows and columns of the keypad
#define KEYPAD_PORT PORTD
#define KEYPAD_DDR DDRD
#define KEYPAD_PIN PIND

#define ROWS 4
#define COLS 4

// Define keypad layout
char keys[ROWS][COLS] = {
    {'D', '#', '0', '*'},
    {'C', '9', '8', '7'},
    {'B', '6', '5', '4'},
    {'A', '3', '2', '1'}
};

char keypad_scan() {
    // Loop through each column and check for key press
    for (int col = 0; col < COLS; col++) {
        // Set the current column to LOW
        KEYPAD_PORT &= ~(0b00000001 << col);

        // Loop through each row and check if any key is pressed
        for (int row = 0; row < ROWS; row++) {
            // If a key is pressed, return its value
            if (!(KEYPAD_PIN & (0b00010000 << row))) {
                // Wait for key debounce
                _delay_ms(50);
                while (!(KEYPAD_PIN & (0b00010000 << row)));

                // Return the pressed key
                return keys[row][col];
            }
        }

        // Reset the column to HIGH for the next iteration
        KEYPAD_PORT |= (0b00000001 << col);
    }

    // No key is pressed
    return '\0';
}

void EEPROMwrite(unsigned int address, char data) {
    //wait for completion of previous write 
    while (EECR & (1<<EEPE));

    //set up address and data regs 
    EEAR = address; 
    EEDR = data;

    //write logical 1 to EEMPE 
    EECR |= (1<<EEMPE);

    //start eeprom write 
    EECR |= (1<<EEPE);
}

char EEPROMread(unsigned int address) {
    //wait for completion of writes 
    while (EECR & (1<<EEPE));

    //set up address 
    EEAR = address;

    //start eeprom read 
    EECR |= (1<<EERE);

    //return data 
    return EEDR;
}

void changeSecret(){
    char key = keypad_scan();
    lcd_clrscr();
    lcd_puts("Enter new key : ");
    lcd_gotoxy(0,1);

    while (key == '\0') {
        key = keypad_scan();
    }

    lcd_putc(key);

    EEPROMwrite(0, key);
    _delay_ms(1000);

}

char caesar(char c)
{   
    int k=EEPROMread(0);
    
    return (c + EEPROMread(0) - 48);
}

void encrypt(){
    char key = keypad_scan();
    lcd_clrscr();
    lcd_puts("String: ");
    int x = 0;

    while (key != '3') {
        key = keypad_scan();

        while(key == '\0'){
            key = keypad_scan();
        }   
        _delay_ms(400);

        lcd_putc(key);

        lcd_gotoxy(x, 1);
        lcd_putc(caesar(key));
        lcd_gotoxy(9 + x, 0);

        x++;
    }

    _delay_ms(1000);
}



int main(void)
{
    // Set columns as inputs and enable internal pull-ups
    KEYPAD_DDR = 0b00001111;
    KEYPAD_PORT = 0b11110000;

    lcd_init(LCD_DISP_ON);

    lcd_clrscr();
    lcd_puts("1 : Encrypt");
    lcd_gotoxy(0,1);
    lcd_puts("2 : Change Key");

    // changeSecret();

    while(1){

        char key = keypad_scan();

        if(key == '2'){
            changeSecret();
        }

        if(key == '1'){
            encrypt();
        }

        _delay_ms(400);

        lcd_clrscr();
        lcd_puts("1 : Encrypt");
        lcd_gotoxy(0,1);
        lcd_puts("2 : Change Key");
        
    }

    return 0;
}