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

unsigned char ceaser_encrypt(unsigned char data) {
    if(data >= 'A' && data <= 'Z') {
        data = (data - 'A' + 3) % 26 + 'A';
    } else if(data >= 'a' && data <= 'z') {
        data = (data - 'a' + 3) % 26 + 'a';
    }

    return data;
}

int main(void) {
    usart_init();

    while (1)
    {
        while(1){
            unsigned char data = usart_receive();
            if(data == '\n') {
                usart_send('\n');
                break;
            }
            usart_send(ceaser_encrypt(data));
        }
    }
    

    return 0;
}