#include <Arduino.h>

const int Beeper = 13;
const int R = 25, B = 26, G = 27;

const int decibalMeter = 34;
const int photoResistor = 02;

const int thresholdSoundValue = 2000;
const int thresholdLightValue = 3000;

void detect();
void detectSplashSound ();
void detectNightLights ();
void alert ();
void alertSounds ();
void alertLights ();
void reset();

void setup() {
  pinMode(decibalMeter, INPUT); pinMode(photoResistor, INPUT);
  
  pinMode(R, OUTPUT); pinMode(G, OUTPUT); pinMode(B, OUTPUT);
  pinMode(Beeper, OUTPUT);
  
  Serial.begin(115200);
}

void loop() {
  detect();
  delay(500);
}

void detect(){
  detectSplashSound();
  detectNightLights();
}

void detectSplashSound() {
  int decibal_value = analogRead(decibalMeter);
  
    Serial.print("Sound Value: ");
    Serial.print(decibal_value);
    Serial.println();

  if(decibal_value > thresholdSoundValue)
  {
    alert();
  }
}

void detectNightLights () {
  int intensity_value = analogRead(photoResistor);

  Serial.print("Light Intensity Value: ");
  Serial.print(intensity_value);
  Serial.println();

  if(intensity_value > thresholdLightValue)
  {
    alert();
  }
}

void alert (){
  Serial.println("Alert Started");
  alertSounds ();
  alertLights ();
  delay(5000);
  reset();
}

void alertSounds () {
  digitalWrite(Beeper, HIGH); 
  delay(1000);        
  digitalWrite(Beeper, LOW); 
  delay(500);  
}

void alertLights ()
{
  digitalWrite(G,LOW);
  digitalWrite(B,LOW);
  digitalWrite(R,HIGH);
  delay(200);

  digitalWrite(G,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(R,LOW);
  delay(200);
}

void reset()
{
  Serial.println("Alert Reset");
  digitalWrite(Beeper, LOW);
  digitalWrite(G,LOW);
  digitalWrite(B,LOW);
  digitalWrite(R,LOW);
}