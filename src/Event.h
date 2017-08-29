#include <Arduino.h>
#include <vector>
#include <functional>

using namespace std;

class Event {
	public:
		 void on(std::function<void()> c, int event);
		 void emit(int event);
	protected:
		vector < pair<function<void()>, int> >  callbacks;
};