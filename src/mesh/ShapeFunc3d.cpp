#include "ShapeFunc3d.h"

ShapeFunc3d::ShapeFunc3d(Integral3d* in):integral(in){
}

ShapeFunc3d::~ShapeFunc3d(){
}

//

ShapeTetrahedron::ShapeTetrahedron(IntegralTetrahedron* inte):ShapeFunc3d(inte){
	int n=integral->n; //number of integral points
	N=new double[n*4];
	dN=new double[n*3*4];
	for(int i=0;i<n;i++){
		const Vector3d& xi=integral->xi[i];
		N[i*4+0]=1.-xi.x-xi.y-xi.z;N[i*4+1]=xi.x;N[i*4+2]=xi.y;N[i*4+3]=xi.z;
		dN[12*i+0*4+0]=-1.0;dN[12*i+0*4+1]= 1.0;dN[12*i+0*4+2]= 0.0;dN[12*i+0*4+3]= 0.0;//dN/dxi
		dN[12*i+1*4+0]=-1.0;dN[12*i+1*4+1]= 0.0;dN[12*i+1*4+2]= 1.0;dN[12*i+1*4+3]= 0.0;//dN/deta
		dN[12*i+2*4+0]=-1.0;dN[12*i+2*4+1]= 0.0;dN[12*i+2*4+2]= 0.0;dN[12*i+2*4+3]= 1.0;//dN/deta
	}
}
ShapeTetrahedron::~ShapeTetrahedron(){
	delete[] N;
	delete[] dN;
}
//
ShapeHexahedron::ShapeHexahedron(IntegralHexahedron* inte):ShapeFunc3d(inte){
	int n=integral->n; //number of integral points
	N=new double[n*8];
	dN=new double[n*3*8];
	for(int i=0;i<n;i++){
		const Vector3d& xi=integral->xi[i];
		double a1=1.+xi.x, a2=1.-xi.x;
		double b1=1.+xi.y, b2=1.-xi.y;
		double c1=1.+xi.z, c2=1.-xi.z;
		N[8*i+0]=0.125*a2*b2*c2;N[8*i+1]=0.125*a1*b2*c2;
		N[8*i+2]=0.125*a1*b1*c2;N[8*i+3]=0.125*a2*b1*c2;
		N[8*i+4]=0.125*a2*b2*c1;N[8*i+5]=0.125*a1*b2*c1;
		N[8*i+6]=0.125*a1*b1*c1;N[8*i+7]=0.125*a2*b1*c1;
		dN[24*i+0*8+0]=-0.125*b2*c2;dN[24*i+0*8+1]= 0.125*b2*c2;
		dN[24*i+0*8+2]= 0.125*b1*c2;dN[24*i+0*8+3]=-0.125*b1*c2;
		dN[24*i+0*8+4]=-0.125*b2*c1;dN[24*i+0*8+5]= 0.125*b2*c1;
		dN[24*i+0*8+6]= 0.125*b1*c1;dN[24*i+0*8+7]=-0.125*b1*c1;//dN/dxi
		dN[24*i+1*8+0]=-0.125*a2*c2;dN[24*i+1*8+1]=-0.125*a1*c2;
		dN[24*i+1*8+2]= 0.125*a1*c2;dN[24*i+1*8+3]= 0.125*a2*c2;
		dN[24*i+1*8+4]=-0.125*a2*c1;dN[24*i+1*8+5]=-0.125*a1*c1;
		dN[24*i+1*8+6]= 0.125*a1*c1;dN[24*i+1*8+7]= 0.125*a2*c1;//dN/deta
		dN[24*i+2*8+0]=-0.125*a2*b2;dN[24*i+2*8+1]=-0.125*a1*b2;
		dN[24*i+2*8+2]=-0.125*a1*b1;dN[24*i+2*8+3]=-0.125*a2*b1;
		dN[24*i+2*8+4]= 0.125*a2*b2;dN[24*i+2*8+5]= 0.125*a1*b2;
		dN[24*i+2*8+6]= 0.125*a1*b1;dN[24*i+2*8+7]= 0.125*a2*b1;//dN/dzeta
	}
}
ShapeHexahedron::~ShapeHexahedron(){
	delete[] N;
	delete[] dN;
}
//
ShapePrism::ShapePrism(IntegralPrism* inte):ShapeFunc3d(inte){
	int n=integral->n; //number of integral points
	N=new double[n*6];
	dN=new double[n*3*6];
	for(int i=0;i<n;i++){
		const Vector3d& xi=integral->xi[i];
		double l=1.-xi.x-xi.y, a=0.5*(1.-xi.z), b=0.5*(1.+xi.z);
		N[6*i+0]=l*a;   N[6*i+1]=xi.x*a;
		N[6*i+2]=xi.y*a;N[6*i+3]=l*b;
		N[6*i+4]=xi.x*b;N[6*i+5]=xi.y*b;
		dN[18*i+0*6+0]=-a;dN[18*i+0*6+1]= a;
		dN[18*i+0*6+2]= 0;dN[18*i+0*6+3]=-b;
		dN[18*i+0*6+4]= b;dN[18*i+0*6+5]= 0;//dN/dxi
		dN[18*i+1*6+0]=-a;dN[18*i+1*6+1]= 0;
		dN[18*i+1*6+2]= a;dN[18*i+1*6+3]=-b;
		dN[18*i+1*6+4]= 0;dN[18*i+1*6+5]= b;//dN/deta
		dN[18*i+2*6+0]=-0.5*l;   dN[18*i+2*6+1]=-0.5*xi.x;
		dN[18*i+2*6+2]=-0.5*xi.y;dN[18*i+2*6+3]= 0.5*l;
		dN[18*i+2*6+4]= 0.5*xi.x;dN[18*i+2*6+5]= 0.5*xi.y;//dN/dzeta
	}
}
ShapePrism::~ShapePrism(){
	delete[] N;
	delete[] dN;
}
