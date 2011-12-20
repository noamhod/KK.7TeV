#include "all.h"

bool doLumiXSweights = false; //!!! // true if want to scale binned samples to 1 smooth sample and to scale MC to data luminosity. This affects mostly the errors
				
static const Int_t    nlogmassbins = nMassBins;
static const Double_t logmassmin   = minMassBin;
static const Double_t logmassmax   = maxMassBin;
static Double_t logmassbins[nlogmassbins+1];


int truth_entries = 0;

double   yqmin   = minyQ;
double   yqmax   = maxyQ;
int      nyqbins = nyQbins;

double costmin   = minCosTheta;
double costmax   = maxCosTheta;
int    ncostbins = nCosThetaBins;

bool truth_all_isValid;
vector<float>* truth_all_mc_pt;
vector<float>* truth_all_mc_m;
vector<float>* truth_all_mc_eta;
vector<float>* truth_all_mc_phi;
vector<int>*   truth_all_mc_status;
vector<int>*   truth_all_mc_barcode;
vector<int>*   truth_all_mc_pdgId;
vector<float>* truth_all_mc_charge;

vector<float>* truth_all_partons_mc_pt;
vector<float>* truth_all_partons_mc_m;
vector<float>* truth_all_partons_mc_eta;
vector<float>* truth_all_partons_mc_phi;
vector<int>*   truth_all_partons_mc_status;
vector<int>*   truth_all_partons_mc_barcode;
vector<int>*   truth_all_partons_mc_pdgId;
vector<float>* truth_all_partons_mc_charge;

bool recon_all_isValid;
vector<float>* recon_all_pt;
vector<float>* recon_all_m;
vector<float>* recon_all_eta;
vector<float>* recon_all_phi;
vector<float>* recon_all_charge;

TVector3*       tv3qa = new TVector3;
TLorentzVector* tlvqa = new TLorentzVector;
TLorentzVector* tlvqb = new TLorentzVector;
TLorentzVector* tlvqBoosted = new TLorentzVector;
TVector3*       tv3mua = new TVector3;
TVector3*       tv3b = new TVector3;
TLorentzVector* tlvmua = new TLorentzVector;
TLorentzVector* tlvmub = new TLorentzVector;
TLorentzVector* tlvmuaBoosted = new TLorentzVector;
TLorentzVector* tlvmubBoosted = new TLorentzVector;
TLorentzVector* tlvBoostVector = new TLorentzVector;
TVector3*       tv3BoostVector = new TVector3;
TMapTSd       wgtMap;
TMapTSP2TTREE treMap;
TTree* tree;
TText* txt;

vector<TH1D*> vhPyQ;
vector<TH1D*> vhPyQdenominator;
vector<TH1D*> vhAcceptance;
vector<TH1D*> vhAcceptanceDenominator;

void settree(TString fPath, TString name, Double_t N, Double_t sigma)
{
	_DEBUG("settree");
	
	TFile* f = new TFile(fPath,"READ");
	treMap.insert( make_pair(name, (TTree*)f->Get("truth/truth_tree")->Clone("")) );
	wgtMap.insert( make_pair(name, luminosity/(N/sigma)) );
}

void settrees()
{
	_DEBUG("settrees");

	treMap.clear();
	wgtMap.clear();
	// settree("../data/mcLocalControl_DYmumu_75M120.root", "mcLocalControl_DYmumu_75M120", 19996, 0.81705*nb2fb);
	settree("../data/mcLocalControl_DYmumu_120M250.root", "mcLocalControl_DYmumu_120M250", 19999, 0.0086861*nb2fb);
	settree("../data/mcLocalControl_DYmumu_250M400.root", "mcLocalControl_DYmumu_250M400", 19996, 0.00041431*nb2fb);
	settree("../data/mcLocalControl_DYmumu_400M600.root", "mcLocalControl_DYmumu_400M600", 19993, 0.000067464*nb2fb);
	settree("../data/mcLocalControl_DYmumu_600M800.root", "mcLocalControl_DYmumu_600M800", 15994, 0.000011168*nb2fb);
	settree("../data/mcLocalControl_DYmumu_800M1000.root", "mcLocalControl_DYmumu_800M1000", 19992, 0.0000027277*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1000M1250.root", "mcLocalControl_DYmumu_1000M1250", 19995, 0.00000091646*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1250M1500.root", "mcLocalControl_DYmumu_1250M1500", 19993, 0.00000024942*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 19997, 0.000000076876*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1750M2000.root", "mcLocalControl_DYmumu_1750M2000", 19993, 0.000000026003*nb2fb);
	settree("../data/mcLocalControl_DYmumu_M2000.root", "mcLocalControl_DYmumu_M2000", 19996, 0.000000015327*nb2fb);
}

void parseDYbinName(string name, Double_t& massbinlowedge, Double_t& massbinhighedge)
{
	string prefix = "mcLocalControl_DYmumu_";
	string::size_type loc = name.find("M");
	string high = name.substr(loc+1);
	string low = "";
	string chr = "";
	for(int i=(int)prefix.length() ; i<(int)loc ; i++)
	{
		chr = name[i];
		if(chr!="M") low+=chr;
	}
	if(low=="")
	{
		massbinlowedge  = logmassbins[nlogmassbins-1]; //2000.;
		massbinhighedge = logmassbins[nlogmassbins];   //maxMass;
		return;
	}
	massbinhighedge = validate_double(high);
	massbinlowedge  = validate_double(low);
}

void setbranches()
{
	_DEBUG("setbranches");

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
	
	recon_all_pt     = 0;
	recon_all_m      = 0;
	recon_all_eta    = 0;
	recon_all_phi    = 0;
	recon_all_charge = 0;

	tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
	tree->SetBranchAddress("truth_all_mc_pt",   &truth_all_mc_pt);
	tree->SetBranchAddress("truth_all_mc_m",    &truth_all_mc_m);
	tree->SetBranchAddress("truth_all_mc_eta",  &truth_all_mc_eta);
	tree->SetBranchAddress("truth_all_mc_phi",  &truth_all_mc_phi);
	tree->SetBranchAddress("truth_all_mc_status",  &truth_all_mc_status);
	tree->SetBranchAddress("truth_all_mc_barcode", &truth_all_mc_barcode);
	tree->SetBranchAddress("truth_all_mc_pdgId",   &truth_all_mc_pdgId);
	tree->SetBranchAddress("truth_all_mc_charge",  &truth_all_mc_charge);
	
	tree->SetBranchAddress("truth_all_partons_mc_pt",      &truth_all_partons_mc_pt);
	tree->SetBranchAddress("truth_all_partons_mc_m",       &truth_all_partons_mc_m);
	tree->SetBranchAddress("truth_all_partons_mc_eta",     &truth_all_partons_mc_eta);
	tree->SetBranchAddress("truth_all_partons_mc_phi",     &truth_all_partons_mc_phi);
	tree->SetBranchAddress("truth_all_partons_mc_status",  &truth_all_partons_mc_status);
	tree->SetBranchAddress("truth_all_partons_mc_barcode", &truth_all_partons_mc_barcode);
	tree->SetBranchAddress("truth_all_partons_mc_pdgId",   &truth_all_partons_mc_pdgId);
	tree->SetBranchAddress("truth_all_partons_mc_charge",  &truth_all_partons_mc_charge);
	
	tree->SetBranchAddress("recon_all_isValid", &recon_all_isValid);
	tree->SetBranchAddress("recon_all_pt",      &recon_all_pt);
	tree->SetBranchAddress("recon_all_m",       &recon_all_m);
	tree->SetBranchAddress("recon_all_eta",     &recon_all_eta);
	tree->SetBranchAddress("recon_all_phi",     &recon_all_phi);
	tree->SetBranchAddress("recon_all_charge",  &recon_all_charge);
	
	_DEBUG("successfully read mc branches");
}

void setLogBins(Int_t nbins, Double_t min, Double_t max, Double_t* xpoints)
{
	_DEBUG("setLogBins");

	Double_t logmin  = log10(min);
	Double_t logmax  = log10(max);
	Double_t logbinwidth = (Double_t)( (logmax-logmin)/(Double_t)nbins );
	xpoints[0] = min;
	for(Int_t i=1 ; i<=nbins ; i++) xpoints[i] = TMath::Power( 10,(logmin + i*logbinwidth) );
}

double getMassBinCenter(int massBin)
{
	return logmassbins[massBin-1]+(logmassbins[massBin]-logmassbins[massBin-1])/2.;
}

double getMassBinLowEdge(int massBin)
{
	_DEBUG("getMassBinLowEdge");
	return logmassbins[massBin-1];
}

double getMassBinHighEdge(int massBin)
{
	_DEBUG("getMassBinHighEdge");
	return logmassbins[massBin];
}

Int_t loop(int massBin)
{
	_DEBUG("loop");
	Int_t    N = 0;
	Double_t W = 1.;
	
	Double_t lowmasscut  = getMassBinLowEdge(massBin);
	Double_t highmasscut = getMassBinHighEdge(massBin);
	
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		tree = it->second;
		setbranches();
		N = tree->GetEntriesFast();
		W = wgtMap[it->first];
		_INFO("name = "+(string)it->first+" -> N="+_s(N));
		truth_entries = 0;
		
		float YQ = -999.;
		float mHat = -999.;
		float ca = -999.;
		float cb = -999.;
		float cost = -999.;
		
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			if(!truth_all_isValid) continue;
			
			int imuontru  = (truth_all_mc_pdgId->at(0)>0) ? 0 : 1;
			int iamuontru = (imuontru==0) ? 1 : 0;
			tlvmua->SetPtEtaPhiM(truth_all_mc_pt->at(imuontru),truth_all_mc_eta->at(imuontru),truth_all_mc_phi->at(imuontru),truth_all_mc_m->at(imuontru));
			tlvmub->SetPtEtaPhiM(truth_all_mc_pt->at(iamuontru),truth_all_mc_eta->at(iamuontru),truth_all_mc_phi->at(iamuontru),truth_all_mc_m->at(iamuontru));
			YQ   = ySystem(tlvmua,tlvmub);
			mHat = imass(tlvmua,tlvmub);
			
			Double_t massbinlowedge  = 0.;
			Double_t massbinhighedge = 0.;
			parseDYbinName((string)it->first,massbinlowedge,massbinhighedge);
			if(mHat<massbinlowedge || mHat>massbinhighedge) continue; // in this mass bin, do not take events from different DY mass bins
			
			if(mHat<lowmasscut || mHat>highmasscut)         continue; // to get the events in the relevant mass bin
			if(YQ>+2.5 || YQ<-2.5)                          continue; // to reject events that have no P(yQ) calculated
			
			ca    = truth_all_mc_charge->at(imuontru);
			cb    = truth_all_mc_charge->at(iamuontru);
			cost = cosThetaCollinsSoper(tlvmua,ca,tlvmub,cb);
			// double cost = cosThetaBoost(tlvmua,ca,tlvmub,cb);
			
			vhAcceptanceDenominator[massBin-1]->Fill(cost,W);
			
			int iquark = (truth_all_partons_mc_pdgId->at(0)>0) ? 0 : 1;
			int iaquark = (iquark==0) ? 1 : 0;
			tlvqa->SetPtEtaPhiM(truth_all_partons_mc_pt->at(iquark), truth_all_partons_mc_eta->at(iquark), truth_all_partons_mc_phi->at(iquark),truth_all_partons_mc_m->at(iquark));
			tlvqb->SetPtEtaPhiM(truth_all_partons_mc_pt->at(iaquark), truth_all_partons_mc_eta->at(iaquark), truth_all_partons_mc_phi->at(iaquark),truth_all_partons_mc_m->at(iaquark));
			
			// boost to the qqbar system rest frame
			// tlvqBoosted   = Boost(tlvqa,tlvqb,tlvqa); 
			// tlvmuaBoosted = Boost(tlvqa,tlvqb,tlvmua);
			
			// boost to the mu+mu- system rest frame
			tlvqBoosted   = Boost(tlvmua,tlvmub,tlvqa);
			tlvmuaBoosted = Boost(tlvmua,tlvmub,tlvmua);
			
			tv3qa->SetPtEtaPhi(tlvqBoosted->Pt(),tlvqBoosted->Eta(),tlvqBoosted->Phi());
			tv3mua->SetPtEtaPhi(tlvmuaBoosted->Pt(),tlvmuaBoosted->Eta(),tlvmuaBoosted->Phi());
			double costheta_mutru_quark = tv3qa->Dot((*tv3mua))/(tv3qa->Mag()*tv3mua->Mag());
			
			(*tlvBoostVector) = (*tlvqa)+(*tlvqb);
			(*tv3BoostVector) = tlvBoostVector->BoostVector();
			double cosalpha_beta_quark = tv3qa->Dot((*tv3BoostVector))/(tv3qa->Mag()*tv3BoostVector->Mag());
			if(cosalpha_beta_quark<=0.) vhPyQ[massBin-1]->Fill(YQ,W);
			vhPyQdenominator[massBin-1]->Fill(YQ,W);
			
			truth_entries++;
			
			
			
			/////////////////////////////
			/// reconstructed ///////////
			/////////////////////////////
			
			if(!recon_all_isValid) continue;
			
			int imuonrec  = (recon_all_charge->at(0)<0) ? 0 : 1;
			int iamuonrec = (imuonrec==0) ? 1 : 0;
			tlvmua->SetPtEtaPhiM(recon_all_pt->at(imuonrec),  recon_all_eta->at(imuonrec),  recon_all_phi->at(imuonrec),  recon_all_m->at(imuonrec));
			tlvmub->SetPtEtaPhiM(recon_all_pt->at(iamuonrec), recon_all_eta->at(iamuonrec), recon_all_phi->at(iamuonrec), recon_all_m->at(iamuonrec));
			YQ   = ySystem(tlvmua,tlvmub);
			mHat = imass(tlvmua,tlvmub);
			
			if(mHat<lowmasscut || mHat>highmasscut)         continue; // to get the events in the relevant mass bin
			if(YQ>+2.5 || YQ<-2.5)                          continue; // to reject events that have no P(yQ) calculated
			
			ca    = recon_all_charge->at(imuonrec);
			cb    = recon_all_charge->at(iamuonrec);
			cost = cosThetaCollinsSoper(tlvmua,ca,tlvmub,cb);
			// double cost = cosThetaBoost(tlvmua,ca,tlvmub,cb);
			
			vhAcceptance[massBin-1]->Fill(cost,W);
		}
		_INFO("truth_entries = "+_s(truth_entries));
	}
	
	vhPyQ[massBin-1]->Divide(vhPyQdenominator[massBin-1]);
	vhAcceptance[massBin-1]->Divide(vhAcceptanceDenominator[massBin-1]);
	
	return N;
}

void draw(int massBin)
{
	TString sMassBin = (TString)_s(massBin);
	
	TCanvas* cnvPyQ = new TCanvas("cPyQ_"+sMassBin, "", 600,400);
	cnvPyQ->SetFillColor(0);
	
	TCanvas* cnvAcc = new TCanvas("cAcc_"+sMassBin, "", 600,400);
	cnvAcc->SetFillColor(0);
	
	TPaveText* pvtxt_massbinname = new TPaveText(0.3277592,0.8056995,0.4916388,0.9002591,"brNDC");
	pvtxt_massbinname->SetFillColor(0);
	pvtxt_massbinname->SetTextFont(42);
	txt = pvtxt_massbinname->AddText("m_{#mu#mu}: "+(TString)_s(logmassbins[massBin-1])+"#rightarrow"+(TString)_s(logmassbins[massBin])+" GeV");
	
	/// P(yQ)
	cnvPyQ->cd();
	cnvPyQ->Draw();
	vhPyQ[massBin-1]->SetMarkerStyle(24);
	vhPyQ[massBin-1]->SetMarkerSize(1);
	vhPyQ[massBin-1]->Draw("e1x1");
	pvtxt_massbinname->Draw("SAMES");
	cnvPyQ->SaveAs("plots/PyQ_"+sMassBin+".png");
	cnvPyQ->SaveAs("plots/PyQ_"+sMassBin+".eps");
	cnvPyQ->SaveAs("plots/PyQ_"+sMassBin+".pdf");
	cnvPyQ->SaveAs("plots/PyQ_"+sMassBin+".ps");
	cnvPyQ->SaveAs("plots/PyQ_"+sMassBin+".root");
	cnvPyQ->SaveAs("plots/PyQ_"+sMassBin+".C");
	
	/// Acceptance
	cnvAcc->cd();
	cnvAcc->Draw();
	vhAcceptance[massBin-1]->SetMarkerStyle(24);
	vhAcceptance[massBin-1]->SetMarkerSize(1);
	vhAcceptance[massBin-1]->Draw("e1x1");
	pvtxt_massbinname->Draw("SAMES");
	cnvAcc->SaveAs("plots/Acceptance_"+sMassBin+".png");
	cnvAcc->SaveAs("plots/Acceptance_"+sMassBin+".eps");
	cnvAcc->SaveAs("plots/Acceptance_"+sMassBin+".pdf");
	cnvAcc->SaveAs("plots/Acceptance_"+sMassBin+".ps");
	cnvAcc->SaveAs("plots/Acceptance_"+sMassBin+".root");
	cnvAcc->SaveAs("plots/Acceptance_"+sMassBin+".C");
	
	
	TFile* f = new TFile("plots/PyQ_DYmumu_all.root","UPDATE");
	f->cd();
	vhPyQ[massBin-1]->Write();
	vhAcceptance[massBin-1]->Write();
	f->Write();
	f->Close();
	delete f;
	
	delete cnvPyQ;
	delete cnvAcc;
	delete pvtxt_massbinname;
}

void setHistos(int massBin)
{
	TString sMassBin = (TString)_s(massBin);
	TString sTitles = "";
	
	sTitles = "Fraction of events where #vec{#beta}_{Q}^{det}#bullet#vec{p}_{q}^{cmf}<0;y_{Q};P(y_{Q})";
	vhPyQ.push_back(new TH1D("PyQ_massbin_"+sMassBin,sTitles,nyqbins,yqmin,yqmax));
	vhPyQdenominator.push_back(new TH1D("PyQ_massbin_"+sMassBin+"_denominator",sTitles,nyqbins,yqmin,yqmax));
	vhPyQ[massBin-1]->SetDefaultSumw2(kTRUE);
	vhPyQdenominator[massBin-1]->SetDefaultSumw2(kTRUE);
	vhPyQ[massBin-1]->SetMarkerStyle(24);
	vhPyQ[massBin-1]->SetMarkerSize(1);
	vhPyQdenominator[massBin-1]->SetMarkerStyle(24);
	vhPyQdenominator[massBin-1]->SetMarkerSize(1);
	
	sTitles = "Acceptance in cos#theta*";
	vhAcceptance.push_back(new TH1D("acc_massbin_"+sMassBin,sTitles,ncostbins,costmin,costmax));
	vhAcceptanceDenominator.push_back(new TH1D("acc_massbin_"+sMassBin+"_denominator",sTitles,ncostbins,costmin,costmax));
	vhAcceptance[massBin-1]->SetDefaultSumw2(kTRUE);
	vhAcceptanceDenominator[massBin-1]->SetDefaultSumw2(kTRUE);
	vhAcceptance[massBin-1]->SetMarkerStyle(24);
	vhAcceptance[massBin-1]->SetMarkerSize(1);
	vhAcceptanceDenominator[massBin-1]->SetMarkerStyle(24);
	vhAcceptanceDenominator[massBin-1]->SetMarkerSize(1);
}

void PyQ_DYmumu()
{
	setMSGlevel(SILENT,VISUAL,VISUAL);

	_DEBUG("PyQ_DYmumu");
	style();
	colors();
	
	TFile* fTmp = new TFile("plots/PyQ_DYmumu_all.root","RECREATE");
	fTmp->Write();
	fTmp->Close();
	delete fTmp;
	
	setLogBins(nlogmassbins,logmassmin,logmassmax,logmassbins);
	
	///////////////////
	settrees(); ///////
	///////////////////
	
	for(int massBin=1 ; massBin<=nlogmassbins ; massBin++)
	{
		_INFO("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~START: mass bin "+_s(massBin)+"~~~~~~~~~~~~~~~~~~~~~~~~");
		////////////////////////////////////////////////////
		setHistos(massBin); ////////////////////////////////
		Int_t N = loop(massBin); ///////////////////////////
		draw(massBin); //////////////////////////////////
		////////////////////////////////////////////////////
		_INFO("completted massBin="+_s(massBin)+" with N="+_s(N));
	}
}


