#include <Wire.h>
#include <AccelStepper.h>
const int STEP = 52;
const int DIR = 50;
const int ENA = 48;
int fuggStatus = 0;
int fuggRaw=0;
int fuggVal=0;
int incArray[20];
byte incByte=0;      //_____     _____     _______
int sor=0;           //r,g,b,l,w,r,g,b,l,w,r ,g ,b, l, w
int analogPinArray[20]{2,3,4,0,5,6,7,0,8,9,10,11,12,0, 13};
                     //0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15.ödik
AccelStepper stepper (1,STEP,DIR);

void setup(){        //pinMode(pin,OUTPUT) be kell állítani!!!
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(ENA, OUTPUT);
  stepper.setMaxSpeed(10000);
  stepper.setAcceleration(10000);
  digitalWrite(ENA, HIGH);
  for(int n=0;n>20;n++){
    pinMode(analogPinArray[n], OUTPUT);
  }
}

void loop(){
  delay(100);
}
void receiveEvent(int howMany){
  Serial.print('\n');
  Serial.println("receive_event()");
  while(Wire.available()){
    Serial.println("wire_av()");
    for(sor=0;sor<20;sor++){
      incByte = Wire.read();
      incArray[sor]=incByte;
      analogWrite(analogPinArray[sor], incByte);
      Serial.print(incArray[sor]);
      Serial.print(",");
      }
    }
    fuggRaw = incArray[15];
    if (fuggRaw != fuggStatus){ //Alapból 0-án, van, nincs call()
      Serial.print('\n');
      Serial.println("in the if statement");
      fuggelhuzo(fuggRaw);
      fuggStatus = fuggRaw;
    }
}
void fuggelhuzo(int fuggRaw){
  Serial.println("_____fuggelhuzo()_____");
  Serial.print("fuggRaw: ");
  Serial.println(fuggRaw);
  delay(1000);
  digitalWrite(ENA, LOW);
  digitalWrite(ENA, HIGH);
  /*delay(100);
  fuggRaw=1;
  fuggVal = fuggRaw*22750;            //91000/4=22750
  digitalWrite(ENA, LOW);             //enable stepper
  stepper.runToNewPosition(500);
  stepper.runToNewPosition(0);
  digitalWrite(ENA, HIGH);            //disable stepper
*/
}
