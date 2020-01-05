#include <Volume.h>
#include "pitches.h"
#include "songs.h"

#define photocellFrequPin 3
#define callibrationPin 13
#define photocellVolPin 2
#define  inPin 13
#define button 2
#define _case1 3
#define _case2 4


int pitches[]={ 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978};
Volume vol;
int photocellFrequReading;
int minFrequValue = 1023;
int maxFrequValue = 0;

int photocellVolReading;
int minVolValue = 1023;
int maxVolValue = 0;
int duration;

int currentState;
int prevState;
int timesPressed=0;

void getTimesPressed()
{
  Serial.println(timesPressed);
  currentState = digitalRead(button);
  if(currentState != prevState)
  {
    if(currentState == 1 && prevState == 0){
      timesPressed++;
    }
  }
  prevState=currentState;
  //return timesPressed
}

void playMario(int breakCondition)
{
    Serial.println(" 'Mario Theme'");
    int size = sizeof(mario) / sizeof(int);
    int _volume = 255;
    for (int thisNote = 0; thisNote < size; thisNote++) 
    {
      getTimesPressed();
      if (timesPressed != breakCondition)
        break;
      if(mario[thisNote] == 0)
        _volume = 1;
      else
        _volume = 255;
       int noteDuration = marioTempo[thisNote] ;
       int pauseBetweenNotes = noteDuration * 1.30;
       
       vol.tone(mario[thisNote], _volume);
       vol.delay(noteDuration);
       
       vol.tone(20000,1);
       vol.delay(pauseBetweenNotes);
 
      
       // stop the tone playing:
    }

}


void playNever(int breakCondition)
{
    Serial.println(" 'Never gonna give you up'");
    int size = sizeof(never) / sizeof(int);
    int _volume = 255;
    for (int thisNote = 0; thisNote < size; thisNote++) 
    {
      getTimesPressed();
      if (timesPressed != breakCondition)
        break;
      if(never[thisNote] == 0)
        _volume = 1;
      else
        _volume = 255;
       //to calculate the note duration simply multiply the tempo with 50   
       int noteDuration = neverTempo[thisNote] * 50;
       int pauseBetweenNotes = noteDuration * 1.30;
       
       vol.tone(never[thisNote], _volume);
       vol.delay(noteDuration);
       
       vol.tone(20000,1);
       vol.delay(pauseBetweenNotes);
 
      
       // stop the tone playing:
    }

}

void setup() {
  // cat timp e aprins led-ul se calibreaza
  pinMode(callibrationPin, OUTPUT);
  digitalWrite(callibrationPin, HIGH);
  pinMode(inPin,INPUT);
  pinMode(button, INPUT);
  pinMode(_case1, OUTPUT);
  pinMode(_case2, OUTPUT);
  
  // put your setup code here, to run once:

  while(millis() < 5000)
  {
      photocellFrequReading = analogRead(photocellFrequPin);
      if(photocellFrequReading > maxFrequValue)
      {
        maxFrequValue = photocellFrequReading;
      }
      else 
          if(photocellFrequReading < minFrequValue)
          {
            minFrequValue  = photocellFrequReading;
          }
      
      photocellVolReading = analogRead(photocellVolPin);
      if(photocellVolReading > maxVolValue)
      {
        maxVolValue = photocellVolReading;
      }
      else 
          if(photocellVolReading < minVolValue)
          {
            minVolValue = photocellVolReading;
          }
  }  
  digitalWrite(callibrationPin, LOW);
  vol.begin();
  Serial.begin(9600);  
}

int getFrequency()
{
  int frequency;
  //get the reading from the photocell
  photocellFrequReading = analogRead(photocellFrequPin);
  //map the value to the corresponding frequency value
  if(photocellFrequReading < minFrequValue)
    photocellFrequReading  = minFrequValue;
  if(photocellFrequReading > maxFrequValue)
    photocellFrequReading  = maxFrequValue;
  frequency = map(photocellFrequReading, minFrequValue, maxFrequValue, 0, 89);
  //Serial.print("Mapped value: ");
  //Serial.println(frequency);
  return pitches[frequency];
}

byte getVolume()
{
  byte volume;
  photocellVolReading = analogRead(photocellVolPin);
  //Serial.print("Duration: ");
  //Serial.println(duration);
  if(photocellVolReading < minVolValue)
    photocellVolReading  = minVolValue;
  if(photocellVolReading > maxVolValue)
    photocellVolReading  = maxVolValue;
  volume = map(photocellVolReading, minVolValue, maxVolValue, 50, 255);
  if(volume == 50)
    volume=50;
  return volume;
}

void loop() {
  // put your main code here, to run repeatedly:
  getTimesPressed();
  //Serial.println(_case);
  if(timesPressed % 3 == 0)
  {
    int frequency = getFrequency();
    byte volume = getVolume();
    digitalWrite(_case1,LOW);
    digitalWrite(_case2,LOW);
    Serial.print("FREQUENCY / VOLUME : ");
    Serial.print(frequency);
    Serial.print("  /  ");
    Serial.println(volume);
    vol.tone(frequency, volume);
  }
  else if (timesPressed % 3 == 1)
  {
    digitalWrite(_case1,LOW);
    digitalWrite(_case2,HIGH);
    playMario(timesPressed);
  }
  else if(timesPressed % 3 == 2)
  {
    digitalWrite(_case1,HIGH);
    digitalWrite(_case2,LOW);
    playNever(timesPressed);
    //vol.noTone();
  }
  
  
  
}
