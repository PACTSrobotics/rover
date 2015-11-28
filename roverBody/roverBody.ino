#include <H_Bridge.h>
// Note: Arduino 1.0 and later version IDE has SoftwareSerial Library
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial XBeeSerial(2, 3);


#define ARM_PIN_HORIZONTAL         11


#define LEFT_DRIVE_PIN_1  13
#define LEFT_DRIVE_PIN_2  12
#define LEFT_DRIVE_EN_PIN 10

#define RIGHT_DRIVE_PIN_1 7
#define RIGHT_DRIVE_PIN_2 8
#define RIGHT_DRIVE_EN_PIN 9

#define ARM_DRIVE_PIN_1 A0
#define ARM_DRIVE_PIN_2 4
#define ARM_DRIVE_EN_PIN 6



// Input Commands#define HEAD_PIN           10

#define BEGIN_COMMAND  0x77  // decimal = 119, binary = 0111 0111
#define MOTORLEFT      0x1   // decimal =   1, binary = 0000 0001
#define MOTORRIGHT     0x2   // decimal =   2, binary = 0000 0010

Servo armServo;

H_Bridge leftDrive(LEFT_DRIVE_PIN_1, LEFT_DRIVE_PIN_2, LEFT_DRIVE_EN_PIN);
H_Bridge rightDrive(RIGHT_DRIVE_PIN_1, RIGHT_DRIVE_PIN_2, RIGHT_DRIVE_EN_PIN);
H_Bridge armDrive(ARM_DRIVE_PIN_1, ARM_DRIVE_PIN_2,ARM_DRIVE_EN_PIN);
int command[2];

void setup() {
  XBeeSerial.begin(9600);     
  armServo.attach(ARM_PIN_HORIZONTAL);
}

void loop() {
  // listen for wireless commands
  if (XBeeSerial.available() > 0) {
    if (readCommand() > 0) {
      executeCommand();
    }
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
  
  if(c == MOTORLEFT){
     if(speed >= 0) {
       leftDrive.start(leftDrive.FORWARD, map(constrain(speed,0,127), 0, 127, 0, 255));
     }
     
  }
  if(c == MOTORRIGHT){

  }

}

