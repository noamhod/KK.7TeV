/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifndef COUPLINGS_H
#define COUPLINGS_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <complex>

#include "units.h"
#include "types.h"
#include "logs.h"

namespace couplings
{

static bool doScale      = false;
static bool doScaleWidth = true; // turn on/off the g^2 scale in the BW width (default = true)

static const double thetaE6_psi = 0.;
static const double thetaE6_chi = -pi/2.;
static const double thetaE6_eta = atan(-sqrt(5./3.))+pi/2.; //+asin(sqrt(3./8.));
static const double thetaE6_I   = -asin(sqrt(5./8.));

static double thetaE6 = thetaE6_psi;

void setCouplingsScale(bool doscale)
{
	doScale = doscale;
}

void setScaleWidth(bool doscale)
{
	doScaleWidth = doscale;
}

void setThetaE6(double thetae6)
{
	if(fabs(thetae6)>2.*pi) _FATAL("fabs(thetae6)>2.*pi for thetae6="+_s(thetae6));
	thetaE6 = thetae6;
}

void setThetaE6(TString model)
{
	if     (model=="psi") setThetaE6(thetaE6_psi);
	else if(model=="chi") setThetaE6(thetaE6_chi);
	else if(model=="eta") setThetaE6(thetaE6_eta);
	else if(model=="I")   setThetaE6(thetaE6_I);
	else _FATAL("E6 model :"+(string)model+", is not supported.");
}

ui2fermion ui2f;
s2fermion  s2f;

void setFermions()
{
	// FROM PDG
	// ui2f.insert( make_pair(1,  new fermion("dwn",     1, 5.7*MeV2GeV,     -f13, -f12) ) );
	// ui2f.insert( make_pair(2,  new fermion("up",      2, 3.1*MeV2GeV,     +f23, +f12) ) );
	// ui2f.insert( make_pair(3,  new fermion("strange", 3, 100.*MeV2GeV,    -f13, -f12) ) );
	// ui2f.insert( make_pair(4,  new fermion("charm",   4, 1290.*MeV2GeV,   +f23, +f12) ) );
	// ui2f.insert( make_pair(5,  new fermion("bottom",  5, 4670.*MeV2GeV,   -f13, -f12) ) );
	// ui2f.insert( make_pair(6,  new fermion("top",     6, 172900.*MeV2GeV, +f23, +f12) ) );
	// ui2f.insert( make_pair(11, new fermion("electron",     11, 0.511*MeV2GeV,   -1., -f12) ) );
	// ui2f.insert( make_pair(12, new fermion("neutrino e",   12, 0.*MeV2GeV,       0., +f12) ) );
	// ui2f.insert( make_pair(13, new fermion("muon",         13, 105.6*MeV2GeV,   -1., -f12) ) );
	// ui2f.insert( make_pair(14, new fermion("neutrino mu",  14, 0.*MeV2GeV,       0., +f12) ) );
	// ui2f.insert( make_pair(15, new fermion("tau",          15, 1776.82*MeV2GeV, -1., -f12) ) );
	// ui2f.insert( make_pair(16, new fermion("neutrino tau", 16, 0.*MeV2GeV,       0., +f12) ) );
	
	// FROM PYTHIA6.4 MANUAL
	ui2f.insert( make_pair(1,  new fermion("dwn",          1,  0.33,            -f13, -f12) ) );
	ui2f.insert( make_pair(2,  new fermion("up",           2,  0.33,            +f23, +f12) ) );
	ui2f.insert( make_pair(3,  new fermion("strange",      3,  0.5,             -f13, -f12) ) );
	ui2f.insert( make_pair(4,  new fermion("charm",        4,  1.5,             +f23, +f12) ) );
	ui2f.insert( make_pair(5,  new fermion("bottom",       5,  4.8,             -f13, -f12) ) );
	ui2f.insert( make_pair(6,  new fermion("top",          6,  175,             +f23, +f12) ) );
	ui2f.insert( make_pair(11, new fermion("electron",     11, 0.511*MeV2GeV,   -1.,  -f12) ) );
	ui2f.insert( make_pair(12, new fermion("neutrino e",   12, 0.*MeV2GeV,       0.,  +f12) ) );
	ui2f.insert( make_pair(13, new fermion("muon",         13, 105.6*MeV2GeV,   -1.,  -f12) ) );
	ui2f.insert( make_pair(14, new fermion("neutrino mu",  14, 0.*MeV2GeV,       0.,  +f12) ) );
	ui2f.insert( make_pair(15, new fermion("tau",          15, 1776.82*MeV2GeV, -1.,  -f12) ) );
	ui2f.insert( make_pair(16, new fermion("neutrino tau", 16, 0.*MeV2GeV,       0.,  +f12) ) );
	
	s2f.insert( make_pair("dwn",   ui2f[1] ) );
	s2f.insert( make_pair("up",    ui2f[2] ) );
	s2f.insert( make_pair("str",   ui2f[3] ) );
	s2f.insert( make_pair("chm",   ui2f[4] ) );
	s2f.insert( make_pair("bot",   ui2f[5] ) );
	s2f.insert( make_pair("top",   ui2f[6] ) );
	s2f.insert( make_pair("elec",  ui2f[11] ) );
	s2f.insert( make_pair("nuel",  ui2f[12] ) );
	s2f.insert( make_pair("muon",  ui2f[13] ) );
	s2f.insert( make_pair("numu",  ui2f[14] ) );
	s2f.insert( make_pair("tau",   ui2f[15] ) );
	s2f.insert( make_pair("nutau", ui2f[16] ) );
}

inline string namef(unsigned int id) { return ui2f[id]->name; }
inline int    Ncf(unsigned int id)   { return ui2f[id]->Nc; }
inline double mf(unsigned int id)    { return ui2f[id]->mass; }
inline double I3f(unsigned int id)   { return ui2f[id]->I3; }
inline double qf(unsigned int id)    { return ui2f[id]->charge; }


//////////////////////////////////////////////////////////////////////////////////
// KK scale factor couplings:
// This should affect the type of the couplings (complex) and the widths which
// are proportional to (|fgX*gL|^2+|fgX*gR|^2) ~ |fgX|^2*(|gL|^2+|gR|^2)  

static const dcomplex fgZPinit(1.,0.);
static const dcomplex fgGKKinit(1.,0.);
static const dcomplex fgZKKinit(1.,0.);
static dcomplex fgZP(1.,0.);
static dcomplex fgGKK(1.,0.);
static dcomplex fgZKK(1.,0.);
inline void setFgZP(double re, double im)  { fgZP  = dcomplex(re,im); }
inline void setFgGKK(double re, double im) { fgGKK = dcomplex(re,im); }
inline void setFgZKK(double re, double im) { fgZKK = dcomplex(re,im); }
inline double fgZP2()  { return real(fgZP*conj(fgZP)); }
inline double fgGKK2() { return real(fgGKK*conj(fgGKK)); }
inline double fgZKK2() { return real(fgZKK*conj(fgZKK)); }
inline void resetfgZP()  { fgZP  = fgZPinit; }
inline void resetfgGKK() { fgGKK = fgGKKinit; }
inline void resetfgZKK() { fgZKK = fgZKKinit; }


//////////////////////////////////////////////////////////////////////////////////
// regular couplings

// SM
inline double gG(unsigned int id)  { return qf(id); }
inline double gZL(unsigned int id) { return (I3f(id)-qf(id)*sw2)/sqrt(sw2*cw2); }
inline double gZR(unsigned int id) { return -qf(id)*sw2/sqrt(sw2*cw2); }
inline double gZH(unsigned int id, double h)
{
	if     (h==-f12) return gZL(id);
	else if(h==+f12) return gZR(id);
	else _FATAL("unknown helicity: "+_s(h));
	return 0.;
}

// E6
inline double gVE6(unsigned int id)
{
	double gV = 0.;
	
	// if     (id==s2f["nuel"]->id || id==s2f["numu"]->id || id==s2f["nutau"]->id) gV = 1./6.*sqrt(5./2.)*cos(thetaE6)-3./2.*sqrt(1./6.)*sin(thetaE6);
	// else if(id==s2f["elec"]->id || id==s2f["muon"]->id || id==s2f["tau"]->id)   gV = -2./sqrt(6.)*sin(thetaE6);
	// else if(id==s2f["up"]->id   || id==s2f["chm"]->id  || id==s2f["top"]->id)   gV = 0.;
	// else if(id==s2f["dwn"]->id  || id==s2f["str"]->id  || id==s2f["bot"]->id)   gV = +2./sqrt(6.)*sin(thetaE6);
	// else _FATAL("id="+_s(id)+" is not supported");
	// return gV;
	
	if     (id==s2f["nuel"]->id || id==s2f["numu"]->id || id==s2f["nutau"]->id) gV =1./6.*(sqrt(10.)*cos(thetaE6)-3.*sqrt(6.)*sin(thetaE6))*sqrt(sw2);
	else if(id==s2f["elec"]->id || id==s2f["muon"]->id || id==s2f["tau"]->id)   gV = -4./sqrt(6.)*sin(thetaE6)*sqrt(sw2);
	else if(id==s2f["up"]->id   || id==s2f["chm"]->id  || id==s2f["top"]->id)   gV = 0.;
	else if(id==s2f["dwn"]->id  || id==s2f["str"]->id  || id==s2f["bot"]->id)   gV = +4./sqrt(6.)*sin(thetaE6)*sqrt(sw2);
	else _FATAL("id="+_s(id)+" is not supported");
	return gV;
}
inline double gAE6(unsigned int id)
{
	double gA = 0.;
	
	// if     (id==s2f["nuel"]->id || id==s2f["numu"]->id || id==s2f["nutau"]->id) gA = 1./6.*sqrt(5./2.)*cos(thetaE6)-3./2.*sqrt(1./6.)*sin(thetaE6);
	// else if(id==s2f["elec"]->id || id==s2f["muon"]->id || id==s2f["tau"]->id)   gA = 1./3.*sqrt(5./2.)*cos(thetaE6)-sqrt(1./6.)*sin(thetaE6);
	// else if(id==s2f["up"]->id   || id==s2f["chm"]->id  || id==s2f["top"]->id)   gA = 1./3.*sqrt(5./2.)*cos(thetaE6)+sqrt(1./6.)*sin(thetaE6);
	// else if(id==s2f["dwn"]->id  || id==s2f["str"]->id  || id==s2f["bot"]->id)   gA = 1./3.*sqrt(5./2.)*cos(thetaE6)-sqrt(1./6.)*sin(thetaE6);
	// else _FATAL("id="+_s(id)+" is not supported");
	// return gA;
	
	if     (id==s2f["nuel"]->id || id==s2f["numu"]->id || id==s2f["nutau"]->id) gA = 1./6.*(sqrt(10.)*cos(thetaE6)-3.*sqrt(6.)*sin(thetaE6))*sqrt(sw2);
	else if(id==s2f["elec"]->id || id==s2f["muon"]->id || id==s2f["tau"]->id)   gA = 1./3.*(sqrt(10.)*cos(thetaE6)-sqrt(6.)*sin(thetaE6))*sqrt(sw2);
	else if(id==s2f["up"]->id   || id==s2f["chm"]->id  || id==s2f["top"]->id)   gA = 1./3.*(sqrt(10.)*cos(thetaE6)+sqrt(6.)*sin(thetaE6))*sqrt(sw2);
	else if(id==s2f["dwn"]->id  || id==s2f["str"]->id  || id==s2f["bot"]->id)   gA = 1./3.*(sqrt(10.)*cos(thetaE6)-sqrt(6.)*sin(thetaE6))*sqrt(sw2);
	else _FATAL("id="+_s(id)+" is not supported");
	return gA;
}
inline double gLE6(unsigned int id) { return /* (gVE6(id)+gAE6(id))/2.; */ /* (1./sqrt(sw2*cw2))*(gVE6(id)+gAE6(id))/2.; */ (1./(2.*sqrt(cw2*sw2)))*(gVE6(id)+gAE6(id))/2.; }
inline double gRE6(unsigned int id) { return /* (gVE6(id)-gAE6(id))/2.; */ /* (1./sqrt(sw2*cw2))*(gVE6(id)-gAE6(id))/2.; */ (1./(2.*sqrt(cw2*sw2)))*(gVE6(id)-gAE6(id))/2.; }
inline double gHE6(unsigned int id, double h)
{
	if     (h==-f12) return gLE6(id);
	else if(h==+f12) return gRE6(id);
	else _FATAL("unknown helicity: "+_s(h));
	return 0.;
}

// ZP (real methods for ZP are like for Z0)
inline dcomplex fgZPL(unsigned int id)           { return fgZP*gZL(id); }
inline dcomplex fgZPR(unsigned int id)           { return fgZP*gZR(id); }
inline dcomplex fgZPH(unsigned int id, double h) { return fgZP*gZH(id,h); }

// ZP E6 
inline dcomplex fgE6L(unsigned int id)           { return fgZP*gLE6(id); }
inline dcomplex fgE6R(unsigned int id)           { return fgZP*gRE6(id); }
inline dcomplex fgE6H(unsigned int id, double h) { return fgZP*gHE6(id,h); }

// KK (no scale)
inline double qGKK(unsigned int id)            { return sq2*gG(id); }
inline double gZKKR(unsigned int id)           { return sq2*gZR(id); }
inline double gZKKL(unsigned int id)           { return sq2*gZL(id); }
inline double gZKKH(unsigned int id, double h) { return sq2*gZH(id,h); }

// KK with scale
inline dcomplex fqGKK(unsigned int id)            { return fgGKK*qGKK(id); }
inline dcomplex fgZKKR(unsigned int id)           { return fgZKK*gZKKR(id); }
inline dcomplex fgZKKL(unsigned int id)           { return fgZKK*gZKKL(id); }
inline dcomplex fgZKKH(unsigned int id, double h) { return fgZKK*gZKKH(id,h); }



}

#endif

