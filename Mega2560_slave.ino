#include <Wire.h>
int fuggStatus = 0;
int fuggRaw=0;
int incArray[20];
byte incByte=0;//_____     _____     ________
int sor=0;           //r,g,b,l,w,r,g,b,l,w,r ,g ,b, l, w
int analogPinArray[20]{2,3,4,0,5,6,7,0,8,9,10,11,12,0, 13};
                     //0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15.ödik
int digitalPinArray[10]{15,16,17,18,19};

void setup(){        //pinMode(pin,OUTPUT) be kell állítani!!!
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  for(int n=0;n>20;n++){
    pinMode(analogPinArray[n], OUTPUT);
    pinMode(digitalPinArray[n], OUTPUT);
    
  }
  
}

void loop(){
  delay(100);
}

void receiveEvent(int howMany){
  Serial.print('\n');
  while(Wire.available()){
    for(sor=0;sor<20;sor++){
      incByte = Wire.read();
      incArray[sor]=incByte;
      analogWrite(analogPinArray[sor], incByte);
      Serial.print(incArray[sor]);
      Serial.print(",");
      fuggRaw = incArray[14]
      if (incArray[14] != fuggStatus){ //Alapból 0-án, van, nincs call()
        fuggelhuzo(fuggRaw);
        fuggStatus = incArray[14];
      }
    }
  }
}
void fuggelhuzo(int fuggRaw){
  fuggVal = fuggRaw*22750;            //91000/4=22750
  digitalWrite(ENA, LOW);             //enable stepper
  stepper.runToNewPosition(fuggVal);
  digitalWrite(ENA, HIGH);            //disable stepper
}
