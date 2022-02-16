#include <Wire.h>
int incArray[20];
byte incByte=0;//_____     _____     ________
int sor=0;     //r,g,b,l,w,r,g,b,l,w,r ,g ,b, l, w
int pinArray[20]{2,3,4,0,5,6,7,0,8,9,10,11,12,0,13};

void setup(){
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
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
      analogWrite(pinArray[sor], incByte);
      Serial.print(incArray[sor]);
      Serial.print(",");
    }
  }
  //Serial.print(incArray[12]);
}
