#define BLYNK_TEMPLATE_ID           "TMPLC2bbysVN"
#define BLYNK_DEVICE_NAME           "SmartGarden"
#define BLYNK_AUTH_TOKEN            "Lcq_f2OnmEyHYmOZiV9WYErnpQCPijGA"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ESP32";
char pass[] = "hoilamgi12";

#define DHTPIN 21          // What digital pin we're connected to
#define DHTTYPE DHT11
#define SOILMOISTURE_PIN 35
#define RELAY_PIN 23     

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

float t =0;
int h = 0;
int manual_button;
int buttonState;

void sendSensor()
{
  int hu = analogRead(SOILMOISTURE_PIN);
  h = map(hu,0,4095,100,0);
  t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  Serial.print(hu);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V0, t);
}

void setup()
{
  pinMode(SOILMOISTURE_PIN,INPUT);
  pinMode(RELAY_PIN,OUTPUT);
  digitalWrite(RELAY_PIN,HIGH);
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(500L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
  Mode();
}
BLYNK_WRITE(V4){
  manual_button =  param.asInt();
  Serial.println(manual_button);
}
WidgetLED led_state(V3);
BLYNK_WRITE(V2){                      //auto hoac manual
  buttonState = param.asInt();
  Serial.println(buttonState);
}

void Mode(){
  if (buttonState == 1) {
    if (h <=42 && t <=35){
      digitalWrite(RELAY_PIN, LOW);
      led_state.on();
    }else if ( h >42) {
      digitalWrite(RELAY_PIN, HIGH);
      led_state.off();
    }
  }else if (buttonState == 0){
      if (manual_button == 1){
      digitalWrite(RELAY_PIN, LOW);
      led_state.on();

    }else {
      digitalWrite(RELAY_PIN, HIGH);
      led_state.off();
    }
  }
  }
