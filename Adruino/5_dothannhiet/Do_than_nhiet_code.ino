#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

SoftwareSerial mySoftwareSerial(4, 3); // RX, TX

DFRobotDFPlayerMini myDFPlayer;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int b, c, d, doc[4], e = 10;
float a ;

void setup() {

  Serial.begin(9600);
   lcd.init();                    
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Nhiet do:");
  mySoftwareSerial.begin(9600);
  Serial.println("Adafruit MLX90614 test");
  mlx.begin();
  if (!myDFPlayer.begin( mySoftwareSerial, true, false)) {
    while (true) {
      delay(0);
    }
    myDFPlayer.play(14);
    delay(8100);
  }
  myDFPlayer.volume(1);
}

void loop() {

  donhietdo();

}
void donhietdo() {
  myDFPlayer.play(14);
  delay(8100);
  delay(50);
  myDFPlayer.play(13);
  delay(3300);
  a = mlx.readObjectTempC() + 2, 1;
  lcd.setCursor(9,0);
  lcd.print(a);
  delay(10);
  //phần tÁCH chữ số ///
  b = a / 10 ;
  c = a - b * 10 ;
  d = a * 10 - b * 100 - c * 10 ;
  // gán phần tách vào mảng //
  doc[0] = int(b);
  doc[1] = int(c);
  doc[2] = int(e);
  doc[3] = int(d);
  //đọc âm thanh ra Loa //
  for (int i = 0; i < 4; i++) {
    switch (doc[i]) {
      case 0 : myDFPlayer.play(10);
        delay(1400);
        break;
      case 1 : myDFPlayer.play(1);
        delay(1400);
        break;
      case 2 : myDFPlayer.play(2);
        delay(1400);
        break;
      case 3 : myDFPlayer.play(3);
        delay(1400);
        break;
      case 4 : myDFPlayer.play(4);
        delay(1400);
        break;
      case 5 : myDFPlayer.play(5);
        delay(1400);
        break;
      case 6 : myDFPlayer.play(6);
        delay(1400);
        break;
      case 7 : myDFPlayer.play(7);
        delay(1400);
        break;
      case 8 : myDFPlayer.play(8);
        delay(1400);
        break;
      case 9 : myDFPlayer.play(9);
        delay(1400);
        break;
      case 10 : myDFPlayer.play(11);
        delay(1400);
        break;
    }
  }
  myDFPlayer.play(12);
  delay(1400);
  if ((a > 35) && (a < 37, 5)) {
    myDFPlayer.play(15);
    delay(5500);
  }
  if (a < 35) {
    myDFPlayer.play(16);
    delay(2500);
  }
  if (a > 38) {
    myDFPlayer.play(18);
    delay(2600);
  }
  delay(1000);
  myDFPlayer.play(17);
  delay(3300);
  delay(5100);
}
