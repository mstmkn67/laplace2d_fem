#ifndef _ILU_BICGSTAB_H_
#define _ILU_BICGSTAB_H_

#include "bicgstab.h"

class ILUBiCGSTAB:public BiCGSTAB{
public:
	ILUBiCGSTAB(int N,double* A,double* x,double* b,int max_ite,double tol);
	virtual ~ILUBiCGSTAB();
	
	virtual int update();
	
	virtual void matvec(double alpha,double* xx,double beta,double* yy);
	virtual void psolve(double* xx,double* bb);
protected:
	virtual void matrix_ILUdcmp();
private:
	double* A;
	double* val_LU;
	double* pivots;
};

#endif // _ILU_BICGSTAB_H_
