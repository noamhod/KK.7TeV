#include "TROOT.h"
#include "TF1.h"
#include "TLine.h"
#include "TCanvas.h"

Double_t fCS(Double_t *x, Double_t *par)
{
	Double_t xx = x[0];
	//Double_t f = 3./8. * (1. + xx*xx + 8./3.*par[0]*xx);
	Double_t f = par[0]*(1. + xx*xx) + par[1]*xx;
	return f;
}

TF1* CS(Double_t A, Double_t B, Double_t xmin, Double_t xmax, Color_t col)
{
	TF1 *f = new TF1("CS",fCS,xmin,xmax,1);
	f->SetParNames("A","B");
	//f->SetParameter("B",B);
	f->SetParameter(0,A);
	f->SetParameter(1,B);
	f->SetLineColor(col);
	f->SetLineWidth(1);
	return f;
}

void plot()
{
	TCanvas* cnv = new TCanvas("cnv", "", 600,400);
	cnv->Draw();
	cnv->cd();
	Double_t dB = 0.1;
	Double_t dA = 0.1;
	Double_t maxAbsB = +10.;
	Double_t maxAbsA = +10.;
	Double_t xmin = -1.;
	Double_t xmax = +1.;
	Color_t c  = kRed;
	Color_t dc = 5;
	vector<vector<TF1*> > vvf;

	
	int indexA = 0;
	for(Double_t A=1. ; A<=+maxAbsA ; A=A+dA)
	{
		vector<TF1*> vf;
		vvf.push_back( vf );
		int indexB = 0;
		for(Double_t B=-maxAbsB ; B<=+maxAbsB ; B=B+dB)
		{
			TF1* f = CS(A,B,xmin,xmax,c);
			vvf[indexA].push_back( (TF1*)f->Clone() );
			delete f;

			//cout << "Afb=" << Afb << endl;

			if(indexA==0  &&  indexB==0)
			{
				vvf[indexA][indexB]->SetMaximum(100.);
				vvf[indexA][indexB]->SetMinimum(0.);
				vvf[indexA][indexB]->Draw();
			}
			else                         vvf[indexA][indexB]->Draw("SAMES");
			
			indexB++;
		}
		indexA++;
	}
	
	TLine* line = new TLine(xmin,0.,xmax,0.);
	line->Draw("SAMES");
}
