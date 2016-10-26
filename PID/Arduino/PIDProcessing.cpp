#include "PIDProcessing.h"

// == PUBLICS == //

PIDProcessing::PIDProcessing(float _kP, float _kI, float _kD) : PID(_kP, _kI, _kD){
  KStr = valStr = "";
}

PIDProcessing::PIDProcessing(float _kP, float _kI, float _kD, float _outMin, float _outMax) : PID(_kP, _kI, _kD, _outMin, _outMax){
  KStr = valStr = "";
}

void PIDProcessing::sendToGraphics(int input, int output){
	char val[15] = {
		'\0','\0','\0','\0','\0',
    '\0','\0','\0','\0','\0',
    '\0','\0','\0','\0','\0'};           

	sprintf(val, "*%i_%i\n", input, output);
	Serial.print(val);
}

void PIDProcessing::receiveProcessing(char inChar){
    if(inChar == '\n'){
      setParameters(valStr.toFloat(), KStr.toInt());

      KStr = "";
      valStr = "";
    }else{
      if(inChar == '*') checkValue = true;
      else if(inChar == '_')  checkValue = false; 
      else{
        if(checkValue)  KStr += inChar;
        else            valStr += inChar;
      }
    }	
}


// == PRIVATES == //

void PIDProcessing::setParameters(const float value, const int param){

  if(param == P)      setKp(value);
  else if(param == I) setKi(value);
  else if(param == D) setKd(value);
  else if(param == S) setSetPoint(value);

}