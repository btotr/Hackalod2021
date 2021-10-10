#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "Model.h"
#include "geo.h"
#include "SRF05.h"

#include <string>
#include <cmath>
#include <sstream>
#include <vector>
#include <iterator>

class GEO geo;

enum events { waiting };
volatile int connections;


const int echoPin1 = 14;  //D5 Or GPIO-14 of nodemcu
const int trigPin1 = 12;  //D6 Or GPIO-12 of nodemcu
const int trigPin2 = 13;  //D7 Or GPIO-0 of nodemcu
const int echoPin2 = 15;  //D8 Or GPIO-0 of nodemcu

SRF05 srf1(trigPin1, echoPin1);
SRF05 srf2(trigPin2, echoPin2);


AsyncWebServer server(80);

void Model::init() {
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      //this->emit(this->waiting);
    }
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String coordinates = "test";
        request->send(200, "text/plain", coordinates);
    });
      
    AsyncElegantOTA.begin(&server);
	server.begin();
    srf1.setCorrectionFactor(1.035);
	srf2.setCorrectionFactor(1.035);
	
}

int Model::getConnections() {
	return connections;
}

String  Model::getServerIp(){
    return String(WiFi.localIP().toString().c_str());   
}

String Model::getHTML(String body) {
  return String("HTTP/1.1 200 OK\r\n") +
    "Content-Type: text/plain\r\n" +
    "Connection: close\r\n"
    "\r\n" +
    body +
    "\r\n";
}

String Model::getCoordinates() {
    int correction = 5;
    float a = srf1.getCentimeter();
    float b = srf2.getCentimeter() + correction;
    float c = 50; 
    float x = (pow(c, 2) + pow(b, 2) - pow(a, 2))/(2*c);
    float y = sqrt((pow(b, 2) - pow(x,2)));
    
    String distance = String(a) + ", " + String(b) + " , x:" + String(x) + " y:" + String(y);

    return distance;
}


void Model::update() {
  //* WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  //if (client) {
  //	connections++;
  //	this->emit(this->newConnection);
  //	int x = 121687;
  //  int y = 487484;
  //	String body = String(geo.locationToWGS84(x, y).c_str()) + 
  //	"\r\n" + String(this->getCoordinates()) ;
  //	
  //  client.println(this->getHTML(body));
 //   delay(1);
 //   // close the connection:
 //   client.stop();
 // }

  AsyncElegantOTA.loop();
}






// events

void Model::on(events event, std::function<void()> c) {
	callbacks.push_back(std::make_pair(c, static_cast<int>(event)));
};

void Model::emit(int event) {
	for (int i=0; i< callbacks.size(); i++){
		 if (callbacks[i].second == event) {
		 	callbacks[i].first();
		 }
	 };
};
