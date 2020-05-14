#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

int PinButton = 12;
int PinLed = 15;

int PinBuzz = 23;
int PWMFreq = 2000;
int PWMChan = 0;
int PWMRes = 8;

int PinRGB = 13;
int NPLeds = 1;
Adafruit_NeoPixel Pixels = Adafruit_NeoPixel(NPLeds, PinRGB, NEO_GRB + NEO_KHZ800);

int PinMic = 35;
bool MicPulse = false;

void IRAM_ATTR isr()
{
    MicPulse = true;
}

void setup()
{

  Serial.begin(115200);

  pinMode(PinLed, OUTPUT);
  pinMode(PinButton, INPUT);
  pinMode(PinBuzz, OUTPUT);
  pinMode(PinMic, INPUT);

  ledcSetup(PWMChan, PWMFreq, PWMRes); //configuro frec y resoluc. de canal PWM
  ledcAttachPin(PinBuzz, PWMChan); //asigno por que pin voy a sacar el PWM
  Pixels.begin();
  Pixels.clear();

  attachInterrupt(PinMic, isr, FALLING);

}


void loop()
{
  int ButtonState;

  delay(250);
  Pixels.setPixelColor(0, Pixels.Color(0, 255, 0));
  Pixels.show();
  digitalWrite(PinLed, LOW);

  delay(250);
  digitalWrite(PinLed, HIGH);
  Pixels.setPixelColor(0, Pixels.Color(0, 0, 255));
  Pixels.show();

  ButtonState = digitalRead(PinButton);
  Serial.println(ButtonState);

  if(MicPulse)
  {
    Serial.println("Mic Pulse!");
    MicPulse = false;
    ledcWrite(PWMChan, 255);
    for (float Freq=880.0; Freq<1770; Freq=(Freq*1.0594))
    {
      ledcWriteTone(PWMChan, (int)Freq);
      delay(50);
    }
    ledcWrite(PWMChan, 0);
  }


}
