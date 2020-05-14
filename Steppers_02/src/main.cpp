// Test prueba de los dos motores PaP en sus 3 diferentes formas de movimiento

// -Paso Simple alimenta de a una bobina a la vez
// -Paso Doble de a dos bobinas a la vez
// -Paso mixto hace una y dos
// ->Simple y Doble van a la misma velocidad(rapido), pero doble tiene el doble de torque(y consumo)
// ->Mixto reduce la velocidad a la mitad, aumenta presicion, sube 50% consumo

#include "PaP.h"

int PinBuzz = 23;
int PinLed = 15;

void setup() {

  //inicializo zumbador apagado
  pinMode(PinBuzz, OUTPUT);
  digitalWrite(PinBuzz,LOW);

  //prendo led testigo de encendido
  pinMode(PinLed, OUTPUT);
  digitalWrite(PinLed,LOW);

  PapConfig();

}

void loop(){

  PaP_Avanzar();

  delay(2000);

}
