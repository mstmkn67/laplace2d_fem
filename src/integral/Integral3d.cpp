#include "Integral3d.h"

IntegralTetrahedron::IntegralTetrahedron(int type){
	n=type/100;
	we=new double[n]; xi=new Vector3d[n];
	double a,b,c,d;
	switch(type){
		case 400:
			a=sqrt(2./3.);
			b=1./sqrt(3.);
			xi[0].set(0.,-a,-b);
			xi[1].set(0., a,-b);
			xi[2].set(-a,0., b);
			xi[3].set( a,0., b);
			we[0]=we[1]=we[2]=we[3]=2.;
			break;
		case 600:
			a=1./sqrt(6.);
			b=1./sqrt(2.);
			c=1./sqrt(3.);
			d=sqrt(2./3.);
			xi[0].set( a, b,-c);
			xi[1].set( a,-b,-c);
			xi[2].set(-a, b, c);
			xi[3].set(-a,-b, c);
			xi[4].set(-d, 0,-c);
			xi[5].set( d, 0, c);
			we[0]=we[1]=we[2]=we[3]=we[4]=we[5]=4./3.;
			break;
		case 601:
			xi[0].set( 1, 0, 0);
			xi[1].set(-1, 0, 0);
			xi[2].set( 0, 1, 0);
			xi[3].set( 0,-1, 0);
			xi[4].set( 0, 0, 1);
			xi[5].set( 0, 0,-1);
			we[0]=we[1]=we[2]=we[3]=we[4]=we[5]=4./3.;
			break;
		case 1400:
			a=sqrt(19./30.);
			b=sqrt(19./33.);
			xi[0 ].set( a, 0, 0);xi[1 ].set(-a, 0, 0);
			xi[2 ].set( 0, a, 0);xi[3 ].set( 0,-a, 0);
			xi[4 ].set( 0, 0, a);xi[5 ].set( 0, 0,-a);
			xi[6 ].set(-b,-b,-b);xi[7 ].set( b,-b,-b);
			xi[8 ].set(-b, b,-b);xi[9 ].set( b, b,-b);
			xi[10].set(-b,-b, b);xi[11].set( b,-b, b);
			xi[12].set(-b, b, b);xi[13].set( b, b, b);
			we[0]=we[1]=we[2]=we[3]=we[4]=we[5]=320./361.;
			we[6]=we[7]=we[8]=we[9]=we[10]=we[11]=we[12]=we[13]=121./361.;
			break;
		default:
			cout << "IntegralTetrahedron error!" << endl;
			cout << type << " is not implemented." << endl;
			break;
	}
}
IntegralTetrahedron::~IntegralTetrahedron(){
	delete[] we; delete[] xi;
}
//
IntegralHexahedron::IntegralHexahedron(int type){
	n=type/100;
	we=new double[n]; xi=new Vector3d[n];
	double a,b,c;
	switch(type){
		case 100:
			xi[0].set(0.25,0.25,0.25);
			we[0]=1./6.;
			break;
		case 400:
			a=(5.-sqrt(5.))/20.;
			b=(5.+3.*sqrt(5.))/20.;
			xi[0].set(a,a,a);
			xi[1].set(a,a,b);
			xi[2].set(a,b,a);
			xi[3].set(b,a,a);
			we[0]=we[1]=we[2]=we[3]=1./24.;
			break;
		/*case 500:
			a=0.25,b=1./6.,0.5,c=;
			xi[0].set(a,a,a);
			xi[1].set(b,b,b);
			xi[2].set(b,b,c);
			xi[3].set(b,c,b);
			xi[3].set(c,b,b);
			we[0]=-2./15.;
			we[1]=we[2]=we[3]=we[4]=3./40.;
			break;*/
		default:
			cout << "IntegralHexahedron error!" << endl;
			cout << type << " is not implemented." << endl;
			break;
	}
}

IntegralHexahedron::~IntegralHexahedron(){
	delete[] we; delete[] xi;
}
//
IntegralPrism::IntegralPrism(int type_1d,int type_triangle){
	n=type_1d*type_triangle/100;
	we=new double[n];xi=new Vector3d[n];
	Integral1d* i1=new Integral1d(type_1d);
	IntegralTriangle* it=new IntegralTriangle(type_triangle);
	int s=0;
	for(int i=0;i<i1->n;i++){
		for(int j=0;j<it->n;j++){
			xi[s].set(it->xi[j].x,it->xi[j].y,i1->xi[i]);
			we[s]=it->we[j]*i1->we[i];
		}
	}
	delete it;
	delete i1;
}
IntegralPrism::~IntegralPrism(){
	delete[] we;delete[] xi;
}
