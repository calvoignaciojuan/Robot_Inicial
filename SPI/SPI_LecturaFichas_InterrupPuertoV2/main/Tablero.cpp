
#include "Tablero.h"

SPIClass * SPI_GENERAL = new SPIClass(HSPI);; //creo la clase general de SPI

byte EstadoLedsPuertoProgramasA = 0x00;
byte EstadoLedsPuertoProgramasB = 0x00;
byte EstadoLedsPuertoFuncionesA = 0x00;

void ConfigTablero(){

  pinMode(LedIndicador,OUTPUT);
  digitalWrite(LedIndicador,LOW); //APAGADO
  
  //Pines botones como entradas
  pinMode(PinBotonProg0,INPUT);
  pinMode(PinBotonProg1,INPUT);
  pinMode(PinBotonProg2,INPUT);
  pinMode(PinBotonFuncion,INPUT);  

  //Chip Enables como salidas y HIGH(deshabilitadas)
  pinMode(nCS_LEDS_FUNCIONES,OUTPUT);
  pinMode(nCS_LEDS_PROGRAMAS,OUTPUT);
  pinMode(nCS_FICHAS_PUERTO0,OUTPUT);
  pinMode(nCS_FICHAS_PUERTO1,OUTPUT);
  pinMode(nCS_FICHAS_PUERTO2,OUTPUT);
  pinMode(nCS_FICHAS_PUERTO3,OUTPUT);
  pinMode(nCS_FICHAS_PUERTO4,OUTPUT);  
  digitalWrite(nCS_LEDS_FUNCIONES,HIGH);
  digitalWrite(nCS_LEDS_PROGRAMAS,HIGH);
  digitalWrite(nCS_FICHAS_PUERTO0,HIGH);
  digitalWrite(nCS_FICHAS_PUERTO1,HIGH);
  digitalWrite(nCS_FICHAS_PUERTO2,HIGH);
  digitalWrite(nCS_FICHAS_PUERTO3,HIGH);
  digitalWrite(nCS_FICHAS_PUERTO4,HIGH);

  //Pines de interrupcion como entradas
  pinMode(INT_EXP0,INPUT);
  pinMode(INT_EXP1,INPUT);
  pinMode(INT_EXP2,INPUT);
  pinMode(INT_EXP3,INPUT);
  pinMode(INT_EXP4,INPUT);
  
  config_sensors_ports();
  config_leds_Ports();
}

void config_sensors_ports(){ //configuro puertos como entrada
  
  //puertos de fichas como entradas  
  write_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,IODIR_A_ADDR,IO_INPUTS); //PuertoExpan 0 - Puerto A
  write_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,IODIR_B_ADDR,IO_INPUTS); //PuertoExpan 0 - Puerto B
  
  write_expansion_port(nCS_FICHAS_PUERTO1,SPI_PUERTO_1_SENSORES_FUNCIONES_ADDR,IODIR_A_ADDR,IO_INPUTS); //PuertoExpan 1 - Puerto A
  write_expansion_port(nCS_FICHAS_PUERTO1,SPI_PUERTO_1_SENSORES_FUNCIONES_ADDR,IODIR_B_ADDR,IO_INPUTS); //PuertoExpan 1 - Puerto B
  
  write_expansion_port(nCS_FICHAS_PUERTO2,SPI_PUERTO_2_SENSORES_FUNCIONES_ADDR,IODIR_A_ADDR,IO_INPUTS); //PuertoExpan 2 - Puerto A
  write_expansion_port(nCS_FICHAS_PUERTO2,SPI_PUERTO_2_SENSORES_FUNCIONES_ADDR,IODIR_B_ADDR,IO_INPUTS); //PuertoExpan 2 - Puerto B
  
  write_expansion_port(nCS_FICHAS_PUERTO3,SPI_PUERTO_3_SENSORES_FUNCIONES_ADDR,IODIR_A_ADDR,IO_INPUTS); //PuertoExpan 3 - Puerto A
  write_expansion_port(nCS_FICHAS_PUERTO3,SPI_PUERTO_3_SENSORES_FUNCIONES_ADDR,IODIR_B_ADDR,IO_INPUTS); //PuertoExpan 3 - Puerto B
  
  write_expansion_port(nCS_FICHAS_PUERTO4,SPI_PUERTO_4_SENSORES_FUNCIONES_ADDR,IODIR_A_ADDR,IO_INPUTS); //PuertoExpan 4 - Puerto A
  write_expansion_port(nCS_FICHAS_PUERTO4,SPI_PUERTO_4_SENSORES_FUNCIONES_ADDR,IODIR_B_ADDR,IO_INPUTS); //PuertoExpan 4 - Puerto B
}


byte Leerficha(int  Numficha){
  
  switch (Numficha) {
  case Ficha10:
    return (~read_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,GPIO_A_ADDR) & B00001111);
    break;
  case Ficha11:
    return (~read_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,GPIO_A_ADDR) & B11110000)>>4;
    break;
  case Ficha12:
    return (~read_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,GPIO_B_ADDR) & B00001111);
    break;
  case Ficha13:
    return (~read_expansion_port(nCS_FICHAS_PUERTO0,SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR,GPIO_B_ADDR) & B11110000)>>4;
    break;
  case Ficha14:
    return (~read_expansion_port(nCS_FICHAS_PUERTO3,SPI_PUERTO_3_SENSORES_FUNCIONES_ADDR,GPIO_A_ADDR) & B00001111);
    break;
  case Ficha5:
    return (~read_expansion_port(nCS_FICHAS_PUERTO1,SPI_PUERTO_1_SENSORES_FUNCIONES_ADDR,GPIO_A_ADDR) & B00001111);
    break;
  case Ficha6:
    return (~read_expansion_port(nCS_FICHAS_PUERTO1,SPI_PUERTO_1_SENSORES_FUNCIONES_ADDR,GPIO_A_ADDR) & B11110000)>>4;
    break;
  case Ficha7:
    return (~read_expansion_port(nCS_FICHAS_PUERTO1,SPI_PUERTO_1_SENSORES_FUNCIONES_ADDR,GPIO_B_ADDR) & B00001111);
    break;
  case Ficha8:
    return (~read_expansion_port(nCS_FICHAS_PUERTO1,SPI_PUERTO_1_SENSORES_FUNCIONES_ADDR,GPIO_B_ADDR) & B11110000)>>4;
    break;
  case Ficha9:
    return (~read_expansion_port(nCS_FICHAS_PUERTO3,SPI_PUERTO_3_SENSORES_FUNCIONES_ADDR,GPIO_A_ADDR) & B11110000)>>4;
    break;
  case Ficha0:
    return (~read_expansion_port(nCS_FICHAS_PUERTO2,SPI_PUERTO_2_SENSORES_FUNCIONES_ADDR,GPIO_A_ADDR) & B00001111);
    break;
  case Ficha1:
    return (~read_expansion_port(nCS_FICHAS_PUERTO2,SPI_PUERTO_2_SENSORES_FUNCIONES_ADDR,GPIO_A_ADDR) & B11110000)>>4;
    break;
  case Ficha2:
    return (~read_expansion_port(nCS_FICHAS_PUERTO2,SPI_PUERTO_2_SENSORES_FUNCIONES_ADDR,GPIO_B_ADDR) & B00001111);
    break;
  case Ficha3:
    return (~read_expansion_port(nCS_FICHAS_PUERTO2,SPI_PUERTO_2_SENSORES_FUNCIONES_ADDR,GPIO_B_ADDR) & B11110000)>>4;
    break;
  case Ficha4:
    return (~read_expansion_port(nCS_FICHAS_PUERTO3,SPI_PUERTO_3_SENSORES_FUNCIONES_ADDR,GPIO_B_ADDR) & B00001111);
    break;
  case Ficha15:
    return (~read_expansion_port(nCS_FICHAS_PUERTO4,SPI_PUERTO_4_SENSORES_FUNCIONES_ADDR,GPIO_A_ADDR) & B00000111);
    break;
  case Ficha16:
    return (~read_expansion_port(nCS_FICHAS_PUERTO4,SPI_PUERTO_4_SENSORES_FUNCIONES_ADDR,GPIO_A_ADDR) & B00111000)>>3;
    break;
  case Ficha17:
    return (~read_expansion_port(nCS_FICHAS_PUERTO4,SPI_PUERTO_4_SENSORES_FUNCIONES_ADDR,GPIO_B_ADDR) & B00001110)>>1;
    break;
  case Ficha18:
    return ((~read_expansion_port(nCS_FICHAS_PUERTO4,SPI_PUERTO_4_SENSORES_FUNCIONES_ADDR,GPIO_A_ADDR) & B11000000)>>6) | ((~read_expansion_port(nCS_FICHAS_PUERTO4,SPI_PUERTO_4_SENSORES_FUNCIONES_ADDR,GPIO_B_ADDR) & B00000001)<<2);
    break;

  default:
    return 0;
    break;
  }
}

//Envia dato a un registro de un chip determinado por el chipAddress
void write_expansion_port(byte nCs_pin,byte chip_address,byte reg_address,byte data){

    delay(10);
    digitalWrite(nCs_pin, LOW);
    SPI_GENERAL->begin(SCLK, MISO, MOSI, nCs_pin);
    SPI_GENERAL->beginTransaction( SPISettings(spiClk, MSBFIRST, SPI_MODE1) ); //Chequear MODE, MSB, FREQ
    SPI_GENERAL->transfer(BASEADDR_MCP23S17 | (chip_address<<1) | CMD_WR); //Envia datos
    SPI_GENERAL->transfer(reg_address); //Envia datos
    SPI_GENERAL->transfer(data); //Envia datos
    digitalWrite(nCs_pin, HIGH); //Chip disable
    SPI_GENERAL->endTransaction(); //Libera puerto SPI
}

byte read_expansion_port(byte nCs_pin,byte chip_address,byte reg_address){

    uint8_t data_in0=0;
    uint8_t data_in1=0;
    uint8_t result=0;

    delay(10);
    digitalWrite(nCs_pin, LOW);
    SPI_GENERAL->begin(SCLK, MISO, MOSI, nCs_pin);
    SPI_GENERAL->beginTransaction( SPISettings(spiClk, MSBFIRST, SPI_MODE1) ); //Chequear MODE, MSB, FREQ
    SPI_GENERAL->transfer((BASEADDR_MCP23S17 | (chip_address<<1) | CMD_RD)); //Envia datos
    data_in0=SPI_GENERAL->transfer(reg_address); //Envia datos
    data_in1=SPI_GENERAL->transfer(0x00); //Lee datos
    digitalWrite(nCs_pin, HIGH); //Chip disable
    SPI_GENERAL->endTransaction(); //Libera puerto SPI
    result=((data_in0 & B00000001)<<7) | ((data_in1 & B11111110)>>1);
    return result;
}

/////////////////////////// LEDS /////////////////////////////////////////////////////

//Configura a los dos puertos de expansion como salida para controlar los 19 leds
void config_leds_Ports(){

  //primero las 5 leds de funciones que estan en el puertoA del integrado ADDRESS
  write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,IODIR_A_ADDR,IO_OUTPUTS);
  //segundo puerto A del integrado ADDRESS 5 (los 15 leds de programas)
  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,IODIR_A_ADDR,IO_OUTPUTS);
  //TERCERO puerto B del integrado ADDRESS 5 (los 15 leds de programas)
  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,IODIR_B_ADDR,IO_OUTPUTS);

  //INICIALIZO TODOS LOS LEDS APAGADOS
  ApagarLedsTablero();
}

void PrenderLed(int  NumFicha){
  
  switch (NumFicha) {

    case Ficha0:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB | B00000100;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha1:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB | B00001000;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha2:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB | B00010000;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha3:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB | B00100000;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha4:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB | B01000000;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha5:
    
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA | B00100000;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha6:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA | B01000000;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha7:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA | B10000000;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha8:
    
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB | B00000001;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha9:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB | B00000010;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha10:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA | B00000001;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha11:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA | B00000010;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha12:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA | B00000100;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha13:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA | B00001000;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha14:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA | B00010000;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;  
    case Ficha15:
  
      EstadoLedsPuertoFuncionesA= EstadoLedsPuertoFuncionesA | B00000001;
      write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,EstadoLedsPuertoFuncionesA);
      break; 
    case Ficha16:
  
      EstadoLedsPuertoFuncionesA= EstadoLedsPuertoFuncionesA | B00000010;
      write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,EstadoLedsPuertoFuncionesA);
      break;
    case Ficha17:
  
      EstadoLedsPuertoFuncionesA= EstadoLedsPuertoFuncionesA | B00000100;
      write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,EstadoLedsPuertoFuncionesA);
      break;
    case Ficha18:
  
      EstadoLedsPuertoFuncionesA= EstadoLedsPuertoFuncionesA | B00001000;
      write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,EstadoLedsPuertoFuncionesA);
      break;
  
    default:
      break;
  }
}

void ApagarLed(int  NumFicha){
  
  switch (NumFicha) {

    case Ficha0:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB & B11111011;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha1:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB & B11110111;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha2:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB & B11101111;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha3:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB & B11011111;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha4:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB & B10111111;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha5:
    
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA & B11011111;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha6:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA & B10111111;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha7:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA & B01111111;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha8:
    
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB & B11111110;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha9:
  
      EstadoLedsPuertoProgramasB= EstadoLedsPuertoProgramasB & B11111101;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,EstadoLedsPuertoProgramasB);
      break;
    case Ficha10:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA & B11111110;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha11:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA & 11111101;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha12:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA & B11111011;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha13:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA & B11110111;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;
    case Ficha14:
  
      EstadoLedsPuertoProgramasA= EstadoLedsPuertoProgramasA & B11101111;
      write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,EstadoLedsPuertoProgramasA);
      break;  
    case Ficha15:
  
      EstadoLedsPuertoFuncionesA= EstadoLedsPuertoFuncionesA & B11111110;
      write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,EstadoLedsPuertoFuncionesA);
      break; 
    case Ficha16:
  
      EstadoLedsPuertoFuncionesA= EstadoLedsPuertoFuncionesA & B11111101;
      write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,EstadoLedsPuertoFuncionesA);
      break;
    case Ficha17:
  
      EstadoLedsPuertoFuncionesA= EstadoLedsPuertoFuncionesA & B11111011;
      write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,EstadoLedsPuertoFuncionesA);
      break;
    case Ficha18:
  
      EstadoLedsPuertoFuncionesA= EstadoLedsPuertoFuncionesA & B11110111;
      write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,EstadoLedsPuertoFuncionesA);
      break;
  
    default:
      break;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////   FUNCIONES PARA TESTING     ///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////


//funcion test para mostrar todas las fichas del tablero
void TestLeerYMotrarFichas(){

  Serial.print("F0: ");Serial.print(Leerficha(0));
  Serial.print(" F1: ");Serial.print(Leerficha(1));
  Serial.print(" F2: ");Serial.print(Leerficha(2));
  Serial.print(" F3: ");Serial.print(Leerficha(3));
  Serial.print(" F4: ");Serial.print(Leerficha(4));
  Serial.print(" F5: ");Serial.print(Leerficha(5));
  Serial.print(" F6: ");Serial.print(Leerficha(6));
  Serial.print(" F7: ");Serial.print(Leerficha(7));
  Serial.print(" F8: ");Serial.print(Leerficha(8));
  Serial.print(" F9: ");Serial.print(Leerficha(9));
  Serial.print(" F10: ");Serial.print(Leerficha(10));
  Serial.print(" F11: ");Serial.print(Leerficha(11));
  Serial.print(" F12: ");Serial.print(Leerficha(12));
  Serial.print(" F13: ");Serial.print(Leerficha(13));
  Serial.print(" F14: ");Serial.print(Leerficha(14));
  Serial.print(" F15: ");Serial.print(Leerficha(15));
  Serial.print(" F16: ");Serial.print(Leerficha(16));
  Serial.print(" F17: ");Serial.print(Leerficha(17));
  Serial.print(" F18: ");Serial.print(Leerficha(18));
  Serial.println("");
  
}

void ApagarLedsTablero(){

  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,0x00);
  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,0x00);
  write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,0x00);  
  
  EstadoLedsPuertoProgramasA = 0x00;
  EstadoLedsPuertoProgramasB = 0x00;
  EstadoLedsPuertoFuncionesA = 0x00; 
}

void PrenderLedsTablero(){

  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,0xFF);
  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,0xFF);
  write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,0xFF);  

  EstadoLedsPuertoProgramasA = 0xFF;
  EstadoLedsPuertoProgramasB = 0xFF;
  EstadoLedsPuertoFuncionesA = 0xFF; 
}

void TestingLeds(){

   ApagarLedsTablero(); PrenderLed(0); delay(200);  ApagarLedsTablero(); PrenderLed(1); delay(200);  ApagarLedsTablero(); PrenderLed(2); delay(200);
   ApagarLedsTablero(); PrenderLed(3); delay(200);  ApagarLedsTablero(); PrenderLed(4); delay(200);  ApagarLedsTablero(); PrenderLed(5); delay(200);
   ApagarLedsTablero(); PrenderLed(6); delay(200);  ApagarLedsTablero(); PrenderLed(7); delay(200);  ApagarLedsTablero(); PrenderLed(8); delay(200);
   ApagarLedsTablero(); PrenderLed(9); delay(200);  ApagarLedsTablero(); PrenderLed(10);delay(200);  ApagarLedsTablero(); PrenderLed(11);delay(200);
   ApagarLedsTablero(); PrenderLed(12);delay(200);  ApagarLedsTablero(); PrenderLed(13);delay(200);  ApagarLedsTablero(); PrenderLed(14);delay(200);
   ApagarLedsTablero(); PrenderLed(15);delay(200);  ApagarLedsTablero(); PrenderLed(16);delay(200);  ApagarLedsTablero(); PrenderLed(17);delay(200);
   ApagarLedsTablero(); PrenderLed(18);delay(200);
   
   ApagarLedsTablero();   
   delay(500);

   PrenderLed(0); delay(200); PrenderLed(1); delay(200); PrenderLed(2); delay(200); PrenderLed(3); delay(200); PrenderLed(4); delay(200); 
   PrenderLed(5); delay(200); PrenderLed(6); delay(200); PrenderLed(7); delay(200); PrenderLed(8); delay(200); PrenderLed(9); delay(200);
   PrenderLed(10); delay(200); PrenderLed(11); delay(200);PrenderLed(12); delay(200); PrenderLed(13); delay(200); PrenderLed(14); delay(200); 
   PrenderLed(15); delay(200); PrenderLed(16); delay(200); PrenderLed(17); delay(200); PrenderLed(18); delay(200);

   ApagarLedsTablero();  delay(500);   
   PrenderLedsTablero(); delay(500);
   ApagarLedsTablero();  delay(500);
   PrenderLedsTablero(); delay(500);
   ApagarLedsTablero();
   
}
