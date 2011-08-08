/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef selection_cxx
#include "selection.h"

using namespace cuts;

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

inline bool selection::findBestVertex(int nTracksCut, int nTypeCut, float z0cut, int nvxp,
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
		
		if(nPVtracks>nTracksCut  &&  nPVtype==nTypeCut  &&  dPVz0<z0cut)
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

inline int selection::getPVindex(int nTracksCut, int nTypeCut, float z0cut, int nvxp,
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
		if(nPVtracks>nTracksCut  &&  nPVtype==nTypeCut  &&  dPVz0<z0cut)
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


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 


inline bool selection::isGRLCut( float isGRLCutVal, int isGRL )
{
	if(b_print) cout << "in isGRLCut: isGRL=" << isGRL << endl;
	return ( (float)isGRL == isGRLCutVal ) ? true : false;
}

inline bool selection::triggerCut( float triggerCutVal, int isTrigger, string triggerName )
{
	if(b_print) cout << "in triggerCut: triggerName=" << triggerName << " value=" << isTrigger << endl;
	return ( (float)isTrigger == triggerCutVal ) ? true : false;
}

inline bool selection::pTCut( float pTCutVal, float pt )
{
	pt *= MeV2TeV;
	if(b_print) cout << "in pTCut: pt=" << pt << endl;
	return ( fabs(pt)>pTCutVal ) ? true : false;
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

inline bool selection::etaCut( float etaCutVal, float Eta )
{
	if(b_print) cout << "in etaCut: Eta=" << Eta << endl;
	return ( fabs(Eta)<etaCutVal ) ? true : false;
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

inline bool selection::d0Cut( float d0CutVal, float d0 )
{
	if(b_print) cout << "in d0Cut: d0=" << d0 << endl;
	return ( fabs(d0)<d0CutVal ) ? true : false;
}

inline bool selection::z0Cut( float z0CutVal, float z0 )
{
	if(b_print) cout << "in z0Cut: z0=" << z0 << endl;
	return ( fabs(z0)<z0CutVal ) ? true : false;
}

inline bool selection::isCombMuCut( float isCombMuCutVal, int isCombMu )
{
	/*mu_staco_isCombinedMuon*/
	if(b_print) cout << "in isCombMuCut: isCombMu=" << isCombMu << endl;
	return ( (float)isCombMu == isCombMuCutVal ) ? true : false;
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


inline bool selection::nIDhitsRel16Cut(float expectBLayerHitCutVal, float nBLHitsCutVal, 
									   float nPIXhitsCutVal,        float nSCThitsCutVal,     float nPIXSCTHolesCutVal,
									   float nTRThitsCutVal,        float nTRTratioThreshold, float etaAbsThreshold,
									   int   expectBLayerHit,       int nBLHits,
									   int   nPIXhits,              int nPixelDeadSensors,    int nPixHoles,
									   int   nSCThits,              int nSCTDeadSensors,      int nSCTHoles,   
									   int   nTRTHits,              int nTRTOutliers,
									   float Eta)
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
	if(fabs(Eta)<etaAbsThreshold)
	{
		bool passedTRTsum = (nTRT >= nTRThitsCutVal) ? true : false;
		bool passedTRTrat = ((float)nTRTOutliers < nTRTratioThreshold*(float)nTRT) ? true : false;
		bool passedTRT = (passedTRTsum && passedTRTrat) ? true : false;
		if(!passedTRT) return false;
	}
	else if(fabs(Eta)>=etaAbsThreshold)
	{
		if(nTRT>nTRThitsCutVal)
		{
			bool passedTRTrat = ((float)nTRTOutliers < nTRTratioThreshold*(float)nTRT) ? true : false;
			if(!passedTRTrat) return false;
		}
	}
	
	return true;
}

inline bool selection::nMShitsRel16Cut(float nMDTB_IMO_HitsCutVal, float nMDTE_IMO_HitsCutVal,
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

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

#endif

