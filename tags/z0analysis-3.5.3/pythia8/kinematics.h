#include "basics.h"

#ifndef KINEMATICS_H
#define KINEMATICS_H

inline float imass( TLorentzVector* pa, TLorentzVector* pb )
{
	TLorentzVector pTmp = (*pa)+(*pb);
	return pTmp.M();
}

inline float QT( TLorentzVector* pa, TLorentzVector* pb )
{
	TLorentzVector pTmp = (*pa)+(*pb);
	return pTmp.Perp();
}

inline float ySystem( TLorentzVector* pa, TLorentzVector* pb )
{
	TLorentzVector pTmp = (*pa)+(*pb);
	return pTmp.Rapidity();
}

inline float chi( TLorentzVector* pa, TLorentzVector* pb )
{
	return TMath::Exp(fabs(pa->Rapidity()-pb->Rapidity()));
}

inline float yStar( TLorentzVector* pa, TLorentzVector* pb )
{
	return (pa->Rapidity()-pb->Rapidity())/2.;
}

inline float yB( TLorentzVector* pa, TLorentzVector* pb )
{
	return (pa->Rapidity()+pb->Rapidity())/2.;
}

inline float betaSystem( TLorentzVector* pa, TLorentzVector* pb )
{
	TLorentzVector pTmp = (*pa)+(*pb);
	return pTmp.Beta();
}

inline TVector3 systemBoostVector( TLorentzVector* pa, TLorentzVector* pb )
{
	TLorentzVector pTmp = (*pa)+(*pb);
	return pTmp.BoostVector();
}

inline TLorentzVector* Boost( TLorentzVector* pBoost, TLorentzVector* p )
{
	TLorentzVector* pBoosted = (TLorentzVector*)p->Clone("");
	pBoosted->Boost(-1.*pBoost->BoostVector());
	return pBoosted;
}

inline TLorentzVector* Boost( TLorentzVector* pa, TLorentzVector* pb, TLorentzVector* p )
{
	TLorentzVector pTmp = (*pa)+(*pb);
	TLorentzVector* pBoosted = (TLorentzVector*)p->Clone("");
	pBoosted->Boost(-1.*pTmp.BoostVector());
	return pBoosted;
}

inline float betazSystem( TLorentzVector* pa, TLorentzVector* pb )
{
	TLorentzVector pTmp = (*pa)+(*pb);
	return (pTmp.Mag()!=0.) ? pTmp.Pz()/pTmp.Mag() : -999.;
}

inline float betaTSystem( TLorentzVector* pa, TLorentzVector* pb )
{
	TLorentzVector pTmp = (*pa)+(*pb);
	return (pTmp.Mag()!=0.) ? pTmp.Pt()/pTmp.Mag() : -999.;
}

inline float betaSystem( float pa, float pb, float ea, float eb )
{
	return ((ea+eb)>0.) ? (pa+pb)/(ea+eb) : -999.;
}

inline float cosThetaBoost( TLorentzVector* pa, float ca, TLorentzVector* pb, float cb )
{
	// http://xrootd.slac.stanford.edu/BFROOT/www/doc/workbook_backup_010108/analysis/analysis.html
	// A useful quantity in many analyses is the helicity angle.
	// In the reaction Y -> X -> a + b, the helicity angle of 
	// particle a is the angle measured in the rest frame of the
	//decaying parent particle, X, between the direction of the
	// decay daughter a and the direction of the grandparent particle Y.

	TLorentzVector pTmp = (*pa)+(*pb); // this is the mumu system (Z) 4vector
	TVector3 ZboostVector = pTmp.BoostVector(); // this is the 3vector of the Z
	TLorentzVector p; // this is the muon 4vector
	
	if(ca<0)      p.SetPxPyPzE(pa->Px(),pa->Py(),pa->Pz(),pa->E());
	else if(cb<0) p.SetPxPyPzE(pb->Px(),pb->Py(),pb->Pz(),pb->E());
	p.Boost( -ZboostVector ); // boost p to the dimuon CM (rest) frame
	float cosThetaB = p.Vect()*pTmp.Vect()/(p.P()*pTmp.P());
	//if (ySystem(pa,pb) < 0) cosThetaB *= -1.; // reclassify ???
	return cosThetaB;
}

inline float cosThetaCollinsSoper( TLorentzVector* pa, float ca, TLorentzVector* pb, float cb )
{
	// this will work only for leptons e, mu and tau
	// by default it is assumed that pa is the lepton
	// if instead pb is the lepton, then the result is
	// reclassified by a (-) sign - see line 4.
	float mass2 = imass(pa,pb)*imass(pa,pb);
	float QT2 = QT(pa,pb)*QT(pa,pb);
	//float cosThetaCS = 2.*( pa->Plus()*pb->Minus() - pa->Minus()*pb->Plus() ) / sqrt( mass2 * (mass2 + QT2) );
	float cosThetaCS = 2.*( pa->Pz()*pb->E() - pa->E()*pb->Pz() ) / sqrt( mass2 * (mass2 + QT2) );
	if (ca>0. && cb<0.)     cosThetaCS *= -1.; // if pb is the lepton
	if (ySystem(pa,pb) < 0) cosThetaCS *= -1.; // reclassify
	return cosThetaCS;
}

#endif

