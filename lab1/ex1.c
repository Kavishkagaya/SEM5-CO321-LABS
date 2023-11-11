#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void)
{
    DDRB = DDRB | (1 << 5);
    DDRB = DDRB | (1 << 4);
    DDRB = DDRB | (1 << 3);
    DDRB = DDRB | (1 << 2);
    while (1)
    {
        PORTB = PORTB | (1 << 5);
        PORTB = PORTB | (1 << 4);
        PORTB = PORTB | (1 << 3);
        PORTB = PORTB | (1 << 2);
        _delay_ms(BLINK_DELAY_MS);
        PORTB = PORTB & ~(1 << 5);
        PORTB = PORTB & ~(1 << 4);
        PORTB = PORTB & ~(1 << 3);
        PORTB = PORTB & ~(1 << 2);
        _delay_ms(BLINK_DELAY_MS);
    }
}