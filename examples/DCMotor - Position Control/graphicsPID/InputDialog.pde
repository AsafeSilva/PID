String portname = null;

void openSerialPort()
{
  if (portname == null) return;
  if (port != null) port.stop();
  
  port = new Serial(this, portname, 9600);
  //portSerial.createText("Current Port: " + portname, 1, 15, 14);
  
  port.bufferUntil('\n');
}

void selectSerialPort()
{
  String result = (String) JOptionPane.showInputDialog(frame,
    "Selecione a porta serial que corresponde ao seu Arduino.",
    "Selecione a porta serial",
    JOptionPane.QUESTION_MESSAGE,
    null,
    Serial.list(),
    0);
    
  if (result != null) {
    portname = result;
    openSerialPort();
  }
}
   
private float value = 0;
float inputDialog(String text){
   String input = JOptionPane.showInputDialog( text );

   if(input != null)
     value = Float.parseFloat(input);
   
   return value;
}