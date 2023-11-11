#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 100

int main(void)
{
    DDRB = DDRB | (1 << 5);
    while (1)
    {
        PORTB = PORTB | (1 << 5);
        _delay_ms(BLINK_DELAY_MS);
        PORTB = PORTB & ~(1 << 5);
        _delay_ms(BLINK_DELAY_MS);
    }
}