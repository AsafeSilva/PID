import javax.swing.JOptionPane;
import processing.serial.*;
Serial port = null;

Windows janelaMenu, janelaInput, janelaOutput;
Windows Instructions;
Graphic Input, Output, SetPoint;

int red   = #FF1408,
    green = #17FF08,
    blue  = #1B08FF;

PFont f;

String buff = "";    // String para armazenar valores
int NEWLINE = 10;    // '\n' = 10 em inteiro
byte index = 0;      // variável para comutar o valor para o gráfico

boolean init = false;  // variável de inicialização

void setup(){
    f = createFont("AlteHaasGrotesk_Bold-48.vlw", 18);
    textFont(f);
    size(900, 600);
    smooth();
    
    // 
    //port = new Serial(this, "COM44", 9600); 

    //for(int i = 0; i < width; i += 10)  line(i, 0, i, height);
    //for(int i = 0; i < height; i += 10)  line(0, i, width, i);
    
    /* criar objeto da classe Windows:
       nomeDaReferencia = new Windows (x0, y0, width, height);
       ou
       nomeDaReferencia = new Windows (x0, y0, width, height, backGround); 
       criar janela realmente:
       nomeDaReferencia.createWindow ("NomeDaJanela");
       ou
       nomeDaReferencia.createWindow ("NomeDaJanela", textSize);
       criar texto extra:
       nomeDaReferencia.createText ("Texto", x0, y0, textSize);
    */
    
    janelaMenu = new Windows(10, 10, width/4.5, height-20);
    janelaMenu.createWindow("Menu");  
    janelaInput = new Windows(220, 10, 670, height/2-15);
    janelaInput.createWindow("PID Input");    
    janelaOutput = new Windows(220, height/2 + 5, 670, height/2-15);
    janelaOutput.createWindow("PID Output");  
    
    /* criar objeto da classe Graphic:
       nomeDaReferencia = new Graphic (object Window, cor, minValue, maxValue);
    */
    Output   = new Graphic(janelaOutput, red, 0, 255);
    Input    = new Graphic(janelaInput,  blue, 0, 3000);
    SetPoint = new Graphic(janelaInput,  green, 0, 3000);
    
    
    // Janela de intruções
    Instructions = new Windows(10, height-130, width/4.5, 120, #DEBAB1);
    Instructions.createWindow("=== Intruções: ===\n" +
                            "S: Select Serial Port\n" + 
                            "P: Select kP\n" +
                            "I: Select kI\n" +
                            "D: Select kD\n" +
                            "T: Select SetPoint", 12); 
}

void draw(){
  // === ATUALIZA JANELAS === //
  janelaInput.createWindow("PID Input");
  janelaOutput.createWindow("PID Output"); 
  janelaMenu.createWindow("Menu");  
  Instructions.createWindow("=== Intruções: ===\n" +
                            "S: Select Serial Port\n" + 
                            "P: Select kP\n" +
                            "I: Select kI\n" +
                            "D: Select kD\n" +
                            "T: Select SetPoint", 12);
                            
  // == INSERE GRÁFICO NA JANELA == //
  Input.drawGraphic();
  Output.drawGraphic();
  SetPoint.drawGraphic();
  
  SetPoint.addNewSample((int)setPoint);
  
  // === ATUALIZA VALORES NA JANELA DE MENU ===///
  janelaMenu.createText("== Settings: ==\n\n" +
                        "SetPoint:\n     " + setPoint + "\n" +
                        "Input:\n     " + Input.getSample() + "\n" +
                        "Output:\n     " + Output.getSample() + "\n\n" +
                        "kP: " + kP + "\n" +
                        "kI: " + kI + "\n" +
                        "kD: " + kD + "\n\n", 2, 50, 18); 
           
  
  // == AQUISIÇÃO DOS DADOS VINDOS DO ARDUINO == //
  if(init && portname != null)
    while (port.available() > 0) SerialEvent((char)port.read());

}

String input = "", output = "";
boolean checkValue;
boolean stringOfNumber;  // variável para saber se os valores que chegaram só contém números 

void SerialEvent(char inChar){
  
  /*
    Recebe valores atualizados do Arduino
    Ex.:
      *200_255\n
      ==
      input = 200;
      output = 255;
  */
    
  if(inChar == '\n'){

    stringOfNumber = true;  
    // Confere toda a string para saber se só contém números   
    for(int i = 0; i < input.length(); i++){
      if(input.charAt(i) < '0' || input.charAt(i) > '9') stringOfNumber = false;
    }

    if(stringOfNumber)
      Input.addNewSample(Integer.parseInt(input));
      

    stringOfNumber = true;  
    // Confere toda a string para saber se só contém números   
    for(int i = 0; i < output.length(); i++){
      if(output.charAt(i) < '0' || output.charAt(i) > '9') stringOfNumber = false;
    }

    if(stringOfNumber)
      Output.addNewSample(Integer.parseInt(output));
    
    
    input = "";
    output = "";
  }else{
    
    if(inChar == '*') checkValue = true;
    else if(inChar == '_') checkValue = false;
    else{
      if(checkValue) input  += inChar;
      else           output += inChar;
    }
  }

}


void keyPressed(){
  if(key == 0x20) init = true;     // SPACE para iniciar!
  
  if(key == 's' || key == 'S') selectSerialPort();
  if(key == 'p' || key == 'P'){
    kP = inputDialog("Enter kP:");
    sendSerial(kP, P); // Select kP
  }  
  if(key == 'i' || key == 'I'){
    kI = inputDialog("Enter kI:");
    sendSerial(kI, I); // Select kI
  }
  if(key == 'd' || key == 'D'){
    kD = inputDialog("Enter kD:");
    sendSerial(kD, D); // Select kD
  }
  if(key == 't' || key == 'T'){
    setPoint = inputDialog("Enter SetPoint");
    sendSerial(setPoint, S);  // Select target (SetPoint)
  }
}