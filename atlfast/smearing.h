#include "basics.h"

#ifndef SMEARING_H
#define SMEARING_H

const double average    = 0.; // for gaussian smearing
const double stdev      = 1.; // for gaussian smearing
const double resolution = 0.12; // resolution for smearing pT~1TeV
const double pTtrkScale = 1.e+3; // in GeV/c
TRandom* gaussRandGen   = new TRandom();

inline double gaussRand()
{
	return gaussRandGen->Gaus(average, stdev); 
}
inline double smear_pT(double pT)
{
	return 1./(1./pT + gaussRand()*resolution/pTtrkScale);
}
inline double smear_px(double pTsmeared, double phi)
{
	return pTsmeared*cos(phi);
}
inline double smear_py(double pTsmeared, double phi)
{
	return pTsmeared*sin(phi);
}
inline double smear_pz(double pTsmeared, double theta)
{
	return pTsmeared/tan(theta);
}
inline double smear_e(double pTsmeared,  double theta)
{
	return pTsmeared/sin(theta);
}
inline void compare2true(
double px0, double py0, double pz0, double e0,
double pxS, double pyS, double pzS, double eS
)
{
	cout << "(pxS[" << pxS << "]/px0[" << px0 << "] - 1)% = " << (pxS/px0 - 1.)*100 << endl;
	cout << "(pyS[" << pyS << "]/py0[" << py0 << "] - 1)% = " << (pyS/py0 - 1.)*100 << endl;
	cout << "(pzS[" << pzS << "]/pz0[" << pz0 << "] - 1)% = " << (pzS/pz0 - 1.)*100 << endl;
	cout << "(eS[" <<  eS  << "]/e0["  << e0  << "] - 1)% = " << (eS/e0 - 1.)*100 << "\n" << endl;
}

inline void smear(bool print, TLorentzVector* p_orig, TLorentzVector* p_smer, double& cg_smer, int& id_smer)
{	
	double pTSmeared = smear_pT( p_orig->Pt() );
	p_smer->SetPxPyPzE(
	smear_px(pTSmeared,p_orig->Phi()),
	smear_py(pTSmeared,p_orig->Phi()),
	smear_pz(pTSmeared,p_orig->Theta()),
	smear_e(pTSmeared,p_orig->Theta())
	);
	if(pTSmeared<0.)
	{
		cg_smer*=-1.;
		id_smer*=-1;
		if(print) cout << "smeared pT=" << pTSmeared  << " ==> charge flip !" << endl;
	}
	
	if(print)
	{
		compare2true(
		p_orig->Px(),p_orig->Py(),p_orig->Pz(),p_orig->E(),
		p_smer->Px(),p_smer->Py(),p_smer->Pz(),p_smer->E()
		);
	}
}

#endif

