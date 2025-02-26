#include <Arduino.h>
#include <Timer.h>
#include <LED.h>
#include <Button.h>
#include <EEPROM.h>
#include <MyRotary.h> 



const int LED_1_PIN = 9;
const int LED_2_PIN = 10;
const int SHUTTER_PIN = 4;
const int BUTTON_PIN = 7;
const int BUTTON_PIN2 = 12;
const int POTI_PIN = A0;
const int ENCODER_CLK = A3;
const int ENCODER_DT = A2;

// Enum für die Zustände
enum State {
  IDLE,
  LEFT_HALF_ON,
  LEFT_FULL_ON,
  RIGHT_HALF_ON,
  RIGHT_FULL_ON,
  FOTO_LEFT,
  FOTO_RIGHT, 
  ADJUST_BRIGHTNESS_LOW,
  ADJUST_BRIGHTNESS_HIGH
};

// Variablen
State currentState = IDLE;
Timer changeTimer;
Timer rampTimer;
Led ledOne(LED_1_PIN);
Led ledTwo(LED_2_PIN);
Button b1(BUTTON_PIN);
Button b2(BUTTON_PIN2);
MyRotary rotary(ENCODER_CLK,ENCODER_DT);



const int sollBrightness = 255; // Zielhelligkeit für LEDs
int LedBrightnessOne = sollBrightness/2; // aktuelle Helligkeit der jeweiligen LED
int LedBrightnessTwo = sollBrightness/2;
bool bEntry = true;




void stateMachine();

void setup() {
  Serial.begin(9600);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(SHUTTER_PIN, OUTPUT);
  pinMode(POTI_PIN,INPUT);

 
  
}

void loop() {
  //Serial.println(digitalRead(BUTTON_PIN2));
  //Serial.println(b2.getButtonClick());
  stateMachine();  
}


void stateMachine(){
  // Zustandsmaschine
  switch (currentState) {
    case IDLE:
      {if(bEntry){
        bEntry = false;
        ledOne.setBrightness(0);
        ledTwo.setBrightness(0);
        Serial.println("IDLE");
      }
 
      if (b1.getButtonClick()){
        bEntry = true;
        currentState = LEFT_HALF_ON;
      }
      if (b2.getButtonClick()){
        bEntry = true;
        currentState = ADJUST_BRIGHTNESS_LOW;
      }
      break;
      }

    case LEFT_HALF_ON:
    {if(bEntry){
        bEntry = false;
        ledOne.setBrightness(ledOne.getLowBrightness());
        ledTwo.setBrightness(0);
        changeTimer.start(1000);
        Serial.println("LEFT_HALF_ON");
      }
 
      if (changeTimer.isFinished()){
        bEntry = true;
        currentState = LEFT_FULL_ON;
      }
      break;
      }

    case LEFT_FULL_ON:
      {if(bEntry){
        bEntry = false;
        ledOne.ramp(ledOne.getHighBrightness(),1000);        
        changeTimer.start(1000);
        Serial.println("LEFT_FULL_ON");
      }
      if (changeTimer.isFinished()) {
        bEntry = true;
        currentState = FOTO_LEFT;
      }
      break;
      }

    case FOTO_LEFT:
      {if(bEntry){
          bEntry = false;
          digitalWrite(SHUTTER_PIN, HIGH); // Kameraauslöser aktivieren
          delay(100); // Kurze Verzögerung
          digitalWrite(SHUTTER_PIN, LOW);  // Kameraauslöser deaktivieren
          Serial.println("FOTO_LEFT");
        }
      
      if (true) {
        bEntry = true;
        currentState = RIGHT_HALF_ON;
      }
      break;
      }

    case RIGHT_HALF_ON:
      {if(bEntry){
        bEntry = false;
        ledOne.setBrightness(0);
        ledTwo.setBrightness(ledTwo.getLowBrightness());
        changeTimer.start(1000);
        Serial.println("RIGHT_HALF_ON");
      }
 
      if (changeTimer.isFinished()){
        bEntry = true;
        currentState = RIGHT_FULL_ON;
      }
      break;
      }

    case RIGHT_FULL_ON:
      {if(bEntry){
        bEntry = false;
        ledTwo.ramp(ledTwo.getHighBrightness(),1000);        
        changeTimer.start(1000);
        Serial.println("RIGHT_FULL_ON");
      }
      if (changeTimer.isFinished()) {
        bEntry = true;
        currentState = FOTO_RIGHT;
      }
      break;
      }

    case FOTO_RIGHT:
      {if(bEntry){
          bEntry = false;
          digitalWrite(SHUTTER_PIN, HIGH); // Kameraauslöser aktivieren
          delay(100); // Kurze Verzögerung
          digitalWrite(SHUTTER_PIN, LOW);  // Kameraauslöser deaktivieren
          Serial.println("FOTO_RIGHT");
        }
      
      if (true) {
        bEntry = true;
        currentState = IDLE;
      }
      break;
      }
    case ADJUST_BRIGHTNESS_LOW:
    {
      if(bEntry){
        bEntry = false;        
        Serial.println("ADJUST_BRIGHTNESS_LOW");
      }
      int potiValue = map(analogRead(POTI_PIN),0,1023,0,100);
      ledOne.setLowBrightness(potiValue);
      ledTwo.setLowBrightness(potiValue);
      ledOne.setBrightness(ledOne.getLowBrightness());
      ledTwo.setBrightness(ledTwo.getLowBrightness());
      //rotary.readEncoder();
      if (b2.getButtonClick()){        
        bEntry = true;
        currentState = ADJUST_BRIGHTNESS_HIGH;
        
        }
      break;   
    }
    case ADJUST_BRIGHTNESS_HIGH:
    {
      if(bEntry){
        bEntry = false;        
        Serial.println("ADJUST_BRIGHTNESS_HIGH");
      }
      int potiValue2 = map(analogRead(POTI_PIN),0,1023,0,100);
      ledOne.setHighBrightness(potiValue2);
      ledTwo.setHighBrightness(potiValue2);
      ledOne.setBrightness(ledOne.getHighBrightness());
      ledTwo.setBrightness(ledTwo.getHighBrightness());
      
      if (b2.getButtonClick()){
        bEntry = true;
        currentState = IDLE;
      }
      break;
    }
  }
}
  
