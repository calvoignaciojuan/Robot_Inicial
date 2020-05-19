//PROGRAMA test de interrupciones de puertos fichas

#include "Tablero.h"
///////////////////////////////////////////



portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

volatile int cont =0;
volatile int TotalInterrupciones=0;

void IRAM_ATTR F_10_11_12_13() {

  portENTER_CRITICAL_ISR(&mux); //equivalente a desactivar las interrupciones, para que no haya conflictos de accesos a las variables
  
  //digitalWrite(LedIndicador,!digitalRead(LedIndicador));
  cont++; 
  TotalInterrupciones++;
  Leerficha(10);//limpio flag PORTA
  Leerficha(12);//limpio flag PORTB

  portEXIT_CRITICAL_ISR(&mux); 
}

void setup() {

  Serial.begin(115200);
  ConfigTablero();

  digitalWrite(LedIndicador,HIGH);
  
  //write_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,IOCON_B,0x40); // CONFIGURO que INT se active por puertoA o puertoB
  write_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,GPINTEN_A,0xFF); // todo puerto A de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,GPINTEN_B,0xFF); // todo puerto B de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,IOCON_A,0x40); // CONFIGURO que INT se active por puertoA o puertoB   
  
   
  Leerficha(10); //realizo lectura para limpiar la primer interrupcion debido a que cuando no hay ficha los sensores estan en 1(lo considera un cambio de estado)
  Leerficha(12);//limpio flag
  
  delay(100);
  
  attachInterrupt(INT0_0, F_10_11_12_13, FALLING);  //el pin por defecto esta en alto, la interrupcion lo baja
}
///////////////////////////////////////////
void loop()
{
  Serial.print("interrupcion total: "); Serial.println(TotalInterrupciones);
  //Serial.print("Estado Pin: "); Serial.println(digitalRead(INT0_0));
  if(cont>0){
    cont=0;
    Serial.print("interrupcion total: "); Serial.println(TotalInterrupciones);
  }
  delay(1000);

}
