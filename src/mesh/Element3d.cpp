#include "Element3d.h"

map<int,ShapeFunc3d*> Element3d::shape;
map<int,Integral3d*> Element3d::integral;

Element3d::Element3d(int n):np(n){
	vertex=new Vertex3d*[np];
	stiff=new double[np*np];
	mass=new double[np*np];
	force=new double[np];
}
Element3d::~Element3d(){
	delete[] force;
	delete[] mass;
	delete[] stiff;
	delete[] vertex;
}
Tensor3x3 Element3d::getJacobiInv(const Vector3d& xi){
	return getJacobi(xi).invert();
}
double Element3d::getJacobiDet(const Vector3d& xi){
	return getJacobi(xi).det();
}
void Element3d::getJacobiInvDet(const Vector3d& xi,Tensor3x3& j,double& J){
	j=getJacobiInv(xi);
	J=getJacobi(xi).det();
}
void Element3d::coef(){
	for(int j=0;j<np;j++){
		for(int i=0;i<np;i++){
			stiff[np*j+i]=0.0;
			mass[np*j+i]=0.0;
		}
		force[j]=0.0;
	}
	int inp=integral[np]->n;
	double dNt[3*np];
	for(int i=0;i<inp;i++){
		Tensor3x3 ja;double J;
		getJacobiInvDet(integral[np]->xi[i],ja,J);
		//stiff matrix
		for(int j=0;j<np;j++){
			dNt[0*np+j]=ja.x.x*shape[np]->dN[np*3*i+0*np+j]+ja.x.y*shape[np]->dN[np*3*i+1*np+j]+ja.x.z*shape[np]->dN[np*3*i+2*np+j];
			dNt[1*np+j]=ja.y.x*shape[np]->dN[np*3*i+0*np+j]+ja.y.y*shape[np]->dN[np*3*i+1*np+j]+ja.y.z*shape[np]->dN[np*3*i+2*np+j];
			dNt[2*np+j]=ja.z.x*shape[np]->dN[np*3*i+0*np+j]+ja.z.y*shape[np]->dN[np*3*i+1*np+j]+ja.z.z*shape[np]->dN[np*3*i+2*np+j];
		}
		for(int j=0;j<np;j++){
			for(int k=0;k<np;k++){
				stiff[np*j+k]+=integral[np]->we[i]*(dNt[0*np+j]*dNt[0*np+k]+dNt[1*np+j]*dNt[1*np+k]+dNt[2*np+j]*dNt[2*np+k])*J;
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
Tetrahedron::Tetrahedron():Element3d(4){}
Tetrahedron::Tetrahedron(Vertex3d** v):Element3d(4){
	for(int i=0;i<4;i++)vertex[i]=v[i];
}
Tetrahedron::~Tetrahedron(){}
Tensor3x3 Tetrahedron::getJacobi(const Vector3d& xi){
	const Vector3d& r0=vertex[0]->pos;
	const Vector3d& r1=vertex[1]->pos;
	const Vector3d& r2=vertex[2]->pos;
	const Vector3d& r3=vertex[3]->pos;
	return Tensor3x3(r1.x-r0.x, r1.y-r0.y, r1.z-r0.z,
	                 r2.x-r0.x, r2.y-r0.y, r2.z-r0.z,
	                 r3.x-r0.x, r3.y-r0.y, r3.z-r0.z);
}
//
Hexahedron::Hexahedron():Element3d(8){}
Hexahedron::Hexahedron(Vertex3d** v):Element3d(8){
	for(int i=0;i<8;i++)vertex[i]=v[i];
}
Hexahedron::~Hexahedron(){}
Tensor3x3 Hexahedron::getJacobi(const Vector3d& xi){
	const Vector3d& r0=vertex[0]->pos;const Vector3d& r1=vertex[1]->pos;
	const Vector3d& r2=vertex[2]->pos;const Vector3d& r3=vertex[3]->pos;
	const Vector3d& r4=vertex[4]->pos;const Vector3d& r5=vertex[5]->pos;
	const Vector3d& r6=vertex[6]->pos;const Vector3d& r7=vertex[7]->pos;
	double a1=1.+xi.x,a2=1.-xi.x, b1=1.+xi.y,b2=1.-xi.y, c1=1.+xi.z,c2=1.-xi.z;
	double m00=0.125*(-b2*c2*r0.x+b2*c2*r1.x+b1*c2*r2.x-b1*c2*r3.x-b2*c1*r4.x+b2*c1*r5.x+b1*c1*r6.x-b1*c1*r7.x);
	double m01=0.125*(-b2*c2*r0.y+b2*c2*r1.y+b1*c2*r2.y-b1*c2*r3.y-b2*c1*r4.y+b2*c1*r5.y+b1*c1*r6.y-b1*c1*r7.y);
	double m02=0.125*(-b2*c2*r0.z+b2*c2*r1.z+b1*c2*r2.z-b1*c2*r3.z-b2*c1*r4.z+b2*c1*r5.z+b1*c1*r6.z-b1*c1*r7.z);//
	double m10=0.125*(-a2*c2*r0.x-a1*c2*r1.x+a1*c2*r2.x+a2*c2*r3.x-a2*c1*r4.x-a1*c1*r5.x+a1*c1*r6.x+a2*c1*r7.x);
	double m11=0.125*(-a2*c2*r0.y-a1*c2*r1.y+a1*c2*r2.y+a2*c2*r3.y-a2*c1*r4.y-a1*c1*r5.y+a1*c1*r6.y+a2*c1*r7.y);
	double m12=0.125*(-a2*c2*r0.z-a1*c2*r1.z+a1*c2*r2.z+a2*c2*r3.z-a2*c1*r4.z-a1*c1*r5.z+a1*c1*r6.z+a2*c1*r7.z);//
	double m20=0.125*(-a2*b2*r0.x-a1*b2*r1.x-a1*b1*r2.x-a2*b1*r3.x+a2*b2*r4.x+a1*b2*r5.x+a1*b1*r6.x+a2*b1*r7.x);
	double m21=0.125*(-a2*b2*r0.y-a1*b2*r1.y-a1*b1*r2.y-a2*b1*r3.y+a2*b2*r4.y+a1*b2*r5.y+a1*b1*r6.y+a2*b1*r7.y);
	double m22=0.125*(-a2*b2*r0.z-a1*b2*r1.z-a1*b1*r2.z-a2*b1*r3.z+a2*b2*r4.z+a1*b2*r5.z+a1*b1*r6.z+a2*b1*r7.z);
	return Tensor3x3(m00,m01,m02,
	                 m10,m11,m12,
	                 m20,m21,m22);
}
//
Prism::Prism():Element3d(6){}
Prism::Prism(Vertex3d** v):Element3d(6){
	for(int i=0;i<6;i++)vertex[i]=v[i];
}
Prism::~Prism(){}
Tensor3x3 Prism::getJacobi(const Vector3d& xi){
	const Vector3d& r0=vertex[0]->pos;const Vector3d& r1=vertex[1]->pos;
	const Vector3d& r2=vertex[2]->pos;const Vector3d& r3=vertex[3]->pos;
	const Vector3d& r4=vertex[4]->pos;const Vector3d& r5=vertex[5]->pos;
	double l=1.-xi.x-xi.y,a=0.5*(1.-xi.z),b=0.5*(1.+xi.z);
	return Tensor3x3(-a*r0.x+a*r1.x-b*r3.x+b*r4.x,
	                 -a*r0.y+a*r1.y-b*r3.y+b*r4.y,
	                 -a*r0.z+a*r1.z-b*r3.z+b*r4.z,//
	                 -a*r0.x+a*r2.x-b*r3.x+b*r5.x,
	                 -a*r0.y+a*r2.y-b*r3.x+b*r5.y,
	                 -a*r0.z+a*r2.z-b*r3.x+b*r5.z,//
	                 -0.5*l*r0.x-0.5*xi.x*r1.x-0.5*xi.y*r2.x+0.5*l*r3.x+0.5*xi.x*r4.x+0.5*xi.y*r5.x,
	                 -0.5*l*r0.y-0.5*xi.x*r1.y-0.5*xi.y*r2.y+0.5*l*r3.y+0.5*xi.x*r4.y+0.5*xi.y*r5.y,
	                 -0.5*l*r0.z-0.5*xi.x*r1.z-0.5*xi.y*r2.z+0.5*l*r3.z+0.5*xi.x*r4.z+0.5*xi.y*r5.z);
}
