#include <Arduino.h>
#include "Event.h"
#include <functional>

class Model : Event {
	public:
		void init();
		enum events { newConnection };
		void on(int event, std::function<void()> c);
		void on(events event, std::function<void()> c);
		void emit(int event);
		void update();
		String getHTML();
		int getConnections();
};