#include <Arduino.h>
#include <SerialView.h>
#include <Model.h>
#include <WIFI.h>

class SerialView view;
class Model model;
class WIFI wifi;

void newConnectionCallback() {
	view.printConnections(model.getConnections());
}

void wifiConnectingCallback() {
    view.debug("Connecting to WIFI...");
}

void wifiConnectedCallback() {
    model.init();
    model.on(Model::newConnection, newConnectionCallback);
	view.debug(model.getServerIp());
}

void setup() {
    view.init();
    view.debug("test");
    wifi.on(WIFI::wifiConnecting, wifiConnectingCallback);
    wifi.on(WIFI::wifiConnected, wifiConnectedCallback);
    wifi.setup();
}

void loop() {
    model.update();
}