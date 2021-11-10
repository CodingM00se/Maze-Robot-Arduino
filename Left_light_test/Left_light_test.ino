/**
 * Right light sensor test
 * Eric McCallum
 */


void setup() {
  tone(4, 3000, 1000);
  delay(1000);

  Serial.begin(9600);
}

void loop() {
  long tRight = rcTime(6);
  Serial.print("tRight = ");
  Serial.print(tRight);
  Serial.println(" us");
  delay(1000);
}

long rcTime(int pin) {
  pinMode(pin, OUTPUT); // charge capacitor
  digitalWrite(pin, HIGH); // ... by setting pin output to high
  delay(1); // for 1 ms
  pinMode(pin, INPUT); // set pin to input
  digitalWrite(pin, LOW); // with no pullup
  long time = micros(); // mark the time

  while(digitalRead(pin)); // wait for voltage < threshold 
  time = micros() - time; // calculate decay time
  return time; // return decay time 
}
