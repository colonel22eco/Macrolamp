#include <Arduino.h>
#include <RotaryEncoder.h>

#ifndef MYROTARY
#define MYROTARY

/*!
	\brief Klasse für MYROTARY


*/
class MyRotary
{
  private:
    int CLK;
    int DT;
    int ROTARYSTEPS =1;
    int ROTARYMAX =100;
    int ROTARYMIN =0;
    int lastPos = -1;
    int newPos;
    RotaryEncoder encoder;

    
  public:
    MyRotary(int CLK_PIN, int DT_PIN) : CLK(CLK_PIN), DT(DT_PIN),encoder(DT, CLK, RotaryEncoder::LatchMode::TWO03){        
        pinMode(this->CLK, INPUT);
        pinMode(this->DT, INPUT);        
        
    } 
  //! Memberfunktion
  /*!
    \brief liest die Eingaben des Encoders und speichert die Position in Counter ab

    \return void
  */
void readEncoder()
{  
  encoder.tick();
  newPos = encoder.getPosition() * ROTARYSTEPS;
  if (newPos < ROTARYMIN) {
    encoder.setPosition(ROTARYMIN / ROTARYSTEPS);
    newPos = ROTARYMIN;

  } else if (newPos > ROTARYMAX) {
    encoder.setPosition(ROTARYMAX / ROTARYSTEPS);
    newPos = ROTARYMAX;
  } 
  if (lastPos != newPos) {
    Serial.print(newPos);
    Serial.println();
    lastPos = newPos;
  }
}

//! Memberfunktion
  /*!
    \brief gibt den Positionswert von 0-100 zurück

    \return void
  */
int getPosition()
{
  return newPos;
}
  
  
};

#endif