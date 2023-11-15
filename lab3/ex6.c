#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int count=0;

int main(void){
    TCNT0 = 131;
    TCNT1 = 34286;

    DDRB |= (1 << 5) | (1<<3);

    TCCR0A = 0x00;
    TCCR0B = 0x04;

    TCCR1A = 0x00;
    TCCR1B = 0x04;

    sei();

    TIMSK0 |= (1 << TOIE0);
    TIMSK1 |= (1 << TOIE1);

    while (1)
    {
    }    
}

ISR (TIMER0_OVF_vect){
    if(count >= 25){
        PORTB ^= (1 << 5);
        count = 0;
    }
    else{
        count++;
    }
    TCNT0 = 131;
}

ISR (TIMER1_OVF_vect){
    PORTB ^= (1 << 3);
    TCNT1 = 34286;
}