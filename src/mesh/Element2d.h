#ifndef _ELEMENT_2D_H_
#define _ELEMENT_2D_H_

#include <map>
#include <iostream>
using namespace std;
#include "../coord/Tensor2x2.h"
#include "Vertex2d.h"
#include "ShapeFunc2d.h"

class Element2d{
public:
	Element2d(int number_of_point);
	virtual ~Element2d();
	//
	virtual void coef();
	double* stiff;
	double* mass;
	double* force;
	//
	Vertex2d** vertex;
	double area;
	int np; //3 --> triangle, 4 --> tetragon
	//
	//before constructing element classes, below values should be assigned.
	static map<int,Integral2d*> integral;
	static map<int,ShapeFunc2d*> shape;
protected:
	virtual Tensor2x2 getJacobi(const Vector2d& xi)=0;
	virtual Tensor2x2 getJacobiInv(const Vector2d& xi);
	virtual double getJacobiDet(const Vector2d& xi);
	virtual void getJacobiInvDet(const Vector2d& xi,Tensor2x2& j,double& J);
};

class Triangle:public Element2d{
public:
	Triangle();
	Triangle(Vertex2d** vertex);
	virtual ~Triangle();
protected:
	//Jacobi matrix between original and normal coordinate
	virtual Tensor2x2 getJacobi(const Vector2d& xi);
	virtual Tensor2x2 getJacobiInv(const Vector2d& xi);
	virtual double getJacobiDet(const Vector2d& xi);
	virtual void getJacobiInvDet(const Vector2d& xi,Tensor2x2& j,double& J);
	//
	//static ShapeTriangle* shape;
	//static IntegralTriangle* integral;
};

class Tetragon:public Element2d{
public:
	Tetragon();
	Tetragon(Vertex2d** vertex);
	virtual ~Tetragon();
protected:
	//Jacobi matrix between original and normal coordinate
	virtual Tensor2x2 getJacobi(const Vector2d& xi);
	//
	//static ShapeTetragon* shape;
	//static IntegralTetragon* integral;
};

#endif // _ELEMENT_2D_H_
