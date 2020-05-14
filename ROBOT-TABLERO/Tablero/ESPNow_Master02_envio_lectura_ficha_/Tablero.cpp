
#include "Tablero.h"

SPIClass * SPI_GENERAL = new SPIClass(HSPI);; //creo la clase general de SPI

void ConfigTablero(){

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

  config_leds_Ports();
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

void config_sensors_ports(byte CsPuerto,byte chip_address,byte reg_address){ //configuro puerto como entrada
  
  write_expansion_port(CsPuerto,chip_address,reg_address,IO_INPUTS);
}

byte read_expansion_port(byte nCs_pin,byte chip_address,byte reg_address){

    uint8_t data_in0=0;
    uint8_t data_in1=0;
    uint8_t result=0;

    //configuro como entradas los puertos del puerto de expansion
    config_sensors_ports(nCs_pin,chip_address,reg_address);

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

  //INICIALIZO TODOS LOS LEDS EN APAGADOS
  write_expansion_port(nCS_LEDS_FUNCIONES, SPI_LED_FUNCIONES_ADDR , GPIO_A_ADDR, 0X00);
  write_expansion_port(nCS_LEDS_PROGRAMAS, SPI_LED_PROGRAMAS_ADDR, GPIO_A_ADDR, 0X00);
  write_expansion_port(nCS_LEDS_PROGRAMAS, SPI_LED_PROGRAMAS_ADDR, GPIO_B_ADDR, 0X00);
}

void PrenderLed(int  NumFicha){
  
  switch (NumFicha) {

  case Ficha0:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,B00000100);
    break;
  case Ficha1:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,B00001000);
    break;
  case Ficha2:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,B00010000);
    break;
  case Ficha3:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,B00100000);
    break;
  case Ficha4:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,B01000000);
    break;
  case Ficha5:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B00100000);
    break;
  case Ficha6:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B01000000);
    break;
  case Ficha7:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B10000000);
    break;
  case Ficha8:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,B00000001);
    break;
  case Ficha9:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,B00000010);
    break;
  case Ficha10:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B00000001);
    break;
  case Ficha11:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B00000010);
    break;
  case Ficha12:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B00000100);
    break;
  case Ficha13:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B00001000);
    break;
  case Ficha14:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B00010000);
    break;  
  case Ficha15:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B00000001);
    break; 
  case Ficha16:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B00000010);
    break;
  case Ficha17:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B00000100);
    break;
  case Ficha18:
    config_leds_Ports();
    write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,B00001000);
    break;

  default:
    break;
  }
}

void TestingLeds(){
  
   PrenderLed(0);
   delay(200);
   PrenderLed(1);
   delay(200);
   PrenderLed(2);
   delay(200);
   PrenderLed(3);
   delay(200);
   PrenderLed(4);
   delay(200);
   PrenderLed(5);
   delay(200);
   PrenderLed(6);
   delay(200);
   PrenderLed(7);
   delay(200);
   PrenderLed(8);
   delay(200);
   PrenderLed(9);
   delay(200);
   PrenderLed(10);
   delay(200);
   PrenderLed(11);
   delay(200);
   PrenderLed(12);
   delay(200);
   PrenderLed(13);
   delay(200);
   PrenderLed(14);
   delay(200);
   PrenderLed(15);
   delay(200);
   PrenderLed(16);
   delay(200);
   PrenderLed(17);
   delay(200);
   PrenderLed(18);
   delay(200);

    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,0x00);
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,0x00);
    write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,0x00);
    delay(500);
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,0xFF);
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,0xFF);
    write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,0xFF);
    delay(500);
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,0x00);
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,0x00);
    write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,0x00);
    delay(500);
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,0xFF);
    write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,0xFF);
    write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,0xFF);
    delay(500);
   
}
