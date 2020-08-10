#ifndef _MESH_3D_H_
#define _MESH_3D_H_

#include <vector>
using namespace std;
#include "Vertex3d.h"
#include "Element3d.h"
#include "Region3d.h"

class Mesh3d{
public:
	Mesh3d();
	virtual ~Mesh3d();
	virtual void adjacent();
	virtual void equation_number();
	virtual void coef();
	int nequation;
	vector<Vertex3d*> vertex;
	vector<Element3d*> element;
	vector<Region3d*> region;
};

#endif // _MESH_3D_H_
