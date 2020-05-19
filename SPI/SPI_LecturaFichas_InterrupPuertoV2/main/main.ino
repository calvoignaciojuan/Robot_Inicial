//PROGRAMA test de interrupciones de puertos fichas

#include "Tablero.h"
///////////////////////////////////////////



portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

volatile int cont =0;
volatile int TotalInterrupciones=0;

void IRAM_ATTR F_0_1_2_3() {

  portENTER_CRITICAL_ISR(&mux); //equivalente a desactivar las interrupciones, para que no haya conflictos de accesos a las variables
 
  //leo los puertos para bajar los flags de interrupcion y ya que estoy actualizo estado leds
  Leerficha(0)!=0 ? PrenderLed(0):  ApagarLed(0);
  Leerficha(1)!=0 ? PrenderLed(1):  ApagarLed(1);
  Leerficha(2)!=0 ? PrenderLed(2):  ApagarLed(2);
  Leerficha(3)!=0 ? PrenderLed(3):  ApagarLed(3);

  portEXIT_CRITICAL_ISR(&mux); 
}

void IRAM_ATTR F_5_6_7_8() {

  portENTER_CRITICAL_ISR(&mux); //equivalente a desactivar las interrupciones, para que no haya conflictos de accesos a las variables

  //leo los puertos para bajar los flags de interrupcion y ya que estoy actualizo estado leds
  Leerficha(5)!=0 ? PrenderLed(5):  ApagarLed(5);
  Leerficha(6)!=0 ? PrenderLed(6):  ApagarLed(6);
  Leerficha(7)!=0 ? PrenderLed(7):  ApagarLed(7);
  Leerficha(8)!=0 ? PrenderLed(8):  ApagarLed(8);

  portEXIT_CRITICAL_ISR(&mux); 
}

void IRAM_ATTR F_10_11_12_13() {

  portENTER_CRITICAL_ISR(&mux); //equivalente a desactivar las interrupciones, para que no haya conflictos de accesos a las variables

  //leo los puertos para bajar los flags de interrupcion y ya que estoy actualizo estado leds
  Leerficha(10)!=0 ? PrenderLed(10):  ApagarLed(10);
  Leerficha(11)!=0 ? PrenderLed(11):  ApagarLed(11);
  Leerficha(12)!=0 ? PrenderLed(12):  ApagarLed(12);
  Leerficha(13)!=0 ? PrenderLed(13):  ApagarLed(13);

  portEXIT_CRITICAL_ISR(&mux); 
}

void IRAM_ATTR F_15_16_17_18() {

  portENTER_CRITICAL_ISR(&mux); //equivalente a desactivar las interrupciones, para que no haya conflictos de accesos a las variables

  //leo los puertos para bajar los flags de interrupcion y ya que estoy actualizo estado leds
  Leerficha(15)!=0 ? PrenderLed(15):  ApagarLed(15);
  Leerficha(16)!=0 ? PrenderLed(16):  ApagarLed(16);
  Leerficha(17)!=0 ? PrenderLed(17):  ApagarLed(17);
  Leerficha(18)!=0 ? PrenderLed(18):  ApagarLed(18);

  portEXIT_CRITICAL_ISR(&mux); 
}

void IRAM_ATTR F_4_9_14() {

  portENTER_CRITICAL_ISR(&mux); //equivalente a desactivar las interrupciones, para que no haya conflictos de accesos a las variables

  //leo los puertos para bajar los flags de interrupcion y ya que estoy actualizo estado leds
  Leerficha(4)!=0 ? PrenderLed(4):  ApagarLed(4);
  Leerficha(9)!=0 ? PrenderLed(9):  ApagarLed(9);
  Leerficha(14)!=0 ? PrenderLed(14):  ApagarLed(14);

  portEXIT_CRITICAL_ISR(&mux); 
}

void setup() {

  Serial.begin(115200);
  
  ConfigTablero();

  digitalWrite(LedIndicador,HIGH);
  
  //PUERTO EXP 0 CONFIG INTERRUP
  write_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,GPINTEN_A,0xFF); // todo puerto A de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,GPINTEN_B,0xFF); // todo puerto B de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,IOCON_A,0x40); // CONFIGURO que INT se active por puertoA o puertoB   
  Leerficha(10); //realizo lectura para limpiar la primer interrupcion debido a que cuando no hay ficha los sensores estan en 1(lo considera un cambio de estado)
  Leerficha(12);//limpio flag
  attachInterrupt(INT_EXP0, F_10_11_12_13, FALLING);  //el pin por defecto esta en alto, la interrupcion lo baja
  
  //PUERTO EXP 1 CONFIG INTERRUP
  write_expansion_port(nCS_FICHAS_PUERTO1,SPI_PUERTO_1_SENSORES_FUNCIONES_ADDR,GPINTEN_A,0xFF); // todo puerto A de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO1,SPI_PUERTO_1_SENSORES_FUNCIONES_ADDR,GPINTEN_B,0xFF); // todo puerto B de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO1,SPI_PUERTO_1_SENSORES_FUNCIONES_ADDR,IOCON_A,0x40); // CONFIGURO que INT se active por puertoA o puertoB  
  Leerficha(5); //realizo lectura para limpiar la primer interrupcion debido a que cuando no hay ficha los sensores estan en 1(lo considera un cambio de estado)
  Leerficha(7);//limpio flag
  attachInterrupt(INT_EXP1, F_5_6_7_8, FALLING);  //el pin por defecto esta en alto, la interrupcion lo baja

  //PUERTO EXP 2 CONFIG INTERRUP
  write_expansion_port(nCS_FICHAS_PUERTO2,SPI_PUERTO_2_SENSORES_FUNCIONES_ADDR,GPINTEN_A,0xFF); // todo puerto A de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO2,SPI_PUERTO_2_SENSORES_FUNCIONES_ADDR,GPINTEN_B,0xFF); // todo puerto B de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO2,SPI_PUERTO_2_SENSORES_FUNCIONES_ADDR,IOCON_A,0x40); // CONFIGURO que INT se active por puertoA o puertoB  
  Leerficha(0); //realizo lectura para limpiar la primer interrupcion debido a que cuando no hay ficha los sensores estan en 1(lo considera un cambio de estado)
  Leerficha(2);//limpio flag
  attachInterrupt(INT_EXP2, F_0_1_2_3, FALLING);  //el pin por defecto esta en alto, la interrupcion lo baja

  //PUERTO EXP 3 CONFIG INTERRUP
  write_expansion_port(nCS_FICHAS_PUERTO3,SPI_PUERTO_3_SENSORES_FUNCIONES_ADDR,GPINTEN_A,0xFF); // todo puerto A de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO3,SPI_PUERTO_3_SENSORES_FUNCIONES_ADDR,GPINTEN_B,0xFF); // todo puerto B de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO3,SPI_PUERTO_3_SENSORES_FUNCIONES_ADDR,IOCON_A,0x40); // CONFIGURO que INT se active por puertoA o puertoB  
  Leerficha(4); //realizo lectura para limpiar la primer interrupcion debido a que cuando no hay ficha los sensores estan en 1(lo considera un cambio de estado)
  Leerficha(14);//limpio flag
  attachInterrupt(INT_EXP3, F_4_9_14, FALLING);  //el pin por defecto esta en alto, la interrupcion lo baja

  //PUERTO EXP 4 CONFIG INTERRUP
  write_expansion_port(nCS_FICHAS_PUERTO4,SPI_PUERTO_4_SENSORES_FUNCIONES_ADDR,GPINTEN_A,0xFF); // todo puerto A de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO4,SPI_PUERTO_4_SENSORES_FUNCIONES_ADDR,GPINTEN_B,0xFF); // todo puerto B de expansor 0 habilito interrupcion al cambiar de estado
  write_expansion_port(nCS_FICHAS_PUERTO4,SPI_PUERTO_4_SENSORES_FUNCIONES_ADDR,IOCON_A,0x40); // CONFIGURO que INT se active por puertoA o puertoB  
  Leerficha(15); //realizo lectura para limpiar la primer interrupcion debido a que cuando no hay ficha los sensores estan en 1(lo considera un cambio de estado)
  Leerficha(17);//limpio flag
  attachInterrupt(INT_EXP4, F_15_16_17_18, FALLING);  //el pin por defecto esta en alto, la interrupcion lo baja
    
}
///////////////////////////////////////////
void loop()
{
  Serial.print("F0: ");Serial.print(Leerficha(0),BIN); Serial.print(" F1: ");Serial.println(Leerficha(1),BIN);
  delay(1000);

}
