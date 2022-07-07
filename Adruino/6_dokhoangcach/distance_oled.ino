#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define trigPin D5
#define echoPin D6
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()   {
   Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

}

void loop(){
 
//    ​digitalWrite(trig,0);   // tắt chân tri
//    ​delayMicroseconds(2)
//    ​digitalWrite(trig,1);   // phát xung từ chân tri
//    ​delayMicroseconds(5);   // xung có độ dài 5 microSecond
//    ​digitalWrite(trig,0);   // tắt chân tri
    
 delay(100);
 long duration, distance;
 digitalWrite(trigPin, LOW);  
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 distance = (duration/2) / 29.1;

 distance = (duration/2) / 73.914;

 oled.setCursor(22,10);  //oled display
 oled.setTextSize(2);
 oled.setTextColor(WHITE);
 oled.println(distance);
 oled.setCursor(55,10);
 oled.setTextSize(2);

 oled.println("cm");

 oled.println("in");

 oled.display();
 delay(500);
 oled.clearDisplay();
 Serial.println(distance);//debug
}
