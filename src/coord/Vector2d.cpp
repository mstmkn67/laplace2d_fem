//===== Vector2d.cpp ========================================================

#include "Vector2d.h"

bool Vector2d::outputParen = true;

//=====  output  ============================================================

ostream& operator << (ostream& os, const Vector2d& v)
{
	if( Vector2d::parenIsOn() ) {
		os << "( " << v.x << ", " << v.y << " )";
	}
	else {
		os << v.x << " " << v.y;
	}

	return os;
}

istream& operator >> (istream& is, Vector2d& v)
{
	double	x, y;
	char	c = 0;

	is >> c;
	if( c == '(' ) {
		is >> x >> c;
		if( c == ',' ) {
			is >> y >> c;
			if( is && c == ')' ) {
				v.set(x,y);
				return is;
			}
		}
	}
	else {
		is.putback(c);
		is >> x >> y;
		if( is ) {
			v.set(x,y);
			return is;
		}
	}
	is.clear(ios::badbit);		// set badbit ON
	return is;
}
