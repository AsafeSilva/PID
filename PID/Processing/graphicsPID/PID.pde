float kP = 0, kI = 0, kD = 0;
float setPoint;

static final int P = 1;
static final int I = 2;
static final int D = 3;
static final int S = 4;

void debug(){
  String val = "kP: " + kP + "  kI: " + kI + "  kD: " + kD;
  println(val);
}

// envia valores atualizados para o arduino
// 1 -> kP; 2 -> kI; 3 -> kD; 4 -> SetPoint
// Ex:
//    "*1_2.1" -> kP = 2.1
//    "*4_700" -> SetPoint = 700;
void sendSerial(float value, int param){
   String valSend = "*" + param + "_" + value + "\n";
   
   // se porta serial foi conectada
   if(portname != null)
     port.write(valSend);
}