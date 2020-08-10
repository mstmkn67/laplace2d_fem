#ifndef _VERTEX_3D_H_
#define _VERTEX_3D_H_
class Element3d;

#include "../coord/Vector3d.h"

class Vertex3d{
public:
	Vertex3d():eqn(0){}
	Vertex3d(const Vector3d& r):pos(r),eqn(0){}
	vector<Element3d*> element;
	int eqn;
	Vector3d pos;
};


#endif // _VERTEX_3D_H_
