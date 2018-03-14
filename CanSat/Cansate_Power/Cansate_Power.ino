#include <Wire.h>
#include <math.h>
#define U1 A3
#define U2 A2
#define U3 A1
#define U4 A0
#define POWER_BOARD 0x11
#define DEBUG
float  BatteryVol,LoadVol,PowerSystem,PowerLoad;
uint8_t powerDate[16];

void setup() {
  // put your setup code here, to run once:
  Wire.begin(POWER_BOARD);
  Wire.onRequest(readVolandWatt);
  Serial.begin(9600);
  pinMode(U1,INPUT);
  pinMode(U2,INPUT);
  pinMode(U3,INPUT);
  pinMode(U4,INPUT);
}

//void readVolandWatt(/*int howMany*/);
void debugPrint()
{
 Serial.println();
 Serial.print(BatteryVol);
 Serial.print("  ");
 Serial.println(LoadVol);
 Serial.print(PowerSystem);Serial.print("  ");
 Serial.println(PowerLoad);
 delay(1000);
}
void loop() {
  // put your main code here, to run repeatedly:
  readVolandWatt();
  #ifdef DEBUG
  debugPrint();
  #endif
}


  


void readVolandWatt(){
  float V1,V2,V3,V4;
 BatteryVol  = (analogRead(U1)*10.0)/1024.0;
  V2 = (analogRead(U2)*10.0)/1024.0;
  V1 = abs(BatteryVol-V2);
  PowerSystem = V1*BatteryVol/0.05;
  LoadVol = (analogRead(U3)*10.0)/1024.0;
  V4 = (analogRead(U4)*10.0)/1024.0;
  V3 = abs(LoadVol-V4);
  PowerLoad = V3*LoadVol/0.05;
 /*Serial.print(BatteryVol);
  Serial.print("  ");
  Serial.println(LoadVol);*/
  memcpy(powerDate,&BatteryVol,4);
  memcpy(powerDate+4,&LoadVol,4);
  memcpy(powerDate+8,&PowerSystem,4);
  memcpy(powerDate+12,&PowerLoad,4); 
  for (int i=0;i<16;i++)
  {
  Wire.write(powerDate[i]);
 // Serial.print(powerDate[i]);
  delay(1);
 
  }
}


