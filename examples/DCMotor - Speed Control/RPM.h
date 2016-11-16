class RPM{
private:
  long time;
  long last_time;
  long rpm;
  int divisions;
  
public:

  volatile unsigned long rotation;

  RPM(long time, int divisions){
    this->divisions = divisions;
    this->time = time;
    last_time = millis();
  }

  void process(){
    /*
      time * 1E-03 s ----- rotation
                 1 s ----- RPS
      RPS = 1 * rotation / (time * 1E-03)           
    */

    if(millis() - last_time >= time){
      rpm = rotation * 1000L / (divisions * time);
      rotation = 0;
      last_time = millis();
    }
    
    /*  X rot------X millis
         xROT------60000millis (1min)
        ROT = rot * 60000 / millis
    */
    // long dt = millis() - last_time;
    // long dRot = _rotation - last_rot;
    // long rpm = _rotation * 60000 / dt;
    // last_rot = _rotation;
    // last_time = millis();
  }

  long getRPM(bool debug = false){
    if(debug){
      Serial.print(rpm);
      Serial.println(" RPS");   
    }
      return rpm;
  }

};