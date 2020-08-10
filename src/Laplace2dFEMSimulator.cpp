#include "Laplace2dFEMSimulator.h"

Laplace2dFEMSimulator::Laplace2dFEMSimulator(UDFManager* i,UDFManager* o)
:in(i),out(o){
	timer=new Timer();
	timer->start();
}

Laplace2dFEMSimulator::~Laplace2dFEMSimulator(){
	delete fem;
	for(auto r:mesh->region)delete r;
	for(auto e:mesh->element)delete e;
	for(auto v:mesh->vertex)delete v;
	delete mesh;
	delete timer;
}

void Laplace2dFEMSimulator::update(){
	//precondition
	input_mesh();
	mesh->adjacent();
	input_region();
	mesh->equation_number();
	input_fem();
	//
	mesh->coef();
	//
	fem->update();
	//
	output();
}

void Laplace2dFEMSimulator::input_mesh(){
	mesh=new Mesh2d;
	Location vloc("input.vertex[]");
	for(int i=0;i<in->size(vloc);i++){
		vloc.next();
		Vector2d r(in->d(vloc.sub("position.x")),in->d(vloc.sub("position.y")));
		mesh->vertex.push_back(new LaplaceVertex2d(r));
	}
	cout << "number of vertices: " << mesh->vertex.size() << endl;
	Location eloc("input.element[]");
	for(int i=0;i<in->size(eloc);i++){
		eloc.next();
		vector<int> v=in->iarray(eloc.sub("vertex[]"));
		if(in->size(eloc.sub("vertex[]"))==3){
			int id0=in->getLocation("Vertex",v[0]).getIndex().get()[0];
			int id1=in->getLocation("Vertex",v[1]).getIndex().get()[0];
			int id2=in->getLocation("Vertex",v[2]).getIndex().get()[0];
			Vertex2d* vertex[3];
			vertex[0]=mesh->vertex[id0];vertex[1]=mesh->vertex[id1];
			vertex[2]=mesh->vertex[id2];
			mesh->element.push_back(new Triangle(vertex));
		}else if(in->size(eloc.sub("vertex[]"))==4){
			int id0=in->getLocation("Vertex",v[0]).getIndex().get()[0];
			int id1=in->getLocation("Vertex",v[1]).getIndex().get()[0];
			int id2=in->getLocation("Vertex",v[2]).getIndex().get()[0];
			int id3=in->getLocation("Vertex",v[3]).getIndex().get()[0];
			Vertex2d* vertex[4];
			vertex[0]=mesh->vertex[id0];vertex[1]=mesh->vertex[id1];
			vertex[2]=mesh->vertex[id2];vertex[3]=mesh->vertex[id3];
			mesh->element.push_back(new Tetragon(vertex));
		}
	}
	cout << "number of elements: " << mesh->element.size() << endl;
}

void Laplace2dFEMSimulator::input_region(){
	Location rloc("input.region[]");
	for(int i=0;i<in->size(rloc);i++){
		rloc.next();
		LaplaceRegion2d* region=new LaplaceRegion2d;
		string t=in->s(rloc.sub("type"));
		if(t=="phi"){
			region->type='p';
			region->value=in->d(rloc.sub("phi"));
		}else if(t=="q"){
			region->type='q';
			region->value=in->d(rloc.sub("q"));
		}
		vector<int> v=in->iarray(rloc.sub("vertex[]"));
		vector<int>::iterator j=v.begin();
		for(;j!=v.end();j++){
			int id=in->getLocation("Vertex",*j).getIndex().get()[0];
			region->vertex.push_back(mesh->vertex[id]);
			if(t=="phi"){
				mesh->vertex[id]->eqn=-1;
				((LaplaceVertex2d*)(mesh->vertex[id]))->phi=in->d(rloc.sub("phi"));
			}
		}
		mesh->region.push_back(region);
	}
	cout << "number of regions: " << mesh->region.size() << endl;
}

void Laplace2dFEMSimulator::input_fem(){
	int i=in->i("input.bicgstab.max_iteration");
	double d=in->d("input.bicgstab.tolerance");
	fem=new LaplaceFEM2d(mesh,i,d);
}

void Laplace2dFEMSimulator::output(){
	Location loc("output.vertex[]");
	vector<Vertex2d*>::iterator v=mesh->vertex.begin();
	for(;v!=mesh->vertex.end();v++){
		loc.next();
		out->put(loc.sub("phi"),((LaplaceVertex2d*)(*v))->phi);
	}
	out->put("output.solver.iteration",fem->get_iteration());
	out->put("output.solver.tolerance",fem->get_precision());
	out->put("output.time",timer->get());
	out->write();
}
