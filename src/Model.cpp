#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Model.h"
#include "SerialView.h"

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

class SerialView dview;

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
  return String("HTTP/1.1 200 OK\r\n") +
    "Content-Type: text/plain\r\n" +
    "Connection: close\r\n" + 
    "\r\n" +
    t +
    "\r\n";
}

String Model::parseRequest(String request) {
  dview.debug("requesting" + request);
  return request;
}

void Model::update() {
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client) {
  	connections++;
  	this->emit(this->newConnection);
  	dview.debug("requesting");

        client.println(this->getHTML("test"));

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
