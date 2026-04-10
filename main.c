/*
 * line_follower.c
 *
 * Created: 3/3/2026 6:35:07 PM
 * Author : josel
 */ 
 #include "leds.h"
 #include "motors.h"
 #include "adc.h"
 #include <avr/delay.h>

int main(void)
{
    leds_init();
    //run_prog_indicator();
    motors_init();
    adc_init();
    /*
    for (uint8_t i = 0; i<255; i++)
    {
    motor_right(MOTOR_BACKWARD,i);
    motor_left(MOTOR_FORWARD,i);
    _delay_ms(50);
    }
    */
    uint16_t test_adc=0;
	while (1) 
    {
        //test channel 0
        test_adc = read_adc(0);
		if (test_adc >= 512)
        // Derivation Pot value (>= 2.5v) =((2.5v)x(1023))/5v=511.5
            run_prog_indicator();
        //test channel 1
        test_adc = read_adc(1);
		if (test_adc >= 299)
        //CNY70 distance value(7mm)=((1.46v)x(1023))/5v=298.71 
            run_prog_indicator();
    }
}

