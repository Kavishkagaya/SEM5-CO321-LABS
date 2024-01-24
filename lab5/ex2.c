#include <avr/io.h>
#include <string.h>
#include <stdio.h>

void startADC()
{
    ADCSRA |= (1 << ADSC); // Start conversion
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

int main(void)
{
    DDRD = 0xFF; // Set all pins on PORTD as output

    ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << ADLAR);                 // AVCC with external capacitor at AREF pin, ADC1, Left adjust result
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, Enable ADC interrupt, 128 prescaler
    // DIDR0 = (1 << ADC1D); // Disable digital input buffer on ADC1 pin

    startADC();
    usart_init();

    while (1)
    {
        if (ADCSRA & (1 << ADIF)) // If conversion is complete
        {
            ADCSRA |= (0 << ADIF); // Clear ADIF

            char str[10];
            sprintf(str, "%d\n", ADCH);

            for (int i = 0; i < strlen(str); i++)
            {
                usart_send(str[i]);
            }

            if (ADCH > 200)
            {
                PORTD = 0xFF;
            }
            else
            {
                PORTD = 0x00;
            }

            startADC();
        }
    }
}
