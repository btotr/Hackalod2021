#pragma once
#include <Arduino.h>

class AbstractView {
	public:
		void init();
		void printConnections(int connections);
		void debug(String message);
};