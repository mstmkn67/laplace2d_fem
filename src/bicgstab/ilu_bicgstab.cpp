#include "ilu_bicgstab.h"

ILUBiCGSTAB::ILUBiCGSTAB(int N,double* A_,double* x,double* b,int max_ite,double tol)
:BiCGSTAB(N,x,b,max_ite,tol),A(A_){
	pivots=new double[N];
	val_LU=new double[N*N];
	#pragma omp parallel for
	for(int i=0;i<N;i++){
		pivots[i]=0.0;
		for(int j=0;j<N;j++){
			val_LU[i*N+j]=0.0;
		}
	}
}

ILUBiCGSTAB::~ILUBiCGSTAB(){
}


int ILUBiCGSTAB::update(){
	matrix_ILUdcmp();
	return BiCGSTAB::update();
}

void ILUBiCGSTAB::matrix_ILUdcmp(){
	int i,j,k,found;
	double element;
	#pragma omp parallel for
	for( i = 0; i < N; i++ ){ pivots[i] = A[i*(N+1)]; }
	#pragma omp parallel for
	for( i = 0; i < N; i++ ){
		pivots[i] = 1.0/pivots[i];
		for( j = i+1; j < N; j++ ){
			found = 1;
			for( k = 0; k < j; k++){
				if( k == i ){
					found = 0;
					element = A[j*N+k];
					break;
				}
			}
			if(found == 0){
				val_LU[j*(N+1)] = A[j*(N+1)] - element * pivots[i] * A[i*N+j] ;
			}
		}
	}
}

void ILUBiCGSTAB::matvec(double alpha,double *xx,double beta,double* yy){
	#pragma omp parallel for
	for(int i=0;i<N;i++){
		yy[i]=beta*yy[i];
		for(int j=0;j<N;j++){
			yy[i]+=alpha*A[N*i+j]*xx[j];
		}
	}
}

void ILUBiCGSTAB::psolve(double* xx,double* bb){
	int i,j;  double sum;
	#pragma omp parallel for
	for(i = 0; i < N; i++){
		sum = 0.0;
		for(j = 0; j < i; j++){
			sum += val_LU[i*N+j] * xx[j];
		}
		xx[i] = pivots[i] * (bb[i] - sum);
	}
	#pragma omp parallel for
	for(i = N-1; i >= 0; i--){
		sum = 0.0;
		for(j = i+1; j < N; j++){
			sum  += val_LU[i*N+j] * xx[j];
			xx[i] -= - pivots[i] * sum;
		}
	}
}
