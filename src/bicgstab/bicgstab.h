// Iterative template routine -- BiCGSTAB
//
// BiCGSTAB solves the unsymmetric linear system Ax = b 
// using the Preconditioned BiConjugate Gradient Stabilized method
//
#ifndef _BICGSTAB_H_
#define _BICGSTAB_H_

#include <cmath>
#include <iostream>
using namespace std;

class BiCGSTAB{
public:
	BiCGSTAB(int N,double* x,double* b,int max_ite,double tol);
	virtual ~BiCGSTAB();
	
	virtual int update();
	
	virtual void matvec(double alpha,double* xx,double beta,double* yy)=0;
	virtual void psolve(double* xx,double* bb)=0;
	
	int N;
	double* x;
	double* b;
	double* work;
	int max_iter;//update後に、最大の繰り返しすうが出力(updateを行なうときに元の値_max_iterに戻される)
	double tol;
	const double _tol;const int _max_iter;
	//temporary
	double resid;
protected:
	double get_norm(double *x);
	double inner_product( double *x1, double *x2);
	int array_copy( double* destArray, double* srcArray);
private:
	
};

#endif // _BICGSTAB_H_
