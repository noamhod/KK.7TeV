/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */


#ifdef tagNprobe_cxx
#include "tagNprobe.h"

/*
Tag & Probe on Zmumu recipe
---------------------------
First things:
	0. prepare 2 identical histograms:
	   a. probe-muon candidates
	   b. successful probe-muons
	   the efficiency histogram will be hEff=h(b)/h(a)
	1. apply preselection
	2. apply *single* muon selection
	   THIS HAS TO BE DONE WITHOUT THE pT, eta or phi CUTS SINCE
	   WE INVESTIGATE THE EFFICIENCY VS THESE VARIABLES
	3. get a vector of all the "good" muons
---------------------------
Tag muon selection:
	0. mu_index>=0 (otherwise, get seg fault...)
	1. find the muon with smallest dr (mu_L1/EF_dr)
	2. check that mu_L1_dr<0.4 OR mu_EF_dr<0.2
	3. match the muon and trigger tracks by calculating dR=sqrt(dphi^2+deta^2) - compare it with mu_L1/EF_dr value
	4. check that the muon has pT>~1 GeV (don't want to look below that)
	5. check that the muon has pT<20 TeV (...)
	6. check that the matched trigger has pT >= relevant pT threshold (L1_MU10==>10GeV, EF_MU13==>13GeV,...)
	================
	===> tagged <===
	================
---------------------------
Probe muon lookup:
	0. |d0_tag–d0_probe|<0.2 mm
	1. |z0_tag-z0_probe|<1 mm
	2. |phi_tag-phi_probe|>0.5pi
	3. |m(tag+probe)-mZ0|<20 GeV
	4. Q_tag*Q_probe<0
	5. check that the muon has pT>~1 GeV (don't want to look below that)
	6. check that the muon has pT<20 TeV (...)
	=============================================
	===> found a probe candidate.            <===
	===> fill the denominator histograms (a) <===
	=============================================
	7. mu_index>=0 (otherwise, get seg fault...)
	8. check that mu_L1_dr<0.4 OR mu_EF_dr<0.2
	9. check that the matched trigger has pT >= relevant pT threshold (L1_MU10==>10GeV, EF_MU13==>13GeV,...)
	=============================================
	===> tagged and probed.                  <===
	===> fill the denominator histograms (a) <===
	===> fill the numerator histograms (b)   <===
	=============================================
---------------------------
*/


tagNprobe::tagNprobe()
{
	dRmax_mu_L1 = 0.4;
	dRmax_mu_EF = 0.2;
	dRmax_muTrk_trigTrk = 0.01;
	mu_pTmin = 1.;     // in GeV
	mu_pTmax = 200000; // in GeV (20 TeV)
	dd0max_muTag_muProb = 0.2; // in mm
	dz0max_muTag_muProb = 1.; // in mm
	dMmax_muTag_muProb = 20.; // in GeV
	dphimax_muTag_muProb = 0.5*pi;
}

tagNprobe::~tagNprobe()
{
	
}

//-------------- for rel16 -------------------------------------------------------------------------------
// matchLXtrigger = matchL1trigger or matchL2trigger (X=1 or X=2)
int tagNprobe::matchLXtrigger(int mu_ROIindex,
							  float mu_dR,
							  float mu_phi,
							  float mu_eta,
							  float pTthreshold,
							  vector<float>*  trig_phi,
							  vector<float>*  trig_eta,
							  vector<float>*  trig_pt,
							  vector<string>* trig_thresholdName
							  )
{
	if(false) cout << "trig_thresholdName = " << trig_thresholdName << endl;

	float mu_dRthreshold     = 0.2;
	float muTrig_dRthreshold = 0.2;
	
	if(mu_ROIindex<0)      return -999;
	if(mu_dR<0.)           return -999;
	if(trig_pt==0)         return -999;    
	if(trig_pt->size()==0) return -999;    
	if(trig_pt->at(mu_ROIindex)*MeV2GeV < pTthreshold) return -999;    
	float dphi_muTrig = 100.;
	float deta_muTrig = 100.;
	float dR_muTrig   = 100.;
	if(mu_dR<mu_dRthreshold)
	{
		dphi_muTrig = trig_phi->at(mu_ROIindex) - mu_phi;
		deta_muTrig = trig_eta->at(mu_ROIindex) - mu_eta;
		dR_muTrig   = sqrt(dphi_muTrig*dphi_muTrig + deta_muTrig*deta_muTrig);
		if(dR_muTrig<=muTrig_dRthreshold  &&  dR_muTrig<=mu_dR) { cout << "L1: dR_muTrig=" << dR_muTrig << endl; return mu_ROIindex; }
	}
	return -999;
}

int tagNprobe::matchEFtrigger(int mu_ROIindex,
							  float mu_dR,
							  float mu_phi,
							  float mu_eta,
							  float pTthreshold,
							  vector<vector<float> >* trig_phi,
							  vector<vector<float> >* trig_eta,
							  vector<vector<float> >* trig_pt,
							  vector<vector<int> >*   trig_has)
{
	float mu_dRthreshold     = 0.2;
	float muTrig_dRthreshold = 0.2;

	if(mu_ROIindex<0) return -999;
	if(mu_dR<0.)      return -999;
	float dphi_muTrig = 100.;
	float deta_muTrig = 100.;
	float dR_muTrig   = 100.;
	float dR_min      = 100.;
	int iTrigTrack    = -999;
	if(mu_dR<mu_dRthreshold)
	{
		for(int t=0 ; t<(int)trig_has->at(mu_ROIindex).size() ; t++)
		{
			if(!trig_has->at(mu_ROIindex)[t])                     continue;
			if(trig_pt->at(mu_ROIindex)[t]*MeV2GeV < pTthreshold) continue;
			dphi_muTrig = trig_phi->at(mu_ROIindex)[t] - mu_phi;
			deta_muTrig = trig_eta->at(mu_ROIindex)[t] - mu_eta;
			dR_muTrig   = sqrt(dphi_muTrig*dphi_muTrig + deta_muTrig*deta_muTrig);
			if(dR_muTrig<dR_min)
			{
				iTrigTrack = t;
				dR_min = dR_muTrig;
			}
		}
		if(dR_min<=muTrig_dRthreshold  &&  dR_min<=mu_dR) { cout << "dR_min=" << dR_min << endl; return iTrigTrack; }
	}
	return -999;
}
//-----------------------------------------------------------------------------------------------------------

// needs to be called after the single muon selection, as done without the pT, eta and phi cuts.
int tagNprobe::tagMask
(
	string sTrigName, string sTrigType, float pTtrigThreshold,
	vector<bool>& mu_qaflg,
	int skipMuIndex, int& muTag, int& ROITag, int& trigTrkTag,
	vector<int>*   mu_index,
	vector<float>* mu_dr,
	vector<float>* mu_phi,
	vector<float>* mu_eta,
	vector<float>* mu_pt,
	vector<float>* mu_qoverp,
	vector<float>* mu_theta,
	vector<vector<float> >* trig_phi,
	vector<vector<float> >* trig_eta,
	vector<vector<float> >* trig_pt,
	vector<vector<int> >*   trig_has
)
{
	// mask:
	// 0: at least one NULL pointer given
	// 1: less than 2 muons in the event
	// 2: less than 2 good muons in the event
	// 3: problem with trigger name association
	// 4: cannot find a tag muon candidate
	// 5: found a tag muon candidate but there are no ROIs to match with
	// 6: found a tag muon candidate but cannot match it with an ROI
	// 7: found a tag muon candidate, matched it with an ROI but cannot match it with a trigger track
	// 8: problem with "sTrigType"
	// 9: found a tag muon and matched it with an ROI and a trigger track but pT(mu) is < mu_pTmin
	// 10: found a tag muon candidate and matched it with an ROI and a trigger track but pT(mu) is > mu_pTmax
	// 11: found a tag muon candidate and matched it with an ROI and a trigger track, pT(mu) is in bounds but pT(trigTrk) < pTtrigThreshold
	// 12: found a tag muon
	
	if(mu_index==0)  return 0;
	if(mu_dr==0)     return 0;
	if(mu_phi==0)    return 0;
	if(mu_eta==0)    return 0;
	if(mu_pt==0)     return 0;
	if(mu_qoverp==0) return 0;
	if(mu_theta==0)  return 0;
	if(trig_phi==0)  return 0;
	if(trig_eta==0)  return 0;
	if(trig_pt==0)   return 0;
	if(trig_has==0)  return 0;
	
	if(mu_qaflg.size()<2) return 1;
	
	int nGoodMus = 0;
	for(int i=0 ; i<(int)mu_qaflg.size() ; i++) nGoodMus += mu_qaflg[i];
	if(nGoodMus<2) return 2;
	
	if     ( (size_t)sTrigName.find("L1")!=string::npos ) dRmax_mu_trig = dRmax_mu_L1;
	else if( (size_t)sTrigName.find("EF")!=string::npos ) dRmax_mu_trig = dRmax_mu_EF;
	else return 3;
	
	float dRmax  = 999.;
	int tagIndex = 0;
	int iROI     = -1;
	for(int i=0 ; i<(int)mu_dr->size() ; i++)
	{
		if(i==skipMuIndex) continue; // if this muon was already tagged
		if(!mu_qaflg[i])   continue;
		float dr  = mu_dr->at(i);
		int index = mu_index->at(i); 
		if(dr<0.)            continue;
		if(dr>dRmax)         continue;
		if(dr>dRmax_mu_trig) continue;
		dRmax    = dr;
		tagIndex = i;
		iROI     = index;
	}
	if(iROI<0) return 4;
	
	if(trig_has->at(iROI).size()<1) return 5;
	
	dRmax = 999;
	int iTrigTrk = -1;
	int nROIs = 0;
	for(int j=0 ; j<(int)trig_has->at(iROI).size() ; j++)
	{
		if( !trig_has->at(iROI)[j] ) continue;
		nROIs++;
		float dphi = trig_phi->at(iROI)[j] - mu_phi->at(tagIndex);
		float deta = trig_eta->at(iROI)[j] - mu_eta->at(tagIndex);
		float dr = sqrt(dphi*dphi + deta*deta);
		if(dr>dRmax)               continue;
		if(dr>dRmax_muTrk_trigTrk) continue;
		dRmax    = dr;
		iTrigTrk = j;
	}
	if(nROIs==0)   return 6;
	if(iTrigTrk<0) return 7;
	
	float pTtag = 0.;
	if(sTrigType=="SA" || sTrigType=="MS") pTtag = kin.pT(mu_qoverp->at(tagIndex),mu_theta->at(tagIndex))*MeV2GeV;
	else if(sTrigType=="CB")               pTtag = mu_pt->at(tagIndex)*MeV2GeV;
	else return 8;
	
	if(pTtag<mu_pTmin) return 9;
	if(pTtag>mu_pTmax) return 10;
	
	float pTtagTrig = trig_pt->at(iROI)[iTrigTrk];
	if(pTtagTrig<pTtrigThreshold) return 11;
	
	// return indices by reference
	muTag      = tagIndex;
	ROITag     = iROI;
	trigTrkTag = iTrigTrk;
	return 12;
}


// needs to be called after tagMask returned 12.
int tagNprobe::probeCandMask
(
	string sTrigType,
	TVectorP2VL& pmu, vector<bool>& mu_qaflg,
	int muTag,
	vector<float>* mu_phi,
	vector<float>* mu_eta,
	vector<float>* mu_pt,
	vector<float>* mu_qoverp,
	vector<float>* mu_theta,
	vector<float>* mu_d0,
	vector<float>* mu_z0,
	vector<float>* mu_charge
)
{
	// mask:
	// 0: at least one NULL pointer given
	// 1: less than 2 muons in the event
	// 2: less than 2 good muons in the event
	// 3: problem with trigger type association
	// 4: cannot find any probe muon candidates
	// 5: found at least one probe muon candidate (indices are stored in the vector m_viProbes)
	
	////////////////////////////////////////////////
	if(m_viProbes.size()>0) m_viProbes.clear(); ////
	////////////////////////////////////////////////
	
	if(mu_phi==0)    return 0;
	if(mu_eta==0)    return 0;
	if(mu_pt==0)     return 0;
	if(mu_charge==0) return 0;
	if(mu_qoverp==0) return 0;
	if(mu_theta==0)  return 0;
	if(mu_z0==0)     return 0;
	if(mu_d0==0)     return 0;
	
	if(mu_qaflg.size()<2) return 1;
	
	int nGoodMus = 0;
	for(int i=0 ; i<(int)mu_qaflg.size() ; i++) nGoodMus += mu_qaflg[i];
	if(nGoodMus<2) return 2;
	
	if(sTrigType!="SA" && sTrigType!="MS" && sTrigType!="CB") return 3;
	
	for(int i=0 ; i<(int)mu_pt->size() ; i++)
	{
		if(i==muTag)     continue; // mu_probe!=mu_tag...  
		if(!mu_qaflg[i]) continue;
	
		// tag+prob muons have to composite a Z candidate
		float dz0   = fabs(mu_z0->at(i) - mu_z0->at(muTag));
		float dd0   = fabs(mu_d0->at(i) - mu_d0->at(muTag));
		float dphi  = fabs(mu_phi->at(i) - mu_phi->at(muTag));
		float mHat  = kin.imass(pmu[i],pmu[muTag]); // pmu is already in TeV
		float Q1xQ2 = mu_charge->at(i)*mu_charge->at(muTag);
		float dm    = fabs(mHat-mZ0*GeV2TeV)*TeV2GeV;
		
		if(dz0>dz0max_muTag_muProb)    continue;
		if(dd0>dd0max_muTag_muProb)    continue;
		if(dphi<=dphimax_muTag_muProb) continue;
		if(dm>dMmax_muTag_muProb)      continue;
		if(Q1xQ2>0.)                   continue;
		
		// already checked that sTrigType is valid
		float pTprob  = 0.;
		if(sTrigType=="CB") pTprob = kin.pT(mu_qoverp->at(i),mu_theta->at(i))*MeV2GeV;
		else                pTprob = mu_pt->at(i)*MeV2GeV;
		if(pTprob<mu_pTmin) continue;
		if(pTprob>mu_pTmax) continue;
		
		/////////////////////////////
		// FOUND A PROBE CANDIDATE //
		m_viProbes.push_back(i); ////
		/////////////////////////////
	}
	if(m_viProbes.size()==0) return 4;
	return 5;
}
	

int tagNprobe::probeMask
(
	int iprobeCand,
	string sTrigName, float pTtrigThreshold,
	vector<bool>& mu_qaflg,
	int muTag, int ROITag, int trigTrkTag,
	int& muProb, int& ROIProb, int& trigTrkProb,
	vector<int>*   mu_index,
	vector<float>* mu_dr,
	vector<float>* mu_phi,
	vector<float>* mu_eta,
	vector<vector<float> >* trig_phi,
	vector<vector<float> >* trig_eta,
	vector<vector<float> >* trig_pt,
	vector<vector<int> >*   trig_has
)
{
	// mask:
	// 0: at least one NULL pointer given
	// 1: less than 2 muons in the event
	// 2: less than 2 good muons in the event
	// 3: problem with trigger name association
	// 4: mu_prob = mu_tag  OR  ROIprob = ROItag
	// 5: mu_dr_probe < 0
	// 6: mu_dr_probe > dRmax_mu_trig
	// 7: found ROI but it is < 0
	// 8: found a valid ROI but the corresponding tigger track vector size is <=0
	// 9: found a valid ROI and the corresponding tigger track vector size is >0 but there are no tracks with "has" flag turned on 
	// 10: found a valid ROI with at least one track with "has" flag turned on, but cannot match it with the probe muon candidate
	// 11: found a valid ROI with at least one track with "has" flag turned on, matched it with the probe muon candidate but trigger pT < pTtrigThreshold
	// 12: found a probe muon

	if(mu_index==0)  return 0;
	if(mu_dr==0)     return 0;
	if(mu_phi==0)    return 0;
	if(mu_eta==0)    return 0;
	if(trig_phi==0)  return 0;
	if(trig_eta==0)  return 0;
	if(trig_pt==0)   return 0;
	if(trig_has==0)  return 0;
	
	if(mu_qaflg.size()<2) return 1;
	
	int nGoodMus = 0;
	for(int i=0 ; i<(int)mu_qaflg.size() ; i++) nGoodMus += mu_qaflg[i];
	if(nGoodMus<2) return 2;
	
	if     ( (size_t)sTrigName.find("L1")!=string::npos ) dRmax_mu_trig = dRmax_mu_L1;
	else if( (size_t)sTrigName.find("EF")!=string::npos ) dRmax_mu_trig = dRmax_mu_EF;
	else return 3;

	if(iprobeCand==muTag) return 4; // mu_probe!=mu_tag...
	
	float dr  = mu_dr->at(iprobeCand);
	int index = mu_index->at(iprobeCand);
	if(index==ROITag)    return 4; // ROI_probe!=ROI_tag...   ???????????????????????????????????????????
	if(dr<0.)            return 5;
	if(dr>dRmax_mu_trig) return 6;
	int iROI = index;
	if(iROI<0) return 7;
	
	if(trig_has->at(iROI).size()<1) return 8;
	
	float dRmax  = 999;
	int iTrigTrk = -1;
	int nROIs    = 0;
	for(int j=0 ; j<(int)trig_has->at(iROI).size() ; j++)
	{
		//if(j==trigTrkTag)            continue; // trigTrk_probe!=trigTrk_tag...
		if( !trig_has->at(iROI)[j] ) continue;
		nROIs++;
		float dphi = trig_phi->at(iROI)[j] - mu_phi->at(iprobeCand);
		float deta = trig_eta->at(iROI)[j] - mu_eta->at(iprobeCand);
		float dr = sqrt(dphi*dphi + deta*deta);
		if(dr>dRmax_muTrk_trigTrk) continue;
		if(dr>dRmax)               continue;
		dRmax    = dr;
		iTrigTrk = j;
	}
	if(nROIs==0)   return 9;
	if(iTrigTrk<0) return 10;
	
	float pTprobTrig = trig_pt->at(iROI)[iTrigTrk];
	if(pTprobTrig<pTtrigThreshold) return 11;
	
	// return indices by reference
	muProb      = iprobeCand;
	ROIProb     = iROI;
	trigTrkProb = iTrigTrk;
	return 12;
}

void tagNprobe::calculateEfficiency(TH1D* hCandidates, TH1D* hSucceeded, TH1D* hEfficiency, bool isTruth)
{
	if(isTruth) cout << "isTruth = " << isTruth << endl;

	Double_t cand;
	Double_t prob;
	Double_t eff;
	Double_t deff;
	for(Int_t b=0 ; b<=hEfficiency->GetNbinsX()+1 ; b++) // include overflow/underflow
	{
		cand = hCandidates->GetBinContent(b);
		prob = hSucceeded->GetBinContent(b);
		eff  = (cand!=0) ? prob/cand : 0.;
		deff = (cand!=0) ? sqrt(eff*(1.-eff)/cand) : 0.;
		hEfficiency->SetBinContent(b,eff);
		hEfficiency->SetBinError(b,deff);
		//if(!isTruth) hEfficiency->SetBinError(b,deff);
	}
}

void tagNprobe::calculateEfficiency(TH2D* hCandidates, TH2D* hSucceeded, TH2D* hEfficiency, bool isTruth)
{
	if(isTruth) cout << "isTruth = " << isTruth << endl;
	
	Double_t cand;
	Double_t prob;
	Double_t eff;
	Double_t deff;
	for(Int_t bx=0 ; bx<=hEfficiency->GetNbinsX()+1 ; bx++) // include overflow/underflow
	{
		for(Int_t by=0 ; by<=hEfficiency->GetNbinsY()+1 ; by++) // include overflow/underflow
		{
			cand = hCandidates->GetBinContent(bx,by);
			prob = hSucceeded->GetBinContent(bx,by);
			eff  = (cand!=0) ? prob/cand : 0.;
			deff = (cand!=0) ? sqrt(eff*(1.-eff)/cand) : 0.;
			hEfficiency->SetBinContent(bx,by,eff);
			hEfficiency->SetBinError(bx,by,deff);
			//if(!isTruth) hEfficiency->SetBinError(b,deff);
		}
	}
}

void tagNprobe::calculateEfficiency(TMapSP2TH1D* hMapCandidates, TMapSP2TH1D* hMapSucceeded, TMapSP2TH1D* hMapEfficiency, bool isTruth)
{
	if(isTruth) cout << "isTruth = " << isTruth << endl;
	
	for(TMapSP2TH1D::iterator it=hMapCandidates->begin() ; it!=hMapCandidates->end() ; it++)
	{
		Double_t cand;
		Double_t prob;
		Double_t eff;
		Double_t deff;
		
		string trigper = it->first;
		
		for(Int_t b=0 ; b<=(*hMapEfficiency)[trigper]->GetNbinsX()+1 ; b++) // include overflow/underflow
		{
			cand = (*hMapCandidates)[trigper]->GetBinContent(b);
			prob = (*hMapSucceeded)[trigper]->GetBinContent(b);
			eff  = (cand!=0) ? prob/cand : 0.;
			deff = (cand!=0) ? sqrt(eff*(1.-eff)/cand) : 0.;
			(*hMapEfficiency)[trigper]->SetBinContent(b,eff);
			(*hMapEfficiency)[trigper]->SetBinError(b,deff);
			//if(!isTruth) (*hMapEfficiency)[trigper]->SetBinError(b,deff);
		}
	}
}
#endif



