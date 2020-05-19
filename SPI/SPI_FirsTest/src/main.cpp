#include <Arduino.h>
#include <SPI.h>
///////////////////////////////////////////
#define LED_STATUS  15
///////////////////////////////////////////
// SPI
#define SCLK  14 // Pin Clock SPI
#define MISO 12 //Pin MISO
#define MOSI 13 // Pin MOSI
///////////////////////////////////////////
//MCP23S17 LEDS
#define nCS_LEDS_FUNCIONES 32
#define nCS_LEDS_PROGRAMAS 27
#define BASEADDR_MCP23S17  0x40  //Address general del IC
#define SPI_LED_PROGRAMAS_ADDR 0x05 // Address configurada por HW
#define SPI_LED_FUNCIONES_ADDR 0x06 // Address configurada por HW
#define CMD_WR  0x00 //Bit write
#define CMD_RD  0x01 //Bit read
#define IODIR_A_ADDR  0x00  //Direccion del registro IODIR A (para configurar si es salida o entrada)
#define IODIR_B_ADDR  0x01  //Direccion del registro IODIR B (para configurar si es salida o entrada)
#define GPIO_A_ADDR  0x12  //Direccion del registro GPIO A
#define GPIO_B_ADDR  0x13  //Direccion del registro GPIO B
#define IO_OUTPUTS 0x00   //Valor para configurar IO como salida.
///////////////////////////////////////////
static const int spiClk = 1000000; // 1 MHz
SPIClass * SPI_GENERAL = NULL; //Leds programa

void write_expansion_port(byte nCs_pin,byte chip_address,byte reg_address,byte data){

    delay(100);
    byte b;   //Auxiliar
    SPI_GENERAL->begin(SCLK, MISO, MOSI, nCs_pin);
    SPI_GENERAL->beginTransaction( SPISettings(spiClk, MSBFIRST, SPI_MODE1) ); //Chequear MODE, MSB, FREQ
    digitalWrite(nCs_pin, LOW);
    b = (BASEADDR_MCP23S17 | (chip_address<<1) | CMD_WR);
    SPI_GENERAL->transfer(b); //Envia datos
    b = reg_address;  //Address GPIO config
    SPI_GENERAL->transfer(b); //Envia datos
    b = data; //Valor de configuracion
    SPI_GENERAL->transfer(b); //Envia datos
    digitalWrite(nCs_pin, HIGH); //Chip disable
    SPI_GENERAL->endTransaction(); //Libera puerto SPI

}

//Configura a los dos puertos de expansion como salida para controlar los 19 leds
void config_leds_salidas(){

  SPI_GENERAL = new SPIClass(HSPI); //clase general para la comunicacion SPI (sensores y leds)
  pinMode(nCS_LEDS_FUNCIONES, OUTPUT); //nCS_LEDS_FUNCIONES como salida
  pinMode(nCS_LEDS_PROGRAMAS, OUTPUT); //nCS_LEDS_FUNCIONES como salida
  delay(2);
  //primero las 5 leds de funciones que estan en el puertoA del integrado ADDRESS
  write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,IODIR_A_ADDR,IO_OUTPUTS);
  //segundo puerto A del integrado ADDRESS 5 (los 15 leds de programas)
  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,IODIR_A_ADDR,IO_OUTPUTS);
  //TERCERO puerto B del integrado ADDRESS 5 (los 15 leds de programas)
  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,IODIR_B_ADDR,IO_OUTPUTS);

  //INICIALIZO TODOS LOS LEDS EN APAGADOS
  write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,0X00);

  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,0X00);

  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,0X00);

}

void setup() {
  delay(100);
  pinMode(LED_STATUS, OUTPUT); //Status LED
  config_leds_salidas();
  config_leds_salidas();
}
///////////////////////////////////////////
void loop()
{

  digitalWrite(LED_STATUS, HIGH);   // turn the LED on (HIGH is the voltage level)
  write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,0xFF);
  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,0xFF);
  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,0xFF);
  delay(500);

  digitalWrite(LED_STATUS, LOW);    // turn the LED off by making the voltage LOW
  write_expansion_port(nCS_LEDS_FUNCIONES,SPI_LED_FUNCIONES_ADDR,GPIO_A_ADDR,0x00);
  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_A_ADDR,0x00);
  write_expansion_port(nCS_LEDS_PROGRAMAS,SPI_LED_PROGRAMAS_ADDR,GPIO_B_ADDR,0x00);
  delay(500);
}
