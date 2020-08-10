#ifndef _INTEGRAL1D_H_
#define _INTEGRAL1D_H_

#include <iostream>
#include <cmath>
using namespace std;

class Integral1d{
public:
	Integral1d(int type);
	virtual ~Integral1d();
	//
	int n;
	double* we;
	double* xi;
};


#endif // _INTEGRAL1D_H_
