#include <Arduino.h>
#include <SPI.h>
#include "Tablero.h"

//ESPNow
#include <esp_now.h>
#include <WiFi.h>

esp_now_peer_info_t slave;      // Global copy of slave
#define CHANNEL 1
#define PRINTSCANRESULTS 0
#define DELETEBEFOREPAIR 0

// Init ESP Now with fallback
void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    // Retry InitESPNow, add a counte and then restart?
    // InitESPNow();
    // or Simply Restart
    ESP.restart();
  }
}

// Scan for slaves in AP mode
void ScanForSlave() {
  int8_t scanResults = WiFi.scanNetworks();
  // reset on each scan
  bool slaveFound = 0;
  memset(&slave, 0, sizeof(slave)); //inicializa esclavo en 0

  Serial.println("");
  if (scanResults == 0) {
    Serial.println("No WiFi devices in AP Mode found");
  } else {
    Serial.print("Found "); Serial.print(scanResults); Serial.println(" devices ");
    for (int i = 0; i < scanResults; ++i) {
      // Print SSID and RSSI for each device found
      String SSID = WiFi.SSID(i);
      int32_t RSSI = WiFi.RSSI(i);
      String BSSIDstr = WiFi.BSSIDstr(i);

      if (PRINTSCANRESULTS) {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(SSID);
        Serial.print(" (");
        Serial.print(RSSI);
        Serial.print(")");
        Serial.println("");
        delay(5000);
      }
      delay(10);
      // Check if the current device starts with `Slave`
      if (SSID.indexOf("Slave") == 0) {
        // SSID of interest
        Serial.println("Found a Slave.");
        Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
        // Get BSSID => Mac Address of the Slave
        int mac[6];
        if ( 6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x%c",  &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] ) ) {
          for (int ii = 0; ii < 6; ++ii ) {
            slave.peer_addr[ii] = (uint8_t) mac[ii];
          }
        }

        slave.channel = CHANNEL; // pick a channel
        slave.encrypt = 0; // no encryption

        slaveFound = 1;
        // we are planning to have only one slave in this example;
        // Hence, break after we find one, to be a bit efficient
        break;
      }
    }
  }

  if (slaveFound) {
    Serial.println("Slave Found, processing..");
  } else {
    Serial.println("Slave Not Found, trying again.");
  }

  // clean up ram
  WiFi.scanDelete();
}

// Check if the slave is already paired with the master.
// If not, pair the slave with master
bool manageSlave() {
  
  if (slave.channel == CHANNEL) {
    if (DELETEBEFOREPAIR) {
      deletePeer();
    }

    Serial.print("Slave Status: ");
    const esp_now_peer_info_t *peer = &slave;
    const uint8_t *peer_addr = slave.peer_addr;
    // check if the peer exists
    bool exists = esp_now_is_peer_exist(peer_addr);
    if ( exists) {
      // Slave already paired.
      //Serial.println("Already Paired");
      return true;
    } else {
      // Slave not paired, attempt pair
      esp_err_t addStatus = esp_now_add_peer(peer);
      if (addStatus == ESP_OK) {
        // Pair success
        Serial.println("Pair success");
        return true;
      } else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
        // How did we get so far!!
        Serial.println("ESPNOW Not Init");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_ARG) {
        Serial.println("Invalid Argument");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_FULL) {
        Serial.println("Peer list full");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
        Serial.println("Out of memory");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
        Serial.println("Peer Exists");
        return true;
      } else {
        Serial.println("Not sure what happened");
        return false;
      }
    }
  } else {
    // No slave found to process
    Serial.println("No Slave found to process");
    return false;
  }
}

void deletePeer() {
  const esp_now_peer_info_t *peer = &slave;
  const uint8_t *peer_addr = slave.peer_addr;
  esp_err_t delStatus = esp_now_del_peer(peer_addr);
  Serial.print("Slave Delete Status: ");
  if (delStatus == ESP_OK) {
    // Delete success
    Serial.println("Success");
  } else if (delStatus == ESP_ERR_ESPNOW_NOT_INIT) {
    // How did we get so far!!
    Serial.println("ESPNOW Not Init");
  } else if (delStatus == ESP_ERR_ESPNOW_ARG) {
    Serial.println("Invalid Argument");
  } else if (delStatus == ESP_ERR_ESPNOW_NOT_FOUND) {
    Serial.println("Peer not found.");
  } else {
    Serial.println("Not sure what happened");
  }
}

// send data
void sendData(byte data) {
  
  const uint8_t *peer_addr = slave.peer_addr;
  
  if (manageSlave()){ //antes de enviar chequeo estar conectado
    Serial.print("Sending: "); Serial.println(data,BIN);
    Serial.print("----------------------------------------------   ");
    esp_err_t result = esp_now_send(peer_addr, &data, sizeof(data));
    //Serial.print("Send Status: ");
    if (result == ESP_OK) {
      Serial.println("Success");
    } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
      // How did we get so far!!
      Serial.println("ESPNOW not Init.");
    } else if (result == ESP_ERR_ESPNOW_ARG) {
      Serial.println("Invalid Argument");
    } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
      Serial.println("Internal Error");
    } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
      Serial.println("ESP_ERR_ESPNOW_NO_MEM");
    } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
      Serial.println("Peer not found.");
    } else {
      Serial.println("Not sure what happened");
    }
  } 
  else {
      Serial.println("Slave pair failed!");
  }  
}

// callback when data is sent from Master to Slave
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//  char macStr[18];
//  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
//           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//  Serial.print("Last Packet Sent to: "); Serial.println(macStr);
//  Serial.print("Last Packet Send Status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void InterpretaFichaFuncion(byte Lectura){
  if (Lectura!=0){
    switch(Lectura){
      case B00000001:
        EnviarFilaFichasPrograma(Fila0);
        break;              
      case B00000010:
        EnviarFilaFichasPrograma(Fila1);
        break;
      case B00000100:
        EnviarFilaFichasPrograma(Fila2);            
        break;
      default:
          // statements
      break;
     }
  }  
}

void EnviarFilaFichasFunciones(){
  byte Lectura0=0,Lectura1=0,Lectura2=0,Lectura3=0;
  
  Lectura0=Leerficha(Ficha15);
  Lectura1=Leerficha(Ficha16);
  Lectura2=Leerficha(Ficha17);
  Lectura3=Leerficha(Ficha18);

  Serial.print("FichasFunciones: ");Serial.print(Lectura0);Serial.print(" ");Serial.print(Lectura1);Serial.print(" "); Serial.print(Lectura2);Serial.print(" "); Serial.println(Lectura3);   
 
  InterpretaFichaFuncion(Lectura0);
  InterpretaFichaFuncion(Lectura1);
  InterpretaFichaFuncion(Lectura2);
  InterpretaFichaFuncion(Lectura3);
}

void EnviarFilaFichasPrograma(int Fila){

  //Linea cero es la primera superior
  byte Lectura0=0,Lectura1=0,Lectura2=0,Lectura3=0,Lectura4=0;
  
  switch (Fila){
    case Fila0:
        Lectura0=Leerficha(Ficha0);
        Lectura1=Leerficha(Ficha1);
        Lectura2=Leerficha(Ficha2);
        Lectura3=Leerficha(Ficha3);
        Lectura4=Leerficha(Ficha4);
      break;
    case Fila1:
        Lectura0=Leerficha(Ficha5);
        Lectura1=Leerficha(Ficha6);
        Lectura2=Leerficha(Ficha7);
        Lectura3=Leerficha(Ficha8);
        Lectura4=Leerficha(Ficha9);
      break;
    case Fila2:      
        Lectura0=Leerficha(Ficha10);
        Lectura1=Leerficha(Ficha11);
        Lectura2=Leerficha(Ficha12);
        Lectura3=Leerficha(Ficha13);
        Lectura4=Leerficha(Ficha14);          
      break;
    default:
      // statements
      break;
    }

    Serial.print("FichasProgramas: ");Serial.print(Lectura0);Serial.print(" ");Serial.print(Lectura1);Serial.print(" "); Serial.print(Lectura2);Serial.print(" "); Serial.print(Lectura3);Serial.print(" "); Serial.println(Lectura4);   
    
    if (Lectura0!=0){
      sendData(Lectura0);
    }        
    if (Lectura1!=0){
      sendData(Lectura1);
    }        
    if (Lectura2!=0){
      sendData(Lectura2);
    }        
    if (Lectura3!=0){
      sendData(Lectura3);
    }        
    if (Lectura4!=0){
      sendData(Lectura4);
    } 
}

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

volatile boolean BotonProg0Presionado = false;
volatile boolean BotonProg1Presionado = false;
volatile boolean BotonProg2Presionado = false;
volatile boolean BotonFuncionPresionado = false;

void IRAM_ATTR handleInterrupt0(){ //si se aprieta cualquiera de los 4 botones atiendo la interrupcion, la idea es no perder botones presionados

  portENTER_CRITICAL_ISR(&mux); //equivalente a desactivar las interrupciones, para que no haya conflictos de accesos a las variables
  if (!BotonProg0Presionado){
    BotonProg0Presionado = true;  
  }
  portEXIT_CRITICAL_ISR(&mux); 
}

void IRAM_ATTR handleInterrupt1(){ //si se aprieta cualquiera de los 4 botones atiendo la interrupcion, la idea es no perder botones presionados

  portENTER_CRITICAL_ISR(&mux); //equivalente a desactivar las interrupciones, para que no haya conflictos de accesos a las variables
  if (!BotonProg1Presionado){
    BotonProg1Presionado = true;  
  }
  portEXIT_CRITICAL_ISR(&mux); 
}

void IRAM_ATTR handleInterrupt2(){ //si se aprieta cualquiera de los 4 botones atiendo la interrupcion, la idea es no perder botones presionados

  portENTER_CRITICAL_ISR(&mux); //equivalente a desactivar las interrupciones, para que no haya conflictos de accesos a las variables
  if (!BotonProg2Presionado){
    BotonProg2Presionado = true;  
  }
  portEXIT_CRITICAL_ISR(&mux); 
}

void IRAM_ATTR handleInterrupt3(){ //si se aprieta cualquiera de los 4 botones atiendo la interrupcion, la idea es no perder botones presionados

  portENTER_CRITICAL_ISR(&mux); //equivalente a desactivar las interrupciones, para que no haya conflictos de accesos a las variables
  if (!BotonFuncionPresionado){
    BotonFuncionPresionado = true;
  }  
  portEXIT_CRITICAL_ISR(&mux); 
}

void setup() {
  
  Serial.begin(115200);
  //Set device in STA mode to begin with
  WiFi.mode(WIFI_STA);
  
  Serial.print("STA MAC: "); Serial.println(WiFi.macAddress()); // This is the mac address of the Master in Station Mode  
  InitESPNow(); // Init ESPNow with a callback logic  
  esp_now_register_send_cb(OnDataSent); // Once ESPNow is successfully Init, we will register for Send CB to

  //we scan for slave
  ScanForSlave(); 
  manageSlave(); //agrega al esclavo

  ConfigTablero(); 
  
  //interrupciones
  attachInterrupt(digitalPinToInterrupt(PinBotonProg0), handleInterrupt0, RISING);
  attachInterrupt(digitalPinToInterrupt(PinBotonProg1), handleInterrupt1, RISING);
  attachInterrupt(digitalPinToInterrupt(PinBotonProg2), handleInterrupt2, RISING);
  attachInterrupt(digitalPinToInterrupt(PinBotonFuncion), handleInterrupt3, RISING);  
}

///////////////////////////////////////////
void loop()
{
  if(BotonProg0Presionado){
    //Serial.println("Boton0");      
    EnviarFilaFichasPrograma(Fila0);
    delay(1000); // tiempo para eliminar rebotes de boton, y limpio flag
    BotonProg0Presionado=false;
  }
  
  if(BotonProg1Presionado){     
    //Serial.println("Boton1");  
    EnviarFilaFichasPrograma(Fila1); 
    delay(1000); // tiempo para eliminar rebotes de boton, y limpio flag
    BotonProg1Presionado=false;   
  }
  
  if(BotonProg2Presionado){     
   // Serial.println("Boton2");  
    EnviarFilaFichasPrograma(Fila2); 
    delay(1000); // tiempo para eliminar rebotes de boton, y limpio flag
    BotonProg2Presionado=false;    
  }
  
  if(BotonFuncionPresionado){ 
    //Serial.println("Boton3");      
    EnviarFilaFichasFunciones();
    delay(1000); // tiempo para eliminar rebotes de boton, y limpio flag
    BotonFuncionPresionado=false;    
  }
    
}
