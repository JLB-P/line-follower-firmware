#include <avr/io.h>
#include <avr/delay.h>

void leds_init(){
    //Set the corresponding port pin to output
	DDRB|=(1<<PB5); //LED on PB5
}
void run_prog_indicator(){
    for(int i=0; i < 10; i++ ){
        PORTB &= ~(1<<PB5);
        _delay_ms(100);
        PORTB |= (1<<PB5);
        _delay_ms(100);
    }

}
