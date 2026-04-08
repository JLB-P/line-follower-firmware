#include <avr/io.h>
#include <avr/interrupt.h>
#include "motors.h"

void motors_init()
{
	/*	set up pwm for speed control
	*	PWM Phase Correct 8 bits Mode(WGM10 = 1)
	*	Clear OC1A/OC1B on Compare Match when up-counting.
	*	Set OC1A/OC1B on Compare Match when down-counting.
	*	(COM1A1/COM1B1 = 1)
	*/
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM10); 
	
	/*Practical: pick 20–30 kHz unless your motor driver specifies otherwise.
	* Always check the driver’s max switching frequency and current-sense bandwidth.
	* freq_PWM = fclk/2xNxTOP = 16000000/(2X1X255) = 31.37255 Khz
	* No prescaler (CS10=1)
	*/
	TCCR1B=(1<<CS10);

	//Set the corresponding port pin to output
	DDRB|=(1<<PB1); //OC1A pwm speed control for right motor
	DDRB|=(1<<PB2); //OC1B pwm speed control for left motor
	//set PD0 & PD1 as output for motor direction
	DDRD|=0X0F;	
	/*Set the direction control PINs to OUT
	| MPU	|H BRIDGE| DESCRIPTION         |          
	|-------+--------+-------------+-------|
	| PB1	|	ENA  |--> SPEED    | MOTOR |
	| PD0	|	IN1	 |--> CW_DIR   | RIGHT |
	| PD1	|	IN2	 |--> CC_DIR   |       |
	|-------+--------+-------------+-------|
	| PB2	|	ENB  |--> SPEED    | MOTOR |
	| PD2	|	IN3	 |--> CW_DIR   | LEFT  |
	| PD3	|	IN4	 |--> CC_DIR   |       |
	|-------+--------+-------------+-------|*/
	//OCR1A = 200;
 	//OCR1B = 200;
}

void motor_right(uint8_t dir,uint8_t speed) 
{
	//Direction
	if(dir == MOTOR_STOP)
	{
		PORTD &=(~(1<<PD0));
		PORTD &=(~(1<<PD1));
	}

	else if(dir == MOTOR_BACKWARD)
	{
		PORTD &=(~(1<<PD0));
		PORTD |=(1<<PD1);
	}
	else if(dir == MOTOR_FORWARD)
	{
		PORTD &=(~(1<<PD1));
		PORTD |=(1<<PD0);
	}

	//Speed
	uint8_t sreg=SREG;//Status Register

	cli();

	OCR1A=(uint8_t)(((float)speed/255.0)*ROBO_SPEED);

	SREG=sreg;
}

void motor_left(uint8_t dir,uint8_t speed)
{
	//Direction
	if(dir == MOTOR_STOP)
	{
		PORTD &=(~(1<<PD2));
		PORTD &=(~(1<<PD3));
	}

	else if(dir == MOTOR_FORWARD)
	{
		PORTD &=(~(1<<PD3));
		PORTD |=(1<<PD2);
	}
	else if(dir == MOTOR_BACKWARD)
	{
		PORTD &=(~(1<<PD2));
		PORTD |=(1<<PD3);
	}

	//Speed
	uint8_t sreg=SREG;

	cli();

	OCR1B=(uint8_t)(((float)speed/255.0)*ROBO_SPEED);

	SREG=sreg;
}