//Tensor2x2
//2x2の実数型テンソル

#ifndef _TENSOR_2X2_H_
#define _TENSOR_2X2_H_
#include <iomanip>
#include <vector>
#include "Vector2d.h"
using namespace std;

class Tensor2x2{
public:
	Tensor2x2(double mxx=0.0,double mxy=0.0,
            double myx=0.0,double myy=0.0)
		:x(mxx,mxy),y(myx,myy){}
	Tensor2x2(const Vector2d& vecx,const Vector2d& vecy):x(vecx),y(vecy){}
	//メンバ
	Vector2d x,y;
	void set(double mxx=0.0,double mxy=0.0,
           double myx=0.0,double myy=0.0)
		{x=Vector2d(mxx,mxy);y=Vector2d(myx,myy);}
	void set(const Vector2d& vecx,const Vector2d& vecy)
		{x=vecx;y=vecy;}
	double det();
	double det()const;
	double trace(){return x.x+y.y;}
	double trace()const{return x.x+y.y;}
	void clear(){x=Vector2d(0.0,0.0);y=Vector2d(0.0,0.0);}
	double& operator()(unsigned i,unsigned j);
	double get(unsigned i,unsigned j)const;
	vector<vector<double> > getSTLVector();
	Tensor2x2 transpose();
	Tensor2x2 invert();
	Tensor2x2 transpose()const;
	Tensor2x2 invert()const;

	Tensor2x2& operator = (const Tensor2x2& m);
	Tensor2x2& operator += (const Tensor2x2& m);
	Tensor2x2& operator -= (const Tensor2x2& m);
	Tensor2x2& operator *= (const double& m);
	Tensor2x2& operator /= (const double& m);

	Tensor2x2 operator - ()const;
	
	friend Tensor2x2 operator + (const Tensor2x2& m1,const Tensor2x2& m2);
	friend Tensor2x2 operator - (const Tensor2x2& m1,const Tensor2x2& m2);
	friend Tensor2x2 operator / (const Tensor2x2& m,const double& s);
	friend Tensor2x2 operator * (const Tensor2x2& m1,const Tensor2x2& m2);
	friend Tensor2x2 operator * (const double& d, const Tensor2x2& m1);
	friend Tensor2x2 operator * (const Tensor2x2& m1,const double& d);
	friend Vector2d  operator * (const Tensor2x2& m, const Vector2d& v);
	
	//////////特殊な操作//////////
	//A:B(A_{ij}B_{ji})を計算
	friend double dot2(const Tensor2x2& m1,const Tensor2x2& m2);
	//(AB)_{ab}=A_aB_b
	friend Tensor2x2 dyad(const Vector2d& A,const Vector2d& B);
	//座標系の変換Qの行列式は1にしましょう
	//Q_{ab}r_b
	friend Vector2d convert(const Tensor2x2& Q,const Vector2d& r);
	//Q_{ar}A_{rq}Q_{qb}
	friend Tensor2x2 convert(const Tensor2x2& Q,const Tensor2x2& A);

	friend ostream& operator << (ostream& os, const Tensor2x2& m){
		os	<< m.x << endl << m.y ;
		return os;
	}

	friend istream& operator >> (istream& is, Tensor2x2& m){
		is	>> m.x	>> m.y;
		return is;
	}
};

inline double& Tensor2x2::operator()(unsigned i,unsigned j){
	if(i==0){
		if(j==0)return x.x;
		return x.y;
	}else if(i==1){
		if(j==0)return y.x;
		return y.y;
	}
}

inline double Tensor2x2::get(unsigned i,unsigned j)const
{
	if(i==0){
		if(j==0)return x.x;
		return x.y;
	}else if(i==1){
		if(j==0)return y.x;
		return y.y;
	}
}

inline vector<vector<double> > Tensor2x2::getSTLVector()
{
	vector<vector<double> > a;
	a.resize(2);
	a[0].resize(2);
	a[1].resize(2);
	a[0][0]=x.x;a[0][1]=x.y;
	a[1][0]=y.x;a[1][1]=y.y;
	return a;
}

inline Tensor2x2& Tensor2x2::operator = (const Tensor2x2& m)
{
	x=m.x;
	y=m.y;
	return *this;
}

inline Tensor2x2& Tensor2x2::operator += (const Tensor2x2& m)
{
	x+=m.x;
	y+=m.y;
	return *this;
}

inline Tensor2x2& Tensor2x2::operator -= (const Tensor2x2& m)
{
	x-=m.x;
	y-=m.y;
	return *this;
}

inline Tensor2x2& Tensor2x2::operator *= (const double& m)
{
	x*=m;
	y*=m;
	return *this;
}

inline Tensor2x2& Tensor2x2::operator /= (const double& m)
{
	x/=m;
	y/=m;
	return *this;
}

inline Tensor2x2 Tensor2x2::operator - ()const
{
	return Tensor2x2(-x,-y);
}

inline Tensor2x2 operator + (const Tensor2x2& m1, const Tensor2x2& m2)
{
	return Tensor2x2(m1.x+m2.x, m1.y+m2.y);
}

inline Tensor2x2 operator - (const Tensor2x2& m1, const Tensor2x2& m2)
{
	return Tensor2x2(m1.x-m2.x, m1.y-m2.y);
}

inline Tensor2x2 operator / (const Tensor2x2& m, const double& s)
{
	return Tensor2x2(m.x/s, m.y/s);
}

inline Tensor2x2 operator * (const Tensor2x2& m1, const Tensor2x2& m2){
	return Tensor2x2(
		m1.x.x*m2.x.x + m1.x.y*m2.y.x,
	  m1.x.x*m2.x.y + m1.x.y*m2.y.y,//
		m1.y.x*m2.x.x + m1.y.y*m2.y.x,
	  m1.y.x*m2.x.y + m1.y.y*m2.y.y);
}

inline double dot2(const Tensor2x2& m1,const Tensor2x2& m2)
{
	return (m1*m2).trace();
}

inline Tensor2x2 operator * (const double& d,const Tensor2x2& m){
	return Tensor2x2(d*m.x,d*m.y);
}

inline Tensor2x2 operator * (const Tensor2x2& m, const double& d){
	return Tensor2x2(d*m.x,d*m.y);
}

inline Vector2d  operator * (const Tensor2x2& m, const Vector2d& v){
	return Vector2d(m.x.x*v.x+m.x.y*v.y,
	                m.y.x*v.x+m.y.y*v.y);
}

inline Tensor2x2 Tensor2x2::transpose()
{
	return Tensor2x2(x.x,y.x,
		               x.y,y.y);
}

inline Tensor2x2 Tensor2x2::transpose()const
{
	return Tensor2x2(x.x,y.x,
		               x.y,y.y);
}

inline Tensor2x2 Tensor2x2::invert(){
	double a=x.x*y.y-x.y*y.x;
	return Tensor2x2( y.y/a,-x.y/a,
	                 -y.x/a, x.x/a);
}

inline Tensor2x2 Tensor2x2::invert()const{
	double a=x.x*y.y-x.y*y.x;
	return Tensor2x2( y.y/a,-x.y/a,
	                 -y.x/a, x.x/a);
}

inline double Tensor2x2::det(){
	return x.x*y.y-x.y*y.x;
}

inline double Tensor2x2::det()const{
	return x.x*y.y-x.y*y.x;
}

inline Tensor2x2 dyad(const Vector2d& A,const Vector2d& B)
{
	return Tensor2x2(
		A.x*B.x,A.x*B.y,
		A.y*B.x,A.y*B.y);
}

inline Vector2d convert(const Tensor2x2& Q,const Vector2d& r)
{
	return Vector2d(
		Q.x.x*r.x+Q.x.y*r.y,
		Q.y.x*r.x+Q.y.y*r.y);
}

inline Tensor2x2 convert(const Tensor2x2& Q,const Tensor2x2& A)
{
	return Q*A*(Q.transpose());
}

#endif //_TENSOR_2X2_H_

