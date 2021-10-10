#include <Arduino.h>
#include "SerialView.h"



void SerialView::init()
{
      Serial.begin(115200);
}

void SerialView::show(String message) 
{
	 Serial.println(message);
}


void SerialView::debug(String message)
{
    bool debugb = true;
    if (debugb) {
        Serial.println(message);
    }
}
