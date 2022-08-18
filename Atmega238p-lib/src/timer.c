#include "timer.h"

unsigned long pulsePin(int pin_number, int state)
{
    unsigned long i = 0;

    if (state == HIGH)
    {
        while(readPin(pin_number) != HIGH);

        TCCR0A = 1 << WGM01;
        TCNT0 = 0;
        OCR0A = 160; // MODIFIER
        TCCR0B = 1 << CS00;

        while (readPin(pin_number) != LOW)
        {
            TIFR0 = 1 << OCF0A;
        
            while (!(TIFR0 & (1 << OCF0A)));
            i++;
        }

        TCCR0B = 0;
    }
    else
    {
        while(readPin(pin_number) != LOW);

        TCCR0A = 1 << WGM01;
        TCNT0 = 0;
        OCR0A = 160; 
        TCCR0B = 1 << CS00;

        while (readPin(pin_number) != HIGH)
        {
            TIFR0 = 1 << OCF0A;
        
            while (!(TIFR0 & (1 << OCF0A)));
            i++;
        }

        TCCR0B = 0;
    }

    return i * 10;
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