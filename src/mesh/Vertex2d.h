#ifndef _VERTEX_2D_H_
#define _VERTEX_2D_H_

#include "../coord/Vector2d.h"
class Element2d;

class Vertex2d{
public:
	Vertex2d():eqn(0){}
	Vertex2d(const Vector2d& r):pos(r),eqn(0){}
	vector<Element2d*> element;
	int eqn;
	Vector2d pos;
};

#endif // _VERTEX_2D_H_
