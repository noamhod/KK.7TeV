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

namespace couplings
{

static bool doScale = false;

ui2fermion ui2f;
s2fermion  s2f;

void setFermions()
{
	ui2f.insert( make_pair(1,  new fermion("dwn",     1, 5.7*MeV2GeV,     -f13, -f12) ) );
	ui2f.insert( make_pair(2,  new fermion("up",      2, 3.1*MeV2GeV,     +f23, +f12) ) );
	ui2f.insert( make_pair(3,  new fermion("strange", 3, 100.*MeV2GeV,    -f13, -f12) ) );
	ui2f.insert( make_pair(4,  new fermion("charm",   4, 1290.*MeV2GeV,   +f23, +f12) ) );
	ui2f.insert( make_pair(5,  new fermion("bottom",  5, 4670.*MeV2GeV,   -f13, -f12) ) );
	ui2f.insert( make_pair(6,  new fermion("top",     6, 172900.*MeV2GeV, +f23, +f12) ) );
	ui2f.insert( make_pair(11, new fermion("electron",     11, 0.511*MeV2GeV,   -1., -f12) ) );
	ui2f.insert( make_pair(12, new fermion("neutrino e",   12, 0.*MeV2GeV,       0., +f12) ) );
	ui2f.insert( make_pair(13, new fermion("muon",         13, 105.6*MeV2GeV,   -1., -f12) ) );
	ui2f.insert( make_pair(14, new fermion("neutrino mu",  14, 0.*MeV2GeV,       0., +f12) ) );
	ui2f.insert( make_pair(15, new fermion("tau",          15, 1776.82*MeV2GeV, -1., -f12) ) );
	ui2f.insert( make_pair(16, new fermion("neutrino tau", 16, 0.*MeV2GeV,       0., +f12) ) );
	
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
inline double gZL(unsigned int id) { return -qf(id)*sw2/sqrt(sw2*cw2); }
inline double gZR(unsigned int id) { return (I3f(id)-qf(id)*sw2)/sqrt(sw2*cw2); }
inline double gZH(unsigned int id, double h)
{
	if     (h==-f12) return gZL(id);
	else if(h==+f12) return gZR(id);
	else { cerr << "unknown helicity: " << h << endl; exit(-1); }
	return 0.;
}

// ZP (real methods for ZP are like for Z0)
inline dcomplex fgZPL(unsigned int id)           { return fgZP*gZL(id); }
inline dcomplex fgZPR(unsigned int id)           { return fgZP*gZR(id); }
inline dcomplex fgZPH(unsigned int id, double h) { return fgZP*gZH(id,h); }

// KK
inline double qGKK(unsigned int id)  { return sq2*gG(id); }
inline double gZKKR(unsigned int id) { return sq2*gZR(id); }
inline double gZKKL(unsigned int id) { return sq2*gZL(id); }
inline double gZKKH(unsigned int id, double h)
{
	if     (h==-f12) return gZKKL(id);
	else if(h==+f12) return gZKKR(id);
	else { cerr << "unknown helicity: " << h << endl; exit(-1); }
	return 0.;
}
inline dcomplex fgZKKR(unsigned int id)           { return fgZKK*gZKKR(id); }
inline dcomplex fgZKKL(unsigned int id)           { return fgZKK*gZKKL(id); }
inline dcomplex fgZKKH(unsigned int id, double h) { return fgZKK*gZKKH(id,h); }
inline dcomplex fqGKK(unsigned int id)            { return fgGKK*qGKK(id); }



}

#endif

