#include "all.h"
#include "roofit.h"

/*
	1. There are 2 kinds of unbinned, non-detector weights:
		a. cross section weight, wXS, because the samples are binned in mass - relevant for the three models
		b. model weight, xR, the ratio between ZP or KK and Z0 - relevant for the ZP and KK models only
	2. There is the acceptance binned weight (trigger efficiency is ignored currently)
	3. The truth PDF is (3/8)*(1+x^2+Afb*x)
	4. The PDF should be corrected for the acceptance by a simple multiplication:      PDF(x) = PDFtru(x)*Acc(x)
	5. Each event should be weighted (unbinned) according to the non-detector weights: w = wXS*wR
*/

// bins for the mHat histos
const  int      nxbins = 30;
static Double_t logXmin;
static Double_t logXmax;
static Double_t logXbinwidth;
static Double_t xbins[nxbins+1];
Int_t  iMassNbins = 30; // for non log bins


double   costmin = minCosTheta;
double   costmax = maxCosTheta;
int      ncostbins = nCosThetaBins;

double _Afb = 0.;

TFile* file = new TFile("weights.root", "READ");

vector<TTree*> vtData;
float mass_tru, mass_rec, mass_wgt;
float cost_tru, cost_rec, cost_wgt;
float xscn_wgt;

vector<TH1D*>  vhAcc;
vector<TH1D*>  vhMass;
vector<TString> vModelName;
TLegend* leg;
TPaveText* pvtxt;
TText* txt;

RooRealVar* cosThe; // the variable 
RooRealVar* weight; // the weight
RooRealVar* Afb;     // the parameter to find


vector<RooAbsData*> vDataSet; // Roo Data holder
vector<RooFitResult*> vFitResult;


vector<RooAbsPdf*> vModel;   // the final model pdf
vector<RooAbsPdf*> vDetAcc;  // will be taken from the acceptance histogram
vector<RooAbsPdf*> vRecEff;  // will be taken from the reconstruction efficiency histogram
vector<RooAbsPdf*> vTrigEff; // will be taken from the trigger efficiency histogram
vector<RooAbsPdf*> vEffPdf;  // will be the product of all the eff-like pdf's (=rec*trig*acc)
RooAbsPdf* sigPdf;  // will be the truth pdf

vector<RooDataHist*> vrdhAcc;
vector<RooHistPdf*>  vrhpdfAcc;


void setBranches(int mod)
{
	vtData[mod]->SetBranchAddress( "mass_tru", &mass_tru );
	vtData[mod]->SetBranchAddress( "mass_rec", &mass_rec );
	vtData[mod]->SetBranchAddress( "mass_wgt", &mass_wgt );
	vtData[mod]->SetBranchAddress( "cost_tru", &cost_tru );
	vtData[mod]->SetBranchAddress( "cost_rec", &cost_rec );
	vtData[mod]->SetBranchAddress( "cost_wgt", &cost_wgt );
	vtData[mod]->SetBranchAddress( "xscn_wgt", &xscn_wgt );
}

void setLogMassBins(Double_t xmin, Double_t xmax)
{
	logXmin  = log10(xmin);
	logXmax  = log10(xmax);
	logXbinwidth = (Double_t)( (logXmax-logXmin)/(Double_t)nxbins );
	xbins[0] = xmin;
	for(Int_t i=1 ; i<=nxbins ; i++) xbins[i] = TMath::Power( 10,(logXmin + i*logXbinwidth) );
}

void init(int massBin, int mod)
{
	TH1D* hMassBinsDummy = (TH1D*)file->Get("all_histograms/hDummy_afb")->Clone("");
	Double_t iMassMin = hMassBinsDummy->GetBinLowEdge(massBin);
	Double_t iMassMax = iMassMin + hMassBinsDummy->GetBinWidth(massBin);
	
	TString sMassBin = (TString)tostring(massBin);
	string sMassMin = tostring((double)iMassMin);
	string sMassMax = tostring((double)iMassMax);
	TString sTitle = "Mass-bin[" + sMassBin + "] " + sMassMin + "#rightarrow" + sMassMax + " GeV";
	
	setLogMassBins(iMassMin, iMassMax);

	cosThe = new RooRealVar("cosTheta","cos#theta*",costmin,costmax);
    cosThe->setRange("range_cosThe",costmin,costmax);
	cosThe->setBins(ncostbins);
	
	weight = new RooRealVar("weight","weight",0.,1e10);
    //weight->setRange("range_weight",costmin,costmax);
	//weight->setBins(ncostbins);

	Afb = new RooRealVar("Afb","A_{fb}",_Afb,-10.,+10.);

	sigPdf = new RooGenericPdf("CSPDF","CSPDF","(3./8.)*(1. + cosTheta*cosTheta + (8./3.)*Afb*cosTheta)",RooArgSet(*cosThe,*Afb));
	//sigPdf = new RooGenericPdf("CSPDF","CSPDF","(1. + cosTheta*cosTheta + (8./3.)*Afb*cosTheta)",RooArgSet(*cosThe,*Afb));

	TString sName, sId;
	Color_t col; 
	
	switch(mod)
	{
		case Z0:
			sName = "Z^{0}";
			sId = "Z0";
			col = cGammaZ;
			break;
		case ZP:
			sName = "Z'_{SSM}";
			sId = "ZP";
			col = cWJets;
			break;
		case KK:
			sName = "S^{1}/Z_{2} KK";
			sId = "KK";
			col = cDiboson;
			break;
	}
	
	vModelName.push_back( sName );
	
	//vhMass.push_back( new TH1D("hMass_"+sId,"",iMassNbins, iMassMin, iMassMax) );
	vhMass.push_back( new TH1D("hMass_"+sId,"",nxbins,xbins) );
	vhMass[mod]->Reset();
	vhMass[mod]->SetLineColor(col);
	vhMass[mod]->SetTitle(sTitle);
	vhMass[mod]->SetXTitle("m_{#mu#mu} GeV");
	vhMass[mod]->SetYTitle("Events");
	vhMass[mod]->GetXaxis()->SetMoreLogLabels(); 
	vhMass[mod]->GetXaxis()->SetMoreLogLabels(); 
	
	if(mod==Z0) vtData.push_back( (TTree*)file->Get("ntuples/tree_ZP_"+sMassBin) );
	else        vtData.push_back( (TTree*)file->Get("ntuples/tree_"+sId+"_"+sMassBin) );
	
	vhAcc.push_back( (TH1D*)file->Get("cosTheta_histograms/hCosTh"+sId+"_acceptance_"+sMassBin)->Clone("") );
	
	vrdhAcc.push_back( new RooDataHist("rdhAcc"+sId,"rdhAcc"+sId,RooArgSet(*cosThe),vhAcc[mod]) );
	vrhpdfAcc.push_back( new RooHistPdf("rhpdfAcc"+sId,"rhpdfAcc"+sId,RooArgSet(*cosThe),*vrdhAcc[mod],1) );
	vDetAcc.push_back( vrhpdfAcc[mod] );
	vModel.push_back( new RooProdPdf("model_"+sId,"truPdf*effP",*sigPdf,*vDetAcc[mod]) );
	vDataSet.push_back( new RooDataSet("data_"+sId,"data_"+sId,RooArgSet(*cosThe,*weight),WeightVar(weight->GetName())) );
}



void reset()
{
	for(int i=0 ; i<(int)vModelName.size() ; i++)
	{
		delete vhMass[i];
		delete vrdhAcc[i];
		delete vrhpdfAcc[i];
		delete vModel[i];
		delete vDataSet[i];
	}

	vModelName.clear();
	vhMass.clear();
	vtData.clear();
	vhAcc.clear();
	vrdhAcc.clear();
	vrhpdfAcc.clear();
	vDetAcc.clear();
	vModel.clear();
	vDataSet.clear();
	
	delete cosThe;
	delete weight;
	delete Afb;
	delete sigPdf;
}


void loop(int mod)
{
	Int_t N;
	
	setBranches(mod);
	N = vtData[mod]->GetEntries();
	for(Int_t i=0 ; i<N ; i++)
	{
		vtData[mod]->GetEntry(i);
		*cosThe = cost_rec;
		float w;
		if(mod==Z0)
		{
			//*weight = 1.; // !!!
			w = 1.;
			vhMass[mod]->Fill(mass_rec,xscn_wgt);
		}
		else
		{
			//*weight = xscn_wgt*cost_wgt;
			w = xscn_wgt*cost_wgt;
			vhMass[mod]->Fill(mass_rec,xscn_wgt*mass_wgt);
		}
		
		vDataSet[mod]->add(RooArgSet(*cosThe),w);
	}
}

bool minuitStatus( TMinuit * m) 
{
	if (!m) return false;

	TString stat = gMinuit->fCstatu;
	cout << "Minuit: " << stat << ". " << endl;
	if ( stat.Contains("SUCCESSFUL")  || stat.Contains("CONVERGED")  ||stat.Contains("OK") ) return true;

	return false;
}

RooFitResult* fit(int mod)
{
	TMinuit* gFit(0);
	
	_Afb = 0.;
	
	const RooArgSet* fitParsInital = vModel[mod]->getParameters(vDataSet[mod],false);
	RooRealVar* x = (RooRealVar*)fitParsInital->find("Afb");
	if(x) *x = 0.;
	delete fitParsInital;
	
	RooFitResult* fitresult = vModel[mod]->fitTo( *vDataSet[mod],Minos(true),Range("range_cosThe"),Strategy(2),Save(kTRUE),Timer(kTRUE),SumW2Error(true),NumCPU(8));
	gFit = gMinuit;
	return fitresult;
}

void plot(int mod, TVirtualPad* pad)
{
	pad->cd();
	
	RooPlot* plotCosTheta = cosThe->frame(Name("plotCosTheta"), Title( vModelName[mod] ));
	vDataSet[mod]->plotOn(plotCosTheta,Name("cos#theta*"),XErrorSize(0),MarkerSize(0.3),Binning(ncostbins));
	vDetAcc[mod]->plotOn(plotCosTheta,LineWidth(1),LineColor(kBlue));
	//vDetAcc[mod]->plotOn(plotCosTheta,LineWidth(1),LineColor(kGreen),NormRange("rangeX"));

	vModel[mod]->plotOn(plotCosTheta,LineWidth(1),LineColor(kRed),NormRange("range_cosThe"));
	//vModel[mod]->paramOn(plotCosTheta,Layout(0.7,1.,0.4),Format("NEU",AutoPrecision(1)));
	//vModel[mod]->paramOn(plotCosTheta,Layout(0.8,0.95,0.2));
	vModel[mod]->paramOn(plotCosTheta);
	plotCosTheta->getAttText()->SetTextSize(0.05);
	plotCosTheta->getAttLine()->SetLineWidth(0.05);
		
	pad->SetLeftMargin(0.2);
	plotCosTheta->SetTitleOffset(2,"Y");
	plotCosTheta->Draw();
}

void getFit(int mod)
{
	vFitResult.push_back( fit(mod) );
}

void Afb_RooFit_weighted()
{
	style();
	
	int nColumns = 5;
	
	TCanvas* cnv = new TCanvas("fit", "fit", 1024,1280);
	cnv->Draw();
	cnv->Divide(nColumns,nMassBins); // const int nMassBins is defined in constants.h
	
	vector<vector<TVirtualPad*> > vPad;
	vector<vector<TVirtualPad*> > vPadBin;
	vector<vector<double> >       vAfbResult;
	vector<vector<double> >       vAfbError;
	
	vector<TVirtualPad*> vPadTmp;
	vector<double>       vAfbResultTmp;
	vector<double>       vAfbErrorTmp;
	
	vector<TString>      vTitles;
	vector<TCanvas*>     vCanvases;
	vector<TH1D*>        vhMassTmp;
	
	leg = new TLegend(0.006269594,0.03457447,0.9902473,0.4069149,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	pvtxt = new TPaveText(0.006269594,0.5531915,0.9902473,0.9255319,"brNDC");
	pvtxt->SetFillColor(kWhite);
	
	int padCounter = 1;
	
	for(int massBin=1 ; massBin<=nMassBins ; massBin++)
	{
		TString sMassBin = (TString)tostring(massBin);
		
		vPadTmp.clear();
		vAfbResultTmp.clear();
		vAfbErrorTmp.clear();
		vhMassTmp.clear();
		
		vPad.push_back(vPadTmp);
		vPadBin.push_back(vPadTmp);
		vAfbResult.push_back(vAfbResultTmp);
		vAfbError.push_back(vAfbErrorTmp);
		
		vCanvases.push_back( new TCanvas("tmp", "", 604,400) );
		vCanvases[massBin-1]->SetName( sMassBin );
		vCanvases[massBin-1]->Divide(2,2);
		
		
		for(int mod=Z0 ; mod<=KK ; mod++)
		{
			////////////////////////
			init(massBin, mod); ////
			loop(mod); /////////////
			getFit(mod); ///////////
			////////////////////////
			
			vAfbResult[massBin-1].push_back( Afb->getVal() );
			vAfbError[massBin-1].push_back( Afb->getError() );
			//cout << vModelName[mod] << " --> Afb = " << vAfbResult[mod] << " +- " << vAfbError[mod] << endl;
			
			vPad[massBin-1].push_back( cnv->cd( padCounter ) );
			padCounter++;
			plot(mod,vPad[massBin-1][mod]);
			
			vPadBin[massBin-1].push_back( vCanvases[massBin-1]->cd(mod+1) );
			plot(mod,vPadBin[massBin-1][mod]);
		}
		
		vTitles.push_back( vhMass[Z0]->GetTitle() );
		
		vPad[massBin-1].push_back( cnv->cd( padCounter ) );
		padCounter++;
		vPad[massBin-1][KK+1]->SetLogy();
		vPad[massBin-1][KK+1]->SetLogx();
		
		Double_t hMin = getYmin(vhMass[Z0]);
		hMin = (getYmin(vhMass[ZP]) < hMin) ? getYmin(vhMass[ZP]) : hMin;
		hMin = (getYmin(vhMass[KK]) < hMin) ? getYmin(vhMass[KK]) : hMin;
		Double_t hMax = vhMass[Z0]->GetMaximum();
		hMax = (vhMass[ZP]->GetMaximum() > hMax) ? vhMass[ZP]->GetMaximum() : hMax;
		hMax = (vhMass[KK]->GetMaximum() > hMax) ? vhMass[KK]->GetMaximum() : hMax;
		
		vhMass[Z0]->SetMinimum(0.5*hMin);
		vhMass[Z0]->SetMaximum(1.5*hMax);
		
		vhMassTmp.push_back( (TH1D*)vhMass[Z0]->Clone("") );
		vhMassTmp.push_back( (TH1D*)vhMass[ZP]->Clone("") );
		vhMassTmp.push_back( (TH1D*)vhMass[KK]->Clone("") );
		
		if(massBin==1) leg->AddEntry((TH1D*)vhMass[Z0]->Clone(""), "SM #gamma/Z^{0} (#it{ATLAS} MC10 rec')", "l");
		vhMassTmp[Z0]->Clone("")->Draw();
		if(massBin==1) leg->AddEntry((TH1D*)vhMass[ZP]->Clone(""), "1000 GeV Z' SSM Template", "l");
		vhMassTmp[ZP]->Clone("")->Draw("SAMES");
		if(massBin==1) leg->AddEntry((TH1D*)vhMass[KK]->Clone(""), "1000 GeV S^{1}/Z_{2} KK Template", "l");
		vhMassTmp[KK]->Clone("")->Draw("SAMES");
		vPad[massBin-1][KK+1]->RedrawAxis();
		
		pvtxt->Clear();
		txt = pvtxt->AddText( vTitles[massBin-1] );
		//pvtxt->InseretTxt( vTitles[massBin-1] );
		vPad[massBin-1].push_back( cnv->cd( padCounter ) );
		padCounter++;
		pvtxt->Clone("")->Draw();
		leg->Draw("SAMES");
		
		
		//------------------------------------------------------------
		// for the binned canvases
		vPadBin[massBin-1].push_back( vCanvases[massBin-1]->cd( KK+2 ) );
		vPadBin[massBin-1][KK+1]->Draw();
		vPadBin[massBin-1][KK+1]->SetLogy();
		vPadBin[massBin-1][KK+1]->SetLogx();
		vhMassTmp[Z0]->Clone("")->Draw();
		vhMassTmp[ZP]->Clone("")->Draw("SAMES");
		vhMassTmp[KK]->Clone("")->Draw("SAMES");
		vPadBin[massBin-1][KK+1]->RedrawAxis();
		
		vCanvases[massBin-1]->Update();
		vCanvases[massBin-1]->SaveAs("fitplots/FitMassBin_" + sMassBin + ".root");
		vCanvases[massBin-1]->SaveAs("fitplots/FitMassBin_" + sMassBin + ".C");
		vCanvases[massBin-1]->SaveAs("fitplots/FitMassBin_" + sMassBin + ".eps");
		vCanvases[massBin-1]->SaveAs("fitplots/FitMassBin_" + sMassBin + ".ps");
		vCanvases[massBin-1]->SaveAs("fitplots/FitMassBin_" + sMassBin + ".pdf");
		vCanvases[massBin-1]->SaveAs("fitplots/FitMassBin_" + sMassBin + ".png");
		//------------------------------------------------------------
		
		
		cout << "### completted massBin=" << massBin << " ###" << endl;
		/////////////
		reset(); ////
		/////////////
		cout << "### reset massBin=" << massBin << " ###" << endl;
	}
	
	cnv->Update();
	
	cnv->SaveAs("fitplots/FitAllMassBins.root");
	cnv->SaveAs("fitplots/FitAllMassBins.C");
	cnv->SaveAs("fitplots/FitAllMassBins.eps");
	cnv->SaveAs("fitplots/FitAllMassBins.ps");
	cnv->SaveAs("fitplots/FitAllMassBins.pdf");
	cnv->SaveAs("fitplots/FitAllMassBins.png");
}


