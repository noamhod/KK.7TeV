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


///////////////////////////////////////
// selectors //////////////////////////
///////////////////////////////////////
TString ntupledir      = "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/data"; // "/data/hod/2011/NTUPLE";
bool doData            = false;
bool doDYtautau        = false;
bool fastDYmumu        = true;
bool largeDYmumu       = false;
bool drawGmm           = false;
bool doFullKKtemplates = false;
bool doFullZPtemplates = true;
Int_t printmod         = 5000;
Bool_t dolog           = true;
bool dopileup          = true;
bool doEWkfactor       = true;
bool doQCDkfactor      = true;
///////////////////////////////////////

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
vector<unsigned short>* allauthor;
vector<int>* author;
vector<float>* beta;
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
		if(order>=20) continue; // only BGs !
		if(name=="DYtautau") continue; // DYtautau is part of DYmumu
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

void templateText(TString tsMCname, bool isTruth, Bool_t isTmplate=false)
{
	_DEBUG("templateText");
	
	if(leg_template==NULL)
	{
		leg_template = new TLegend(0.60,0.70,0.85,0.87,NULL,"brNDC");
		leg_template->SetFillStyle(4000); //will be transparent
		leg_template->SetFillColor(0);
		leg_template->SetTextFont(42);
	}
	else leg_template->Clear();
	
	TString ZPname         = tsMCname;
	TString KKtemplateName = getTemplateName(tsMCname,"KK");
	TString ZPtemplateName = getTemplateName(tsMCname);
	TString massNmae = getTemplateBareTitle(tsMCname);
	
	TString legTitle = "";
	
	legTitle = "DY "+(isTruth)?"tru":"rec";
	leg_template->AddEntry(h1Map["hMassDYmumu_truth"],legTitle,"f");
	
	if(isTmplate)
	{
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
		legTitle = "Z'_{SSM} "+massNmae+" GeV Pythia8 ";
		legTitle += (isTruth)?"tru":"rec";
		leg_template->AddEntry(h1Map[tsMCname],legTitle,"f");
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
	cnvMap[oName]->cd();
	tobj->Draw(drawopt);
	cnvMap[oName]->RedrawAxis();
	cnvMap[oName]->Update();
}

void drawratio(TH1* th1n, TH1* th1d, vector<TString>& vtsMCbgds, TString drawopt_n="", TString drawopt_d="", Bool_t logx=!dolog, Bool_t logy=!dolog)
{
	_DEBUG("draw");

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
	hr->Draw("e1x1");
	linMap[lName]->Draw("SAMES");
	cnvMap[hName]->Update();
	tvp_ratio->RedrawAxis();
}

void drawon(TString existing_oName, TObject* tobj, TString drawopt="", Int_t padNumber=-1)
{
	_DEBUG("drawon");
	_DEBUG("existing_oName = "+(string)existing_oName);
	
	if(padNumber<1) cnvMap[existing_oName]->cd();
	else            cnvMap[existing_oName]->cd(padNumber);
	
	if(drawopt=="") tobj->Draw("SAMES");
	else            tobj->Draw(drawopt+" SAMES");
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
	if(!dopileup)     pdfName += "_nopileup";
	if(!doEWkfactor)  pdfName += "_noEWkFactor";
	if(!doQCDkfactor) pdfName += "_noQCDkFactor";
	pdfName += ".pdf";
	unsigned int mapcount = 0;
	unsigned int mapsize  = cnvMap.size();
	for(TMapTSP2TCNV::iterator it=cnvMap.begin() ; it!=cnvMap.end() ; ++it)
	{
		mapcount++;
		TString pName = oDir+"/mcdata_"+it->first;
		if(!dopileup)     pName += "_nopileup";
		if(!doEWkfactor)  pName += "_noEWkFactor";
		if(!doQCDkfactor) pName += "_noQCDkFactor";
		it->second->SaveAs(pName+".png");
		it->second->SaveAs(pName+".eps");
		it->second->SaveAs(pName+".pdf");
		it->second->SaveAs(pName+".root");
		it->second->SaveAs(pName+".C");
		
		pName = pdfName;
		if(it==cnvMap.begin()) pName = pdfName+"(";
		if(mapcount==mapsize)  pName = pdfName+")";
		it->second->SetTitle(it->first);
		it->second->SaveAs(pName);
		it->second->SetTitle("");
	}
	
	_INFO("save all histograms (to a single .root file)");
	TString pName = oDir+"/mcdata_histograms";
	if(!dopileup)     pName += "_nopileup";
	if(!doEWkfactor)  pName += "_noEWkFactor";
	if(!doQCDkfactor) pName += "_noQCDkFactor";
	pName += ".root";
	TFile* f = new TFile(pName,"RECREATE");
	f->cd();
	for(TMapTSP2TH1::iterator it=h1Map.begin() ; it!=h1Map.end() ; ++it) {_INFO("XXX: "+(string)it->first); it->second->Write();}
	for(TMapTSP2TH2::iterator it=h2Map.begin() ; it!=h2Map.end() ; ++it) {_INFO("XXX: "+(string)it->first); it->second->Write();}
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
	
	/*
	if(name=="mcLocalControl_Zmumu")
	{
		TFile* fZmumu = new TFile(ntupledir+"/mcLocalControl_Zmumu.root", "READ");
		TEventList* elist;
		TTree* ztree = (TTree*)fZmumu->Get("truth/truth_tree");
		ztree->SetEventList(0);
		ztree->Draw(">>elist","truth_all_Mhat<=250.");
		elist = (TEventList*)gDirectory->Get("elist");
		Double_t Ntru = elist->GetN();
		ztree->SetEventList(elist);
		_INFO("Ntru(m<=250 GeV) = "+_s(Ntru)+", Ninput="+_s(N));
		if(N!=Ntru)
		{
			_WARNING("setting N to N="+_s(Ntru)+" to get the correct luminosity");
			N = Ntru;
		}
		
		treMap.insert( make_pair(name, (TTree*)ztree->Clone("")) );
	}
	else treMap.insert( make_pair(name, (TTree*)file->Get("truth/truth_tree")->Clone("")) );
	*/
	treMap.insert( make_pair(name, (TTree*)file->Get("truth/truth_tree")->Clone("")) );
	flatLumiWgtMap.insert( make_pair(name, luminosity/(N/sigma)) );
	mcNeventsMap.insert( make_pair(name, N) );
	mcSigmaMap.insert( make_pair(name, sigma) );
	pathMap.insert( make_pair(name, fPath) );
}

void setDATAtree()
{
	_DEBUG("setDATAtree");
	
	fName = ntupledir+"/analysisLocalControl.root";
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
	grpx.insert( make_pair("Diboson",  new GRPX(proccount(counter),"Diboson",     kOrange-4,-1,  kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Diboson"]->order,"Diboson") );
	grpx.insert( make_pair("TTbar",    new GRPX(proccount(counter),"t#bar{t}",     kRed+1,-1,     kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["TTbar"]->order,"TTbar") );
	if(doDYtautau)
	{
		grpx.insert( make_pair("DYtautau", new GRPX(proccount(counter),"DY#tau#tau",  kRed-5,-1,     kBlack,1,1,  -1,-1,-1)));
		grpx_ordered.insert( make_pair(grpx["DYtautau"]->order,"DYtautau") );
	}
	
	counter = 20;
	grpx.insert( make_pair("Data", new GRPX(counter,"Data",   -1,-1,  -1,-1,-1,  kBlack,24,0.8)));
	grpx_ordered.insert( make_pair(grpx["Data"]->order,"Data") );
	
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
	
	counter = 200;
	grpx.insert( make_pair("Gmm_01_1750",  new GRPX(counter,"1750 GeV G*",  kViolet+1,-1,    kBlack,1,1,   -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Gmm_01_1750"]->order,"Gmm_01_1750") );
	grpx.insert( make_pair("Gmm_01_2000",  new GRPX(proccount(counter),"2000 GeV G*",  kViolet+6,-1,  kBlack,1,1,   -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Gmm_01_2000"]->order,"Gmm_01_2000") );
	grpx.insert( make_pair("Gmm_01_2250",  new GRPX(proccount(counter),"2250 GeV G*",  kViolet+10,-1,  kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Gmm_01_2250"]->order,"Gmm_01_2250") );
	
	// counter = 300;
	// grpx.insert( make_pair("Zprime_SSM500_template",  new GRPX(counter,"500 GeV Z'_{SSM} template",  -1,-1,    kOrange+10,1,2,  -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["Zprime_SSM500_template"]->order,"Zprime_SSM500_template") );
	// grpx.insert( make_pair("Zprime_SSM750_template",  new GRPX(proccount(counter),"750 GeV Z'_{SSM} template",  -1,-1,  kOrange+8,1,2,   -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["Zprime_SSM750_template"]->order,"Zprime_SSM750_template") );
	// grpx.insert( make_pair("Zprime_SSM1000_template",  new GRPX(proccount(counter),"1000 GeV Z'_{SSM} template",  -1,-1,  kOrange+8,1,2,   -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["Zprime_SSM1000_template"]->order,"Zprime_SSM1000_template") );
	// grpx.insert( make_pair("Zprime_SSM1500_template",  new GRPX(proccount(counter),"1500 GeV Z'_{SSM} template",  -1,-1,  kOrange+8,1,2,   -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["Zprime_SSM1500_template"]->order,"Zprime_SSM1500_template") );
	// grpx.insert( make_pair("Zprime_SSM1750_template",  new GRPX(proccount(counter),"1750 GeV Z'_{SSM} template",  -1,-1,  kOrange+5,1,2,   -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["Zprime_SSM1750_template"]->order,"Zprime_SSM1750_template") );
	// grpx.insert( make_pair("Zprime_SSM2000_template",  new GRPX(proccount(counter),"2000 GeV Z'_{SSM} template",  -1,-1,  kOrange+3,1,2,   -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["Zprime_SSM2000_template"]->order,"Zprime_SSM2000_template") );
	
	// counter = 400;
	// grpx.insert( make_pair("KK500_template",  new GRPX(counter,"500 GeV KK template",  -1,-1,    kGreen+4,1,2,  -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["KK500_template"]->order,"KK500_template") );
	// grpx.insert( make_pair("KK750_template",  new GRPX(proccount(counter),"750 GeV KK template",  -1,-1,  kGreen-1,1,2,   -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["KK750_template"]->order,"KK750_template") );
	// grpx.insert( make_pair("KK1000_template",  new GRPX(proccount(counter),"1000 GeV KK template",  -1,-1,  kGreen-1,1,2,   -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["KK1000_template"]->order,"KK1000_template") );
	// grpx.insert( make_pair("KK1500_template",  new GRPX(proccount(counter),"1500 GeV KK template",  -1,-1,  kGreen-1,1,2,   -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["KK1500_template"]->order,"KK1500_template") );
	// grpx.insert( make_pair("KK1750_template",  new GRPX(proccount(counter),"1750 GeV KK template",  -1,-1,  kGreen-1,1,2,   -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["KK1750_template"]->order,"KK1750_template") );
	// grpx.insert( make_pair("KK2000_template",  new GRPX(proccount(counter),"2000 GeV KK template",  -1,-1,  kGreen-8,1,2,   -1,-1,-1)));
	// grpx_ordered.insert( make_pair(grpx["KK2000_template"]->order,"KK2000_template") );
	
	counter = 500;
	grpx.insert( make_pair("Zprime_SSM_m2000",  new GRPX(counter,"2 TeV Z'_{SSM} with interference", kMagenta+1,-1,    kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["Zprime_SSM_m2000"]->order,"Zprime_SSM_m2000") );
	grpx.insert( make_pair("ExtraDimsTEV_m2000",  new GRPX(proccount(counter),"2 TeV #gamma_{KK}/Z_{KK} with interference", kMagenta-1,-1,  kBlack,1,1,   -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["ExtraDimsTEV_m2000"]->order,"ExtraDimsTEV_m2000") );
	
	counter = 1000;
	grpx.insert( make_pair("MCsum", new GRPX(counter,"#Sum MC",  -1,-1,  -1,-1,-1,  kRed,  20,0.8)));
	grpx_ordered.insert( make_pair(grpx["MCsum"]->order,"MCsum") );
}

void setMCtrees(TString tsMCname)
{
	_DEBUG("setMCtrees");
	
	////////////////
	clearMaps(); ///
	////////////////

	
	if(tsMCname=="DYmumu")
	{
		if(!largeDYmumu)
		{
			if(fastDYmumu)
			{
				setMCtree(ntupledir+"/mcLocalControl_DYmumu_75M120.root", "mcLocalControl_DYmumu_75M120", 20000, 7.9862E-01*nb2fb);
				setMCtree(ntupledir+"/mcLocalControl_DYmumu_120M250.root", "mcLocalControl_DYmumu_120M250", 20000, 8.5275E-03*nb2fb);
			}
			else setMCtree(ntupledir+"/mcLocalControl_Zmumu.root", "mcLocalControl_Zmumu", 4878990, 8.3470E-01*nb2fb); // need to do a cut to keep events only up to 250 GeV
			
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_250M400.root", "mcLocalControl_DYmumu_250M400", 20000, 4.1075E-04*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_400M600.root", "mcLocalControl_DYmumu_400M600", 20000, 6.6459E-05*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_600M800.root", "mcLocalControl_DYmumu_600M800", 20000, 1.1002E-05*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_800M1000.root", "mcLocalControl_DYmumu_800M1000", 20000, 2.6516E-06*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_1000M1250.root", "mcLocalControl_DYmumu_1000M1250", 20000, 8.9229E-07*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_1250M1500.root", "mcLocalControl_DYmumu_1250M1500", 20000, 2.3957E-07*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 20000, 7.3439E-08*nb2fb);    // !!!!!!!!!!!
			// setMCtree(ntupledir+"/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 99999, 7.3439E-08*nb2fb); // !!!!!!!!!!! 
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_1750M2000.root", "mcLocalControl_DYmumu_1750M2000", 20000, 2.4614E-08*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYmumu_M2000.root", "mcLocalControl_DYmumu_M2000", 20000, 1.4001E-08*nb2fb);
		}

		else
		{
			if(fastDYmumu)
			{
				setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_75M120.root", "mcLocalControl_Pythia6_DYmumu_75M120",   100000, 7.9836E-01*nb2fb);
				// setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_120M250.root", "mcLocalControl_Pythia6_DYmumu_120M250", 100000, 8.5304E-03*nb2fb);
				setMCtree(ntupledir+"/mcLocalControl_DYmumu_120M250.root", "mcLocalControl_DYmumu_120M250", 20000, 8.5275E-03*nb2fb); // this is the old DY !!!!!!
			}
			else setMCtree(ntupledir+"/mcLocalControl_Zmumu.root", "mcLocalControl_Zmumu", 4878990, 8.3470E-01*nb2fb); // need to do a cut to keep events only up to 250 GeV
			
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_250M400.root",   "mcLocalControl_Pythia6_DYmumu_250M400",   100000, 4.1004E-04*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_400M600.root",   "mcLocalControl_Pythia6_DYmumu_400M600",   100000, 6.6393E-05*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_600M800.root",   "mcLocalControl_Pythia6_DYmumu_600M800",   100000, 1.0955E-05*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_800M1000.root",  "mcLocalControl_Pythia6_DYmumu_800M1000",  100000, 2.6470E-06*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1000M1250.root", "mcLocalControl_Pythia6_DYmumu_1000M1250", 100000, 8.9015E-07*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1250M1500.root", "mcLocalControl_Pythia6_DYmumu_1250M1500", 100000, 2.3922E-07*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1500M1750.root", "mcLocalControl_Pythia6_DYmumu_1500M1750", 100000, 7.3439E-08*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1750M2000.root", "mcLocalControl_Pythia6_DYmumu_1750M2000", 100000, 2.4643E-08*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2000M2250.root", "mcLocalControl_Pythia6_DYmumu_2000M2250", 100000, 8.7619E-09*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2250M2500.root", "mcLocalControl_Pythia6_DYmumu_2250M2500", 100000, 3.2232E-09*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2500M2750.root", "mcLocalControl_Pythia6_DYmumu_2500M2750", 100000, 1.2073E-09*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2750M3000.root", "mcLocalControl_Pythia6_DYmumu_2750M3000", 100000, 4.4763E-10*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_M3000.root",     "mcLocalControl_Pythia6_DYmumu_M3000",     100000, 2.5586E-10*nb2fb);
		}
	}
	
	/*
	if(tsMCname=="DYtautau")
	{
		if(doDYtautau)
		{
			setMCtree(ntupledir+"/mcLocalControl_DYtautau_75M120.root", "mcLocalControl_DYtautau_75M120", 20000, 7.9494E-01*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYtautau_120M250.root", "mcLocalControl_DYtautau_120M250", 20000, 8.5494E-03*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYtautau_250M400.root", "mcLocalControl_DYtautau_250M400", 20000, 4.0995E-04*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYtautau_400M600.root", "mcLocalControl_DYtautau_400M600", 20000, 6.6406E-05*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYtautau_600M800.root", "mcLocalControl_DYtautau_600M800", 20000, 1.1002E-05*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYtautau_800M1000.root", "mcLocalControl_DYtautau_800M1000", 20000, 2.6510E-06*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYtautau_1000M1250.root", "mcLocalControl_DYtautau_1000M1250", 20000, 8.9229E-07*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYtautau_1250M1500.root", "mcLocalControl_DYtautau_1250M1500", 20000, 2.3996E-07*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYtautau_1500M1750.root", "mcLocalControl_DYtautau_1500M1750", 20000, 7.3305E-08*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYtautau_1750M2000.root", "mcLocalControl_DYtautau_1750M2000", 20000, 2.4613E-08*nb2fb);
			setMCtree(ntupledir+"/mcLocalControl_DYtautau_M2000.root", "mcLocalControl_DYtautau_M2000", 20000, 1.4001E-08*nb2fb);
		}
	}
	
	if(tsMCname=="TTbar")
	{
		setMCtree(ntupledir+"/mcLocalControl_T1_McAtNlo_Jimmy.root", "mcLocalControl_T1_McAtNlo_Jimmy", 999500, 1.4562E-01*nb2fb*5.4259E-01);
	}
	
	if(tsMCname=="Diboson")
	{
		setMCtree(ntupledir+"/mcLocalControl_WW_Herwig.root", "mcLocalControl_WW_Herwig", 2442266, 17487.); // AMI: 3.1106E-02*nb2fb*3.8947E-01
		setMCtree(ntupledir+"/mcLocalControl_WZ_Herwig.root", "mcLocalControl_WZ_Herwig", 239949,  5743.); // AMI: 1.1485E-02*nb2fb*3.1043E-01
		setMCtree(ntupledir+"/mcLocalControl_ZZ_Herwig.root", "mcLocalControl_ZZ_Herwig", 244999,  1271.); // AMI: 4.5721E-03*nb2fb*2.1319E-01
	}
	
	
	if(tsMCname=="Gmm_01_1750")
	{
		setMCtree(ntupledir+"/mcLocalControl_Gmm_01_1750.root", "mcLocalControl_Gmm_01_1750", 10000, 1.6320E-06*nb2fb);
	}
	if(tsMCname=="Gmm_01_2000")
	{
		setMCtree(ntupledir+"/mcLocalControl_Gmm_01_2000.root", "mcLocalControl_Gmm_01_2000", 10000, 5.8721E-07*nb2fb);
	}
	if(tsMCname=="Gmm_01_2250")
	{
		setMCtree(ntupledir+"/mcLocalControl_Gmm_01_2250.root", "mcLocalControl_Gmm_01_2250", 10000, 2.1381E-07*nb2fb);
	}
	*/
	

	if(tsMCname=="Zprime_SSM500")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM500.root", "mcLocalControl_Zprime_SSM500", 20000, 2.6071E-03*nb2fb);
	}
	if(tsMCname=="Zprime_SSM750")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM750.root", "mcLocalControl_Zprime_SSM750", 20000, 4.7349E-04*nb2fb);
	}
	if(tsMCname=="Zprime_SSM1000")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM1000.root", "mcLocalControl_Zprime_SSM1000", 20000, 1.2466E-04*nb2fb);
	}
	if(tsMCname=="Zprime_SSM1500")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM1500.root", "mcLocalControl_Zprime_SSM1500", 20000, 1.4380E-05*nb2fb);
	}
	if(tsMCname=="Zprime_SSM1750")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM1750.root", "mcLocalControl_Zprime_SSM1750", 20000, 5.6743E-06*nb2fb);
	}
	if(tsMCname=="Zprime_SSM2000")
	{
		setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM2000.root", "mcLocalControl_Zprime_SSM2000", 20000, 2.4357E-06*nb2fb);
	}
	
	if(tsMCname=="Zprime_SSM_m2000")
	{
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_120M450.root",   "mcLocalControl_Pythia8_ZprimeSSM_m2000_120M450",   40000, 7.9574E-03*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_450M850.root",   "mcLocalControl_Pythia8_ZprimeSSM_m2000_450M850",   10000, 3.8040E-05 *nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_850M1300.root",  "mcLocalControl_Pythia8_ZprimeSSM_m2000_850M1300",  10000, 1.7327E-06*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_1300M1800.root", "mcLocalControl_Pythia8_ZprimeSSM_m2000_1300M1800", 10000, 1.5144E-07*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_1800M2300.root", "mcLocalControl_Pythia8_ZprimeSSM_m2000_1800M2300", 10000, 1.0133E-06*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_2300M2800.root", "mcLocalControl_Pythia8_ZprimeSSM_m2000_2300M2800", 10000, 1.1455E-08*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_2800M3300.root", "mcLocalControl_Pythia8_ZprimeSSM_m2000_2800M3300", 10000, 7.0524E-10*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ZprimeSSM_m2000_mumu_M3300.root",     "mcLocalControl_Pythia8_ZprimeSSM_m2000_M3300",     10000, 6.6724E-11*nb2fb);
	}

	if(tsMCname=="ExtraDimsTEV_m2000")
	{
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_120M450.root",   "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_120M450",   40000, 7.7227E-03*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_450M850.root",   "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_450M850",   10000, 2.1906E-05*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_850M1300.root",  "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_850M1300",  10000, 2.0058E-07*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_1300M1800.root", "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_1300M1800", 10000, 1.3579E-06*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_1800M2300.root", "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_1800M2300", 10000, 9.4190E-06*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_2300M2800.root", "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_2300M2800", 10000, 4.7462E-08*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_2800M3300.root", "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_2800M3300", 10000, 2.9864E-10*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia8_ExtraDimsTEV_m2000_mumu_M3300.root",     "mcLocalControl_Pythia8_ExtraDimsTEV_m2000_M3300",     10000, 3.2102E-09*nb2fb);
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
	setLogBins(nlogfullimassbins,logfullimassmin,logfullimassmax,logfullimassbins);
	setLogBins(nloglimitimassbins, loglimitimassmin, loglimitimassmax, loglimitimassbins);
	setLogBins(nlogofficialimassbins,logofficialimassmin,logofficialimassmax,logofficialimassbins);
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
	if(doFullKKtemplates || doFullZPtemplates)
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
		h1Map.insert( make_pair("hEtaSubleading"+name, new TH1D("hEtaSubleading"+name,";#eta_{#mu}^{leading};Events",nEtabins,Etamin,Etamax)) );
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
		h1Map.insert( make_pair("hPhiSubleading"+name, new TH1D("hPhiSubleading"+name,";#phi_{#mu}^{leading};Events",nPhibins,Phimin,Phimax)) );
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
		h1Map.insert( make_pair("hpTSubleading"+name, new TH1D("hpTSubleading"+name,";p_{T}^{leading} GeV;Events",nsqrtofficialptbins,sqrtofficialptbins)) );
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
		
		if(name.Contains("Data")) continue;
		
		Scale(h1Map["hNvxp_no_puwgt"+name],ratio_nopileup);
		Scale(h1Map["hNvxp_with_puwgt"+name],ratio);
		
		Scale(h1Map["hMassNumbers"+name],ratio);
		Scale(h1Map["hMass"+name],ratio);
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
		if(name=="DYmumu" && (doFullKKtemplates || doFullZPtemplates))
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

void hMCsumall(TString tsMCname)
{
	h1Map["hNvxp_no_puwgtMCsum"]->Add(h1Map["hNvxp_no_puwgt"+tsMCname]);
	h1Map["hNvxp_with_puwgtMCsum"]->Add(h1Map["hNvxp_with_puwgt"+tsMCname]);
	h1Map["hMassNumbersMCsum"]->Add(h1Map["hMassNumbers"+tsMCname]);
	h1Map["hMassMCsum"]->Add(h1Map["hMass"+tsMCname]);	
	h1Map["hMass_limit_MCsum"]->Add(h1Map["hMass_limit_"+tsMCname]);
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

void hbgdraw(TString type, TString sufx="", bool dologx=false, bool dology=false)
{
	vector<TString> vtsMCbgds;
	for(TMapiTS::iterator it=grpx_ordered.begin() ; it!=grpx_ordered.end() ; ++it)
	{
		int order    = it->first;
		TString name = it->second;
		if(order>20) continue; // only backgrounds and data
		if(order==0)
		{
			vtsMCbgds.clear();
			setMinMax(h1Map[type+name+sufx],h1Map[type+"Data"+sufx],true);
			draw(h1Map[type+name+sufx], "", "", dologx, dology);
		}
		if(name!="Data")
		{
			drawon(type+grpx_ordered[0]+sufx, h1Map[type+name+sufx]);
			vtsMCbgds.push_back(type+name+sufx);
		}
		else drawon(type+grpx_ordered[0]+sufx, h1Map[type+"Data"+sufx], "e1x1");
	}
	drawtxton(type+grpx_ordered[0]+sufx);
	drawratio(h1Map[type+"Data"+sufx], h1Map[type+"MCsum"+sufx], vtsMCbgds, "e1x1", "", dologx, dology);
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
		if(name.Contains("Zprime")  || name.Contains("ExtraDimsTEV")) // both are drawn on top of the DYmumu
		{
			_INFO("drawing -> "+(string)name);
			
			if(name.Contains("_m2000"))
			{
				_INFO("name -> "+(string)name);
			
				for(int t=0 ; t<2 ; t++)
				{
					objname = "hMass"+name;
					if(t==0) objname += "_truth";
					refname = "hMassDYmumu";
					if(t==0) refname += "_truth";
					setMinMax(h1Map[refname],h1Map[objname],true);
					draw(h1Map[refname], objname, "", dolog, dolog); // the canvas will be named with the 2nd argument
					drawon(objname, h1Map[objname]);
					templateText(name, (t==0)?true:false, false);
					drawtemplatetxton(objname);
					_INFO("drawn -> "+(string)objname);
					
					objname = "hpTLeading"+name;
					if(t==0) objname += "_truth";
					refname = "hpTLeadingDYmumu";
					if(t==0) refname += "_truth";
					setMinMax(h1Map[refname],h1Map[objname],true);
					draw(h1Map[refname], objname, "", dolog, dolog); // the canvas will be named with the 2nd argument
					drawon(objname, h1Map[objname]);
					templateText(name, (t==0)?true:false, false);
					drawtemplatetxton(objname);
					_INFO("drawn -> "+(string)objname);
				}
			}
			else // if(!name.Contains("_m2000")) then this is the regular Zprime's and the corresponding Z'/KK templates - all are drawn on top of the DYmumu
			{
				_INFO("name -> "+(string)name);
			
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
						drawon(objname, h1Map[hname]);
					}
					templateText(name, (t==0)?true:false, true);
					drawtemplatetxton(objname);
					_INFO("drawn -> "+(string)objname);
					
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
						drawon(objname, h1Map[hname]);
					}
					templateText(name, (t==0)?true:false, true);
					drawtemplatetxton(objname);
					_INFO("drawn -> "+(string)objname);
				}
			}
		}
	}

	hbgdraw("hNvxp_no_puwgt");
	hbgdraw("hNvxp_with_puwgt");
	hbgdraw("hMassNumbers","",dolog,dolog);
	hbgdraw("hMass","",dolog,dolog);
	hbgdraw("hyQ");
	hbgdraw("hQT","",dolog,dolog);
	hbgdraw("hEtaQ");
	hbgdraw("hEtaLeading");
	hbgdraw("hEtaSubleading");
	hbgdraw("hPhiLeading");
	hbgdraw("hPhiSubleading");
	hbgdraw("hpTLeading","",dolog,dolog);
	hbgdraw("hpTSubleading","",dolog,dolog);
	
	
	///// 2d
	bool is2d = true;
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

void hfill(TString tsRunType="", TString tsMCname="", Double_t wgt=1.)
{
	_DEBUG("hfill");
	
	float mass = 0.;
	float yQ   = 0.;
	float QT   = 0.;
	float etaQ = 0.;
	float cosThetaCS = 0.;
	float cosThetaHE = 0.;
	float dr1  = 0.;
	float dr2  = 0.;
	float ca   = 0.;
	float cb   = 0.;
	float etaLeading = 0.;
	float etaSubleading = 0.;
	float phiLeading = 0.;
	float phiSubleading = 0.;
	float pTLeading = 0.;
	float pTSubleading = 0.;
	float dEta = 0.;
	
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
	
	float event_weight_backgrounds = 1.;
	float event_weight_signals     = 1.;
	
	if(tsRunType=="MC")
	{
		/////////////////////////
		/// weights handeling ///
		/////////////////////////
		
		// all weights
		event_weight_backgrounds = 1.;
		event_weight_signals     = 1.;
		
		bool isDY       = (tsMCname.Contains("DY")) ? true:false;
		bool isEWSignal = (tsMCname.Contains("Zprime") || tsMCname.Contains("ExtraDimsTEV")) ? true:false;
		bool isGSignal  = (tsMCname.Contains("Gmm")) ? true:false;
	
		event_weight_backgrounds = all_mcevent_weight;
		event_weight_backgrounds *= (dopileup)             ? all_pileup_weight      : 1.;
		event_weight_backgrounds *= (doEWkfactor  && isDY) ? all_EW_kfactor_weight  : 1.;
		event_weight_backgrounds *= (doQCDkfactor && isDY) ? all_QCD_kfactor_weight : 1.;
		
		event_weight_signals = all_mcevent_weight;
		event_weight_signals *= (dopileup)                   ? all_pileup_weight      : 1.;
		event_weight_signals *= (doQCDkfactor && !isGSignal) ? all_QCD_kfactor_weight : 1.;
		
		float event_weight = 1.;
		if(isEWSignal || isGSignal) event_weight = event_weight_signals;
		else                        event_weight = event_weight_backgrounds;
		float event_weight_nopileup = (!dopileup) ? event_weight : event_weight/all_pileup_weight;
	
		_DEBUG("");
	
		if(truth_all_isValid)
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
			}
			
			_DEBUG("");
			
			if(tsMCname=="DYmumu" || tsMCname.Contains("Zprime") || tsMCname.Contains("ExtraDimsTEV"))
			{
				// the official samples
				h1Map["hMass"+tsMCname+"_truth"]->Fill(mass,wgt*event_weight);
				h1Map["hpTLeading"+tsMCname+"_truth"]->Fill(pTLeading,wgt*event_weight);
				h1Map["hMass_limit_"+tsMCname+"_truth"]->Fill(mass*GeV2TeV,wgt*event_weight);
			
				// the templates
				if(tsMCname=="DYmumu")
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
						
						h1Map["hMassKK"+massName+"_template_truth"]->Fill(truth_mass,wgt*event_weight_signals*KKoverSM_weight); // need to fluctuate this later
						h1Map["hMassZprime_SSM"+massName+"_template_truth"]->Fill(truth_mass,wgt*event_weight_signals*ZPoverSM_weight); // need to fluctuate this later

						h1Map["hMass_limit_KK"+massName+"_template_truth"]->Fill(truth_mass*GeV2TeV,wgt*event_weight_signals*KKoverSM_weight);
						h1Map["hMass_limit_Zprime_SSM"+massName+"_template_truth"]->Fill(truth_mass*GeV2TeV,wgt*event_weight_signals*ZPoverSM_weight);

						h1Map["hpTLeadingKK"+massName+"_template_truth"]->Fill(pTLeading,wgt*event_weight_signals*KKoverSM_weight); // need to fluctuate this later
						h1Map["hpTLeadingZprime_SSM"+massName+"_template_truth"]->Fill(pTLeading,wgt*event_weight_signals*ZPoverSM_weight); // need to fluctuate this later
					}
					
					// limit templates
					if(doFullKKtemplates || doFullZPtemplates)
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
								h1Map["hMass_truth_template_KK"+massName]->Fill(truth_mass*GeV2TeV,wgt*event_weight_signals*KKnoSMoverSM_weight); // need to fluctuate this later
								maxKKwgt = (KKnoSMoverSM_weight>maxKKwgt) ? KKnoSMoverSM_weight : maxKKwgt;
							}
							else if(doFullZPtemplates)
							{
								ZPnoSMoverSM_weight = weightZPnoSM(truth_cost,truth_s,truth_idIn,idOut);
								h1Map["hMass_truth_template_Zprime_SSM"+massName]->Fill(truth_mass*GeV2TeV,wgt*event_weight_signals*ZPnoSMoverSM_weight); // need to fluctuate this later
								maxZPwgt = (ZPnoSMoverSM_weight>maxZPwgt) ? ZPnoSMoverSM_weight : maxZPwgt;
							}
						}
					}
				}
			}
			
			_DEBUG("");
			if(recon_all_isValid)
			{
				imuonrec  = (recon_all_charge->at(0)<0.) ? 0 : 1;
				iamuonrec = (imuonrec==0) ? 1 : 0;
				
				tlvtmp->SetPtEtaPhiM(recon_all_pt->at(imuonrec), recon_all_eta->at(imuonrec), recon_all_phi->at(imuonrec), muonMass);
				dr1 = fkinematics::dR(tlvtmp,tlvmutrua);
				dr2 = fkinematics::dR(tlvtmp,tlvmutrub);
				imuonrec  = (dr1<=dr2) ? imuonrec : iamuonrec;
				iamuonrec = (imuonrec==0) ? 1 : 0;
				// if(dr1>dr2) _WARNING("dr1(recA,truA) > dr2(recA,truB)");
				
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
				if(tsMCname=="DYmumu") // templates
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
					if(doFullKKtemplates || doFullZPtemplates)
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
	else if(tsRunType=="DATA")
	{
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
		
		if(mass>=imasslogicbins[0]  &&  mass<=imasslogicbins[1]) nData70to110 += 1.;
		
		_DEBUG("");
		
		///////////////////////////////////
		/// DATA histo fill statrs here ///
		///////////////////////////////////
		h1Map["hNvxp_no_puwgtData"]->Fill(vxp_n);
		h1Map["hNvxp_with_puwgtData"]->Fill(vxp_n);
		h1Map["hMassNumbersData"]->Fill(mass);
		h1Map["hMassData"]->Fill(mass);
		h1Map["hyQData"]->Fill(yQ);
		h1Map["hQTData"]->Fill(QT);
		h1Map["hEtaQData"]->Fill(etaQ);
		h1Map["hEtaLeadingData"]->Fill(etaLeading);
		h1Map["hEtaSubleadingData"]->Fill(etaSubleading);
		h1Map["hPhiLeadingData"]->Fill(phiLeading);
		h1Map["hPhiSubleadingData"]->Fill(phiSubleading);
		h1Map["hpTLeadingData"]->Fill(pTLeading);
		h1Map["hpTSubleadingData"]->Fill(pTSubleading);
		h1Map["hMass_limit_Data"]->Fill(mass*GeV2TeV); // for the 1d limit
		
		///// 2d
		h2Map["hMassCosThetaCSData"]->Fill(mass,cosThetaCS);
		h2Map["hMassyQData"]->Fill(mass,yQ);
		
		_DEBUG("");
	}
}

void init(TTree* t=NULL)
{
	_DEBUG("init");

	if(t==NULL) // data
	{
		setDATAtree();
		setDATAbranches();
		_DEBUG("successfully fetched data tree");
	}
	else // mc
	{
		tree = t;
		setMCbranches();
		_DEBUG("successfully fetched MC tree");
	}
}

void writeKKtemplates()
{
	// remember old dir
	TDirectory* olddir = gDirectory;
	TFile* fTemplates = NULL;
	if(doFullKKtemplates)      fTemplates = new TFile("plots/KK_templates.root", "RECREATE");
	else if(doFullZPtemplates) fTemplates = new TFile("plots/ZP_templates.root", "RECREATE");
	else                       fTemplates = new TFile("plots/XX_templates.root", "RECREATE");
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
			//int order     = it->first;
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
			   truth_all_isValid                  && 
			   recon_all_isValid                  && 
			   truth_all_Mhat>250.) continue;
			
			
			if(!truth_all_isValid) continue;
			// hfill("MC", mcName, flatLumiWgtMap[it->first]); ////
			hfill("MC", mcName, getFlatLumiWeight(it->first)); ////
			///////////////////////////////////////////////////////
			
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
	
	///////////////////////
	setFermions(); ////////
	setkFactors(false); ///
	///////////////////////
	
	style();
	samples();
	hbook();
	text();


	//// data
	if(doData)
	{
		init();
		Int_t N = tree->GetEntriesFast();
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			////////////////////////////////////
			//// blocks of analysis go here ////
			////////////////////////////////////
			hfill("DATA"); /////////////////////
			////////////////////////////////////
			
			monitor("Data",entry,N);
		}
		_INFO("Data: done.");
	}
	
	//---- MCs
	for(TMapiTS::iterator it=grpx_ordered.begin() ; it!=grpx_ordered.end() ; ++it)
	{
		int order    = it->first;
		TString name = it->second;
		_INFO((string)name+" -> starting");
		if(name=="Data")              continue; // data is handeled separately
		if(name=="MCsum")             continue; // MCsum is handeled separately
		if(name.Contains("template")) continue; // templates are made out of the DYmumu
		setMCtrees(name);
		runMCproc(name);
		if(order<20) hMCsumall(name); // sum only BGs
		_INFO((string)name+" -> finished");
	}
	
	
	// finalize
	
	if(doData && (largeDYmumu && !fastDYmumu)) hscale2Zpeak(); // must come before hdraw.
	writeKKtemplates();
	hdraw();
	save("plots");
	printNumbers();
	printMassBins();
}
