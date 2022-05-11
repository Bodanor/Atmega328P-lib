#ifndef __TIMER_H__
#define __TIMER_H__

#include <avr/io.h>
#include "util_pin.h"

unsigned long pulsePin(int pin_number, int state);
void delayMC(long mc);
#endif