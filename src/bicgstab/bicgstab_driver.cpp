#include <iostream>
using namespace std;
#include "ilu_bicgstab.h"
#include "jacobi_bicgstab.h"
#include "non_bicgstab.h"
//
//using subroutine bicgstab in templates, 
//the problem in the following python code is solved.
//
//from Numeric import *
//from LinearAlgebra import *
//A=array([[1.0, 0.1, 0.2, 0.3, 0.4],
//         [0.0, 1.0, 0.1, 0.1, 0.1],
//         [0.0, 0.0, 1.0, 0.1, 0.1],
//         [0.0, 0.0, 0.0, 1.0, 0.1],
//         [0.0, 0.0, 0.0, 0.0, 1.0]])
//b=array([1.0,2.0,3.0,4.0,5.0])
//print solve_linear_equations(A,b)


int main(){
	int N=5;
	double A[25]={
		1.0, 0.1, 0.2, 0.3, 0.4,
		0.0, 1.0, 0.1, 0.1, 0.1,
		0.0, 0.0, 1.0, 0.1, 0.1,
		0.0, 0.0, 0.0, 1.0, 0.1,
		0.0, 0.0, 0.0, 0.0, 1.0
	};
	double bb[5]={
		1.0,2.0,3.0,4.0,5.0
	};
	
	double* x=new double[N];
	for(int i=0;i<N;i++)x[i]=0.0;
	int iter=100;
	double resid=1e-20;
	
	BiCGSTAB* bicgstab=new NonBiCGSTAB(N,A,x,bb,iter,resid);
	//BiCGSTAB* bicgstab=new JacobiBiCGSTAB(N,A,x,bb,iter,resid);
	//BiCGSTAB* bicgstab=new ILUBiCGSTAB(N,A,x,bb,iter,resid);
	int info=bicgstab->update();
	cout << "info:" << info << endl;
	cout << "iter:" << bicgstab->max_iter << endl;
	cout << "resid:" << bicgstab->tol << endl;
	for(int i=0;i<N;i++){
		cout << x[i] << " ";
	}
	cout << endl;
	delete bicgstab;
	return 0;
}
