#include "basics.h"

#ifndef ASYMGRAPH_H
#define ASYMGRAPH_H


double error_poisson_up(double data)
{
	double y1 = data + 1.0;
	double d = 1.0 - 1.0/(9.0*y1) + 1.0/(3*TMath::Sqrt(y1));
	return y1*d*d*d-data;
}

double error_poisson_down(double data)
{
	double y = data;
	if (y == 0.0) return 0.0;
	double d = 1.0 - 1.0/(9.0*y) - 1.0/(3.0*TMath::Sqrt(y));
	return data-y*d*d*d;
}

TGraphAsymmErrors* GetPoissonizedGraph(TH1D* histo, bool isXerr)
{
	TGraphAsymmErrors* graph = new TGraphAsymmErrors();
	
	int j=0;
	for (int i=1;i<=histo->GetNbinsX();++i)
	{
		if (histo->GetBinContent(i)!=0)
		{ 
			graph->SetPoint(j,histo->GetBinCenter(i),histo->GetBinContent(i));
			graph->SetPointError(j,
			(isXerr) ? histo->GetBinWidth(i)/2. : 0.,
			(isXerr) ? histo->GetBinWidth(i)/2. : 0.,
			error_poisson_down(histo->GetBinContent(i)),
			error_poisson_up(histo->GetBinContent(i))
			);
			++j;
		}
	}
	return graph;
}

#endif
