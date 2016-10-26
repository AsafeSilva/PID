# PID + Processing

Controle, ajuste e visualize com a tela de supervisório seu sistema com PID!

## PID.h

Esta biblioteca possui métodos que permitem controlar sistemas com a plataforma Arduino através
de um controlador PID simples implementada em C++.
Esta classe recebe a leitura (do sensor de temperatura, por exemplo), e calcula a saída P.I.D. de 
acordo com os ganhos (kP, kI, kD) fornecidos.

- A classe PID permite três tipos de Contrutores:

```
PID myPID; 
// Com este contrutor os ganhos kP, kI e kD são iniciadas com 0.
```

```
// Com este contrutor os ganhos kP, kI e kD são iniciadas com 0.
PID myPID; 
```

```
// Inicia os ganhos Kp, Ki, Kd, respectivamente, com valores desejados
PID myPID(1.0, 1.0, 1.0);
```

```
// Mesmo que o anterior, com o acréscimo de dois parâmetros: outMin e outMax (saída mínima e saída máxima).
PID myPID(1.0, 1.0, 1.0, 0, 255); 
```

- Possui os seguintes métodos:

```
// Seta um novo setPoint (valor desejado)
void setSetPoint(float _setPoint);
```

```
// Seta ganhos separadamente
void setKp(float _kP);
void setKi(float _kI);
void setKd(float _kD);  
```

```
// Seta todos os ganhos numa só função
void setParameters(float _kP, float _kI, float _kD);
```

```
// Seta limites da saída
void setLimits(int _outMin, int _outMax);
```

```
// Metódo para atualizar valor de entrada da planta PID
void addInput(float _newInput);
```

```
// Método que realiza cálculos e retorna a saída do PID
float compute();
```

```
// Métodos que retorna parametros do PID
float getKp();
float getKi();
float getKd();
float getSetPoint();
```

## PIDProcessing.h
