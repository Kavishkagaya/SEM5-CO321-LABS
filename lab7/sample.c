#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void EEPROMwrite(unsigned int address, unsigned char data)
{
    // wait for completion of previous write
    while (EECR & (1 << EEPE))
        ;
    // set up address and data regs
    EEAR = address;
    EEDR = data;
    // write logical one to EEMWE
    EECR |= (1 << EEMPE);
    // start EEPROM write by setting EEPE
    EECR |= (1 << EEPE);
}

char EEPROMRead(unsigned int address)
{
    // wait for completion of previous write
    while (EECR & (1 << EEPE))
        ;
    // set up address
    EEAR = address;
    // start EEPROM read by writing EERE
    EECR |= (1 << EERE);
    // return data from data register
    return EEDR;
}

void usart_init()
{
    UBRR0 = 0x67;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void usart_send(unsigned char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    UDR0 = data;
}

unsigned char usart_receive(void)
{
    while (!(UCSR0A & (1 << RXC0)))
        ;

    return UDR0;
}

int main(void)
{
    // Your main code here
    unsigned char message[] = "Hello World!";
    int length = strlen(message);
    for (int i = 0; i < length; i++)
    {
        EEPROMwrite(0x00 + i, message[i]);
    }

    char result[100];
    for (int i = 0; i < length; i++)
    {
        result[i] = EEPROMRead(0x00 + i);
    }
    result[length] = '\0'; // Don't forget to null-terminate the string

    usart_init();

    for (int i = 0; i < length; i++)
    {
        usart_send(result[i]);
    }

    while (1)
    {
        // Your main loop code here
    }
    return 0;
}