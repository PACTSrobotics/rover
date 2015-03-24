// Note: Arduino 1.0 and later version IDE has SoftwareSerial Library
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial XBeeSerial(2, 3);
                
#define LEFT_PIN           6                   
#define RIGHT_PIN          11    
#define HEAD_PIN           10
// Input Commands
#define BEGIN_COMMAND  0x7F  // decimal = 127, binary = 0111 1111
#define MOTORLEFT      0x1   // decimal =   1, binary = 0000 0001
#define MOTORRIGHT     0x2   // decimal =   2, binary = 0000 0010
#define HEADMOTOR      0x4   // decimal =   4, binary = 0000 0100
Servo Left;
Servo Right;
Servo Head;

int command[2];

void setup() {
  XBeeSerial.begin(9600);     
  Left.attach(LEFT_PIN);
  Right.attach(RIGHT_PIN);
  Head.attach(HEAD_PIN);
  pinMode(13, OUTPUT);
}

void loop() {
  // listen for wireless commands
  if (XBeeSerial.available() > 0) {
    if (readCommand() > 0) {
      executeCommand();
      digitalWrite(13,OUTPUT);
    }
    digitalWrite(13, OUTPUT);
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
  
  if(c & MOTORLEFT){
    Left.write(speed);
  }
  if(c & MOTORRIGHT){
    Right.write(speed);
  }
  if(c & HEADMOTOR){
    Head.write(speed);
  }

  /*
  digitalWrite(DRIVE_ENABLE_PIN, LOW);
  if (c & FORWARD) {
    digitalWrite(BACKWARD_PIN, LOW);
    digitalWrite(FORWARD_PIN, HIGH);
  }
  if (c & BACKWARD) {
    digitalWrite(FORWARD_PIN, LOW);
    digitalWrite(BACKWARD_PIN, HIGH);
  }
  if (c & (FORWARD | BACKWARD)) {
    //digitalWrite(DRIVE_ENABLE_PIN, HIGH);
    analogWrite(DRIVE_ENABLE_PIN, speed);
  }

  digitalWrite(TURN_ENABLE_PIN, LOW);
  if (c & LEFT) {
    digitalWrite(RIGHT_PIN, LOW);
    digitalWrite(LEFT_PIN, HIGH);
  }
  if (c & RIGHT) {
    digitalWrite(LEFT_PIN, LOW);
    digitalWrite(RIGHT_PIN, HIGH);
  }
  if (c & (LEFT | RIGHT)) {
    digitalWrite(TURN_ENABLE_PIN, HIGH);
  }*/
}

