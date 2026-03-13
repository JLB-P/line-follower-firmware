/*
 * ports.c
 *
 * Created: 3/3/2026 6:50:04 PM
 *  Author: josel
 */ 
#include <avr/io.h>

void init_ports (void){
	//init port B
	DDRB |= 1 << PINB5;
}