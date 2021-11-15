#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  tone(4, 3000, 1000);
  delay(1000);

  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700); // 
}
