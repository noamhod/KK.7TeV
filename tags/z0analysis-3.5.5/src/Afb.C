/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */


#ifdef Afb_cxx
#include "Afb.h"

Afb::Afb()
{
	m_mmap_Afb_CS = new TMultimapff();
	m_mmap_Afb_HE = new TMultimapff();
}

Afb::~Afb()
{
	
}


void Afb::fillAfbMap(float mhat, float cosThCS, float cosThHE)
{
	m_mmap_Afb_CS->insert( make_pair(mhat,cosThCS) ); 
	m_mmap_Afb_HE->insert( make_pair(mHat,cosThHE) );
}

void Afb::calculateAfb(TH1D* h)
{	
	TAxis* xaxis   = h->GetXaxis();
	float mHatmin  = (float)xaxis->GetXmin();
	float mHatmax  = (float)xaxis->GetXmax();
	float binWidth = (float)h->GetBinWidth(1); // The bins must be with uniform width !!!
	vector<float> Nf;
	vector<float> Nb;
	
	for(Int_t b=0 ; b<=h->GetNbinsX() ; b++)
	{
		Nf.push_back(0.);
		Nb.push_back(0.);
	}
	
	for(TMultimapff::iterator itCS=m_mmap_Afb_CS->begin() ; itCS!=m_mmap_Afb_CS->end() ; ++itCS)
	{
		mHat              = itCS->first;
		cosThCollinsSoper = itCS->second;
	
		if(mHat>=mHatmin  &&  mHat<=mHatmax)
		{
			int bin = 1 + (int)floor((mHat-mHatmin)/binWidth);
			if(cosThCollinsSoper>=0) Nf[bin-1]++;
			else         Nb[bin-1]++;
		}
	}
	
	for(Int_t b=1 ; b<=h->GetNbinsX() ; b++)
	{
		float N = Nf[b-1]+Nb[b-1];
		
		// the Forward-Backward Asymmetry:
		float afb = (N>0.) ? (Nf[b-1]-Nb[b-1])/N : -999.;
		
		// the Forward-Backward Asymmetry error: 
		// if N=Nf+Nb, p=Nf/N, q=1-p=Nb/N, then A=p-q=2*p-1.
		// The statistical error on p is sqrt(p*q/N) (binomial distribution),
		// and from this, the statistical error on A is sqrt((1-A*A)/N)
		float dafb = (N>0.) ? sqrt( (1.-afb*afb)/N ) : 0.;
		
		h->SetBinContent(b,afb);
		h->SetBinError(b,dafb);
	}
	
	Nf.clear();
	Nb.clear();
}
#endif



