#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/fkinematics.h"
#include "../include/units.h"
#include "../include/couplings.h"
#include "../include/width.h"
#include "../include/helicity.h"
#include "../include/kFactors.h"

using namespace couplings;
using namespace width;
using namespace helicity;
using namespace kFactors;

#define BosonPtReweightingTool_cxx
#include "BosonPtReweightingTool.C"
BosonPtReweightingTool* ZpTrw = new BosonPtReweightingTool("PythiaMC11",true);

///////////////////////////////////////
// selectors //////////////////////////
///////////////////////////////////////
bool doData            = true;
bool do33st            = true;
bool do32st            = false;
bool doSmearing        = true;     // false is simply the old selection (before 3+3 / 3+2) -> should not be used !
bool doTemplates       = false;    // must be true if doFullKKtemplates is true or if doFullZPtemplates is true
bool doQCD             = true;     // must be "false" if doIsolationStudy is "true"
bool doIsolationStudy  = false;    // must be "false" if doQCD is true
bool doIsolation       = false;    // should be true for the histogram of the null-isolation-cut only !!!
bool doWjets           = true;     // no need to rename the output files
bool doScale2Zpeak     = true;
bool doDYtautau        = true;     // no need to rename the output files
bool fastDYmumu        = false;
bool largeDYmumu       = true;
bool doFullKKtemplates = false;    // will not change anything if doTemplates is "false"
bool doFullZPtemplates = false;    // will not change anything if doTemplates is "false"
bool dopileup          = true;
bool doEWkfactor       = true;
bool doEWkfactorSig    = false;
bool doQCDkfactor      = true;
bool doZpT             = true;
bool doCouplingsScale  = false;
bool doRemoveHighMass  = false;
void matchFlags()
{
	doQCD = !doIsolationStudy;
	do32st  = !do33st;
	if(!doTemplates)
	{
		doFullKKtemplates = false;
		doFullZPtemplates = false;
	}
}
TString fileNmaeSuffix()
{
	TString name = "";
	if(!doData)           name += "_noData";
	if(!doTemplates)      name += "_noTmplts";
	if(!doQCD)            name += "_noQCD";
	if(!doScale2Zpeak)    name += "_noZpeak";
	if(fastDYmumu)        name += "_fastDY";
	if(!largeDYmumu)      name += "_smallDY";
	if(!dopileup)         name += "_noPUrw";
	if(!doEWkfactor)      name += "_noEWkF";
	if(!doEWkfactorSig)   name += "_noEWkFsig";
	if(!doQCDkfactor)     name += "_noQCDkF";
	if(!doZpT)            name += "_noZpTrw";
	if(!doCouplingsScale) name += "_noCoupScale";
	if(!doRemoveHighMass) name += "_noHighMass";
	if(doIsolation)       name += "_noIso";
	if(doIsolationStudy)  name += "_isoStudy";
	if(doFullZPtemplates) name += "_templateZP";
	if(doFullKKtemplates) name += "_templateKK";
	return name;
}
///////////////////////////////////////

// other parameters
TString ntupledir = "";
TString ntupledir_regular     = "/data/hod/2011/NTUPLE";
TString ntupledir_noisolation = "/data/hod/2011/NTUPLE/noisolation";
// TString ntupledir_no2munoiso  = "/data/hod/2011/NTUPLE/no2munoiso";

Int_t printmod    = 5000;
Bool_t dolog      = true;

double mZprimeMin = 500.;
double mZprimeMax = 2000.;
double dMZprime   = 250.;
	
double mGmmMin = 1750.;
double mGmmMax = 2250.;
double dMGmm   = 250.;

double mKKmmMin = 130.;
double mKKmmMax = 3050.;
double dMKKmm   = 40.;

double maxKKwgt = 0.;
double maxZPwgt = 0.;

float zpeak_ratio_with_pileup = 1.;
float zpeak_ratio_no_pileup   = 1.;

float nMCall70to110          = 0;
float nMCall70to110_nopileup = 0;
float nData70to110           = 0;

float event_weight = 1.;
float event_weight_nopileup = 1.;
float event_weight_signals = 1.;
float event_weight_backgrounds = 1.;
double ZpTweight = 1.;
double kFQCD_NNLOvLOss = 1.;
double kFEW_NNLOvLOs   = 1.;

int nMaxBGs = 0;

TFile* file;
TTree* tree;
TString fName;
TString tName;
TPaveText* pvtxt_lumi;
TPaveText* pvtxt_atlas;
TLegend*   leg;
TLegend*   leg_template;
TText* txt;
TMapTSP2TCNV  cnvMap;
TMapTSP2TOBJ  oMap;
TMapTSP2TH1   h1Map;
TMapTSP2TH2   h2Map;
TMapSP2TGraph grMap;
TMapTSP2TLINE linMap;
TMapTSP2TTREE treMap;
TMapTSTS      pathMap;
TMapTSd       flatLumiWgtMap;
TMapTSd       mcNeventsMap;
TMapTSd       mcSigmaMap;
TMapTSvf      mcPeriodsNevtsMap;
TMapdi        pTtoIndexMap;

TMapTS2GRPX grpx;
TMapiTS     grpx_ordered;

TLorentzVector* tlva   = new TLorentzVector;
TLorentzVector* tlvb   = new TLorentzVector;
TLorentzVector* tlvtmp = new TLorentzVector;
TVector3*       tv3a   = new TVector3;
TVector3*       tv3b   = new TVector3;
TVector3*       tv3mu  = new TVector3;

TLorentzVector* tlvmutrua = new TLorentzVector;
TLorentzVector* tlvmutrub = new TLorentzVector;
TLorentzVector* tlvmureca = new TLorentzVector;
TLorentzVector* tlvmurecb = new TLorentzVector;
TLorentzVector* tlvqa  = new TLorentzVector;
TLorentzVector* tlvqb  = new TLorentzVector;

TLorentzVector* tlvmutruaBoosted = new TLorentzVector;
TLorentzVector* tlvmutrubBoosted = new TLorentzVector;
TLorentzVector* tlvmurecaBoosted = new TLorentzVector;
TLorentzVector* tlvmurecbBoosted = new TLorentzVector;
TLorentzVector* tlvqaBoosted  = new TLorentzVector;
TLorentzVector* tlvqbBoosted  = new TLorentzVector;

TVector3*       tv3mutrua = new TVector3;
TVector3*       tv3mutrub = new TVector3;
TVector3*       tv3mureca = new TVector3;
TVector3*       tv3murecb = new TVector3;
TVector3*       tv3qa  = new TVector3;
TVector3*       tv3qb  = new TVector3;
TVector3*       tv3q   = new TVector3;

TVector3*       tv3mutruaBoosted = new TVector3;
TVector3*       tv3mutrubBoosted = new TVector3;
TVector3*       tv3murecaBoosted = new TVector3;
TVector3*       tv3murecbBoosted = new TVector3;
TVector3*       tv3qaBoosted  = new TVector3;
TVector3*       tv3qbBoosted  = new TVector3;


/////////////  MC  /////////////
float all_actualIntPerXing;
float all_averageIntPerXing;
unsigned int all_mc_channel_number;
unsigned int all_mc_event_number;
double all_mc_event_weight;

int   all_RunNumber;
float all_pileup_weight;
float all_intime_pileup_weight;
float all_outoftime_pileup_weight;
float all_lumi_pileup_weight;
float all_EW_kfactor_weight;
float all_QCD_kfactor_weight;
float all_mcevent_weight;
float all_total_weight;
unsigned int all_randomized_decision;

bool truth_all_isValid;
vector<float>* truth_all_mc_pt;
vector<float>* truth_all_mc_m;
vector<float>* truth_all_mc_eta;
vector<float>* truth_all_mc_phi;
vector<int>*   truth_all_mc_status;
vector<int>*   truth_all_mc_barcode;
vector<int>*   truth_all_mc_pdgId;
vector<float>* truth_all_mc_charge;
float truth_all_Mhat;
float truth_all_CosThetaCS;
float truth_all_CosThetaHE;
float truth_all_ySystem;
float truth_all_QT;

vector<float>* truth_all_partons_mc_pt;
vector<float>* truth_all_partons_mc_m;
vector<float>* truth_all_partons_mc_eta;
vector<float>* truth_all_partons_mc_phi;
vector<int>*   truth_all_partons_mc_status;
vector<int>*   truth_all_partons_mc_barcode;
vector<int>*   truth_all_partons_mc_pdgId;
vector<float>* truth_all_partons_mc_charge;

vector<double>* truth_all_vKKwgt;
vector<double>* truth_all_vZPwgt;
vector<double>* truth_all_vBSMmass;

bool recon_all_isValid;
int recon_all_vxp_n;
vector<float>* recon_all_E;
vector<float>* recon_all_pt;
vector<float>* recon_all_m;
vector<float>* recon_all_eta;
vector<float>* recon_all_phi;
vector<float>* recon_all_px;
vector<float>* recon_all_py;
vector<float>* recon_all_pz;
vector<float>* recon_all_charge;
vector<float>* recon_all_y;
vector<int>*   recon_all_id;
vector<float>* recon_all_theta;

vector<float>* recon_all_ptcone20;
vector<float>* recon_all_ptcone30;
vector<float>* recon_all_ptcone40;
vector<float>* recon_all_etcone20;
vector<float>* recon_all_etcone30;
vector<float>* recon_all_etcone40;
vector<float>* recon_all_nucone20;
vector<float>* recon_all_nucone30;
vector<float>* recon_all_nucone40;
vector<unsigned short>* recon_all_allauthor;
vector<int>*   recon_all_author;
vector<float>* recon_all_beta;
vector<float>* recon_all_isMuonLikelihood;
vector<float>* recon_all_matchchi2;
vector<int>*   recon_all_matchndof;

float recon_all_Mhat;
float recon_all_CosThetaCS;
float recon_all_CosThetaHE;
float recon_all_ySystem;
float recon_all_QT;
////////////////////////////////

///////////// data /////////////
float actualIntPerXing;
float averageIntPerXing;
unsigned int mc_channel_number;
unsigned int mc_event_number;
double mc_event_weight;

float pileup_weight;
float EW_kfactor_weight;
float QCD_kfactor_weight;
float mcevent_weight;

int vxp_n;
vector<float>* E;
vector<float>* pt;
vector<float>* m;
vector<float>* eta;
vector<float>* phi;
vector<float>* px;
vector<float>* py;
vector<float>* pz;
vector<float>* charge;
vector<float>* me_d0;
vector<float>* me_z0;
vector<float>* me_phi;
vector<float>* me_theta;
vector<float>* me_qoverp;
vector<float>* ie_d0;
vector<float>* ie_z0;
vector<float>* ie_phi;
vector<float>* ie_theta;
vector<float>* ie_qoverp;
vector<unsigned short>* allauthor;
vector<int>* author;
vector<float>* beta;
vector<float>* isMuonLikelihood;
vector<float>* matchchi2;
vector<int>* matchndof;
vector<float>* etcone20;
vector<float>* etcone30;
vector<float>* etcone40;
vector<float>* nucone20;
vector<float>* nucone30;
vector<float>* nucone40;
vector<float>* ptcone20;
vector<float>* ptcone30;
vector<float>* ptcone40;
float Mhat;
float CosThetaCS;
float CosThetaHE;
float Ysystem;
float Q_T;
float CosThetaDimu;
float ipTDiff;
float EtaSum;
////////////////////////////////


///////////// admin /////////////
void graphics(TH1* th1,
			  Color_t fillcolor=-1, Int_t fillstyle=-1,
			  Color_t linecolor=-1, Int_t linestyle=-1, Width_t linewidth=-1,
			  Color_t mrkrcolor=-1, Int_t mrkrstyle=-1, Float_t mrkrsize=-1,
			  Bool_t moreLogLabels=true, Bool_t noexponent=true,
			  TString title="", TString xtitle="", TString ytitle="")
{
	_DEBUG("graphics");
	
	if(mrkrcolor>0) th1->SetMarkerColor(mrkrcolor);
	if(mrkrstyle>0) th1->SetMarkerStyle(mrkrstyle);
	if(mrkrsize>0)  th1->SetMarkerSize(mrkrsize);
	
	if(fillcolor>0) th1->SetFillColor(fillcolor);
	if(fillstyle>0) th1->SetFillStyle(fillstyle);
	
	if(linecolor>0) th1->SetLineColor(linecolor);
	if(linestyle>0) th1->SetLineStyle(linestyle);
	if(linewidth>0) th1->SetLineWidth(linewidth);
	
	if(moreLogLabels) th1->GetXaxis()->SetMoreLogLabels(); 
	if(noexponent)    th1->GetXaxis()->SetNoExponent(); 
	
	if(title!="")  th1->SetTitle(title);
	if(xtitle!="") th1->SetXTitle(xtitle);
	if(ytitle!="") th1->SetYTitle(ytitle);
}

void text()
{
	_DEBUG("text");

	pvtxt_atlas = new TPaveText(0.4032663,0.75,0.5678392,0.85,"brNDC"); // 0.2110553,0.7097902,0.3756281,0.8041958 -> for 2d
	//pvtxt_atlas->SetFillColor(0);
	pvtxt_atlas->SetFillStyle(4000); //will be transparent
	pvtxt_atlas->SetFillColor(0);
	pvtxt_atlas->SetTextFont(42);
	txt = pvtxt_atlas->AddText("#bf{#splitline{#it{ATLAS}}{#scale[0.42]{work in progress}}}");
	
	pvtxt_lumi = new TPaveText(0.4032663,0.63,0.5678392,0.738,"brNDC"); // 0.2110553,0.5926573,0.3756281,0.6993007 -> for 2d
	//pvtxt_lumi->SetFillColor(kWhite);
	pvtxt_lumi->SetFillStyle(4000); //will be transparent
	pvtxt_lumi->SetFillColor(0);
	TString sLumi = (TString)_s(luminosity,2);
	txt = pvtxt_lumi->AddText( "#intLdt~"+ sLumi +" fb^{-1}" );
	
	leg = new TLegend(0.6627517,0.60,0.7919463,0.87,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->AddEntry(h1Map["hMassData"],"Data","lep");
	for(TMapiTS::iterator it=grpx_ordered.begin() ; it!=grpx_ordered.end() ; ++it)
	{
		int order    = it->first;
		TString name = it->second;
		if(order>=nMaxBGs)                  continue; // only BGs !
		if(name=="DYtautau")                continue; // DYtautau is part of DYmumu
		if(name=="QCD" && doIsolationStudy) continue; // the QCD is taken from jjmu15X in the isolation study
		leg->AddEntry(h1Map["hMass"+name],grpx[name]->label,"f");
	}
}

TString getTemplateName(TString tsZPname, TString newName="")
{
	_DEBUG("getTemplateName");
	
	TString name = tsZPname;
	if(newName=="KK") name.ReplaceAll("Zprime_SSM",10,"KK",2);
	name.Append("_template");
	return name;
}

TString getTemplateBareTitle(TString tsZPname)
{
	_DEBUG("getTemplateBareTitle");
	
	TString name = tsZPname;
	name.ReplaceAll("Zprime_SSM",10,"",0);
	return name;
}

TString getTemplateBareTitlePythia8(TString tsZPname)
{
	_DEBUG("getTemplateBareTitle");
	
	TString name = "";
	if(tsZPname.Contains("Zprime")) name = "Z'_{SSM} 2000 GeV Pythia8 ";
	else                            name = "#gamma_{KK}/Z_{KK} GeV Pythia8 ";
	return name;
}

void templateText(TString tsMCname, bool isTruth, Bool_t isTmplate=false)
{
	_DEBUG("templateText");
	
	if(leg_template==NULL)
	{
		leg_template = new TLegend(0.57,0.70,0.83,0.85,NULL,"brNDC");
		leg_template->SetFillStyle(4000); //will be transparent
		leg_template->SetFillColor(0);
		leg_template->SetTextFont(42);
	}
	else leg_template->Clear();
	
	TString ZPname         = tsMCname;
	TString KKtemplateName = getTemplateName(tsMCname,"KK");
	TString ZPtemplateName = getTemplateName(tsMCname);
	
	TString legTitle = "";
	
	legTitle = "DY ";
	legTitle += (isTruth)?"tru":"rec";
	leg_template->AddEntry(h1Map["hMassDYmumu"],legTitle,"f");
	
	if(isTmplate)
	{
		TString massNmae = getTemplateBareTitle(tsMCname);
		legTitle = "Z'_{SSM} "+massNmae+" GeV Pythia6 ";
		legTitle += (isTruth)?"tru":"rec";
		leg_template->AddEntry(h1Map["hMass"+ZPname],legTitle,"f");         // doesn't matter if it is pT or mass truth sice they have the same graphic properties
		legTitle = "Z'_{SSM} "+massNmae+" GeV Template ";
		legTitle += (isTruth)?"tru":"rec";
		leg_template->AddEntry(h1Map["hMass"+ZPtemplateName],legTitle,"l"); // doesn't matter if it is pT or mass truth sice they have the same graphic properties
		legTitle = "#gamma_{KK}/Z_{KK} "+massNmae+" GeV Template ";
		legTitle += (isTruth)?"tru":"rec";
		leg_template->AddEntry(h1Map["hMass"+KKtemplateName],legTitle,"l"); // doesn't matter if it is pT or mass truth sice they have the same graphic properties
	}
	else
	{
		legTitle = getTemplateBareTitlePythia8(tsMCname);
		legTitle += (isTruth)?"tru":"rec";
		leg_template->AddEntry(h1Map["hMass"+tsMCname],legTitle,"f");
		if(tsMCname.Contains("Zprime"))
		{
			legTitle = "Z'_{SSM} 2000 GeV Template ";
			legTitle += (isTruth)?"tru":"rec";
			leg_template->AddEntry(h1Map["hMassZprime_SSM2000_template"],legTitle,"l");
		}
		else
		{
			legTitle = "#gamma_{KK}/Z_{KK} 2000 GeV Template ";
			legTitle += (isTruth)?"tru":"rec";
			leg_template->AddEntry(h1Map["hMassKK2000_template"],legTitle,"l");
		}
	}
}


void draw(TObject* tobj, TString newname="", TString drawopt="", Bool_t logx=!dolog, Bool_t logy=!dolog, Bool_t logz=!dolog)
{
	_DEBUG("draw");

	TString oName = (newname=="") ? (TString)tobj->GetName() : newname;
	TString cName = "c"+oName;
	cnvMap.insert( make_pair(oName, new TCanvas(cName,cName,600,400)) );
	if(logx) cnvMap[oName]->SetLogx();
	if(logy) cnvMap[oName]->SetLogy();
	if(logz) cnvMap[oName]->SetLogz();
	cnvMap[oName]->SetTicks(1,1);
	cnvMap[oName]->cd();
	tobj->Draw(drawopt);
	cnvMap[oName]->RedrawAxis();
	cnvMap[oName]->Update();
}

void drawratio(TH1* th1n, TH1* th1d, vector<TString>& vtsMCbgds, TString drawopt_n="", TString drawopt_d="", Bool_t logx=!dolog, Bool_t logy=!dolog)
{
	_DEBUG("drawratio");

	TString hName = (TString)th1n->GetName();
	hName = hName+"MCratio";
	TString cName = "c"+hName;
	
	cnvMap.insert( make_pair(hName, new TCanvas(cName,cName,600,550)) );
	
	cnvMap[hName]->Divide(1,2);
	TVirtualPad* tvp_hists = cnvMap[hName]->cd(1);
	TVirtualPad* tvp_ratio = cnvMap[hName]->cd(2);
	
	if(logx) tvp_ratio->SetLogx();
	if(logx) tvp_hists->SetLogx();
	if(logy) tvp_hists->SetLogy();
	
	tvp_hists->SetPad(0.00, 0.35, 1.00, 1.00);
	tvp_ratio->SetPad(0.00, 0.00, 1.00, 0.35);

	tvp_hists->SetBottomMargin(0.012);
	tvp_ratio->SetBottomMargin(0.20);
	tvp_ratio->SetTopMargin(0.012);
	
	tvp_hists->SetTicks(1,1);
	tvp_ratio->SetTicks(1,1);

	TString cloneName_n = th1n->GetName();
	TString cloneName_d = th1d->GetName();
	TH1D* th1n_tmp = (TH1D*)th1n->Clone(cloneName_n+"_th1n_tmp");
	TH1D* th1d_tmp = (TH1D*)th1d->Clone(cloneName_d+"_th1d_tmp");
	th1n_tmp->Sumw2();
	th1d_tmp->Sumw2();

	TH1D* hr = (TH1D*)th1n->Clone(hName);
	TString sXtitle = (TString)th1n->GetXaxis()->GetTitle();
	// TString sTitle = "#frac{Data}{#sum MC#times wgt};"+sXtitle+";Ratio";
	TString sTitle = ";"+sXtitle+";Data/sumMC";
	hr->SetTitle(sTitle);
	hr->Divide(th1n_tmp,th1d_tmp,1.,1.,"B");

	hr->GetXaxis()->SetLabelSize(0.075);
	hr->GetYaxis()->SetLabelSize(0.075);
	hr->GetXaxis()->SetTitleSize(0.075);
	hr->GetYaxis()->SetTitleSize(0.075);
	hr->SetTitleSize(0.075);
	hr->SetTitleSize(0.075);
	hr->GetYaxis()->SetTitleOffset(0.5);
	hr->SetMinimum(0.);
	hr->SetMaximum(+2.);
	
	if(logx) setlogx(hr);
	
	string name = (string)hName;
	if(name.find("Nvxp")!=string::npos)
	{
		ofstream fWeights("pileup.weights");
		for(Int_t b=1 ; b<=hr->GetNbinsX() ; b++) fWeights << "pu weight: Nvtx=" << b << " -> wgt=" << hr->GetBinContent(b) << " +- " << hr->GetBinError(b) << endl;
		fWeights.close();
	}
	
	TString lName = "l"+hName;
	linMap.insert( make_pair(lName, new TLine(hr->GetXaxis()->GetXmin(),1.,hr->GetXaxis()->GetXmax(),1.)) );

	tvp_hists->cd();
	for(int v=0 ; v<(int)vtsMCbgds.size() ; v++)
	{
		// th1d->Draw(drawopt_d);
		// th1n->Draw(drawopt_n+"SAMES");
		if(v==0) h1Map[vtsMCbgds[v]]->Draw(drawopt_d);
		else     h1Map[vtsMCbgds[v]]->Draw(drawopt_d+"SAMES");
	}
	th1n->Draw(drawopt_n+"SAMES");
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	leg->Draw("SAMES");
	cnvMap[hName]->Update();
	tvp_hists->RedrawAxis();

	tvp_ratio->cd();
	hr->Draw("epx0");
	linMap[lName]->Draw("SAMES");
	cnvMap[hName]->Update();
	tvp_ratio->RedrawAxis();
}

void drawon(TString existing_oName, TObject* tobj, TString drawopt="", Int_t padNumber=-1)
{
	_DEBUG("drawon");
	
	if(padNumber<1) { cnvMap[existing_oName]->cd(); }
	else            { cnvMap[existing_oName]->cd(padNumber); }
	
	if(drawopt=="") { tobj->Draw("SAMES"); }
	else            { tobj->Draw(drawopt+" SAMES"); }
	cnvMap[existing_oName]->RedrawAxis();
	cnvMap[existing_oName]->Update();
}

void drawtxton(TString existing_oName, bool is2d=false)
{
	_DEBUG("drawtxton");

	cnvMap[existing_oName]->cd();
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	if(!is2d) leg->Draw("SAMES");
}

void drawtemplatetxton(TString existing_oName)
{
	_DEBUG("drawtxton");

	cnvMap[existing_oName]->cd();
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	leg_template->DrawClone("SAMES");
}

void save(TString oDir)
{
	_DEBUG("save");

	_INFO("save all canvases");
	
	TString pdfName = oDir+"/mcdata_histograms";
	pdfName += fileNmaeSuffix();
	pdfName += ".pdf";
	
	TString pdfTempltaesName = oDir+"/mcdata_template_histograms";
	pdfTempltaesName += fileNmaeSuffix();
	pdfTempltaesName += ".pdf";
	
	unsigned int mapcount = 0;
	unsigned int mapsize  = cnvMap.size();
	for(TMapTSP2TCNV::iterator it=cnvMap.begin() ; it!=cnvMap.end() ; ++it)
	{
		mapcount++;
		TString pName = oDir+"/mcdata_"+it->first;
		pName += fileNmaeSuffix();
		it->second->SaveAs(pName+".png");
		it->second->SaveAs(pName+".eps");
		it->second->SaveAs(pName+".pdf");
		it->second->SaveAs(pName+".root");
		it->second->SaveAs(pName+".C");
		
		pName = pdfName;
		if(it==cnvMap.begin()) pName = pdfName+"(";
		if(mapcount==mapsize)  pName = pdfName+")";
		it->second->SaveAs(pName);
		
		if( ((it->first.Contains("m2000") || it->first.Contains("Zprime")) && (it->first.Contains("hMass") || it->first.Contains("hpTLeading"))) || it->first.Contains("_templates") )
		{
			pName = pdfTempltaesName;
			if(it==cnvMap.begin()) pName = pdfTempltaesName+"(";
			if(mapcount==mapsize)  pName = pdfTempltaesName+")";
			it->second->SaveAs(pName);
		}
	}
	
	_INFO("save all histograms (to a single .root file)");
	TString pName = oDir+"/mcdata_histograms";
	pName += fileNmaeSuffix();
	pName += ".root";
	TFile* f = new TFile(pName,"RECREATE");
	f->cd();
	for(TMapTSP2TH1::iterator it=h1Map.begin() ; it!=h1Map.end() ; ++it)
	{
		if(it->second!=NULL) it->second->Write();
		else _WARNING("This name -> ["+(string)it->first+"] is not in h1Map");
	}
	for(TMapTSP2TH2::iterator it=h2Map.begin() ; it!=h2Map.end() ; ++it)
	{
		if(it->second!=NULL) it->second->Write();
		else _WARNING("This name -> ["+(string)it->first+"] is not in h2Map");
	}
	f->Write();
	f->Close();
	delete f;
}

void clearMaps()
{
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		if(it->second) delete it->second; // the trees take a lot of memory, delete them.
	}
	
	treMap.clear();
	flatLumiWgtMap.clear();
	mcNeventsMap.clear();
	mcSigmaMap.clear();
	pathMap.clear();
}

void setMCtree(TString fPath, TString name, Double_t N, Double_t sigma)
{
	_DEBUG("setMCtree");
	
	file = new TFile(fPath,"READ");
	treMap.insert( make_pair(name, (TTree*)file->Get("truth/truth_tree")->Clone("")) );
	if(name.Contains("Pythia8")) _INFO((string)name+" -> N="+_s((int)treMap[name]->GetEntries()));
	flatLumiWgtMap.insert( make_pair(name, luminosity/(N/sigma)) );
	mcNeventsMap.insert( make_pair(name, N) );
	mcSigmaMap.insert( make_pair(name, sigma) );
	pathMap.insert( make_pair(name, fPath) );
}

void setDATAtree(TString name="Data")
{
	_DEBUG("setDATAtree");
	
	ntupledir = (!doIsolation)     ? ntupledir_regular    : ntupledir_noisolation;
	// ntupledir = (doIsolationStudy) ? ntupledir_no2munoiso : ntupledir;
	ntupledir = (doIsolationStudy) ? ntupledir_noisolation : ntupledir;

	if(name=="Data")     fName = ntupledir+"/analysisLocalControl";
	else if(name=="QCD") fName = ntupledir+"/analysisLocalControl_QCD";
	fName += (do33st && !do32st) ? "_33st"  : "";
	fName += (do32st && !do33st) ? "_32st"  : "";
	fName += (doIsolationStudy)  ? "_noIso" : "";
	fName += ".root";
	
	tName = "allCuts/allCuts_tree";
	file = new TFile(fName,"READ");
	tree = (TTree*)file->Get(tName);
}

int proccount(int& counter)
{
	counter = counter+1;
	return counter;
}

void samples()
{
	_DEBUG("samples");
	/*GRPX::GRPX(int o, TString l,
				 Color_t fc, Int_t fs,
				 Color_t lc, Int_t ls, Int_t lw,
				 Color_t mc, Int_t mst, Int_t mss,
				 )*/
	int counter = 0;
	grpx.insert( make_pair("DYmumu",   new GRPX(counter,"#gamma/Z",      kAzure+8,-1,   kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["DYmumu"]->order,"DYmumu") );
	grpx.insert( make_pair("Diboson",  new GRPX(proccount(counter),"Diboson",     kOrange+1,-1,  kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Diboson"]->order,"Diboson") );
	grpx.insert( make_pair("TTbar",    new GRPX(proccount(counter),"t#bar{t}",     kRed+1,-1,     kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["TTbar"]->order,"TTbar") );
	if(doDYtautau)
	{
		grpx.insert( make_pair("DYtautau", new GRPX(proccount(counter),"DY#tau#tau",  kRed-5,-1,     kBlack,1,1,  -1,-1,-1)));
		grpx_ordered.insert( make_pair(grpx["DYtautau"]->order,"DYtautau") );
	}
	if(doWjets)
	{
		grpx.insert( make_pair("W+jets", new GRPX(proccount(counter),"W+jets",     kGreen+1,-1,     kBlack,1,1,  -1,-1,-1)));
		grpx_ordered.insert( make_pair(grpx["W+jets"]->order,"W+jets") );
	}
	if(doQCD)
	{
		grpx.insert( make_pair("QCD", new GRPX(proccount(counter),"QCD",  kYellow-9,-1,     kBlack,1,1,  -1,-1,-1)));
		grpx_ordered.insert( make_pair(grpx["QCD"]->order,"QCD") );
	}
	if(doIsolationStudy)
	{
		grpx.insert( make_pair("jjmu15X", new GRPX(proccount(counter),"jjmu15X",  kYellow-9,-1,     kBlack,1,1,  -1,-1,-1)));
		grpx_ordered.insert( make_pair(grpx["jjmu15X"]->order,"jjmu15X") );
	}
	
	counter = 20;
	grpx.insert( make_pair("Data", new GRPX(counter,"Data",   -1,-1,  kBlack,1,2,  kBlack,20,0.8)));
	grpx_ordered.insert( make_pair(grpx["Data"]->order,"Data") );
	
	////////////////////////////
	// 1->19 are backgrounds ///
	// 20 is data //////////////
	nMaxBGs = 20; //////////////
	////////////////////////////
	
	counter = 100;
	grpx.insert( make_pair("Zprime_SSM500",  new GRPX(counter,"500 GeV Z'_{SSM}",  kAzure+0,-1,    kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Zprime_SSM500"]->order,"Zprime_SSM500") );
	grpx.insert( make_pair("Zprime_SSM750",  new GRPX(proccount(counter),"750 GeV Z'_{SSM}",  kAzure-2,-1,  kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Zprime_SSM750"]->order,"Zprime_SSM750") );
	grpx.insert( make_pair("Zprime_SSM1000",  new GRPX(proccount(counter),"1000 GeV Z'_{SSM}",  kAzure-2,-1,  kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Zprime_SSM1000"]->order,"Zprime_SSM1000") );
	grpx.insert( make_pair("Zprime_SSM1500",  new GRPX(proccount(counter),"1500 GeV Z'_{SSM}",  kAzure-2,-1,  kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Zprime_SSM1500"]->order,"Zprime_SSM1500") );
	grpx.insert( make_pair("Zprime_SSM1750",  new GRPX(proccount(counter),"1750 GeV Z'_{SSM}",  kAzure-3,-1,  kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Zprime_SSM1750"]->order,"Zprime_SSM1750") );
	grpx.insert( make_pair("Zprime_SSM2000",  new GRPX(proccount(counter),"2000 GeV Z'_{SSM}",  kAzure-4,-1,  kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Zprime_SSM2000"]->order,"Zprime_SSM2000") );
	
	/* counter = 200;
	grpx.insert( make_pair("Gmm_01_1750",  new GRPX(counter,"1750 GeV G*",  kViolet+1,-1,    kBlack,1,1,   -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Gmm_01_1750"]->order,"Gmm_01_1750") );
	grpx.insert( make_pair("Gmm_01_2000",  new GRPX(proccount(counter),"2000 GeV G*",  kViolet+6,-1,  kBlack,1,1,   -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Gmm_01_2000"]->order,"Gmm_01_2000") );
	grpx.insert( make_pair("Gmm_01_2250",  new GRPX(proccount(counter),"2250 GeV G*",  kViolet+10,-1,  kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Gmm_01_2250"]->order,"Gmm_01_2250") ); */
	
	counter = 300;
	grpx.insert( make_pair("Zprime_SSM_m2000",  new GRPX(counter,"2 TeV Z'_{SSM} with interference", kMagenta+1,-1,    kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Zprime_SSM_m2000"]->order,"Zprime_SSM_m2000") );
	grpx.insert( make_pair("ExtraDimsTEV_m2000",  new GRPX(proccount(counter),"2 TeV #gamma_{KK}/Z_{KK} with interference", kMagenta-1,-1,  kBlack,1,1,   -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["ExtraDimsTEV_m2000"]->order,"ExtraDimsTEV_m2000") );
	
	counter = 400;
	grpx.insert( make_pair("MCsum", new GRPX(counter,"#Sum MC",  -1,-1,  -1,-1,-1,  kRed,  20,0.8)));
	grpx_ordered.insert( make_pair(grpx["MCsum"]->order,"MCsum") );
}

void setMCtrees(TString tsMCname)
{
	_DEBUG("setMCtrees");
	
	////////////////
	clearMaps(); ///
	////////////////

	ntupledir = (!doIsolation)     ? ntupledir_regular    : ntupledir_noisolation;
	// ntupledir = (doIsolationStudy) ? ntupledir_no2munoiso : ntupledir;
	ntupledir = (doIsolationStudy) ? ntupledir_noisolation : ntupledir;
	
	TString sNMst = "";
	sNMst += (do33st && !do32st) ? "_33st" : "";
	sNMst += (do32st && !do33st) ? "_32st" : "";
	
	TString sSMR = "";
	sSMR += (doSmearing) ? "_smeared" : "";
	
	TString sISO = "";
	sISO += (doIsolationStudy) ? "_noIso" : "";
	
	////////////////////////////////////////////
	TString filesuffix = sNMst+sSMR+sISO; //////
	////////////////////////////////////////////
	
	if(tsMCname=="DYmumu")
	{
		if(!largeDYmumu)
		{
			if(fastDYmumu)
			{
				setMCtree(ntupledir+"/mcLocalControl_DYmumu_75M120"+filesuffix+".root", "mcLocalControl_DYmumu_75M120", 20000, 7.9862E-01*nb2fb);
				setMCtree(ntupledir+"/mcLocalControl_DYmumu_120M250"+filesuffix+".root", "mcLocalControl_DYmumu_120M250", 20000, 8.5275E-03*nb2fb);
			}
			else setMCtree(ntupledir+"/mcLocalControl_Zmumu"+filesuffix+".root", "mcLocalControl_Zmumu", 4878990, 8.3470E-01*nb2fb); // need to do a cut to keep events only up to 250 GeV
			
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_250M400"+filesuffix+".root", "mcLocalControl_DYmumu_250M400", 20000, 4.1075E-04*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_400M600"+filesuffix+".root", "mcLocalControl_DYmumu_400M600", 20000, 6.6459E-05*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_600M800"+filesuffix+".root", "mcLocalControl_DYmumu_600M800", 20000, 1.1002E-05*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_800M1000"+filesuffix+".root", "mcLocalControl_DYmumu_800M1000", 20000, 2.6516E-06*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_1000M1250"+filesuffix+".root", "mcLocalControl_DYmumu_1000M1250", 20000, 8.9229E-07*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_1250M1500"+filesuffix+".root", "mcLocalControl_DYmumu_1250M1500", 20000, 2.3957E-07*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_1500M1750"+filesuffix+".root", "mcLocalControl_DYmumu_1500M1750", 20000, 7.3439E-08*nb2fb);    // !!!!!!!!!!!
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_1750M2000"+filesuffix+".root", "mcLocalControl_DYmumu_1750M2000", 20000, 2.4614E-08*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_M2000"+filesuffix+".root", "mcLocalControl_DYmumu_M2000", 20000, 1.4001E-08*nb2fb);
		}
		else
		{
			if(fastDYmumu)
			{
				setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_75M120"+filesuffix+".root",  "mcLocalControl_Pythia6_DYmumu_75M120",  100000, 7.9836E-01*nb2fb);
				setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_120M250"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_120M250", 100000, 8.5304E-03*nb2fb);
			}
			else setMCtree(ntupledir+"/mcLocalControl_Zmumu"+filesuffix+".root", "mcLocalControl_Zmumu", 4878990, 8.3470E-01*nb2fb); // need to do a cut to keep events only up to 250 GeV
			
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_250M400"+filesuffix+".root",   "mcLocalControl_Pythia6_DYmumu_250M400",   100000, 4.1004E-04*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_400M600"+filesuffix+".root",   "mcLocalControl_Pythia6_DYmumu_400M600",   100000, 6.6393E-05*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_600M800"+filesuffix+".root",   "mcLocalControl_Pythia6_DYmumu_600M800",   100000, 1.0955E-05*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_800M1000"+filesuffix+".root",  "mcLocalControl_Pythia6_DYmumu_800M1000",  100000, 2.6470E-06*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1000M1250"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_1000M1250", 100000, 8.9015E-07*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1250M1500"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_1250M1500", 100000, 2.3922E-07*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1500M1750"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_1500M1750", 100000, 7.3439E-08*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1750M2000"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_1750M2000", 100000, 2.4643E-08*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2000M2250"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_2000M2250", 100000, 8.7619E-09*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2250M2500"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_2250M2500", 100000, 3.2232E-09*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2500M2750"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_2500M2750", 100000, 1.2073E-09*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2750M3000"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_2750M3000", 100000, 4.4763E-10*nb2fb);
			if(!doRemoveHighMass) setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_M3000"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_M3000", 100000, 2.5586E-10*nb2fb); // this is taken out because the EW k-factors are valid only below 3 TeV
		}
	}
	
	if(tsMCname=="DYtautau"  && doDYtautau)
	{
		setMCtree(ntupledir+"/mcLocalControl_DYtautau_75M120"+filesuffix+".root", "mcLocalControl_DYtautau_75M120", 20000, 7.9494E-01*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_DYtautau_120M250"+filesuffix+".root", "mcLocalControl_DYtautau_120M250", 20000, 8.5494E-03*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_DYtautau_250M400"+filesuffix+".root", "mcLocalControl_DYtautau_250M400", 20000, 4.0995E-04*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_DYtautau_400M600"+filesuffix+".root", "mcLocalControl_DYtautau_400M600", 20000, 6.6406E-05*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_DYtautau_600M800"+filesuffix+".root", "mcLocalControl_DYtautau_600M800", 20000, 1.1002E-05*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_DYtautau_800M1000"+filesuffix+".root", "mcLocalControl_DYtautau_800M1000", 20000, 2.6510E-06*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_DYtautau_1000M1250"+filesuffix+".root", "mcLocalControl_DYtautau_1000M1250", 20000, 8.9229E-07*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_DYtautau_1250M1500"+filesuffix+".root", "mcLocalControl_DYtautau_1250M1500", 20000, 2.3996E-07*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_DYtautau_1500M1750"+filesuffix+".root", "mcLocalControl_DYtautau_1500M1750", 20000, 7.3305E-08*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_DYtautau_1750M2000"+filesuffix+".root", "mcLocalControl_DYtautau_1750M2000", 20000, 2.4613E-08*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_DYtautau_M2000"+filesuffix+".root", "mcLocalControl_DYtautau_M2000", 20000, 1.4001E-08*nb2fb);
	}
	
	if(tsMCname=="TTbar")
	{
		setMCtree(ntupledir+"/mcLocalControl_T1_McAtNlo_Jimmy"+filesuffix+".root", "mcLocalControl_T1_McAtNlo_Jimmy", 999500, 89.4*pb2fb); // AMI: 1.4562E-01*nb2fb*5.4259E-01
	}
		
	if(tsMCname=="Diboson")
	{
		setMCtree(ntupledir+"/mcLocalControl_WW_Herwig"+filesuffix+".root", "mcLocalControl_WW_Herwig", 2442266, 17487.); // AMI: 3.1106E-02*nb2fb*3.8947E-01
		setMCtree(ntupledir+"/mcLocalControl_WZ_Herwig"+filesuffix+".root", "mcLocalControl_WZ_Herwig", 239949,  5743.);  // AMI: 1.1485E-02*nb2fb*3.1043E-01
		setMCtree(ntupledir+"/mcLocalControl_ZZ_Herwig"+filesuffix+".root", "mcLocalControl_ZZ_Herwig", 244999,  1271.);  // AMI: 4.5721E-03*nb2fb*2.1319E-01
	}

	if(tsMCname=="jjmu15X"  &&  doIsolationStudy)
	{
		setMCtree(ntupledir+"/mcLocalControl_PythiaB_ccmu15X"+filesuffix+".root", "mcLocalControl_PythiaB_ccmu15X", 1499697, 2.84E+04*pb2fb); //http://cdsweb.cern.ch/record/1282370/files/ATL-CAL-PROC-2010-001.pdf?version=3
		setMCtree(ntupledir+"/mcLocalControl_PythiaB_bbmu15X"+filesuffix+".root", "mcLocalControl_PythiaB_bbmu15X", 4492093, 7.39E+04*pb2fb); //http://cdsweb.cern.ch/record/1282370/files/ATL-CAL-PROC-2010-001.pdf?version=3
	}
	
	if(tsMCname=="W+jets"  && doWjets)
	{
		// setMCtree(ntupledir+"/mcLocalControl_Wmunu"+filesuffix+".root", "mcLocalControl_Wmunu", 6959806, 8.7017E+00*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_AlpgenJimmyWmunuNp0_pt20"+filesuffix+".root", "mcLocalControl_AlpgenJimmyWmunuNp0_pt20", 3421954, 8.2840*nb2fb); // AMI: 6.9324E+00*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_AlpgenJimmyWmunuNp1_pt20"+filesuffix+".root", "mcLocalControl_AlpgenJimmyWmunuNp1_pt20", 2479594, 1.5616*nb2fb); // AMI: 1.3059E+00*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_AlpgenJimmyWmunuNp2_pt20"+filesuffix+".root", "mcLocalControl_AlpgenJimmyWmunuNp2_pt20", 3718149, 0.4533*nb2fb); // AMI: 3.7807E-01*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_AlpgenJimmyWmunuNp3_pt20"+filesuffix+".root", "mcLocalControl_AlpgenJimmyWmunuNp3_pt20", 988857,  0.1217*nb2fb); // AMI: 1.0185E-01*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_AlpgenJimmyWmunuNp4_pt20"+filesuffix+".root", "mcLocalControl_AlpgenJimmyWmunuNp4_pt20", 254950,  0.0310*nb2fb); // AMI: 2.5720E-02*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_AlpgenJimmyWmunuNp5_pt20"+filesuffix+".root", "mcLocalControl_AlpgenJimmyWmunuNp5_pt20", 70000,   0.0083*nb2fb); // AMI: 6.9999E-03*nb2fb);
	}
	
	
	
	
	/* 
	if(tsMCname=="Gmm_01_1750")
	{
		setMCtree(ntupledir+"/mcLocalControl_Gmm_01_1750"+filesuffix+".root", "mcLocalControl_Gmm_01_1750", 10000, 1.6320E-06*nb2fb);
	}
	if(tsMCname=="Gmm_01_2000")
	{
		setMCtree(ntupledir+"/mcLocalControl_Gmm_01_2000"+filesuffix+".root", "mcLocalControl_Gmm_01_2000", 10000, 5.8721E-07*nb2fb);
	}
	if(tsMCname=="Gmm_01_2250")
	{
		setMCtree(ntupledir+"/mcLocalControl_Gmm_01_2250"+filesuffix+".root", "mcLocalControl_Gmm_01_2250", 10000, 2.1381E-07*nb2fb);
	}
	*/
	

	if(tsMCname=="Zprime_SSM500")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM500"+filesuffix+".root", "mcLocalControl_Zprime_SSM500", 20000, 2.6071E-03*nb2fb);
	}
	if(tsMCname=="Zprime_SSM750")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM750"+filesuffix+".root", "mcLocalControl_Zprime_SSM750", 20000, 4.7349E-04*nb2fb);
	}
	if(tsMCname=="Zprime_SSM1000")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM1000"+filesuffix+".root", "mcLocalControl_Zprime_SSM1000", 20000, 1.2466E-04*nb2fb);
	}
	if(tsMCname=="Zprime_SSM1500")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM1500"+filesuffix+".root", "mcLocalControl_Zprime_SSM1500", 20000, 1.4380E-05*nb2fb);
	}
	if(tsMCname=="Zprime_SSM1750")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM1750"+filesuffix+".root", "mcLocalControl_Zprime_SSM1750", 20000, 5.6743E-06*nb2fb);
	}
	if(tsMCname=="Zprime_SSM2000")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM2000"+filesuffix+".root", "mcLocalControl_Zprime_SSM2000", 20000, 2.4357E-06*nb2fb);
	}
	
	if(tsMCname=="Zprime_SSM_m2000")
	{
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_120M450"+filesuffix+".root",   "mcLocalControl_Pythia8_ZprimeSSM_m2000_120M450",   40000, 0.00926176*nb2fb);// 7.9574E-03*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_450M850"+filesuffix+".root",   "mcLocalControl_Pythia8_ZprimeSSM_m2000_450M850",   10000, 4.61608E-05*nb2fb);// 3.8040E-05 *nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_850M1300"+filesuffix+".root",  "mcLocalControl_Pythia8_ZprimeSSM_m2000_850M1300",  10000, 2.20599E-06*nb2fb);// 1.7327E-06*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_1300M1800"+filesuffix+".root", "mcLocalControl_Pythia8_ZprimeSSM_m2000_1300M1800", 10000, 2.07705E-07*nb2fb);// 1.5144E-07*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_1800M2300"+filesuffix+".root", "mcLocalControl_Pythia8_ZprimeSSM_m2000_1800M2300", 10000, 1.46265E-06*nb2fb);// 1.0133E-06*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_2300M2800"+filesuffix+".root", "mcLocalControl_Pythia8_ZprimeSSM_m2000_2300M2800", 10000, 1.94916E-08*nb2fb);// 1.1455E-08*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_2800M3300"+filesuffix+".root", "mcLocalControl_Pythia8_ZprimeSSM_m2000_2800M3300", 10000, 1.4684E-09*nb2fb);// 7.0524E-10*nb2fb);
		if(!doRemoveHighMass) setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_M3300"+filesuffix+".root", "mcLocalControl_Pythia8_ZprimeSSM_m2000_M3300", 10000, 1.69363E-10*nb2fb);// 6.6724E-11*nb2fb);
	}

	if(tsMCname=="ExtraDimsTEV_m2000")
	{
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_120M450"+filesuffix+".root",   "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_120M450",   40000, 0.00898959*nb2fb);// 7.7227E-03*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_450M850"+filesuffix+".root",   "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_450M850",   10000, 2.66544E-05*nb2fb);// 2.1906E-05*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_850M1300"+filesuffix+".root",  "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_850M1300",  10000, 2.56013E-07*nb2fb);// 2.0058E-07*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_1300M1800"+filesuffix+".root", "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_1300M1800", 10000, 1.89361E-06*nb2fb);// 1.3579E-06*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_1800M2300"+filesuffix+".root", "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_1800M2300", 10000, 1.47063E-05*nb2fb);// 9.4190E-06*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_2300M2800"+filesuffix+".root", "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_2300M2800", 10000, 8.47227E-08*nb2fb);// 4.7462E-08*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_2800M3300"+filesuffix+".root", "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_2800M3300", 10000, 6.53577E-10*nb2fb);// 2.9864E-10*nb2fb);
		if(!doRemoveHighMass) setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_M3300"+filesuffix+".root", "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_M3300", 10000, 9.45194E-09*nb2fb);// 3.2102E-09*nb2fb);
	}
}

void setMCbranches()
{
	_DEBUG("setMCbranches");

	truth_all_mc_pt = 0;
	truth_all_mc_m = 0;
	truth_all_mc_eta = 0;
	truth_all_mc_phi = 0;
	truth_all_mc_status = 0;
	truth_all_mc_barcode = 0;
	truth_all_mc_pdgId = 0;
	truth_all_mc_charge = 0;
	
	truth_all_partons_mc_pt = 0;
	truth_all_partons_mc_m = 0;
	truth_all_partons_mc_eta = 0;
	truth_all_partons_mc_phi = 0;
	truth_all_partons_mc_status = 0;
	truth_all_partons_mc_barcode = 0;
	truth_all_partons_mc_pdgId = 0;
	truth_all_partons_mc_charge = 0;

	recon_all_E = 0;
	recon_all_pt = 0;
	recon_all_m = 0;
	recon_all_eta = 0;
	recon_all_phi = 0;
	recon_all_px = 0;
	recon_all_py = 0;
	recon_all_pz = 0;
	recon_all_charge = 0;
	recon_all_y = 0;
	recon_all_id = 0;
	recon_all_theta = 0;
	
	recon_all_ptcone20 = 0;
	recon_all_ptcone30 = 0;
	recon_all_ptcone40 = 0;
	recon_all_etcone20 = 0;
	recon_all_etcone30 = 0;
	recon_all_etcone40 = 0;
	recon_all_nucone20 = 0;
	recon_all_nucone30 = 0;
	recon_all_nucone40 = 0;
	recon_all_allauthor = 0;
	recon_all_author = 0;
	recon_all_beta = 0;
	recon_all_isMuonLikelihood = 0;
	recon_all_matchchi2 = 0;
	recon_all_matchndof = 0;

	
	E = 0;
	pt = 0;
	m = 0;
	eta = 0;
	phi = 0;
	px = 0;
	py = 0;
	pz = 0;
	charge = 0;
	allauthor = 0;
	author = 0;
	beta = 0;
	me_d0 = 0;
	me_z0 = 0;
	me_phi = 0;
	me_theta = 0;
	me_qoverp = 0;
	ie_d0 = 0;
	ie_z0 = 0;
	ie_phi = 0;
	ie_theta = 0;
	ie_qoverp = 0;
	
	tree->SetBranchAddress( "all_actualIntPerXing",  &all_actualIntPerXing );
	tree->SetBranchAddress( "all_averageIntPerXing", &all_averageIntPerXing );
	tree->SetBranchAddress( "all_mc_channel_number", &all_mc_channel_number );
	tree->SetBranchAddress( "all_mc_event_number",   &all_mc_event_number );
	tree->SetBranchAddress( "all_mc_event_weight",   &all_mc_event_weight );
	
	tree->SetBranchAddress( "all_RunNumber",         &all_RunNumber );
	
	tree->SetBranchAddress( "all_pileup_weight",      &all_pileup_weight );
	tree->SetBranchAddress( "all_intime_pileup_weight",    &all_intime_pileup_weight );
	tree->SetBranchAddress( "all_outoftime_pileup_weight", &all_outoftime_pileup_weight );
	tree->SetBranchAddress( "all_lumi_pileup_weight", &all_lumi_pileup_weight );
	tree->SetBranchAddress( "all_EW_kfactor_weight",  &all_EW_kfactor_weight );
	tree->SetBranchAddress( "all_QCD_kfactor_weight", &all_QCD_kfactor_weight );
	tree->SetBranchAddress( "all_mcevent_weight",     &all_mcevent_weight );
	tree->SetBranchAddress( "all_total_weight",       &all_total_weight );
	tree->SetBranchAddress( "all_randomized_decision",&all_randomized_decision );

	tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
	tree->SetBranchAddress("truth_all_mc_pt", &truth_all_mc_pt);
	tree->SetBranchAddress("truth_all_mc_m", &truth_all_mc_m);
	tree->SetBranchAddress("truth_all_mc_eta", &truth_all_mc_eta);
	tree->SetBranchAddress("truth_all_mc_phi", &truth_all_mc_phi);
	tree->SetBranchAddress("truth_all_mc_status", &truth_all_mc_status);
	tree->SetBranchAddress("truth_all_mc_barcode", &truth_all_mc_barcode);
	tree->SetBranchAddress("truth_all_mc_pdgId", &truth_all_mc_pdgId);
	tree->SetBranchAddress("truth_all_mc_charge", &truth_all_mc_charge);
	tree->SetBranchAddress("truth_all_Mhat", &truth_all_Mhat);
	tree->SetBranchAddress("truth_all_CosThetaCS", &truth_all_CosThetaCS);
	tree->SetBranchAddress("truth_all_CosThetaHE", &truth_all_CosThetaHE);
	tree->SetBranchAddress("truth_all_ySystem", &truth_all_ySystem);
	tree->SetBranchAddress("truth_all_QT", &truth_all_QT);
	
	tree->SetBranchAddress("truth_all_partons_mc_pt", &truth_all_partons_mc_pt);
	tree->SetBranchAddress("truth_all_partons_mc_m", &truth_all_partons_mc_m);
	tree->SetBranchAddress("truth_all_partons_mc_eta", &truth_all_partons_mc_eta);
	tree->SetBranchAddress("truth_all_partons_mc_phi", &truth_all_partons_mc_phi);
	tree->SetBranchAddress("truth_all_partons_mc_status", &truth_all_partons_mc_status);
	tree->SetBranchAddress("truth_all_partons_mc_barcode", &truth_all_partons_mc_barcode);
	tree->SetBranchAddress("truth_all_partons_mc_pdgId", &truth_all_partons_mc_pdgId);
	tree->SetBranchAddress("truth_all_partons_mc_charge", &truth_all_partons_mc_charge);
	
	tree->SetBranchAddress("truth_all_vKKwgt",   &truth_all_vKKwgt);
	tree->SetBranchAddress("truth_all_vZPwgt",   &truth_all_vZPwgt);
	tree->SetBranchAddress("truth_all_vBSMmass", &truth_all_vBSMmass);

	tree->SetBranchAddress("recon_all_isValid", &recon_all_isValid);
	tree->SetBranchAddress("recon_all_vxp_n", &recon_all_vxp_n);
	tree->SetBranchAddress("recon_all_E", &recon_all_E);
	tree->SetBranchAddress("recon_all_pt", &recon_all_pt);
	tree->SetBranchAddress("recon_all_m", &recon_all_m);
	tree->SetBranchAddress("recon_all_eta", &recon_all_eta);
	tree->SetBranchAddress("recon_all_phi", &recon_all_phi);
	tree->SetBranchAddress("recon_all_px", &recon_all_px);
	tree->SetBranchAddress("recon_all_py", &recon_all_py);
	tree->SetBranchAddress("recon_all_pz", &recon_all_pz);
	tree->SetBranchAddress("recon_all_charge", &recon_all_charge);
	tree->SetBranchAddress("recon_all_ptcone20", &recon_all_ptcone20);
	tree->SetBranchAddress("recon_all_ptcone30", &recon_all_ptcone30);
	tree->SetBranchAddress("recon_all_ptcone40", &recon_all_ptcone40);
	tree->SetBranchAddress("recon_all_etcone20", &recon_all_etcone20);
	tree->SetBranchAddress("recon_all_etcone30", &recon_all_etcone30);
	tree->SetBranchAddress("recon_all_etcone40", &recon_all_etcone40);
	tree->SetBranchAddress("recon_all_nucone20", &recon_all_nucone20);
	tree->SetBranchAddress("recon_all_nucone30", &recon_all_nucone30);
	tree->SetBranchAddress("recon_all_nucone40", &recon_all_nucone40);
	tree->SetBranchAddress("recon_all_allauthor", &recon_all_allauthor);
	tree->SetBranchAddress("recon_all_author", &recon_all_author);
	tree->SetBranchAddress("recon_all_beta", &recon_all_beta);
	tree->SetBranchAddress("recon_all_isMuonLikelihood", &recon_all_isMuonLikelihood);
	tree->SetBranchAddress("recon_all_matchchi2", &recon_all_matchchi2);
	tree->SetBranchAddress("recon_all_matchndof", &recon_all_matchndof);
	tree->SetBranchAddress("recon_all_y", &recon_all_y);
	tree->SetBranchAddress("recon_all_id", &recon_all_id);
	tree->SetBranchAddress("recon_all_theta", &recon_all_theta);
	tree->SetBranchAddress("recon_all_Mhat", &recon_all_Mhat);
	tree->SetBranchAddress("recon_all_CosThetaCS", &recon_all_CosThetaCS);
	tree->SetBranchAddress("recon_all_CosThetaHE", &recon_all_CosThetaHE);
	tree->SetBranchAddress("recon_all_ySystem", &recon_all_ySystem);
	tree->SetBranchAddress("recon_all_QT", &recon_all_QT);
	
	_DEBUG("successfully read mc branches");
}

void setDATAbranches()
{
	_DEBUG("setDATAbranches");

	E = 0;
	pt = 0;
	m = 0;
	eta = 0;
	phi = 0;
	px = 0;
	py = 0;
	pz = 0;
	charge = 0;
	allauthor = 0;
	author = 0;
	beta = 0;
	me_d0 = 0;
	me_z0 = 0;
	me_phi = 0;
	me_theta = 0;
	me_qoverp = 0;
	ie_d0 = 0;
	ie_z0 = 0;
	ie_phi = 0;
	ie_theta = 0;
	ie_qoverp = 0;
	
	allauthor = 0;
	author = 0;
	beta = 0;
	isMuonLikelihood = 0;
	matchchi2 = 0;
	matchndof = 0;
	etcone20 = 0;
	etcone30 = 0;
	etcone40 = 0;
	nucone20 = 0;
	nucone30 = 0;
	nucone40 = 0;
	ptcone20 = 0;
	ptcone30 = 0;
	ptcone40 = 0;
	
	tree->SetBranchAddress( "actualIntPerXing",  &actualIntPerXing );
	tree->SetBranchAddress( "averageIntPerXing", &averageIntPerXing );
	tree->SetBranchAddress( "mc_channel_number", &mc_channel_number );
	tree->SetBranchAddress( "mc_event_number",   &mc_event_number );
	tree->SetBranchAddress( "mc_event_weight",   &mc_event_weight );
	
	tree->SetBranchAddress( "pileup_weight",  &pileup_weight );
	tree->SetBranchAddress( "EW_kfactor_weight", &EW_kfactor_weight );
	tree->SetBranchAddress( "QCD_kfactor_weight", &QCD_kfactor_weight );
	tree->SetBranchAddress( "mcevent_weight", &mcevent_weight );
	
	tree->SetBranchAddress("vxp_n", &vxp_n);
	
	tree->SetBranchAddress("E", &E);
	tree->SetBranchAddress("pt", &pt);
	tree->SetBranchAddress("m", &m);
	tree->SetBranchAddress("eta", &eta);
	tree->SetBranchAddress("phi", &phi);
	tree->SetBranchAddress("px", &px);
	tree->SetBranchAddress("py", &py);
	tree->SetBranchAddress("pz", &pz);
	tree->SetBranchAddress("charge", &charge);
	tree->SetBranchAddress("allauthor", &allauthor);
	tree->SetBranchAddress("author", &author);
	tree->SetBranchAddress("beta", &beta);
	tree->SetBranchAddress("me_d0", &me_d0);
	tree->SetBranchAddress("me_z0", &me_z0);
	tree->SetBranchAddress("me_phi", &me_phi);
	tree->SetBranchAddress("me_theta", &me_theta);
	tree->SetBranchAddress("me_qoverp", &me_qoverp);
	tree->SetBranchAddress("ie_d0", &ie_d0);
	tree->SetBranchAddress("ie_z0", &ie_z0);
	tree->SetBranchAddress("ie_phi", &ie_phi);
	tree->SetBranchAddress("ie_theta", &ie_theta);
	tree->SetBranchAddress("ie_qoverp", &ie_qoverp);
	tree->SetBranchAddress("allauthor", &allauthor);
	tree->SetBranchAddress("author", &author);
	tree->SetBranchAddress("beta", &beta);
	tree->SetBranchAddress("isMuonLikelihood", &isMuonLikelihood);
	tree->SetBranchAddress("matchchi2", &matchchi2);
	tree->SetBranchAddress("matchndof", &matchndof);
	tree->SetBranchAddress("etcone20", &etcone20);
	tree->SetBranchAddress("etcone30", &etcone30);
	tree->SetBranchAddress("etcone40", &etcone40);
	tree->SetBranchAddress("nucone20", &nucone20);
	tree->SetBranchAddress("nucone30", &nucone30);
	tree->SetBranchAddress("nucone40", &nucone40);
	tree->SetBranchAddress("ptcone20", &ptcone20);
	tree->SetBranchAddress("ptcone30", &ptcone30);
	tree->SetBranchAddress("ptcone40", &ptcone40);
	tree->SetBranchAddress("Mhat", &Mhat);
	tree->SetBranchAddress("CosThetaCS", &CosThetaCS);
	tree->SetBranchAddress("CosThetaHE", &CosThetaHE);
	tree->SetBranchAddress("Ysystem", &Ysystem);
	tree->SetBranchAddress("Q_T", &Q_T);
	tree->SetBranchAddress("CosThetaDimu", &CosThetaDimu);
	tree->SetBranchAddress("ipTDiff", &ipTDiff);
	tree->SetBranchAddress("EtaSum", &EtaSum);
	
	_DEBUG("successfully read data branches");
}

float getFlatLumiWeight(TString mcName)
{
	_DEBUG("getFlatLumiWeight");
	float N     = mcNeventsMap[mcName];
	float sigma = mcSigmaMap[mcName];
	float Lmc   = N/sigma;
	return luminosity/Lmc;
}


void hbook()
{
	_DEBUG("hbook");

	setLogBins(npbins,pmin,pmax,pbins);
	setLogBins(nlogptbins,logptmin,logptmax,logptbins);
	setLogBins(nlogqtbins,logqtmin,logqtmax,logqtbins);
	setLogBins(nlogmassbins,logmassmin,logmassmax,logmassbins);
	setLogBins(nlogimassbins,logimassmin,logimassmax,logimassbins);
	setLogBins(nlogfullimassbins,logfullimassmin,logfullimassmax,logfullimassbins);
	setLogBins(nloglimitimassbins, loglimitimassmin, loglimitimassmax, loglimitimassbins);
	setLogBins(nlogofficialimassbins,logofficialimassmin,logofficialimassmax,logofficialimassbins);
	setLogBins(nlogisoimassbins,logisoimassmin,logisoimassmax,logisoimassbins);
	setSqrtBins(nsqrtofficialptbins, sqrtofficialptmin, sqrtofficialptmax, sqrtofficialptbins);
	setSqrtBins(nsqrtofficialqtbins, sqrtofficialqtmin, sqrtofficialqtmax, sqrtofficialqtbins);
	
	//// lines
	linMap.insert( make_pair("hMassCosThetaCS_horline", new TLine(linfullimassmin,0.,linfullimassmax,0.)) );
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		linMap.insert( make_pair("hMassCosThetaCS_vertline_"+_s(logmassbins[ms]), new TLine(logmassbins[ms],minFullCosTheta,logmassbins[ms],maxFullCosTheta)) );
	}
	linMap.insert( make_pair("hMassyQ_horline", new TLine(linfullimassmin,0.,linfullimassmax,0.)) );
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		linMap.insert( make_pair("hMassyQ_vertline_"+_s(logmassbins[ms]), new TLine(logmassbins[ms],minfullyQ,logmassbins[ms],maxfullyQ)) );
	}
	
	//// KK/ZP templates for the limit
	if((doFullKKtemplates || doFullZPtemplates) && doTemplates)
	{
		for(double M=mKKmmMin ; M<=mKKmmMax ; M+=dMKKmm)
		{
			TString massName = (TString)_s(M);
			
			if(doFullKKtemplates)
			{
				h1Map.insert( make_pair("hMass_template_KK"+massName, new TH1D("hMass_template_KK"+massName, "#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
				h1Map.insert( make_pair("hMass_truth_template_KK"+massName, new TH1D("hMass_truth_template_KK"+massName, "#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
			}
			else if(doFullZPtemplates)
			{
				h1Map.insert( make_pair("hMass_template_Zprime_SSM"+massName, new TH1D("hMass_template_Zprime_SSM"+massName, "#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
				h1Map.insert( make_pair("hMass_truth_template_Zprime_SSM"+massName, new TH1D("hMass_truth_template_Zprime_SSM"+massName, "#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
			}
		}
	}
	
	/* graphics(TH1* th1,
			  Color_t fillcolor=-1, Int_t fillstyle=-1,
			  Color_t linecolor=-1, Int_t linestyle=-1, Int_t linewidth=-1,
			  Color_t mrkrcolor=-1, Int_t mrkrstyle=-1, Float_t mrkrsize=-1,
			  Bool_t moreLogLabels=true, Bool_t noexponent=true,
			  TString title="", TString xtitle="", TString ytitle="") */
			  
	for(TMapTS2GRPX::iterator it=grpx.begin() ; it!=grpx.end() ; ++it)
	{
		TString name = it->first;
		
		///////////////////////////////////////////////////////
		//Templates: skip all but DYmumu and the templates ////
		///////////////////////////////////////////////////////
		
		// For the truth information of the DYmumu Z' and the templates
		if(name=="DYmumu" || name.Contains("Zprime") || name.Contains("ExtraDimsTEV"))
		{
			int mtypemax = (name.Contains("_m2000") || name=="DYmumu") ? 1 : 3; // don't need to loop on the pyhtia8 samples
			for(int mtype=0 ; mtype<mtypemax ; mtype++)
			{
				TString mname = "";
				Color_t mfillcolor = -1;
				Int_t   mfillstyle = -1;
				Color_t mlinecolor = -1;
				Int_t   mlinestyle = -1;
				Int_t   mlinewidth = -1;
				Color_t mmrkrcolor = -1;
				Int_t   mmrkrstyle = -1;
				Float_t mmrkrsize  = -1;
				
				if(mtype==0) // official pythia6 Z's -OR- official pythia8 Z' / KK
				{
					mname = name;
					mfillcolor = grpx[name]->filcolor;
					mfillstyle = grpx[name]->filstyle;
					mlinecolor = grpx[name]->lincolor;
					mlinestyle = grpx[name]->linstyle;
					mlinewidth = grpx[name]->linwidth;
					mmrkrcolor = grpx[name]->mrkcolor;
					mmrkrstyle = grpx[name]->mrkstyle;
					mmrkrsize  = grpx[name]->mrksize;
				}
				if(mtype==1) // template Z'
				{
					mname = getTemplateName(name);
					mfillcolor = -1;
					mfillstyle = -1;
					mlinecolor = kOrange + 10;
					mlinestyle = +1;
					mlinewidth = +1;
					mmrkrcolor = -1;
					mmrkrstyle = -1;
					mmrkrsize  = -1;
				}
				if(mtype==2) // template KK
				{
					mname = getTemplateName(name,"KK");
					mfillcolor = -1;
					mfillstyle = -1;
					mlinecolor = kOrange + 3;
					mlinestyle = +1;
					mlinewidth = +1;
					mmrkrcolor = -1;
					mmrkrstyle = -1;
					mmrkrsize  = -1;
				}
				
				h1Map.insert( make_pair("hMass"+mname+"_truth", new TH1D("hMass"+mname+"_truth",";m_{#mu#mu} GeV;Events",nlogofficialimassbins,logofficialimassbins)) );
				setlogx(h1Map["hMass"+mname+"_truth"]);
				graphics(h1Map["hMass"+mname+"_truth"],mfillcolor,mfillstyle,mlinecolor,mlinestyle,mlinewidth,mmrkrcolor,mmrkrstyle,mmrkrsize);
				
				h1Map.insert( make_pair("hpTLeading"+mname+"_truth", new TH1D("hpTLeading"+mname+"_truth",";p_{T}^{leading} GeV;Events",nsqrtofficialptbins,sqrtofficialptbins)) );
				setlogx(h1Map["hpTLeading"+mname+"_truth"]);
				graphics(h1Map["hpTLeading"+mname+"_truth"],mfillcolor,mfillstyle,mlinecolor,mlinestyle,mlinewidth,mmrkrcolor,mmrkrstyle,mmrkrsize);
				
				h1Map.insert( make_pair("hMass_limit_"+mname+"_truth", new TH1D("hMass_limit_"+mname+"_truth", "#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
				
				if(mtype>0) // templates
				{
					h1Map.insert( make_pair("hMass"+mname, new TH1D("hMass"+mname,";m_{#mu#mu} GeV;Events",nlogofficialimassbins,logofficialimassbins)) );
					setlogx(h1Map["hMass"+mname]);
					graphics(h1Map["hMass"+mname],mfillcolor,mfillstyle,mlinecolor,mlinestyle,mlinewidth,mmrkrcolor,mmrkrstyle,mmrkrsize);
					
					h1Map.insert( make_pair("hpTLeading"+mname, new TH1D("hpTLeading"+mname,";p_{T}^{leading} GeV;Events",nsqrtofficialptbins,sqrtofficialptbins)) );
					setlogx(h1Map["hpTLeading"+mname]);
					graphics(h1Map["hpTLeading"+mname],mfillcolor,mfillstyle,mlinecolor,mlinestyle,mlinewidth,mmrkrcolor,mmrkrstyle,mmrkrsize);
					
					h1Map.insert( make_pair("hMass_limit_"+mname, new TH1D("hMass_limit_"+mname, "#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
				}
			}
		}
	}
	
	// For the truth information of all the models
	for(TMapTS2GRPX::iterator it=grpx.begin() ; it!=grpx.end() ; ++it)
	{
		TString name = it->first;
		
		h1Map.insert( make_pair("hNvxp_no_puwgt"+name, new TH1D("hNvxp_no_puwgt"+name,";N_{vertices};Events",35,1.,36.)) );
		graphics(h1Map["hNvxp_no_puwgt"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		h1Map.insert( make_pair("hNvxp_with_puwgt"+name, new TH1D("hNvxp_with_puwgt"+name,";N_{vertices};Events",35,1.,36.)) );
		graphics(h1Map["hNvxp_with_puwgt"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		
		h1Map.insert( make_pair("hMassNumbers"+name, new TH1D("hMassNumbers"+name,";m_{#mu#mu} GeV;Events",imasslogicnbins,imasslogicbins)) );
		setlogx(h1Map["hMassNumbers"+name]);
		graphics(h1Map["hMassNumbers"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		h1Map.insert( make_pair("hMass"+name, new TH1D("hMass"+name,";m_{#mu#mu} GeV;Events",nlogofficialimassbins,logofficialimassbins)) );
		setlogx(h1Map["hMass"+name]);
		graphics(h1Map["hMass"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		h1Map.insert( make_pair("hMass1GeV"+name, new TH1D("hMass1GeV"+name,";m_{#mu#mu} GeV;Events",nlingevimassbins,lingevimassmin,lingevimassmax)) );
		setlogx(h1Map["hMass1GeV"+name]);
		graphics(h1Map["hMass1GeV"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
				 
		h1Map.insert( make_pair("hMassAntiIsolated"+name, new TH1D("hMassAntiIsolated"+name,";m_{#mu#mu} GeV;Events",nlogisoimassbins,logisoimassbins)) );
		setlogx(h1Map["hMassAntiIsolated"+name]);
		graphics(h1Map["hMassAntiIsolated"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		h1Map.insert( make_pair("hIsolationFull"+name, new TH1D("hIsolationFull"+name,";#Sigmap_{T}^{trk}/p_{T}^{#mu};Events",nisofullbins,isofullmin,isofullmax)) );
		setlogx(h1Map["hIsolationFull"+name]);
		graphics(h1Map["hIsolationFull"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		h1Map.insert( make_pair("hIsolationLow"+name, new TH1D("hIsolationLow"+name,";#Sigmap_{T}^{trk}/p_{T}^{#mu};Events",nisobins,isomin,isomax)) );
		setlogx(h1Map["hIsolationLow"+name]);
		graphics(h1Map["hIsolationLow"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		
		h1Map.insert( make_pair("hyQ"+name, new TH1D("hyQ"+name,";y_{Q};Events",nyQbins,minyQ,maxyQ)) );
		setlogx(h1Map["hyQ"+name]);
		graphics(h1Map["hyQ"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
				 
		h1Map.insert( make_pair("hQT"+name, new TH1D("hQT"+name,";Q_{T} GeV;Events",nsqrtofficialqtbins,sqrtofficialqtbins)) );
		setlogx(h1Map["hQT"+name]);
		graphics(h1Map["hQT"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		
		h1Map.insert( make_pair("hEtaQ"+name, new TH1D("hEtaQ"+name,";#eta_{Q};Events",netaQbins,etaQmin,etaQmax)) );
		setlogx(h1Map["hEtaQ"+name]);
		graphics(h1Map["hEtaQ"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
				 
		h1Map.insert( make_pair("hEtaLeading"+name, new TH1D("hEtaLeading"+name,";#eta_{#mu}^{leading};Events",nEtabins,Etamin,Etamax)) );
		setlogx(h1Map["hEtaLeading"+name]);
		graphics(h1Map["hEtaLeading"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		h1Map.insert( make_pair("hEtaSubleading"+name, new TH1D("hEtaSubleading"+name,";#eta_{#mu}^{subleading};Events",nEtabins,Etamin,Etamax)) );
		setlogx(h1Map["hEtaSubleading"+name]);
		graphics(h1Map["hEtaSubleading"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
				 
		h1Map.insert( make_pair("hPhiLeading"+name, new TH1D("hPhiLeading"+name,";#phi_{#mu}^{leading};Events",nPhibins,Phimin,Phimax)) );
		setlogx(h1Map["hPhiLeading"+name]);
		graphics(h1Map["hPhiLeading"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		h1Map.insert( make_pair("hPhiSubleading"+name, new TH1D("hPhiSubleading"+name,";#phi_{#mu}^{subleading};Events",nPhibins,Phimin,Phimax)) );
		setlogx(h1Map["hPhiSubleading"+name]);
		graphics(h1Map["hPhiSubleading"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		
		h1Map.insert( make_pair("hpTLeading"+name, new TH1D("hpTLeading"+name,";p_{T}^{leading} GeV;Events",nsqrtofficialptbins,sqrtofficialptbins)) );
		setlogx(h1Map["hpTLeading"+name]);
		graphics(h1Map["hpTLeading"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		h1Map.insert( make_pair("hpTSubleading"+name, new TH1D("hpTSubleading"+name,";p_{T}^{subleading} GeV;Events",nsqrtofficialptbins,sqrtofficialptbins)) );
		setlogx(h1Map["hpTSubleading"+name]);
		graphics(h1Map["hpTSubleading"+name],
				 grpx[name]->filcolor,grpx[name]->filstyle,
				 grpx[name]->lincolor,grpx[name]->linstyle,grpx[name]->linwidth,
				 grpx[name]->mrkcolor,grpx[name]->mrkstyle,grpx[name]->mrksize);
		
		//// flat 1d
		h1Map.insert( make_pair("hMass_limit_"+name, new TH1D("hMass_limit_"+name, "#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		
		//// 2d
		h2Map.insert( make_pair("hMassCosThetaCS"+name, new TH2D("hMassCosThetaCS"+name,";m_{#mu#mu} GeV;cos(#theta*);Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
		setlogx(h2Map["hMassCosThetaCS"+name]);
		
		h2Map.insert( make_pair("hMassyQ"+name, new TH2D("hMassyQ"+name,";m_{#mu#mu} GeV;y_{Q};Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nfullyQbins,minfullyQ,maxfullyQ)) );
		setlogx(h2Map["hMassyQ"+name]);
	}
}

float getDataMCratio()
{
	float ratio = -999.;
	ratio = (nMCall70to110>0.) ? nData70to110/nMCall70to110 : 1.;
	_INFO("counting ratio  -> DATA/MC in "+_s(imasslogicbins[0])+" to "+_s(imasslogicbins[1])+" GeV is: "+_s(ratio,8));
	ratio = h1Map["hMassNumbersData"]->GetBinContent(1)/h1Map["hMassNumbersMCsum"]->GetBinContent(1);
	_INFO("histogram ratio -> DATA/MC in "+_s(imasslogicbins[0])+" to "+_s(imasslogicbins[1])+" GeV is: "+_s(ratio,8));
	return ratio;
}

float getDataMCratioNoPileup()
{
	float ratio = (nMCall70to110_nopileup>0.) ? nData70to110/nMCall70to110_nopileup : 1.;
	_INFO("DATA/MC (no pileup) in 70 to 110 GeV is: "+_s(ratio,8));
	return ratio;
}

void hscale2Zpeak()
{
	float ratio          = getDataMCratio();
	float ratio_nopileup = getDataMCratioNoPileup();
	
	zpeak_ratio_with_pileup = ratio;
	zpeak_ratio_no_pileup   = ratio_nopileup;
	
	for(TMapTS2GRPX::iterator it=grpx.begin() ; it!=grpx.end() ; ++it)
	{
		TString name = it->first;
		
		/////////////////////////////////////////////
		if(name.Contains("Data")) continue; /////////
		if(name.Contains("QCD"))  continue; /////////
		/////////////////////////////////////////////
		
		Scale(h1Map["hNvxp_no_puwgt"+name],ratio_nopileup);
		Scale(h1Map["hNvxp_with_puwgt"+name],ratio);
		
		Scale(h1Map["hMassNumbers"+name],ratio);
		Scale(h1Map["hMass"+name],ratio);
		Scale(h1Map["hMass1GeV"+name],ratio);
		Scale(h1Map["hMass_limit_"+name],ratio);
		
		if(name=="DYmumu" || name.Contains("Zprime") || name.Contains("ExtraDimsTEV"))
		{
			int mtypemax = (name.Contains("_m2000") || name=="DYmumu") ? 1 : 3; // don't need to loop on the pyhtia8 samples
			for(int mtype=0 ; mtype<mtypemax ; mtype++)
			{
				TString mname = "";
				if(mtype==0) mname = name; // official pythia6 Z's -OR- official pythia8 Z' / KK
				if(mtype==1) mname = getTemplateName(name); // template Z'
				if(mtype==2) mname = getTemplateName(name,"KK"); // template KK
				
				Scale(h1Map["hMass"+mname+"_truth"],ratio);
				Scale(h1Map["hpTLeading"+mname+"_truth"],ratio);
				Scale(h1Map["hMass_limit_"+mname+"_truth"],ratio);
				
				if(mtype>0) // the templates
				{
					Scale(h1Map["hMass"+mname],ratio);
					Scale(h1Map["hpTLeading"+mname],ratio);
					Scale(h1Map["hMass_limit_"+mname],ratio);
				}
			}
		}
		
		//// KK templates for the limit
		if(name=="DYmumu" && (doFullKKtemplates || doFullZPtemplates) && doTemplates)
		{
			for(double M=mKKmmMin ; M<=mKKmmMax ; M+=dMKKmm)
			{
				TString massName = (TString)_s(M);
				if(doFullKKtemplates)
				{
					Scale(h1Map["hMass_template_KK"+massName],ratio);
					Scale(h1Map["hMass_truth_template_KK"+massName],ratio);
				}
				else if(doFullZPtemplates)
				{
					Scale(h1Map["hMass_template_Zprime_SSM"+massName],ratio);
					Scale(h1Map["hMass_truth_template_Zprime_SSM"+massName],ratio);
				}
			}
		}
		
		// Scale(h1Map["hMassAntiIsolated"+name],ratio);
		// Scale(h1Map["hIsolationFull"+name],ratio);
		// Scale(h1Map["hIsolationLow"+name],ratio);
		Scale(h1Map["hyQ"+name],ratio);
		Scale(h1Map["hQT"+name],ratio);
		Scale(h1Map["hEtaQ"+name],ratio);
		Scale(h1Map["hEtaLeading"+name],ratio);
		Scale(h1Map["hEtaSubleading"+name],ratio);
		Scale(h1Map["hPhiLeading"+name],ratio);
		Scale(h1Map["hPhiSubleading"+name],ratio);
		Scale(h1Map["hpTLeading"+name],ratio);
		Scale(h1Map["hpTSubleading"+name],ratio);
		
		Scale(h2Map["hMassCosThetaCS"+name],ratio);
		Scale(h2Map["hMassyQ"+name],ratio);
	}
}

void hMCsumDY(TString tsMCname)
{
	if(!tsMCname.Contains("DYtautau")) return; // DYtautau is part of DYmumu

	h1Map["hNvxp_no_puwgtDYmumu"]->Add(h1Map["hNvxp_no_puwgtDYtautau"]);
	h1Map["hNvxp_with_puwgtDYmumu"]->Add(h1Map["hNvxp_with_puwgtDYtautau"]);
	h1Map["hMassNumbersDYmumu"]->Add(h1Map["hMassNumbersDYtautau"]);
	h1Map["hMassDYmumu"]->Add(h1Map["hMassDYtautau"]);
	h1Map["hMass1GeVDYmumu"]->Add(h1Map["hMass1GeVDYtautau"]);
	h1Map["hMassAntiIsolatedDYmumu"]->Add(h1Map["hMassAntiIsolatedDYtautau"]);	
	h1Map["hMass_limit_DYmumu"]->Add(h1Map["hMass_limit_DYtautau"]);
	h1Map["hIsolationFullDYmumu"]->Add(h1Map["hIsolationFullDYtautau"]);
	h1Map["hIsolationLowDYmumu"]->Add(h1Map["hIsolationLowDYtautau"]);
	h1Map["hyQDYmumu"]->Add(h1Map["hyQDYtautau"]);
	h1Map["hQTDYmumu"]->Add(h1Map["hQTDYtautau"]);
	h1Map["hEtaQDYmumu"]->Add(h1Map["hEtaQDYtautau"]);
	h1Map["hEtaLeadingDYmumu"]->Add(h1Map["hEtaLeadingDYtautau"]);
	h1Map["hEtaSubleadingDYmumu"]->Add(h1Map["hEtaSubleadingDYtautau"]);
	h1Map["hPhiLeadingDYmumu"]->Add(h1Map["hPhiLeadingDYtautau"]);
	h1Map["hPhiSubleadingDYmumu"]->Add(h1Map["hPhiSubleadingDYtautau"]);
	h1Map["hpTLeadingDYmumu"]->Add(h1Map["hpTLeadingDYtautau"]);
	h1Map["hpTSubleadingDYmumu"]->Add(h1Map["hpTSubleadingDYtautau"]);
	
	///// 2d
	h2Map["hMassCosThetaCSDYmumu"]->Add(h2Map["hMassCosThetaCSDYtautau"]);
	h2Map["hMassyQDYmumu"]->Add(h2Map["hMassyQDYtautau"]);
}

void hMCsumall(TString tsMCname)
{
	if(tsMCname.Contains("DYtautau")) return; // DYtautau is part of DYmumu

	h1Map["hNvxp_no_puwgtMCsum"]->Add(h1Map["hNvxp_no_puwgt"+tsMCname]);
	h1Map["hNvxp_with_puwgtMCsum"]->Add(h1Map["hNvxp_with_puwgt"+tsMCname]);
	h1Map["hMassNumbersMCsum"]->Add(h1Map["hMassNumbers"+tsMCname]);
	h1Map["hMassMCsum"]->Add(h1Map["hMass"+tsMCname]);	
	h1Map["hMass1GeVMCsum"]->Add(h1Map["hMass1GeV"+tsMCname]);	
	h1Map["hMassAntiIsolatedMCsum"]->Add(h1Map["hMassAntiIsolated"+tsMCname]);	
	h1Map["hMass_limit_MCsum"]->Add(h1Map["hMass_limit_"+tsMCname]);
	h1Map["hIsolationFullMCsum"]->Add(h1Map["hIsolationFull"+tsMCname]);
	h1Map["hIsolationLowMCsum"]->Add(h1Map["hIsolationLow"+tsMCname]);
	h1Map["hyQMCsum"]->Add(h1Map["hyQ"+tsMCname]);
	h1Map["hQTMCsum"]->Add(h1Map["hQT"+tsMCname]);
	h1Map["hEtaQMCsum"]->Add(h1Map["hEtaQ"+tsMCname]);
	h1Map["hEtaLeadingMCsum"]->Add(h1Map["hEtaLeading"+tsMCname]);
	h1Map["hEtaSubleadingMCsum"]->Add(h1Map["hEtaSubleading"+tsMCname]);
	h1Map["hPhiLeadingMCsum"]->Add(h1Map["hPhiLeading"+tsMCname]);
	h1Map["hPhiSubleadingMCsum"]->Add(h1Map["hPhiSubleading"+tsMCname]);
	h1Map["hpTLeadingMCsum"]->Add(h1Map["hpTLeading"+tsMCname]);
	h1Map["hpTSubleadingMCsum"]->Add(h1Map["hpTSubleading"+tsMCname]);
	
	///// 2d
	h2Map["hMassCosThetaCSMCsum"]->Add(h2Map["hMassCosThetaCS"+tsMCname]);
	h2Map["hMassyQMCsum"]->Add(h2Map["hMassyQ"+tsMCname]);
}

void hbgdraw(TString type, bool dologx=false, bool dology=false)
{
	vector<TString> vtsMCbgds;
	for(TMapiTS::iterator it=grpx_ordered.begin() ; it!=grpx_ordered.end() ; ++it)
	{
		int order    = it->first;
		TString name = it->second;
		
		if(order>20)                  continue; // only backgrounds and data
		if(name.Contains("DYtautau")) continue; // DYtautau is part of DYmumu
		
		if(order==0)
		{
			vtsMCbgds.clear();
			setMinMax(h1Map[type+name],h1Map[type+"Data"],true);
			draw(h1Map[type+name], "", "", dologx, dology);
		}
		
		if(name!="Data")
		{
			drawon(type+grpx_ordered[0], h1Map[type+name]);
			vtsMCbgds.push_back(type+name);
		}
		else
		{
			drawon(type+grpx_ordered[0], h1Map[type+"Data"], "epx0");
		}
	}
	
	drawtxton(type+grpx_ordered[0]);
	drawratio(h1Map[type+"Data"], h1Map[type+"MCsum"], vtsMCbgds, "epx0", "", dologx, dology);
	vtsMCbgds.clear();
}

void hdraw()
{
	_DEBUG("hdraw");
	
	for(TMapTS2GRPX::iterator it=grpx.begin() ; it!=grpx.end() ; ++it)
	{
		TString name = it->first;
		
		TString objname = "";
		TString refname = "";
		TString tptname = "";
		
		if((name.Contains("Zprime")  || name.Contains("ExtraDimsTEV"))  &&  !doIsolationStudy) // both are drawn on top of the DYmumu
		{
			if(name.Contains("_m2000"))
			{
				for(int t=0 ; t<2 ; t++)
				{
					objname = "hMass"+name;
					if(t==0) objname += "_truth";
					refname = "hMassDYmumu";
					if(t==0) refname += "_truth";
					tptname = (name.Contains("Zprime")) ? "hMassZprime_SSM2000_template" : "hMassKK2000_template";
					if(t==0) tptname += "_truth";
					setMinMax(h1Map[refname],h1Map[objname],true);
					draw(h1Map[refname], objname, "", dolog, dolog); // the canvas will be named with the 2nd argument
					drawon(objname, h1Map[objname]);
					drawon(objname, h1Map[tptname]);
					templateText(name, (t==0)?true:false, false);
					drawtemplatetxton(objname);
					
					objname = "hpTLeading"+name;
					if(t==0) objname += "_truth";
					refname = "hpTLeadingDYmumu";
					if(t==0) refname += "_truth";
					tptname = (name.Contains("Zprime")) ? "hpTLeadingZprime_SSM2000_template" : "hpTLeadingKK2000_template";
					if(t==0) tptname += "_truth";
					setMinMax(h1Map[refname],h1Map[objname],true);
					draw(h1Map[refname], objname, "", dolog, dolog); // the canvas will be named with the 2nd argument
					drawon(objname, h1Map[objname]);
					drawon(objname, h1Map[tptname]);
					templateText(name, (t==0)?true:false, false);
					drawtemplatetxton(objname);
				}
			}
			else // if(!name.Contains("_m2000")) then this is the regular Zprime's and the corresponding Z'/KK templates - all are drawn on top of the DYmumu
			{			
				TString massName = getTemplateBareTitle(name);
			
				for(int t=0 ; t<2 ; t++)
				{
					objname = "hMass_"+massName+"_templates";
					if(t==0) objname += "_truth";
					refname = "hMassDYmumu";
					if(t==0) refname += "_truth";
					draw(h1Map[refname], objname, "", dolog, dolog);
					for(int mtype=0 ; mtype<3 ; mtype++)
					{
						TString hname = "hMass";
						if(mtype==0) hname += name; // official pythia6 Z's
						if(mtype==1) hname += getTemplateName(name); // template Z'
						if(mtype==2) hname += getTemplateName(name,"KK"); // template KK
						
						if(t==0) hname += "_truth";
						drawon(objname, h1Map[hname]);
					}
					templateText(name, (t==0)?true:false, true);
					drawtemplatetxton(objname);
					
					objname = "hpTLeading"+massName+"_templates";
					if(t==0) objname += "_truth";
					refname = "hpTLeadingDYmumu";
					if(t==0) refname += "_truth";
					draw(h1Map[refname], objname, "", dolog, dolog);
					for(int mtype=0 ; mtype<3 ; mtype++)
					{
						TString hname = "hpTLeading";
						if(mtype==0) hname += name; // official pythia6 Z's
						if(mtype==1) hname += getTemplateName(name); // template Z'
						if(mtype==2) hname += getTemplateName(name,"KK"); // template KK
						
						if(t==0) hname += "_truth";
						drawon(objname, h1Map[hname]);
					}
					templateText(name, (t==0)?true:false, true);
					drawtemplatetxton(objname);
				}
			}
		} // end of templates
	}
	
	if(!doIsolationStudy)
	{
		hbgdraw("hNvxp_no_puwgt");
		hbgdraw("hNvxp_with_puwgt");
		hbgdraw("hMassNumbers",dolog,dolog);
		hbgdraw("hMass",dolog,dolog);
		hbgdraw("hMass1GeV",!dolog,dolog);
		hbgdraw("hyQ");
		hbgdraw("hQT",dolog,dolog);
		hbgdraw("hEtaQ");
		hbgdraw("hEtaLeading");
		hbgdraw("hEtaSubleading");
		hbgdraw("hPhiLeading");
		hbgdraw("hPhiSubleading");
		hbgdraw("hpTLeading",dolog,dolog);
		hbgdraw("hpTSubleading",dolog,dolog);
	}
	else
	{
		hbgdraw("hMassAntiIsolated",dolog,dolog);
		hbgdraw("hIsolationFull",!dolog,dolog);
		hbgdraw("hIsolationLow",!dolog,dolog);
	}
	
	///// 2d
	bool is2d = true;
	if(!doIsolationStudy)
	{
		for(TMapTS2GRPX::iterator it=grpx.begin() ; it!=grpx.end() ; ++it)
		{
			TString name = it->first;
			TString type = "";
			
			type = "hMassCosThetaCS";
			h2Map[type+name]->SetMinimum( getXYmin(h2Map[type+name]) );
			draw(h2Map["hMassCosThetaCS"+name], "", "COLZ", dolog, !dolog, dolog);
			drawon(type+name, linMap[type+"_horline"]);
			for(int ms=0 ; ms<=nlogmassbins ; ms++) drawon(type+name, linMap[type+"_vertline_"+_s(logmassbins[ms])]);
			drawtxton(type+name, is2d);
			
			type = "hMassyQ";
			draw(h2Map[type+name], "", "COLZ", dolog, !dolog, dolog);
			h2Map[type+name]->SetMinimum( getXYmin(h2Map[type+name]) );
			drawon(type+name, linMap[type+"_horline"]);
			for(int ms=0 ; ms<=nlogmassbins ; ms++) drawon(type+name, linMap[type+"_vertline_"+_s(logmassbins[ms])]);
			drawtxton(type+name, is2d);
		}
	}
}

void weightsNoPU(TString tsMCname, float mass=0., unsigned int truXid=0, double truXmass=0., double truXpT=0.)
{
	//// ZpT reweighting
	ZpTweight = (
				 (tsMCname=="DYmumu" || tsMCname.Contains("Zprime") || tsMCname.Contains("ExtraDimsTEV"))  &&
				 (truXid==PDTZ || truXid==PDTZPRIME0 || truXid==PDTKK)
				 ) ? ZpTrw->GetWeightZee(truXpT,truXmass) : 1.; 
	if(isnaninf(ZpTweight)) _FATAL("ZpTweight is nan or inf -> "+_s(ZpTweight)+": in truXid="+_s(truXid)+", truXmass="+_s(truXmass)+" MeV, truXpT="+_s(truXpT)+" MeV");
	
	//// kFactors:			
	kFQCD_NNLOvLOss = ((tsMCname=="DYmumu"         ||
					   tsMCname.Contains("Zprime") ||
					   tsMCname.Contains("ExtraDimsTEV")) && mass>0.) ? QCD(mass,"NNLO/LO**") : 1.;
	kFEW_NNLOvLOs = (tsMCname=="DYmumu" && mass>0.) ? ElectroWeak(mass) : 1.;
	if(isnaninf(kFQCD_NNLOvLOss)) _FATAL("kFQCD_NNLOvLOss is nan or inf -> "+_s(kFQCD_NNLOvLOss)+": in "+_s(mass)+" GeV");
	if(isnaninf(kFEW_NNLOvLOs))   _FATAL("kFEW_NNLOvLOs is nan or inf -> "+_s(kFEW_NNLOvLOs)+": in "+_s(mass)+" GeV");
	
	//// all weights
	bool isDY       = (tsMCname.Contains("DY")) ? true:false;
	bool isEWSignal = (tsMCname.Contains("Zprime") || tsMCname.Contains("ExtraDimsTEV")) ? true:false;
	bool isGSignal  = (tsMCname.Contains("Gmm")) ? true:false;
	
	event_weight_backgrounds = all_mcevent_weight;
	event_weight_backgrounds *= (doEWkfactor  && isDY) ? kFEW_NNLOvLOs     : 1.;
	event_weight_backgrounds *= (doQCDkfactor && isDY) ? kFQCD_NNLOvLOss   : 1.;
	event_weight_backgrounds *= (doZpT)                ? ZpTweight         : 1.;
	if(isnaninf(event_weight_backgrounds)) _FATAL("event_weight_backgrounds is nan or inf -> "+_s(event_weight_backgrounds));
	
	event_weight_signals = all_mcevent_weight;
	event_weight_signals *= (doQCDkfactor && isEWSignal) ? kFQCD_NNLOvLOss : 1.;
	event_weight_signals *= (doZpT)                      ? ZpTweight       : 1.;
	if(isnaninf(event_weight_signals)) _FATAL("event_weight_signals is nan or inf -> "+_s(event_weight_signals));

	event_weight = (isEWSignal || isGSignal) ? event_weight_signals : event_weight_backgrounds;
	if(isnaninf(event_weight)) _FATAL("event_weight is nan or inf -> "+_s(event_weight));
}
void weights(TString tsMCname, float mass=0., unsigned int truXid=0, double truXmass=0., double truXpT=0.)
{
	//////////////////////////////////////////////////////////
	//// get the weights without the pileup //////////////////
	weightsNoPU(tsMCname, mass, truXid, truXmass, truXpT); ///
	//////////////////////////////////////////////////////////
	
	event_weight_nopileup = event_weight;
	if(isnaninf(event_weight_nopileup)) _FATAL("event_weight_nopileup is nan or inf -> "+_s(event_weight_nopileup));
	
	event_weight *= (dopileup) ? all_pileup_weight : 1.;
	if(isnaninf(event_weight)) _FATAL("event_weight is nan or inf -> "+_s(event_weight));
}

void hfill_isoStudy(TString tsRunType="", TString tsMCname="", Double_t wgt=1.)
{
	_DEBUG("hfill_isoStudy");
	
	int imuontru  = -999;
	int iamuontru = -999;
	float iso30a = 0.;
	float iso30b = 0.;
	float mass   = 0.;
	float ca     = 0.;
	float cb     = 0.;
	int   ai     = -1;
	int   bi     = -1;
	unsigned int truXid = 0;
	double truXmass     = 0.;
	double truXpT       = 0.;
	bool isoppositecharge = false;
	
	if(pTtoIndexMap.size()!=0) pTtoIndexMap.clear();
	
	if(tsRunType=="MC")
	{
		if(truth_all_isValid) // this is needed only for the weights
		{
			if(tsMCname=="DYmumu" || tsMCname.Contains("Zprime") || tsMCname.Contains("ExtraDimsTEV"))
			{
				imuontru  = (truth_all_mc_pdgId->at(0)>0) ? 0 : 1;
				iamuontru = (imuontru==0) ? 1 : 0;
				tlvmutrua->SetPtEtaPhiM(truth_all_mc_pt->at(imuontru),  truth_all_mc_eta->at(imuontru),  truth_all_mc_phi->at(imuontru),  muonMass);
				tlvmutrub->SetPtEtaPhiM(truth_all_mc_pt->at(iamuontru), truth_all_mc_eta->at(iamuontru), truth_all_mc_phi->at(iamuontru), muonMass);
				(*tv3mutrua) = tlvmutrua->Vect();
				(*tv3mutrub) = tlvmutrub->Vect();
				tlvmutruaBoosted = fkinematics::Boost(tlvmutrua,tlvmutrub,tlvmutrua);
				tlvmutrubBoosted = fkinematics::Boost(tlvmutrua,tlvmutrub,tlvmutrub);
				(*tv3mutruaBoosted) = tlvmutruaBoosted->Vect();
				(*tv3mutrubBoosted) = tlvmutrubBoosted->Vect();
				mass = fkinematics::imass(tlvmutrua,tlvmutrub);
			}
			if(tsMCname=="DYmumu")
			{
				// X = Z/Z'/ZKK are always at index 4.
				truXid   = truth_all_partons_mc_pdgId->at(4);
				truXmass = truth_all_partons_mc_m->at(4)*GeV2MeV;
				truXpT   = truth_all_partons_mc_pt->at(4)*GeV2MeV;
			}			
		}
		
		//////////////////////////////////////////////////////
		weights(tsMCname, mass, truXid, truXmass, truXpT); ///
		//////////////////////////////////////////////////////
			
		if(recon_all_isValid)
		{
			_DEBUG("");			
			unsigned int nMus = recon_all_pt->size();
			
			////////////////////////////////////////////////////////////////////
			if(nMus!=2) _FATAL("nMus!=2 (in the null-isolation selection)"); ///
			////////////////////////////////////////////////////////////////////
			
			if(nMus<2) return;
			else if(nMus==2)
			{
				ca = recon_all_charge->at(0);
				cb = recon_all_charge->at(1);
				isoppositecharge = (ca*cb<0.) ? true : false;
				if(!isoppositecharge) return;
				ai = 0;
				bi = 1;
			}
			else
			{			
				for(unsigned int mu=0 ; mu<nMus ; mu++) pTtoIndexMap.insert( make_pair(recon_all_pt->at(mu),mu) );
				TMapdi::reverse_iterator rit=pTtoIndexMap.rbegin();
				ai = rit->second;
				rit++;
				bi = rit->second;
				isoppositecharge = (recon_all_charge->at(ai)*recon_all_charge->at(bi)<0.) ? true : false;
				while(!isoppositecharge  &&  rit!=pTtoIndexMap.rend())
				{
					rit++;
					bi = rit->second;
					isoppositecharge = (recon_all_charge->at(ai)*recon_all_charge->at(bi)<0.) ? true : false;
				}
				if(!isoppositecharge) return;
			}
			if(ai==bi || ai<0 || bi<0) return;
			tlvmureca->SetPtEtaPhiM(recon_all_pt->at(ai), recon_all_eta->at(ai), recon_all_phi->at(ai), muonMass);
			tlvmurecb->SetPtEtaPhiM(recon_all_pt->at(bi), recon_all_eta->at(bi), recon_all_phi->at(bi), muonMass);
			tlvmurecaBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmureca);
			tlvmurecbBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmurecb);
			(*tv3murecaBoosted) = tlvmurecaBoosted->Vect();
			(*tv3murecbBoosted) = tlvmurecbBoosted->Vect();
			mass = fkinematics::imass(tlvmureca,tlvmurecb);
			if(mass<70.) return;
			
			iso30a = (recon_all_pt->at(ai)!=0.) ? recon_all_ptcone30->at(ai)/recon_all_pt->at(ai) : -999.;
			iso30b = (recon_all_pt->at(bi)!=0.) ? recon_all_ptcone30->at(bi)/recon_all_pt->at(bi) : -999.;
			
			h1Map["hIsolationFull"+tsMCname]->Fill(iso30a,wgt*event_weight_nopileup/*event_weight*/);
			h1Map["hIsolationLow"+tsMCname]->Fill(iso30a,wgt*event_weight_nopileup/*event_weight*/);

			h1Map["hIsolationFull"+tsMCname]->Fill(iso30b,wgt*event_weight_nopileup/*event_weight*/);
			h1Map["hIsolationLow"+tsMCname]->Fill(iso30b,wgt*event_weight_nopileup/*event_weight*/);
			
			if((iso30a>=0.1 && iso30a<=1.) && (iso30b>=0.1 && iso30b<=1.)) // fill the invariant mass distribution of anti isolated pairs
			{
				h1Map["hMassAntiIsolated"+tsMCname]->Fill(mass,wgt*event_weight_nopileup/*event_weight*/);
			}
			
			/*
			for(unsigned int mu=0 ; mu<nMus ; mu++)
			{
				iso30 = (recon_all_pt->at(mu)!=0.) ? recon_all_ptcone30->at(mu)/recon_all_pt->at(mu) : -999.;
				h1Map["hIsolationFull"+tsMCname]->Fill(iso30,wgt*event_weight);
				h1Map["hIsolationLow"+tsMCname]->Fill(iso30,wgt*event_weight);
			}
			*/
		}
	}
	else if(tsRunType=="Data")
	{
		unsigned int nMus = pt->size();
		
		////////////////////////////////////////////////////////////////////
		if(nMus!=2) _FATAL("nMus!=2 (in the null-isolation selection)"); ///
		////////////////////////////////////////////////////////////////////
		
		if(nMus<2) return;
		else if(nMus==2)
		{
			ca = charge->at(0);
			cb = charge->at(1);
			isoppositecharge = (ca*cb<0.) ? true : false;
			if(!isoppositecharge) return;
			ai = 0;
			bi = 1;
		}
		else
		{			
			for(unsigned int mu=0 ; mu<nMus ; mu++) pTtoIndexMap.insert( make_pair(pt->at(mu),mu) );
			TMapdi::reverse_iterator rit=pTtoIndexMap.rbegin();
			ai = rit->second;
			rit++;
			bi = rit->second;
			isoppositecharge = (charge->at(ai)*charge->at(bi)<0.) ? true : false;
			while(!isoppositecharge  &&  rit!=pTtoIndexMap.rend())
			{
				rit++;
				bi = rit->second;
				isoppositecharge = (charge->at(ai)*charge->at(bi)<0.) ? true : false;
			}
			if(!isoppositecharge) return;
		}
		if(ai==bi || ai<0 || bi<0) return;
		tlvmureca->SetPtEtaPhiM(pt->at(ai)*MeV2GeV, eta->at(ai), phi->at(ai), muonMass);
		tlvmurecb->SetPtEtaPhiM(pt->at(bi)*MeV2GeV, eta->at(bi), phi->at(bi), muonMass);
		tlvmurecaBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmureca);
		tlvmurecbBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmurecb);
		(*tv3murecaBoosted) = tlvmurecaBoosted->Vect();
		(*tv3murecbBoosted) = tlvmurecbBoosted->Vect();
		mass = fkinematics::imass(tlvmureca,tlvmurecb);
		if(mass<70.) return;
		
		iso30a = (pt->at(ai)!=0.) ? ptcone30->at(ai)/pt->at(ai) : -999.;
		iso30b = (pt->at(bi)!=0.) ? ptcone30->at(bi)/pt->at(bi) : -999.;
		h1Map["hIsolationFull"+tsRunType]->Fill(iso30a,wgt);
		h1Map["hIsolationLow"+tsRunType]->Fill(iso30a,wgt);
		
		h1Map["hIsolationFull"+tsRunType]->Fill(iso30b,wgt);
		h1Map["hIsolationLow"+tsRunType]->Fill(iso30b,wgt);
		
		if((iso30a>=0.1 && iso30a<=1.) && (iso30b>=0.1 && iso30b<=1.)) // fill the invariant mass distribution of anti isolated pairs
		{
			// wgt = 0.0006;
			h1Map["hMassAntiIsolated"+tsRunType]->Fill(mass,wgt);
		}
		
		/*
		for(unsigned int mu=0 ; mu<pt->size() ; mu++)
		{
			iso30 = (pt->at(mu)!=0.) ? ptcone30->at(mu)/pt->at(mu) : -999.;
			h1Map["hIsolationFull"+tsRunType]->Fill(iso30,wgt);
			h1Map["hIsolationLow"+tsRunType]->Fill(iso30,wgt);
		}
		*/
	}
}

void hfill(TString tsRunType="", TString tsMCname="", Double_t wgt=1.)
{
	_DEBUG("hfill");
	
	float mass = 0.;
	float yQ   = 0.;
	float QT   = 0.;
	float etaQ = 0.;
	float cosThetaCS = 0.;
	float cosThetaHE = 0.;
	// float dr1  = 0.;
	// float dr2  = 0.;
	float ca   = 0.;
	float cb   = 0.;
	float etaLeading = 0.;
	float etaSubleading = 0.;
	float phiLeading = 0.;
	float phiSubleading = 0.;
	float pTLeading = 0.;
	float pTSubleading = 0.;
	float dEta = 0.;
	float iso30Leading = 0.;
	float iso30Subleading = 0.;
	
	float truth_mass = 0.;
	float truth_s    = 0.;
	float truth_cost = 0.;
	unsigned int truth_idIn = 0;
	unsigned int idOut      = 13; // muon
	double KKoverSM_weight     = 0.;
	double ZPoverSM_weight     = 0.;
	double KKnoSMoverSM_weight = 0.;
	double ZPnoSMoverSM_weight = 0.;
	
	int imuontru  = -999;
	int iamuontru = -999;
	int imuonrec  = -999;
	int iamuonrec = -999;
	
	int iquark  = -999;
	int iaquark = -999;
	
	unsigned int truXid = 0;
	double truXmass  = 0.;
	double truXpT    = 0.;
	// double ZpTweight = 1.;
	
	// double kFQCD_NNLOvLOss = 1.;
	// double kFEW_NNLOvLOs   = 1.;
	
	// float event_weight_backgrounds = 1.;
	// float event_weight_signals     = 1.;
	
	if(tsRunType=="MC")
	{
		if(truth_all_isValid)
		{
			if(!tsMCname.Contains("W+jets")) // there may be only one tru muon in AlpgenJimmy !!!
			{
				imuontru  = (truth_all_mc_pdgId->at(0)>0) ? 0 : 1;
				iamuontru = (imuontru==0) ? 1 : 0;
				tlvmutrua->SetPtEtaPhiM(truth_all_mc_pt->at(imuontru),  truth_all_mc_eta->at(imuontru),  truth_all_mc_phi->at(imuontru),  muonMass);
				tlvmutrub->SetPtEtaPhiM(truth_all_mc_pt->at(iamuontru), truth_all_mc_eta->at(iamuontru), truth_all_mc_phi->at(iamuontru), muonMass);
				(*tv3mutrua) = tlvmutrua->Vect();
				(*tv3mutrub) = tlvmutrub->Vect();
				tlvmutruaBoosted = fkinematics::Boost(tlvmutrua,tlvmutrub,tlvmutrua);
				tlvmutrubBoosted = fkinematics::Boost(tlvmutrua,tlvmutrub,tlvmutrub);
				(*tv3mutruaBoosted) = tlvmutruaBoosted->Vect();
				(*tv3mutrubBoosted) = tlvmutrubBoosted->Vect();
				mass          = fkinematics::imass(tlvmutrua,tlvmutrub);
				pTLeading     = truth_all_mc_pt->at(imuontru);
			}
			_DEBUG("");
			
			if(tsMCname=="DYmumu") // the templates
			{
				// (1) take the true quark and the true muon and boost it to the cmf.
				// (2) calculate cos(theta*) between the muon and the quark
				// (3) get the quark id
				// (4) get the mass of the intermediate state (Z)
				// iquark = (truth_all_partons_mc_pdgId->at(0)>0) ? 0 : 1;
				// iaquark = (iquark==0) ? 1 : 0;
				iquark = (truth_all_partons_mc_pdgId->at(2)>0) ? 2 : 3; // incoming partons are written in enties 2 and 3 of the vectors "truth_all_partons_mc_*"
				iaquark = (iquark==2) ? 3 : 2;
				tlvqa->SetPtEtaPhiM(truth_all_partons_mc_pt->at(iquark), truth_all_partons_mc_eta->at(iquark), truth_all_partons_mc_phi->at(iquark),truth_all_partons_mc_m->at(iquark));
				tlvqb->SetPtEtaPhiM(truth_all_partons_mc_pt->at(iaquark), truth_all_partons_mc_eta->at(iaquark), truth_all_partons_mc_phi->at(iaquark),truth_all_partons_mc_m->at(iaquark));
				(*tv3qa) = tlvqa->Vect();
				(*tv3qb) = tlvqb->Vect();
				tlvqaBoosted = fkinematics::Boost(tlvqa,tlvqb,tlvqa);
				tlvqbBoosted = fkinematics::Boost(tlvqa,tlvqb,tlvqb);
				(*tv3qaBoosted) = tlvqaBoosted->Vect();
				(*tv3qbBoosted) = tlvqbBoosted->Vect();
			
				// bits for the KK weights
				tv3q->SetPtEtaPhi(tlvqaBoosted->Pt(),tlvqaBoosted->Eta(),tlvqaBoosted->Phi());
				tv3mu->SetPtEtaPhi(tlvmutruaBoosted->Pt(),tlvmutruaBoosted->Eta(),tlvmutruaBoosted->Phi());
				truth_cost = tv3q->Dot((*tv3mu))/(tv3q->Mag()*tv3mu->Mag()); // truth cos(theta*)
				truth_idIn = truth_all_partons_mc_pdgId->at(iquark);         // truth incoming flavor
				truth_mass = fkinematics::imass(tlvqa,tlvqb);                // truth gamma/Z mass
				//truth_mass = truth_all_partons_mc_m->at(4);                // truth gamma/Z mass
				if(fabs(truth_mass-truth_all_partons_mc_m->at(4))/sqrt(truth_all_partons_mc_m->at(4))>3.)
				{
					_WARNING("truth mass mismatch: M(qqbar)="+_s(truth_all_partons_mc_m->at(4))+", M(4->"+_s(truth_all_partons_mc_pdgId->at(4))+")="+_s(truth_mass));
				}
				truth_s = truth_mass*truth_mass;
				
				// X = Z/Z'/ZKK are always at index 4.
				truXid   = truth_all_partons_mc_pdgId->at(4);
				truXmass = truth_all_partons_mc_m->at(4)*GeV2MeV;
				truXpT   = truth_all_partons_mc_pt->at(4)*GeV2MeV;
			}
			
			_DEBUG("");
			
			//////////////////////////////////////////////////////
			//// weights handeling ///////////////////////////////
			weights(tsMCname, mass, truXid, truXmass, truXpT); ///
			//////////////////////////////////////////////////////
			
	
			_DEBUG("");
			
			
			if(tsMCname=="DYmumu" || tsMCname.Contains("Zprime") || tsMCname.Contains("ExtraDimsTEV"))
			{
				// the official samples
				h1Map["hMass"+tsMCname+"_truth"]->Fill(mass,wgt*event_weight);
				h1Map["hpTLeading"+tsMCname+"_truth"]->Fill(pTLeading,wgt*event_weight);
				h1Map["hMass_limit_"+tsMCname+"_truth"]->Fill(mass*GeV2TeV,wgt*event_weight);
			
				// the templates
				if(tsMCname=="DYmumu"  &&  !doIsolationStudy)
				{
					// simple templates (at the official Z' points)
					for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
					{
						if(M==1250.) continue;
						//////////////////////////////
						// propagate the KK mass /////
						setKKmass(M); ////////////////
						setZPmass(M); ////////////////
						//////////////////////////////
						TString massName = (TString)_s(M);
						
						KKoverSM_weight = weightKK(truth_cost,truth_s,truth_idIn,idOut);
						ZPoverSM_weight = weightZP(truth_cost,truth_s,truth_idIn,idOut);
						
						h1Map["hMassKK"+massName+"_template_truth"]->Fill(mass,wgt*event_weight_signals*KKoverSM_weight); // need to fluctuate this later
						h1Map["hMassZprime_SSM"+massName+"_template_truth"]->Fill(mass,wgt*event_weight_signals*ZPoverSM_weight); // need to fluctuate this later

						h1Map["hMass_limit_KK"+massName+"_template_truth"]->Fill(mass*GeV2TeV,wgt*event_weight_signals*KKoverSM_weight);
						h1Map["hMass_limit_Zprime_SSM"+massName+"_template_truth"]->Fill(mass*GeV2TeV,wgt*event_weight_signals*ZPoverSM_weight);

						h1Map["hpTLeadingKK"+massName+"_template_truth"]->Fill(pTLeading,wgt*event_weight_signals*KKoverSM_weight); // need to fluctuate this later
						h1Map["hpTLeadingZprime_SSM"+massName+"_template_truth"]->Fill(pTLeading,wgt*event_weight_signals*ZPoverSM_weight); // need to fluctuate this later
					}
					
					// limit templates
					if((doFullKKtemplates || doFullZPtemplates) && doTemplates  &&  !doIsolationStudy)
					{
						for(double M=mKKmmMin ; M<=mKKmmMax ; M+=dMKKmm)
						{
							//////////////////////////////
							// propagate the KK mass /////
							setKKmass(M); ////////////////
							setZPmass(M); ////////////////
							//////////////////////////////
							TString massName   = (TString)_s(M);
							
							_DEBUG("massName="+(string)massName);
							
							if(doFullKKtemplates)
							{
								KKnoSMoverSM_weight = weightKKnoSM(truth_cost,truth_s,truth_idIn,idOut);
								h1Map["hMass_truth_template_KK"+massName]->Fill(mass*GeV2TeV,wgt*event_weight_signals*KKnoSMoverSM_weight); // need to fluctuate this later
								maxKKwgt = (KKnoSMoverSM_weight>maxKKwgt) ? KKnoSMoverSM_weight : maxKKwgt;
							}
							else if(doFullZPtemplates)
							{
								ZPnoSMoverSM_weight = weightZPnoSM(truth_cost,truth_s,truth_idIn,idOut);
								h1Map["hMass_truth_template_Zprime_SSM"+massName]->Fill(mass*GeV2TeV,wgt*event_weight_signals*ZPnoSMoverSM_weight); // need to fluctuate this later
								maxZPwgt = (ZPnoSMoverSM_weight>maxZPwgt) ? ZPnoSMoverSM_weight : maxZPwgt;
							}
						}
					}
				} // end of templates 
			}

			_DEBUG("");
			
			if(recon_all_isValid)
			{
				imuonrec  = (recon_all_charge->at(0)<0.) ? 0 : 1;
				iamuonrec = (imuonrec==0) ? 1 : 0;

				/*
				tlvtmp->SetPtEtaPhiM(recon_all_pt->at(imuonrec), recon_all_eta->at(imuonrec), recon_all_phi->at(imuonrec), muonMass);
				dr1 = fkinematics::dR(tlvtmp,tlvmutrua);
				dr2 = fkinematics::dR(tlvtmp,tlvmutrub);
				imuonrec  = (dr1<=dr2) ? imuonrec : iamuonrec;
				iamuonrec = (imuonrec==0) ? 1 : 0;
				// if(dr1>dr2) _WARNING("dr1(recA,truA) > dr2(recA,truB)");
				*/
				
				tlvmureca->SetPtEtaPhiM(recon_all_pt->at(imuonrec),  recon_all_eta->at(imuonrec),  recon_all_phi->at(imuonrec),  muonMass);
				tlvmurecb->SetPtEtaPhiM(recon_all_pt->at(iamuonrec), recon_all_eta->at(iamuonrec), recon_all_phi->at(iamuonrec), muonMass);
				(*tv3mureca) = tlvmureca->Vect();
				(*tv3murecb) = tlvmurecb->Vect();
				tlvmurecaBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmureca);
				tlvmurecbBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmurecb);
				(*tv3murecaBoosted) = tlvmurecaBoosted->Vect();
				(*tv3murecbBoosted) = tlvmurecbBoosted->Vect();
			}
			
			_DEBUG("");
			////////////////////////////
			/// analysis statrs here ///
			////////////////////////////
			
			if(recon_all_isValid  &&  imuonrec>=0. && iamuonrec>=0.  &&  imuonrec!=iamuonrec)
			{
				ca = recon_all_charge->at(imuonrec);
				cb = recon_all_charge->at(iamuonrec);
				if(ca*cb>=0.) _WARNING("ca*cb>=0, skipping event");
				mass          = fkinematics::imass(tlvmureca,tlvmurecb);
				yQ            = fkinematics::ySystem(tlvmureca,tlvmurecb);
				QT            = fkinematics::QT(tlvmureca,tlvmurecb);
				etaQ          = fkinematics::etaSystem(tlvmureca,tlvmurecb);
				cosThetaCS    = fkinematics::cosThetaCollinsSoper(tlvmureca,ca,tlvmurecb,cb);
				cosThetaHE    = fkinematics::cosThetaBoost(tlvmureca,ca,tlvmurecb,cb);
				etaLeading    = recon_all_eta->at(0);
				etaSubleading = recon_all_eta->at(1);
				phiLeading    = recon_all_phi->at(0);
				phiSubleading = recon_all_phi->at(1);
				pTLeading     = recon_all_pt->at(0);
				pTSubleading  = recon_all_pt->at(1);
				dEta          = fabs(etaLeading-etaSubleading);
				iso30Leading    = (recon_all_pt->at(0)!=0.) ? recon_all_ptcone30->at(0)/recon_all_pt->at(0) : -999.;
				iso30Subleading = (recon_all_pt->at(1)!=0.) ? recon_all_ptcone30->at(1)/recon_all_pt->at(1) : -999.;
				
				// for the Z peak normalization
				if(grpx[tsMCname]->order <= 20) // sum only backgrounds
				{
					if(mass>=imasslogicbins[0]  &&  mass<=imasslogicbins[1]) nMCall70to110          += 1.*wgt*event_weight;
					if(mass>=imasslogicbins[0]  &&  mass<=imasslogicbins[1]) nMCall70to110_nopileup += 1.*wgt*event_weight_nopileup;
				}
				/////////////////////////////////
				/// MC histo fill statrs here ///
				/////////////////////////////////
				
				_DEBUG("");
				
				if(tsMCname=="DYmumu"  &&  !doIsolationStudy) // templates
				{
					// simple templates (at the official Z' points)
					for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
					{
						if(M==1250.) continue;
						//////////////////////////////
						// propagate the KK mass /////
						setKKmass(M); ////////////////
						setZPmass(M); ////////////////
						//////////////////////////////
						TString massName = (TString)_s(M);
						
						KKoverSM_weight = weightKK(truth_cost,truth_s,truth_idIn,idOut);
						ZPoverSM_weight = weightZP(truth_cost,truth_s,truth_idIn,idOut);
						
						h1Map["hMassKK"+massName+"_template"]->Fill(mass,wgt*event_weight_signals*KKoverSM_weight); // need to fluctuate this later
						h1Map["hMassZprime_SSM"+massName+"_template"]->Fill(mass,wgt*event_weight_signals*ZPoverSM_weight); // need to fluctuate this later
						
						h1Map["hpTLeadingKK"+massName+"_template"]->Fill(pTLeading,wgt*event_weight_signals*KKoverSM_weight); // need to fluctuate this later
						h1Map["hpTLeadingZprime_SSM"+massName+"_template"]->Fill(pTLeading,wgt*event_weight_signals*ZPoverSM_weight); // need to fluctuate this later
						
						h1Map["hMass_limit_KK"+massName+"_template"]->Fill(mass*GeV2TeV,wgt*event_weight_signals*KKoverSM_weight); // for the 1d limit
						h1Map["hMass_limit_Zprime_SSM"+massName+"_template"]->Fill(mass*GeV2TeV,wgt*event_weight_signals*ZPoverSM_weight); // for the 1d limit
					}
					
					// limit templates
					if((doFullKKtemplates || doFullZPtemplates)  &&  doTemplates  &&  !doIsolationStudy)
					{
						for(double M=mKKmmMin ; M<=mKKmmMax ; M+=dMKKmm)
						{
							//////////////////////////////
							// propagate the KK mass /////
							setKKmass(M); ////////////////
							setZPmass(M); ////////////////
							//////////////////////////////
							TString massName   = (TString)_s(M);
							
							if(doFullKKtemplates)
							{
								KKnoSMoverSM_weight = weightKKnoSM(truth_cost,truth_s,truth_idIn,idOut);
								h1Map["hMass_template_KK"+massName]->Fill(mass*GeV2TeV,wgt*event_weight_signals*KKnoSMoverSM_weight); // need to fluctuate this later
							}
							else if(doFullZPtemplates)
							{
								ZPnoSMoverSM_weight = weightZPnoSM(truth_cost,truth_s,truth_idIn,idOut);
								h1Map["hMass_template_Zprime_SSM"+massName]->Fill(mass*GeV2TeV,wgt*event_weight_signals*ZPnoSMoverSM_weight); // need to fluctuate this later
							}
						}
					}
				}
				
				h1Map["hNvxp_no_puwgt"+tsMCname]->Fill(recon_all_vxp_n,wgt*event_weight_nopileup);
				h1Map["hNvxp_with_puwgt"+tsMCname]->Fill(recon_all_vxp_n,wgt*event_weight);
				h1Map["hMassNumbers"+tsMCname]->Fill(mass,wgt*event_weight);
				h1Map["hMass"+tsMCname]->Fill(mass,wgt*event_weight);
				h1Map["hMass1GeV"+tsMCname]->Fill(mass,wgt*event_weight);
				h1Map["hIsolationFull"+tsMCname]->Fill(iso30Leading,wgt*event_weight);
				h1Map["hIsolationFull"+tsMCname]->Fill(iso30Subleading,wgt*event_weight); // same histogram for isolation !
				h1Map["hIsolationLow"+tsMCname]->Fill(iso30Leading,wgt*event_weight);
				h1Map["hIsolationLow"+tsMCname]->Fill(iso30Subleading,wgt*event_weight); // same histogram for isolation !
				h1Map["hyQ"+tsMCname]->Fill(yQ,wgt*event_weight);
				h1Map["hQT"+tsMCname]->Fill(QT,wgt*event_weight);
				h1Map["hEtaQ"+tsMCname]->Fill(etaQ,wgt*event_weight);
				h1Map["hEtaLeading"+tsMCname]->Fill(etaLeading,wgt*event_weight);
				h1Map["hEtaSubleading"+tsMCname]->Fill(etaSubleading,wgt*event_weight);
				h1Map["hPhiLeading"+tsMCname]->Fill(phiLeading,wgt*event_weight);
				h1Map["hPhiSubleading"+tsMCname]->Fill(phiSubleading,wgt*event_weight);
				h1Map["hpTLeading"+tsMCname]->Fill(pTLeading,wgt*event_weight);
				h1Map["hpTSubleading"+tsMCname]->Fill(pTSubleading,wgt*event_weight);
				h1Map["hMass_limit_"+tsMCname]->Fill(mass*GeV2TeV,wgt*event_weight); // for the 1d limit
				
				_DEBUG("");
				
				///// 2d
				h2Map["hMassCosThetaCS"+tsMCname]->Fill(mass,cosThetaCS,wgt*event_weight);
				h2Map["hMassyQ"+tsMCname]->Fill(mass,yQ,wgt*event_weight);
				_DEBUG("");
			}
		}
	}
	else if(tsRunType=="Data" || tsRunType=="QCD")
	{
		wgt = (tsRunType=="QCD") ? 0.0006 : 1.;
	
		imuonrec  = (charge->at(0)<0.) ? 0 : 1;
		iamuonrec = (imuonrec==0) ? 1 : 0;
		
		tlvmureca->SetPtEtaPhiM(pt->at(imuonrec)*MeV2GeV,  eta->at(imuonrec),  phi->at(imuonrec),  muonMass);
		tlvmurecb->SetPtEtaPhiM(pt->at(iamuonrec)*MeV2GeV, eta->at(iamuonrec), phi->at(iamuonrec), muonMass);
		(*tv3mureca) = tlvmureca->Vect();
		(*tv3murecb) = tlvmurecb->Vect();
		tlvmurecaBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmureca);
		tlvmurecbBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmurecb);
		(*tv3murecaBoosted) = tlvmurecaBoosted->Vect();
		(*tv3murecbBoosted) = tlvmurecbBoosted->Vect();
	
		////////////////////////////
		/// analysis statrs here ///
		////////////////////////////
	
		ca = charge->at(imuonrec);
		cb = charge->at(iamuonrec);
		if(ca*cb>=0.) _WARNING("ca*cb>=0, skipping event");
		mass          = fkinematics::imass(tlvmureca,tlvmurecb);
		yQ            = fkinematics::ySystem(tlvmureca,tlvmurecb);
		QT            = fkinematics::QT(tlvmureca,tlvmurecb);
		etaQ          = fkinematics::etaSystem(tlvmureca,tlvmurecb);
		cosThetaCS    = fkinematics::cosThetaCollinsSoper(tlvmureca,ca,tlvmurecb,cb);
		cosThetaHE    = fkinematics::cosThetaBoost(tlvmureca,ca,tlvmurecb,cb);
		etaLeading    = eta->at(0);
		etaSubleading = eta->at(1);
		phiLeading    = phi->at(0);
		phiSubleading = phi->at(1);
		pTLeading     = pt->at(0)*MeV2GeV;
		pTSubleading  = pt->at(1)*MeV2GeV;
		dEta  = fabs(etaLeading-etaSubleading);
		iso30Leading    = (pt->at(0)!=0.) ? ptcone30->at(0)/pt->at(0) : -999.;
		iso30Subleading = (pt->at(1)!=0.) ? ptcone30->at(1)/pt->at(1) : -999.;
		
		if(mass>=imasslogicbins[0]  &&  mass<=imasslogicbins[1]) nData70to110 += 1.;
		
		_DEBUG("");
		///////////////////////////////////
		/// DATA histo fill statrs here ///
		///////////////////////////////////
		h1Map["hNvxp_no_puwgt"+tsRunType]->Fill(vxp_n,wgt);
		h1Map["hNvxp_with_puwgt"+tsRunType]->Fill(vxp_n,wgt);
		h1Map["hMassNumbers"+tsRunType]->Fill(mass,wgt);
		h1Map["hMass"+tsRunType]->Fill(mass,wgt);
		h1Map["hMass1GeV"+tsRunType]->Fill(mass,wgt);
		h1Map["hIsolationFull"+tsRunType]->Fill(iso30Leading,wgt);
		h1Map["hIsolationFull"+tsRunType]->Fill(iso30Subleading,wgt); // same histo for isolation
		h1Map["hIsolationLow"+tsRunType]->Fill(iso30Leading,wgt);
		h1Map["hIsolationLow"+tsRunType]->Fill(iso30Subleading,wgt); // same histo for isolation
		h1Map["hyQ"+tsRunType]->Fill(yQ,wgt);
		h1Map["hQT"+tsRunType]->Fill(QT,wgt);
		h1Map["hEtaQ"+tsRunType]->Fill(etaQ,wgt);
		h1Map["hEtaLeading"+tsRunType]->Fill(etaLeading,wgt);
		h1Map["hEtaSubleading"+tsRunType]->Fill(etaSubleading,wgt);
		h1Map["hPhiLeading"+tsRunType]->Fill(phiLeading,wgt);
		h1Map["hPhiSubleading"+tsRunType]->Fill(phiSubleading,wgt);
		h1Map["hpTLeading"+tsRunType]->Fill(pTLeading,wgt);
		h1Map["hpTSubleading"+tsRunType]->Fill(pTSubleading,wgt);
		h1Map["hMass_limit_"+tsRunType]->Fill(mass*GeV2TeV,wgt); // for the 1d limit
		
		///// 2d
		h2Map["hMassCosThetaCS"+tsRunType]->Fill(mass,cosThetaCS,wgt);
		h2Map["hMassyQ"+tsRunType]->Fill(mass,yQ,wgt);
		
		_DEBUG("");
	}
}

void init(TTree* t=NULL, TString name="")
{
	_DEBUG("init");

	if(t==NULL && name !="") // data or QCD
	{
		if(name=="Data")
		{
			setDATAtree("Data");
			setDATAbranches();
			_DEBUG("successfully fetched data tree");
		}
		else if(name=="QCD")
		{
			setDATAtree("QCD");
			setDATAbranches();
			_DEBUG("successfully fetched QCD tree");
		}
		else _FATAL("name should be Data or QCD");
	}
	else // mc
	{
		tree = t;
		setMCbranches();
		_DEBUG("successfully fetched MC tree");
	}
}

void writeTemplates()
{
	_DEBUG("writeTemplates");
	
	// remember old dir
	TDirectory* olddir = gDirectory;
	TFile* fTemplates = NULL;
	
	TString fTemplatesName = "plots/";
	if(doFullKKtemplates)      fTemplatesName += "KK";
	else if(doFullZPtemplates) fTemplatesName += "ZP";
	else                       fTemplatesName += "XX";
	fTemplatesName += "_templates";
	fTemplatesName += fileNmaeSuffix();
	fTemplatesName += ".root";
	fTemplates = new TFile(fTemplatesName, "RECREATE");
	
	olddir->cd();
	TObjArray* templates_KK = new TObjArray;
	TObjArray* templates_KK_truth = new TObjArray;
	TObjArray* templates_ZP = new TObjArray;
	TObjArray* templates_ZP_truth = new TObjArray;

	unsigned int itemplate = 0;
	if(doFullKKtemplates)
	{
		for(double M=mKKmmMin ; M<=mKKmmMax ; M+=dMKKmm)
		{
			TString massName = (TString)_s(M);
			templates_KK->Add( (TH1D*)h1Map["hMass_template_KK"+massName]->Clone("") );
			templates_KK_truth->Add( (TH1D*)h1Map["hMass_truth_template_KK"+massName]->Clone("") );
			itemplate++;
		}
	}
	else if(doFullZPtemplates)
	{
		for(double M=mKKmmMin ; M<=mKKmmMax ; M+=dMKKmm)
		{
			TString massName = (TString)_s(M);
			templates_ZP->Add( (TH1D*)h1Map["hMass_template_Zprime_SSM"+massName]->Clone("") );
			templates_ZP_truth->Add( (TH1D*)h1Map["hMass_truth_template_Zprime_SSM"+massName]->Clone("") );
			itemplate++;
		}
	}
	else
	{
		for(TMapiTS::iterator it=grpx_ordered.begin() ; it!=grpx_ordered.end() ; ++it)
		{
			TString name  = it->second;
			TString title = grpx[name]->label+";m_{#mu#mu} TeV;Events";
			if(!name.Contains("KK")) continue;
			templates_KK->Add( (TH1D*)h1Map["hMass_limit_"+name]->Clone("") );
			templates_KK->At(itemplate)->Print();
			itemplate++;
		}
	}
	
	fTemplates->cd();
	
	if(doFullKKtemplates)
	{
		templates_KK->SetOwner(kTRUE);
		templates_KK->Write("template", TObject::kSingleKey);
		templates_KK_truth->SetOwner(kTRUE);
		templates_KK_truth->Write("truth_template", TObject::kSingleKey);
	}
	else if(doFullZPtemplates)
	{
		templates_ZP->SetOwner(kTRUE);
		templates_ZP->Write("template", TObject::kSingleKey);
		templates_ZP_truth->SetOwner(kTRUE);
		templates_ZP_truth->Write("truth_template", TObject::kSingleKey);
	}
	else
	{
		templates_KK->SetOwner(kTRUE);
		templates_KK->Write("template", TObject::kSingleKey);
	}
	
	fTemplates->cd();
	TH1D* hDYrec = (TH1D*)h1Map["hMass_limit_DYmumu"]->Clone("");
	TH1D* hDYtru = (TH1D*)h1Map["hMass_limit_DYmumu_truth"]->Clone("");
	TH1D* hBGsum = (TH1D*)h1Map["hMass_limit_MCsum"]->Clone("");
	TH1D* hData  = (TH1D*)h1Map["hMass_limit_Data"]->Clone("");
	hDYrec->Write();
	hDYtru->Write();
	hBGsum->Write();
	hData->Write();
	
	fTemplates->Write();
	fTemplates->Close();
}

void monitor(TString name, Int_t entry, Int_t N)
{
	if(entry%printmod==0) cout << name << ": progress " << setprecision(2) << fixed << (float)entry/(float)N*100. << "%\r" << flush;
}

void runMCproc(TString mcName)
{
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		init(it->second);		
		Int_t N = tree->GetEntriesFast();
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			
			////////////////////////////////////////////
			//// blocks of analysis go here ////////////
			////////////////////////////////////////////
			if(mcName=="DYmumu"                   &&
			   it->first=="mcLocalControl_Zmumu"  &&
			   truth_all_Mhat>250.) continue;
			
			if(!truth_all_isValid && !doIsolationStudy) continue;			
			if(doIsolationStudy) hfill_isoStudy("MC", mcName, getFlatLumiWeight(it->first)); ////
			else                 hfill("MC", mcName, getFlatLumiWeight(it->first)); /////////////			
			/////////////////////////////////////////////////////////////////////////////////////
			
			monitor(mcName,entry,N);
		}		
		_INFO((string)it->first+": done.");
	}
}

void printMassBins()
{
	vector<Double_t> vN(imasslogicnbins,0.);
	cout << "\t" << "bins ";
	for(int bin=0 ; bin<(int)imasslogicnbins ; bin++)
	{
		cout << setprecision(0) << fixed << imasslogicbins[bin] << "-" << imasslogicbins[bin+1] << "  ";
	}
	cout << endl;
	cout << "--------------------------------------" << endl;
	for(TMapiTS::iterator it=grpx_ordered.begin() ; it!=grpx_ordered.end() ; ++it)
	{
		int order    = it->first;
		TString name = it->second;
		if(order>20  &&  !name.Contains("MCsum")) continue; // only backgrounds, total bg's and data
		if(name.Contains("DYtautau"))             continue; // DYtautau is part of DYmumu
		cout << "\t" << name << "  ";
		for(Int_t bin=1 ; bin<=h1Map["hMassNumbers"+name]->GetNbinsX() ; bin++)
		{
			Double_t N = h1Map["hMassNumbers"+name]->GetBinContent(bin);
			if(!name.Contains("Data") &&  !name.Contains("MCsum")) vN[bin-1]+=N;
			cout << setprecision(2) << fixed << N << "  ";
		}
		cout << endl;
	}
	cout << "--------------------------------------" << endl;
	cout << "\t" << "total bg  ";
	for(int bin=0 ; bin<(int)imasslogicnbins ; bin++)
	{
		cout << setprecision(2) << fixed << vN[bin] << "  ";
	}
	cout << endl;
}

void printNumbers()
{
	_INFO("zpeak ratio with pileup = "+_s(zpeak_ratio_with_pileup));
	_INFO("zpeak ratio no pileup   = "+_s(zpeak_ratio_no_pileup));
	_INFO("maxKKwgt = "+_s(maxKKwgt));
	_INFO("maxZPwgt = "+_s(maxZPwgt));
}

void run()
{
	msglvl[DBG] = SILENT; // SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	_DEBUG("run");
	
	///////////////////////////////////////////////
	// theoretical stuff... ///////////////////////
	setFermions(); ////////////////////////////////
	setkFactors(doEWkfactor && doEWkfactorSig); ///
	resetKKmass();/////////////////////////////////
	resetZPmass(); ////////////////////////////////
	setCouplingsScale(doCouplingsScale); //////////
	resetfgZP(); //////////////////////////////////
	resetfgGKK(); /////////////////////////////////
	resetfgZKK(); /////////////////////////////////
	///////////////////////////////////////////////
	
	matchFlags();
	style();
	samples();
	hbook();
	text();


	//// data
	if(doData)
	{
		init(NULL,"Data");
		Int_t N = tree->GetEntriesFast();
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			if(doIsolationStudy) hfill_isoStudy("Data");
			else                 hfill("Data");			
			monitor("Data",entry,N);
		}
		_INFO("Data: done.");
	}
	
	//// QCD
	if(doQCD && !doIsolationStudy)
	{
		init(NULL,"QCD");
		Int_t N = tree->GetEntriesFast();
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			hfill("QCD");			
			monitor("QCD",entry,N);
		}
		_INFO("QCD: done.");
	}
	
	
	//---- MCs
	for(TMapiTS::iterator it=grpx_ordered.begin() ; it!=grpx_ordered.end() ; ++it)
	{
		int order    = it->first;
		TString name = it->second;
		if(name=="Data")     continue; // data is handeled separately
		if(name=="QCD")      continue; // QCD is handeled separately
		if(name=="MCsum")    continue; // MCsum is handeled separately

		_INFO((string)name+" -> starting");
		setMCtrees(name);
		runMCproc(name);
		_INFO((string)name+" -> finished");
		
		if(name.Contains("DYtautau")) hMCsumDY(name); // DYtautau is part of DYmumu
		if(order<nMaxBGs && !name.Contains("DYtautau")) hMCsumall(name); // sum only BGs (order==nMaxBGs is data) and skip DYtautau that is included in DYmumu		
	}
	if(!doIsolationStudy)
	{
		hMCsumall("QCD");
		_INFO("summing -> QCD");
	}
	
	// finalize
	if(doData && doScale2Zpeak && !doIsolationStudy) hscale2Zpeak(); // must come before hdraw.
	if((doFullKKtemplates || doFullZPtemplates) && doTemplates  &&  !doIsolationStudy) writeTemplates();
	hdraw();
	save("plots");
	if(!doIsolationStudy) printNumbers();
	if(!doIsolationStudy) printMassBins();
}
