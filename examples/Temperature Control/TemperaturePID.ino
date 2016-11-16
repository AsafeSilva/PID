#include "PIDProcessing.h"
#include "_config.h"


PIDProcessing pid(0.0, 0.0, 0.0);


void setup(){

	Serial.begin(SERIAL_SPEED);
	while(!Serial);

	pinMode(pinLamp, OUTPUT);
	pinMode(pinCooler, OUTPUT);

}


void loop(){

	int temperature = temp(pinTemp);
	int outPID = (int) pid.compute();

	pid.addInput(temperature);

	analogWrite(pinLamp, outPID);
	analogWrite(pinCooler, 255-outPID);

	pid.sendToGraphics(temperature, outPID);
}

void serialEvent(){
    while(Serial.available()){
      char inChar = (char)Serial.read();

      pid.receiveProcessing(inChar);
    }
}