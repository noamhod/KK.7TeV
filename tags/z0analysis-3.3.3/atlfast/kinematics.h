#include "basics.h"

#ifndef KINEMATICS_H
#define KINEMATICS_H

inline void pTSort(TMapdi& pTtoIndex, int& index_a, int& index_b)
{
	// the map is already sorted by the pT size but,
	// from the lowest to the highest, so there's
	// no need to convert values.
	// the following line defines the reversed iterator
	// so the "rbegin()" points the iterator to the entry
	// with the largest pT and so on.
	
	if(pTtoIndex.size()<2)
	{
		cout << "ERROR: in pTSort(TMapdi& pTtoIndex, int& index_a, int& index_b), trying to sort a <2 map. Exitting now !" << endl;
		exit(-1);
	}
	
	///////////////////////////////////////////////////////////////////////////////
	// no matter how many entries in the map, just take the 2 with highest pT: ////
	TMapdi::reverse_iterator rit=pTtoIndex.rbegin(); //////////////////////////////
	index_a = rit->second; ///////////////////////////////////////////////////////
	rit++; ////////////////////////////////////////////////////////////////////////
	index_b = rit->second; ///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
}

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

