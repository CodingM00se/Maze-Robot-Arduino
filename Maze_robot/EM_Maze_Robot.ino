/** Maze Robot Navigation Sketch
    Written by Eric McCallum
    modified code and reverse engineered from Parallax
    ideas: 
    - replace the light sensors to the side and IR sensors to the front
    - change the light behavior to back up instead of avoid shade (avoid arches in other words) 
    change behavior first and if all else fails, try replacing the locations next class. 
*/

/** Current issues:
 *  gets stuck on columns. can be reduced by sharper turns. recommended by classmate to gradually increase frequency
 */

#include <Servo.h>

Servo servoLeft;
Servo servoRight;
int irLeft;
int irRight;
int dt = 1000;

// kpl fields
const int setpoint = 2; // setpoint to reference from in the proportional control
const int kpl = -45; // proportional control constant left
const int kpr = -55; // proportional control constant right

void setup() {
  tone(4, 3000, 1000); // plays speaker tone
  delay(1000); // plays for 1 sec
  Serial.begin(9600);

  // inputs
  pinMode(10, INPUT);
  pinMode(3, INPUT);

  // outputs
  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);

  // servo attachments
  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop() {
  kplManeuver();
  kplAvoid();
  maneuver(150, 150, 95);
}

/* Does a frequency sweep to determine a dsitance from x Hz to 38000 Hz */
int irDistance(int irLedPin, int irReceiverPin) {
  int distance = 0;
  for (long f = 44400; f <= 46900; f += 1000) { // determines freq sweep
    distance += irDetect(irLedPin, irReceiverPin, f);
  }
  return distance;
}

/* Detects an IR signal and returns it */
int irDetect(int irLedPin, int irReceiverPin, long frequency) {
  tone(irLedPin, frequency, 8); // IRLED 38 kHz for at least 1 ms
  delay(1); // wait 1 ms
  int ir = digitalRead(irReceiverPin); // ir value received gets stored
  delay(1);
  return ir; // return 1 no detect, return 0 detect
}

/* For measuring the ir values in distance */
void irMeasure() {
  int irLeft = irDistance(9, 10);
  int irRight = irDistance(2, 3);
  Serial.print(irLeft);
  Serial.print("  ");
  Serial.println(irRight);
  delay(100);
}

/* KPL ir avoidance used to drive away from walls */
void kplAvoid() {
  int irLeft = irDistance(2, 3);
  int irRight = irDistance(9, 10);
  
  int driveLeft = (setpoint - irLeft) * kpl;
  int driveRight = (setpoint - irRight) * kpr;
  maneuver(driveLeft, driveRight, 20);

  delay(10);
}

/* KPL ir direction to navigate through maze (?) */
void kplManeuver() {
  int irLeft = irDistance(2, 3);
  int irRight = irDistance(9, 10);
  
  int driveLeft = (setpoint - irLeft) * kpl;
  int driveRight = (setpoint - irRight) * kpr;

  int drive = (driveLeft + driveRight) / 2;
  
  maneuver(drive, drive, 20);

  delay(10);
}

/* Controls movement of the robot.
    speedLeft, speedRigh ranges: Backward Linear  Stop  Linear  Forward
                                 -200     -100      0   100     200
*/
void maneuver(int speedLeft, int speedRight, int msTime) {
  servoLeft.writeMicroseconds(1500 + speedLeft); // Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Right servo speed
  if (msTime == -1) {
    servoLeft.detach();
    servoRight.detach();
  }
  delay(msTime); // delay for ms time
}
