
//Control de un servomotor giro completo en sentido horario y giro completo en sentido antihorario

#include <Arduino.h>
#include <Servo.h>

int PinBuzz = 23;
int PinLed = 15;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {

  //inicializo zumbador apagado
  pinMode(PinBuzz, OUTPUT);
  digitalWrite(PinBuzz,LOW);

  //prendo led testigo de encendido
  pinMode(PinLed, OUTPUT);
  digitalWrite(PinLed,LOW);

  myservo.attach(2);  // attaches the servo on pin 13 to the servo object
}

void loop() {
  // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(5);                       // waits 15ms for the servo to reach the position
  // }
  //
  // delay(2000);
  //
  // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(5);                       // waits 15ms for the servo to reach the position
  // }

  myservo.write(30);
  delay(3000);
  myservo.write(150);
  delay(3000);

}
