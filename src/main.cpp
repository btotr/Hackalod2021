#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <OLEDView.h>
#include <Model.h>

class OLEDView view;
class Model model;

const char* ssid = "meerveld 2.4g";
const char* password = "?";

void callback() {
	view.printConnections(model.getConnections());
}

void setupWifi() {
    WiFi.begin(ssid, password);
    // wait until we have a connection
	while (WiFi.status() != WL_CONNECTED) {
    	delay(2000);
    	view.debug("connecting to WIFI ...");
	}
	view.debug(WiFi.localIP().toString().c_str());
}


void setup() {
    view.init();
    setupWifi();
    model.init();
    model.on(Model::newConnection, callback);
}

void loop() {
    model.update();
}