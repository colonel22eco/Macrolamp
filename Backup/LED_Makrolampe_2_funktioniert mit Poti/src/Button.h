#include <Arduino.h>

#ifndef BUTTON
#define BUTTON

/*!
	\brief Klasse für Button


*/
class Button
{
  private:
    int PIN;
    bool lastButtonState = true;
    bool actualButtonState = true;
    long actualTime;
    long lastTime = 0;
    long timeDebounce = 100;
  public:
    Button(int GPIO_PIN) : PIN(GPIO_PIN){
        pinMode(this->PIN, INPUT_PULLUP);
        lastButtonState = digitalRead(PIN); // Anfangszustand
    } //initiierung der LED mit dem jeweiligen Pin
  //! Memberfunktion
  /*!
    \brief schaltet  ein

    \return void
  */
bool getButtonClick()
{

    actualTime = millis();
    actualButtonState = digitalRead(PIN);

   if (actualButtonState == LOW && lastButtonState == HIGH && ((actualTime - lastTime) >= timeDebounce)) {
    lastTime = actualTime;
    lastButtonState = actualButtonState;
    Serial.println("Klick erkannt");
    return true; // Klick erkannt
}


    lastButtonState = actualButtonState; // Button-Zustand immer aktualisieren
    //Serial.println("kein Klick erkannt");
    return false; // Kein Klick
}
  
  
};

#endif