#ifndef _SHAPE_FUNC_3D_H_
#define _SHAPE_FUNC_3D_H_

#include "../integral/Integral3d.h"

class ShapeFunc3d{
public:
	ShapeFunc3d(Integral3d* integral);
	virtual ~ShapeFunc3d();
	double* N;
	double* dN;
	Integral3d* integral;
};

class ShapeTetrahedron:public ShapeFunc3d{
public:
	ShapeTetrahedron(IntegralTetrahedron* integral);
	virtual ~ShapeTetrahedron();
};

class ShapeHexahedron:public ShapeFunc3d{
public:
	ShapeHexahedron(IntegralHexahedron* integral);
	virtual ~ShapeHexahedron();
};

class ShapePrism:public ShapeFunc3d{
public:
	ShapePrism(IntegralPrism* integral);
	virtual ~ShapePrism();
};

#endif // _SHAPE_FUNC_3D_H_
