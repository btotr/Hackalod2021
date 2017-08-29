#include <Arduino.h>
#include "AbstractView.h"

class SerialView : AbstractView {
	public:
		void init();
		void printConnections(int connections);
		void debug(String message);
};