#include <SoftwareSerial.h>

SoftwareSerial XBeeSerial(2, 3);

#define Exicute 0x77
#define Left 0x1
#define Right 0x2
#define Head 0x3
#define Stock 0x4
#define Light 0x5
#define UpDownOffset 88
#define LeftRightOffset 88
#define UpDownRange 
#define LeftRightRange

void setup(){
  XBeeSerial.begin(9600);
  Serial.begin(9600);
}

void loop(){
  //int right = constrain(((map(analogRead(A0), 0, 1023,0,255) - 90) + (map(analogRead(A1), 0, 1023,0,255) - 90)/2)+90,0,255);
  //int left = constrain(((map(analogRead(A0), 0, 1023,0,255) - 90) - (map(analogRead(A1), 0, 1023,0,255) - 90)/2)+90,0,255);
  int right = map(analogRead(A0), 0,1023,0,255);
  int left = map(analogRead(A3), 0,1023,0,255);

  
  int head = map(analogRead(A2), 0,1023,0,180)+2;
  
  XBeeSerial.write(Exicute);
  XBeeSerial.write(Left);
  XBeeSerial.write(left);
  XBeeSerial.write(Exicute);
  XBeeSerial.write(Right);
  XBeeSerial.write(right);
  XBeeSerial.write(Exicute);
  XBeeSerial.write(Head);
  XBeeSerial.write(head);
  
  Serial.print(map(analogRead(A1), 0,1023,0,180) ,DEC);
  Serial.print(" ");
  Serial.print(map(analogRead(A0), 0,1023,0,180) ,DEC);
  Serial.print(" ");
  Serial.print(left, DEC);
  Serial.print(" ");
  Serial.print(right, DEC);
  //Serial.print(" ");
  //Serial.print(map(analogRead(A2), 0,1023,0,180) ,DEC);
  Serial.println(" ");

  delay(50);
  
  
}


