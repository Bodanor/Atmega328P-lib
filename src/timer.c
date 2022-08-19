#include "../include/timer.h"

unsigned long pulsePin(int pin_number, int state)
{
    volatile uint8_t *port = getPinPort(pin_number);
    uint8_t pinmask = getPinMask(pin_number);
    uint8_t stateMask;
    unsigned long loops = 0;
    unsigned long clocks = 0;
    unsigned long max_loops = 16 * 1000000 / 16;

    if (state == HIGH)
        stateMask = pinmask;
    else
        stateMask = 0;
    
    while ((*getInputPortRegister(pin_number) & pinmask) == stateMask)
        if(loops++ == max_loops)
            return 0;
    
    while ((*getInputPortRegister(pin_number) & pinmask) != stateMask)
        if(loops++ == max_loops)
            return 0;
    
    while ((*getInputPortRegister(pin_number) & pinmask) == stateMask)
        if(loops++ == max_loops)
            return 0;
        clocks++;
    
    return(clocks * 21 + 16)/16;
    
}

void delayMicro(long microseconds)
{

    unsigned long i = 0;
    unsigned long wait = microseconds / 5;

    TCCR0A = 1 << WGM01;
    TCNT0 = 0;
    OCR0A = 10;
    TCCR0B = 1 << CS01;

    while (i < wait)
    {
        TIFR0 = 1 << OCF0A;

        while (!(TIFR0 & (1 << OCF0A)));

        i++;
    }
}