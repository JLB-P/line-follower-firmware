/*
 * line_follower.c
 *
 * Created: 3/3/2026 6:35:07 PM
 * Author : jlb
 */ 
 #include "leds.h"
 #include "motors.h"
 #include "adc.h"
 #include "irsensors.h"
 #include <util/delay.h>
//global variables
float current_sensor_position = 0.0;
/*Tuning process
  1. Set Ki and kd to zero
  2. Start with Kp at 50% speed
    example: speed = 990 rpm, maximum error = 3.5, Kp = (990x0.5)/3.5 = 141.4 */
float kp = 150;	//Proportional Gain
/* 3. Start with kd at 0.5 of Kp, example: Kd = 0.5 x 150 = 75 */
float kd =  100;	//Differential Gain
/* 4. Start with Ki at 0.02 of Kp, example: Ki = 0.002 x 150 = 0.3 */
float ki =  0.2;	//Integral Gain
int32_t eInteg = 0;	//Integral accumulator
int32_t ePrev  = 0;		//Previous Error
float control_signal; //Control signal

//PID controller 
float pid_controller(float cur_position,float set_point)
{
	float pid;
	float error;

	error = set_point - cur_position; //calculate error
	pid = (kp * error)  + (ki * eInteg) + (kd * (error - ePrev));

	eInteg += error;                  // integral is simply a summation over time
	ePrev = error;                    // save previous for derivative

	return pid;
}

int main(void)
{
    leds_init();
    test_leds();
    motors_init();
    adc_init();
  
    float previous_sensor_position = 0.0; //initialize sensor position
	while (1) 
    {
        current_sensor_position = read_sensors(); //read current sensor position
        if (current_sensor_position == 0xFF) //no line detected
            current_sensor_position = previous_sensor_position; //use previous sensor position to decide direction
        control_signal = pid_controller(current_sensor_position, 3.5); //3.5 is the required sensor position to be on the line, as 3.5 is the middle point of 6 sensors
        if (control_signal > 510) //maximum control signal is 510 (255 each motor)
            control_signal = 510;
        if (control_signal < -510) //minimum control signal is -510 (255 each motor)
            control_signal = -510;
        if (control_signal >= 0.0) //turn right
        {
            if (control_signal > 255) //if control signal is greater than 255, set it to 255 for one motor and the rest to the other motor   
                motor_left(MOTOR_BACKWARD, (control_signal-255));
            else motor_left(MOTOR_FORWARD, (255-control_signal));
            motor_right(MOTOR_BACKWARD, 255);
        }
        if (control_signal <= 0.0) //turn left
        {
            if (control_signal < -255) //if control signal is less than -255, set it to -255 for one motor and the rest to the other motor   
                motor_right(MOTOR_FORWARD, -(control_signal+255));
            else motor_right(MOTOR_BACKWARD, (255+control_signal));
            motor_left(MOTOR_FORWARD, 255);
        }
        previous_sensor_position = current_sensor_position; //update previous sensor position
    }
}

