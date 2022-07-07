#include <Servo.h>
int servo = 8;
Servo myservo;

void setup() {
  myservo.attach(servo);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  if (sensorValue  < 700)  
  {
    myservo.write(20); 
    delay(300);
  }
  else myservo.write(0);

  Serial.println(sensorValue);
  delay(1);        
}
