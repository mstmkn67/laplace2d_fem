#include "ShapeFunc2d.h"

ShapeFunc2d::ShapeFunc2d(Integral2d* in):integral(in){
}

ShapeFunc2d::~ShapeFunc2d(){
}

//

ShapeTriangle::ShapeTriangle(IntegralTriangle* inte):ShapeFunc2d(inte){
	int n=integral->n; //number of integral points
	N=new double[n*3];
	dN=new double[n*2*3];
	for(int i=0;i<n;i++){
		const Vector2d& xi=integral->xi[i];
		N[i*3+0]=1.-xi.x-xi.y;N[i*3+1]=xi.x;N[i*3+2]=xi.y;
		dN[6*i+0*3+0]=-1.0;dN[6*i+0*3+1]= 1.0;dN[6*i+0*3+2]= 0.0;//dN/dxi
		dN[6*i+1*3+0]=-1.0;dN[6*i+1*3+1]= 0.0;dN[6*i+1*3+2]= 1.0;//dN/deta
	}
}
ShapeTriangle::~ShapeTriangle(){
	delete[] N;
	delete[] dN;
}
//
ShapeTetragon::ShapeTetragon(IntegralTetragon* inte):ShapeFunc2d(inte){
	int n=integral->n; //number of integral points
	N=new double[n*4];
	dN=new double[n*2*4];
	for(int i=0;i<n;i++){
		const Vector2d& xi=integral->xi[i];
		N[4*i+0]=0.25*(1.-xi.x)*(1.-xi.y);N[4*i+1]=0.25*(1.+xi.x)*(1.-xi.y);
		N[4*i+2]=0.25*(1.+xi.x)*(1.+xi.y);N[4*i+3]=0.25*(1.-xi.x)*(1.+xi.y);
		dN[8*i+0*4+0]=0.25*(-1.+xi.y);dN[8*i+0*4+1]=0.25*( 1.-xi.y);
		dN[8*i+0*4+2]=0.25*( 1.+xi.y);dN[8*i+0*4+3]=0.25*(-1.-xi.y);//dN/dxi
		dN[8*i+1*4+0]=0.25*(-1.+xi.x);dN[8*i+1*4+1]=0.25*(-1.-xi.x);
		dN[8*i+1*4+2]=0.25*( 1.+xi.x);dN[8*i+1*4+3]=0.25*( 1.-xi.x);//dN/deta
	}
}
ShapeTetragon::~ShapeTetragon(){
	delete[] N;
	delete[] dN;
}
