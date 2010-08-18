/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef selection_cxx
#include "selection.h"

selection::selection()
{
	sinitialize();
}

selection::~selection()
{
	sfinalize();
}


void selection::sinitialize()
{
	m_util = new utilities();	

	b_print     = false;
	/*
	d_pTCut          = 15.*m_util->d_toGeV;
	d_etaCut         = 2.4;
	d_d0Cut          = 150.; // mm ?
	d_z0Cut          = 150.; // mm ?
	d_cosThetaDimuCut = -0.9;
	d_imassCut       = 20.*m_util->d_toGeV;
*/
}

void selection::sfinalize()
{
	//delete m_util;
}

void selection::initSelectionCuts(TMapsd* cutFlowMap, TMapds* cutFlowOrdered)
{
	m_cutFlowMap     = cutFlowMap;
	m_cutFlowOrdered = cutFlowOrdered;

	/*
	for(TMapds::iterator ii=cutFlowOrdered->begin() ; ii!=cutFlowOrdered->end() ; ++ii)
	{
		string scutname = ii->second;
		double cutValue = cutFlowMap->operator[](scutname);
		
		if(scutname=="pT")        d_pTCut = cutValue * m_util->d_toGeV;
		if(scutname=="eta")       d_etaCut = cutValue;
		if(scutname=="d0")        d_d0Cut = cutValue;
		if(scutname=="z0")        d_z0Cut = cutValue;
		if(scutname=="cosThetaDimu") d_cosThetaDimuCut = cutValue;
		if(scutname=="imass")     d_imassCut = cutValue * m_util->d_toGeV;
	}
	*/
}

bool selection::pTCut( double pTCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in pTCut: pT(pa)=" << pT(pa) << ", pT(pb)=" << pT(pb) << endl;
	return ( fabs(pT(pa))>=pTCutVal  &&  fabs(pT(pb))>=pTCutVal ) ? true : false;
}

bool selection::etaCut( double etaCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in etaCut: eta(pa)=" << eta(pa) << ", eta(pb)=" << eta(pb) << endl;
	return ( fabs(eta(pa))<=etaCutVal  &&  fabs(eta(pb))<=etaCutVal ) ? true : false;
}

bool selection::imassCut( double imassCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in imassCut: imass(pa,pb)=" << imass(pa,pb) << endl;
	return ( imass(pa,pb) >= imassCutVal ) ? true : false;
}

bool selection::cosThetaDimuCut( double cosThetaDimuCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in cosThetaDimuCut: cosThetaDimu(pa,pb)=" << cosThetaDimu(pa,pb) << endl;
	return ( cosThetaDimu(pa,pb) > cosThetaDimuCutVal ) ? true : false;
}

bool selection::oppositeCharge( double ca, double cb )
{
	if(b_print) cout << "in oppositeCharge: ca=" << ca << ", cb=" << cb << endl;
	return ( ca*cb<0 ) ? true : false;
}

bool selection::d0Cut( double d0CutVal, double d0a, double d0b )
{
	if(b_print) cout << "in d0Cut: d0=" << d0a << ", d0b=" << d0b << endl;
	return ( fabs(d0a)<=d0CutVal  &&  fabs(d0b)<=d0CutVal ) ? true : false;
}

bool selection::z0Cut( double z0CutVal, double z0a, double z0b )
{
	if(b_print) cout << "in d0Cut: z0=" << z0a << ", z0b=" << z0b << endl;
	return ( fabs(z0a)<=z0CutVal  &&  fabs(z0b)<=z0CutVal ) ? true : false;
}

void selection::buildMuonPairMap( 	TMapii& mupair,
									double ca, int ia,
									double cb, int ib)
{
	if(!oppositeCharge(ca,cb)) { if(b_print) {cout << "failed 0 charge cut" << endl;} return; }
	mupair.insert( make_pair(ia,ib) );
}

void selection::buildMuonPairMap( TMapii& mupair,
								  TLorentzVector* pa, double ca, double d0a, double z0a, int ia,
								  TLorentzVector* pb, double cb, double d0b, double z0b, int ib)
{
	// run over all the dimuon-level cuts (i.e., not the event-level cuts such as L1_MU6 or GRL etc.)
	// if one of the dimuon-level cuts fails, return from this function and do not insert this pair
	// into the muPair map.
	// If passed all dimuon-level cuts, then insert this pair into the muPair map.
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		string scutname = ii->second;
		double cutValue = m_cutFlowMap->operator[](scutname);
		
		if(scutname=="oppositeCharcge")      if(!oppositeCharge(ca,cb))           { if(b_print) {cout << "failed 0 charge cut" << endl;} return; }
		if(scutname=="pT")           if(!pTCut(cutValue,pa,pb))           { if(b_print) {cout << "failed pT cut"       << endl;} return; }
		if(scutname=="eta")          if(!etaCut(cutValue,pa,pb))          { if(b_print) {cout << "failed eta cut"      << endl;} return; }
		if(scutname=="d0")           if(!d0Cut(cutValue,d0a,d0b))         { if(b_print) {cout << "failed d0 cut"       << endl;} return; }
		if(scutname=="z0")           if(!z0Cut(cutValue,z0a,z0b))         { if(b_print) {cout << "failed z0 cut"       << endl;} return; }
		if(scutname=="cosThetaDimu") if(!cosThetaDimuCut(cutValue,pa,pb)) { if(b_print) {cout << "failed cosmic cut"   << endl;} return; }
		if(scutname=="imass")        if(!imassCut(cutValue,pa,pb))        { if(b_print) {cout << "failed imass cut"    << endl;} return; }
	}
	/*
	if(!oppositeCharge(ca,cb))             { if(b_print) {cout << "failed 0 charge cut" << endl;} return; }
	if(!pTCut(d_pTCut,pa,pb))              { if(b_print) {cout << "failed pT cut"       << endl;} return; }
	if(!etaCut(d_etaCut,pa,pb))            { if(b_print) {cout << "failed eta cut"      << endl;} return; }
	if(!d0Cut(d_d0Cut,d0a,d0b))            { if(b_print) {cout << "failed d0 cut"       << endl;} return; }
	if(!z0Cut(d_z0Cut,z0a,z0b))            { if(b_print) {cout << "failed z0 cut"       << endl;} return; }
	if(!imassCut(d_imassCut,pa,pb))        { if(b_print) {cout << "failed imass cut"    << endl;} return; }
	if(!cosThetaDimuCut(d_cosThetaDimuCut,pa,pb)) { if(b_print) {cout << "failed cosmic cut"   << endl;} return; } //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ???
	*/
	mupair.insert( make_pair(ia,ib) );
}

bool selection::removeOverlaps( TMapii& mupair, int ia, int ib)
{
	bool docontinue = false;
	for(TMapii::iterator it=mupair.begin() ; it!=mupair.end() ; ++it)
	{
		if(it->first==ia  &&  it->second==ib) {docontinue=true; break;}
		if(it->first==ib  &&  it->second==ia) {docontinue=true; break;}
	}
	if(docontinue) { if(b_print) cout << "overlap removed !" << endl; }
	return docontinue;
}


void selection::findBestMuonPair( TMapii& mupair, int& ia, int& ib)
{
	int n = mupair.size();
	if(b_print) cout << "n=" << n << endl;
	ia = 0;
	ib = 0;
}

#endif

