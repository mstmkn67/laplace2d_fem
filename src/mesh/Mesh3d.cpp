#include "Mesh3d.h"

Mesh3d::Mesh3d(){
	Element3d::integral[4]=new IntegralTetrahedron(400);
	Element3d::integral[6]=new IntegralPrism(4,400);
	Element3d::integral[8]=new IntegralHexahedron(400);
	Element3d::shape[4]=new ShapeTetrahedron((IntegralTetrahedron*)(Element3d::integral[4]));
	Element3d::shape[6]=new ShapePrism((IntegralPrism*)(Element3d::integral[6]));
	Element3d::shape[8]=new ShapeHexahedron((IntegralHexahedron*)(Element3d::integral[8]));
}

Mesh3d::~Mesh3d(){
	map<int,Integral3d*>::iterator i=Element3d::integral.begin();
	for(;i!=Element3d::integral.end();i++){
		delete i->second;
	}
	map<int,ShapeFunc3d*>::iterator j=Element3d::shape.begin();
	for(;j!=Element3d::shape.end();j++){
		delete j->second;
	}
}

void Mesh3d::adjacent(){
	vector<Element3d*>::iterator i=element.begin();
	for(;i!=element.end();i++){
		for(int j=0;j<(*i)->np;j++){
			(*i)->vertex[j]->element.push_back(*i);
		}
	}
}

void Mesh3d::equation_number(){
	int n=0;
	vector<Vertex3d*>::iterator v=vertex.begin();
	for(;v!=vertex.end();v++){
		if((*v)->eqn!=-1){
			(*v)->eqn=n;
			n++;
		}
	}
	nequation=n;
}


void Mesh3d::coef(){
	vector<Element3d*>::iterator i=element.begin();
	for(;i!=element.end();i++){
		(*i)->coef();
	}
}

