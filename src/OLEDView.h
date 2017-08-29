#include <Arduino.h>
#include "AbstractView.h"

class OLEDView : AbstractView{
	public:
		void init();
		void printConnections(int connections);
		void debug(String message);
};