#ifndef _ELEMENT_3D_H_
#define _ELEMENT_3D_H_

#include <map>
#include <iostream>
using namespace std;
#include "../coord/Tensor3x3.h"
#include "Vertex3d.h"
#include "ShapeFunc3d.h"

class Element3d{
public:
	Element3d(int np);
	virtual ~Element3d();
	//
	virtual void coef();
	double* stiff;
	double* mass;
	double* force;
	//
	Vertex3d** vertex;
	double volume;
	int np;//4 --> Tetrahedron, 6--> Prism , 8 --> Hexahedron
	//before constructing element classes, below values should be assigned.
	static map<int,Integral3d*> integral;
	static map<int,ShapeFunc3d*> shape;
protected:
	virtual Tensor3x3 getJacobi(const Vector3d& xi)=0;
	virtual Tensor3x3 getJacobiInv(const Vector3d& xi);
	virtual double getJacobiDet(const Vector3d& xi);
	virtual void getJacobiInvDet(const Vector3d& xi,Tensor3x3& j,double& J);
};

class Tetrahedron:public Element3d{
public:
	Tetrahedron();
	Tetrahedron(Vertex3d** vertex);
	virtual ~Tetrahedron();
protected:
	virtual Tensor3x3 getJacobi(const Vector3d& xi);
};

class Hexahedron:public Element3d{
public:
	Hexahedron();
	Hexahedron(Vertex3d** vertex);
	virtual ~Hexahedron();
protected:
	virtual Tensor3x3 getJacobi(const Vector3d& xi);
};

class Prism:public Element3d{
public:
	Prism();
	Prism(Vertex3d** vertex);
	virtual ~Prism();
protected:
	virtual Tensor3x3 getJacobi(const Vector3d& xi);
};


#endif // _ELEMENT_3D_H_
