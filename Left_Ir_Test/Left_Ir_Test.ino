/**
 * Left IR sensor test
 * Eric McCallum
 */


void setup() {
  tone(4, 3000, 1000); // play speaker tone on pin 4, 3000 Hz for 1 s
  delay(1000);
  pinMode(10, INPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int irLeft = irDetect(9, 10, 38000);
  Serial.println(irLeft);
  delay(100);
}

int irDetect(int irLedPin, int irReceiverPin, long frequency) {
  tone(irLedPin, frequency, 8); // IRLED 38 kHz for 1 ms
  delay(1);
  int ir = digitalRead(irReceiverPin);
  delay(1); // down time before recheck (sleep period)
  return ir; // return 1 not detect, 0 detect
}
