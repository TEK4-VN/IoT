
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
MPU6050 mpu6050(Wire);
#define OLED_Address 0x3C // 0x3C device address of I2C OLED. Few other OLED has 0x3D
Adafruit_SSD1306 oled(128, 64); // create our screen object setting resolution to 128x64
 
long timer = 0;
int steps = 0;
float distanceinonestep = 71; //change it according to your distance between your legs in cm
float distance;
void setup() {
  Serial.begin(9600);
oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.display();
  delay(2000);
  // Clear the buffer
  oled.clearDisplay();
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();
  if (millis() - timer > 1000) {
    Serial.print(mpu6050.getAccY());
  }
  if (mpu6050.getAccY() > 1)
  {
    steps += 1;
    delay(350);
  }

  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(10, 0);
  oled.println("steps");
  oled.println(steps);


  distance = steps * distanceinonestep / 100;
  oled.println("distance");
  oled.println(distance);
  oled.display();
  delay(100);
  oled.clearDisplay();
}
