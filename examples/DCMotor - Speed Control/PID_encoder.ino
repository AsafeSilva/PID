#include "PIDProcessing.h"
#include "RPM.h"

RPM rpm(100, 4);
PIDProcessing pid(0.0, 0.0, 0.0);

void InterruptEncoder(){
  rpm.rotation++;
}

void setup(){
  Serial.begin(9600);
  while(!Serial);

  DDRD = 0b1010;

  // pid.setSetPoint(500);
  attachInterrupt(0, InterruptEncoder, RISING);

}


void loop() {

    rpm.process();  // realiza cálculo de RPM/RPS

    int input    = (int) rpm.getRPM();
    pid.addInput( (float)input );
           
    int output   = (int) pid.compute(); 
    analogWrite(3, output); 

    pid.sendToGraphics(input, output);
}


void serialEvent(){
    while(Serial.available()){
      char inChar = (char)Serial.read();

      pid.receiveProcessing(inChar);
    }
}