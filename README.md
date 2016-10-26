# PID + Processing

Controle, ajuste e visualize com a tela de supervisório seu sistema com PID!

# PID.h

Esta biblioteca possui métodos que permitem controlar sistemas com a plataforma Arduino através
de um controlador PID simples implementada em C++.
Esta classe recebe a leitura (do sensor de temperatura, por exemplo), e calcula a saída P.I.D. de 
acordo com os ganhos (kP, kI, kD) fornecidos.

- A classe PID permite três tipos de Contrutores:

<div class="highlight highlight-source-c++">
<pre>PID myPID;
<span class="pl-c">// Com este contrutor os ganhos kP, kI e kD são iniciadas com 0.</span>
</pre>
</div>

<div class="highlight highlight-source-c++">
<pre>PID myPID(1.0, 1.0, 1.0);
<span class="pl-c">// Inicia os ganhos Kp, Ki, Kd, respectivamente, com valores desejados</span>
</pre>
</div>

<div class="highlight highlight-source-c++">
<pre>PID myPID(1.0, 1.0, 1.0, 0, 255); 
<span class="pl-c">// Mesmo que o anterior, com o acréscimo de dois parâmetros: outMin e outMax (saída mínima e saída máxima).
</span>
</pre>
</div>


- Possui os seguintes métodos:

<div class="highlight highlight-source-c++">
<pre>void setSetPoint(float _setPoint);
<span class="pl-c">// Seta um novo setPoint (valor desejado)</span>
</pre>
</div>

<div class="highlight highlight-source-c++">
<pre>
void setKp(float _kP);
void setKi(float _kI);
void setKd(float _kD); 
<span class="pl-c">// Seta ganhos separadamente</span>
</pre>
</div>


<div class="highlight highlight-source-c++">
<pre>
void setParameters(float _kP, float _kI, float _kD);
<span class="pl-c">// Seta todos os ganhos numa só função</span>
</pre>
</div>


<div class="highlight highlight-source-c++">
<pre>
void setLimits(int _outMin, int _outMax);
<span class="pl-c">// Seta limites da saída</span>
</pre>
</div>

<div class="highlight highlight-source-c++">
<pre>
void addInput(float _newInput);
<span class="pl-c">// Metódo para atualizar valor de entrada da planta PID</span>
</pre>
</div>

<div class="highlight highlight-source-c++">
<pre>
float compute();
<span class="pl-c">
// Método que realiza cálculos e retorna a saída do PID</span>
</pre>
</div>

<div class="highlight highlight-source-c++">
<pre>
float getKp();
float getKi();
float getKd();
float getSetPoint();
<span class="pl-c">// Métodos que retornam parâmetros do PID</span>
</pre>
</div>

# PIDProcessing.h
