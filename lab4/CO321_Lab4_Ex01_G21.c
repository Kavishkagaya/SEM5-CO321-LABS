#include <avr/io.h>

int main(void)
{
    DDRD |= (1 << PD6);

    TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
    TCCR0B = (1 << CS01) | (1 << CS00);

    OCR0A = 10;

    while (1)
    {
    }
}
