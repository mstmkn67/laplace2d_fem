#ifndef _LAPLACE2D_FEM_SIMULATOR_H_
#define _LAPLACE2D_FEM_SIMULATOR_H_

#include "udfmanager.h"
#include "mesh/Mesh2d.h"
#include "LaplaceVertex2d.h"
#include "LaplaceRegion2d.h"
#include "LaplaceFEM2d.h"
#include "utility/Timer.h"

class Laplace2dFEMSimulator{
public:
	Laplace2dFEMSimulator(UDFManager* in,UDFManager* out);
	virtual ~Laplace2dFEMSimulator();
	virtual void update();
protected:
	virtual void input_mesh();
	virtual void input_region();
	virtual void input_fem();
	virtual void output();
private:
	UDFManager* in;
	UDFManager* out;
	Mesh2d* mesh;
	Timer* timer;
	LaplaceFEM2d* fem;
};

#endif // _LAPLACE2D_FEM_SIMULATOR_H_
