#include <Arduino.h>
#include "OLEDView.h"
#include "SSD1306Wire.h"

// API: https://github.com/squix78/esp8266-oled-ssd1306

SSD1306Wire display(0x3c, D2, D1);  // ADDRESS, SDA, SCL

void OLEDView::init() 
{
	display.init();
	display.setFont(ArialMT_Plain_10);
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.flipScreenVertically();
}

void OLEDView::show(String message) 
{
	display.clear();
	display.drawString(10, 10, message);
	display.display();
}

void OLEDView::debug(String message)
{
    bool debugb = true;
    if(debugb){
	    display.clear();
	    display.drawString(10, 10, message);
	    display.display();
	}
}
