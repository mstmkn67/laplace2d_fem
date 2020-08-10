#ifndef _INTEGRAL3D_H_
#define _INTEGRAL3D_H_

#include <iostream>
using namespace std;
#include "Integral1d.h"
#include "Integral2d.h"

class Integral3d{
public:
	int n;
	double* we; // weight
	Vector3d* xi; // general coordinate
};

class IntegralTetrahedron:public Integral3d{
public:
	IntegralTetrahedron(int type);
	virtual ~IntegralTetrahedron();
};

class IntegralHexahedron:public Integral3d{
public:
	IntegralHexahedron(int type);
	virtual ~IntegralHexahedron();
};

class IntegralPrism:public Integral3d{
public:
	IntegralPrism(int type_1d,int type_triangle);
	virtual ~IntegralPrism();
};


#endif // _INTEGRAL3D_H_
