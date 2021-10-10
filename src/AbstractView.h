#pragma once
#include <Arduino.h>

class AbstractView {
	public:
		void init();
		void show(String message);
		void debug(String message);
};
