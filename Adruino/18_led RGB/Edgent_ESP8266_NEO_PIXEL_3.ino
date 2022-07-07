#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME "LED RGB NEOPIXEL"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_NODE_MCU_BOARD
//#define USE_WEMOS_D1_MINI
#include "BlynkEdgent.h"
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include "FastLED.h"
#define NUM_LEDS1 16
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds1[NUM_LEDS1];
#define LEDPIN D1
#define OUTPUT1 D2
int bright=255;
int r,g,b;
BlynkTimer timer;
WidgetLED led(V0);

void setup(){
  Serial.begin(115200);
  delay(100);
  pinMode(OUTPUT1,OUTPUT);
  BlynkEdgent.begin();

  FastLED.addLeds<LED_TYPE, LEDPIN, COLOR_ORDER>(leds1, NUM_LEDS1).setCorrection( TypicalLEDStrip );
  timer.setInterval(1000,handleTimer);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
  static1(r, g, b,bright);
}
void handleTimer(){
  if (led.getValue()) {
    led.off();
  } else {
    led.on();
  }
}
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V1,V2,V3,V4,V5);
}
BLYNK_WRITE(V1){
  r = param.asInt();
}
BLYNK_WRITE(V2){
  g = param.asInt();
}
BLYNK_WRITE(V3){
  b = param.asInt();
}
BLYNK_WRITE(V4){
  bright = param.asInt(); 
}
BLYNK_WRITE(V5){
  int p = param.asInt();
  digitalWrite(OUTPUT1,p);
}
void static1(int r, int g, int b,int brightness){
  FastLED.setBrightness(brightness);
  for (int i = 0; i < NUM_LEDS1; i++ )
  {
    leds1[i] = CRGB(r, g, b);
  }
  FastLED.show();
}
