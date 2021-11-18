/** Maze Robot Navigation Sketch
    Written by Eric McCallum
    modified code and reverse engineered from Parallax
*/

/** Current issues:
 *  1) Issue with setting the irleft and irRight variables to global accessible variables
 *  2) issue with setting the ir sensors to move into the opposite directions and not towards it 
 */

#include <Servo.h>

Servo servoLeft;
Servo servoRight;


// kpl fields
const int setpoint = 2; // setpoint to reference from in the proportional control
const int kpl = -50; // proportional control constant left
const int kpr = -50; // proportional control constant right

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
  kplControl();
  delay(10);
  lightManeuver();
  delay(10);
}

/**
   IR FUNCTIONS
*/

/* Does a frequency sweep to determine a dsitance from x Hz to 38000 Hz */
int irDistance(int irLedPin, int irReceiverPin) {
  int distance = 0;
  for (long f = 38000; f <= 46900; f += 1000) { // determines freq sweep
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
void kplControl() {
  int driveLeft = (setpoint - irLeft) * kpl;
  int driveRight = (setpoint - irRight) * kpr;
  maneuver(driveLeft, driveRight, 20);
}

/**
   LIGHT SENSOR FUNCTIONS
*/


void lightManeuver() {
  float tLeft = float(rcTime(8)); // Get left light and make float
  float tRight = float(rcTime(6)); // Get right light and make float

  float ndShade;  // Normalized differential shade
  ndShade = tRight / (tLeft + tRight) - 0.5;  // Calculate and subtract 0.5

  int speedLeft, speedRight;  // Declare speed variables

  if (ndShade > 0.0) {  // is there shade on the right?
    speedLeft = int(200.0 - (ndShade * 3000.0)); // slow down left wheel
    speedLeft = constrain(speedLeft, -200, 200);
    speedRight = 200; // Full speed right wheel
  }

  else {  // is there shade on the left?
    speedRight = int(200.0 + (ndShade * 3000.0)); // slow down right wheel
    speedRight = constrain(speedRight, -200, 200);
    speedLeft = 200;  // full speed left wheel
  }
  maneuver(speedLeft, speedRight, 20);  // set wheel speeds
}

/* Charges the capacitors and gets the time it takes for decay for light nav */
long rcTime(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(5);
  pinMode(pin, INPUT);
  digitalWrite(pin, LOW);
  long time = micros();
  while (digitalRead(pin));
  time = micros() - time;
  return time;
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
