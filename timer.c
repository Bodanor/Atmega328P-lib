#include "timer.h"

unsigned long pulsePin(int pin_number, int state)
{
    long i = 0;

    if (state == HIGH)
    {
        while(readPin(pin_number) != HIGH);

        TCCR0A = 0;
        TCCR0B = 1 << CS00;

        while (readPin(pin_number) != LOW)
        {
            TCNT0 = 8;
            TIFR0 = 1 << TOV0;
        
            while (!TIFR0 & (1 << TOV0));
            i++;
        }

        TCCR0B = 0;
    }
    else
    {
        while(readPin(pin_number) != LOW);

        TCCR0A = 0;
        TCCR0B = 1 << CS00;

        while (readPin(pin_number) != HIGH)
        {
            TCNT0 = 8;
            TIFR0 = 1 << TOV0;
        
            while (!TIFR0 & (1 << TOV0));
            i++;
        }

        TCCR0B = 0;
    }

    return i;
}

void delayMs(long microseconds)
{

    unsigned int i = 0;
    unsigned int wait = microseconds / 0.1;

    TCCR0A = 1 << WGM01;
    TCNT0 = 0;
    OCR0A = 2;
    TCCR0B = 1 << CS00;

    while (i < wait)
    {
        TIFR0 = 1 << OCF0A;

        while (!(TIFR0 & (1 << OCF0A)));

        i++;
    }
}