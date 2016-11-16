#include "PID.h"

PID::PID(float _kP, float _kI, float _kD){
    setParameters(_kP, _kI, _kD);
    setSetPoint(0);

    outMax = 255;
    outMin = 0;

}

PID::PID(float _kP, float _kI, float _kD, float _outMin, float _outMax){
    setParameters(_kP, _kI, _kD);

    outMax = _outMax;
    outMin = _outMin;
}

void PID::setSetPoint(float _setPoint){
	setPoint = _setPoint;
}

void PID::setKp(float _kP){  kP = _kP; }
void PID::setKi(float _kI){  kI = _kI; }
void PID::setKd(float _kD){  kD = _kD; }  

void PID::setParameters(float _kP, float _kI, float _kD){
	kP = _kP; 
	kI = _kI;
	kD = _kD;
}

void PID::setLimits(int _outMin, int _outMax){
	outMin = _outMin;
	outMax = _outMax;
}

void PID::addInput(float _newInput){
	newInput = _newInput;
}

float PID::compute(){

	unsigned long time = (millis() - lastTime); 
	lastTime = millis();
	float dTime = time/1000.0f;

	// calculate error
	error = (setPoint - newInput);

	// Implementation of P
	P = kP * error;

	// Implementation of I
	// I += kI * (lastError + error) * dTime / 2;
	I += kI * error * dTime;
	I = constrain(I, outMin, outMax);

	// Implementation of D
	D = kD * (error - lastError) / dTime;

	// Calculate output PID
	output = P + I + D;
	output = constrain(output, outMin, outMax);

	lastError = error;

	return output;
}


float PID::getKp(){return kP;}
float PID::getKi(){return kI;}
float PID::getKd(){return kD;}
float PID::getSetPoint(){return setPoint;}
