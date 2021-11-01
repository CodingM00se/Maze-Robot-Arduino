#include <Servo.h>

Servo servoLeft;
Servo servoRight;

/* 
 *  notes:
 *  brightness value should be above 7000. 
 *  if both 7000, go forward
 *  if one is 7000, pivot into the value
 *  if neither is 7000, go back 
 */

void setup() {
  tone(4, 3000, 1000);
  delay(1000);
  Serial.begin(9600);
  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop() {
  float tLeft = float(rcTime(8));
  float tRight = float(rcTime(6));
  float ndShade;
  ndShade = tRight / (tLeft + tRight) - 0.5;

  Serial.println("tLeft   ndShade   tRight");
  Serial.print(tLeft);
  Serial.print(" ");
  Serial.print(ndShade);
  Serial.print("    ");
  Serial.println(tRight);
  Serial.println(' ');
  delay(300);
}

long rcTime(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(5);
  pinMode(pin, INPUT);
  digitalWrite(pin, LOW);
  long time = micros();
  while(digitalRead(pin));
  time = micros() - time;
  return time;
}

void maneuver(int speedLeft, int speedRight, int msTime) {
  servoLeft.writeMicroseconds(1500 + speedLeft);
  servoRight.writeMicroseconds(1500 - speedRight);
  if(msTime == -1) {
    servoLeft.detach();
    servoRight.detach();
  }
  delay(msTime);
}
