#include "../include/util_pin.h"

void setState(int pin_number, int state)
{
    if (pin_number >= 0 && pin_number <= 7)
    {
        if (state == INPUT)
            ClearBit(DDRD, pin_number);
        else
            SetBit(DDRD, pin_number);
    }
    else if (pin_number >= 8 && pin_number <= 13)
    {
        pin_number -= 8;
        if (state == INPUT)
            ClearBit(DDRB, pin_number);
        else
            SetBit(DDRB, pin_number);
    }
    else if (pin_number >= 14 && pin_number <= 19)
    {
        pin_number -= 14;
        if (state == INPUT)
            ClearBit(DDRC, pin_number);
        else
            SetBit(DDRC, pin_number);
    }
}

void writePin(int pin_number, int state)
{
    if (pin_number >= 0 && pin_number <= 7)
    {
        if (state == LOW)
            ClearBit(PORTD, pin_number);
        else
            SetBit(PORTD, pin_number);
    }
    else if (pin_number >= 8 && pin_number <= 13)
    {
        pin_number -= 8;
        if (state == LOW)
            ClearBit(PORTB, pin_number);
        else
            SetBit(PORTB, pin_number);
    }
    else if (pin_number >= 14 && pin_number <= 19)
    {
        pin_number -= 14;
        if (state == LOW)
            ClearBit(PORTC, pin_number);
        else
            SetBit(PORTC, pin_number);
    }

}

int readPin(int pin_number)
{
    int state;

    if (pin_number >= 0 && pin_number <= 7)
    {
       state = PIND & (1 << pin_number);
    }
    else if (pin_number >= 8 && pin_number <= 13)
    {
        pin_number -= 8;
        state = PINB & (1 << pin_number);
    }
    else if (pin_number >= 14 && pin_number <= 19)
    {
        pin_number -= 14;
        state = PINC & (1 << pin_number);
    }
    if (state > 0)
        return 1;
    else
        return 0;

}
