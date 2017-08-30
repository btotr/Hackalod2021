#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Model.h"


enum events { newConnection };
volatile int connections; // used to hold the connections

WiFiServer server(80);

void Model::init() {
	server.begin();
}

int Model::getConnections() {
	return connections;
}

String  Model::getServerIp(){
    return String(WiFi.localIP().toString().c_str());   
}

String Model::getHTML() {
  return String("HTTP/1.1 200 OK\r\n") +
    "Content-Type: text/html\r\n" +
    "Connection: close\r\n" +  // the connection will be closed after completion of the response
    "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
    "\r\n" +
    "<html>" +
    "hoipipelepoi" +
    "</html>" +
    "\r\n";
}

void Model::update() {
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client) {
  	connections++;
  	this->emit(this->newConnection);
  	while (client.connected()) {
      // read line by line what the client (web browser) is requesting
      if (client.available()) {
        String line = client.readStringUntil('\r');
        if (line.length() == 1 && line[0] == '\n') {
          client.println(getHTML());
          break;
        }
      }
    }
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