#ifndef __UART_H__
#define __UART_H__

#include <avr/io.h>

/*
 * 1200
 * 2400
 * 4800
 * 9600
 * 19200
 * 38400
 * 57600
 * 115200
*/
#define B1200 1200
#define B2400 2400
#define B4800 4800
#define B9600 9600
#define B19200 19200
#define B38400 38400
#define B57600 57600
#define B115200 115200
#define BAUDRATE(x) F_CPU/16/x-1

void USART_Init(unsigned int baudSpeed);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_SendStr(const char *str);

#endif