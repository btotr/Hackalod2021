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
String latlon;

#define SOUND_SPEED 0.034


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
        request->send(200, "text/plain", latlon);
    });
      
    AsyncElegantOTA.begin(&server);
	server.begin();
	
	/*pinMode(trigPin1, OUTPUT);
	pinMode(echoPin1, INPUT);
	pinMode(trigPin2, OUTPUT);
	pinMode(echoPin2, INPUT);*/
    //srf1.setModeSingle();
	//srf2.setModeSingle();
	//srf1.setSpeedOfSound(340.5);
	//srf2.setSpeedOfSound(340.5);
	//srf1.setCorrectionFactor(1.035);
	//srf2.setCorrectionFactor(1.035);
	
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
    // get local coordinates

    int correctionx = -4;
    int correctiony = -9;
    float a = 500;
    float b = 500;


    while(a>200 || b>200){
         a = srf1.getCentimeter() ;
         b = srf2.getCentimeter() /2 ;
         delay(500);
    }
    
    
    
    
    float c = 50; // distance between sensors
    float lx = (pow(c, 2) + pow(b, 2) - pow(a, 2))/(2*c) + correctionx;
    float ly = sqrt((pow(b, 2) - pow(lx,2))) + correctiony;
    
    // translate to RD
    float RDx2 = 167714; // knooppunt 99 Gelderland
    float RDx1 = 141035; // knooppunt 99 Utrecht
    float RDy2 = 475480; // knooppunt 37 Flevoland
    float RDy1 = 450602; // knooppunt 70 Utrecht
    
    float RDx = (((RDx2 - RDx1)/c)*lx)+RDx1;
    float RDy = (((RDy2 - RDy1)/c)*ly)+RDy1;
    
    // translate to WGS84
     latlon = geo.locationToWGS84(RDx, RDy).c_str();
    //String debug = "d1: " +String(d1)+" d2: "+String(d2)+" da:" + String(a) + ", db:" + String(b) + " , lx:" + String(lx) + " ly:" + String(ly) + " rdx:" + String(RDx) + " rdy:" + String(RDy) + " latlon: " + latlon;

    

    return latlon;
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
