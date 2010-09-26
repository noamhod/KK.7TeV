/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef fitRooFit_cxx
#include "fitRooFit.h"

//#include "RooExtendedExponent.h"


fitRooFit::fitRooFit()
{

}

fitRooFit::fitRooFit(vector<double>* x)
{	
	m_xVecPtr = x;
}

fitRooFit::~fitRooFit()
{

}

void fitRooFit::minimize(bool signal_only, TH1D* h, double* yields)
{
	if(false) cout << "signal_only=" << signal_only << endl;

	//////////////////////////////////////////////////////
	// NOTE: the branch name has to be exactly the same as
	// the observable name (RooRealVar)
	//////////////////////////////////////////////////////
	int eventsInFitRange = 0;
	m_imassTree = new TTree("imassTree", "imassTree");
	m_imassTree->Branch("imass", &m_imass);
	for(int i=0 ; i<(int)m_xVecPtr->size() ; i++)
	{
		m_imass = m_xVecPtr->at(i);
		m_imassTree->Fill();
		if(m_imass>=XFITMIN  &&  m_imass<=XFITMAX) eventsInFitRange++;
	}
	m_imassTree->Write();

	
	// --- SUM
	// --- Construct signal+background PDF ---
	double sbg = scale2data(h)/h->GetBinWidth(1);
	double bg  = scale2bg(h)/h->GetBinWidth(1);
	cout << "Guess Ns=" << (int)sbg << endl;
	cout << "Guess Nb=" << (int)bg << endl;
	int nentries = (int)h->GetEntries();
	RooRealVar nsig("nsig","#signal events",(int)sbg,1,nentries);
	RooRealVar nbkg("nbkg","#background events",(int)bg,1,nentries);
	

	
	// --- Observable ---
	// RooRealVar(const char* name, const char* title, Double_t value, Double_t minValue, Double_t maxValue, const char* unit = "")
	//RooRealVar imass("imass", "#hat{m}_{#mu#mu}", XFULLMIN, XFULLMAX, "MeV");
	RooRealVar imass("imass", "#hat{m}_{#mu#mu}", XFITMIN, XFITMAX, "MeV");
	imass.setRange("fitRange",XFITMIN,XFITMAX);
	
	
	
	// -- SIGNAL
	/*
		RooVoigtian(const char* name, const char* title, RooAbsReal& _x, RooAbsReal& _mean, RooAbsReal& _width, RooAbsReal& _sigma, Bool_t doFast = kFALSE);
		RooVoigtian is an efficient implementation of the convolution
		of a Breit-Wigner with a Gaussian, making use of the complex error function.
		RooFitCore provides two algorithms for the evaluation of the complex
		error function (the default CERNlib C335 algorithm, and a faster,
		look-up-table based method). By default, RooVoigtian employs the
		default (CERNlib) algorithm. Select the faster algorithm either in
		the constructor, or with the selectFastAlgorithm() method
	*/
	// --- Signal Parameters
	RooRealVar gaussMean("mean", "m_{Z^{0}}", 91000., XFITMIN, XFITMAX);
	RooRealVar gaussSigma("sigma", "Resolution", 3000., 100., 10000.);
	RooRealVar breitWignerMean("mean", "m_{Z^{0}}", 91000., XFITMIN, XFITMAX);
	RooRealVar breitWignerGamma("gamma", "#Gamma", 2495.2);
	////////////////////////////////////////////////////////
	// fix the BW width parameter to the known value (PDG)
	breitWignerGamma.setConstant(kTRUE);////////////////////
	////////////////////////////////////////////////////////
	
	
	
	// --- Build the convolution of the Gauss and Breit-Wigner PDFs ---
	RooVoigtian BreitGaussSignal("BreitGauss", "Breit-Wigner #otimes Gauss PDF", imass, breitWignerMean, breitWignerGamma, gaussSigma);
	

	
	
	// --- BACKGROUND
	//RooExponential(const char* name, const char* title, RooAbsReal& _x, RooAbsReal& _c)
	// --- Background Parameters
	RooRealVar expMeasure("exp", "Exponent measure", -1.e-6, -1.e-4, -1.e-8);
	//RooRealVar expConstant("expConstant", "Exponent constant", 2., 1.e-3, 100.);
	// --- Build the background exponential PDFs ---
	RooExponential ExponentBG("ExponentBG", "Exponential BG", imass, expMeasure);
	//RooExtendedExponent ExponentBG("ExponentBG", "Exponential BG", imass, expMeasure, expConstant);
	

	
	

	// shape: model(x) = nsig/(nsig+nbkg)*sig(x) + nbkg/(nsig+nbkg)*bkg(x) 
	// norm:  Nexpect  = nsig + nbkg
	// Combined: Nexpect*model(x) = nsig*sig(*x) + nbkg*bkg(x)
	RooAddPdf model("model", "BreitGaussSignal #oplus ExponentBG", RooArgList(BreitGaussSignal,ExponentBG), RooArgList(nsig,nbkg));
	
	// redefine the generic PDFs in the fit range
	//RooExtendPdf sigE("sigE", "signalExtended",     BreitGaussSignal, nsig, "fitRange");
	//RooExtendPdf bkgE("bkgE", "backgroundExtended", ExponentBG,       nbkg, "fitRange");
	//RooAddPdf model("model", "BreitGaussSignal #oplus ExponentBG", RooArgList(sigE,bkgE));
	

	
	
	// model(x) = fsig*sig(x) + (1-fsig)*bkg(x)
	//RooRealVar fsig("fsig","signal fraction",0.9,0.,1.);
	//RooAddPdf model("model", "BreitGaussSignal #oplus ExponentBG", RooArgList(BreitGaussSignal,ExponentBG), fsig);
	
	// --- get the data set ---
	RooDataSet* data = new RooDataSet("data", "data", m_imassTree, imass);
	//RooRealVar boundaries("boundaries","boundaries",XFITMIN,XFITMAX);
	//RooDataSet* data = new RooDataSet("data", "data", m_imassTree, RooArgSet(imass, boundaries));
	

	
	
	// --- Perform extended ML fit of composite PDF to data ---
	model.fitTo(*data, Range("fitRange"), Extended(kTRUE));
	

	
	
	// --- Perform a regular ML fit of composite PFD to data
	//model.fitTo(*data, Range("fitRange"));
		
	// --- Plot toy data and composite PDF overlaid ---
	TCanvas* canv_imass_roofit = new TCanvas("imass_roofit","imass_roofit",602,400);
	canv_imass_roofit->Draw();
	canv_imass_roofit->cd();
	RooPlot* frame = imass.frame();
	RooBinning b((int)h->GetNbinsX(),XFULLMIN,XFULLMAX,"imassBins");
	data->plotOn(frame, Binning(b), XErrorSize(0) /*, Invisible()*/);
	model.plotOn(frame,Range("fitRange"));
	model.plotOn(frame,Range("fitRange"),Components(BreitGaussSignal),LineColor(kRed),LineWidth(1));
	model.plotOn(frame,Range("fitRange"),Components(ExponentBG),LineStyle(kDashed),LineWidth(1));
	model.paramOn(frame,data,"",1,"NELU", 0.15, 0.48, 0.922);
	
	
	double leg_x1 = 0.705;
	double leg_x2 = 0.919;
	double leg_y1 = 0.336;
	double leg_y2 = 0.922;
	TLegend* leg_roofit = new TLegend(leg_x1, leg_y1*2., leg_x2, leg_y2);
	TGraph* tgraph_dat = new TGraph();
	TLine* tline_sig = new TLine();
	tline_sig->SetLineWidth(1); tline_sig->SetLineColor(kRed); tline_sig->SetLineStyle(1);
	TLine* tline_bg = new TLine();
	tline_bg->SetLineWidth(1); tline_bg->SetLineColor(kBlue); tline_bg->SetLineStyle(kDashed);
	TLine* tline_fit = new TLine();
	tline_fit->SetLineWidth(2); tline_fit->SetLineColor(kBlue); tline_fit->SetLineStyle(1);
	leg_roofit->AddEntry( tgraph_dat, "Data", "lep");
	leg_roofit->AddEntry( tline_sig, "S = BW #otimes Gauss", "L");
	leg_roofit->AddEntry( tline_bg, "BG = Exp", "L");
	leg_roofit->AddEntry( tline_fit, "ML fit = S #oplus BG", "L");
	frame->addObject(leg_roofit);
	
	frame->SetMinimum(1.e-5);
	
	frame->Draw();
	canv_imass_roofit->Update();
	canv_imass_roofit->Write();
	
	
	/*
	the error bars for entries at low statistics are not 
	symmetric: RooFit by default shows the 68% confidence interval for Poisson statistics (To be more precise
	the intervals shown are ‘classic central ’ intervals as described in Table I of Cousins, Am. J. Phys. 63, 398 (1995)),
	which are  generally asymmetric, especially at low statistics, and a more accurate reflection of the statistical 
	uncertainty in each bin if the histogram contents arose from a Poisson process. You can choose to have the usual sqrt(N)
	error shown by adding DataError(RooAbsData::SumW2) to the  data.plotOn() line. This option only affects the visualization
	of the dataset.
	*/
	
	cout << "breitWignerMean = " << breitWignerMean.getVal() << " +- " << breitWignerMean.getError() << endl;
	cout << "breitWignerGamma = " << breitWignerGamma.getVal() << " +- " << breitWignerGamma.getError() << endl;
	cout << "gaussSigma = " << gaussSigma.getVal() << " +- " << gaussSigma.getError() << endl;
	cout << "expMeasure = " << expMeasure.getVal() << " +- " << expMeasure.getError() << endl;
	//cout << "expConstant = " << expConstant.getVal() << " +- " << expConstant.getError() << endl;
	
	// For extended ML fit:
	cout << "nsig = " << nsig.getVal() << " +- " << nsig.getError() << endl;
	cout << "nbkg = " << nbkg.getVal() << " +- " << nbkg.getError() << endl;
	yields[0] = nsig.getVal();
    yields[1] = nbkg.getVal();
	cout << "\nyields[0] = " <<  yields[0] << " +- " << nsig.getError() << endl;
	cout << "yields[1] = " <<  yields[1] << " +- " << nbkg.getError() << "\n" << endl;
	
	
	// For regular ML fit
	//double fs = fsig.getVal();
	//double fb = 1.-fsig.getVal();
	//yields[0] = fs*eventsInFitRange;
    //yields[1] = fb*eventsInFitRange;
	//cout << "\nyields[0] = " <<  yields[0] << " +- " << fs*fb*eventsInFitRange << endl;
	//cout << "yields[1] = " <<  yields[1]   << " +- " << fs*fb*eventsInFitRange << "\n" << endl;
	
	RooArgSet* params = model.getVariables();
	params->Print("v");
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
}

#endif

