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
	b_print     = false;
}

void selection::sfinalize()
{

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 


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

void selection::buildMuonPairMap( TMapii& mupair, TVectorP2VL& pmu )
{
	if(pmu.size()>1)
	{               
		for(int n=0 ; n<(int)pmu.size() ; n++)
		{               
			for(int m=0 ; m<(int)pmu.size() ; m++)
			{
				// dont pair with itself
				if( m==n ) continue;

				// remove overlaps (mupair is a multimap !!!)
				if( removeOverlaps(mupair, n, m) ) continue;

				mupair.insert( make_pair(n,m) );
			}
		}
	}
}




// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

bool selection::oppositeChargePair(vector<float>* vcharge, int a, int b)
{
	return ( vcharge->at(a) * vcharge->at(b) < 0) ? true : false;
}

bool selection::findMostMassivePair(TVectorP2VL& pmu, TMapii& allmupairMap)
{
	bool found = false;
	double current_imass;
	double imassMax = 0.;
	int ai, bi;
	for(TMapii::iterator it=allmupairMap.begin() ; it!=allmupairMap.end() ; ++it)
	{
		ai = it->first;
		bi = it->second;
		
		// find the pair with the largest invariant mass
		current_imass = imass(pmu[ai],pmu[bi]);
		if(current_imass > imassMax)
		{
			imassMax = current_imass;
			found = true;
		}
	}
	
	if(!found)
	{
		if(b_print) cout << "WARNING:  in selection::findMostMassivePair:  didn't find any good muon pair" << endl;
	}
	
	return found;
}

void selection::findMostMassivePair(vector<float>* vcharge, TVectorP2VL& pmu, TMapii& allmupairMap, int& iBest_a, int&iBest_b)
{
	double current_imass;
	double imassMax = 0.;
	int ai, bi;
	iBest_a = 0;
	iBest_b = 0;
	for(TMapii::iterator it=allmupairMap.begin() ; it!=allmupairMap.end() ; ++it)
	{
		ai = it->first;
		bi = it->second;
		
		// find the mu+mu- pair with the largest invariant mass
		// and set the incices of the two muons (by charge)
		if( oppositeChargePair(vcharge,ai,bi) )
		{
			current_imass = imass(pmu[ai],pmu[bi]);
			if(current_imass > imassMax)
			{
				imassMax = current_imass;
				iBest_a = ai;
				iBest_b = bi;
			}
		}
	}
}

void selection::findMostHipTPair(vector<float>* mu_pt, int& iBest_a, int&iBest_b)
{
	int vSize = (int)mu_pt->size();
	vector<float> tmp_pt;
	for(int i=0 ; i<vSize ; i++) tmp_pt.push_back( mu_pt->at(i) );
	sort(tmp_pt.begin(), tmp_pt.end());

	for(int i=0 ; i<vSize ; i++)
	{
		if(mu_pt->at(i)==tmp_pt[vSize-1]  &&  tmp_pt[vSize-1]!=tmp_pt[vSize-2]) iBest_a = i;
		if(mu_pt->at(i)==tmp_pt[vSize-2]  &&  tmp_pt[vSize-1]!=tmp_pt[vSize-2]) iBest_b = i;
	}
}

bool selection::findBestVertex(int nTracksCut, int nTypeCut, double z0Cut, int nvxp,
							   vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z)
{
	bool found = false;

	int   nPVtracks;
	int   nPVtype;
	float dPVz0;
	for(int i=0 ; i<nvxp ; i++)
	{
		nPVtracks = v_vxp_nTracks->at(i);
		nPVtype   = v_vxp_type->at(i);
		dPVz0     = fabs( v_vxp_z->at(i) );
		
		if(nPVtracks>nTracksCut  &&  nPVtype==nTypeCut  &&  dPVz0<z0Cut) found = true;
	}
	
	if(!found)
	{
		if(b_print) cout << "WARNING:  in selection::findBestVertex:  didn't find any good vertex" << endl;
	}
	
	return found;
}

int selection::getPVindex(int nTracksCut, int nTypeCut, double z0Cut, int nvxp,
						  vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z)
{
	int   nPVtracks;
	int   nPVtype;
	float dPVz0;
	float z0min = 9999;
	int   index = 0;
	for(int i=0 ; i<(int)nvxp ; i++)
	{
		nPVtracks = v_vxp_nTracks->at(i);
		nPVtype   = v_vxp_type->at(i);
		dPVz0     = fabs( v_vxp_z->at(i) );
		if(nPVtracks>nTracksCut  &&  nPVtype==nTypeCut  &&  dPVz0<z0Cut)
		{
			if(dPVz0<z0min)
			{
				z0min = dPVz0;
				index = i;
			}
		}
	}
	return index;
}

bool selection::findHipTmuon(double hipTmuonCut, double MShipTmuonCut, int nmu,
							 vector<float>* v_pT, vector<float>* v_qoverp, vector<float>* v_theta )
{
	bool found = false;
	
	double pt;
	double pTms;
	double qOp;
	double theta;

	for(int i=0 ; i<nmu ; i++)
	{
		pt    = v_pT->at(i) * MeV2TeV;     //mu_staco_pt->at(i);
		qOp   = v_qoverp->at(i) / MeV2TeV; //mu_staco_me_qoverp->at(i);
		theta = v_theta->at(i);  //mu_staco_me_theta->at(i);
		pTms  = pT(qOp, theta);
		
		if(pt > hipTmuonCut)   found = true;
		if(pTms > MShipTmuonCut) found = true;
	}
	
	if(!found)
	{
		if(b_print) cout << "WARNING:  in selection::findHipTmuon:  didn't find any hipT muon" << endl;
	}
	
	return found;
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

bool selection::isEF_muXCut( double isEF_muXCutVal, int isEF_muX )
{
	if(b_print) cout << "in isEF_muXCut: isEF_muX=" << isEF_muX << endl;
	return ( (double)isEF_muX == isEF_muXCutVal ) ? true : false;
}

bool selection::triggerCut( double triggerCutVal, int isTrigger, string triggerName )
{
	if(b_print) cout << "in triggerCut: triggerName=" << triggerName << " value=" << isTrigger << endl;
	return ( (double)isTrigger == triggerCutVal ) ? true : false;
}

bool selection::pTCut( double pTCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in pTCut: pT(pa)=" << pT(pa) << ", pT(pb)=" << pT(pb) << endl;
	return ( fabs(pT(pa))>pTCutVal  &&  fabs(pT(pb))>pTCutVal ) ? true : false;
}

bool selection::pTCut( double pTCutVal, double pT )
{
	pT *= MeV2TeV;
	if(b_print) cout << "in pTCut: pT=" << pT << endl;
	return ( fabs(pT)>pTCutVal ) ? true : false;
}

bool selection::pTCut( double pTCutVal, double me_qOp_a, double me_theta_a, double me_qOp_b, double me_theta_b )
{
	// pT=|p|*sin(theta)
	// qOp=charge/|p|
	double pT_a = pT(me_qOp_a, me_theta_a);
	double pT_b = pT(me_qOp_b,me_theta_b);
	pT_a *= MeV2TeV;
	pT_b *= MeV2TeV;
	
	if(b_print) cout << "in pTCut: pT(a)=" << pT_a << ", pT(b)=" << pT_b << endl;
	return ( fabs(pT_a)>pTCutVal  &&  fabs(pT_b)>pTCutVal ) ? true : false;
}

bool selection::pTCut( double pTCutVal, double me_qOp, double me_theta )
{
	// pT=|p|*sin(theta)
	// qOp=charge/|p|
	double pt = pT(me_qOp,me_theta);
	pt *= MeV2TeV;
	
	if(b_print) cout << "in pTCut: pT=" << pt << endl;
	return ( fabs(pt)>pTCutVal ) ? true : false;
}

bool selection::etaCut( double etaCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in etaCut: eta(pa)=" << eta(pa) << ", eta(pb)=" << eta(pb) << endl;
	return ( fabs(eta(pa))<etaCutVal  &&  fabs(eta(pb))<etaCutVal ) ? true : false;
}

bool selection::etaCut( double etaCutVal, double eta_a, double eta_b )
{
	if(b_print) cout << "in etaCut: eta_a=" << eta_a << ", eta_b=" << eta_b << endl;
	return ( fabs(eta_a)<etaCutVal  &&  fabs(eta_b)<etaCutVal ) ? true : false;
}

bool selection::etaCut( double etaCutVal, double eta )
{
	if(b_print) cout << "in etaCut: eta=" << eta << endl;
	return ( fabs(eta)<etaCutVal ) ? true : false;
}

bool selection::etaTightCut( double etaTightCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in etaTightCut: eta(pa)=" << eta(pa) << ", eta(pb)=" << eta(pb) << endl;
	return ( fabs(eta(pa))<etaTightCutVal  &&  fabs(eta(pb))<etaTightCutVal ) ? true : false;
}

bool selection::etaTightCut( double etaTightCutVal, double eta_a, double eta_b )
{
	if(b_print) cout << "in etaTightCut: eta_a=" << eta_a << ", eta_b=" << eta_b << endl;
	return ( fabs(eta_a)<etaTightCutVal  &&  fabs(eta_b)<etaTightCutVal ) ? true : false;
}

bool selection::etaTightCut( double etaTightCutVal, double eta )
{
	if(b_print) cout << "in etaTightCut: eta=" << eta << endl;
	return ( fabs(eta)<etaTightCutVal ) ? true : false;
}

bool selection::imassCut( double imassCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in imassCut: imass(pa,pb)=" << imass(pa,pb) << endl;
	return ( imass(pa,pb) > imassCutVal ) ? true : false;
}

bool selection::cosThetaDimuCut( double cosThetaDimuCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in cosThetaDimuCut: cosThetaDimu(pa,pb)=" << cosThetaDimu(pa,pb) << endl;
	return ( cosThetaDimu(pa,pb) > cosThetaDimuCutVal ) ? true : false;
}

bool selection::etaSumCut( double etaSumCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	double etasum = eta(pa) + eta(pb);
	if(b_print) cout << "in etaSum: etaSum(a,b)=" << etasum << endl;
	return ( fabs(etasum) < etaSumCutVal ) ? true : false;
}

bool selection::oppositeChargeCut( double ca, double cb )
{
	if(b_print) cout << "in oppositeCharge: ca=" << ca << ", cb=" << cb << endl;
	return ( ca*cb<0 ) ? true : false;
}

bool selection::oppositeChargeCut( double oppositeChargeCutVal, double ca, double cb )
{
	if(b_print) cout << "in oppositeCharge: ca=" << ca << ", cb=" << cb << endl;
	return ( ca*cb<oppositeChargeCutVal ) ? true : false;
}

bool selection::d0Cut( double d0CutVal, double d0a, double d0b )
{
	if(b_print) cout << "in d0Cut: d0=" << d0a << ", d0b=" << d0b << endl;
	return ( fabs(d0a)<d0CutVal  &&  fabs(d0b)<d0CutVal ) ? true : false;
}

bool selection::d0Cut( double d0CutVal, double d0 )
{
	if(b_print) cout << "in d0Cut: d0=" << d0 << endl;
	return ( fabs(d0)<d0CutVal ) ? true : false;
}

bool selection::z0Cut( double z0CutVal, double z0a, double z0b )
{
	if(b_print) cout << "in z0Cut: z0=" << z0a << ", z0b=" << z0b << endl;
	return ( fabs(z0a)<z0CutVal  &&  fabs(z0b)<z0CutVal ) ? true : false;
}

bool selection::z0Cut( double z0CutVal, double z0 )
{
	if(b_print) cout << "in z0Cut: z0=" << z0 << endl;
	return ( fabs(z0)<z0CutVal ) ? true : false;
}

bool selection::prmVtxNtracksCut( double prmVtxNtracksCutVal, int nPVtracks )
{
	/*vxp_nTracks=number of tracks > 2*/
	if(b_print) cout << "in prmVtxNtracksCut: nPVtracks=" << nPVtracks << endl;
	return ( (double)nPVtracks > prmVtxNtracksCutVal ) ? true : false;
}

bool selection::prmVtxTypeCut( double prmVtxTypeCutVal, int nPVtype )
{
	/*vxp_type==1*/
	if(b_print) cout << "in prmVtxTypeCut: nPVtype=" << nPVtype << endl;
	return ( (double)nPVtype == prmVtxTypeCutVal ) ? true : false;
}

bool selection::prmVtxZ0Cut( double prmVtxZ0CutVal, double dPVz0, double dPVz0err )
{
	dPVz0err = 0; // USE IT ??????????????????????????????????????????????
	
	/*vxp_z=absolute z position of primary vertex < 150mms*/
	if(b_print) cout << "in prmVtxZ0Cut: dPVz0=" << dPVz0 << endl;
	return ( fabs(dPVz0) < prmVtxZ0CutVal ) ? true : false;
}

bool selection::isCombMuCut( double isCombMuCutVal, int isCombMua, int isCombMub )
{
	/*mu_staco_isCombinedMuon*/
	if(b_print) cout << "in isCombMuCut: isCombMua=" << isCombMua << ", isCombMub=" << isCombMub << endl;
	return ( (double)isCombMua == isCombMuCutVal && (double)isCombMub == isCombMuCutVal ) ? true : false; // both are comb mu
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

bool selection::pTmatchRatioCut(double pTmatchHighRatioCutVal,
								double pTmatchLowRatioCutVal,
								double me_qOp, double me_theta,
								double id_qOp, double id_theta )
{
	// pT=|p|*sin(theta)
	// qOp=charge/|p|
	double pT_id = pT(id_qOp,id_theta);
	double pT_ms = pT(me_qOp,me_theta);
	pT_id *= MeV2TeV;
	pT_ms *= MeV2TeV;
	
	double ratio = (pT_id!=0.) ? fabs(pT_ms/pT_id) : 0.;
	
	/* mu_staco_me_qover_p, mu_staco_me_theta, mu_staco_id_qover_p, mu_staco_id_theta */
	// pT ratio of Muon Extrapolated track to ID track greater than 0.5
	if(b_print) cout << "in pTmatchLowRatioCut: pT_id=" << pT_id << ", pT_ms=" << pT_ms << endl;
	return ( ratio > pTmatchLowRatioCutVal  &&  ratio < pTmatchHighRatioCutVal) ? true : false;
}

bool selection::pTmatchAbsDiffCut(double pTmatchDiffCutVal,
								  double me_qOp, double me_theta,
								  double id_qOp, double id_theta )
{
	// pT=|p|*sin(theta)
	// qOp=charge/|p|
	double pT_id = pT(id_qOp,id_theta);
	double pT_ms = pT(me_qOp,me_theta);
	pT_id *= MeV2TeV;
	pT_ms *= MeV2TeV;
	
	double diff = fabs(pT_ms - pT_id);
	
	/* mu_staco_me_qover_p, mu_staco_me_theta, mu_staco_id_qover_p, mu_staco_id_theta */
	// pT ratio of Muon Extrapolated track to ID track greater than 0.5
	if(b_print) cout << "in pTmatchDiffCut: pT_id=" << pT_id << ", pT_ms=" << pT_ms << endl;
	return ( diff < pTmatchDiffCutVal) ? true : false;
}

bool selection::isolationXXCut( double isolationCutVal, string sIsoValName, double pTmu, double pTcone )
{
	/*mu_staco_ptcone20, mu_staco_pt*/
	// track sum pT in 0.2 cone relative to muon pT less than 0.05
	pTmu   *= MeV2TeV;
	pTcone *= MeV2TeV;
	double isolation = (pTmu==0) ? 999 : pTcone/pTmu;
	
	if(b_print) cout << "in isolationXXCut: isolation(" << sIsoValName << ")=" << isolation << endl;
	return ( isolation < isolationCutVal ) ? true : false;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

bool selection::primaryVertexCut( double prmVtxNtracksCutVal, double prmVtxTypeCutVal, double prmVtxZ0CutVal,
								  vector<int>* pviPVtracks,
								  vector<int>* pviPVtype,
								  vector<float>* pvfPVz0,
								  vector<float>* pvfPVz0err,
								  int& bestVtxIndex)
{

	int nPVtracks;
	int nPVtype;
	float dPVz0;
	float dPVz0err;
	double minPVz0 = prmVtxZ0CutVal;
	
	int nPassed = 0;
	
	/////////////////////
	bestVtxIndex = 0; ///
	/////////////////////

	bool bPassed = true;
	for(int i=0 ; i<(int)pviPVtracks->size() ; i++)
	{
		bPassed = true;
		
		nPVtracks = pviPVtracks->at(i);
		nPVtype   = pviPVtype->at(i);
		dPVz0     = fabs( pvfPVz0->at(i) );
		dPVz0err  = pvfPVz0err->at(i);
		
		if( !prmVtxNtracksCut(prmVtxNtracksCutVal, nPVtracks) )
		{
			bPassed = false;
			if(b_print) cout << "\t\tin primaryVertexCut:prmVtxNtracksCut nPVtracks=" << nPVtracks << endl;
		}
		if( !prmVtxTypeCut(prmVtxTypeCutVal, nPVtype) )
		{
			bPassed = false;
			if(b_print) cout << "\t\tin primaryVertexCut:prmVtxTypeCut nPVtype=" << nPVtype << endl;
		}
		if( !prmVtxZ0Cut(prmVtxZ0CutVal, dPVz0, dPVz0err) )
		{
			bPassed = false;
			if(b_print) cout << "\t\tin primaryVertexCut:prmVtxZ0Cut dPVz0=" << dPVz0 << endl;
		}
		
		nPassed += (bPassed) ? 1 : 0;
		if(dPVz0 < minPVz0)
		{
			minPVz0      = dPVz0;
			bestVtxIndex = i; // return the best vertex
		}
	}
	
	if(b_print) { cout << "\t\tnPassed=" << nPassed << endl; }
	
	return (nPassed>0) ? true : false; // MOVE THIS HARD-CODED VALUE TO THE CUTFLOW FILE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

bool selection::nIDhitsCut( double nSCThitsCutVal, double nPIXhitsCutVal, double nIDhitsCutVal, int nSCThits, int nPIXhits )
{
	if( !nSCThitsCut(nSCThitsCutVal,nSCThits) )
	{
		if(b_print) cout << "in nIDhitsCut:nSCThitsCut nSCThits=" << nSCThits << endl;
		return false;
	}
	if( !nPIXhitsCut(nPIXhitsCutVal,nPIXhits) )
	{
		if(b_print) cout << "in nIDhitsCut:nPIXhitsCut nPIXhits=" << nPIXhits << endl;
		return false;
	}
	
	int nIDhits = nSCThits+nPIXhits;
	if( nIDhits < nIDhitsCutVal )
	{
		if(b_print) cout << "in nIDhitsCut: nIDhits=" << nIDhits << endl;
		return false;
	}
	
	return true;
}

bool selection::nMS3stationsMDThits(double nMDTIHitsCutVal, double nMDTMHitsCutVal, double nMDTOHitsCutVal, double nMDTBEEHitsCutVal, double nMDTBIS78HitsCutVal,
									int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
									int nMDTEIHits, int nMDTEMHits, int nMDTEOHits,
									int nMDTBEEHits, int nMDTBIS78Hits)
{
	// Require 3 stations on the muon track, i.e. hits in the Inner, Middle and Outer chambers;
	// Reject muons with hits in BEE, BIS7 and BIS8
	
	bool passedB = true;
	passedB = (passedB  &&  nMDTBIHits >= nMDTIHitsCutVal) ? true  : false;
	passedB = (passedB  &&  nMDTBMHits >= nMDTMHitsCutVal) ? true  : false;
	passedB = (passedB  &&  nMDTBOHits >= nMDTOHitsCutVal) ? true  : false;
	
	bool passedE = true;
	passedE = (passedE  &&  nMDTEIHits >= nMDTIHitsCutVal) ? true  : false; 
	passedE = (passedE  &&  nMDTEMHits >= nMDTMHitsCutVal) ? true  : false;
	passedE = (passedE  &&  nMDTEOHits >= nMDTOHitsCutVal) ? true  : false;
	
	bool passed = true;
	passed = (passed  &&  (passedB || passedE)  &&  nMDTBEEHits ==   nMDTBEEHitsCutVal)   ? true : false;
	passed = (passed  &&  (passedB || passedE)  &&  nMDTBIS78Hits == nMDTBIS78HitsCutVal) ? true : false;
	
	return passed;
}

bool selection::pTmatchingRatioCut( double pTmatchHighRatioCutVal,
									double pTmatchLowRatioCutVal,
									double me_qOp_a, double me_theta_a,
									double id_qOp_a, double id_theta_a,
									double me_qOp_b, double me_theta_b,
									double id_qOp_b, double id_theta_b
								   )
{
	// at least one has to pass
	bool bPassed = true;
	int nPassed = 0;
	if( !pTmatchRatioCut(pTmatchHighRatioCutVal, pTmatchLowRatioCutVal, me_qOp_a, me_theta_a, id_qOp_a, id_theta_a) )
	{
		bPassed = false;
		if(b_print) cout << "in pTmatching:pTmatchRatioCut: mu(a)" << endl;
	}
	else nPassed++;
	if( !pTmatchRatioCut(pTmatchHighRatioCutVal, pTmatchLowRatioCutVal, me_qOp_b, me_theta_b, id_qOp_b, id_theta_b) )
	{
		bPassed = false;
		if(b_print) cout << "in pTmatching:pTmatchRatioCut: mu(b)" << endl;
	}
	else nPassed++;
	
	return (bPassed || nPassed>0) ? true : false;
}

bool selection::pTmatchingAbsDiffCut( double pTmatchDiffCutVal,
									  double me_qOp_a, double me_theta_a,
									  double id_qOp_a, double id_theta_a,
									  double me_qOp_b, double me_theta_b,
									  double id_qOp_b, double id_theta_b
									)
{
	// at least one has to pass
	bool bPassed = true;
	int nPassed = 0;
	
	if( !pTmatchAbsDiffCut(pTmatchDiffCutVal, me_qOp_a, me_theta_a, id_qOp_a, id_theta_a) )
	{
		bPassed = false;
		if(b_print) cout << "in pTmatching:pTmatchAbsDiffCut: mu(a)" << endl;
	}
	else nPassed++;
	if( !pTmatchAbsDiffCut(pTmatchDiffCutVal, me_qOp_b, me_theta_b, id_qOp_b, id_theta_b) )
	{
		bPassed = false;
		if(b_print) cout << "in pTmatching:pTmatchAbsDiffCut: mu(b)" << endl;
	}
	else nPassed++;
	
	return (bPassed || nPassed>0) ? true : false;
}

bool selection::impactParameterCut( double d0CutVal, double z0CutVal,
									double d0a, double d0b,
									double z0a, double z0b )
{
	bool bPassed = true;

	if( !d0Cut(d0CutVal, d0a, d0b) )
	{
		bPassed = false;
		if(b_print) cout << "in impactParameter:d0Cut  d0a=" << d0a << ", d0b=" << d0b << endl;
	}
	if( !z0Cut(z0CutVal, z0a, z0b) )
	{
		bPassed = false;
		if(b_print) cout << "in impactParameter:z0Cut  z0a=" << z0a << ", z0b=" << z0b << endl;
	}
	
	return (bPassed) ? true : false;
}

bool selection::impactParameterCut( double d0CutVal, double z0CutVal, double d0, double z0 )
{
	if( !d0Cut(d0CutVal, d0) ) return false;
	if( !z0Cut(z0CutVal, z0) ) return false;
	
	return true;
}

bool selection::pTandEtaTightCut( double pTCutVal, double etaTightCutVal, double me_qOp, double me_theta, double eta )
{
	if( !etaTightCut( etaTightCutVal, eta ) )  return false;
	if( !pTCut( pTCutVal, me_qOp, me_theta ) ) return false;
	
	return true;
}

bool selection::pTandEtaTightCut( double pTCutVal, double etaTightCutVal, double pT, double eta )
{
	if( !etaTightCut( etaTightCutVal, eta ) )  return false;
	if( !pTCut( pTCutVal, pT ) )               return false;
	
	return true;
}

bool selection::pairXXisolation( double isolationCutVal, string sIsoValName,
								 double pTmua, double pTmub, double pTconea, double pTconeb )
{
	bool bPassed = true;
	
	if( !isolationXXCut(isolationCutVal,sIsoValName,pTmua,pTconea) )
	{
		bPassed = false;
		if(b_print) cout << "in pairXXisolation:isolationXXCut: mu(A)" << endl;
	}
	if( !isolationXXCut(isolationCutVal,sIsoValName,pTmub,pTconeb) )
	{
		bPassed = false;
		if(b_print) cout << "in pairXXisolation:isolationXXCut: mu(B)" << endl;
	}
	
	return (bPassed) ? true : false;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

#endif

