#include <Servo.h>

Servo servo;
int signal;
void setup()
{
  Serial.begin(9600);
  servo.write(0);
  servo.attach(8);
}

void loop()
{ 
  if(Serial.available() > 0)
  {
    signal  = Serial.parseInt();
  }
  if(signal == 1)
  {
    Serial.println("Received signal 1, doing 180 angle");
    servo.write(180);
    Serial.println("debug 0");
  }
  
  else if(signal == 2)
  {
    Serial.println("Received signal 0, returning to 0");
    servo.write(0);
    Serial.println("debug 0");
  }
  else
  {
    Serial.println("Waiting for input value... ");
  }
  delay(500);
}