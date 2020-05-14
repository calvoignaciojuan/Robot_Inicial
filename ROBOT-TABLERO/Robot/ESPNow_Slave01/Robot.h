#ifndef ROBOT
#define ROBOT

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>


///////////////////////////////////////////
//                LEDS
///////////////////////////////////////////
#define LedIndicador 15
#define LedRGB 13
#define NumLedsRGB 1

#define Microfono 35

///////////////////////////////////////////
//              ZUMBADOR
///////////////////////////////////////////
#define Zumbador 23
#define PWMCanal 3
#define PWMResolucion 8
#define PWMFreq 2000

#define Servo1Pin 2
#define Servo1Canal 10
#define Servo1AnguloInicial 150

#define Servo2Pin 4
#define Servo2Canal 11
#define Servo2AnguloInicial 150


////////////////////////////////////////////
//              FUNCIONES
////////////////////////////////////////////
void ConfigRobot();
void ZumbadorSonar();
void ServosPosicionInicial();
void MoverServo1();
void MoverServo2();

#endif
