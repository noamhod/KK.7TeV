/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef kinematics_cxx
#include "kinematics.h"

kinematics::kinematics() {}

kinematics::~kinematics() {}

double kinematics::imass( TLorentzVector* pa, TLorentzVector* pb )
{
	m_pTmp = (*pa)+(*pb);
	return m_pTmp.M();
}

double kinematics::pT( TLorentzVector* p )
{
	return p->Perp();
}

double kinematics::eta( TLorentzVector* p )
{
	return p->PseudoRapidity();
}

double kinematics::dR( TLorentzVector* pa, TLorentzVector* pb )
{
	pa = NULL;
	pb = NULL;
	//return pa->DrEtaPhi(pb);
	return 0.;
}

double kinematics::pAbs( TLorentzVector* p )
{       
	return p->Mag();
}       

double kinematics::cosThetaDimu( TLorentzVector* pa, TLorentzVector* pb )
{
	double paMag = sqrt( pa->Px()*pa->Px() + pa->Py()*pa->Py() + pa->Pz()*pa->Pz() );
	double pbMag = sqrt( pb->Px()*pb->Px() + pb->Py()*pb->Py() + pb->Pz()*pb->Pz() );	
	double costh = (pa->Px()*pb->Px() + pa->Py()*pb->Py() + pa->Pz()*pb->Pz()) / (paMag*pbMag);
	return costh;
}

double kinematics::QT( TLorentzVector* pa, TLorentzVector* pb )
{
	m_pTmp = (*pa)+(*pb);
	return m_pTmp.Perp();
}       

double kinematics::y( TLorentzVector* p )
{       
	return p->Rapidity();
}       

double kinematics::ySystem( TLorentzVector* pa, TLorentzVector* pb )
{
	m_pTmp = (*pa)+(*pb);
	return m_pTmp.Rapidity();
}

double kinematics::cosThetaCollinsSoper( TLorentzVector* pa, double ca,
										 TLorentzVector* pb, double cb )
{
	// this will work only for leptons e, mu and tau
	// by default it is assumed that pa is the lepton
	// if instead pb is the lepton, then the result is
	// reclassified by a (-) sign - see line 4.
	double mass2 = imass(pa,pb)*imass(pa,pb);
	double QT2 = QT(pa,pb)*QT(pa,pb);
	//double cosThetaCS = 2.*( pa->Plus()*pb->Minus() - pa->Minus()*pb->Plus() ) / sqrt( mass2 * (mass2 + QT2) );
	double cosThetaCS = 2.*( pa->Pz()*pb->E() - pa->E()*pb->Pz() ) / sqrt( mass2 * (mass2 + QT2) );
	if (ca>0. && cb<0.)     cosThetaCS *= -1.; // if pb is the lepton
	if (ySystem(pa,pb) < 0) cosThetaCS *= -1.; // reclassify
	return cosThetaCS;
}



#endif

