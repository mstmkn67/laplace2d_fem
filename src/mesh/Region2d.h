#ifndef _REGION2D_H_
#define _REGION2D_H_

#include "Vertex2d.h"

class Region2d{
public:
	Region2d(){}
	virtual ~Region2d(){}
	vector<Vertex2d*> vertex;
};

#endif // _REGION2D_H_
