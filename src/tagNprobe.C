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

int tagNprobe::tagNprobeMask(vector<int>* isMatched, TVectorP2VL& pmu, vector<float>* charge, int& itag, int& iprobe)
{
	// Tag&Probe mask:
	// retrun 0: matched vector is null or empty (no fill)
	// retrun 1: event CANNOT be tagged (no fill)
	// retrun 2: event was tagged, probe candidate found but not probed
	// retrun 3: event was tagged, probe candidate found and probed
	// retrun 4: else

	if(isMatched->size()<1) return 0;
	
	bool tag1  = false;
	int  itag1 = 0;
	for(int t=0 ; t<(int)isMatched->size() ; t++)
	{
		if(t==itag)           continue; // in the second call of this function, don't count it as tag
		if(!isMatched->at(t)) continue; // have to trigger...
		itag1 = t;
		tag1  = true;
		break;
	}
	if(!tag1) return 1; // cannot be tagged
	
	
	for(int t=0 ; t<(int)isMatched->size() ; t++)
	{
		if(t==itag1)  continue; // skip the tag (the probe cannot be the tag...)
		if(t==iprobe) continue; // in the second call of this function, don't count it as probe
		
		mHat  = kin.imass(pmu[itag1],pmu[t]);
		Q1xQ2 = charge->at(itag1)*charge->at(t);
		
		if(fabs(mHat-mZ0*GeV2TeV)>mHatDiffThreshold) continue; // have to be on Z mass
		if(Q1xQ2>=0.)                                continue; // require opposite charge
		
		itag   = itag1;
		iprobe = t;
		
		if(!isMatched->at(t)) return 2; // tagged but not probed
		else                  return 3; // tagged and probed 
	}
	
	return 4;
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



