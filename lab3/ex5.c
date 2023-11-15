#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int count=0;

int main(void){
    TCNT0 = 131;

    DDRB |= (1 << 5) | (1<<3);

    TCCR0A = 0x00;
    TCCR0B = 0x04;

    sei();

    TIMSK0 |= (1 << TOIE0);

    while (1)
    {
        PORTB ^= (1 << 3);
        _delay_ms(100);
    }    
}

ISR (TIMER0_OVF_vect){
    if(count >= 50){
        PORTB ^= (1 << 5);
        count = 0;
    }
    else{
        count++;
    }
}