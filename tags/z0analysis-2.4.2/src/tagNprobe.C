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

bool tagNprobe::findTag(vector<int>* isMatched, vector<float>* dR)
{
	if(isMatched==0)         return false;
	if(isMatched->size()==0) return false;

	bool tagged = false;
	dRbest = 1000.;
	for(int t=0 ; t<(int)isMatched->size() ; t++)
	{
		if(!isMatched->at(t)) continue;
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

int tagNprobe::findProbe(vector<int>* isMatched, TVectorP2VL& pmu, vector<float>* charge, int itag)
{
	// Probe mask:
	// retrun 0: matched vector is NULL or empty
	// retrun 1: found probe candidate but didn't probed it
	// retrun 2: found probe candidate and probed it
	// retrun 3: else

	if(isMatched==0)         return 0;
	if(isMatched->size()==0) return 0;
	
	bool probeCandidate = false;
	
	for(int t=0 ; (t<(int)isMatched->size() && t!=itag) ; t++)
	{
		mHat  = kin.imass(pmu[itag],pmu[t]);
		Q1xQ2 = charge->at(itag)*charge->at(t);
		if( fabs(mHat-mZ0*GeV2TeV)<mHatDiffThreshold  &&  Q1xQ2<0. ) // on Z mass and opposite charge
		{
			probeIndex = t;
			probeCandidate = true;
			if( isMatched->at(t) ) return 2;
		}
	}
	
	if(probeCandidate) return 1;
	
	return 3;
}

int tagNprobe::tagNprobeMask(int wasEventTriggered, vector<int>* isMatched, vector<float>* dR,
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
	
	if(!wasEventTriggered)  return 0;
	if(isMatched->size()<1) return 1;
	
	// Tag first
	isTag = findTag(isMatched,dR);
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
	int probMask = findProbe(isMatched, pmu, charge, tagIndex);
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

int tagNprobe::truthMask(int wasEventTriggered, vector<int>* isMatched, vector<float>* dR,
						 vector<float>* eta, vector<float>* phi,
						 vector<float>* etaTruth, vector<float>* phiTruth, vector<float>* pTtruth,
						 int& irec, int& itru)
{
	// Truth efficiency mask:
	// retrun 0: truth pT vector is <=0
	// retrun 1: didn't find truth muon with pT>0.
	// retrun 2: found truth muon with pT>0 and event was not triggered
	// retrun 3: found truth muon with pT>0, event was triggered but isMatched=0 or isMatched->size()=0
	// retrun 4: found truth muon with pT>0, event was triggered but no reconstructed muon was matched to the trigger
	// retrun 4: found truth muon with pT>0, event was triggered but no reconstructed muon was matched to the trigger
	// retrun 5: found truth muon with pT>0, event was triggered and reconstructed muon was matched to the trigger but didn't match to truth
	// retrun 6: found truth muon with pT>0, event was triggered and reconstructed muon was matched to the trigger and to truth
	// retrun 7: else

	if(pTtruth->size()<=0) return 0;
	
	float pTmax = 0.;
	truth_pTmaxIndex = 0;
	recon_pTmaxIndex = 0;
	triggerIndex = 0;
	bool  pTmaxFound = false;
	bool  reconFound  = false;
	bool  trigFound   = false;
	dRbest = 1000.;
	
	
	// find the truth candidate
	for(int i=0 ; i<(int)pTtruth->size() ; i++)
	{
		if(pTtruth->at(i) > pTmax)
		{
			pTmax = pTtruth->at(i);
			truth_pTmaxIndex = i;
			pTmaxFound = true;
		}
	}
	itru = truth_pTmaxIndex;
	if(!pTmaxFound) return 1;
	if(!wasEventTriggered) return 2;
	if(isMatched==0  ||  isMatched->size()==0) return 3;
	
	// find the main reconstructed trigger muon
	for(int t=0 ; t<(int)isMatched->size() ; t++)
	{
		if(!isMatched->at(t)) continue;
		float dr = dR->at(t);
		if(dr<dRbest  &&  dr>0.)
		{
			dRbest = dr;
			triggerIndex = t;
			trigFound = true;
		}
	}
	if(!trigFound) return 4;
	if(dRbest>dRthreshold) return 5;
	
	// match the reconstructed triggered muon to the truth muon
	dRbest = 1000.;
	for(int tt=0 ; tt<(int)pTtruth->size() ; tt++)
	{
		float deta = eta->at(triggerIndex)-etaTruth->at(tt);
		float dphi = phi->at(triggerIndex)-phiTruth->at(tt);
		float dr = sqrt( deta*deta + dphi*dphi );
		if(dr<dRbest  &&  dr>0.)
		{
			dRbest = dr;
			recon_pTmaxIndex = tt;
			reconFound = true;
		}
	}
	irec = recon_pTmaxIndex;
	if(!reconFound) return 5;
	if(dRbest<=dRthreshold) return 6;
	return 7;
}

void tagNprobe::calculateEfficiency(TH1D* hCandidates, TH1D* hSucceeded, TH1D* hEfficiency, bool isTruth)
{
	Double_t cand;
	Double_t prob;
	Double_t eff;
	Double_t deff;
	for(Int_t b=0 ; b<=hEfficiency->GetNbinsX() ; b++) // include overflow/underflow
	{
		cand = hCandidates->GetBinContent(b);
		prob = hSucceeded->GetBinContent(b);
		eff  = (cand!=0) ? prob/cand : 0.;
		deff = (cand!=0) ? sqrt(eff*(1.-eff)/cand) : 0.;
		hEfficiency->SetBinContent(b,eff);
		if(!isTruth) hEfficiency->SetBinError(b,deff);
	}
}
#endif



