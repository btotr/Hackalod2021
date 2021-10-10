#include <Arduino.h>
#include "AbstractView.h"

class OLEDView : AbstractView{
	public:
		void init();
		void show(String message);
		void debug(String message);
};
