#ifndef _JACOBI_BICGSTAB_H_
#define _JACOBI_BICGSTAB_H_

#include "bicgstab.h"

class JacobiBiCGSTAB:public BiCGSTAB{
public:
	JacobiBiCGSTAB(int N,double* A,double* x,double* b,int max_ite,double tol);
	virtual ~JacobiBiCGSTAB();
	
	virtual void matvec(double alpha,double* xx,double beta,double* yy);
	virtual void psolve(double* xx,double* bb);
private:
	double* A;
};

#endif // _JACOBI_BICGSTAB_H_
