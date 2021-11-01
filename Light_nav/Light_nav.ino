#include <Servo.h>

Servo servoLeft;
Servo servoRight;

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

  int speedLeft, speedRight;

  if (ndShade > 0.0) {
    speedLeft = int(200.0 - (ndShade * 1000));
    speedLeft = constrain(speedLeft, -200, 200);
    speedRight = 200;
  }
  else {
    speedRight = int(200.0 + (ndShade * 1000.0));
    speedRight = constrain(speedRight, -200, 200);
    speedLeft = 200;
  }

  maneuver(speedLeft, speedRight, 20);
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
