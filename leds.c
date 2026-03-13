/*
 * leds.c
 *
 * Created: 3/3/2026 7:08:08 PM
 *  Author: josel
 */ 
#include <avr/io.h>
#include <util/delay.h>

void led_on_off (void){
	PORTB ^= 1 << PINB5;
	_delay_ms(50);
}