/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */


#ifdef tagNprobe_cxx
#include "tagNprobe.h"

tagNprobe::tagNprobe()
{
	dRthreshold = 0.2;
	mu_dRthreshold = 0.2;
	muTrig_dRthreshold = 0.2;
	mHatDiffThreshold = 10.*GeV2TeV;
}

tagNprobe::~tagNprobe()
{
	
}

void tagNprobe::reset()
{
	tagIndex   = -1;
	probeIndex = -1;
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
							  vector<string>* trig_thresholdName, ofstream* f
							  )
{
	if(false) cout << "trig_thresholdName = " << trig_thresholdName << endl;

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
		if(dR_muTrig<=muTrig_dRthreshold  &&  dR_muTrig<=mu_dR) { (*f) << "L1: dR_muTrig=" << dR_muTrig << endl; return mu_ROIindex; }
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
							  vector<vector<int> >*   trig_has, ofstream* f)
{
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
		if(dR_min<=muTrig_dRthreshold  &&  dR_min<=mu_dR) { (*f) << "dR_min=" << dR_min << endl; return iTrigTrack; }
	}
	return -999;
}
//-----------------------------------------------------------------------------------------------------------

bool tagNprobe::findTag(vector<int>* trigger_match, vector<float>* dR)
{
	if(trigger_match==0)         return false;
	if(dR==0)                    return false;
	if(trigger_match->size()==0) return false;

	bool tagged = false;
	dRbest = 1000.;
	for(int t=0 ; t<(int)trigger_match->size() ; t++)
	{
		if(!trigger_match->at(t)) continue;
		float dr = dR->at(t);
		if(dr<dRbest  &&  dr>0.)
		{
			dRbest = dr;
			tagIndex = t;
			tagged = true;
		}
	}
	if(!tagged) return false;
	
	if(dRbest<=dRthreshold) return true;
	else
	{
		cout << "best tag and trigger objects mismatched: dR=" << dRbest << " where dR threshold is " << dRthreshold << endl;
		return false;
	}
	return false;
}

int tagNprobe::findProbe(vector<int>* trigger_match, TVectorP2VL& pmu, vector<float>* charge, int itag)
{
	// Probe mask:
	// retrun 0: matched vector is NULL or empty
	// retrun 1: found probe candidate but didn't probed it
	// retrun 2: found probe candidate and probed it
	// retrun 3: else

	if(trigger_match==0)         return 0;
	if(charge==0)                return 0;
	if(trigger_match->size()==0) return 0;
	
	bool probeCandidate = false;
	
	for(int t=0 ; (t<(int)trigger_match->size() && t!=itag) ; t++)
	{
		mHat  = kin.imass(pmu[itag],pmu[t]);
		Q1xQ2 = charge->at(itag)*charge->at(t);
		if( fabs(mHat-mZ0*GeV2TeV)<mHatDiffThreshold  &&  Q1xQ2<0. ) // on Z mass and opposite charge
		{
			probeIndex = t;
			probeCandidate = true;
			if( trigger_match->at(t) ) return 2;
		}
	}
	
	if(probeCandidate) return 1;
	
	return 3;
}

int tagNprobe::tagNprobeMask(int wasEventTriggered, vector<int>* trigger_match, vector<float>* dR,
							 TVectorP2VL& pmu, vector<float>* charge, int& itag, int& iprobe)
{
	// Tag&Probe mask:
	// retrun 0: event was not triggered
	// retrun 1: matched vector is NULL or empty
	// retrun 2: event was not tagged
	// retrun 3: event was tagged but with a problem
	// retrun 4: event was tagged, found a probe candidate but not probed it and there's a problem with this cand
	// retrun 5: event was tagged, found a probe candidate but not probed it
	// retrun 6: event was tagged, found a probe candidate and probed it but the probe has a problem
	// retrun 7: event was tagged and probed
	// retrun 8: else
	
	/////////////////
	reset(); ////////
	/////////////////
	
	bool tagged = false;
	
	if(!wasEventTriggered)      return 0;
	if(trigger_match==NULL)     return 0;
	if(dR==NULL)                return 0;
	if(charge==NULL)            return 0;
	if(trigger_match->size()<1) return 1;
	
	// Tag first
	isTag = findTag(trigger_match,dR);
	if(!isTag) return 2;
	if(tagIndex<0  ||  tagIndex>=(int)pmu.size())
	{
		cout << "ERROR: tag is found but its index is invalid: tagIndex=" << tagIndex << endl;
		return 3;
	}
	tagged = true;
	itag   = tagIndex;
	
	// Probe mask:
	// retrun 0: matched vector is NULL or empty
	// retrun 1: found probe candidate but didn't probed it
	// retrun 2: found probe candidate and probed it
	// retrun 3: else
	int probMask = findProbe(trigger_match, pmu, charge, tagIndex);
	if(probMask==0) return 1;
	if(probMask==1)
	{
		iprobe = probeIndex;
		if(probeIndex<0  ||  probeIndex>=(int)pmu.size())
		{
			cout << "ERROR: candidtae probe is found but its index is invalid: candidateProbeIndex=" << probeIndex << endl;
			return 4;
		}
		if(tagged) return 5; // tag + probe-candidate (that was not probed)
	}
	if(probMask==2)
	{
		iprobe = probeIndex;
		if(probeIndex<0  ||  probeIndex>=(int)pmu.size())
		{
			cout << "ERROR: probe is found but its index is invalid: probeIndex=" << probeIndex << endl;
			return 6;
		}
		if(tagged) return 7;  // tag + probe
	}
	if(probMask==3) return 8;
	
	return 8;
}

int tagNprobe::tagNprobeMask(float trigger_min, float trigger_threshold, vector<float>* trigger_pT, vector<int>* trigger_match,
							 TVectorP2VL& pmu, vector<float>* qOp, vector<float>* theta, vector<float>* charge,
							 int& itag, int& iprobe)
{
	// Tag&Probe mask:
	// retrun 0: matched vector is null or empty (no fill)
	// retrun 1: event CANNOT be tagged (no fill)
	// retrun 2: event was tagged but not probed
	// retrun 3: event was tagged and probed but probe candidate has pT < trigger_threshold ???
	// retrun 4: event was tagged and probed but probe candidate has pT problem
	// retrun 5: event was tagged and probed
	// retrun 6: else

	if(trigger_match==NULL)     return 0;
	if(trigger_pT==NULL)        return 0;
	if(charge==NULL)            return 0;
	if(qOp==NULL)               return 0;
	if(theta==NULL)             return 0;
	if(trigger_match->size()<1) return 0;
	
	bool btag = false;
	int  itag_current = 0;
	for(int t=0 ; t<(int)trigger_match->size() ; t++)
	{
		pTtag = fabs(kin.pT(qOp->at(t)/MeV2GeV,theta->at(t)));
	
		if(t==itag)                                     continue; // in the second call of this function, don't count it as tag
		if(!trigger_match->at(t))                       continue; // have to trigger...
		if(trigger_pT->at(t)*MeV2GeV<trigger_threshold) continue; // muon has to pass the relevant trigger pT threshold
		if(pTtag<=trigger_min)                          continue; // muon cannot have pT < pT threshold
		if(trigger_pT->at(t)*MeV2TeV>20.)               continue; // muon trigger pT threshold is not valid
		itag_current = t;
		btag  = true;
		break;
	}
	if(!btag) return 1; // cannot be tagged
	
	
	for(int t=0 ; t<(int)trigger_match->size() ; t++)
	{
		if(t==itag_current) continue; // skip the current tag (the probe cannot be the tag...)
		if(t==iprobe)       continue; // in the second call of this function, don't count it as probe
		
		mHat    = kin.imass(pmu[itag_current],pmu[t]);
		Q1xQ2   = charge->at(itag_current)*charge->at(t);
		pTprobe = fabs(kin.pT(qOp->at(t)/MeV2GeV,theta->at(t)));
		
		if(fabs(mHat-mZ0*GeV2TeV)>mHatDiffThreshold) continue; // have to be on Z mass
		if(Q1xQ2>=0.)                                continue; // require opposite charge
		if(pTprobe<=trigger_min)                     continue; // require minimum probe pT=1 GeV
		
		itag   = itag_current;
		iprobe = t;
		
		if(!trigger_match->at(t)) return 2; // tagged but not probed
		else
		{
			if(trigger_pT->at(t)*MeV2GeV<trigger_threshold) return 3; // tagged and probed but probe candidate has pT < trigger_threshold ???
			if(trigger_pT->at(t)*MeV2TeV>20.)               return 4; // tagged and probed but probe candidate has pT problem
			return 5;                                                 // tagged and probed
		}
	}
	
	return 6;
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



