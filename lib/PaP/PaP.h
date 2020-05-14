#ifndef PaP
#define PaP

#include <Arduino.h>

#define MIZQ_IN1  33
#define MIZQ_IN2  25
#define MIZQ_IN3  26
#define MIZQ_IN4  27
#define MDER_IN1  19
#define MDER_IN2  18
#define MDER_IN3  5
#define MDER_IN4  17

// DECLARACION DE FUNCIONES
void PapConfig();

void EjecutarPaso(int TipoDePaso[][4],int NumeroPasoMotorIzq,int NumeroPasoMotorDer);
int NextStep(boolean Direction,int StepNumber, int PasosPorVuelta);
void PaP_Avanzar();
void PaP_Retroceder();
void PaP_GirarIzquierda();
void PaP_GirarDerecha();
void PaP_ApagarMotores();

#endif
