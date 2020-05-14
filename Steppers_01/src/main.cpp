// Programa para testear motor Paso a Paso en sus 3 velocidad
// -Paso Simple alimenta de a una bobina a la vez
// -Paso Doble de a dos bobinas a la vez
// -Paso mixto hace una y dos
// ->Simple y Doble van a la misma velocidad(rapido), pero doble tiene el doble de torque(y consumo)
// ->Mixto reduce la velocidad a la mitad, aumenta presicion, sube 50% consumo

#include <Arduino.h>

#define MIZQ_IN1  33
#define MIZQ_IN2  25
#define MIZQ_IN3  26
#define MIZQ_IN4  27

int steps_left; //fullStep = 2048 () halfStep = 4096
boolean Direction = true;
int Step_Number = 0;                       // Define el paso actual de la secuencia
int PasosPorVuelta;   //fullStep = 4 halfStep = 8

// de a una bobina
int Paso_Simple [ 4 ][ 4 ] =
{    {1, 0, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 1, 0},
     {0, 0, 0, 1}
};

//de a dos bobinas a la vez
int Paso_Doble [ 4 ][ 4 ] =
{    {1, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 1, 1},
     {1, 0, 0, 1}
 };

// una bobina, dos bobinas y asi, mas suave el movimiento, consumo alternado
int Paso_Mixto [ 8 ][ 4 ] =
{    {1, 0, 0, 0},
     {1, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 1, 1},
     {0, 0, 0, 1},
     {1, 0, 0, 1}
};

// DECLARACION DE FUNCIONES
void stepper(int TipoDePaso[][4]);
void SetDirection();
void ApagarMotorIzq();

void setup() {
  pinMode(MIZQ_IN1, OUTPUT);
  pinMode(MIZQ_IN2, OUTPUT);
  pinMode(MIZQ_IN3, OUTPUT);
  pinMode(MIZQ_IN4, OUTPUT);
}

void loop(){

//paso simple
  PasosPorVuelta=4;
  steps_left=2048;
  while(steps_left>0)
  {
    stepper(Paso_Simple) ;     // Avanza un paso
    steps_left-- ;  // Un paso menos
    delay (4) ;
  }
  ApagarMotorIzq();
  delay(2000);
  //Direction =! Direction;  // Invertimos la direceccion de giro


//paso doble
  PasosPorVuelta=4;
  steps_left=2048;
  while(steps_left>0)
  {
    stepper(Paso_Doble) ;     // Avanza un paso
    steps_left-- ;  // Un paso menos
    delay (4) ;
  }
  ApagarMotorIzq();
  delay(2000);
  //Direction =! Direction;  // Invertimos la direceccion de giro

//paso Paso_Mixto
  PasosPorVuelta=8;
  steps_left=4096;
  while(steps_left>0)
  {
    stepper(Paso_Mixto) ;     // Avanza un paso
    steps_left-- ;  // Un paso menos
    delay (4) ;
  }
  ApagarMotorIzq();
  delay(2000);
  //Direction =! Direction;  // Invertimos la direceccion de giro
}

void stepper(int TipoDePaso[][4]){            //Avanza un paso
  digitalWrite( MIZQ_IN1, TipoDePaso[Step_Number][ 0] );
  digitalWrite( MIZQ_IN2, TipoDePaso[Step_Number][ 1] );
  digitalWrite( MIZQ_IN3, TipoDePaso[Step_Number][ 2] );
  digitalWrite( MIZQ_IN4, TipoDePaso[Step_Number][ 3] );

  SetDirection();
}

void SetDirection(){
  if(Direction)
    Step_Number++;
  else
    Step_Number--;

  Step_Number = ( Step_Number + PasosPorVuelta ) % PasosPorVuelta ;
}

void ApagarMotorIzq(){
  //apago el motor
  digitalWrite( MIZQ_IN1, 0 );
  digitalWrite( MIZQ_IN2, 0 );
  digitalWrite( MIZQ_IN3, 0 );
  digitalWrite( MIZQ_IN4, 0 );
}
