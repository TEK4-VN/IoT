
#include <DNSServer.h>
//#include <WebServer.h>
#include <WiFiManager.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define ENA   5          // Điều khiển tốc độ động cơ bên trái     GPIO5(D1)
#define ENB   12          // Điều khiển tốc độ động cơ bên phải    GPIO12(D6)
#define IN1  4          // L298N in1 Động cơ trái quay             GPIO4(D2)
#define IN2  0          // L298N in2 Động cơ trái quay ngược lại   GPIO0(D3)
#define IN3  2           // L298N in3 Động cơ phải quay            GPIO2(D4)
#define IN4  14           // L298N in4 Động cơ phải quay ngược lại GPIO14(D5)
// You should get Auth Token in the Blynk App.
char auth[] = "kK0XQ7B6BXaQ91gketkdenJgrClRLvmW"; //YourToken
// Your WiFi credentials. 
char ssid[] = "Tầng 3"; //YourNetworkName
char pass[] = "Tanghai@"; //YourPassword
BlynkTimer timer;

int minRange = 312;
int maxRange = 712;
int tocdoxe = 800;         // 400 - 1023.
/********************************************* Tiến tới *****************************************************/
void tien()
{
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, 90);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, 80);
}
/********************************** Lùi lại ******************************************/
void lui()
{
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 80);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 80);
}
/********************************** Dừng lại ******************************************/
void dung()
{
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 0);
}
/********************************** Rẽ trái ******************************************/
void retrai()
{
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 100);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, 100);
}
/********************************** Rẽ phải ******************************************/
void rephai()
{
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, 100);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 100);
}
/**********************************************************/

BLYNK_WRITE(V0) {
  int x = param[0].asInt();
  int y = param[1].asInt();

 
 if (y < maxRange && y > minRange && x < maxRange && x > minRange) // dừng
 {
   dung(); 
   Serial.println("Dừng");
 }
 else if (y >= maxRange && x >= minRange && x<= maxRange) // tới 
 {
   tien(); Serial.println("Đang tới");
  }
 else if (x >= maxRange && y >= minRange && y<=maxRange)// rẽ phải
 { 
  retrai(); Serial.println("Đang rẽ phải");
 }
 
 else if (x<=minRange && y >= minRange && y<=maxRange)// rẽ trái
 { 
  rephai(); Serial.println("Đang rẽ trái");
 }
 
  else if (y <= minRange && x >= minRange && x<= maxRange)// Lui
  {
    lui(); Serial.println("Đang lùi");
  }
  
}

void setup() {
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT); 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(115200);

  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  
  Blynk.begin(auth, ssid, pass);

  Serial.println("connected...ok :)");
  
}

void loop() {
  Blynk.run();
  timer.run();
}
