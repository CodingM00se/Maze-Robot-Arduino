/**
 * Right light sensor test
 * Eric McCallum
 */


void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Light value left sensor = ");
  Serial.println(analogRead(A0));
  delay(1000);
}
