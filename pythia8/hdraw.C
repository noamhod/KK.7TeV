/////////////////////////////////////////////////////////////
// USAGE ////////////////////////////////////////////////////
// broot hstack.C++ --ftype=noPUrw --htype=Mass --istru=0 ///
/////////////////////////////////////////////////////////////


#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/histos.h"
#include "../include/units.h"
#include "../src/AtlasStyle.C"

#define VERBOSEARGS

void atlasstyle()
{
	gROOT->Reset();
	gROOT->ForceStyle();
	gROOT->LoadMacro("../src/AtlasStyle.C");
	SetAtlasStyle();
}

void hdraw()
{
	msglvl[DBG] = SILENT; // SILENT
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	atlasstyle();
	
	_INFO("USAGE: broot hdraw.C++ --mtype=1000 --htype=Mass --channel=mumu --runNumber=4");
	
	for(int i=0 ; i<gApplication->Argc() ; i++)
	{
		#ifdef VERBOSEARGS
		printf("Arg  %d:  %s\n",i,gApplication->Argv(i));
		#endif
	}
	if(gApplication->Argc()>10) _FATAL("gApplication->Argc()="+_s(gApplication->Argc()));
	TString mtype     = "";
	TString htype     = "";
	TString channel   = "";
	TString runnumber = "";
	for(int i=0 ; i<gApplication->Argc() ; i++)
	{	
		if(((TString)gApplication->Argv(i)).Contains("--mtype="))     mtype     = ((TString)gApplication->Argv(i)).ReplaceAll("--mtype=","");
		if(((TString)gApplication->Argv(i)).Contains("--htype="))     htype     = ((TString)gApplication->Argv(i)).ReplaceAll("--htype=","");
		if(((TString)gApplication->Argv(i)).Contains("--channel="))   channel   = ((TString)gApplication->Argv(i)).ReplaceAll("--channel=","");
		if(((TString)gApplication->Argv(i)).Contains("--runNumber=")) runnumber = ((TString)gApplication->Argv(i)).ReplaceAll("--runNumber=","");
	}
	_INFO("mtype="+(string)mtype);
	_INFO("htype="+(string)htype);
	_INFO("channel="+(string)channel);
	_INFO("runnumber="+(string)runnumber);

	
	// flags
	bool doKK   = false;
	bool doLogx = (htype.Contains("Mass") || htype.Contains("AFB") || htype.Contains("pT")) ? true : false;
	bool doLogy = (htype.Contains("Mass") || htype.Contains("pT") || htype.Contains("QT")) ? true : false;
	doLogy      = (htype.Contains("AFB")  || htype.Contains("CosTheta")) ? false : doLogy;
	
	_DEBUG("");
	
	vector<TString> vNames;
	vNames.push_back( "DY_"+channel );
	vNames.push_back( "ZP_ssm_mBSM"+mtype+"_"+channel );
	vNames.push_back( "ZP_psi_mBSM"+mtype+"_"+channel );
	vNames.push_back( "ZP_chi_mBSM"+mtype+"_"+channel );
	vNames.push_back( "ZP_eta_mBSM"+mtype+"_"+channel );
	if(doKK) vNames.push_back( "KK_mBSM"+mtype+"_"+channel );
	
	_DEBUG("");
	
	vector<TString> vLabels;
	for(unsigned int n=0 ; n<vNames.size() ; n++)
	{
		if(vNames[n].Contains("DY"))  vLabels.push_back( " #gamma/Z" );
		if(vNames[n].Contains("ssm")) vLabels.push_back( " Z'_{SSM}     ("+mtype+" GeV)" );
		if(vNames[n].Contains("psi")) vLabels.push_back( " Z'_{#psi}        ("+mtype+" GeV)" );
		if(vNames[n].Contains("chi")) vLabels.push_back( " Z'_{#chi}        ("+mtype+" GeV)" );
		if(vNames[n].Contains("eta")) vLabels.push_back( " Z'_{#eta}        ("+mtype+" GeV)" );
		if(vNames[n].Contains("KK"))  vLabels.push_back( " #gamma_{KK}/Z_{KK} ("+mtype+" GeV)" );
	}
	
	_DEBUG("");
	
	vector<Color_t> vColors;
	for(unsigned int n=0 ; n<vNames.size() ; n++)
	{
		if(vNames[n].Contains("DY"))  vColors.push_back( kAzure-9 );
		if(vNames[n].Contains("ssm")) vColors.push_back( kRed+2 );
		if(vNames[n].Contains("psi")) vColors.push_back( kOrange-3 );
		if(vNames[n].Contains("chi")) vColors.push_back( kMagenta-7 );
		if(vNames[n].Contains("eta")) vColors.push_back( kBlue );
		if(vNames[n].Contains("KK"))  vColors.push_back( kGreen+2 );
	}
	
	_DEBUG("");
	
	vector<Int_t> vLinestyles;
	for(unsigned int n=0 ; n<vNames.size() ; n++)
	{
		if(vNames[n].Contains("DY"))  vLinestyles.push_back( 1 );
		if(vNames[n].Contains("ssm")) vLinestyles.push_back( 1 );
		if(vNames[n].Contains("psi")) vLinestyles.push_back( 1 );
		if(vNames[n].Contains("chi")) vLinestyles.push_back( 2 );
		if(vNames[n].Contains("eta")) vLinestyles.push_back( 3 );
		if(vNames[n].Contains("KK"))  vLinestyles.push_back( 1 );
	}
	
	_DEBUG("");
	
	vector<TFile*> vFiles;
	for(unsigned int n=0 ; n<vNames.size() ; n++)
	{
		TString fname = "plots/"+vNames[n]+"_"+runnumber+".root";
		vFiles.push_back( new TFile(fname,"READ") );
	}
	
	_DEBUG("");
	
	vector<TH1D*> vHists;
	vector<TH1D*> vHistsLin;
	for(unsigned int n=0 ; n<vNames.size() ; n++)
	{
		vFiles[n]->cd();
		TString hname = "h"+htype+vNames[n];
		vHists.push_back( (TH1D*)vFiles[n]->Get(hname)->Clone() );
		vHists[n]->SetLineColor(vColors[n]);
		vHists[n]->SetLineStyle(vLinestyles[n]);
		if(doLogx)
		{
			vHists[n]->GetXaxis()->SetMoreLogLabels(1);
			vHists[n]->GetXaxis()->SetNoExponent();
		}
		if(vNames[n].Contains("DY"))
		{
			if(!htype.Contains("AFB")) vHists[n]->SetFillColor(vColors[n]);
			// if(htype.Contains("AFB_QRK")) vHists[n]->SetFillColor(vColors[n]);
		}
		if(htype=="Mass")
		{
			hname = "h"+htype+"Linear"+vNames[n];
			vHistsLin.push_back( (TH1D*)vFiles[n]->Get(hname)->Clone() );
			vHistsLin[n]->SetLineColor(vColors[n]);
			vHistsLin[n]->SetLineStyle(vLinestyles[n]);
		}
	}
	
	_DEBUG("");
	
	Double_t legxmin = 0.69;
	Double_t legxmax = 0.79;
	Double_t legymin = (!htype.Contains("AFB")) ? 0.70 : 0.20;
	Double_t legymax = (!htype.Contains("AFB")) ? 0.94 : 0.44;
	TLegend* leg = new TLegend(legxmin,legymin,legxmax,legymax);
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextSize(0.035);
	for(unsigned int n=0 ; n<vNames.size() ; n++)
	{
		if(vNames[n].Contains("DY")) leg->AddEntry(vHists[n],vLabels[n],"f");
		else                         leg->AddEntry(vHists[n],vLabels[n],"F");
	}
	
	_DEBUG("");
	
	// text
	TLatex *t = new TLatex();
	t->SetNDC(1);
	t->SetTextAlign(13);
	t->SetTextSize(0.05);
	t->SetTextColor(kBlack);
	
	_DEBUG("");
	
	// draw !
	TCanvas* c = new TCanvas("Canvas","Canvas",10,10,800,600); 
	c->SetTicks(1,1);
	if(doLogx) c->SetLogx();
	if(doLogy) c->SetLogy();
	c->cd();
	c->Draw();
	for(unsigned int n=0 ; n<vNames.size() ; n++)
	{
		if(n==0) vHists[n]->Draw("hist");
		else     vHists[n]->Draw("hist SAMES");
	}
	leg->Draw("SAMES");
	TString generator = "#scale[1.17]{P}#scale[1]{YTHIA8} #scale[0.9]{(+MRSTMCal)}";
	TString ppcme     = "#it{pp} collisions at #sqrt{s}=7 TeV";
	TString lumilabel = "Luminosity(truth) ~ "+(TString)_s(5)+" fb^{-1}";
	TString afblabel  = "";
	if(htype.Contains("AFB_QRK")) afblabel = "A_{fb} of proper cos#theta*";
	if(htype.Contains("AFB_HE"))  afblabel = "Uncorrected A_{fb} of cos#theta_{#beta}*";
	if(htype.Contains("AFB_CS"))  afblabel = "Uncorrected A_{fb} of Collins-Soper";
	t->DrawLatex(0.20,0.36,generator);
	t->DrawLatex(0.20,0.30,ppcme);
	if(htype.Contains("AFB")) t->DrawLatex(0.20,0.24,afblabel);
	else                      t->DrawLatex(0.20,0.24,lumilabel);
	
	c->Update();
	
	if(htype.Contains("AFB"))
	{
		TLine* line = new TLine(vHists[0]->GetXaxis()->GetXmax(),0.,vHists[0]->GetXaxis()->GetXmin(),0.);
		line->Draw("SAMES");
	}
	
	if(htype=="Mass")
	{
		// TPad *subpad = new TPad("subpad","",0.58,0.17,0.83,0.41);
		Double_t padymin = (doKK) ? 0.37 : 0.38;
		Double_t padymax = (doKK) ? 0.64 : 0.66;
		TPad *subpad = new TPad("subpad","",0.20,padymin,0.50,padymax);
		subpad->SetLogy();
		subpad->Draw();
		subpad->cd();
		subpad->DrawFrame(0.4,6,0.8,11);
		Double_t max = 0.;
		for(unsigned int n=0 ; n<vNames.size() ; n++)
		{
			// if(!doKK) continue;
			max = (vHistsLin[n]->GetMaximum()>max) ? vHistsLin[n]->GetMaximum() : max;
		}
		for(unsigned int n=0 ; n<vNames.size() ; n++)
		{
			// if(!doKK) continue;
			vHistsLin[n]->SetMaximum(2*max);
			if(n==0) vHistsLin[n]->Draw("hist");
			else     vHistsLin[n]->Draw("hist SAMES");
		}
		
		c->cd();
	}
	c->Update();
	c->RedrawAxis();
	TString name = "h"+htype+"All_mBSM"+mtype+"_"+channel;
	saveas(c,"plots/"+name);
}
