
#include "Robot.h"

Adafruit_NeoPixel Pixels = Adafruit_NeoPixel(NumLedsRGB, LedRGB, NEO_GRB + NEO_KHZ800);
Servo Servo1;  // create servo object to control a servo
Servo Servo2;

void ConfigRobot(){
  
  //Led Indicador
  pinMode(LedIndicador,OUTPUT);
  digitalWrite(LedIndicador,LOW); //se prende con LOW
  
  //Zumbador
  pinMode(Zumbador,OUTPUT);
  ledcSetup(PWMCanal, PWMFreq, PWMResolucion); //configuro frec y resoluc. de canal PWM
  ledcAttachPin(Zumbador, PWMCanal); //asigno por que pin voy a sacar el PWM
  ledcWrite(PWMCanal, 0); //(cambia el duty) intensidad del volumen

  //LED RGB
  Pixels.begin();
  Pixels.clear();
  Pixels.setPixelColor(0, Pixels.Color(255, 0, 0));
  Pixels.show();
  delay(200);
  Pixels.setPixelColor(0, Pixels.Color(0,255, 0));
  Pixels.show();
  delay(200);
  Pixels.setPixelColor(0, Pixels.Color(0,0, 255));
  Pixels.show();
  delay(200);
  Pixels.setPixelColor(0, Pixels.Color(255,255, 255));
  Pixels.show();
  delay(200);
  Pixels.setPixelColor(0, Pixels.Color(0,0,0));
  Pixels.show();
//  Pixels.setPixelColor(0, 0,0,0,126);
//  Pixels.setBrightness(126);
//  Pixels.show();

//  pinMode(Servo1Pin,OUTPUT);
//  digitalWrite(Servo1Pin,LOW);
//  pinMode(Servo2Pin,OUTPUT);
//  digitalWrite(Servo2Pin,LOW);

  ServosPosicionInicial();
    
}

void ZumbadorSonar(){
  ledcWrite(PWMCanal, 255); // volumen al maximo
  for (float Freq=880.0; Freq<1770; Freq=(Freq*1.0594))
  {
    ledcWriteTone(PWMCanal, (int)Freq); //Cambia la frecuencia
    delay(50);
  }
  ledcWrite(PWMCanal, 0); // desactivo el volumen
}

void ServosPosicionInicial(){
  //posicion inicial servos
  Servo1.attach(Servo1Pin,Servo1Canal);  
  Servo2.attach(Servo2Pin,Servo2Canal);
  Servo1.write(Servo1AnguloInicial);
  delay(1000); 
  Servo2.write(Servo2AnguloInicial);
  delay(1000); 
  Servo1.detach();//apago pwm    
  Servo2.detach();//apago pwm   

//  //no se en que posicion esta, pero lo voy llevando de a poco a la inicial
//  for (int veces=1; veces<10; veces++)
//  {   
//    Servo1.attach(Servo1Pin,Servo1Canal);   
//    Servo1.write(Servo1AnguloInicial); 
//    delay(25);
//    Servo1.detach();//apago pwm       
//  }
//   
//  for (int veces=1; veces<10; veces++)
//  {   
//    Servo2.attach(Servo2Pin,Servo2Canal);
//    Servo2.write(Servo2AnguloInicial); 
//    delay(25);  
//    Servo2.detach();//apago pwm   
//  }
//  
//  Servo1.detach();//apago pwm  
//  Servo2.detach();//apago pwm  
}

void MoverServo1(){

  Servo1.attach(Servo1Pin,Servo1Canal);  
  Servo2.attach(Servo2Pin,Servo2Canal);
  
  for (float ang=150; ang>29; ang=ang-10)
  {    
    Servo1.write(ang); 
    delay(50);
    Servo2.write(ang); 
    delay(50);
  }
 
  for (float ang=30; ang<150; ang=ang+10)
  {    
    Servo1.write(ang); 
    delay(50);
    Servo2.write(ang); 
    delay(50);
  }
  Servo1.detach();//apago pwm    
  Servo2.detach();//apago pwm 
   
//  Servo1.attach(Servo1Pin,Servo1Canal);  
//  Servo1.write(30);  
//  delay(1000);
//  Servo1.write(150);  
//  delay(1000);  
//  Servo1.detach();//apago pwm    
//  
}

void MoverServo2(){
  
  Servo2.attach(Servo2Pin,Servo2Canal);
  Servo2.write(30);
  delay(1000);
  Servo2.write(150);
  delay(1000);
  Servo2.detach();//apago pwm  
  
}

////los 2 servos
//  Servo1.attach(Servo1Pin,Servo1Canal);  
//  Servo2.attach(Servo2Pin,Servo2Canal);
//  Servo1.write(30); 
//   Servo2.write(30); 
//  delay(2000);
//  Servo1.write(150); 
//   Servo2.write(150); 
//  delay(2000);  
//  Servo1.detach();//apago pwm    
//  Servo2.detach();//apago pwm  
