//===== Vector3d.h ===========================================================
//
//		3D vector class
//
//				ver.1.0		Aug.10, 1998	J. Takimoto
//
//===========================================================================

#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

#include <math.h>	// for sqrt()
#include <iostream>	// for << and >>
using namespace std;

//============================================================================
//
//  class Vector3d
//
//	data members:
//		double x, y, z;			// public
//	operators:
//		vec = vec,	- vec
//		vec + vec,	vec - vec,	vec += vec,	vec -= vec
//		double * vec,	vec * double,	vec / double
//				vec *= double,	vec /= double
//		vec * vec	(inner product)
//		(vec^vec)	(outer product)
//
//		NOTE: The operator^ has very low precedence, so
//		      parentheses must be used almost always.
//
//	member functions:
//		double length()		= sqrt( vec * vec )
//		double length2()	= vec * vec
//
//
// 'Vector3d.cpp' is necessary only if the followings are used:
//
//	output to / input from stream
//		ostream& operator << (ostream& os, const Vector3d& v);
//		istream& operator >> (istream& is, Vector3d& v);
//
//	static member functions which control output format:
//		static void parenOn()	{ outputParen = true; }
//		static void parenOff()	{ outputParen = false; }
//		static bool parenIsOn()	{ return outputParen; }
//
//	'cout << vec' writes
//		'( x, y, z )'	if parenIsOn()	( default )
//		'x y z'		otherwise
//
//	'cin >> vec' can read either '(x, y, z)' or 'x y z'
//
//============================================================================

class Vector3d {

   public:	
	double x, y, z;			// data members are public

	//----- Constructors -----

	Vector3d(double vx = 0.0, double vy = 0.0, double vz = 0.0)
					: x(vx), y(vy), z(vz)	{}

	Vector3d(const Vector3d& v) : x(v.x), y(v.y), z(v.z) {}

	//----- get/set values -----

	void set(double vx, double vy, double vz) { x = vx; y = vy; z = vz; }

	//----- operators -----

	Vector3d& operator = (const Vector3d& v);

	friend Vector3d operator + (const Vector3d& v1, const Vector3d& v2);
	friend Vector3d operator - (const Vector3d& v1, const Vector3d& v2);
	Vector3d& operator += (const Vector3d& v);
	Vector3d& operator -= (const Vector3d& v);

	friend Vector3d operator * (const Vector3d& v, const double& s);
	friend Vector3d operator * (const double& s, const Vector3d &v);
	friend Vector3d operator / (const Vector3d& v, const double& s);
	Vector3d& operator *= (const double& s);
	Vector3d& operator /= (const double& s);

	friend double operator * (const Vector3d& v1, const Vector3d& v2);
	friend Vector3d operator ^ (const Vector3d& v1, const Vector3d& v2);

	Vector3d operator - () const;

	//-----  length of vector  -----

	double length() const { return sqrt(x*x + y*y + z*z); }
	double length2() const { return x*x + y*y + z*z; }

	//-----  set/reset/get outputParen  -----

	static void parenOn()	{ outputParen = true; }
	static void parenOff()	{ outputParen = false; }
	static bool parenIsOn()	{ return outputParen; }

   private:

	static bool outputParen;	// default value is true (Vector3d.cpp)
};


//============================================================================
//
//	Input / Output Vector3d objects
//
//		these two functions are defined in Vector3d.cpp
//
//============================================================================


ostream& operator << (ostream& os, const Vector3d& v);
istream& operator >> (istream& is, Vector3d& v);


//============================================================================
//
//	Definition of inline operators
//
//============================================================================


//=====  Assignment  =====

inline Vector3d& Vector3d::operator = (const Vector3d& v)
{
	x = v.x; y = v.y; z = v.z;
	return *this;
}

//=====  Vec + Vec , Vec - Vec  =====

inline Vector3d operator + (const Vector3d& v1, const Vector3d& v2)
{
	return Vector3d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vector3d operator - (const Vector3d& v1, const Vector3d& v2)
{
	return Vector3d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vector3d& Vector3d::operator += (const Vector3d& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline Vector3d& Vector3d::operator -= (const Vector3d& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

//=====  scalar*Vec, Vec*scalar, Vec/scalar  =====

inline Vector3d operator * (const Vector3d& v, const double& s)
{
	return Vector3d(s*v.x, s*v.y, s*v.z);
}

inline Vector3d operator * (const double& s, const Vector3d& v)
{
	return Vector3d(s*v.x, s*v.y, s*v.z);
}

inline Vector3d operator / (const Vector3d& v, const double& s)
{
	return Vector3d(v.x/s, v.y/s, v.z/s);
}

inline Vector3d& Vector3d::operator *= (const double& s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

inline Vector3d& Vector3d::operator /= (const double& s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

//======  inner product  =====

inline double operator * (const Vector3d& v1, const Vector3d& v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

//======  outer product  =====

inline Vector3d operator ^ (const Vector3d& v1, const Vector3d& v2)
{
	return Vector3d(v1.y*v2.z - v1.z*v2.y ,
			v1.z*v2.x - v1.x*v2.z ,
			v1.x*v2.y - v1.y*v2.x );
}

//=====  Unary minus  =====

inline Vector3d Vector3d::operator - () const
{
	return Vector3d(-x, -y, -z);
}

#endif	// _VECTOR3D_H_
