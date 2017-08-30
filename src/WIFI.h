#include <Arduino.h>
#include "Event.h"
#include <functional>

class WIFI : Event {
	public:
		void setup();
		enum events { wifiConnected, wifiConnecting };
		void on(events event, std::function<void()> c);
		void emit(int event);
};