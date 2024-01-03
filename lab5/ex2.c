#include <avr/io.h>

void setupADC() {
    ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << ADLAR); // AVCC with external capacitor at AREF pin, ADC1, Left adjust result
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, Enable ADC interrupt, 128 prescaler
    DIDR0 = (1 << ADC1D); // Disable digital input buffer on ADC1 pin
}

void startADC() {
    // Start an ADC conversion
    ADCSRA |= (1 << ADSC);
}

void setupPWM() {
    // Set Fast PWM mode, non-inverting output
    TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);

    // Set prescaler to 64 and start PWM
    TCCR0B = (1 << CS01) | (1 << CS00);
}

int main(void) {
    // Set all pins on PORTD as output
    DDRD = 0xFF;

    setupADC();
    setupPWM();

    while (1) {
        if(ADCSRA & (1 << ADIF)) // If conversion is complete
        {
            ADCSRA |= (0 << ADIF); // Clear ADIF
            OCR0A = ADCH; // Output result to PORTD
            startADC();
        }
    }
}