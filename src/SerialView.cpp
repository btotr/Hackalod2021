#include <Arduino.h>
#include "SerialView.h"

void SerialView::init()
{
      Serial.begin(9600);
}

void SerialView::printConnections(int connections) 
{
	 Serial.println(connections);
}


void SerialView::debug(String message)
{
    Serial.println(message);
}