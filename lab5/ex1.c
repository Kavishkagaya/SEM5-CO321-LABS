#include <avr/io.h>

void startADC()
{
    ADCSRA |= (1 << ADSC); // Start conversion
}

int main(void)
{
    DDRD = 0xFF; // Set all pins on PORTD as output

    ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << ADLAR); // AVCC with external capacitor at AREF pin, ADC1, Left adjust result
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, Enable ADC interrupt, 128 prescaler
    DIDR0 = (1 << ADC1D); // Disable digital input buffer on ADC1 pin

    startADC();

    while (1)
    {
        if(ADCSRA & (1 << ADIF)) // If conversion is complete
        {
            ADCSRA |= (0 << ADIF); // Clear ADIF
            PORTD = ADCH; // Output result to PORTD
            startADC();
        }
    }

}

