#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 100

int main(void)
{
    DDRB |= 0x3F; 
    DDRD &= ~(1 << 7); 
    int pressed = 0;
    int count = 0;

    while (1)
    {
        if ((PIND & (1 << 7)) && !pressed) {
            count++; 
        }

        pressed = (PIND & (1 << 7)) ? 1 : 0;

        PORTB = count;

        _delay_ms(BLINK_DELAY_MS);
    }

    return 0;
}
