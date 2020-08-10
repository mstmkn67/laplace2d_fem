#ifndef _SHAPE_FUNC_2D_H_
#define _SHAPE_FUNC_2D_H_

#include "../integral/Integral2d.h"

class ShapeFunc2d{
public:
	ShapeFunc2d(Integral2d* integral);
	virtual ~ShapeFunc2d();
	double* N;
	double* dN;
	Integral2d* integral;
};

class ShapeTriangle:public ShapeFunc2d{
public:
	ShapeTriangle(IntegralTriangle* integral);
	virtual ~ShapeTriangle();
};

class ShapeTetragon:public ShapeFunc2d{
public:
	ShapeTetragon(IntegralTetragon* integral);
	virtual ~ShapeTetragon();
};

#endif // _SHAPE_FUNC_2D_H_
