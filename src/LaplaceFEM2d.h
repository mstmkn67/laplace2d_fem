#ifndef _LAPLACE_FEM2D_H_
#define _LAPLACE_FEM2D_H_

#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#include "mesh/Mesh2d.h"
#include "LaplaceVertex2d.h"
#include "LaplaceRegion2d.h"
#include "bicgstab/bicgstab.h"

class LaplaceFEM2d{
public:
	LaplaceFEM2d(Mesh2d* mesh,int maxite,double precision);
	virtual ~LaplaceFEM2d();
	virtual void update();
	virtual int get_iteration();
	virtual double get_precision();
protected:
	virtual void lhs();
	virtual void rhs();
	virtual void solve();
private:
	Mesh2d* mesh;
	//matrix
	vector<double> ad;
	vector<double> alu;
	vector<int> lnd;
	vector<int> lnt;
	//vector
	double *b;
	//
	int maxite;
	double precision;
	//
};

class Solver:public BiCGSTAB{
public:
	Solver(int n,double* x,double* b,int max_ite,double tol,
	       vector<double>* ad,vector<double>* alu,vector<int>* lnd,vector<int>* lnt);
	virtual ~Solver();
	virtual void matvec(double alpha,double* xx,double beta,double* yy);
	virtual void psolve(double* xx,double* bb);
private:
	vector<double>* ad;
	vector<double>* alu;
	vector<int>* lnd;
	vector<int>* lnt;
};

#endif // _LAPLACE_FEM2D_H_
