#include "PaP.h"

// -Paso Simple alimenta de a una bobina a la vez
// -Paso Doble de a dos bobinas a la vez
// -Paso mixto hace una y dos
// ->Simple y Doble van a la misma velocidad(rapido), pero doble tiene el doble de torque(y consumo)
// ->Mixto reduce la velocidad a la mitad, aumenta presicion, sube 50% consumo

//int steps_left; //fullStep = 2048 () halfStep = 4096

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

int TipoDePasoUtilizado[4][4];

void PapConfig(){
  //todos los pines involucrados como salidas
  pinMode(MIZQ_IN1, OUTPUT);
  pinMode(MIZQ_IN2, OUTPUT);
  pinMode(MIZQ_IN3, OUTPUT);
  pinMode(MIZQ_IN4, OUTPUT);
  pinMode(MDER_IN1, OUTPUT);
  pinMode(MDER_IN2, OUTPUT);
  pinMode(MDER_IN3, OUTPUT);
  pinMode(MDER_IN4, OUTPUT);

  //paso a utilizar
  memcpy( TipoDePasoUtilizado, Paso_Doble, sizeof(TipoDePasoUtilizado));
}

void PaP_ApagarMotores(){
  //apago ambos motores
  digitalWrite(MIZQ_IN1,0);
  digitalWrite(MIZQ_IN2,0);
  digitalWrite(MIZQ_IN3,0);
  digitalWrite(MIZQ_IN4,0);
  digitalWrite(MDER_IN1,0);
  digitalWrite(MDER_IN2,0);
  digitalWrite(MDER_IN3,0);
  digitalWrite(MDER_IN4,0);
}

void EjecutarPaso(int TipoDePaso[][4],int NumeroPasoMotorIzq,int NumeroPasoMotorDer){            //Avanza un paso
  digitalWrite( MIZQ_IN1, TipoDePaso[NumeroPasoMotorIzq][0]);
  digitalWrite( MIZQ_IN2, TipoDePaso[NumeroPasoMotorIzq][1]);
  digitalWrite( MIZQ_IN3, TipoDePaso[NumeroPasoMotorIzq][2]);
  digitalWrite( MIZQ_IN4, TipoDePaso[NumeroPasoMotorIzq][3]);
  digitalWrite( MDER_IN1, TipoDePaso[NumeroPasoMotorDer][0]);
  digitalWrite( MDER_IN2, TipoDePaso[NumeroPasoMotorDer][1]);
  digitalWrite( MDER_IN3, TipoDePaso[NumeroPasoMotorDer][2]);
  digitalWrite( MDER_IN4, TipoDePaso[NumeroPasoMotorDer][3]);
}

int NextStep(boolean Direction,int StepNumber, int PasosPorVuelta){
  //calculo el siguiente paso de la secuencia
  if(Direction)
    StepNumber++;
  else
    StepNumber--;

  return ((StepNumber + PasosPorVuelta) % PasosPorVuelta);
}

//avanza una vuelta y frena ambos motores PaP
void PaP_Avanzar(){

  boolean DireccionMotorIzq = false; //AVANZA
  boolean DireccionMotorDer = true; //AVANZA
  int NumeroPasoMotorIzq = 0;       // Define el paso actual de la secuencia
  int NumeroPasoMotorDer = 0;
  int PasosPorVuelta=4;             //fullStep = 4 halfStep = 8
  int PasosRestantes=4096;          //fullStep = 2048 () halfStep = 4096 para vuelta completa

  while(PasosRestantes>0)
  {
    EjecutarPaso(TipoDePasoUtilizado,NumeroPasoMotorIzq,NumeroPasoMotorDer) ;     // Avanza un paso
    PasosRestantes--;  // Un paso menos
    NumeroPasoMotorIzq=NextStep(DireccionMotorIzq,NumeroPasoMotorIzq,PasosPorVuelta);
    NumeroPasoMotorDer=NextStep(DireccionMotorDer,NumeroPasoMotorDer,PasosPorVuelta);
    delay (2) ;
  }

  PaP_ApagarMotores();
}

void PaP_Retroceder(){

  boolean DireccionMotorIzq = true; //AVANZA
  boolean DireccionMotorDer = false; //AVANZA
  int NumeroPasoMotorIzq = 0;       // Define el paso actual de la secuencia
  int NumeroPasoMotorDer = 0;
  int PasosPorVuelta=4;             //fullStep = 4 halfStep = 8
  int PasosRestantes=4096;          //fullStep = 2048 () halfStep = 4096 para vuelta completa

  while(PasosRestantes>0)
  {
    EjecutarPaso(TipoDePasoUtilizado,NumeroPasoMotorIzq,NumeroPasoMotorDer) ;     // Avanza un paso
    PasosRestantes--;  // Un paso menos
    NumeroPasoMotorIzq=NextStep(DireccionMotorIzq,NumeroPasoMotorIzq,PasosPorVuelta);
    NumeroPasoMotorDer=NextStep(DireccionMotorDer,NumeroPasoMotorDer,PasosPorVuelta);
    delay (2) ;
  }

  PaP_ApagarMotores();
}

void PaP_GirarIzquierda(){

  boolean DireccionMotorIzq = true; //AVANZA
  boolean DireccionMotorDer = true; //AVANZA
  int NumeroPasoMotorIzq = 0;       // Define el paso actual de la secuencia
  int NumeroPasoMotorDer = 0;
  int PasosPorVuelta=4;             //fullStep = 4 halfStep = 8
  int PasosRestantes=426;          //fullStep = 2048 () halfStep = 4096 para vuelta completa

  while(PasosRestantes>0)
  {
    EjecutarPaso(TipoDePasoUtilizado,NumeroPasoMotorIzq,NumeroPasoMotorDer) ;     // Avanza un paso
    PasosRestantes--;  // Un paso menos
    NumeroPasoMotorIzq=NextStep(DireccionMotorIzq,NumeroPasoMotorIzq,PasosPorVuelta);
    NumeroPasoMotorDer=NextStep(DireccionMotorDer,NumeroPasoMotorDer,PasosPorVuelta);
    delay (2) ;
  }

  PaP_ApagarMotores();
}

void PaP_GirarDerecha(){

  boolean DireccionMotorIzq = false; //AVANZA
  boolean DireccionMotorDer = false; //AVANZA
  int NumeroPasoMotorIzq = 0;       // Define el paso actual de la secuencia
  int NumeroPasoMotorDer = 0;
  int PasosPorVuelta=4;             //fullStep = 4 halfStep = 8
  int PasosRestantes=426;          //fullStep = 2048 () halfStep = 4096 para vuelta completa

  while(PasosRestantes>0)
  {
    EjecutarPaso(TipoDePasoUtilizado,NumeroPasoMotorIzq,NumeroPasoMotorDer) ;     // Avanza un paso
    PasosRestantes--;  // Un paso menos
    NumeroPasoMotorIzq=NextStep(DireccionMotorIzq,NumeroPasoMotorIzq,PasosPorVuelta);
    NumeroPasoMotorDer=NextStep(DireccionMotorDer,NumeroPasoMotorDer,PasosPorVuelta);
    delay (2) ;
  }

  PaP_ApagarMotores();
}
