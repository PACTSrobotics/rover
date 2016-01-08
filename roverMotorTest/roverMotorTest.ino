#include <H_Bridge.h>
// Note: Arduino 1.0 and later version IDE has SoftwareSerial Library
#include <Servo.h>



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

Servo armServo;

H_Bridge leftDrive(LEFT_DRIVE_PIN_1, LEFT_DRIVE_PIN_2, LEFT_DRIVE_EN_PIN);
H_Bridge rightDrive(RIGHT_DRIVE_PIN_1, RIGHT_DRIVE_PIN_2, RIGHT_DRIVE_EN_PIN);
H_Bridge armDrive(ARM_DRIVE_PIN_1, ARM_DRIVE_PIN_2,ARM_DRIVE_EN_PIN);
int command[2];

void setup() {
  armServo.attach(ARM_PIN_HORIZONTAL);
}

void loop() {
  leftDrive.start(H_Bridge::FORWARD, 255);
  rightDrive.start(H_Bridge::FORWARD, 255);
  delay(1000);
  leftDrive.start(H_Bridge::BACK, 255);
  rightDrive.start(H_Bridge::BACK, 255);
  delay(1000);
}
