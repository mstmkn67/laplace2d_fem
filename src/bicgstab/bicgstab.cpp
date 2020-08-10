#include "bicgstab.h"

BiCGSTAB::BiCGSTAB(int N_,double* x_,double* b_,int max_ite_,double tol_)
:N(N_),x(x_),b(b_),max_iter(max_ite_),_max_iter(max_ite_),tol(tol_),_tol(tol_){
	work=new double[N*7];
}

BiCGSTAB::~BiCGSTAB(){
	delete[] work;
}

int BiCGSTAB::update(){
	tol=_tol;max_iter=_max_iter;
	double rho_1,rho_2,alpha,beta,omega;
	int r=0*N,rtld=1*N,p=2*N,phat=3*N,v=4*N,shat=5*N,t=6*N,s=0*N;

	double normb = get_norm(b);
	matvec(-1.0,x,1.0,b);
	array_copy(&work[r],b);
	array_copy(&work[rtld],&work[r]);
	if(normb == 0.0)normb =1.0;
	if((resid = get_norm(&work[r]) / normb) <= tol) {
		tol = resid;
		max_iter = 0;
		return 0;
	}

	int i;
	for(i = 1; i <= max_iter; i++){
		rho_1=inner_product(&work[rtld],&work[r]);
		if(rho_1== 0){
			tol=get_norm(&work[r])/normb;
			return 2;
		}
		if(i == 1){
			array_copy(&work[p],&work[r]);
		}else {
			beta=(rho_1/rho_2) * (alpha/omega);
			#pragma omp parallel for
			for(int j=0; j < N; j++ ){
				work[p+j] = work[r+j] + beta*(work[p+j]-omega * work[v+j]);
			}
			//p = r + beta * (p - omega * v);
		}
		psolve(&work[phat],&work[p]);
		matvec(1.0,&work[phat],0.0,&work[v]);
		alpha = rho_1 / inner_product(&work[rtld],&work[v]);
		//s = r - alpha(0) * v;
		#pragma omp parallel for
		for(int j =0; j < N; j++){
			work[s+j]=work[r+j]-alpha*work[v+j];
		}
		if ((resid = get_norm(&work[s])/normb) < tol) {
			//x += alpha(0) * phat;
			#pragma omp parallel for
			for(int j = 0; j < N; j++){
				x[j] += alpha * work[phat+j];
			}
			tol = resid;
			max_iter = i;
			return 0;
		}
		psolve(&work[shat],&work[s]);
		matvec(1.0,&work[shat],0.0,&work[t]);
		omega=inner_product(&work[t],&work[s])/inner_product(&work[t],&work[t]);
		#pragma omp parallel for
		for(int j=0;j<N;j++){
			// x = x + alpha * p~ + omega * s^ 
			x[j]       = x[j]       + alpha * work[phat+j] + omega * work[shat+j];
			// r = s - omega * t
			work[r+j] = work[s+j] - omega * work[t+j];
		}
		rho_2=rho_1;
		if((resid = get_norm(&work[r]) / normb) < tol) {
			tol = resid;
			max_iter = i;
			return 0;
		}
		if(omega == 0) {
			tol = get_norm(&work[r]) / normb;
			return 3;
		}
	}
	tol = resid;
	return 1;
}

double BiCGSTAB::get_norm(double *x1){
	double norm = 0.0;
	#pragma omp parallel for reduction (+:norm)
	for(int i = 0; i < N; i++ ){
		norm += x1[i] * x1[i];
	}
	return sqrt(norm);
}

double BiCGSTAB::inner_product( double *x1, double *x2){
	double sum = 0.0;
	#pragma omp parallel for reduction (+:sum)
	for(int  i = 0; i < N; i++){
		sum += x1[i]*x2[i];
	}
	return sum;
}

int BiCGSTAB::array_copy( double* destArray, double* srcArray){
	#pragma omp parallel for
	for(int i=0; i<N; i++ ){ 
		destArray[i]=srcArray[i]; 
	}
	return 0;
}
