#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void){
    TCNT1 = 3036;

    DDRB |= (1 << 5) | 0x0f;

    TCCR1A = 0x00;
    TCCR1B = 0x04;

    sei();

    TIMSK1 |= (1 << TOIE1);

    while (1)
    {
        PORTB = PORTB | (1 << 3);
        _delay_ms(BLINK_DELAY_MS);
        PORTB = PORTB & ~(1 << 3);
        PORTB = PORTB | (1 << 2);
        _delay_ms(BLINK_DELAY_MS);
        PORTB = PORTB & ~(1 << 2);
        PORTB = PORTB | (1 << 1);
        _delay_ms(BLINK_DELAY_MS);
        PORTB = PORTB & ~(1 << 1);
        PORTB = PORTB | (1 << 0);
        _delay_ms(BLINK_DELAY_MS);
        PORTB = PORTB & ~(1 << 0);
        PORTB = PORTB | (1 << 1);
        _delay_ms(BLINK_DELAY_MS);
        PORTB = PORTB & ~(1 << 1);
        PORTB = PORTB | (1 << 2);
        _delay_ms(BLINK_DELAY_MS);
        PORTB = PORTB & ~(1 << 2);
    }    
}

ISR (TIMER1_OVF_vect){
    PORTB ^= (1 << 5);
    TCNT1 = 3036;
}