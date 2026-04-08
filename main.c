/*
 * line_follower.c
 *
 * Created: 3/3/2026 6:35:07 PM
 * Author : josel
 */ 
 #include "leds.h"
 #include "motors.h"
 #include "avr/delay.h"

int main(void)
{
    leds_init();
    running_prog_indicator();
    motors_init();
    for (uint8_t i = 0; i<255; i++)
    {
    motor_right(MOTOR_BACKWARD,i);
    motor_left(MOTOR_FORWARD,i);
    _delay_ms(50);
    }
	while (1) 
    {
		
    }
}

