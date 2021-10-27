/* Simple functions movements */

#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  tone(4, 3000, 1000);
  delay(1000);
  servoLeft.attach(13);
  servoRight.attach(12);

  maneuver(200, 2000, 2000);
  maneuver(0, 0, -1);
}

void loop() {
}

void maneuver(int speedLeft, int speedRight, int msTime) {
  // speedleft, speedRight, ranges: backward Linear Stop Linear Forward
  //                                -200,    -100   0    100    200
  servoLeft.writeMicroseconds(1500 + speedLeft);
  servoRight.writeMicroseconds(1500 - speedRight);
  if(msTime == -1) {
    servoLeft.detach();
    servoRight.detach();
  }
  delay(msTime);
}

void forward(int timeVal) {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(timeVal);
}

void turnLeft(int timeVal) {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(timeVal);
}

void turnRight(int timeVal) {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(timeVal);
}

void backward(int timeVal) {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  delay(timeVal);
}

void disableServos() {
  servoLeft.detach();
  servoRight.detach();
}
