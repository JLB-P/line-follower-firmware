/*
 * line_follower.c
 *
 * Created: 3/3/2026 6:35:07 PM
 * Author : josel
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"

int main(void)
{
    /* Replace with your application code */
    init_ports();
	while (1) 
    {
		led_on_off();
    }
}

