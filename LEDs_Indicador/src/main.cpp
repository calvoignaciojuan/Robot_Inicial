
// Test led placa robot inicial GPIO15

#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(15,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(15,HIGH);
  delay(500);
  digitalWrite(15,LOW);
  delay(1000);

}
