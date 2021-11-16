#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300); 
}
