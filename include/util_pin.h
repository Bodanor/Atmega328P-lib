#ifndef __UTIL_PIN_H__
#define __UTIL_PIN_H__

#include <avr/io.h>
#include <stdint.h>

#include "uart.h"
#define NULL 0

#define OUTPUT 1
#define INPUT 0

#define HIGH 1
#define LOW 0

#define SetBit(x, y) (x|=(1 << y))
#define ClearBit(x, y) (x&=~(1 << y))

void setState(int pin_number, int state);
void writePin(int pin_number, int state);
int readPin(int pin_number);
uint8_t getPinMask(uint16_t pin);
uint8_t getPinNumPerPort(uint16_t pin);
volatile uint8_t *getPortDataDirectionRegister(uint16_t pin);
volatile uint8_t *getPinPort(uint16_t pin);
volatile uint8_t *getOutputPortRegister(uint16_t pin);
volatile uint8_t *getInputPortRegister(uint16_t pin);
#endif