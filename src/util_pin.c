#include "../include/util_pin.h"

volatile uint8_t*getOutputPortRegister(uint16_t pin)
{
    if (pin <= 7)
        return &PORTD;
    else if (pin >= 8 && pin <= 13)
        return &PORTB;
    else if (pin >= 14 && pin <= 19)
        return &PORTC;
    else
        return NULL;
        
}
volatile uint8_t *getInputPortRegister(uint16_t pin)
{
    if (pin <= 7)
        return &PIND;
    else if (pin >= 8 && pin <= 13)
        return &PINB;
    else if (pin >= 14 && pin <= 19)
        return &PINC;
    else
        return NULL;
}

volatile uint8_t *getPortDataDirectionRegister(uint16_t pin)
{
    if (pin <= 7)
        return &DDRD;
    else if (pin >= 8 && pin <= 13)
        return &DDRB;
    else if (pin >= 14 && pin <= 19)
        return &DDRC;
    else
        return NULL;
}

uint8_t getPinMask(uint16_t pin)
{
    if (pin <= 7)
        return (1 << pin);
    else if (pin >= 8 && pin <= 13)
        return (1 << (pin - 8));
    else if (pin >= 14 && pin <= 19)
        return (1 << (pin - 14));
    else
        return NULL;

}
uint8_t getPinNumPerPort(uint16_t pin)
{
    if (pin <= 7)
        return pin;
    else if (pin >= 8 && pin <= 13)
        return pin-8;
    else if (pin >= 14 && pin <= 19)
        return pin-14;
    else
        return NULL;

}
void setState(int pin_number, int state)
{
    volatile uint8_t *portRegister = getPortDataDirectionRegister(pin_number);
    pin_number = getPinNumPerPort(pin_number);

    if (state == INPUT)
        ClearBit(*portRegister, pin_number);
    else
        SetBit(*portRegister, pin_number);
}

void writePin(int pin_number, int state)
{
    volatile uint8_t *portRegister = getOutputPortRegister(pin_number);
    pin_number = getPinNumPerPort(pin_number);

    if (state == LOW)
        ClearBit(*portRegister, pin_number);
    else
        SetBit(*portRegister, pin_number);

}

int readPin(int pin_number)
{
    volatile uint8_t *portRegister = getInputPortRegister(pin_number);
    pin_number = getPinNumPerPort(pin_number);

    return *portRegister & (1 << pin_number);

}
