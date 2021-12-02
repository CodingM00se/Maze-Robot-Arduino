/** Maze Robot Navigation Sketch
    Written and Tested by Eric McCallum
    Reverse engineered from Parallax
*/

#include <Servo.h> 

// General fields
Servo servoLeft;
Servo servoRight;
int irLeft; // left ir sensor
int irRight; // right ir sensor
const int dt = 1000; // general delay time 

// kpl fields
const int setpoint = 2; // setpoint to reference from in the proportional control
const int kpl = -35; // proportional control constant left
const int kpr = -40; // proportional control constant right

void setup() {
  tone(4, 3000, 1000); // plays speaker tone
  delay(1000); // plays for 1 sec
  Serial.begin(9600); // Serial monitor initilization

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
  kplManeuver(); // Moves for 10 ms using kpl navigation
  kplAvoid(); // Avoids obstacles for 10 ms using kpl avoidance 
  maneuver(150, 150, 85); // move forward at a value of 150 for 85 ms
}

/* Does a frequency sweep to determine a dsitance from x Hz to y Hz */
int irDistance(int irLedPin, int irReceiverPin) {
  int distance = 0; // sets the initial distance
  for (long f = 44500; f <= 46900; f += 1000) { // determines freq sweep
    distance += irDetect(irLedPin, irReceiverPin, f); // increments the value to determine the distance 
  }
  return distance; // return the distance value 
}

/* Detects an IR signal and returns it */
int irDetect(int irLedPin, int irReceiverPin, long frequency) {
  tone(irLedPin, frequency, 8); // IRLED 38 kHz for at least 1 ms
  delay(1); // wait 1 ms
  int ir = digitalRead(irReceiverPin); // ir value received gets stored
  delay(1); // wait 1 ms
  return ir; // return 1 no detect, return 0 detect
}

/* For measuring the ir values in distance */
void irMeasure() {
  int irLeft = irDistance(9, 10); // sets left ir sensor to pins 9 and 10
  int irRight = irDistance(2, 3); // sets right ir sensor to pins 2 and 3
  Serial.print(irLeft); // print the left ir sensor value 
  Serial.print("  ");
  Serial.println(irRight); // print the right ir sensor value 
  delay(100); // wait 100 ms
}

/* KPL ir avoidance used to drive away from walls */
void kplAvoid() {
  int irLeft = irDistance(2, 3); // sets left ir sensor to pins 2 and 3
  int irRight = irDistance(9, 10); // sets right ir sensor to pins 9 and 10
  
  int driveLeft = (setpoint - irLeft) * kpl; // algorithm to determine the left drive value
  int driveRight = (setpoint - irRight) * kpr; // algorithm to determine the right drive value 
  maneuver(driveLeft, driveRight, 20); // drive with the values generated in the algorithm

  delay(10); // wait 10 ms 
}

/* KPL ir direction to navigate through maze (?) */
void kplManeuver() {
  int irLeft = irDistance(2, 3);  // sets left ir sensor to pins 2 and 3
  int irRight = irDistance(9, 10);  // sets right ir sensor to pins 9 and 10
  
  int driveLeft = (setpoint - irLeft) * kpl;  // algorithm to determine the left drive value
  int driveRight = (setpoint - irRight) * kpr;  // algorithm to determine the right drive value 

  int drive = (driveLeft + driveRight) / 2; // Similar to the avoid function, but takes the average for one drive value
  
  maneuver(drive, drive, 20); // Drive straight for the average value calculated 

  delay(10); // wait 10 ms 
}

/* Controls movement of the robot.
    speedLeft, speedRigh ranges: Backward Linear  Stop  Linear  Forward
                                 -200     -100      0   100     200
*/
void maneuver(int speedLeft, int speedRight, int msTime) {
  servoLeft.writeMicroseconds(1500 + speedLeft); // Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Right servo speed
  if (msTime == -1) { // if delay time somehow falls into a negative value, disable servso
    servoLeft.detach();
    servoRight.detach();
  }
  delay(msTime); // delay for ms time
}
