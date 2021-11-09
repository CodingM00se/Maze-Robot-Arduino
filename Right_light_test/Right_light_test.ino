/**
 * Right light sensor test
 * Eric McCallum
 */


void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Light value right sensor = ");
  Serial.println(analogRead(A1));
  delay(1000);
}
