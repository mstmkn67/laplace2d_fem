#ifndef _LAPLACE_REGION2D_H_
#define _LAPLACE_REGION2D_H_

#include "mesh/Region2d.h"

class LaplaceRegion2d:public Region2d{
public:
	LaplaceRegion2d(){};
	virtual ~LaplaceRegion2d(){};
	char type;
	double value;
private:
};

#endif // _LAPLACE_REGION2D_H_
