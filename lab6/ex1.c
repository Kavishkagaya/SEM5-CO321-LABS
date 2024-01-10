#include <avr/io.h>
#include <string.h>

void usart_init() {
    UBRR0 = 0x67;

    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

void usart_send(unsigned char data) {
    while (!(UCSR0A & (1<<UDRE0)));

    UDR0 = data;
}

unsigned char usart_receive(void) {
    while (!(UCSR0A & (1<<RXC0)));

    return UDR0;
}

int main(void) {
    usart_init();

    char str[] = "E/19/306 Rajakaruna M.M.P.N.\nE/19/309 Rambukwella H.M.W.K.G.\nE/19/310 Ranage R.D.P.R";

    for(int i = 0; i < strlen(str); i++) {
        usart_send(str[i]);
    }

    return 0;
}