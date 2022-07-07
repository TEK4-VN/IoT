#define MK_SENSOR 7
#define MK_RELAY 8

int counter = 0, sensorRead = 0;
unsigned long time_detect = 0, last_time_detect = 0;
void setup() {
  pinMode(MK_SENSOR, INPUT);
  pinMode(MK_RELAY, OUTPUT);
  Serial.begin(115200);
  digitalWrite(MK_RELAY,0);
}

void loop() {
  sensorRead = digitalRead(MK_SENSOR);
  if (sensorRead == 0)
  {
    if (counter == 0) {
      time_detect = millis();
      last_time_detect = time_detect;
      counter++;
    } else if (counter > 0 && millis() - last_time_detect >= 50) {
      last_time_detect = millis();
      counter++;
    }
  }

  if (millis() - time_detect >= 700) {
    if (counter == 2)
    {
      digitalWrite(MK_RELAY, !digitalRead(MK_RELAY));
    }
    counter = 0 ;
  }

  Serial.println(counter);
}
