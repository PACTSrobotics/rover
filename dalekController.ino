#include <SoftwareSerial.h>

SoftwareSerial XBeeSerial(2, 3);

#define Exicute 0x7F
#define Left 0x1
#define Right 0x2
#define UpDownOffset 88
#define LeftRightOffset 88
#define UpDownRange 
#define LeftRightRange

void setup(){
  XBeeSerial.begin(9600);
  Serial.begin(9600);
}

void loop(){
  int left = constrain(((map(analogRead(A1), 0, 1023,0,180) - 90) + (map(analogRead(A0), 0, 1023,0,180) - 90)/2)+90,0,180);
  int right = constrain(((map(analogRead(A1), 0, 1023,0,180) - 90) - (map(analogRead(A0), 0, 1023,0,180) - 90)/2)+90,0,180);
  XBeeSerial.write(Exicute);
  XBeeSerial.write(Left);
  XBeeSerial.write(left);
  XBeeSerial.write(Exicute);
  XBeeSerial.write(Right);
  XBeeSerial.write(right);
  Serial.print(map(analogRead(A1), 0,1023,0,180) ,DEC);
  Serial.print(" ");
  Serial.print(map(analogRead(A0), 0,1023,0,180) ,DEC);
  Serial.print(" ");
  Serial.print(left, DEC);
  Serial.print(" ");
  Serial.print(right, DEC);
  Serial.println(" ");

  delay(50);
  
  
}


