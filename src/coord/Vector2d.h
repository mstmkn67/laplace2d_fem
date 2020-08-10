//===== Vector2d.h ===========================================================

#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include <cmath>
#include <iostream>
using namespace std;

#include "Vector3d.h"

class Vector2d {
public:	
	double x, y;
	Vector2d(double vx = 0.0, double vy = 0.0):x(vx),y(vy){}
	Vector2d(const Vector2d& v):x(v.x),y(v.y){}
	Vector2d(const Vector3d& v):x(v.x),y(v.y){}//3d‚©‚ç2d‚Ì•ÏŠ·

	void set(double vx,double vy){x=vx;y=vy;}
	Vector2d& operator = (const Vector2d& v);
	friend Vector2d operator + (const Vector2d& v1, const Vector2d& v2);
	friend Vector2d operator - (const Vector2d& v1, const Vector2d& v2);
	Vector2d& operator += (const Vector2d& v);
	Vector2d& operator -= (const Vector2d& v);
	friend Vector2d operator * (const Vector2d& v, const double& s);
	friend Vector2d operator * (const double& s, const Vector2d &v);
	friend Vector2d operator / (const Vector2d& v, const double& s);
	Vector2d& operator *= (const double& s);
	Vector2d& operator /= (const double& s);

	friend double operator * (const Vector2d& v1, const Vector2d& v2);
	friend double operator ^ (const Vector2d& v1, const Vector2d& v2);

	Vector2d operator - () const;

	double length() const { return sqrt(x*x + y*y); }
	double length2() const { return x*x + y*y; }

	static void parenOn()	{ outputParen = true; }
	static void parenOff()	{ outputParen = false; }
	static bool parenIsOn()	{ return outputParen; }
private:
	static bool outputParen;
};

ostream& operator << (ostream& os, const Vector2d& v);
istream& operator >> (istream& is, Vector2d& v);

inline
Vector2d& Vector2d::operator = (const Vector2d& v)
{
	x = v.x; y = v.y;
	return *this;
}

inline
Vector2d operator + (const Vector2d& v1, const Vector2d& v2)
{
	return Vector2d(v1.x + v2.x, v1.y + v2.y);
}

inline
Vector2d operator - (const Vector2d& v1, const Vector2d& v2)
{
	return Vector2d(v1.x - v2.x, v1.y - v2.y);
}

inline
Vector2d& Vector2d::operator += (const Vector2d& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

inline
Vector2d& Vector2d::operator -= (const Vector2d& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

inline
Vector2d operator * (const Vector2d& v, const double& s)
{
	return Vector2d(s*v.x, s*v.y);
}

inline
Vector2d operator * (const double& s, const Vector2d& v)
{
	return Vector2d(s*v.x, s*v.y);
}

inline
Vector2d operator / (const Vector2d& v, const double& s)
{
	return Vector2d(v.x/s, v.y/s);
}

inline
Vector2d& Vector2d::operator *= (const double& s)
{
	x *= s;
	y *= s;
	return *this;
}

inline
Vector2d& Vector2d::operator /= (const double& s)
{
	x /= s;
	y /= s;
	return *this;
}

inline
double operator * (const Vector2d& v1, const Vector2d& v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

inline
double operator ^ (const Vector2d& v1, const Vector2d& v2)
{
	return v1.x*v2.y - v1.y*v2.x;
}
inline
Vector2d Vector2d::operator - () const
{
	return Vector2d(-x, -y);
}

#endif	// _VECTOR2D_H_
