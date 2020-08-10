#include "Integral1d.h"

Integral1d::Integral1d(int type){
	n=type;
	we=new double[n]; xi=new double[n];
	switch(type){
		case 1:
			xi[0]=0.0;
			we[0]=2.0;
			break;
		case 2:
			xi[0]=-1.0/sqrt(3.0);xi[1]=-xi[0];
			we[0]=1.0;we[1]=1.0;
			break;
		case 3:
			xi[0]=0.0;xi[1]=-sqrt(0.6);xi[2]=-xi[1];
			we[0]=8./9.;we[1]=5./9.;we[2]=5./9.;
			break;
		case 4:
			xi[0]=-sqrt((3.-2.*sqrt(6./5.))/7.);xi[1]=-xi[0];
			xi[2]=-sqrt((3.+2.*sqrt(6./5.))/7.);xi[3]=-xi[2];
			we[0]=0.5+1./6./sqrt(1.2);we[1]=we[0];
			we[2]=0.5-1./6./sqrt(1.2);we[3]=we[2];
			break;
		case 5:
			xi[0]=0.0;
			xi[1]=-sqrt(5.-4.*sqrt(5./14.))/3.;xi[2]=-xi[1];
			xi[3]=-sqrt(5.+4.*sqrt(5./14.))/3.;xi[4]=-xi[3];
			we[0]=128./225.;
			we[1]=161./450.+13./180./sqrt(5./14.);we[2]=we[1];
			we[3]=161./450.-13./180./sqrt(5./14.);we[4]=we[3];
			break;
		case 6:
			xi[0]=-0.238619186083197;xi[1]=-xi[0];
			xi[2]=-0.661209386466265;xi[3]=-xi[2];
			xi[4]=-0.932469514203152;xi[5]=-xi[4];
			we[0]=0.467913934572691;we[1]=we[0];
			we[2]=0.360761573048139;we[3]=we[2];
			we[4]=0.171324492379170;we[5]=we[4];
			break;
		case 7:
			xi[0]=0.0;
			xi[1]=-0.405845151377397;xi[2]=-xi[1];
			xi[3]=-0.741531185599394;xi[4]=-xi[3];
			xi[5]=-0.949107912342759;xi[6]=-xi[5];
			we[0]=0.417959183673469;
			we[1]=0.381830050505119;we[2]=we[1];
			we[3]=0.279705391489277;we[4]=we[3];
			we[5]=0.129484966168870;we[6]=we[5];
			break;
		default:
			cout << "Integral1d error!" << endl;
			cout << type << " is not implemented." << endl;
			exit(1);
			break;
	}
}

Integral1d::~Integral1d(){
	delete[] we; delete[] xi;
}
