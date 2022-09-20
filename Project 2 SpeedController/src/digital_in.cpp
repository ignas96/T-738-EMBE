#include "digital_in.h"
#include <avr/io.h>

Digital_in::Digital_in(int pin)
{
     pinMask = (1 << pin);
}

void Digital_in::init()
{
    DDRB &= ~ pinMask;
    PORTB |=  pinMask;  // Enable pull-up resistor
}

bool Digital_in::is_hi()
{
    return PINB &  pinMask;
}

bool Digital_in::is_lo()
{
    return !is_hi();
}