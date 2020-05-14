//PROGRAMA QUE LEER LAS FICHAS DEL TABLERO
// CODIFICADAS DE LA SIGUIENTE MANERA
// L1 DE PROGRAMA = FICHA O Y ASI SUBIENDO HASTA L3 DE PROGRAMA= FICHA 14
// LUEGO LAS FICHAS DE FUNCIONES EMPIEZAN EN LA 15 Y TERMINAN EN LA 18

#include "Fichas.h"
///////////////////////////////////////////
#define LED_STATUS  15


void setup() {
  Serial.begin(115200);
  pinMode(LED_STATUS, OUTPUT); //Status LED
}
///////////////////////////////////////////
void loop()
{
  //digitalWrite(LED_STATUS, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.print("F0:"); Serial.print(Leerficha(0),BIN); Serial.print(" F1:"); Serial.print(Leerficha(1),BIN);Serial.print(" F2:"); Serial.print(Leerficha(2),BIN);Serial.print(" F3:"); Serial.print(Leerficha(3),BIN);Serial.print(" F4:"); Serial.print(Leerficha(4),BIN);
  Serial.print(" F5:"); Serial.print(Leerficha(5),BIN); Serial.print(" F6:"); Serial.print(Leerficha(6),BIN);Serial.print(" F7:"); Serial.print(Leerficha(7),BIN);Serial.print(" F8:"); Serial.print(Leerficha(8),BIN);Serial.print(" F9:"); Serial.print(Leerficha(9),BIN);
  Serial.print(" F10:"); Serial.print(Leerficha(10),BIN); Serial.print(" F11:"); Serial.print(Leerficha(11),BIN);Serial.print(" F12:"); Serial.print(Leerficha(12),BIN);Serial.print(" F13:"); Serial.print(Leerficha(13),BIN);Serial.print(" F14:"); Serial.print(Leerficha(14),BIN);
  Serial.print(" F15:"); Serial.print(Leerficha(15),BIN); Serial.print(" F16:"); Serial.print(Leerficha(16),BIN);Serial.print(" F17:"); Serial.print(Leerficha(17),BIN);Serial.print(" F18:"); Serial.println(Leerficha(18),BIN);
  delay(500);

}
