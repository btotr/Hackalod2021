#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "WIFI.h"
#include <config.h>
#include <SerialView.h>

enum events { wifiConnected, wifiConnecting };

void WIFI::setup() {
    WiFi.begin(ssid, pass);
    // wait until we have a connection
	while (WiFi.status() != WL_CONNECTED) {
    	delay(2000);
    	this->emit(this->wifiConnecting);
	}
	this->emit(this->wifiConnected);
	
}

// events

void WIFI::on(events event, std::function<void()> c) {
	callbacks.push_back(std::make_pair(c, static_cast<int>(event)));
};

void WIFI::emit(int event) {
	for (int i=0; i< callbacks.size(); i++){
		 if (callbacks[i].second == event) {
		 	callbacks[i].first();
		 }
	 };
};