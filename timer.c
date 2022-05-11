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

void delayMC(long mc)
{
    unsigned int i = 0;
    TCCR0A = 0;
    TCCR0B = 1 << CS01;

    while (i < 4000)
    {
        TCNT0 = 6;
        TIFR0 = 1 << TOV0;

        while (!(TIFR0 & (1 << TOV0)));

        i++;
    }
}