#ifndef _MESH_2D_H_
#define _MESH_2D_H_

#include <vector>
using namespace std;
#include "Vertex2d.h"
#include "Element2d.h"
#include "Region2d.h"


class Mesh2d{
public:
	Mesh2d();
	virtual ~Mesh2d();
	virtual void adjacent();
	virtual void equation_number();
	virtual void coef();
	int nequation;
	vector<Vertex2d*> vertex;
	vector<Element2d*> element;
	vector<Region2d*> region;
};

#endif // _MESH_H_
