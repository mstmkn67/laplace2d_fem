#ifndef _INTEGRAL2D_H_
#define _INTEGRAL2D_H_

#include <iostream>
using namespace std;
#include "../coord/Vector2d.h"

class Integral2d{
public:
	int n;
	double* we; // weight
	Vector2d* xi; // general coordinate
};

class IntegralTriangle:public Integral2d{
public:
	IntegralTriangle(int type);
	virtual ~IntegralTriangle();
};

class IntegralTetragon:public Integral2d{
public:
	IntegralTetragon(int type);
	virtual ~IntegralTetragon();
};

#endif // _INTEGRAL2D_H_
