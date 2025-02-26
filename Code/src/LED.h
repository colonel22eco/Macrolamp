#include <Arduino.h>

#ifndef LED
#define LED

/*!
	\brief Klasse für RELAIS


*/
class Led
{
  private:
    int PIN;
    int actualBrigthness; // Value 0-100
  public:
    Led(int GPIO_PIN) : PIN(GPIO_PIN){
        pinMode(this->PIN, OUTPUT);
        
    } 
    int lowBrightness = 10;
    int highBrightness = 30;
    //initiierung der LED mit dem jeweiligen Pin
  //! Memberfunktion
  /*!
    \brief setzt die LED auf den Wert des mitgegebenen Parameters. Wertebereich 0 - 100

    \return void
  */
  void setBrightness(int targetBrightness)
  {
    actualBrigthness = targetBrightness;
    int brightnessValueMapped = map(targetBrightness, 0, 100, 0, 255);    
    analogWrite(this->PIN, brightnessValueMapped);
     }
    //! Memberfunktion
  /*!
    \brief lässt die Led auf den Zielwert in eine definierten Zeit ansteigen

    \return void
  */
  void ramp(int targetBrightness, int transitionTime)
  {
    int timeDelay = transitionTime / (targetBrightness-actualBrigthness);
    for(int i = actualBrigthness; i <= targetBrightness; i++)
    {
      setBrightness(i);
      delay(timeDelay); //delay ist eigentlich nicht schlimm, weil der µC eh nichts anderes in der Zeit machen soll
    }    
  }

   //! Memberfunktion
  /*!
    \brief setzt die tiefe Zielhelligkeit

    \return void
  */
  void setLowBrightness(int lowTargetBrightness)
  {
    this->lowBrightness = lowTargetBrightness;
  }

   //! Memberfunktion
  /*!
    \brief setzt die hohe Zielhelligkeit

    \return void
  */
  void setHighBrightness(int highTargetBrightness)
  {
    this->highBrightness = highTargetBrightness;
  }
   //! Memberfunktion
  /*!
    \brief liefert die tiefe Zielhelligkeit

    \return void
  */
  int getLowBrightness()
  {
    return this->lowBrightness;
  }
     //! Memberfunktion
  /*!
    \brief liefert die hohe Zielhelligkeit

    \return void
  */
  int getHighBrightness()
  {
    return this->highBrightness;
  }
  
};

#endif