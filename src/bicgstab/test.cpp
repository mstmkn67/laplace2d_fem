#include "bicgstab.h"
#include <iostream>
using namespace std;

class Test:public BiCGSTAB{
public:
	Test(int N,double* x,double* b,int max_ite,double tol):BiCGSTAB(N,x,b,max_ite,tol){};
	virtual ~Test(){};
	virtual void matvec(double alpha,double* xx,double beta,double* yy){
		for(int i=0;i<N;i++){
			yy[i]=beta*yy[i];
			yy[i]+=alpha*((i+1)*xx[i]);
		}
	}
	virtual void psolve(double* xx,double* bb){
		for(int i=0;i<N;i++)xx[i]=bb[i];
	}
private:
};

int main(){
	double b[]={1.0,2.0,3.0};
	double x[]={0.0,0.0,0.0};
	Test test(3,x,b,100,1e-20);
	test.update();
	cout << x[0] << " " << x[1] << " " << x[2]  <<endl;
	return 0;
};

