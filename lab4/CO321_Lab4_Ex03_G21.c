#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD |= (1 << PD6);

    TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
    TCCR0B = (1 << CS01) | (1 << CS00);

    OCR0A = 127;

    while (1)
    {    
        for (int i = 2; i < 6; i++)
        {
            TCCR0B = i;
            _delay_ms(1000);
        }
        
    }
}
