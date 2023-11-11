#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 100

int main(void)
{
    DDRB |= 1;
    DDRD &= ~(1 << 2);

    EICRA |= (1<<ISC01);

    sei();

    EIMSK |= (1 << INT0);

    while (1)
    {
    }

    return 0;
}

ISR(INT0_vect){
    PORTB ^= 1;
}