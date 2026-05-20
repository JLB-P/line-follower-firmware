#include "adc.h"
#include "irsensors.h"
#include "leds.h"

//Value = ((1.5v*1023)/5v)=306.9
const uint16_t SENSOR_THRES = 307; //Sensor threshold

float read_sensors()
{
    /* In the hardware, LEDs are connected to indicate
    the status of each IR sensor (on= black line, off=white surface):
    eright --> LED1 --> sensor1
    right  --> LED2 --> sensor2
    rmiddle--> LED3 --> sensor3
    lmiddle--> LED4 --> sensor4
    left   --> LED5 --> sensor5
    eleft  --> LED6 --> sensor6
    */
	uint16_t	eright, right, rmiddle , lmiddle, left, eleft; //6 IR sensors arrangement
	uint8_t		sensor1, sensor2, sensor3, sensor4, sensor5, sensor6;
	
	float avgSensor = 0.0;
	
	eright=read_adc(SENSOR1);
	if(eright>SENSOR_THRES) {//far right sensor in black line 
		sensor1 = 1;
		ledon(1);
	}
	else{
		sensor1 = 0;
		ledoff(1);
	}
	right=read_adc(SENSOR2);
	if(right>SENSOR_THRES){//right sensor in black line 
		sensor2 = 1;
		ledon(2);
	}
	else{
		sensor2 = 0;
		ledoff(2);
	}
	rmiddle=read_adc(SENSOR3);
	if(rmiddle>SENSOR_THRES){//middle right sensor in black line
		sensor3 = 1;
		ledon(3);
	}
	else{
		sensor3 = 0;
		ledoff(3);
	}
	lmiddle=read_adc(SENSOR4);
	if(lmiddle>SENSOR_THRES){//middle left sensor in black line
		sensor4 = 1;
		ledon(4);
	}
	else{
		sensor4 = 0;
		ledoff(4);
	}
	left=read_adc(SENSOR5);
	if(left>=SENSOR_THRES){//left sensor in black line 
		sensor5 = 1;
		ledon(5);
	}
	else{
		sensor5 = 0;
		ledoff(5);
	}

	eleft=read_adc(SENSOR6);
	if(eleft>=SENSOR_THRES){//far left sensor in black line 
		sensor6 = 1;
		ledon(6);
	}
	else{
		sensor6 = 0;
		ledoff(6);
	}
	// If all sensors are off, return 0xFF to indicate no line detected
	if(sensor1==0 && sensor2==0 && sensor3==0 && sensor4==0 && sensor5==0 && sensor6==0)
	{
		return 0xFF;
	}
	
	// Calculate weighted average of sensor positions
	avgSensor = (float) sensor1*1 + sensor2*2 + sensor3*3 + sensor4*4 + sensor5*5 + sensor6*6;
	avgSensor = (float) avgSensor / (sensor1 + sensor2 + sensor3 + sensor4 + sensor5 + sensor6);

	return avgSensor;
}