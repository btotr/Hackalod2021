#include <Arduino.h>
#include "AbstractView.h"

class SerialView : AbstractView {
	public:
		void init();
		void show(String message);
		void debug(String message);
};
