#include "uart.h"

void USART_SendStr(const char *str)
{
    while (*str != '\0')
        USART_Transmit(*str++);
}

void USART_Init(unsigned int ubrr)
{
    UBRR0 = ubrr;

    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    UCSR0C = (3<< UCSZ00);
}

void USART_Transmit(unsigned char data)
{
    while (! (UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

unsigned char USART_Receive(void)
{
    while (! (UCSR0A & (1 << RXC0)));
    return UDR0;
}
