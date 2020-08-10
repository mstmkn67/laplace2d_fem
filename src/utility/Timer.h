//Time.hƒNƒ‰ƒX

#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>
#include <iostream>
using namespace std;

class Timer{
public:
	Timer();
	virtual ~Timer();
	virtual double start();
	virtual double get()const;
private:
	time_t time0;//Å‰‚ÌŠÔ
};

ostream& operator << (ostream& os, const Timer& t);

#endif // _TIMER_H_
