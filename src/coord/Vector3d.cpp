//===== Vector3d.cpp ========================================================
//
//		Input / Output Vector3d object
//
//
//				ver.1.0		Aug.10, 1998	J. Takimoto
//
//===========================================================================

#include "Vector3d.h"

//=====	static data member of class Vector3d ================================
//
//	select output format:
//		outputParen ==	true:	( x, y, z )
//				false:	x y z

bool Vector3d::outputParen = true;

//=====  output  ============================================================

ostream& operator << (ostream& os, const Vector3d& v)
{
	if( Vector3d::parenIsOn() ) {
		os << "( " << v.x << ", " << v.y << ", " << v.z << " )";
	}
	else {
		os << v.x << " " << v.y << " " << v.z;
	}

	return os;
}


//=====  input ==============================================================
//
//	both	( x, y, z )	and	x y z	are acceptable
//
//
//		see "The C++ Programing Language (3rd ed.)" by B.Stroustrup,
//			Section 21.3.5
//

istream& operator >> (istream& is, Vector3d& v)
{
	double	x, y, z;
	char	c = 0;

	is >> c;
	if( c == '(' ) {
		is >> x >> c;
		if( c == ',' ) {
			is >> y >> c;
			if( c == ',' ) {
				is >> z >> c;
				if( is && c == ')' ) {
					v.set(x,y,z);
					return is;
				}
			}
		}
	}
	else {
		is.putback(c);
		is >> x >> y >> z;
		if( is ) {
			v.set(x,y,z);
			return is;
		}
	}

	is.clear(ios::badbit);		// set badbit ON
	return is;
}
