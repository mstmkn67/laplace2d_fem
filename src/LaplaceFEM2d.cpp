#include "LaplaceFEM2d.h"

LaplaceFEM2d::LaplaceFEM2d(Mesh2d* m,int mi,double p)
:mesh(m),maxite(mi),precision(p){
	ad.reserve(mesh->nequation);
	lnd.reserve(mesh->nequation);
}

LaplaceFEM2d::~LaplaceFEM2d(){
	delete[] b;
}

void LaplaceFEM2d::update(){
	lhs();
	rhs();
	solve();
}

void LaplaceFEM2d::lhs(){
	vector<Vertex2d*>::iterator v=mesh->vertex.begin();
	for(;v!=mesh->vertex.end();v++){
		int in=(*v)->eqn;
		if(in==-1)continue;
		map<int,double> aa;//transient matrix coef in *v
		vector<Element2d*>::iterator e=(*v)->element.begin();
		for(;e!=(*v)->element.end();e++){
			int i=0;// number of *v in element *e
			for(;i<(*e)->np;i++){
				Vertex2d* v2=(*e)->vertex[i];
				if(*v==v2)break;
			}
			//
			for(int j=0;j<(*e)->np;j++){
				if((*e)->vertex[j]->eqn==-1){
					continue;
				}
				int jn=(*e)->vertex[j]->eqn;
				if(aa.find(jn)==aa.end()){
					aa[jn] =(*e)->stiff[i*(*e)->np+j];
				}else{
					aa[jn]+=(*e)->stiff[i*(*e)->np+j];
				}
			}
		}
		//
		lnd.push_back(aa.size()-1);
		map<int,double>::iterator i=aa.begin();
		for(;i!=aa.end();i++){
			if(in==i->first){
				ad.push_back(i->second);//diagonal coef
			}else{
				alu.push_back(i->second);//non diagonal coef
				lnt.push_back(i->first);
			}
		}
	}
}

void LaplaceFEM2d::rhs(){
	b=new double[mesh->nequation];
	for(int i=0;i<mesh->nequation;i++)b[i]=0.0;//zero reset
	vector<Region2d*>::iterator r=mesh->region.begin();
	for(;r!=mesh->region.end();r++){
		//Dirichlet
		if(((LaplaceRegion2d*)(*r))->type=='p'){
			double phi=((LaplaceRegion2d*)(*r))->value;
			vector<Vertex2d*>::iterator v=(*r)->vertex.begin();
			for(;v!=(*r)->vertex.end();v++){
				vector<Element2d*>::iterator e=(*v)->element.begin();
				for(;e!=(*v)->element.end();e++){
					int j=0;
					for(;j<(*e)->np;j++){
						if((*v)==(*e)->vertex[j])break;
					}
					for(int i=0;i<(*e)->np;i++){
						int in=(*e)->vertex[i]->eqn;
						if(in==-1)continue;
						b[in]+=-(*e)->stiff[i*(*e)->np+j]*phi;
					}
				}
			}
			//}
		}
		//Neuman
		if(((LaplaceRegion2d*)(*r))->type=='q'){
			double q=((LaplaceRegion2d*)(*r))->value;
			vector<Vertex2d*>::iterator v=(*r)->vertex.begin();
			for(;v!=(*r)->vertex.end();v++){
				double a=0.0;
				vector<Element2d*>::iterator e=(*v)->element.begin();
				for(;e!=(*v)->element.end();e++){
					for(int i=0;i<(*e)->np;i++){
						if(*v!=(*e)->vertex[i] &&
						  find((*r)->vertex.begin(),(*r)->vertex.end(),*v)!=(*r)->vertex.end()){
						  a+=0.5*q*((*v)->pos-(*e)->vertex[i]->pos).length();
						}
					}
				}
				b[(*v)->eqn]+=a;
			}
		}
	}
}

void LaplaceFEM2d::solve(){
	double* x=new double[mesh->nequation];
	for(int i=0;i<mesh->nequation;i++)x[i]=0.0;//zero reset
	Solver* solver=new Solver(mesh->nequation,x,b,maxite,precision,&ad,&alu,&lnd,&lnt);
	solver->update();
	int index=0;
	vector<Vertex2d*>::iterator v=mesh->vertex.begin();
	for(;v!=mesh->vertex.end();v++){
		 if((*v)->eqn==-1)continue;
		 ((LaplaceVertex2d*)(*v))->phi=x[index];
		 index++;
	}
	maxite=solver->max_iter;
	precision=solver->tol;
	delete solver;
	delete[] x;
}

int LaplaceFEM2d::get_iteration(){
	return maxite;
}

double LaplaceFEM2d::get_precision(){
	return precision;
}

//////////////////////////////////////////////
Solver::Solver(int n,double* x,double* b,int max_ite,double tol,
	vector<double>* _ad,vector<double>* _alu,vector<int>* _lnd,vector<int>* _lnt)
:BiCGSTAB(n,x,b,max_ite,tol),ad(_ad),alu(_alu),lnd(_lnd),lnt(_lnt){
}

Solver::~Solver(){
}

void Solver::matvec(double alpha,double* xx,double beta,double* yy){
	for(int i=0;i<N;i++)yy[i]=beta*yy[i];
	int index=0;
	for(int i=0;i<N;i++){
		yy[i]+=alpha*(*ad)[i]*xx[i];
		for(int j=0;j<(*lnd)[i];j++){
			yy[i]+=alpha*(*alu)[index]*xx[(*lnt)[index]];
			index++;
		}
	}
}

void Solver::psolve(double* xx,double* bb){
	for(int i=0;i<N;i++){
		xx[i]=bb[i];
	}
}
