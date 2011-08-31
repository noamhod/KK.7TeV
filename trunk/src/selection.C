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

inline bool selection::findBestVertex(int nTypeCut, int nTracksCut, float z0cut,
									  vector<int>* v_vxp_type, vector<int>* v_vxp_nTracks, vector<float>* v_vxp_z)
{
	m_iVtx = -1;
	for(int i=0 ; i<(int)v_vxp_nTracks->size() ; i++)
	{
		if(v_vxp_type->at(i)!=nTypeCut)      continue;
		if(v_vxp_nTracks->at(i)<=nTracksCut) continue;
		if(fabs( v_vxp_z->at(i) )>=z0cut)    continue;
		
		m_iVtx = i;
		return true;
	}
	//_WARNING("didn't find any good vertex\n");
	return false;
}

inline int selection::getPVindex()
{
	return m_iVtx;
}

inline int selection::getPVindex(int nTypeCut, int nTracksCut, float z0cut,
								 vector<int>* v_vxp_type, vector<int>* v_vxp_nTracks, vector<float>* v_vxp_z)
{
	int   nPVtracks;
	int   nPVtype;
	float dPVz0;
	float z0min = 9999;
	int   index = -1;
	for(int i=0 ; i<(int)v_vxp_nTracks->size() ; i++)
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

inline bool selection::oppositeChargeCandidatesCut( vector<float>* v_charge, vector<bool>& v_QAflag)
{
	int muPlus  = 0;
	int muMinus = 0;
	for(int mu=0 ; mu<(int)v_charge->size() ; mu++)
	{
		if     (!v_QAflag[mu])       continue;
		if     (v_charge->at(mu)>0.) muPlus++;
		else if(v_charge->at(mu)<0.) muMinus++;
		else
		{
			_ERROR("in selection::oppositeChargeCandidate -> found charge==0, exitting now.");
			exit(-1);
		}
		if(muPlus>0 && muMinus>0) return true;
	}
	return false;
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
	// track sum pT in 0.XX cone relative to muon pT less than YYY
	//pTmu   *= MeV2TeV;
	//pTcone *= MeV2TeV;
	float isolation = (pTmu==0) ? 999 : pTcone/pTmu;
	
	if(b_print) cout << "in isolationXXCut: isolation(" << sIsoValName << ")=" << isolation << endl;
	return ( isolation < isolationCutVal ) ? true : false;
}


inline bool selection::isolationXXCut( float isolationCutVal, string sIsoValName, float qOp, float theta, float pTcone )
{
	// pTcone *= MeV2TeV;
	// float pTmu = pT(qOp, theta)*MeV2TeV;
	float pTmu = pT(qOp,theta);
	float isolation = (pTmu==0) ? 999 : pTcone/pTmu;
	
	if(b_print) cout << "in isolationXXCut: isolation(" << sIsoValName << ")=" << isolation << endl;
	return ( isolation < isolationCutVal ) ? true : false;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 


inline bool selection::nIDhitsCut(float expectBLayerHitCutVal,
								  float nBLHitsCutVal, 
							      float sumPIXhitsAndPixelDeadSensorsCutVal,
							      float sumSCThitsAndSCTDeadSensorsCutVal,
							      float sumPIXandSCTHolesCutVal,
							      float sumTRThitsAndTRTOutliersCutVal,
							      float etaAbsThreshold,
							      float nTRToutlierRatioThreshold,
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
	
	bool passedPIX = ((nPIXhits+nPixelDeadSensors) >= sumPIXhitsAndPixelDeadSensorsCutVal) ? true : false;
	if(!passedPIX) return false;
	
	bool passedSCT = ((nSCThits+nSCTDeadSensors) >= sumSCThitsAndSCTDeadSensorsCutVal) ? true : false;
	if(!passedSCT) return false;
	
	bool passedHOL = ((nPixHoles+nSCTHoles) <= sumPIXandSCTHolesCutVal) ? true : false;
	if(!passedHOL) return false;
	
	int nTRT = nTRTHits+nTRTOutliers;
	if(fabs(Eta)<etaAbsThreshold)
	{
		bool passedTRTsum = (nTRT >= sumTRThitsAndTRTOutliersCutVal) ? true : false;
		bool passedTRTrat = ((float)nTRTOutliers < nTRToutlierRatioThreshold*(float)nTRT) ? true : false;
		bool passedTRT = (passedTRTsum && passedTRTrat) ? true : false;
		if(!passedTRT) return false;
	}
	else if(fabs(Eta)>=etaAbsThreshold)
	{
		if(nTRT>sumTRThitsAndTRTOutliersCutVal)
		{
			bool passedTRTrat = ((float)nTRTOutliers < nTRToutlierRatioThreshold*(float)nTRT) ? true : false;
			if(!passedTRTrat) return false;
		}
	}
	
	return true;
}

inline bool selection::nMShitsCut(float nMDTBIMOHitsCutVal, float nMDTEIMOHitsCutVal, float nCSCEtaHitsCutVal,
								  float nMDTBarrel_LogicSum, float nMDTorCSCEndcap_LogicSum,
								  float nMDTBEEHitsCutVal, float nMDTEEHitsCutVal, float nMDTBIS78HitsCutVal, 
								  float nRPCLayerPhiHitsCutsVal, float nTGCLayerPhiHitsCutsVal, float nCSCLayerPhiHitsCutVal,
								  float nRPCTGCCSC_LogicSum,
								  int nMDTBIHits, int nMDTBMHits, int nMDTBOHits,
								  int nMDTEIHits, int nMDTEMHits, int nMDTEOHits,
								  int nMDTBEEHits, int nMDTEEHits, int nMDTBIS78Hits,
								  int nRPCLayer1PhiHits, int nRPCLayer2PhiHits, int nRPCLayer3PhiHits,
								  int nTGCLayer1PhiHits, int nTGCLayer2PhiHits, int nTGCLayer3PhiHits, int nTGCLayer4PhiHits,
								  int nCSCEtaHits, int nCSCPhiHits)
{
	// REJECT ANYWAY IF THIS FAILS:
	if(nMDTBEEHits!=nMDTBEEHitsCutVal)     return false;
	if(nMDTEEHits!=nMDTEEHitsCutVal)       return false;
	if(nMDTBIS78Hits!=nMDTBIS78HitsCutVal) return false;

	
	bool passedMDTBI = (nMDTBIHits >= nMDTBIMOHitsCutVal) ? true : false;
	bool passedMDTBM = (nMDTBMHits >= nMDTBIMOHitsCutVal) ? true : false;
	bool passedMDTBO = (nMDTBOHits >= nMDTBIMOHitsCutVal) ? true : false;
	bool passedMDTEI = (nMDTEIHits >= nMDTEIMOHitsCutVal) ? true : false;
	bool passedMDTEM = (nMDTEMHits >= nMDTEIMOHitsCutVal) ? true : false;
	bool passedMDTEO = (nMDTEOHits >= nMDTEIMOHitsCutVal) ? true : false;
	bool passedCSC   = (nCSCEtaHits >= nCSCEtaHitsCutVal) ? true : false;

	
	// CHECK BARREL !!!
	int nRPCsum = (nRPCLayer1PhiHits>=nRPCLayerPhiHitsCutsVal) +
				  (nRPCLayer2PhiHits>=nRPCLayerPhiHitsCutsVal) +
				  (nRPCLayer3PhiHits>=nRPCLayerPhiHitsCutsVal);
	bool passedRPC = (nRPCsum >= nRPCTGCCSC_LogicSum) ? true : false;
	
	bool passedBarrel = (
							(passedMDTBI+passedMDTBM+passedMDTBO)>=nMDTBarrel_LogicSum &&
							(nMDTEIHits)+(nMDTEMHits)+(nMDTEOHits)==0 && // endcap overlap removal
							passedRPC
						) ? true : false;
	if(passedBarrel) return true;
	
	
	// CHECK ENDCAP !!!
	int nTGCCSCsum = (nTGCLayer1PhiHits>=nTGCLayerPhiHitsCutsVal) +
					 (nTGCLayer2PhiHits>=nTGCLayerPhiHitsCutsVal) +
					 (nTGCLayer3PhiHits>=nTGCLayerPhiHitsCutsVal) +
					 (nTGCLayer4PhiHits>=nTGCLayerPhiHitsCutsVal) +
					 (nCSCPhiHits>=nCSCLayerPhiHitsCutVal);
	bool passedTGCCSC = (nTGCCSCsum >= nRPCTGCCSC_LogicSum) ? true : false;
	
	bool passedEndcap = (
							((passedMDTEI||passedCSC)+passedMDTEM+passedMDTEO)>=nMDTorCSCEndcap_LogicSum &&
							(nMDTBIHits)+(nMDTBMHits)+(nMDTBOHits)==0 && // barrel overlap removal
							passedTGCCSC
						) ? true : false;
	if(passedEndcap) return true;
	
	
	// DIDN'T PASS BARREL OR ENDCAP !!!
	return false;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

#endif

