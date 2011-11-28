/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifndef HELICITY_H
#define HELICITY_H

#include "couplings.h"
#include "width.h"

using namespace couplings;
using namespace width;

namespace helicity
{

static const unsigned int nModes  = 100;


//////////////////////////////////////////////////////////
inline dcomplex hAG0(double s, unsigned int idIn, unsigned int idOut)
{
	dcomplex A(0,0);
	A = gG(idIn)*gG(idOut)/s;
	return A;
}
inline dcomplex hAZ0(double s, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	dcomplex A(0,0);
	A = gZH(idIn,hIn)*gZH(idOut,hOut)/(s-mZ2 + Im*s*(wZ0/mZ0));
	return A;
}
inline dcomplex hASM(double s, double cosTheta, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	return( (hAG0(s,idIn,idOut) + hAZ0(s,idIn,idOut,hIn,hOut))*sqrt(1.+4.*hIn*hOut*cosTheta) );
}


//////////////////////////////////////////////////////////
inline dcomplex hAZP0(double s, double cosTheta, double w, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	dcomplex A(0,0);
	double mass = mZP;
	double m2 = mass*mass;
	A = (gZH(idIn,hIn)*gZH(idOut,hOut)/(s-m2 + Im*s*(w/mass)) )*sqrt(1.+4.*hIn*hOut*cosTheta);
	return A;
}
inline dcomplex hAZP(double s, double cosTheta, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	dcomplex A(0,0);
	A = hASM(s,cosTheta,idIn,idOut,hIn,hOut); // the SM term
	double w = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on all the flavors
	{
		w += wZP(it->first);
	}
	A += hAZP0(s,cosTheta,w,idIn,idOut,hIn,hOut);
	return A;
}


//////////////////////////////////////////////////////////
inline dcomplex hAGKKn(double s, double w, unsigned int idIn, unsigned int idOut, unsigned int mode)
{
	dcomplex A(0,0);
	double mKKn2 = (mode*mKK)*(mode*mKK);
	double mass = sqrt(0. + mKKn2);
	double m2 = mass*mass;
	A = gGKK(idIn)*gGKK(idOut)/(s-m2 + Im*s*(w/mass));
	return A;
}
inline dcomplex hAZKKn(double s, double w, unsigned int idIn, unsigned int idOut, double hIn, double hOut, unsigned int mode)
{
	dcomplex A(0,0);
	double mKKn2 = (mode*mKK)*(mode*mKK);
	double mass = sqrt(mZ2 + mKKn2);
	double m2 = mass*mass;
	A = gZKKH(idIn,hIn)*gZKKH(idOut,hOut)/(s-m2 + Im*s*(w/mass));
	return A;
}
inline dcomplex hAKKn(double s, double cosTheta, double wg, double wz, unsigned int idIn, unsigned int idOut, double hIn, double hOut, unsigned int mode)
{
	return ( (hAGKKn(s,wg,idIn,idOut,mode) + hAZKKn(s,wz,idIn,idOut,hIn,hOut,mode))*sqrt(1.+4.*hIn*hOut*cosTheta) );
}
inline dcomplex hAKK(double s, double cosTheta, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	dcomplex A(0,0);
	A = hASM(s,cosTheta,idIn,idOut,hIn,hOut); // the SM term
	for(unsigned int n=1 ; n<=nModes ; n++) // the KK tower
	{
		double wg = 0.;
		double wz = 0.;
		for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on all the flavors
		{
			wg += wGKK(it->first,n);
			wz += wZKK(it->first,n);
		}
		A += hAKKn(s,cosTheta,wg,wz,idIn,idOut,hIn,hOut,n);
	}
	return A;
}


//////////////////////////////////////////////////////
inline double hA2SM(double s, double cosTheta, unsigned int idIn, unsigned int idOut)
{
	dcomplex A(0,0);
	double A2 = 0.;
	for(double hIn=-f12 ; hIn<=+f12 ; hIn++)
	{
		for(double hOut=-f12 ; hOut<=+f12 ; hOut++)
		{
			A = hASM(s,cosTheta,idIn,idOut,hIn,hOut);
			A2 += real(A*conj(A));
		}
	}
	return A2;
}
inline double hA2ZP(double s, double cosTheta, unsigned int idIn, unsigned int idOut)
{
	dcomplex A(0,0);
	double A2 = 0.;
	for(double hIn=-f12 ; hIn<=+f12 ; hIn++)
	{
		for(double hOut=-f12 ; hOut<=+f12 ; hOut++)
		{
			A = hAZP(s,cosTheta,idIn,idOut,hIn,hOut);
			A2 += real(A*conj(A));
		}
	}
	return A2;
}
inline double hA2KK(double s, double cosTheta, unsigned int idIn, unsigned int idOut)
{
	dcomplex A(0,0);
	double A2 = 0.;
	for(double hIn=-f12 ; hIn<=+f12 ; hIn++)
	{
		for(double hOut=-f12 ; hOut<=+f12 ; hOut++)
		{
			A = hAKK(s,cosTheta,idIn,idOut,hIn,hOut);
			A2 += real(A*conj(A));
		}
	}
	return A2;
}


//////////////////////////////////////////////////////////
inline double weightKK(double s, double cosTheta, unsigned int idIn, unsigned int idOut)
{
	return hA2KK(s,cosTheta,idIn,idOut)/hA2SM(s,cosTheta,idIn,idOut);
}
inline double weightZP(double s, double cosTheta, unsigned int idIn, unsigned int idOut)
{
	return hA2ZP(s,cosTheta,idIn,idOut)/hA2SM(s,cosTheta,idIn,idOut);
}


//////////////////////////////////////////////////////////
inline double hA2SMsumQ(double s, double cosTheta, unsigned int idOut)
{
	double A2 = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on the incoming flavors
	{
		unsigned int idIn = it->first;
		A2 += hA2SM(s,cosTheta,idIn,idOut);
	}
	return A2;
}
inline double hA2ZPsumQ(double s, double cosTheta, unsigned int idOut)
{
	double A2 = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on the incoming flavors
	{
		unsigned int idIn = it->first;
		A2 += hA2ZP(s,cosTheta,idIn,idOut);
	}
	return A2;
}
inline double hA2KKsumQ(double s, double cosTheta, unsigned int idOut)
{
	double A2 = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on the incoming flavors
	{
		unsigned int idIn = it->first;
		A2 += hA2KK(s,cosTheta,idIn,idOut);
	}
	return A2;
}


//////////////////////////////////////////////////////////
inline double hA2SMtot(double s, unsigned int idOut) // integrate over the angle cosTheta
{
	double A2 = 0.;
	// A2 = INTEGRATE( hA2SMsumQ(s,cosTheta,idOut), dcosTheta );
	return A2;
}
inline double hA2ZPtot(double s, unsigned int idOut) // integrate over the angle cosTheta
{
	double A2 = 0.;
	// A2 = INTEGRATE( hA2ZPsumQ(s,cosTheta,idOut), dcosTheta );
	return A2;
}
inline double hA2KKtot(double s, unsigned int idOut) // integrate over the angle cosTheta
{
	double A2 = 0.;
	// A2 = INTEGRATE( hA2KKsumQ(s,cosTheta,idOut), dcosTheta );
	return A2;
}


/*
template<class F>
float integrate(const F &f, float x0, float x1)
{
	// . . .
	// . . . f(x) . . .
	// . . .
}

class F
{
	float y,z;
	public:
		F(float y0,float z0) : y(y0), z(z0) { }
		template<class X>
		X operator()(X x) const
		{
			return x*x+y*y+z*z;
		}
};

int main() {
	. . .
	. . .
	F f(2,3);
	integrate(f,0,1);
	. . .
}
*/


}
#endif

