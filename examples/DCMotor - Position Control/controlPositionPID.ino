#include "PIDProcessing.h"

#define LOG 		Serial.print
#define LOGln 		Serial.println
#define BTN_INIT 	8 	// BOTÃO PARA ZERAR
#define FIM_CURSO 	2 	// FIM DE CURSO
#define ENCODER 	3 	// ENCODER
#define M1 			5 	// MOTOR
#define M2 			6	// MOTOR

#define btnInit() !digitalRead(BTN_INIT)
#define readFimDeCurso() !digitalRead(FIM_CURSO)

void readEncoder();
void intFimDeCurso();

PIDProcessing pid;

volatile unsigned int position;

boolean flagSentido;
#define RIGHT false
#define LEFT  true

unsigned long lastTime;
int auxPidOutput;
int pidInput, pidOutput;

void setup() {
	// Config Serial
	Serial.begin(9600);
	while(!Serial);

	// Config pins
	pinMode(BTN_INIT, INPUT_PULLUP);
	pinMode(FIM_CURSO, INPUT_PULLUP);
	pinMode(ENCODER, INPUT);
	pinMode(M1, OUTPUT);
	pinMode(M2, OUTPUT);

	// Change frequency of pwm
	// TCCR0B = TCCR0B & 0b11111000 | 0x01;

	// Config External Interrupt
	attachInterrupt(digitalPinToInterrupt(FIM_CURSO), fimDeCurso, FALLING);
	attachInterrupt(digitalPinToInterrupt(ENCODER), readEncoder, RISING);

	// Config PID
	pid.setLimits(-250, 250);

	Off();
}

void loop() {
	// VOLTA AO PONTO ZERO
	if(btnInit()){
		while(btnInit() && !readFimDeCurso()){	moveLeft(240);	}
		Off();
	}

	pidInput = position;
	pid.addInput(pidInput);
		
	auxPidOutput = (int) pid.compute();
	pidOutput = abs(auxPidOutput);

	if(auxPidOutput >= 0) moveRight(pidOutput);
	else 			      moveLeft(pidOutput);

	pid.sendToGraphics(pidInput, pidOutput); 
}

void serialEvent(){
    while(Serial.available()){
    	char inChar = (char)Serial.read();

    	pid.receiveProcessing(inChar);
    }
}

// INTERRUPÇÃO EXTERNA DO ENCODER
void readEncoder(){
	position = (flagSentido == RIGHT ? position+1 : position-1);
	if(position > 5000) position = 0;
}

// INTERRUPÇÃO EXTERNA DO FIM DE CURSO
void fimDeCurso(){
	position = 0;
}

void moveRight(int pwm){
	analogWrite(M1, pwm);
	analogWrite(M2, 0);
	flagSentido = RIGHT;
}

void moveLeft(int pwm){
	analogWrite(M2, pwm);
	analogWrite(M1, 0);
	flagSentido = LEFT;
}

void Off(){
	digitalWrite(M2, 0);
	digitalWrite(M1, 0);
}