#ifndef __UTILS_H__
#define __UTILS_H__

#include <avr/io.h>

#define OUTPUT 1
#define INPUT 0

#define HIGH 1
#define LOW 0

#define SetBit(x, y) (x|=(1 << y))
#define ClearBit(x, y) (x&=~(1 << y))

void setState(int pin_number, int state);
void writePin(int pin_number, int state);
int readPin(int pin_number);

#endif