#pragma once

#include <Arduino.h>
#include "PID.h"

class PIDProcessing : public PID{
private:
	const int P = 1;  // Proporcional
	const int I = 2;  // Integral
	const int D = 3;  // Derivada
	const int S = 4;  // SetPoint

	// PID* pid;

	String KStr, valStr;
	bool checkValue;

	void setParameters(float value, int param);

public:

	// PIDProcessing(PID* _pid);
	PIDProcessing(float _kP = 0.0, float _kI = 0.0, float _kD = 0.0);
	PIDProcessing(float _kP, float _kI, float _kD, float _outMin, float _outMax);


	// margem de valores (min e max) devem estar
	// de acordo com os valores setados no Processing
	void sendToGraphics(int input, int output);


	// recebe valores atualizados do Processing
	// 1 -> kP; 2 -> kI; 3 -> kD; 4 -> SetPoint
	// Ex:
	//    "*1_2.1" -> kP = 2.1
	//    "*4_700" -> SetPoint = 700;  
	void receiveProcessing(char inChar);
};