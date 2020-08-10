#include "Integral2d.h"

IntegralTriangle::IntegralTriangle(int type){
	n=type/100;
	we=new double[n]; xi=new Vector2d[n];
	switch(type){
		double a,b,c,d,A;
		case 100:
			xi[0].set(1./3.,1./3.);
			we[0]=0.5;
			break;
		case 300:
			xi[0].set(0.5,0.5);
			xi[1].set(0.0,0.5);
			xi[2].set(0.5,0.0);
			we[0]=we[1]=we[2]=1./6.;
			break;
		case 301:
			xi[0].set(1./6.,1./6.);
			xi[1].set(2./3.,1./6.);
			xi[2].set(1./6.,2./3.);
			we[0]=we[1]=we[2]=1./6.;
			break;
		case 400:
			xi[0].set(1./3.,1./3.);
			xi[1].set(1./5.,1./5.);
			xi[2].set(3./5.,1./5.);
			xi[3].set(1./5.,3./5.);
			we[0]=-27./96.;
			we[1]=we[2]=we[3]=25./96.;
			break;
		case 600:
			a=0.445948490915965;
			b=0.091576213509771;
			xi[0].set(a,      a);
			xi[1].set(1.-2.*a,a);
			xi[2].set(a,      1.-2.*a);
			xi[3].set(b,      b);
			xi[4].set(1.-2.*b,b);
			xi[5].set(b,      1.-2.*b);
			we[0]=we[1]=we[2]=0.111690794839005;
			we[3]=we[4]=we[5]=0.054975871827661;
			break;
		case 700:
			a=(6.+sqrt(15.))/21.;
			b=4./7.-a;
			xi[0].set(1./3.,  1./3.);
			xi[1].set(a,      a);
			xi[2].set(1.-2.*a,a);
			xi[3].set(a,      1.-2.*a);
			xi[4].set(b,      b);
			xi[5].set(1.-2.*b,b);
			xi[6].set(b,      1.-2.*b);
			A=(155.+sqrt(15.))/2400.;
			we[0]=9./80.;
			we[1]=we[2]=we[3]=A;
			we[4]=we[5]=we[6]=31./240.-A;
			break;
		case 1200:
			a=0.063089014491502;
			b=0.249286745170910;
			c=0.310352451033785;
			d=0.053145049844816;
			xi[0 ].set(a,       a);
			xi[1 ].set(1.-2.*a, a);
			xi[2 ].set(a,       1.-2.*a);
			xi[3 ].set(b,       b);
			xi[4 ].set(1.-2.*b, b);
			xi[5 ].set(b,       1.-2.*b);
			xi[6 ].set(c,       d);
			xi[7 ].set(d,       c);
			xi[8 ].set(1.-(c+d),c);
			xi[9 ].set(1.-(c+d),d);
			xi[10].set(c,       1.-(c+d));
			xi[11].set(d,       1.-(c+d));
			we[0]=we[1]=we[2]=0.025422453185103;
			we[3]=we[4]=we[5]=0.058393137863189;
			we[6]=we[7]=we[8]=we[9]=we[10]=we[11]
				=0.041425537809187;
			break;
		default:
			cout << "IntegralTriangle error!" << endl;
			cout << type << " is not implemented." << endl;
			break;
	}
}
IntegralTriangle::~IntegralTriangle(){
	delete[] we; delete[] xi;
}
//
IntegralTetragon::IntegralTetragon(int type){
	n=type/100;
	we=new double[n]; xi=new Vector2d[n];
	double r,s,t;
	switch(type){
		case 300:
			xi[0].set(sqrt(2./3.),0.0);
			xi[1].set(-1./sqrt(6.),-1./sqrt(2.));
			xi[2].set(-1./sqrt(6.), 1./sqrt(2.));
			we[0]=we[1]=we[2]=4./3.;
			break;
		case 301:
			xi[0].set(1.0,1.0);
			xi[1].set(-5./9.,2./9.);
			xi[2].set(1./3.,-2./3.);
			we[0]=4./7.;we[1]=27./14.;we[2]=1.5;
			break;
		case 400:
			xi[0].set(-1./sqrt(3.),-1./sqrt(3.));
			xi[1].set( 1./sqrt(3.),-1./sqrt(3.));
			xi[2].set( 1./sqrt(3.), 1./sqrt(3.));
			xi[3].set(-1./sqrt(3.), 1./sqrt(3.));
			we[0]=we[1]=we[2]=we[3]=1.;
			break;
		case 401:
			xi[0].set(-1.,0.);
			xi[1].set( 1.,0.);
			xi[2].set( 0., 1./sqrt(2.));
			xi[3].set( 0.,-1./sqrt(2.));
			we[0]=we[1]=2./3.;
			we[2]=we[3]=4./3.;
			break;
		case 402:
			xi[0].set(-sqrt(2./3.),0.);
			xi[1].set( sqrt(2./3.),0.);
			xi[2].set( 0., sqrt(2./3.));
			xi[3].set( 0.,-sqrt(2./3.));
			we[0]=we[1]=we[2]=we[3]=1.;
			break;
		case 700:
			xi[0].set(0.,0.);
			xi[1].set(0.,-sqrt(14./15.));
			xi[2].set(0., sqrt(14./15.));
			xi[3].set(-sqrt(3./5.),-sqrt(3./5.));
			xi[4].set( sqrt(3./5.),-sqrt(3./5.));
			xi[5].set( sqrt(3./5.), sqrt(3./5.));
			xi[6].set(-sqrt(3./5.), sqrt(3./5.));
			we[0]=8./7.;
			we[1]=we[2]=20./63.;
			we[3]=we[4]=20./36.;
			break;
		case 701:
			r=sqrt(7./15.);
			s=sqrt((7.+sqrt(24.))/15.);
			t=sqrt((7.-sqrt(24.))/15.);
			xi[0].set(0.,0.);
			xi[1].set(-r,-r);
			xi[2].set( r, r);
			xi[3].set( s,-r);
			xi[4].set(-s, t);
			xi[5].set( t,-s);
			xi[6].set(-t, s);
			we[0]=8./7.;
			we[1]=we[2]=we[3]=100./168.;
			we[4]=we[5]=we[6]=20./48.;
			break;
		default:
			cout << "IntegralTetragon error!" << endl;
			cout << type << " is not implemented." << endl;
			break;
	}
}

IntegralTetragon::~IntegralTetragon(){
	delete[] we; delete[] xi;
}
