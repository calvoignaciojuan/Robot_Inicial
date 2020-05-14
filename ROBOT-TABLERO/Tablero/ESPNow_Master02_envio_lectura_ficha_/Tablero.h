#ifndef TABLERO
#define TABLERO

#include <Arduino.h>
#include <SPI.h>

///////////////////////////////////////////
//                 SPI
///////////////////////////////////////////
static const int spiClk = 1000000; // 1 MHz
#define SCLK 14 // Pin Clock SPI
#define MISO 12 //Pin MISO
#define MOSI 13 // Pin MOSI

///////////////////////////////////////////
//           MCP23S17 PUERTOS
////////////////////////////////////////// 
#define nCS_LEDS_FUNCIONES 32
#define nCS_LEDS_PROGRAMAS 27
#define nCS_FICHAS_PUERTO0 21
#define nCS_FICHAS_PUERTO1 22
#define nCS_FICHAS_PUERTO2 23
#define nCS_FICHAS_PUERTO3 25
#define nCS_FICHAS_PUERTO4 26

#define BASEADDR_MCP23S17  0x40  //Address general del IC
#define SPI_PUERTO_0_SENSORES_FUNCIONES_ADDR 0x00
#define SPI_PUERTO_1_SENSORES_FUNCIONES_ADDR 0x01
#define SPI_PUERTO_2_SENSORES_FUNCIONES_ADDR 0x02
#define SPI_PUERTO_3_SENSORES_FUNCIONES_ADDR 0x03
#define SPI_PUERTO_4_SENSORES_FUNCIONES_ADDR 0x04
#define SPI_LED_PROGRAMAS_ADDR 0x05 // Address configurada por HW
#define SPI_LED_FUNCIONES_ADDR 0x06 // Address configurada por HW

#define CMD_WR  0x00 //Bit write
#define CMD_RD  0x01 //Bit read

#define IODIR_A_ADDR  0x00  //Direccion del registro IODIR A (para configurar si es salida o entrada)
#define IODIR_B_ADDR  0x01  //Direccion del registro IODIR B (para configurar si es salida o entrada)
#define GPIO_A_ADDR  0x12  //Direccion del registro GPIO A
#define GPIO_B_ADDR  0x13  //Direccion del registro GPIO B

#define IO_OUTPUTS 0x00   //Valor para configurar IO como salida.
#define IO_INPUTS 0xFF

///////////////////////////////////////////////////////////
//                NUMERO FICHAS Y FILAS
///////////////////////////////////////////////////////////
#define Fila0 0
#define Fila1 1
#define Fila2 2

#define Ficha0 0
#define Ficha1 1
#define Ficha2 2
#define Ficha3 3
#define Ficha4 4
#define Ficha5 5
#define Ficha6 6
#define Ficha7 7
#define Ficha8 8
#define Ficha9 9
#define Ficha10 10
#define Ficha11 11 
#define Ficha12 12
#define Ficha13 13
#define Ficha14 14
#define Ficha15 15
#define Ficha16 16
#define Ficha17 17
#define Ficha18 18

//Botones tablero
#define PinBotonProg0 17
#define PinBotonProg1 19 
#define PinBotonProg2 18
#define PinBotonFuncion 16

/////////////////////////////////////////////////////////////////////////////////////////
//                               FUNCIONES
////////////////////////////////////////////////////////////////////////////////////////

void ConfigTablero(); //llamar siempre en setup

void config_sensors_ports(byte CsPuerto,byte chip_address,byte reg_address);
void write_expansion_port(byte nCs_pin,byte chip_address,byte reg_address,byte data);
byte read_expansion_port(byte nCs_pin,byte chip_address,byte reg_address);
byte Leerficha(int NumFicha);

void config_leds_Ports();
void PrenderLed(int  NumFicha);
void TestingLeds();

#endif
