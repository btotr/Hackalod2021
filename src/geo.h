#include <string>
#include <Arduino.h>


class GEO {
	public:
		std::string locationToWGS84 ( int x, int y );
};
