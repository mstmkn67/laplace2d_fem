#ifndef _REGION3D_H_
#define _REGION3D_H_

#include "Vertex3d.h"

class Region3d{
public:
	Region3d(){}
	virtual ~Region3d(){}
	vector<Vertex3d*> vertex;
};

#endif // _REGION3D_H_
