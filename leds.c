#include <avr/io.h>
#include <util/delay.h>

void leds_init(){
/*LED to sensor assignment
	MPU		LEDs	SENSORS
	-----------------------
	PB4		LED1	sensor1
	PB5		LED2	sensor2
	PD4		LED3	sensor3
	PD5		LED4	sensor4
	PD6		LED5	sensor5
	PD7		LED6	sensor6
    NA      LED7    sensor7
    NA      LED8    sensor8
*/
	//Make i/o pins as outputs
	DDRB |= (1<<PB4)|(1<<PB5);
	DDRD |= (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7);
	//Make them low to turn off led.
	//LEDs are anode activated
	PORTB &= ~((1<<PB4)|(1<<PB5));
    PORTD &= ~((1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7));
}
void test_leds(){
	for(int i=0; i<3; i++){
        
		PORTB |= (1<<PB4);//On
		_delay_ms(50);
		PORTB &=~(1<<PB4); //Off
		_delay_ms(50);

		PORTB |= (1<<PB5);//On
		_delay_ms(50);
		PORTB &=~(1<<PB5); //Off
		_delay_ms(50);

		PORTD |= (1<<PD4);//On
		_delay_ms(50);
		PORTD &=~(1<<PD4); //Off
		_delay_ms(50);

		PORTD |= (1<<PD5);//On
		_delay_ms(50);
		PORTD &=~(1<<PD5); //Off
		_delay_ms(50);

		PORTD |= (1<<PD6);//On
		_delay_ms(50);
		PORTD &=~(1<<PD6); //Off
		_delay_ms(50);

		PORTD |= (1<<PD7);//On
		_delay_ms(50);
		PORTD &=~(1<<PD7); //Off
		_delay_ms(50);
	}
}

void ledon(uint8_t id){
	if (id <= 2){
		PORTB |= (1 << (id+3));
	}
	else if (id >= 3){
		PORTD |= (1 << (id + 1));
	}
}

void ledoff(uint8_t id){
	if (id <= 2){
			PORTB &= ~(1 << (id+3));
		}
		else if (id >= 3){
			PORTD &= ~(1 << (id + 1));
		}
}