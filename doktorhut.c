#define F_CPU 1000000UL

#include <util/delay.h>
#include <avr/io.h>
#include "patterns.h"

/*
 * Map bits to LEDs
 *
 * attiny2313
 * PD0 PD1 PA1 PA0 PD2 PD3 PD4 PD5 PB0 PB1 PB2 PB3 PB4 PB5 PB6 PB7
 * atmega168
 * PC6 PD0 PD1 PD2 PD3 PD4 PD5 PD6 PB1 PB2 PC0 PC1 PC2 PC3 PC4 PC5
 *   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 *
**/
void switch_leds(uint16_t led_state)
{
    PORTD  = ((led_state & 0b1000000000000000)>>15)<<PD0;
    PORTD |= ((led_state & 0b0100000000000000)>>14)<<PD1;
    PORTD |= ((led_state & 0b0010000000000000)>>13)<<PD2;
    PORTD |= ((led_state & 0b0001000000000000)>>12)<<PD3;
    PORTD |= ((led_state & 0b0000100000000000)>>11)<<PD4;
    PORTD |= ((led_state & 0b0000010000000000)>>10)<<PD5;
    PORTD |= ((led_state & 0b0000001000000000)>> 9)<<PD6;
    PORTD |= ((led_state & 0b0000000100000000)>> 8)<<PD7;
    PORTB  = ((led_state & 0b0000000010000000)>> 7)<<PB1;
    PORTB |= ((led_state & 0b0000000001000000)>> 6)<<PB2;
    PORTC  = ((led_state & 0b0000000000100000)>> 5)<<PC0;
    PORTC |= ((led_state & 0b0000000000010000)>> 4)<<PC1;
    PORTC |= ((led_state & 0b0000000000001000)>> 3)<<PC2;
    PORTC |= ((led_state & 0b0000000000000100)>> 2)<<PC3;
    PORTC |= ((led_state & 0b0000000000000010)>> 1)<<PC4;
    PORTC |= ((led_state & 0b0000000000000001)>> 0)<<PC5;
}


void delay_ms(uint16_t n) {
  while (n--) {
    _delay_ms(1);
  }
}


int main (void)
{
    DDRB = (1 << DDB1) | (1 << DDB2);
    DDRC = (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3) | (1 << DDC4) | (1 << DDC5) | (1 << DDC6);
    DDRD = (1 << DDD0) | (1 << DDD1) | (1 << DDD2) | (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);

    uint8_t pattern_idx = 0;
    uint16_t elem_idx = 0;
    uint16_t delay = pattern_delays[0];
    uint8_t repetition_count = 0;
    while(1) {
        switch_leds(patterns[elem_idx]);
        delay_ms(delay);
        // next element of pattern
        elem_idx++;
        // last element reached?
        if (elem_idx >= pattern_endlines[pattern_idx]) {
            // count repetitions
            repetition_count++;
            // last repetition reached?
            if (repetition_count >= pattern_repetitions[pattern_idx]) {
                // reset repetition count
                repetition_count = 0;
                // next pattern
                pattern_idx++;
                // last pattern reached?
                if (pattern_idx >= num_patterns) {
                    // go to first pattern
                    pattern_idx = 0;
                }
                // get element delay for the next pattern
                delay = pattern_delays[pattern_idx];
            }
            // go to first element of pattern
            elem_idx = start_lines[pattern_idx];
        }
    }
    return 0;
}

