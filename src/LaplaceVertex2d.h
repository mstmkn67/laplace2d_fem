#ifndef _LAPLACE_VERTEX_2D_H_
#define _LAPLACE_VERTEX_2D_H_

class LaplaceVertex2d:public Vertex2d{
public:
	LaplaceVertex2d():phi(0.0){}
	LaplaceVertex2d(const Vector2d& r):Vertex2d(r),phi(0.0){}
	double phi;
	//double q;
};

#endif // _LAPLACE_VERTEX_2D_H_
