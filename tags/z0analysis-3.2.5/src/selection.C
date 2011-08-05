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
	b_print = false;
}

void selection::sfinalize()
{

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 


inline bool selection::removeOverlaps( TMapii& mupair, int ia, int ib)
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

inline void selection::buildMuonPairMap( TMapii& mupair, TVectorP2VL& pmu )
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

inline bool selection::oppositeChargePair(vector<float>* vcharge, int a, int b)
{
	return ( vcharge->at(a) * vcharge->at(b) < 0) ? true : false;
}

inline bool selection::findMostMassivePair(TVectorP2VL& pmu, TMapii& allmupairMap)
{
	bool found = false;
	float current_imass;
	float imassMax = 0.;
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

inline void selection::findMostMassivePair(vector<float>* vcharge, TVectorP2VL& pmu, TMapii& allmupairMap, int& iBest_a, int&iBest_b)
{
	float current_imass;
	float imassMax = 0.;
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

inline void selection::findMostHipTPair(vector<float>* mu_pt, int& iBest_a, int&iBest_b)
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

inline bool selection::findBestVertex(int nTracksCut, int nTypeCut, float z0Cut, int nvxp,
									  vector<int>* v_vxp_nTracks, vector<int>* v_vxp_type, vector<float>* v_vxp_z)
{
	bool found = false;

	m_iVtx = -1;
	
	int   nPVtracks;
	int   nPVtype;
	float dPVz0;
	for(int i=0 ; i<nvxp ; i++)
	{
		nPVtracks = v_vxp_nTracks->at(i);
		nPVtype   = v_vxp_type->at(i);
		dPVz0     = fabs( v_vxp_z->at(i) );
		
		if(nPVtracks>nTracksCut  &&  nPVtype==nTypeCut  &&  dPVz0<z0Cut)
		{
			found = true;
			m_iVtx = i;
		}
	}
	
	if(!found)
	{
		if(b_print) cout << "WARNING:  in selection::findBestVertex:  didn't find any good vertex" << endl;
	}
	
	return found;
}

inline int selection::getPVindex()
{
	return m_iVtx;
}

inline int selection::getPVindex(int nTracksCut, int nTypeCut, float z0Cut, int nvxp,
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

inline bool selection::findHipTmuon(float hipTmuonCut, float MShipTmuonCut, int nmu,
									vector<float>* v_pT, vector<float>* v_qoverp, vector<float>* v_theta )
{
	bool found = false;
	
	float pt;
	float pTms;
	float qOp;
	float theta;

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


inline bool selection::isGRLCut( float isGRLCutVal, int isGRL )
{
	if(b_print) cout << "in isGRLCut: isGRL=" << isGRL << endl;
	return ( (float)isGRL == isGRLCutVal ) ? true : false;
}

inline bool selection::isL1_MU6Cut( float isL1_MU6CutVal, int isL1_MU6 )
{
	if(b_print) cout << "in isL1_MU6Cut: isL1_MU6=" << isL1_MU6 << endl;
	return ( (float)isL1_MU6 == isL1_MU6CutVal ) ? true : false;
}

inline bool selection::isEF_muXCut( float isEF_muXCutVal, int isEF_muX )
{
	if(b_print) cout << "in isEF_muXCut: isEF_muX=" << isEF_muX << endl;
	return ( (float)isEF_muX == isEF_muXCutVal ) ? true : false;
}

inline bool selection::triggerCut( float triggerCutVal, int isTrigger, string triggerName )
{
	if(b_print) cout << "in triggerCut: triggerName=" << triggerName << " value=" << isTrigger << endl;
	return ( (float)isTrigger == triggerCutVal ) ? true : false;
}

inline bool selection::pTCut( float pTCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in pTCut: pT(pa)=" << pT(pa) << ", pT(pb)=" << pT(pb) << endl;
	return ( fabs(pT(pa))>pTCutVal  &&  fabs(pT(pb))>pTCutVal ) ? true : false;
}

inline bool selection::pTCut( float pTCutVal, float pT )
{
	pT *= MeV2TeV;
	if(b_print) cout << "in pTCut: pT=" << pT << endl;
	return ( fabs(pT)>pTCutVal ) ? true : false;
}

inline bool selection::pTCut( float pTCutVal, float me_qOp_a, float me_theta_a, float me_qOp_b, float me_theta_b )
{
	// pT=|p|*sin(theta)
	// qOp=charge/|p|
	float pT_a = pT(me_qOp_a, me_theta_a);
	float pT_b = pT(me_qOp_b,me_theta_b);
	pT_a *= MeV2TeV;
	pT_b *= MeV2TeV;
	
	if(b_print) cout << "in pTCut: pT(a)=" << pT_a << ", pT(b)=" << pT_b << endl;
	return ( fabs(pT_a)>pTCutVal  &&  fabs(pT_b)>pTCutVal ) ? true : false;
}

inline bool selection::pTCut( float pTCutVal, float me_qOp, float me_theta )
{
	// pT=|p|*sin(theta)
	// qOp=charge/|p|
	float pt = pT(me_qOp,me_theta);
	pt *= MeV2TeV;
	
	if(b_print) cout << "in pTCut: pT=" << pt << endl;
	return ( fabs(pt)>pTCutVal ) ? true : false;
}

inline bool selection::etaCut( float etaCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in etaCut: eta(pa)=" << eta(pa) << ", eta(pb)=" << eta(pb) << endl;
	return ( fabs(eta(pa))<etaCutVal  &&  fabs(eta(pb))<etaCutVal ) ? true : false;
}

inline bool selection::etaCut( float etaCutVal, float eta_a, float eta_b )
{
	if(b_print) cout << "in etaCut: eta_a=" << eta_a << ", eta_b=" << eta_b << endl;
	return ( fabs(eta_a)<etaCutVal  &&  fabs(eta_b)<etaCutVal ) ? true : false;
}

inline bool selection::etaCut( float etaCutVal, float eta )
{
	if(b_print) cout << "in etaCut: eta=" << eta << endl;
	return ( fabs(eta)<etaCutVal ) ? true : false;
}

inline bool selection::etaTightCut( float etaTightCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in etaTightCut: eta(pa)=" << eta(pa) << ", eta(pb)=" << eta(pb) << endl;
	return ( fabs(eta(pa))<etaTightCutVal  &&  fabs(eta(pb))<etaTightCutVal ) ? true : false;
}

inline bool selection::etaTightCut( float etaTightCutVal, float eta_a, float eta_b )
{
	if(b_print) cout << "in etaTightCut: eta_a=" << eta_a << ", eta_b=" << eta_b << endl;
	return ( fabs(eta_a)<etaTightCutVal  &&  fabs(eta_b)<etaTightCutVal ) ? true : false;
}

inline bool selection::etaTightCut( float etaTightCutVal, float eta )
{
	if(b_print) cout << "in etaTightCut: eta=" << eta << endl;
	return ( fabs(eta)<etaTightCutVal ) ? true : false;
}

inline bool selection::etaBarrelCut( float etaBarrelCutVal, float eta )
{
	if(b_print) cout << "in etaBarrelCut: eta=" << eta << endl;
	return ( fabs(eta)<etaBarrelCutVal ) ? true : false;
}

inline bool selection::imassCut( float imassCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in imassCut: imass(pa,pb)=" << imass(pa,pb) << endl;
	return ( imass(pa,pb) > imassCutVal ) ? true : false;
}

inline bool selection::imassMaxCut( float imassCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in imassMaxCut: imass(pa,pb)=" << imass(pa,pb) << endl;
	return ( imass(pa,pb) < imassCutVal ) ? true : false;
}

inline bool selection::cosThetaDimuCut( float cosThetaDimuCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	if(b_print) cout << "in cosThetaDimuCut: cosThetaDimu(pa,pb)=" << cosThetaDimu(pa,pb) << endl;
	return ( cosThetaDimu(pa,pb) > cosThetaDimuCutVal ) ? true : false;
}

inline bool selection::etaSumCut( float etaSumCutVal, TLorentzVector* pa, TLorentzVector* pb )
{
	float etasum = eta(pa) + eta(pb);
	if(b_print) cout << "in etaSum: etaSum(a,b)=" << etasum << endl;
	return ( fabs(etasum) < etaSumCutVal ) ? true : false;
}

inline bool selection::oppositeChargeCut( float ca, float cb )
{
	if(b_print) cout << "in oppositeCharge: ca=" << ca << ", cb=" << cb << endl;
	return ( ca*cb<0 ) ? true : false;
}

inline bool selection::oppositeChargeCut( float oppositeChargeCutVal, float ca, float cb )
{
	if(b_print) cout << "in oppositeCharge: ca=" << ca << ", cb=" << cb << endl;
	return ( ca*cb<oppositeChargeCutVal ) ? true : false;
}

inline bool selection::d0Cut( float d0CutVal, float d0a, float d0b )
{
	if(b_print) cout << "in d0Cut: d0=" << d0a << ", d0b=" << d0b << endl;
	return ( fabs(d0a)<d0CutVal  &&  fabs(d0b)<d0CutVal ) ? true : false;
}

inline bool selection::d0Cut( float d0CutVal, float d0 )
{
	if(b_print) cout << "in d0Cut: d0=" << d0 << endl;
	return ( fabs(d0)<d0CutVal ) ? true : false;
}

inline bool selection::z0Cut( float z0CutVal, float z0a, float z0b )
{
	if(b_print) cout << "in z0Cut: z0=" << z0a << ", z0b=" << z0b << endl;
	return ( fabs(z0a)<z0CutVal  &&  fabs(z0b)<z0CutVal ) ? true : false;
}

inline bool selection::z0Cut( float z0CutVal, float z0 )
{
	if(b_print) cout << "in z0Cut: z0=" << z0 << endl;
	return ( fabs(z0)<z0CutVal ) ? true : false;
}

inline bool selection::prmVtxNtracksCut( float prmVtxNtracksCutVal, int nPVtracks )
{
	/*vxp_nTracks=number of tracks > 2*/
	if(b_print) cout << "in prmVtxNtracksCut: nPVtracks=" << nPVtracks << endl;
	return ( (float)nPVtracks > prmVtxNtracksCutVal ) ? true : false;
}

inline bool selection::prmVtxTypeCut( float prmVtxTypeCutVal, int nPVtype )
{
	/*vxp_type==1*/
	if(b_print) cout << "in prmVtxTypeCut: nPVtype=" << nPVtype << endl;
	return ( (float)nPVtype == prmVtxTypeCutVal ) ? true : false;
}

inline bool selection::prmVtxZ0Cut( float prmVtxZ0CutVal, float dPVz0, float dPVz0err )
{
	dPVz0err = 0; // USE IT ??????????????????????????????????????????????
	
	/*vxp_z=absolute z position of primary vertex < 150mms*/
	if(b_print) cout << "in prmVtxZ0Cut: dPVz0=" << dPVz0 << endl;
	return ( fabs(dPVz0) < prmVtxZ0CutVal ) ? true : false;
}

inline bool selection::isCombMuCut( float isCombMuCutVal, int isCombMua, int isCombMub )
{
	/*mu_staco_isCombinedMuon*/
	if(b_print) cout << "in isCombMuCut: isCombMua=" << isCombMua << ", isCombMub=" << isCombMub << endl;
	return ( (float)isCombMua == isCombMuCutVal && (float)isCombMub == isCombMuCutVal ) ? true : false; // both are comb mu
}

inline bool selection::isCombMuCut( float isCombMuCutVal, int isCombMu )
{
	/*mu_staco_isCombinedMuon*/
	if(b_print) cout << "in isCombMuCut: isCombMu=" << isCombMu << endl;
	return ( (float)isCombMu == isCombMuCutVal ) ? true : false;
}

inline bool selection::nSCThitsCut( float nSCThitsCutVal, int nSCThits )
{
	/*mu_staco_nSCTHits :  SCT hits >=4*/
	if(b_print) cout << "in nSCThitsCut: nSCThits=" << nSCThits << endl;
	return ( (float)nSCThits >= nSCThitsCutVal ) ? true : false;
}

inline bool selection::nPIXhitsCut( float nPIXhitsCutVal, int nPIXhits )
{
	/*mu_staco_nPixHitss  :  pixel hits >=1*/
	if(b_print) cout << "in nPIXhitsCut: nPIXhits=" << nPIXhits << endl;
	return ( (float)nPIXhits >= nPIXhitsCutVal ) ? true : false;
}

inline bool selection::pTmatchRatioCut(float pTmatchHighRatioCutVal,
									   float pTmatchLowRatioCutVal,
									   float me_qOp, float me_theta,
									   float id_qOp, float id_theta)
{
	// pT=|p|*sin(theta)
	// qOp=charge/|p|
	float pT_id = pT(id_qOp,id_theta);
	float pT_ms = pT(me_qOp,me_theta);
	pT_id *= MeV2TeV;
	pT_ms *= MeV2TeV;
	
	float ratio = (pT_id!=0.) ? fabs(pT_ms/pT_id) : 0.;
	
	/* mu_staco_me_qover_p, mu_staco_me_theta, mu_staco_id_qover_p, mu_staco_id_theta */
	// pT ratio of Muon Extrapolated track to ID track greater than 0.5
	if(b_print) cout << "in pTmatchLowRatioCut: pT_id=" << pT_id << ", pT_ms=" << pT_ms << endl;
	return ( ratio > pTmatchLowRatioCutVal  &&  ratio < pTmatchHighRatioCutVal) ? true : false;
}

inline bool selection::pTmatchAbsDiffCut(float pTmatchDiffCutVal,
										 float me_qOp, float me_theta,
										 float id_qOp, float id_theta )
{
	// pT=|p|*sin(theta)
	// qOp=charge/|p|
	float pT_id = pT(id_qOp,id_theta);
	float pT_ms = pT(me_qOp,me_theta);
	pT_id *= MeV2TeV;
	pT_ms *= MeV2TeV;
	
	float diff = fabs(pT_ms - pT_id);
	
	/* mu_staco_me_qover_p, mu_staco_me_theta, mu_staco_id_qover_p, mu_staco_id_theta */
	// pT ratio of Muon Extrapolated track to ID track greater than 0.5
	if(b_print) cout << "in pTmatchDiffCut: pT_id=" << pT_id << ", pT_ms=" << pT_ms << endl;
	return ( diff < pTmatchDiffCutVal) ? true : false;
}

inline bool selection::isolationXXCut( float isolationCutVal, string sIsoValName, float pTmu, float pTcone )
{
	/*mu_staco_ptcone20, mu_staco_pt*/
	// track sum pT in 0.2 cone relative to muon pT less than 0.05
	pTmu   *= MeV2TeV;
	pTcone *= MeV2TeV;
	float isolation = (pTmu==0) ? 999 : pTcone/pTmu;
	
	if(b_print) cout << "in isolationXXCut: isolation(" << sIsoValName << ")=" << isolation << endl;
	return ( isolation < isolationCutVal ) ? true : false;
}


inline bool selection::isolationXXCut( float isolationCutVal, string sIsoValName, float qOp, float theta, float pTcone )
{
	pTcone *= MeV2TeV;
	float pTmu = pT(qOp, theta)*MeV2TeV;
	float isolation = (pTmu==0) ? 999 : pTcone/pTmu;
	
	if(b_print) cout << "in isolationXXCut: isolation(" << sIsoValName << ")=" << isolation << endl;
	return ( isolation < isolationCutVal ) ? true : false;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

inline bool selection::primaryVertexCut(float prmVtxNtracksCutVal, float prmVtxTypeCutVal, float prmVtxZ0CutVal,
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
	float minPVz0 = prmVtxZ0CutVal;
	
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

inline bool selection::nIDhitsCut( float nSCThitsCutVal, float nPIXhitsCutVal, float nIDhitsCutVal, int nSCThits, int nPIXhits )
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

inline bool selection::nIDhitsMCPrel15Cut(float nSCThitsCutVal, float nPIXhitsCutVal, float nTRThitsCutVal,
										  float etaAbsThreshold, float nTRTratioThreshold,
										  int nSCThits, int nPIXhits, int nTRTHits, int nTRTOutliers,
										  float eta)
{
	// number of pixel hits >=1, number of SCT hits >=6,
	// TRT hits > 5 for eta<1.9, outlier fraction < 0.9. 
	// If TRT hits >5 for eta>=1.9, outlier fraction < 0.9 

	bool passedPIX = (nPIXhits >= nPIXhitsCutVal) ? true : false;
	if(!passedPIX) return false;

	bool passedSCT = (nSCThits >= nSCThitsCutVal) ? true : false;
	if(!passedSCT) return false;
	
	int nTRT = nTRTHits+nTRTOutliers;
	if(fabs(eta)<etaAbsThreshold)
	{
		bool passedTRTsum = (nTRT > nTRThitsCutVal) ? true : false;
		bool passedTRTrat = (nTRTOutliers < nTRTratioThreshold*nTRT) ? true : false;
		bool passedTRT = (passedTRTsum && passedTRTrat) ? true : false;
		if(!passedTRT) return false;
	}
	else if(fabs(eta)>=etaAbsThreshold)
	{
		if(nTRT>nTRThitsCutVal)
		{
			bool passedTRTrat = (nTRTOutliers < nTRTratioThreshold*nTRT) ? true : false;
			if(!passedTRTrat) return false;
		}
	}
	
	return true;
}

inline bool selection::nIDhitsRel16Cut(float expectBLayerHitCutVal, float nBLHitsCutVal, 
									   float nPIXhitsCutVal,        float nSCThitsCutVal,     float nPIXSCTHolesCutVal,
									   float nTRThitsCutVal,        float nTRTratioThreshold, float etaAbsThreshold,
									   int   expectBLayerHit,       int nBLHits,
									   int   nPIXhits,              int nPixelDeadSensors,    int nPixHoles,
									   int   nSCThits,              int nSCTDeadSensors,      int nSCTHoles,   
									   int   nTRTHits,              int nTRTOutliers,
									   float eta)
{
	// !expectBLayerHit OR numberOfBLayerHits >= 1,
	// number of pixel hits + number of crossed dead pixel sensors >=2,
	// number of SCT hits + number of crossed dead SCT sensors >= 6,
	// Number of pixel holes + number of SCT holes <= 1, 
	// TRT hits > 5 for eta<1.9, outlier fraction < 0.9.
	// If TRT hits >5 for eta>=1.9, outlier fraction < 0.9
	
	//bool passedEXPBL = (!expectBLayerHit) ? true : false;
	bool passedEXPBL = (expectBLayerHit==(int)expectBLayerHitCutVal) ? true : false;
	bool passedBL    = (nBLHits>=nBLHitsCutVal)                 ? true : false;
	if(!(passedEXPBL||passedBL)) return false;
	
	bool passedPIX = ((nPIXhits+nPixelDeadSensors) >= nPIXhitsCutVal) ? true : false;
	if(!passedPIX) return false;
	
	bool passedSCT = ((nSCThits+nSCTDeadSensors) >= nSCThitsCutVal) ? true : false;
	if(!passedSCT) return false;
	
	bool passedHOL = ((nPixHoles+nSCTHoles) <= nPIXSCTHolesCutVal) ? true : false;
	if(!passedHOL) return false;
	
	int nTRT = nTRTHits+nTRTOutliers;
	if(fabs(eta)<etaAbsThreshold)
	{
		bool passedTRTsum = (nTRT >= nTRThitsCutVal) ? true : false;
		bool passedTRTrat = ((float)nTRTOutliers < nTRTratioThreshold*(float)nTRT) ? true : false;
		bool passedTRT = (passedTRTsum && passedTRTrat) ? true : false;
		if(!passedTRT) return false;
	}
	else if(fabs(eta)>=etaAbsThreshold)
	{
		if(nTRT>nTRThitsCutVal)
		{
			bool passedTRTrat = ((float)nTRTOutliers < nTRTratioThreshold*(float)nTRT) ? true : false;
			if(!passedTRTrat) return false;
		}
	}
	
	return true;
}

inline bool selection::nMS3stationsMDThits(float nMDTIHitsCutVal, float nMDTMHitsCutVal, float nMDTOHitsCutVal, float nMDTBEEHitsCutVal, float nMDTBIS78HitsCutVal,
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

inline bool selection::nMShits(float nMDTIHitsCutVal, float nMDTMHitsCutVal, float nMDTOHitsCutVal, float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
						float nRPCPhiHitsCutVal,
						int nMDTBIHits, int nMDTBMHits, int nMDTBOHits, int nMDTBIS78Hits, int nMDTBEEHits,
						int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits
						)
{
	// Require 3 stations on the muon track, i.e. hits in the Inner, Middle and Outer chambers;
	// Reject muons with hits in BEE, BIS7 and BIS8
	
	bool passedMDT = true;
	passedMDT = (passedMDT  &&  nMDTBIHits >= nMDTIHitsCutVal) ? true  : false;
	passedMDT = (passedMDT  &&  nMDTBMHits >= nMDTMHitsCutVal) ? true  : false;
	passedMDT = (passedMDT  &&  nMDTBOHits >= nMDTOHitsCutVal) ? true  : false;
	passedMDT = (passedMDT  &&  nMDTBIS78Hits==nMDTBIS78HitsCutVal) ? true  : false;
	passedMDT = (passedMDT  &&  nMDTBEEHits==nMDTBEEHitsCutVal) ?     true  : false;
	
	
	bool passedRPC1 = ((nRPCLayer1PhiHits>=nRPCPhiHitsCutVal  &&  nRPCLayer2PhiHits>=nRPCPhiHitsCutVal)) ? true  : false;
	bool passedRPC2 = ((nRPCLayer1PhiHits>=nRPCPhiHitsCutVal  &&  nRPCLayer3PhiHits>=nRPCPhiHitsCutVal)) ? true  : false;
	bool passedRPC3 = ((nRPCLayer2PhiHits>=nRPCPhiHitsCutVal  &&  nRPCLayer3PhiHits>=nRPCPhiHitsCutVal)) ? true  : false;
	bool passedRPC = true;
	passedRPC = (passedRPC  &&  (passedRPC1 || passedRPC2 || passedRPC3)) ? true  : false;
	
	bool passed = true;
	passed = (passed  &&  passedMDT  &&  passedRPC) ? true : false;
	
	return passed;
}

inline bool selection::nMShits1(float nMDTB_IMO_HitsCutVal, float nMDTE_IMEO_HitsCutVal,
								float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
								float nCSCEtaHitsCutVal,
								float nMDTCSCsumCutVal, float nRPCTGCCSCsumsCutVal,
								int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
								int nMDTEIHits, int nMDTEMHits, int nMDTEEHits, int nMDTEOHits,
								int nMDTBIS78Hits, int nMDTBEEHits,
								int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
								int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
								int nCSCEtaHits, int nCSCPhiHits)
{
	// two MDT(CSC) stations, at least one phi hit and veto BEE and BIS78:
	//(\ Sum_$=IMO nMDTB$Hits>=3 + \Sum_$=IMEO nMDTE$Hits>=3 + nCSCEtaHits>=3 ) >=2 (>=3 for nMShits3 cut)
	// && mu_staco_nMDTBEEHits==0
	// && mu_staco_nMDTBIS78Hits==0
	// && (\Sum_K=1^3 nRPCLayerKPhiHits + \Sum_K=1^4 nTGCLayerKPhiHits + nCSCPhiHits )>=1
	
	bool passedMDTB   = ((nMDTBIHits+nMDTBMHits+nMDTBOHits)            >= nMDTB_IMO_HitsCutVal)  ? true : false;
	bool passedMDTE   = ((nMDTEIHits+nMDTEMHits+nMDTEEHits+nMDTEOHits) >= nMDTE_IMEO_HitsCutVal) ? true : false;
	bool passedCSCEta = (nCSCEtaHits                                   >= nCSCEtaHitsCutVal)     ? true : false;
	bool passedMDTCSC = (((int)passedMDTB+(int)passedMDTE+(int)passedCSCEta) >= nMDTCSCsumCutVal) ? true : false;
	if(!passedMDTCSC) return false;
	 
	bool passedMDTBIS78 = (nMDTBIS78Hits==nMDTBIS78HitsCutVal) ? true : false;
	if(!passedMDTBIS78) return false;
	
	bool passedMDTBEE   = (nMDTBEEHits==nMDTBEEHitsCutVal) ? true : false;
	if(!passedMDTBEE) return false;
	
	int nRPCTGCCSCsum = nRPCLayer1PhiHits+nRPCLayer2PhiHits+nRPCLayer3PhiHits + 
						nTGCLayer1PhiHits+nTGCLayer2PhiHits+nTGCLayer3PhiHits+nTGCLayer4PhiHits +
						nCSCPhiHits;
	bool passedRPCTGCCSC = (nRPCTGCCSCsum >= nRPCTGCCSCsumsCutVal) ? true : false;
	if(!passedRPCTGCCSC) return false;
	
	return true;
}

inline bool selection::nMShits2(float nMDTB_IMO_HitsCutVal, float nMDTE_IMEO_HitsCutVal,
								float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
								float nCSCEtaHitsCutVal,
								float nRPCPhiHitsCutVal, float nTGCPhiHitsCutVal, float nCSCPhiHitsCutVal,
								float nMDTCSCsumCutVal, float nRPCTGCsumsCutVal,
								int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
								int nMDTEIHits, int nMDTEMHits, int nMDTEEHits, int nMDTEOHits,
								int nMDTBIS78Hits, int nMDTBEEHits,
								int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
								int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
								int nCSCEtaHits, int nCSCPhiHits)
{
	// two MDT(CSC) stations, at least one trigger station (hits>=1) and veto BEE and BIS78
	//(\ Sum_$=IMO nMDTB$Hits>=3 + \Sum_$=IMEO nMDTE$Hits>=3 + nCSCEtaHits>=3 ) >=2
	// && mu_staco_nMDTBEEHits==0
	// && mu_staco_nMDTBIS78Hits==0
	// && (\Sum_K=1^3 nRPCLayerKPhiHits>=1 + \Sum_K=1^4 nTGCLayerKPhiHits>=1 + nCSCPhiHits>=1 )>=1
	
	bool passedMDTB   = ((nMDTBIHits+nMDTBMHits+nMDTBOHits)                  >= nMDTB_IMO_HitsCutVal)  ? true : false;
	bool passedMDTE   = ((nMDTEIHits+nMDTEMHits+nMDTEEHits+nMDTEOHits)       >= nMDTE_IMEO_HitsCutVal) ? true : false;
	bool passedCSCEta = (nCSCEtaHits                                         >= nCSCEtaHitsCutVal)     ? true : false;
	bool passedMDTCSC = (((int)passedMDTB+(int)passedMDTE+(int)passedCSCEta) >= nMDTCSCsumCutVal)      ? true : false;
	if(!passedMDTCSC) return false;
	 
	bool passedMDTBIS78 = (nMDTBIS78Hits==nMDTBIS78HitsCutVal) ? true : false;
	if(!passedMDTBIS78) return false;
	
	bool passedMDTBEE   = (nMDTBEEHits==nMDTBEEHitsCutVal) ? true : false;
	if(!passedMDTBEE) return false;
	
	bool passedRPC    = ((nRPCLayer1PhiHits+nRPCLayer2PhiHits+nRPCLayer3PhiHits)                   >= nRPCPhiHitsCutVal) ? true : false;
	bool passedTGC    = ((nTGCLayer1PhiHits+nTGCLayer2PhiHits+nTGCLayer3PhiHits+nTGCLayer4PhiHits) >= nTGCPhiHitsCutVal) ? true : false;
	bool passedCSCPhi = (nCSCPhiHits                                                               >= nCSCPhiHitsCutVal) ? true : false;
	bool passedRPCTGC = (((int)passedRPC+(int)passedTGC+(int)passedCSCPhi)                         >= nRPCTGCsumsCutVal) ? true : false;
	if(!passedRPCTGC) return false;
	
	return true;
}

inline bool selection::nMShitsRel16(float nMDTB_IMO_HitsCutVal, float nMDTE_IMO_HitsCutVal,
									float nMDTBEEHitsCutVal, float nMDTEEHitsCutVal, float nMDTBIS78HitsCutVal, 
									float nCSCEtaHitsCutVal,
									float nPhiHitsCutVal,
									float nMDTCSCsumCutVal, float nRPCTGCCSCsumsCutVal,
									int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
									int nMDTEIHits, int nMDTEMHits, int nMDTEOHits,
									int nMDTBEEHits, int nMDTEEHits, int nMDTBIS78Hits,
									int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
									int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
									int nCSCEtaHits, int nCSCPhiHits)
{
	// At least 3 hits in all of Barrel or Endcap Inner,
	// Middle and Outer MDT/CSC precision layers,
	// at least one phi hit, and no BEE, EE or BIS78 hits
	
	/*
	(
		(nRPCLayer1PhiHits>=1) + (nRPCLayer2PhiHits>=1) + (nRPCLayer3PhiHits>=1) +
		(nTGCLayer1PhiHits>=1) + (nTGCLayer2PhiHits>=1) + (nTGCLayer3PhiHits>=1) + (nTGCLayer4PhiHits>=1) +
		(nCSCPhiHits>=1)
	) >=1
	&& 
	(
		((nMDTBIHits>=3) + (nMDTBMHits>=3) + (nMDTBOHits>=3)) >= 3
		||
		(((nMDTEIHits>=3) || (nCSCEtaHits>=3)) + (nMDTEMHits>=3) + (nMDTEOHits>=3)) >= 3
	)
	&& (nMDTBEEHits==0) && (nMDTEEHits==0) && (nMDTBIS78Hits==0);
	*/
	
	//1) at least one phi hit on the MS track
	//2.1) MS track has at least 3 hits in each of Inner, Middle, Outer of Barrel
	//OR
	//2.2) MS track has at least 3 hits in each of Inner, Middle, Outer of Endcap
	//3) BEE is vetoed & EE is vetoed & BIS78 is vetoed
	//The motivation to implement component (2) is this way is that the 3hits x 3stations
	//requirement should be satisfied by the barrel MS on its own or the endcap MS on its own.
	//An MS track where the barrel alone (or endcap alone) cannot satisfy these quality requirements,
	//may be sensitive to relative misalignments between barrel and endcap, and is not considered
	//robust enough for the first Zprime publication. There are not many such tracks anyway. 
	
	bool passedMDTBI = (nMDTBIHits >= nMDTB_IMO_HitsCutVal) ? true : false;
	bool passedMDTBM = (nMDTBMHits >= nMDTB_IMO_HitsCutVal) ? true : false;
	bool passedMDTBO = (nMDTBOHits >= nMDTB_IMO_HitsCutVal) ? true : false;
	bool passedMDTEI = (nMDTEIHits >= nMDTE_IMO_HitsCutVal) ? true : false;
	bool passedMDTEM = (nMDTEMHits >= nMDTE_IMO_HitsCutVal) ? true : false;
	bool passedMDTEO = (nMDTEOHits >= nMDTE_IMO_HitsCutVal) ? true : false;
	bool passedCSC   = (nCSCEtaHits >= nCSCEtaHitsCutVal)   ? true : false;
	/*
	bool passedMDTCSC = ((passedMDTBI +
						  passedMDTBM +
						  passedMDTBO +
						  (passedMDTEI||passedCSC) +
						  passedMDTEM +
						  passedMDTEO) >= nMDTCSCsumCutVal) ? true : false;
	*/
	bool passedMDTBarrel = ((passedMDTBI + passedMDTBM + passedMDTBO)              >= nMDTCSCsumCutVal) ? true : false;
	bool passedMDTEndcap = (((passedMDTEI||passedCSC) + passedMDTEM + passedMDTEO) >= nMDTCSCsumCutVal) ? true : false;
	bool passedMDTCSC = (passedMDTBarrel || passedMDTEndcap) ? true : false;
	if(!passedMDTCSC) return false;
	 
	bool passedMDTBEE   = (nMDTBEEHits==nMDTBEEHitsCutVal) ? true : false;
	if(!passedMDTBEE)   return false;
	bool passedMDTEE    = (nMDTEEHits==nMDTEEHitsCutVal) ? true : false;
	if(!passedMDTEE)    return false;
	bool passedMDTBIS78 = (nMDTBIS78Hits==nMDTBIS78HitsCutVal) ? true : false;
	if(!passedMDTBIS78) return false;
	
	int nRPCTGCCSCsum = (nRPCLayer1PhiHits>=nPhiHitsCutVal) +
						(nRPCLayer2PhiHits>=nPhiHitsCutVal) +
						(nRPCLayer3PhiHits>=nPhiHitsCutVal) + 
						(nTGCLayer1PhiHits>=nPhiHitsCutVal) +
						(nTGCLayer2PhiHits>=nPhiHitsCutVal) +
						(nTGCLayer3PhiHits>=nPhiHitsCutVal) +
						(nTGCLayer4PhiHits>=nPhiHitsCutVal) +
						(nCSCPhiHits>=nPhiHitsCutVal);
	bool passedRPCTGCCSC = (nRPCTGCCSCsum >= nRPCTGCCSCsumsCutVal) ? true : false;
	if(!passedRPCTGCCSC) return false;
	
	return true;
}

inline bool selection::nMShits2noCSCphi(float nMDTB_IMO_HitsCutVal, float nMDTE_IMEO_HitsCutVal,
										float nMDTBIS78HitsCutVal, float nMDTBEEHitsCutVal,
										float nCSCEtaHitsCutVal,
										float nRPCPhiHitsCutVal, float nTGCPhiHitsCutVal,
										float nMDTCSCsumCutVal, float nRPCTGCsumsCutVal,
										int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
										int nMDTEIHits, int nMDTEMHits, int nMDTEEHits, int nMDTEOHits,
										int nMDTBIS78Hits, int nMDTBEEHits,
										int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
										int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
										int nCSCEtaHits)
{
	//(\ Sum_$=IMO nMDTB$Hits>=3 + \Sum_$=IMEO nMDTE$Hits>=3 + nCSCEtaHits>=3 ) >=2
	// && mu_staco_nMDTBEEHits==0
	// && mu_staco_nMDTBIS78Hits==0
	// && (\Sum_K=1^3 nRPCLayerKPhiHits>=1 + \Sum_K=1^4 nTGCLayerKPhiHits>=1 )>=1
	
	bool passedMDTB   = ((nMDTBIHits+nMDTBMHits+nMDTBOHits)                  >= nMDTB_IMO_HitsCutVal)  ? true : false;
	bool passedMDTE   = ((nMDTEIHits+nMDTEMHits+nMDTEEHits+nMDTEOHits)       >= nMDTE_IMEO_HitsCutVal) ? true : false;
	bool passedCSCEta = (nCSCEtaHits                                         >= nCSCEtaHitsCutVal)     ? true : false;
	bool passedMDTCSC = (((int)passedMDTB+(int)passedMDTE+(int)passedCSCEta) >= nMDTCSCsumCutVal)      ? true : false;
	if(!passedMDTCSC) return false;
	 
	bool passedMDTBIS78 = (nMDTBIS78Hits==nMDTBIS78HitsCutVal) ? true : false;
	if(!passedMDTBIS78) return false;
	
	bool passedMDTBEE   = (nMDTBEEHits==nMDTBEEHitsCutVal) ? true : false;
	if(!passedMDTBEE) return false;
	
	bool passedRPC    = ((nRPCLayer1PhiHits+nRPCLayer2PhiHits+nRPCLayer3PhiHits)                   >= nRPCPhiHitsCutVal) ? true : false;
	bool passedTGC    = ((nTGCLayer1PhiHits+nTGCLayer2PhiHits+nTGCLayer3PhiHits+nTGCLayer4PhiHits) >= nTGCPhiHitsCutVal) ? true : false;
	bool passedRPCTGC = (((int)passedRPC+(int)passedTGC)                                           >= nRPCTGCsumsCutVal) ? true : false;
	if(!passedRPCTGC) return false;
	
	return true;
}

inline bool selection::pTmatchingRatioCut(float pTmatchHighRatioCutVal,
										  float pTmatchLowRatioCutVal,
										  float me_qOp_a, float me_theta_a,
										  float id_qOp_a, float id_theta_a,
										  float me_qOp_b, float me_theta_b,
										  float id_qOp_b, float id_theta_b)
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

inline bool selection::pTmatchingAbsDiffCut(float pTmatchDiffCutVal,
										    float me_qOp_a, float me_theta_a,
										    float id_qOp_a, float id_theta_a,
										    float me_qOp_b, float me_theta_b,
										    float id_qOp_b, float id_theta_b)
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

inline bool selection::impactParameterCut(float d0CutVal, float z0CutVal,
										  float d0a, float d0b,
										  float z0a, float z0b )
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

inline bool selection::impactParameterCut( float d0CutVal, float z0CutVal, float d0, float z0 )
{
	if( !d0Cut(d0CutVal, d0) ) return false;
	if( !z0Cut(z0CutVal, z0) ) return false;
	
	return true;
}

inline bool selection::pTandEtaCut( float pTCutVal, float etaCutVal, float me_qOp, float me_theta, float eta )
{
	if( !etaCut( etaCutVal, eta ) )  return false;
	if( !pTCut( pTCutVal, me_qOp, me_theta ) ) return false;
	
	return true;
}

inline bool selection::pTandEtaTightCut( float pTCutVal, float etaTightCutVal, float me_qOp, float me_theta, float eta )
{
	if( !etaTightCut( etaTightCutVal, eta ) )  return false;
	if( !pTCut( pTCutVal, me_qOp, me_theta ) ) return false;
	
	return true;
}

inline bool selection::pTandEtaBarrelCut( float pTCutVal, float etaBarrelCutVal, float me_qOp, float me_theta, float eta )
{
	if( !etaBarrelCut( etaBarrelCutVal, eta ) )  return false;
	if( !pTCut( pTCutVal, me_qOp, me_theta ) ) return false;
	
	return true;
}

inline bool selection::pTandEtaCut( float pTCutVal, float etaCutVal, float pT, float eta )
{
	if( !etaTightCut( etaCutVal, eta ) )  return false;
	if( !pTCut( pTCutVal, pT ) )          return false;
	
	return true;
}

inline bool selection::pTandEtaTightCut( float pTCutVal, float etaTightCutVal, float pT, float eta )
{
	if( !etaTightCut( etaTightCutVal, eta ) )  return false;
	if( !pTCut( pTCutVal, pT ) )               return false;
	
	return true;
}

inline bool selection::pTandEtaBarrelCut( float pTCutVal, float etaBarrelCutVal, float pT, float eta )
{
	if( !etaBarrelCut( etaBarrelCutVal, eta ) )  return false;
	if( !pTCut( pTCutVal, pT ) )               return false;
	
	return true;
}

inline bool selection::pairXXisolation( float isolationCutVal, string sIsoValName,
										float pTmua, float pTmub, float pTconea, float pTconeb )
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

