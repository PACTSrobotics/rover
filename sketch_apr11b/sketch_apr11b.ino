// Note: Arduino 1.0 and later version IDE has SoftwareSerial Library
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial XBeeSerial(2, 3);
                
#define HEAD               6                   
#define EYE                11    
// Input Commands#define HEAD_PIN           10

#define BEGIN_COMMAND  0x7F  // decimal = 127, binary = 0111 1111
#define HEADMOTOR      0x3   // decimal =   1, binary = 0000 0001
#define EYEMOTOR       0x4   // decimal =   2, binary = 0000 0010
Servo Eye;
Servo HeadRotate;

int command[2];

void setup() {
  XBeeSerial.begin(9600);     
  Eye.attach(EYE);
  HeadRotate.attach(HEAD);
  pinMode(13, OUTPUT);
}

void loop() {
  // listen for wireless commands
  if (XBeeSerial.available() > 0) {
    if (readCommand() > 0) {
      executeCommand();
      digitalWrite(13,HIGH);
    }
    digitalWrite(13, HIGH);
  }
}

int readCommand() {
  int b = XBeeSerial.read();
  if (b == BEGIN_COMMAND) {
    command[0] = readByte();
    command[1] = readByte();
    return 1;
  } else {
    return 0;
  }
}

// blocking read
int readByte() {
  while (true) {
    if (XBeeSerial.available() > 0) {
      return XBeeSerial.read();
    }
  }
}


void executeCommand() {
  int c     = command[0];
  int speed = command[1];
  
  if(c == HEADMOTOR){
    HeadRotate.write(speed);
  }
  if(c == EYEMOTOR){
    Eye.write(speed);
  }

}


