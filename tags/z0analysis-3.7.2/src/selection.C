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

inline bool selection::antid0Cut( float d0CutVal, float d0 )
{
	if(b_print) cout << "in antid0Cut: d0=" << d0 << endl;
	return ( fabs(d0)>d0CutVal ) ? true : false;
}

inline bool selection::antiz0Cut( float z0CutVal, float z0 )
{
	if(b_print) cout << "in antiz0Cut: z0=" << z0 << endl;
	return ( fabs(z0)>z0CutVal ) ? true : false;
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

inline bool selection::constrainedAntiIsolationXXCut( float minIsolationCutVal, float maxIsolationCutVal, string sIsoValName, float pTmu, float pTcone )
{
	// track sum pT in 0.XX cone relative to muon pT less than YYY
	float isolation = (pTmu==0) ? 999 : pTcone/pTmu;
	
	if(b_print) cout << "in isolationXXCut: isolation(" << sIsoValName << ")=" << isolation << endl;
	return (isolation>minIsolationCutVal  &&  isolation<maxIsolationCutVal) ? true : false;
}

inline bool selection::antiIsolationXXCut( float isolationCutVal, string sIsoValName, float pTmu, float pTcone )
{
	// track sum pT in 0.XX cone relative to muon pT more than YYY
	float isolation = (pTmu==0) ? 999 : pTcone/pTmu;
	
	if(b_print) cout << "in isolationXXCut: isolation(" << sIsoValName << ")=" << isolation << endl;
	return ( isolation >= isolationCutVal ) ? true : false;
}

inline bool selection::eTisolationXXCut( float isolationCutVal, string sIsoValName, float eTcone )
{
	// track sum eT in 0.XX cone is more than YYY
	if(b_print) cout << "in isolationXXCut: eTcone(" << sIsoValName << ")=" << eTcone << endl;
	return ( eTcone < isolationCutVal ) ? true : false;
}

inline bool selection::eTantiIsolationXXCut( float isolationCutVal, string sIsoValName, float eTcone )
{
	// track sum pT in 0.XX cone relative to muon pT more than YYY
	if(b_print) cout << "in isolationXXCut: eTcone(" << sIsoValName << ")=" << eTcone << endl;
	return ( eTcone >= isolationCutVal ) ? true : false;
}

inline bool selection::didmuTriggerCut( float drCutVal, float trig_dr, int roi_index )
{
	// loose muon should not be associated with a trigger object
	if(roi_index<0)       return false; // this muon is not associated with a trigger object
	if(trig_dr<0.)        return false; // this muon is not associated with a trigger object
	if(trig_dr>=drCutVal) return false; // this muon is associated with a trigger object but matching cone is too big
	return true;
}

inline bool selection::isLooseNoTightCut( float isLooseCutVal, float isTightCutval, int isLoose, int isTight )
{
	if(isLoose==(int)isLooseCutVal && isTight==(int)isTightCutval) return true;
	return false;
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

inline void selection::classify3233(float MuonPhiHitsCut,    float MuonPhiLayerCut,  float MuonMDTHitsCut,  float MuonMomDiffSigCut,
									float MuonPhiHitsCut2,   float MuonPhiLayerCut2, float MuonMDTHitsCut2, float MuonMomDiffSigCut2,
									vector<float>& mu_sig_diff_qoverp,
									vector<float>* mu_eta, vector<float>* mu_phi, vector<float>* mu_charge,
									vector<int>* mu_nMDTBIHits, vector<int>* mu_nMDTBMHits, vector<int>* mu_nMDTBOHits,
									vector<int>* mu_nMDTEIHits, vector<int>* mu_nMDTEMHits, vector<int>* mu_nMDTEOHits,
									vector<int>* mu_nMDTBEEHits, vector<int>* mu_nMDTEEHits, vector<int>* mu_nMDTBIS78Hits,
									vector<int>* mu_nRPCLayer1PhiHits, vector<int>* mu_nRPCLayer2PhiHits, vector<int>* mu_nRPCLayer3PhiHits,
									vector<int>* mu_nTGCLayer1PhiHits, vector<int>* mu_nTGCLayer2PhiHits, vector<int>* mu_nTGCLayer3PhiHits, vector<int>* mu_nTGCLayer4PhiHits,
									vector<int>* mu_nCSCEtaHits, vector<int>* mu_nCSCPhiHits,
									vector<unsigned int>& classified
									)
{
	unsigned int muSize = mu_eta->size();

	vector<int> mu_phiSector;
	vector<int> mu_nStations;
	vector<int> mu_is3StBarrel;
	vector<int> mu_is3StEndcap;
	vector<int> mu_is3St;
	vector<int> mu_is2StBarrel;
	vector<int> mu_is2StEndcap;
	vector<int> mu_is2St;
	for(unsigned int i=0 ; i<muSize ; i++)
	{
		mu_phiSector.push_back(0);
		mu_nStations.push_back(0);
		mu_is3StBarrel.push_back(0);
		mu_is3StEndcap.push_back(0);
		mu_is3St.push_back(0);
		mu_is2StBarrel.push_back(0);
		mu_is2StEndcap.push_back(0);
		mu_is2St.push_back(0);
	}
	
	for(unsigned int j=0 ; j<muSize ; j++)
	{
		mu_phiSector[j] = getPhiSector(mu_phi->at(j));

		// Count nStations
		mu_nStations[j] =
		(mu_nMDTBIHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTBMHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTBOHits->at(j) >= MuonMDTHitsCut) +
		((mu_nMDTEIHits->at(j) >= MuonMDTHitsCut) || (mu_nCSCEtaHits->at(j) >= MuonMDTHitsCut) ) +
		(mu_nMDTEMHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTEOHits->at(j) >= MuonMDTHitsCut);

		mu_is3StBarrel[j] =
		(fabs(mu_sig_diff_qoverp[j]) < MuonMomDiffSigCut) &&
		((mu_nRPCLayer1PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nRPCLayer2PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nRPCLayer3PhiHits->at(j) >= MuonPhiHitsCut) >= MuonPhiLayerCut) &&
		((mu_nMDTBIHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTBMHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTBOHits->at(j) >= MuonMDTHitsCut) == 3) &&
		(mu_nMDTEIHits->at(j) == 0) &&
		(mu_nMDTEMHits->at(j) == 0) &&
		(mu_nMDTEOHits->at(j) == 0) &&
		(mu_nCSCEtaHits->at(j) == 0) &&
		(mu_nMDTBEEHits->at(j) == 0) &&
		(mu_nMDTEEHits->at(j) == 0) &&
		(mu_nMDTBIS78Hits->at(j) == 0);

		mu_is3StEndcap[j] =
		(fabs(mu_sig_diff_qoverp[j]) < MuonMomDiffSigCut) &&
		((mu_nTGCLayer1PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nTGCLayer2PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nTGCLayer3PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nTGCLayer4PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nCSCPhiHits->at(j)   >= MuonPhiHitsCut) >= MuonPhiLayerCut) &&    
		(((mu_nMDTEIHits->at(j) >= MuonMDTHitsCut) || (mu_nCSCEtaHits->at(j) >= MuonMDTHitsCut) ) +
		(mu_nMDTEMHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTEOHits->at(j) >= MuonMDTHitsCut) == 3) &&
		(mu_nMDTBIHits->at(j) == 0) &&
		(mu_nMDTBMHits->at(j) == 0) &&
		(mu_nMDTBOHits->at(j) == 0) &&
		(mu_nMDTBEEHits->at(j) == 0) &&
		(mu_nMDTEEHits->at(j) == 0) &&
		(mu_nMDTBIS78Hits->at(j) == 0);

		mu_is3St[j] = mu_is3StBarrel[j] || mu_is3StEndcap[j];
		
		mu_is2StBarrel[j] =
		!mu_is3St[j] &&
		(fabs(mu_sig_diff_qoverp[j]) < MuonMomDiffSigCut2) &&
		((mu_nRPCLayer1PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nRPCLayer2PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nRPCLayer3PhiHits->at(j) >= MuonPhiHitsCut2) >= MuonPhiLayerCut2) &&
		((mu_nMDTBIHits->at(j) >= MuonMDTHitsCut2) +
		(mu_nMDTBOHits->at(j) >= MuonMDTHitsCut2) == 2) &&
		(mu_nMDTEIHits->at(j) == 0) &&
		(mu_nMDTEMHits->at(j) == 0) &&
		(mu_nMDTEOHits->at(j) == 0) &&
		(mu_nCSCEtaHits->at(j) == 0) &&
		(mu_nMDTBEEHits->at(j) == 0) &&
		(mu_nMDTEEHits->at(j) == 0) &&
		(mu_nMDTBIS78Hits->at(j) == 0) &&
		(fabs(mu_eta->at(j)) < 1.00) &&
		((mu_phiSector[j] % 2 == 0) || (fabs(mu_eta->at(j)) < 0.85)) &&
		!((mu_phiSector[j] ==  2) && (mu_eta->at(j) > 0.85)) &&
		!((mu_phiSector[j] == 13) && (mu_eta->at(j) > 0.00) && (mu_eta->at(j) < 0.65));
		
		mu_is2StEndcap[j] =
		!mu_is3St[j] &&
		(fabs(mu_sig_diff_qoverp[j]) < MuonMomDiffSigCut2) &&
		((mu_nTGCLayer1PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nTGCLayer2PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nTGCLayer3PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nTGCLayer4PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nCSCPhiHits->at(j)   >= MuonPhiHitsCut2) >= MuonPhiLayerCut2) &&    
		((mu_nMDTEIHits->at(j) >= MuonMDTHitsCut2) +
		(mu_nMDTEMHits->at(j) >= MuonMDTHitsCut2) == 2) &&
		(mu_nMDTBIHits->at(j) == 0) &&
		(mu_nMDTBMHits->at(j) == 0) &&
		(mu_nMDTBOHits->at(j) == 0) &&
		(mu_nMDTBEEHits->at(j) == 0) &&
		(mu_nMDTEEHits->at(j) == 0) &&
		(mu_nMDTBIS78Hits->at(j) == 0) &&
		(mu_phiSector[j] % 2 == 0) && (fabs(mu_eta->at(j)) > 1.20) && (fabs(mu_eta->at(j)) < 1.40);

		// mu_is2St[j] = mu_is2StBarrel[j] || mu_is2StEndcap[j];
		mu_is2St[j] = mu_is2StBarrel[j];
		
		if     (mu_is3St[j]  &&  !mu_is2St[j]) classified[j] = 33;
		else if(mu_is2St[j]  &&  !mu_is3St[j]) classified[j] = 32;
		else                                   classified[j] = 0;
	}
}



inline bool selection::nMShitsCut3233(float MuonPhiHitsCut,    float MuonPhiLayerCut,  float MuonMDTHitsCut,  float MuonMomDiffSigCut,
									  float MuonPhiHitsCut2,   float MuonPhiLayerCut2, float MuonMDTHitsCut2, float MuonMomDiffSigCut2,
									  bool allow3_3st, bool allow3_2st, vector<bool>& muQAflags, vector<float>& mu_sig_diff_qoverp,
									  vector<float>* mu_eta, vector<float>* mu_phi, vector<float>* mu_charge,
									  vector<int>* mu_nMDTBIHits, vector<int>* mu_nMDTBMHits, vector<int>* mu_nMDTBOHits,
									  vector<int>* mu_nMDTEIHits, vector<int>* mu_nMDTEMHits, vector<int>* mu_nMDTEOHits,
									  vector<int>* mu_nMDTBEEHits, vector<int>* mu_nMDTEEHits, vector<int>* mu_nMDTBIS78Hits,
									  vector<int>* mu_nRPCLayer1PhiHits, vector<int>* mu_nRPCLayer2PhiHits, vector<int>* mu_nRPCLayer3PhiHits,
									  vector<int>* mu_nTGCLayer1PhiHits, vector<int>* mu_nTGCLayer2PhiHits, vector<int>* mu_nTGCLayer3PhiHits, vector<int>* mu_nTGCLayer4PhiHits,
									  vector<int>* mu_nCSCEtaHits, vector<int>* mu_nCSCPhiHits,
									  int& ai, int& bi
									  )
{
	if(allow3_3st && allow3_2st) _FATAL("cannot call 3+3 and 3+2");

	unsigned int muSize = mu_eta->size();

	vector<int> mu_phiSector;
	vector<int> mu_nStations;
	vector<int> mu_is3StBarrel;
	vector<int> mu_is3StEndcap;
	vector<int> mu_is3St;
	vector<int> mu_is2StBarrel;
	vector<int> mu_is2StEndcap;
	vector<int> mu_is2St;
	for(unsigned int i=0 ; i<muSize ; i++)
	{
		mu_phiSector.push_back(0);
		mu_nStations.push_back(0);
		mu_is3StBarrel.push_back(0);
		mu_is3StEndcap.push_back(0);
		mu_is3St.push_back(0);
		mu_is2StBarrel.push_back(0);
		mu_is2StEndcap.push_back(0);
		mu_is2St.push_back(0);
	}
	
	for(unsigned int j=0 ; j<muSize ; j++)
	{
		if(!muQAflags[j]) continue;
	
		mu_phiSector[j] = getPhiSector(mu_phi->at(j));

		// Count nStations
		mu_nStations[j] =
		(mu_nMDTBIHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTBMHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTBOHits->at(j) >= MuonMDTHitsCut) +
		((mu_nMDTEIHits->at(j) >= MuonMDTHitsCut) || (mu_nCSCEtaHits->at(j) >= MuonMDTHitsCut) ) +
		(mu_nMDTEMHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTEOHits->at(j) >= MuonMDTHitsCut);

		mu_is3StBarrel[j] =
		(fabs(mu_sig_diff_qoverp[j]) < MuonMomDiffSigCut) &&
		((mu_nRPCLayer1PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nRPCLayer2PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nRPCLayer3PhiHits->at(j) >= MuonPhiHitsCut) >= MuonPhiLayerCut) &&
		((mu_nMDTBIHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTBMHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTBOHits->at(j) >= MuonMDTHitsCut) == 3) &&
		(mu_nMDTEIHits->at(j) == 0) &&
		(mu_nMDTEMHits->at(j) == 0) &&
		(mu_nMDTEOHits->at(j) == 0) &&
		(mu_nCSCEtaHits->at(j) == 0) &&
		(mu_nMDTBEEHits->at(j) == 0) &&
		(mu_nMDTEEHits->at(j) == 0) &&
		(mu_nMDTBIS78Hits->at(j) == 0);

		mu_is3StEndcap[j] =
		(fabs(mu_sig_diff_qoverp[j]) < MuonMomDiffSigCut) &&
		((mu_nTGCLayer1PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nTGCLayer2PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nTGCLayer3PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nTGCLayer4PhiHits->at(j) >= MuonPhiHitsCut) +
		(mu_nCSCPhiHits->at(j)   >= MuonPhiHitsCut) >= MuonPhiLayerCut) &&    
		(((mu_nMDTEIHits->at(j) >= MuonMDTHitsCut) || (mu_nCSCEtaHits->at(j) >= MuonMDTHitsCut) ) +
		(mu_nMDTEMHits->at(j) >= MuonMDTHitsCut) +
		(mu_nMDTEOHits->at(j) >= MuonMDTHitsCut) == 3) &&
		(mu_nMDTBIHits->at(j) == 0) &&
		(mu_nMDTBMHits->at(j) == 0) &&
		(mu_nMDTBOHits->at(j) == 0) &&
		(mu_nMDTBEEHits->at(j) == 0) &&
		(mu_nMDTEEHits->at(j) == 0) &&
		(mu_nMDTBIS78Hits->at(j) == 0);

		mu_is3St[j] = mu_is3StBarrel[j] || mu_is3StEndcap[j];
		
		mu_is2StBarrel[j] =
		!mu_is3St[j] &&
		(fabs(mu_sig_diff_qoverp[j]) < MuonMomDiffSigCut2) &&
		((mu_nRPCLayer1PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nRPCLayer2PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nRPCLayer3PhiHits->at(j) >= MuonPhiHitsCut2) >= MuonPhiLayerCut2) &&
		((mu_nMDTBIHits->at(j) >= MuonMDTHitsCut2) +
		(mu_nMDTBOHits->at(j) >= MuonMDTHitsCut2) == 2) &&
		(mu_nMDTEIHits->at(j) == 0) &&
		(mu_nMDTEMHits->at(j) == 0) &&
		(mu_nMDTEOHits->at(j) == 0) &&
		(mu_nCSCEtaHits->at(j) == 0) &&
		(mu_nMDTBEEHits->at(j) == 0) &&
		(mu_nMDTEEHits->at(j) == 0) &&
		(mu_nMDTBIS78Hits->at(j) == 0) &&
		(fabs(mu_eta->at(j)) < 1.00) &&
		((mu_phiSector[j] % 2 == 0) || (fabs(mu_eta->at(j)) < 0.85)) &&
		!((mu_phiSector[j] ==  2) && (mu_eta->at(j) > 0.85)) &&
		!((mu_phiSector[j] == 13) && (mu_eta->at(j) > 0.00) && (mu_eta->at(j) < 0.65));
		
		mu_is2StEndcap[j] =
		!mu_is3St[j] &&
		(fabs(mu_sig_diff_qoverp[j]) < MuonMomDiffSigCut2) &&
		((mu_nTGCLayer1PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nTGCLayer2PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nTGCLayer3PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nTGCLayer4PhiHits->at(j) >= MuonPhiHitsCut2) +
		(mu_nCSCPhiHits->at(j)   >= MuonPhiHitsCut2) >= MuonPhiLayerCut2) &&    
		((mu_nMDTEIHits->at(j) >= MuonMDTHitsCut2) +
		(mu_nMDTEMHits->at(j) >= MuonMDTHitsCut2) == 2) &&
		(mu_nMDTBIHits->at(j) == 0) &&
		(mu_nMDTBMHits->at(j) == 0) &&
		(mu_nMDTBOHits->at(j) == 0) &&
		(mu_nMDTBEEHits->at(j) == 0) &&
		(mu_nMDTEEHits->at(j) == 0) &&
		(mu_nMDTBIS78Hits->at(j) == 0) &&
		(mu_phiSector[j] % 2 == 0) && (fabs(mu_eta->at(j)) > 1.20) && (fabs(mu_eta->at(j)) < 1.40);

		// mu_is2St[j] = mu_is2StBarrel[j] || mu_is2StEndcap[j];
		mu_is2St[j] = mu_is2StBarrel[j];
	}
	
	//-----Muon-Pair-Formation-----//
	vector<vector<int> > mupair;
	// bool allow3_3st = false;       // Either 3+3 station muon pairs
	// bool allow3_2st = true;        //     or 3+2 station muon pairs
	bool foundpair3_3st = false;
	bool foundpair3_2st = false;

	// If there are more than three muons, take the two leading opposite-sign muons
	// Muons are sorted by pT, in the array of indices mu_index
	if(muSize>=2)
	{
		for(unsigned int i=0 ; i<muSize-1 ; i++)
		{
			if(!muQAflags[i]) continue;
			for(unsigned int j=i+1 ; j<muSize ; j++)
			{
				if(!muQAflags[j]) continue;
				if((mu_charge->at(i)==-mu_charge->at(j)) && (mu_is3St[i] && mu_is3St[j]))
				{
					mupair.push_back(vector<int>());
					mupair[mupair.size()-1].push_back(i);
					mupair[mupair.size()-1].push_back(j);
					foundpair3_3st = true;
					break;
				}
			}
			if(foundpair3_3st) break;
		}
		if(!foundpair3_3st)
		{
			for(unsigned int i=0 ; i<muSize-1 ; i++)
			{
				if(!muQAflags[i]) continue;
				for(unsigned int j=i+1 ; j<muSize ; j++)
				{
					if(!muQAflags[j]) continue;
					if
					(
						(mu_charge->at(i)==-mu_charge->at(j)) && 
						((mu_is3St[i] && mu_is2St[j]) || (mu_is2St[i] && mu_is3St[j]))
					)
					{
						mupair.push_back(vector<int>());
						mupair[mupair.size()-1].push_back(i);
						mupair[mupair.size()-1].push_back(j);
						foundpair3_2st = true;
						break;
					}
				}
				if(foundpair3_2st) break;
			}
		}
	}
	
	if(allow3_3st && foundpair3_3st)
	{
		ai = mupair[0][0];
		bi = mupair[0][1];
		return true;
	}
	if(allow3_2st && foundpair3_2st)
	{
		ai = mupair[0][0];
		bi = mupair[0][1];
		return true;
	}
	return false;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

#endif

