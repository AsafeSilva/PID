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

Já esta classe é usada quando quer processar o PID e também enviar e receber dados do *Processing*.
Ela herda da class `PID.h`, portanto todos os métodos contidos em `PID.h` também podém ser acessados por ela, sem a necessidade de instanciar uma nova referência para a classe `PID.h`.

A classe `PIDProcessing.h` possui o mesmo construtor da `PID.h` que já foi explicado anteriormente.
E possui os seguintes métodos:

```
void sendToGraphics(int input, int output);
```
Este método envia os valores de entrada e saída para o *Processing* (via Serial, portanto o Arduino deve estar conectado ao PC), para serem "desenhados" no Gráfico.


```
void receiveProcessing(char inChar);
```
Este método recebe os parâmetros setados no *Processing* (kP, kI, kD, setPoint) e atualiza as variáveis da classe `PID.h`.
É aconselhado que ele seja "chamado" dentro da função `serialEvent()` do Arduino. Por exemplo:

```ruby
void serialEvent(){
    while(Serial.available()){
    	char inChar = (char)Serial.read();
    	myPid.receiveProcessing(inChar);
    }
}
```


