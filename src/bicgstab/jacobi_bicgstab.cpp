#include "jacobi_bicgstab.h"

JacobiBiCGSTAB::JacobiBiCGSTAB(int N,double* A_,double* x,double* b,int max_ite,double tol)
:BiCGSTAB(N,x,b,max_ite,tol),A(A_){
}

JacobiBiCGSTAB::~JacobiBiCGSTAB(){
}
void JacobiBiCGSTAB::matvec(double alpha,double *xx,double beta,double* yy){
	#pragma omp parallel for
	for(int i=0;i<N;i++){
		yy[i]=beta*yy[i];
		for(int j=0;j<N;j++){
			yy[i]+=alpha*A[N*i+j]*xx[j];
		}
	}
}

void JacobiBiCGSTAB::psolve(double* xx,double* b){
	#pragma omp parallel for
	for(int i=0;i<N;i++){
		xx[i]=b[i]/A[N*i+i];
	}
}
