#ifndef irsensors_H_
#define irsensors_H_

//Map Sensor Number to ADC Channel
#define SENSOR1 0	//Sensor connected to adc channel 0
#define SENSOR2 1	//Sensor connected to adc channel 1
#define SENSOR3 2	//Sensor connected to adc channel 2
#define SENSOR4 3	//Sensor connected to adc channel 3
#define SENSOR5 4	//Sensor connected to adc channel 4
#define SENSOR6 5	//Sensor connected to adc channel 5

float read_sensors();

#endif /* irsensors_H_ */