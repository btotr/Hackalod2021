#include <Arduino.h>
#include "Event.h"
#include <functional>

class Model : Event {
	public:
		void init();
		enum events { newConnection };
		void on(events event, std::function<void()> c);
		void emit(int event);
		void update();
		String getHTML(String answer);
		String parseRequest(String line);
		int getConnections();
		String getServerIp();
};