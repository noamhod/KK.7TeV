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
	m_mmap_Afb = new TMultimapff();
	//file = new ofstream();
	//file->open( "Afb.raw" );
}

Afb::~Afb()
{
	//file->close();
}


void Afb::fillAfbMap(float mHat, float cosTh)
{
	m_mmap_Afb->insert( make_pair(mHat,cosTh) ); 
}

void Afb::calculateAfb(TH1D* h, TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();
	m_Afb_tree = new TTree("Afb_tree","Afb_tree");
	m_Afb_tree->SetDirectory(tdir);
	m_Afb_tree->Branch( "mHat",  &mHat );
	m_Afb_tree->Branch( "cosTh", &cosTh );
	
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
	
	for(TMultimapff::iterator it=m_mmap_Afb->begin() ; it!=m_mmap_Afb->end() ; ++it)
	{
		mHat  = it->first;
		cosTh = it->second;
		m_Afb_tree->Fill();
		//(*file) << mHat << "\t" << cosTh << endl;
		if(mHat>=mHatmin  &&  mHat<=mHatmax)
		{
			int bin = 1 + (int)floor((mHat-mHatmin)/binWidth);
			if(cosTh>=0) Nf[bin-1]++;
			else         Nb[bin-1]++;
			//cout << "Nf[" << bin-1 << "]=" << Nf[bin-1] << ",  Nf[" << bin-1 << "]=" << Nb[bin-1] << endl;
		}
	}
	tdir->cd();
	//m_Afb_tree->Write();
	
	for(Int_t b=1 ; b<=h->GetNbinsX() ; b++)
	{
		float N = Nf[b-1]+Nb[b-1];
		
		// the Forward-Backward Asymmetry:
		float afb = (N>0.) ? (Nf[b-1]-Nb[b-1])/N : 0.;
		
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



