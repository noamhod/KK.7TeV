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

static const double mKKinit = 2000.; // GeV
static const double mZPinit = 2000.; // GeV

static double mKK = 2000.; // GeV
static double mZP = 2000.; // GeV

void setKKmass(double m) { mKK = m; }
void setZPmass(double m) { mZP = m; }
void resetKKmass() { mKK = mKKinit; }
void resetZPmass() { mZP = mZPinit; }

inline double wGKK2ttbar(unsigned int id, unsigned int mode)
{
	if(id!=PDTTOP)
	{
		_ERROR("id!=top, exitting now.");
		exit(-1);
	}

	double mKKn2 = (mode*mKK)*(mode*mKK);
	double mass = sqrt(0. + mKKn2);
	
	if(mass>=2.*mf(id)) return 0.; // mass threshold
	
	double m2 = mass*mass;
	double mf2 = mf(id)*mf(id);
	double qf2 = qf(id)*qf(id);

	// GKK->ttbar
	double w = 2. * Ncf(id)*(alphaEM/6.) * mass * 2.*qf2 * sqrt( 1. - 4.*mf2/m2) * (1. + 2.*mf2/m2); // top is not massless !!!
	
	return w;
}

inline double wZKK2ttbar(unsigned int id, unsigned int mode)
{
	if(id!=PDTTOP)
	{
		_ERROR("id!=top, exitting now.");
		exit(-1);
	}

	double mKKn2 = (mode*mKK)*(mode*mKK);
	double mass = sqrt(mZ2 + mKKn2);
	
	if(mass>=2.*mf(id)) return 0.; // mass threshold
	
	double m2 = mass*mass;
	double mf2 = mf(id)*mf(id);
	
	// ZKK->ttbar
	double w = 2.*
				(1./(24.*pi*sq2))*
				Gmu*Ncf(id)*
				(mZ2*mass)*
				sqrt(1.-4.*mf2/m2)*
				(1.-4.*mf2/m2+(2.*I3f(id)-4.*qf(id)*sw2)*(2.*I3f(id)-4.*qf(id)*sw2)*(1.+2.*mf2/m2)); // top is not massless !!!
	
	return w;
}

inline double wZP2ttbar(unsigned int id)
{
	if(id!=PDTTOP)
	{
		_ERROR("id!=top, exitting now.");
		exit(-1);
	}

	double mass = mZP;
	double m2 = mass*mass;
	
	if(mass>=2.*mf(id)) return 0.; // mass threshold
	
	double mf2 = mf(id)*mf(id);
	
	// Z'->ttbar
	double w = 2.*
				(1./(24.*pi*sq2))*
				Gmu*Ncf(id)*
				(mZ2*mass)*
				sqrt(1.-4.*mf2/m2)*
				(1.-4.*mf2/m2+(2.*I3f(id)-4.*qf(id)*sw2)*(2.*I3f(id)-4.*qf(id)*sw2)*(1.+2.*mf2/m2)); // top is not massless !!!
	
	return w;
}



inline double wGKK2ffbar(unsigned int id, unsigned int mode)
{
	double w = 0.;
	double mKKn2 = (mode*mKK)*(mode*mKK);
	double mass = sqrt(0. + mKKn2);

	// GKK->ffbar
	if(id==PDTTOP) w = wGKK2ttbar(PDTTOP,mode); // ttbar
	else           w = Ncf(id)*(alphaEM/6.) * mass * 4.*(qf(id)*qf(id)); // all the rest
	
	return w;
}

inline double wZKK2ffbar(unsigned int id, unsigned int mode)
{
	double w = 0.;
	double mKKn2 = (mode*mKK)*(mode*mKK);
	double mass = sqrt(mZ2 + mKKn2);
	double I3f2 = I3f(id)*I3f(id);
	
	// ZKK->ffbar
	if(id==PDTTOP) w = wZKK2ttbar(PDTTOP,mode); // ttbar
	else           w = 2.*(1./(3.*pi*sq2))*Gmu*Ncf(id)*(mZ2*mass)*(I3f2-2.*(I3f(id)*qf(id)*sw2)+2.*(qf(id)*sw2)*(qf(id)*sw2)); // all the rest
	
	return w;
}

inline double wZP2ffbar(unsigned int id)
{
	double w = 0.;
	double mass = mZP;
	double I3f2 = I3f(id)*I3f(id);
	
	// Z'->ffbar
	if(id==PDTTOP) w = wZP2ttbar(PDTTOP); // ttbar
	else           w = (1./(6.*pi*sq2))*Gmu*Ncf(id)*(mZ2*mass)*(I3f2-2.*(I3f(id)*qf(id)*sw2)+2.*(qf(id)*sw2)*(qf(id)*sw2)); // all the rest
	
	return w;
}


////////////////////////////////////////////////////////
inline double wTotGKK(unsigned int mode)
{
	double w = 0.;
	// loop on all the flavors
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) w += wGKK2ffbar(it->first,mode);
	return w;
}
inline double wTotZKK(unsigned int mode)
{
	double w = 0.;
	double mKKn2 = (mode*mKK)*(mode*mKK);
	double mass = sqrt(mZ2 + mKKn2);
	/*
	// loop on all the flavors
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) w += wZKK2ffbar(it->first,mode);
	*/
	w = 2. * wZ0 * mass/mZ0;
	if(mass>=2.*mf(PDTTOP)) w += wZKK2ttbar(PDTTOP,mode);
	return w;
}
inline double wTotZP()
{
	double w = 0.;
	double mass = mZP;
	/*
	// loop on all the flavors
	for(ui2fermion::iterator it=ui2f.begin() ; it!=ui2f.end() ; ++it) w += wZP2ffbar(it->first);
	*/
	w = wZ0 * mass/mZ0;
	if(mass>=2.*mf(PDTTOP)) w += wZP2ttbar(PDTTOP);
	return w;
}

}

#endif

