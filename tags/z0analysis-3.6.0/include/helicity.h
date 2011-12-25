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
#include "kFactors.h"

using namespace couplings;
using namespace width;
using namespace kFactors;

namespace helicity
{

static const unsigned int nModes  = 10; // 100;
static const double    min_weight = 0.;
static const double    max_weight = 1.e+5;
static bool dokFactors = false;

void setkFactors(bool dokF)
{
	dokFactors = dokF;
}

inline bool isnaninf(double x)
{
	if(std::isinf(x)) { _WARNING("value is infinity");     return true; }
	if(std::isnan(x)) { _WARNING("value is not a number"); return true; }
	return false;
}

//////////////////////////////////////////////////////////
inline dcomplex hAG0(double s, unsigned int idIn, unsigned int idOut)
{
	dcomplex A(0,0);
	if(s<0.) return A;
	A = gG(idIn)*gG(idOut)/s;
	return A;
}
inline dcomplex hAZ0(double s, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	dcomplex A(0,0);
	if(s<0.) return A;
	A = gZH(idIn,hIn)*gZH(idOut,hOut)/(s-mZ2 + Im*s*(wZ0/mZ0));
	return A;
}
inline dcomplex hASM(double s, double cosTheta, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	dcomplex A(0,0);
	if(fabs(cosTheta)>1.) return A;
	double mass = sqrt(s);
	double sqrtkF = (dokFactors) ? sqrt(ElectroWeak(mass,"NNLO/LO*")) : 1.;
	if(isnaninf(sqrtkF)) { _WARNING("k-factor is nan/inf"); }
	A = sqrtkF*(hAG0(s,idIn,idOut) + hAZ0(s,idIn,idOut,hIn,hOut))*sqrt(1.+4.*hIn*hOut*cosTheta);
	if(isnaninf(real(A*conj(A)))) { _WARNING("|hASM|^2 is nan/inf"); }
	return A;
}


//////////////////////////////////////////////////////////
inline dcomplex hAZP0(double s, double cosTheta, double w, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	dcomplex A(0,0);
	if(s<0.) return A;
	if(fabs(cosTheta)>1.) return A;
	double mass = mZP;
	double m2 = mass*mass;
	A = (gZH(idIn,hIn)*gZH(idOut,hOut)/(s-m2 + Im*s*(w/mass)) )*sqrt(1.+4.*hIn*hOut*cosTheta);
	return A;
}
inline dcomplex hAZP(double s, double cosTheta, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	dcomplex A(0,0);
	A = hASM(s,cosTheta,idIn,idOut,hIn,hOut); // the SM term
	double w = wTotZP();
	// double w = wTotZPsimple();
	A += hAZP0(s,cosTheta,w,idIn,idOut,hIn,hOut);
	return A;
}
inline dcomplex hAZPnoSM(double s, double cosTheta, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	dcomplex A(0,0);
	double w = wTotZP();
	// double w = wTotZPsimple();
	A += hAZP0(s,cosTheta,w,idIn,idOut,hIn,hOut);
	return A;
}


//////////////////////////////////////////////////////////
inline dcomplex hAGKKn(double s, double w, unsigned int idIn, unsigned int idOut, unsigned int mode)
{
	dcomplex A(0,0);
	if(s<0.) return A;
	double mKKn2 = (mode*mKK)*(mode*mKK);
	double mass = sqrt(0. + mKKn2);
	double m2 = mass*mass;
	A = gGKK(idIn)*gGKK(idOut)/(s-m2 + Im*s*(w/mass));
	return A;
}
inline dcomplex hAZKKn(double s, double w, unsigned int idIn, unsigned int idOut, double hIn, double hOut, unsigned int mode)
{
	dcomplex A(0,0);
	if(s<0.) return A;
	double mKKn2 = (mode*mKK)*(mode*mKK);
	double mass = sqrt(mZ2 + mKKn2);
	double m2 = mass*mass;
	A = gZKKH(idIn,hIn)*gZKKH(idOut,hOut)/(s-m2 + Im*s*(w/mass));
	return A;
}
inline dcomplex hAKKn(double s, double cosTheta, double wg, double wz, unsigned int idIn, unsigned int idOut, double hIn, double hOut, unsigned int mode)
{
	dcomplex A(0,0);
	if(fabs(cosTheta)>1.) return A;
	return ( (hAGKKn(s,wg,idIn,idOut,mode) + hAZKKn(s,wz,idIn,idOut,hIn,hOut,mode))*sqrt(1.+4.*hIn*hOut*cosTheta) );
}
inline dcomplex hAKK(double s, double cosTheta, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	dcomplex A(0,0);
	A = hASM(s,cosTheta,idIn,idOut,hIn,hOut); // the SM term
	for(unsigned int n=1 ; n<=nModes ; n++) // the KK tower
	{
		double wg = wTotGKK(n);
		double wz = wTotZKK(n);
		A += hAKKn(s,cosTheta,wg,wz,idIn,idOut,hIn,hOut,n);
	}
	return A;
}
inline dcomplex hAKKnoSM(double s, double cosTheta, unsigned int idIn, unsigned int idOut, double hIn, double hOut)
{
	dcomplex A(0,0);
	for(unsigned int n=1 ; n<=nModes ; n++) // the KK tower
	{
		double wg = wTotGKK(n);
		double wz = wTotZKK(n);
		A += hAKKn(s,cosTheta,wg,wz,idIn,idOut,hIn,hOut,n);
	}
	return A;
}


//////////////////////////////////////////////////////
inline double hA2SM(double cosTheta, double s, unsigned int idIn, unsigned int idOut)
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
inline double hA2ZP(double cosTheta, double s, unsigned int idIn, unsigned int idOut)
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
inline double hA2ZPnoSM(double cosTheta, double s, unsigned int idIn, unsigned int idOut)
{
	dcomplex A(0,0);
	double A2 = 0.;
	for(double hIn=-f12 ; hIn<=+f12 ; hIn++)
	{
		for(double hOut=-f12 ; hOut<=+f12 ; hOut++)
		{
			A = hAZPnoSM(s,cosTheta,idIn,idOut,hIn,hOut);
			A2 += real(A*conj(A));
		}
	}
	return A2;
}
inline double hA2KK(double cosTheta, double s, unsigned int idIn, unsigned int idOut)
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
inline double hA2KKnoSM(double cosTheta, double s, unsigned int idIn, unsigned int idOut)
{
	dcomplex A(0,0);
	double A2 = 0.;
	for(double hIn=-f12 ; hIn<=+f12 ; hIn++)
	{
		for(double hOut=-f12 ; hOut<=+f12 ; hOut++)
		{
			A = hAKKnoSM(s,cosTheta,idIn,idOut,hIn,hOut);
			A2 += real(A*conj(A));
		}
	}
	return A2;
}


//////////////////////////////////////////////////////////
inline void validateinput(double cosTheta, double s, unsigned int idIn, unsigned int idOut)
{
	if(s<0.)              { _ERROR("s<0., exitting now.");              exit(-1); }
	if(fabs(cosTheta)>1.) { _ERROR("fabs(cosTheta)>1., exitting now."); exit(-1); }
	if(idIn==0)           { _ERROR("idIn<0, exitting now.");            exit(-1); }
	if(idOut==0)          { _ERROR("idOut<0, exitting now.");           exit(-1); }
}
inline void validateoutput(double N, double D)
{
	double R = N/D;
	if(std::isinf(R)) { _ERROR("value is infinity -> "+_s(N)+"/"+_s(D)+", exitting now.");     exit(-1); }
	if(std::isnan(R)) { _ERROR("value is not a number -> "+_s(N)+"/"+_s(D)+", exitting now."); exit(-1); }
	if(R<=min_weight) { _WARNING("value too small or negative -> "+_s(N)+"/"+_s(D)); }
	if(R>max_weight)  { _WARNING("value is too large -> "+_s(N)+"/"+_s(D)); }
}
inline double weightKK(double cosTheta, double s, unsigned int idIn, unsigned int idOut)
{
	validateinput(cosTheta,s,idIn,idOut);
	double N = hA2KK(cosTheta,s,idIn,idOut);
	double D = hA2SM(cosTheta,s,idIn,idOut);
	validateoutput(N,D);
	return N/D;
}
inline double weightKKnoSM(double cosTheta, double s, unsigned int idIn, unsigned int idOut)
{
	validateinput(cosTheta,s,idIn,idOut);
	double N = hA2KKnoSM(cosTheta,s,idIn,idOut);
	double D = hA2SM(cosTheta,s,idIn,idOut);
	validateoutput(N,D);
	return N/D;
}
inline double weightZP(double cosTheta, double s, unsigned int idIn, unsigned int idOut)
{
	validateinput(cosTheta,s,idIn,idOut);
	double N = hA2ZP(cosTheta,s,idIn,idOut);
	double D = hA2SM(cosTheta,s,idIn,idOut);
	validateoutput(N,D);
	return N/D;
}
inline double weightZPnoSM(double cosTheta, double s, unsigned int idIn, unsigned int idOut)
{
	validateinput(cosTheta,s,idIn,idOut);
	double N = hA2ZPnoSM(cosTheta,s,idIn,idOut);
	double D = hA2SM(cosTheta,s,idIn,idOut);
	validateoutput(N,D);
	return N/D;
}


//////////////////////////////////////////////////////////
inline double hA2SMsumQ(double cosTheta, double s, unsigned int idOut)
{
	double A2 = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on the incoming flavors ==> meaningless without PDFs
	{
		unsigned int idIn = it->first;
		A2 += hA2SM(s,cosTheta,idIn,idOut);
	}
	return A2;
}
inline double hA2ZPsumQ(double cosTheta, double s, unsigned int idOut)
{
	double A2 = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on the incoming flavors ==> meaningless without PDFs
	{
		unsigned int idIn = it->first;
		A2 += hA2ZP(s,cosTheta,idIn,idOut);
	}
	return A2;
}
inline double hA2ZPnoSMsumQ(double cosTheta, double s, unsigned int idOut)
{
	double A2 = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on the incoming flavors ==> meaningless without PDFs
	{
		unsigned int idIn = it->first;
		A2 += hA2ZPnoSM(s,cosTheta,idIn,idOut);
	}
	return A2;
}
inline double hA2KKsumQ(double cosTheta, double s, unsigned int idOut)
{
	double A2 = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on the incoming flavors ==> meaningless without PDFs
	{
		unsigned int idIn = it->first;
		A2 += hA2KK(s,cosTheta,idIn,idOut);
	}
	return A2;
}
inline double hA2KKnoSMsumQ(double cosTheta, double s, unsigned int idOut)
{
	double A2 = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on the incoming flavors ==> meaningless without PDFs
	{
		unsigned int idIn = it->first;
		A2 += hA2KKnoSM(s,cosTheta,idIn,idOut);
	}
	return A2;
}


//////////////////////////////////////////////////////////////////
// http://homepage.mac.com/sigfpe/Computing/fobjects.html
template<class F>
double integrate(const F &f, double xMin, double xMax, unsigned int nsegments=100)
{
	double dx        = (xMax-xMin)/((double)nsegments);
	double h         = dx/3.;
	double integrand = 0.;
	double I         = 0.;
	double x         = xMin;
	unsigned int i   = 0;
	
	while(i<=nsegments) // i=0(1st point),...,i=nsegments(point nth+1)
	{
		// calculate the integrand 
		integrand = f(x);

		// simpson
		if      (i==0 || i==nsegments)           I+=integrand;
		else if (i%2==0 && i!=0 && i!=nsegments) I+=2.*integrand;
		else                                     I+=4.*integrand;

		// propagate x and i
		x += dx;
		i++;
	}
	return(h*I);
}

class template_hA2SM
{
	double s;
	unsigned int idIn;
	unsigned int idOut;
	public:
		template_hA2SM(double s0, unsigned int idIn0, unsigned int idOut0) : s(s0), idIn(idIn0), idOut(idOut0) { }
		template<class X>
		X operator()(X cosTheta) const
		{
			return hA2SM(cosTheta,s,idIn,idOut);
		}
};
class template_hA2ZP
{
	double s;
	unsigned int idIn;
	unsigned int idOut;
	public:
		template_hA2ZP(double s0, unsigned int idIn0, unsigned int idOut0) : s(s0), idIn(idIn0), idOut(idOut0) { }
		template<class X>
		X operator()(X cosTheta) const
		{
			return hA2ZP(cosTheta,s,idIn,idOut);
		}
};
class template_hA2ZPnoSM
{
	double s;
	unsigned int idIn;
	unsigned int idOut;
	public:
		template_hA2ZPnoSM(double s0, unsigned int idIn0, unsigned int idOut0) : s(s0), idIn(idIn0), idOut(idOut0) { }
		template<class X>
		X operator()(X cosTheta) const
		{
			return hA2ZPnoSM(cosTheta,s,idIn,idOut);
		}
};
class template_hA2KK
{
	double s;
	unsigned int idIn;
	unsigned int idOut;
	public:
		template_hA2KK(double s0, unsigned int idIn0, unsigned int idOut0) : s(s0), idIn(idIn0), idOut(idOut0) { }
		template<class X>
		X operator()(X cosTheta) const
		{
			return hA2KK(cosTheta,s,idIn,idOut);
		}
};
class template_hA2KKnoSM
{
	double s;
	unsigned int idIn;
	unsigned int idOut;
	public:
		template_hA2KKnoSM(double s0, unsigned int idIn0, unsigned int idOut0) : s(s0), idIn(idIn0), idOut(idOut0) { }
		template<class X>
		X operator()(X cosTheta) const
		{
			return hA2KKnoSM(cosTheta,s,idIn,idOut);
		}
};



/////////////////////////////////////////////////////////////////
// class IrZP
// {
	// double s;
	// unsigned int idIn;
	// unsigned int idOut;
	// public:
		// IrZP(double s0, unsigned int idIn0, unsigned int idOut0) : s(s0), idIn(idIn0), idOut(idOut0) { }
		// template<class X>
		// X operator()(X cosTheta) const
		// {
			// return weightZP(cosTheta,s,idIn,idOut);
		// }
// };
// class IrKK
// {
	// double s;
	// unsigned int idIn;
	// unsigned int idOut;
	// public:
		// IrKK(double s0, unsigned int idIn0, unsigned int idOut0) : s(s0), idIn(idIn0), idOut(idOut0) { }
		// template<class X>
		// X operator()(X cosTheta) const
		// {
			// return weightKK(cosTheta,s,idIn,idOut);
		// }
// };






class F
{
	double y;
	double z;
	public:
		F(double y0, double z0) : y(y0), z(z0) { }
		template<class X>
		X operator()(X x) const
		{
			return x*y*z;
		}
};

/*
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

