#include <avr/io.h>

void delay_timer0(){
    TCNT0 = 0x00;

    TCCR0A = 0x00;
    TCCR0B = 0x01;

    while ((TIFR0 & 0x01) == 0);

    TCCR0A = 0x00;
    TCCR0B = 0x00;

    TIFR0 = 0x01;
}

int main(void){
    DDRB  = DDRB | (1<<5);

    while (1)
    {
        PORTB = PORTB | (1<<5);
        delay_timer0();

        PORTB = PORTB & ~(1<<5);
        delay_timer0();
    }
    
}