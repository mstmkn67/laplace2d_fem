//Tensor3x3
//3x3ÇÃé¿êîå^ÉeÉìÉ\Éã

#ifndef _TENSOR_3X3_H_
#define _TENSOR_3X3_H_
#include <iomanip>
#include <vector>
using namespace std;
#include "Vector3d.h"

class Tensor3x3{
public:
	Tensor3x3(double mxx=0.0,double mxy=0.0,double mxz=0.0,
            double myx=0.0,double myy=0.0,double myz=0.0,
            double mzx=0.0,double mzy=0.0,double mzz=0.0)
		:x(mxx,mxy,mxz),y(myx,myy,myz),z(mzx,mzy,mzz){}
	Tensor3x3(const Vector3d& vecx,const Vector3d& vecy,const Vector3d& vecz)
		:x(vecx),y(vecy),z(vecz){}
	//ÉÅÉìÉo
	Vector3d x,y,z;
	void set(double mxx=0.0,double mxy=0.0,double mxz=0.0,
           double myx=0.0,double myy=0.0,double myz=0.0,
           double mzx=0.0,double mzy=0.0,double mzz=0.0)
		{x.set(mxx,mxy,mxz);y.set(myx,myy,myz);z.set(mzx,mzy,mzz);}
	void set(const Vector3d& vecx,const Vector3d& vecy,const Vector3d& vecz)
		{x=vecx;y=vecy;z=vecz;}
	double det();
	double det()const;
	double trace(){return x.x+y.y+z.z;}
	double trace()const{return x.x+y.y+z.z;}
	void clear(){x.set(0.0,0.0,0.0);y.set(0.0,0.0,0.0);z.set(0.0,0.0,0.0);}
	double& operator()(unsigned i,unsigned j);
	double get(unsigned i,unsigned j)const;
	vector<vector<double> > getSTLVector();
	Tensor3x3 transpose();
	Tensor3x3 invert();
	Tensor3x3 transpose()const;
	Tensor3x3 invert()const;

	Tensor3x3& operator = (const Tensor3x3& m);
	Tensor3x3& operator += (const Tensor3x3& m);
	Tensor3x3& operator -= (const Tensor3x3& m);
	Tensor3x3& operator *= (const double& m);
	Tensor3x3& operator /= (const double& m);

	Tensor3x3 operator - ()const;
	
	friend Tensor3x3 operator + (const Tensor3x3& m1,const Tensor3x3& m2);
	friend Tensor3x3 operator - (const Tensor3x3& m1,const Tensor3x3& m2);
	friend Tensor3x3 operator / (const Tensor3x3& m,const double& s);
	friend Tensor3x3 operator * (const Tensor3x3& m1,const Tensor3x3& m2);
	friend Tensor3x3 operator * (const double& d, const Tensor3x3& m1);
	friend Tensor3x3 operator * (const Tensor3x3& m1,const double& d);
	friend Vector3d  operator * (const Tensor3x3& m, const Vector3d& v);
	
	//////////ì¡éÍÇ»ëÄçÏ//////////
	//A:B(A_{ij}B_{ji})ÇåvéZ
	friend double dot2(const Tensor3x3& m1,const Tensor3x3& m2);
	//(BxA)_{ab}=É√_{adc}B_{d}A_{cb}
	friend Tensor3x3 operator^(const Vector3d& B,const Tensor3x3& A);
	//(AxB)_{ab}=É√_{bcd}A_{ac}B_{d}
	friend Tensor3x3 operator^(const Tensor3x3& A,const Vector3d& B);
	//(AB)_{ab}=A_aB_b
	friend Tensor3x3 dyad(const Vector3d& A,const Vector3d& B);
	//ç¿ïWånÇÃïœä∑QÇÃçsóÒéÆÇÕ1Ç…ÇµÇ‹ÇµÇÂÇ§
	//Q_{ab}r_b
	friend Vector3d convert(const Tensor3x3& Q,const Vector3d& r);
	//Q_{ar}A_{rq}Q_{qb}
	friend Tensor3x3 convert(const Tensor3x3& Q,const Tensor3x3& A);

	friend ostream& operator << (ostream& os, const Tensor3x3& m)
	{
		os	<< m.x << endl << m.y << endl	<< m.z ;
		return os;
	}

	friend istream& operator >> (istream& is, Tensor3x3& m)
	{
		is	>> m.x	>> m.y	>> m.z;
		return is;
	}
};

inline double& Tensor3x3::operator()(unsigned i,unsigned j)
{
	if(i==0){
		if(j==0)return x.x;
		if(j==1)return x.y;
		return x.z;
	}else if(i==1){
		if(j==0)return y.x;
		if(j==1)return y.y;
		return y.z;
	}else{
		if(j==0)return z.x;
		if(j==1)return z.y;
		return z.z;
	}
}

inline double Tensor3x3::get(unsigned i,unsigned j)const
{
	if(i==0){
		if(j==0)return x.x;
		if(j==1)return x.y;
		return x.z;
	}else if(i==1){
		if(j==0)return y.x;
		if(j==1)return y.y;
		return y.z;
	}else{
		if(j==0)return z.x;
		if(j==1)return z.y;
		return z.z;
	}
}

inline vector<vector<double> > Tensor3x3::getSTLVector()
{
	vector<vector<double> > a;
	a.resize(3);
	a[0].resize(3);
	a[1].resize(3);
	a[2].resize(3);
	a[0][0]=x.x;a[0][1]=x.y;a[0][2]=x.z;
	a[1][0]=y.x;a[1][1]=y.y;a[1][2]=y.z;
	a[2][0]=z.x;a[2][1]=z.y;a[2][2]=z.z;
	return a;
}

inline Tensor3x3& Tensor3x3::operator = (const Tensor3x3& m)
{
	x=m.x;
	y=m.y;
	z=m.z;  
	return *this;
}

inline Tensor3x3& Tensor3x3::operator += (const Tensor3x3& m)
{
	x+=m.x;
	y+=m.y;
	z+=m.z;
	return *this;
}

inline Tensor3x3& Tensor3x3::operator -= (const Tensor3x3& m)
{
	x-=m.x;
	y-=m.y;
	z-=m.z;
	return *this;
}

inline Tensor3x3& Tensor3x3::operator *= (const double& m)
{
	x*=m;
	y*=m;
	z*=m;
	return *this;
}

inline Tensor3x3& Tensor3x3::operator /= (const double& m)
{
	x/=m;
	y/=m;
	z/=m;
	return *this;
}

inline Tensor3x3 Tensor3x3::operator - ()const
{
	return Tensor3x3(-x,-y,-z);
}

inline Tensor3x3 operator + (const Tensor3x3& m1, const Tensor3x3& m2)
{
	return Tensor3x3(m1.x+m2.x, m1.y+m2.y, m1.z+m2.z);
}

inline Tensor3x3 operator - (const Tensor3x3& m1, const Tensor3x3& m2)
{
	return Tensor3x3(m1.x-m2.x, m1.y-m2.y, m1.z-m2.z);
}

inline Tensor3x3 operator / (const Tensor3x3& m, const double& s)
{
	return Tensor3x3(m.x/s, m.y/s, m.z/s);
}

inline Tensor3x3 operator * (const Tensor3x3& m1, const Tensor3x3& m2){
	return Tensor3x3(
		m1.x.x*m2.x.x + m1.x.y*m2.y.x + m1.x.z*m2.z.x,
	  m1.x.x*m2.x.y + m1.x.y*m2.y.y + m1.x.z*m2.z.y,
	  m1.x.x*m2.x.z + m1.x.y*m2.y.z + m1.x.z*m2.z.z,//
		m1.y.x*m2.x.x + m1.y.y*m2.y.x + m1.y.z*m2.z.x,
	  m1.y.x*m2.x.y + m1.y.y*m2.y.y + m1.y.z*m2.z.y,
	  m1.y.x*m2.x.z + m1.y.y*m2.y.z + m1.y.z*m2.z.z,//
		m1.z.x*m2.x.x + m1.z.y*m2.y.x + m1.z.z*m2.z.x,
	  m1.z.x*m2.x.y + m1.z.y*m2.y.y + m1.z.z*m2.z.y,
	  m1.z.x*m2.x.z + m1.z.y*m2.y.z + m1.z.z*m2.z.z);
}

inline double dot2(const Tensor3x3& m1,const Tensor3x3& m2)
{
	return (m1*m2).trace();
}

inline Tensor3x3 operator * (const double& d,const Tensor3x3& m){
	return Tensor3x3(d*m.x,d*m.y,d*m.z);
}

inline Tensor3x3 operator * (const Tensor3x3& m, const double& d){
	return Tensor3x3(d*m.x,d*m.y,d*m.z);
}

inline Vector3d  operator * (const Tensor3x3& m, const Vector3d& v){
	return Vector3d(m.x*v,m.y*v,m.z*v);
}

inline Tensor3x3 Tensor3x3::transpose()
{
	return Tensor3x3(x.x,y.x,z.x,
		               x.y,y.y,z.y,
		               x.z,y.z,z.z);
}

inline Tensor3x3 Tensor3x3::transpose()const
{
	return Tensor3x3(x.x,y.x,z.x,
		               x.y,y.y,z.y,
		               x.z,y.z,z.z);
}

inline Tensor3x3 Tensor3x3::invert(){
	Tensor3x3 hinv(
		y.y*z.z-y.z*z.y, x.z*z.y-x.y*z.z, x.y*y.z-y.y*x.z,
		y.z*z.x-y.x*z.z, x.x*z.z-x.z*z.x, y.x*x.z-x.x*y.z,
		y.x*z.y-y.y*z.x, x.y*z.x-x.x*z.y, x.x*y.y-y.x*x.y);
	double a=x.x*y.y*z.z+x.y*y.z*z.x+x.z*y.x*z.y
	         -(x.z*y.y*z.x+x.y*y.x*z.z+x.x*z.y*y.z);
	return (hinv/a);
}

inline Tensor3x3 Tensor3x3::invert()const{
	Tensor3x3 hinv(
		y.y*z.z-y.z*z.y, x.z*z.y-x.y*z.z, x.y*y.z-y.y*x.z,
		y.z*z.x-y.x*z.z, x.x*z.z-x.z*z.x, y.x*x.z-x.x*y.z,
		y.x*z.y-y.y*z.x, x.y*z.x-x.x*z.y, x.x*y.y-y.x*x.y);
	double a=x.x*y.y*z.z+x.y*y.z*z.x+x.z*y.x*z.y
	         -(x.z*y.y*z.x+x.y*y.x*z.z+x.x*z.y*y.z);
	return hinv/a;
}

inline double Tensor3x3::det()
{
	return x.x*y.y*z.z+x.y*y.z*z.x+x.z*y.x*z.y-(x.z*y.y*z.x+x.y*y.x*z.z+x.x*z.y*y.z);
}

inline double Tensor3x3::det()const
{
	return x.x*y.y*z.z+x.y*y.z*z.x+x.z*y.x*z.y-(x.z*y.y*z.x+x.y*y.x*z.z+x.x*z.y*y.z);
}

inline Tensor3x3 dyad(const Vector3d& A,const Vector3d& B)
{
	return Tensor3x3(
		A.x*B.x,A.x*B.y,A.x*B.z,
		A.y*B.x,A.y*B.y,A.y*B.z,
		A.z*B.x,A.z*B.y,A.z*B.z);
}

inline Vector3d convert(const Tensor3x3& Q,const Vector3d& r)
{
	return Vector3d(
		Q.x.x*r.x+Q.x.y*r.y+Q.x.z*r.z,
		Q.y.x*r.x+Q.y.y*r.y+Q.y.z*r.z,
		Q.z.x*r.x+Q.z.y*r.y+Q.z.z*r.z);
}

inline Tensor3x3 convert(const Tensor3x3& Q,const Tensor3x3& A)
{
	return Q*A*(Q.transpose());
}

inline Tensor3x3 operator ^ (const Vector3d& B,const Tensor3x3& A){
	return Tensor3x3(												
		B.y*A.z.x-B.z*A.y.x , B.y*A.z.y-B.z*A.y.y , B.y*A.z.z-B.z*A.y.z ,
		B.z*A.x.x-B.x*A.z.x , B.z*A.x.y-B.x*A.z.y , B.z*A.x.z-B.x*A.z.z ,
		B.x*A.y.x-B.y*A.x.x , B.x*A.y.y-B.y*A.x.y , B.x*A.y.z-B.y*A.x.z);
}

inline Tensor3x3 operator ^ (const Tensor3x3& A,const Vector3d& B){
	return Tensor3x3(
		A.x.y*B.z-A.x.z*B.y , A.x.z*B.x-A.x.x*B.z , A.x.x*B.y-A.x.y*B.x ,
		A.y.y*B.z-A.y.z*B.y , A.y.z*B.x-A.y.x*B.z , A.y.x*B.y-A.y.y*B.x ,
		A.z.y*B.z-A.z.z*B.y , A.z.z*B.x-A.z.x*B.z , A.z.x*B.y-A.z.y*B.x);	
}

#endif //_TENSOR_3X3_H_

