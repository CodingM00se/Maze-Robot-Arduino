/** Maze Robot Navigation Sketch
 *  Written by Eric McCallum
 *  modified code and reverse engineered from Parallax
 */

void setup() {
  tone(4, 3000, 1000); // plays speaker tone
  delay(1000); // plays for 1 sec

  // inputs
  pinMode(10, INPUT);
  pinMode(3, INPUT);
  
  // outputs
  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);

  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop() {

}

/**
 * IR FUNCTIONS
 */
/* Does a frequency sweep to determine a dsitance from x Hz to 38000 Hz */ 
int irDistance(int irLedPin, int irReceiverPin) {
  int distance = 0; 
  for(long f = 38000; f <= 42500; f += 1000) { // determines freq sweep
    distance += irDetect(irLedPin, irReceivePin, f);
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

/**
 * LIGHT SENSOR FUNCTIONS
 */

/* Controls movement of the robot. 
 *  speedLeft, speedRigh ranges: Backward Linear  Stop  Linear  Forward
 *                               -200     -100      0   100     200
 */
void maneuver(int speedLeft, int speedRight, int msTime) {
  servoLeft.writeMicroseconds(1500 + speedLeft); // Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Right servo speed
  if(msTime == -1) {
    servoLeft.detach();
    servoRight.detach();
  }
  delay(msTime); // delay for ms time
}
