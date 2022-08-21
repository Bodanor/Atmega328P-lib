#include "../include/timer.h"

//TODO: Write macros for GetPinMask and company to optimize code generation...
/*
    I have enabled to optimization with flag -0S so that *Hopefully* the compiler always optmize this function. I hope compilers doesn't change lmuch of the code...
    It is important to have consistent assembly code as this function is based on instructions clocks cycles and expect the loop to take 18 clocks cycles !
*/
unsigned long __attribute__((optimize("s"))) pulsePin(int pin_number, int state)
{
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
    
    while ((*getInputPortRegister(pin_number) & pinmask) == stateMask){
        if(loops++ == max_loops)
            return 0;
        clocks++;
    }
    
    /*
        Looking at the assembly code produced, we can observe that the loop that increments clocks ad is the main part takes 18 clocks cycles.
        Also, we have take as an account the initalization of the variable. From the start of the function to the main loop part, there is approximately 16 clocks
        Cycles. Keep in mind that there is still some errors introduced by the function getPinMask as is left shift a value based on a pin.
        If for example pin is 1, is takes 3 clocks cycles to return from that function. Whereas is pin is 6, it takes 3*6 time clocks cycles to return !
    */
    return(16 + (clocks*18))/16;
    
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