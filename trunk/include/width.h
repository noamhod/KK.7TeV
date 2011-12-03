/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifndef WIDTH_H
#define WIDTH_H

#include "couplings.h"
#include "enums.h"

using namespace couplings;

namespace width
{

static double mKK = 2000.; // GeV
static double mZP = 2000.; // GeV

inline double wGKK(unsigned int id, unsigned int mode)
{
	double w = 0.;
	double mKKn2 = (mode*mKK)*(mode*mKK);
	double mass = sqrt(0. + mKKn2);
	double m2 = mass*mass;
	double mf2 = mf(id)*mf(id);
	double qf2 = qf(id)*qf(id);

	// GKK
	if(id==PDTTOP  &&  mass>=2.*mf(id)) // top is not massless !!!
	{
		w = Ncf(id)*(alphaEM/6.) * mass * sqrt( 1. - 4.*mf2/m2) * (2.*qf2 + 4.*qf2*mf2/m2);
	}
	else w = Ncf(id)*(alphaEM/6) * mass * 2*(qf(id)*qf(id));
	
	return w;
}

inline double wZKK(unsigned int id, unsigned int mode)
{
	double w = 0.;
	double mKKn2 = (mode*mKK)*(mode*mKK);
	double mass = sqrt(mZ2 + mKKn2);
	double m2 = mass*mass;
	double mf2 = mf(id)*mf(id);
	double I3f2 = I3f(id)*I3f(id);
	
	// ZKK
	if(id==PDTTOP  &&  mass>=2.*mf(id)) // top is not massless !!!
	{
		w = (1./(24.*pi*sq2))*
			Gmu*Ncf(id)*
			(mZ2*mass)*
			sqrt(1.-4.*mf2/m2)*
			(1.-4.*mf2/m2+(2.*I3f(id)-4.*qf(id)*sw2)*(2.*I3f(id)-4.*qf(id)*sw2)*(1.+2.*mf2/m2));
	}
	else w = (1./(3.*pi*sq2))*Gmu*Ncf(id)*(mZ2*mass)*(I3f2-2.*(I3f(id)*qf(id)*sw2)+2.*(qf(id)*sw2)*(qf(id)*sw2));
	
	return w;
}

inline double wZP(unsigned int id)
{
	double w = 0.;
	double mass = mZP;
	double m2 = mass*mass;
	double mf2 = mf(id)*mf(id);
	double I3f2 = I3f(id)*I3f(id);
	
	// ZKK
	if(id==PDTTOP  &&  mass>=2.*mf(id)) // top is not massless !!!
	{
		w = (1./(24.*pi*sq2))*
			Gmu*Ncf(id)*
			(mZ2*mass)*
			sqrt(1.-4.*mf2/m2)*
			(1.-4.*mf2/m2+(2.*I3f(id)-4.*qf(id)*sw2)*(2.*I3f(id)-4.*qf(id)*sw2)*(1.+2.*mf2/m2));
	}
	else w = (1./(3.*pi*sq2))*Gmu*Ncf(id)*(mZ2*mass)*(I3f2-2.*(I3f(id)*qf(id)*sw2)+2.*(qf(id)*sw2)*(qf(id)*sw2));
	
	return w;
}



////////////////////////////////////////////////////////
inline double wTotGKK(unsigned int mode)
{
	double w = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on all the flavors
	{
		w += wGKK(it->first,mode);
	}
	return w;
}
inline double wTotZKK(unsigned int mode)
{
	double w = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on all the flavors
	{
		w += wZKK(it->first,mode);
	}
	return w;
}
inline double wTotZP()
{
	double w = 0.;
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) // loop on all the flavors
	{
		w += wZP(it->first);
	}
	return w;
}


}

#endif

