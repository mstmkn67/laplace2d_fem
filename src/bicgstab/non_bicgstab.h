#ifndef _NON_BICGSTAB_H_
#define _NON_BICGSTAB_H_

#include "bicgstab.h"

class NonBiCGSTAB:public BiCGSTAB{
public:
	NonBiCGSTAB(int N,double* A,double* x,double* b,int max_ite,double tol);
	virtual ~NonBiCGSTAB();
	
	virtual void matvec(double alpha,double* xx,double beta,double* yy);
	virtual void psolve(double* xx,double* bb);
private:
	double* A;
};

#endif // _NON_BICGSTAB_H_
