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
}

void selection::sfinalize()
{
	//delete m_util;
}

void selection::initSelectionCuts(TMapsd* cutFlowMap, TMapds* cutFlowOrdered)
{
	m_cutFlowMap     = cutFlowMap;
	m_cutFlowOrdered = cutFlowOrdered;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

bool selection::isGRLCut( double isGRLCutVal, int isGRL )
{
	if(b_print) cout << "in isGRLCut: isGRL=" << isGRL << endl;
	return ( (double)isGRL == isGRLCutVal ) ? true : false;
}

bool selection::isL1_MU6Cut( double isL1_MU6CutVal, int isL1_MU6 )
{
	if(b_print) cout << "in isL1_MU6Cut: isL1_MU6=" << isL1_MU6 << endl;
	return ( (double)isL1_MU6 == isL1_MU6CutVal ) ? true : false;
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

bool selection::oppositeChargeCut( double ca, double cb )
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

bool selection::prmVtxNtracksCut( double prmVtxNtracksCutVal, vector<int>* nPVtracksPtr, int& pvtxIndex )
{
	/*vxp_nTracks=number of tracks > 2*/
//	if(b_print) cout << "in prmVtxNtracksCut: nPVtracks=" << nPVtracks << endl;
//	return ( (double)nPVtracks > prmVtxNtracksCutVal ) ? true : false;
}

bool selection::prmVtxTypeCut( double prmVtxTypeCutVal, vector<int>* nPVtypePtr, int& pvtxIndex )
{
	/*vxp_type==1*/
//	if(b_print) cout << "in prmVtxTypeCut: nPVtype=" << nPVtype << endl;
//	return ( (double)nPVtype == prmVtxTypeCutVal ) ? true : false;
}

bool selection::prmVtxZ0Cut( double prmVtxZ0CutVal, vector<double>* PVz0Ptr, vector<double>* PVz0errPtr, int& pvtxIndex )
{
	/*vxp_z=absolute z position of primary vertex < 150mms*/
//	if(b_print) cout << "in prmVtxZ0Cut: dPVz0=" << dPVz0 << endl;
//	return ( dPVz0 < prmVtxZ0CutVal ) ? true : false;
}

bool selection::isCombMuCut( double isCombMuCutVal, int isCombMu )
{
	/*mu_staco_isCombinedMuon*/
	if(b_print) cout << "in isCombMuCut: isCombMu=" << isCombMu << endl;
	return ( (double)isCombMu == isCombMuCutVal ) ? true : false;
}

bool selection::nSCThitsCut( double nSCThitsCutVal, int nSCThits )
{
	/*mu_staco_nSCTHits :  SCT hits >=4*/
	if(b_print) cout << "in nSCThitsCut: nSCThits=" << nSCThits << endl;
	return ( (double)nSCThits >= nSCThitsCutVal ) ? true : false;
}

bool selection::nPIXhitsCut( double nPIXhitsCutVal, int nPIXhits )
{
	/*mu_staco_nPixHitss  :  pixel hits >=1*/
	if(b_print) cout << "in nPIXhitsCut: nPIXhits=" << nPIXhits << endl;
	return ( (double)nPIXhits >= nPIXhitsCutVal ) ? true : false;
}

bool selection::nIDhitsCut( double nIDhitsCutVal, int nIDhits )
{
	/*mu_staco_nSCTHits, mu_staco_nPixHitss  :  pixel+SCT hits >=5*/
	if(b_print) cout << "in nIDhitsCut: nIDhits=" << nIDhits << endl;
	return ( (double)nIDhits >= nIDhitsCutVal ) ? true : false;
}

bool selection::pTmatchLowRatioCut()
{
	/* mu_staco_me_qover_p, mu_staco_me_theta, mu_staco_id_qover_p, mu_staco_id_theta */
	// pT ratio of Muon Extrapolated track to ID track greater than 0.5
	return true; // ???????????????????????????????????????????????????????????????????????????????????????????
}

bool selection::pTmatchHighRatioCut()
{
	/* mu_staco_me_qover_p, mu_staco_me_theta, mu_staco_id_qover_p, mu_staco_id_theta */
	// pT ratio of Muon Extrapolated track to ID track less than 2
	return true; // ???????????????????????????????????????????????????????????????????????????????????????????
}

bool selection::impcatParamZ0Cut( double impcatParamZ0CutVal, double impPrmZ0)
{
	/*mu_staco_z0_exPV*/
	// Impact Parameter wrt primary vertex in z0 less than 5mm 
	if(b_print) cout << "in impcatParamZ0Cut: impPrmZ0=" << impPrmZ0 << endl;
	return ( impPrmZ0 < impcatParamZ0CutVal ) ? true : false;
}

bool selection::impcatParamD0Cut( double impcatParamD0CutVal, double impPrmD0 )
{
	/*mu_staco_d0_exPV*/
	// Impact Parameter wrt primary vertex in d0 less than 1mm 
	if(b_print) cout << "in impcatParamD0Cut: impPrmD0=" << impPrmD0 << endl;
	return ( impPrmD0 < impcatParamD0CutVal ) ? true : false;
}

bool selection::isolation20Cut( double isolationCutVal, double pTmu, double pTcone )
{
	/*mu_staco_ptcone20, mu_staco_pt*/
	// track sum pT in 0.2 cone relative to muon pT less than 0.05
	
	double isolation = (pTmu==0) ? 999 : pTcone/pTmu;
	
	if(b_print) cout << "in isolation20Cut: isolation 20=" << isolation << endl;
	return ( isolation < isolationCutVal ) ? true : false;
}

bool selection::isolation30Cut( double isolationCutVal, double pTmu, double pTcone )
{
	/*mu_staco_ptcone30, mu_staco_pt*/
	// track sum pT in 0.3 cone relative to muon pT less than 0.05
	
	double isolation = (pTmu==0) ? 999 : pTcone/pTmu;
	
	if(b_print) cout << "in isolation30Cut: isolation 30=" << isolation << endl;
	return ( isolation < isolationCutVal ) ? true : false;
}

bool selection::isolation40Cut( double isolationCutVal, double pTmu, double pTcone )
{
	/*mu_staco_ptcone40, mu_staco_pt*/
	// track sum pT in 0.4 cone relative to muon pT less than 0.05
	
	double isolation = (pTmu==0) ? 999 : pTcone/pTmu;
	
	if(b_print) cout << "in isolation40Cut: isolation 40=" << isolation << endl;
	return ( isolation < isolationCutVal ) ? true : false;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 


void selection::buildMuonPairMap( 	TMapii& mupair,
									double ca, int ia,
									double cb, int ib)
{
	if(!oppositeChargeCut(ca,cb)) { if(b_print) {cout << "failed 0 charge cut" << endl;} return; }
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
		
		if(scutname=="oppositeCharcge")      if(!oppositeChargeCut(ca,cb))           { if(b_print) {cout << "failed 0 charge cut" << endl;} return; }
		if(scutname=="pT")           if(!pTCut(cutValue,pa,pb))           { if(b_print) {cout << "failed pT cut"       << endl;} return; }
		if(scutname=="eta")          if(!etaCut(cutValue,pa,pb))          { if(b_print) {cout << "failed eta cut"      << endl;} return; }
		if(scutname=="d0")           if(!d0Cut(cutValue,d0a,d0b))         { if(b_print) {cout << "failed d0 cut"       << endl;} return; }
		if(scutname=="z0")           if(!z0Cut(cutValue,z0a,z0b))         { if(b_print) {cout << "failed z0 cut"       << endl;} return; }
		if(scutname=="cosThetaDimu") if(!cosThetaDimuCut(cutValue,pa,pb)) { if(b_print) {cout << "failed cosmic cut"   << endl;} return; }
		if(scutname=="imass")        if(!imassCut(cutValue,pa,pb))        { if(b_print) {cout << "failed imass cut"    << endl;} return; }
	}
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

