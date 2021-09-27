#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Model.h"
#include "OLEDView.h"
#include "geo.h"

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

class OLEDView dview;
class GEO geo;

enum events { newConnection };
volatile int connections; // used to hold the connections



WiFiServer server(80);

void Model::init() {
	server.begin();
	dview.init();
}

int Model::getConnections() {
	return connections;
}

String  Model::getServerIp(){
    return String(WiFi.localIP().toString().c_str());   
}

String Model::getHTML(String t) {
   int x = 121687;
    int y = 487484;
  return String("HTTP/1.1 200 OK\r\n") +
    "Content-Type: text/plain\r\n" +
    "Refresh: 5\r\n" +
    "\r\n" +
    t +
    geo.locationToWGS84(x, y).c_str() +
    "\r\n";
}


void Model::update() {
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client) {
  	connections++;
  	this->emit(this->newConnection);
  	//dview.debug("requesting" + geo.locationToWGS84(x, y).c_str());
    client.println(this->getHTML("test: "));
    delay(1);
    // close the connection:
    client.stop();
  }
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
