#include "Element2d.h"

map<int,ShapeFunc2d*> Element2d::shape;
map<int,Integral2d*> Element2d::integral;

Element2d::Element2d(int n):np(n){
	vertex=new Vertex2d*[np];
	stiff=new double[np*np];
	mass=new double[np*np];
	force=new double[np];
}
Element2d::~Element2d(){
	delete[] force;
	delete[] mass;
	delete[] stiff;
	delete[] vertex;
}
Tensor2x2 Element2d::getJacobiInv(const Vector2d& xi){
	return getJacobi(xi).invert();
}
double Element2d::getJacobiDet(const Vector2d& xi){
	return getJacobi(xi).det();
}
void Element2d::getJacobiInvDet(const Vector2d& xi,Tensor2x2& j,double& J){
	j=getJacobiInv(xi);
	J=getJacobi(xi).det();
}
void Element2d::coef(){
	//zero reset
	for(int j=0;j<np;j++){
		for(int i=0;i<np;i++){
			stiff[np*j+i]=0.0;
			mass[np*j+i]=0.0;
		}
		force[j]=0.0;
	}
	int inp=integral[np]->n;
	double dNt[2*np];
	for(int i=0;i<inp;i++){
		Tensor2x2 ja;double J;
		getJacobiInvDet(integral[np]->xi[i],ja,J);
		//stiff matrix
		for(int j=0;j<np;j++){
			dNt[0*np+j]=ja.x.x*shape[np]->dN[np*2*i+0*np+j]+ja.x.y*shape[np]->dN[np*2*i+1*np+j];
			dNt[1*np+j]=ja.y.x*shape[np]->dN[np*2*i+0*np+j]+ja.y.y*shape[np]->dN[np*2*i+1*np+j];
		}
		for(int j=0;j<np;j++){
			for(int k=0;k<np;k++){
				stiff[np*j+k]+=integral[np]->we[i]*(dNt[0*np+j]*dNt[0*np+k]+dNt[1*np+j]*dNt[1*np+k])*J;
			}
		}
		//mass matrix
		for(int j=0;j<np;j++){
			for(int k=0;k<np;k++){
				mass[np*j+k]+=integral[np]->we[i]*shape[np]->N[np*i+j]*shape[np]->N[np*i+k]*J;
			}
		}
		//force vector
		for(int j=0;j<np;j++){
			force[j]+=integral[np]->we[i]*shape[np]->N[np*i+j]*J;
		}
	}
}
//
Triangle::Triangle():Element2d(3){}
Triangle::Triangle(Vertex2d** v):Element2d(3){
	for(int i=0;i<3;i++)vertex[i]=v[i];
}
Triangle::~Triangle(){}
Tensor2x2 Triangle::getJacobi(const Vector2d& xi){
	const Vector2d& r0=vertex[0]->pos;
	const Vector2d& r1=vertex[1]->pos;
	const Vector2d& r2=vertex[2]->pos;
	return Tensor2x2(r1.x-r0.x, r1.y-r0.y,
	                 r2.x-r0.x, r2.y-r0.y);
}
Tensor2x2 Triangle::getJacobiInv(const Vector2d& xi){
	const Vector2d& r0=vertex[0]->pos;
	const Vector2d& r1=vertex[1]->pos;
	const Vector2d& r2=vertex[2]->pos;
	double det=(r1.x-r0.x)*(r2.y-r0.y)-(r2.x-r0.x)*(r1.y-r0.y);
	return Tensor2x2((r2.y-r0.y)/det, (r0.y-r1.y)/det,
	                 (r0.x-r2.x)/det, (r1.x-r0.x)/det);
}
double Triangle::getJacobiDet(const Vector2d& xi){
	const Vector2d& r0=vertex[0]->pos;
	const Vector2d& r1=vertex[1]->pos;
	const Vector2d& r2=vertex[2]->pos;
	return (r1.x-r0.x)*(r2.y-r0.y)-(r2.x-r0.x)*(r1.y-r0.y);
}
void Triangle::getJacobiInvDet(const Vector2d& xi,Tensor2x2& j,double& J){
	const Vector2d& r0=vertex[0]->pos;
	const Vector2d& r1=vertex[1]->pos;
	const Vector2d& r2=vertex[2]->pos;
	J=(r1.x-r0.x)*(r2.y-r0.y)-(r2.x-r0.x)*(r1.y-r0.y);
	j.set((r2.y-r0.y)/J, (r0.y-r1.y)/J,
	      (r0.x-r2.x)/J, (r1.x-r0.x)/J);
}
//
Tetragon::Tetragon():Element2d(4){}
Tetragon::Tetragon(Vertex2d** v):Element2d(4){
	for(int i=0;i<4;i++)vertex[i]=v[i];
}
Tetragon::~Tetragon(){}

Tensor2x2 Tetragon::getJacobi(const Vector2d& xi){
	const Vector2d& r0=vertex[0]->pos;const Vector2d& r1=vertex[1]->pos;
	const Vector2d& r2=vertex[2]->pos;const Vector2d& r3=vertex[3]->pos;
	return Tensor2x2(
		0.25*((-r0.x+r1.x+r2.x-r3.x)+xi.y*( r0.x-r1.x+r2.x-r3.x)),
		0.25*((-r0.y+r1.y+r2.y-r3.y)+xi.y*( r0.y-r1.y+r2.y-r3.y)),
		0.25*((-r0.x-r1.x+r2.x+r3.x)+xi.x*( r0.x-r1.x+r2.x-r3.x)),
		0.25*((-r0.y-r1.y+r2.y+r3.y)+xi.x*( r0.y-r1.y+r2.y-r3.y)));
}
