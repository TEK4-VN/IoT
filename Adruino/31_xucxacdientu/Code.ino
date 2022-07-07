#include "LedControl.h"  // Include library for the 8x8 LED matrix

// Pins of the 8x8 LED Matrix
int PinCLK   = 7;  
int PinCS    = 6;
int PinDIN   = 5;
int IRSensor = 2;        // Connect the IR sensor to arduino pin 2

LedControl lc    = LedControl(PinDIN, PinCLK, PinCS, 1);
int statusSensor = 0;

// Coordinates of the Dice points in the LED matrix
int DicePic[8][6][2] =
{
  { // Matrix und Start Position:
    {9,9}, {9,8}, {9,7}, {9,6}, {9,5}, {9,4}
  },
  { //1:
    {4,4}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} 
  },
  { //2:
    {2,2}, {6,6}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} 
  },
  { //3:
    {2,6}, {6,2}, {4,4}, {-1,-1}, {-1,-1}, {-1,-1} 
  },
  { //4:
    {2,2}, {2,6}, {6,2}, {6,6}, {-1,-1}, {-1,-1}
  },
  { //5:
    {2,2}, {2,6}, {6,2}, {6,6}, {4,4}, {-1,-1}
  },
  { //6:
    {2,1}, {2,4}, {2,7}, {6,1}, {6,4}, {6,7}
  },
  { //Start:
    {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}
  }
};


// Variables of the dice: position, direction, speed for X and Y
float DiceXpos[6];
float DiceXdir[6];
volatile byte DiceXspeed[6];
float DiceYpos[6];
float DiceYdir[6];
volatile byte DiceYspeed[6];
int DiceValue;
unsigned long timestamp;

void ShowLed(int x, int y, bool onoff) {
// Show only, when x/y in matrix
  if ((x<8) and (y<8) and (x>=0) and (y>=0)) {
    lc.setLed(0, x, y, onoff);
  };
};


void ShowDot(int x, int y, bool onoff) {
  // Show or hide dice point
  ShowLed(x-1, y-1, onoff);
  ShowLed(x,   y-1, onoff);
  ShowLed(x-1, y,   onoff);
  ShowLed(x,   y,   onoff);
};


// Show the number on the dice
void ShowDicePic(int value) {
  boolean done;
  // Move all points from current position to destination of DiceValue
  for (int i = 0; i < 6; i++) {
    DiceXspeed[i] = 100;
    DiceYspeed[i] = 100;

    // Calc x values
    DiceXdir[i]   = 0;
    if (int(DiceXpos[i])>DicePic[value][i][0]) {DiceXdir[i]=-1;} 
    else if (int(DiceXpos[i])<DicePic[value][i][0]) {DiceXdir[i]=1;} 
    
    DiceYdir[i]   = 0;
    if (int(DiceYpos[i])>DicePic[value][i][1]) {DiceYdir[i]=-1;} 
    else if (int(DiceYpos[i])<DicePic[value][i][1]) {DiceYdir[i]=1;} 
  };

  do {
    // Serial.println("Moving");
    for (int i = 0; i < 6; i++) {
      if (int(DiceXpos[i])!=DicePic[value][i][0]) {
        DoStep(DiceXpos[i],DiceXdir[i],DiceXspeed[i],false);
      };
      if (int(DiceYpos[i])!=DicePic[value][i][1]) {
        DoStep(DiceYpos[i],DiceYdir[i],DiceYspeed[i],false);
      };
    };

    lc.clearDisplay(0);
    for (int i = 0; i < 6; i++) {
      ShowDot(int(DiceXpos[i]), int(DiceYpos[i]), true);
    };
    
    delay(50);

    // Dice points are on destition position
    done=true;
    for (int i = 0; i < 6; i++) {
      if (int(DiceXpos[i])!=DicePic[value][i][0]) {done=false;}
      if (int(DiceYpos[i])!=DicePic[value][i][1]) {done=false;}
    }

  } while (done==false);
  //Serial.println("End moving");

  lc.clearDisplay(0);
  for (int i = 0; i < 6; i++) {
    ShowDot(DicePic[value][i][0], DicePic[value][i][1], true);
  };
};


void DoStep(float &pos, float &dir, volatile byte &sp, bool check) {
  pos = pos + float(sp)/255*dir;

  if (check==true) {
    if (pos>7) {
        pos = 7;
        dir = dir*(-1);
    };
    if (pos<1) {
        pos = 1;
        dir = dir*(-1);
    };
  };
  // Velocity decreases every step
  if (sp>0) {sp=sp-1;}
};


void setup() {
  timestamp = millis();
  Serial.begin(9600);
  // The MAX7219 is in power-saving mode on startup. So, we need to send a wakeup call
  lc.shutdown(0, false);  
  lc.setIntensity(0, 8); // Set the brightness to a medium values 
  lc.clearDisplay(0);    // Then clear the display 

  // Innitial animation 
  for (int i = 0; i < 6; i++) {
    DiceXpos[i]   = DicePic[7][i][0];
    DiceYpos[i]   = DicePic[7][i][1];
    
    DiceXdir[i]   = random(3)-1;
    DiceYdir[i]   = random(3)-1;
    DiceXspeed[i] = random(126)+120;
    DiceYspeed[i] = random(126)+120;
  };
  
  lc.clearDisplay(0); // Clear the animation
  ShowDicePic(6);     // Display number 6 on startup
  delay(1000);
  pinMode (IRSensor, INPUT); // Sensor pin INPUT
};


void loop() {
  delay(50);
  statusSensor = digitalRead(IRSensor); // Read the data from the IR Sensor
  Serial.println(statusSensor);
  if (statusSensor == 1){
    if (millis()-timestamp>2000) {
      DiceValue = random(6)+1;          // Generate a number between 1 and 6
      ShowDicePic(DiceValue);
    };
  };
};
