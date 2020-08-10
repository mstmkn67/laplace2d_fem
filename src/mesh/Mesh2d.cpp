#include "Mesh2d.h"

Mesh2d::Mesh2d(){
	Element2d::integral[3]=new IntegralTriangle(400);
	Element2d::integral[4]=new IntegralTetragon(400);
	Element2d::shape[3]=new ShapeTriangle((IntegralTriangle*)(Element2d::integral[3]));
	Element2d::shape[4]=new ShapeTetragon((IntegralTetragon*)(Element2d::integral[4]));
}

Mesh2d::~Mesh2d(){
	for(auto j=Element2d::shape.begin();j!=Element2d::shape.end();j++){
		delete j->second;
	}
	for(auto i=Element2d::integral.begin();i!=Element2d::integral.end();i++){
		//delete i->second;/////////////ここの開放がうまくいかない。
	}
}

void Mesh2d::adjacent(){
	vector<Element2d*>::iterator i=element.begin();
	for(;i!=element.end();i++){
		for(int j=0;j<(*i)->np;j++){
			(*i)->vertex[j]->element.push_back(*i);
		}
	}
}

void Mesh2d::equation_number(){
	int n=0;
	vector<Vertex2d*>::iterator v=vertex.begin();
	for(;v!=vertex.end();v++){
		if((*v)->eqn!=-1){
			(*v)->eqn=n;
			n++;
		}
	}
	nequation=n;
}

void Mesh2d::coef(){
	vector<Element2d*>::iterator i=element.begin();
	for(;i!=element.end();i++){
		(*i)->coef();
	}
}


