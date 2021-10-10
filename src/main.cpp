#include <Arduino.h>
#include <OLEDView.h>
#include <SerialView.h>
#include <Model.h>
#include <WIFI.h>


class OLEDView oledView;
class SerialView serialView;
class Model model;
class WIFI wifi;


void wifiConnectingCallback() {
    oledView.debug("Connecting to WIFI...");
}

void wifiConnectedCallback() {
    model.init();
    //model.on(Model::waiting, waitingCallback);
	oledView.show(model.getServerIp());
}

void setup() {
    oledView.init();
    serialView.init();
    wifi.on(WIFI::wifiConnecting, wifiConnectingCallback);
    wifi.on(WIFI::wifiConnected, wifiConnectedCallback);
    wifi.setup();
}





void loop() {
    model.update();
    serialView.debug(model.getCoordinates());
    delay(5000);

}
