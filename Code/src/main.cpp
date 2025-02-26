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

const int FOTOTIMER = 600; //min 200

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
  ADJUST_BRIGHTNESS_HIGH,
  ADJUST_POSITION_LEFT,
  ADJUST_POSITION_RIGHT
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




bool bEntry = true;




void stateMachine();

void setup() {
  Serial.begin(9600);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(SHUTTER_PIN,OUTPUT);
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
        ledOne.setBrightness(ledOne.getLowBrightness());
        ledTwo.setBrightness(ledTwo.getLowBrightness());
        //ledOne.setBrightness(10);
        //ledTwo.setBrightness(10);
        Serial.println("IDLE");
        digitalWrite(SHUTTER_PIN, LOW);
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
        //ledOne.ramp(ledOne.getLowBrightness(),100);
        ledOne.setBrightness(ledOne.getLowBrightness());
        ledTwo.setBrightness(0);
        changeTimer.start(2000);
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
        ledOne.ramp(ledOne.getHighBrightness(),600);        
        changeTimer.start(400);
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
          delay(FOTOTIMER); // Kurze Verzögerung
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
        //ledTwo.ramp(ledTwo.getLowBrightness(),500);
        changeTimer.start(200);
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
        //ledTwo.ramp(ledTwo.getHighBrightness(),100);     
        ledTwo.setBrightness(ledTwo.getHighBrightness());   
        changeTimer.start(1200);
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
          delay(FOTOTIMER); // Kurze Verzögerung
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
        rotary.setPosition(ledOne.getLowBrightness());
      }
      //int potiValue = map(analogRead(POTI_PIN),0,1023,0,100);
      rotary.readEncoder();
      int potiValue = rotary.getPosition();
      ledOne.setLowBrightness(potiValue);
      ledTwo.setLowBrightness(potiValue);
      ledOne.setBrightness(ledOne.getLowBrightness());
      ledTwo.setBrightness(ledTwo.getLowBrightness());
      
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
        rotary.setPosition(ledOne.getHighBrightness());
      }
      //int potiValue2 = map(analogRead(POTI_PIN),0,1023,0,100);
      rotary.readEncoder();
      int potiValue2 = rotary.getPosition();
      ledOne.setHighBrightness(potiValue2);
      ledTwo.setHighBrightness(potiValue2);
      ledOne.setBrightness(ledOne.getHighBrightness());
      ledTwo.setBrightness(ledTwo.getHighBrightness());
      
      if (b2.getButtonClick()){
        bEntry = true;
        currentState = ADJUST_POSITION_LEFT;
      }
      break;
    }
    case ADJUST_POSITION_LEFT:
    {
      if(bEntry){
        bEntry = false;        
        Serial.println("ADJUST_POSITION_LEFT");
      }
      
      ledOne.setBrightness(ledOne.getLowBrightness());
      ledTwo.setBrightness(0);
      
      if (b2.getButtonClick()){
        bEntry = true;
        currentState = ADJUST_POSITION_RIGHT;
      }
      break;
    }
    case ADJUST_POSITION_RIGHT:
    {
      if(bEntry){
        bEntry = false;        
        Serial.println("ADJUST_POSITION_RIGHT");
      }
      
      ledOne.setBrightness(0);
      ledTwo.setBrightness(ledTwo.getLowBrightness());
      
      if (b2.getButtonClick()){
        bEntry = true;
        currentState = IDLE;
      }
      break;
    }
  }
}
  
