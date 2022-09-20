#include <avr/io.h>
#include "timer0.h"

Timer0::Timer0()
{
    // 
}

void Timer0::init(int period_msec)
{
    // this code sets up timer1 for a 1s @ 16Mhz Clock (mode 4)
    // counting 16000000/1024 cycles of a clock prescaled by 1024
    TCCR0A = 0; // set timer1 to normal operation (all bits in control registers A and B set to zero)
    TCCR0B = 0; //
    TCNT0 = 0; // initialize counter value to 0
    OCR0A = static_cast<uint8_t>((16000000 / 1024 - 1)*period_msec/1000000.0); // assign target count to compare register A (must be less than 65536)
    TCCR0A |= (1 << WGM01); // clear the timer on compare match A
    TIMSK0 |= (1 << OCIE0A); // set interrupt on compare match A
    TCCR0B |= (1 << CS02) | (1 << CS00); // set prescaler to 1024 and start the timer
}

void Timer0::init(int period_msec, float duty_cycle)
{
    // this code sets up timer1 for a 1s period with the specified duty cycle
    TCCR0A = 0; // set timer1 to normal operation (all bits in control registers A and B set to zero)
    TCCR0B = 0;
    TCNT0 = 0; // initialize counter value to 0
    OCR0A = static_cast<uint8_t>((16000000 / 1024 - 1)*period_msec/1000000.0); // assign target count to compare register A (must be less than 65536)
    OCR0B = static_cast<uint8_t>(OCR0A * duty_cycle); // assign target count to compare register B (should not exceed value of OCR1A)
    TCCR0A |= (1 << WGM01); // clear the timer on compare match A
    TIMSK0 |= (1 << OCIE0A); // set interrupt on compare match A
    TIMSK0 |= (1 << OCIE0B); // set interrupt on compare match B
    TCCR0B |= (1 << CS02) | (1 << CS00); // set prescaler to 1024 and start the timer
}

void Timer0::set(float duty_cycle)
{
    OCR1B = static_cast<uint8_t>(OCR0A * duty_cycle); // assign target count to compare register B (should not exceed value of OCR1A)
}