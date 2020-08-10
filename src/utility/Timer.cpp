#include "Timer.h"

Timer::Timer(){
	start();
}

Timer::~Timer(){
}

double Timer::start(){
	time0=time(NULL);
	return 0.0;
}

double Timer::get()const{
	return difftime(time(NULL),time0);
}

ostream& operator << (ostream& os, const Timer& t)
{
	os << t.get();
	return os;
}
