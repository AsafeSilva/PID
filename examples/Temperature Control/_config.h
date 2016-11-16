#pragma once

// == Configure Pins == //
#define pinTemp 	A0
#define pinLamp 	5
#define pinCooler 	3

// == Serial == //
#define SERIAL_SPEED 9600
#define LOG 	Serial.print
#define LOGln	Serial.println

// == Read LM35 == //
#define temp(pin) analogRead(pin)*0.4887

// === Calculo LM35 == //
// 10mV --- 1°C
//  V   ---  T°

// T = V*100  (1)

// 5V --- 1023
//  V --- ADC 

// V = ADC*5/1023  (2)

// (2) em (1)

// T = ADC*5*100/1023
// <<< T = ADC*0.4887 >>>