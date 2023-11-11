#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 200

unsigned int number = 0;

int main(void)
{
    DDRB |= 0x3f;
    DDRD &= ~(1 << 2);

    EICRA |= (1 << ISC01);
    EICRA |= (1 << ISC00);

    EICRA |= (1 << ISC10);
    EICRA |= (1 << ISC11);

    sei();

    EIMSK |= (1 << INT0);
    EIMSK |= (1 << INT1);

    while (1)
    {
    }

    return 0;
}

ISR(INT0_vect)
{
    _delay_ms(500);
    number = (number << 1) | 0;
    PORTB = number;
}

ISR(INT1_vect)
{
    _delay_ms(500);
    number = (number << 1) | 1;
    PORTB = number;
}