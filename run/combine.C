#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/systematics.h"

using namespace systematics;

bool doGrid          = false;
bool doTruth         = false;
bool doEWkf          = false;
bool doInterference  = false;
bool doKKtemplates   = false;
bool doOfficialZP    = false;
bool doScale2Zpeak   = true;
bool dog4bins        = false;
TString channel      = "#mu#mu"; // #mu#mu or ee
TString model        = "ZP";
TString mutype       = "3332st"; // or "33st" or "32st"
TString binning      = "linearbins"; // or "powercins"

TString version      = (doGrid)         ? "v33/"    : "";
TString basedir      = (doInterference) ? ""        : "nointerference/";
TString interference = (doInterference) ? ""        : "_noInterference";
TString overallEWkF  = (doInterference) ? ""        : "_noOverallEWkF";
TString doEWkfactor  = (doEWkf)         ? ""        : "_noEWkF";
TString dotruth      = (doTruth)        ? ""        : "_noTruth";
TString gNbinning    = (dog4bins)       ? "_g4bins" : "_g2bins";
TString KKtemplates  = (doKKtemplates)  ? ""        : "_noKKtmplates";
TString officialZP   = (!doOfficialZP)  ? ""        : "_wthOfficialZP";
TString gNbins       = (dog4bins)       ? "g4bins"  : "g2bins";

Double_t scale2Zpeak = 1.;

double Mmin = 130.;
double Mmax = 5030.;//5030.;
double dM   = 100.;//100.;

TString fpath      = "";
TString fpathSigUp = "";

TString sDir       = "";
TString sDirSigUp  = "";

TObjArray* toarKKtmp;
TObjArray* toarKKtmpSigUp;
TObjArray* toarZPtmp;
TObjArray* toarZPtmpSigUp;

 // remember old dir
TDirectory* olddir = gDirectory;


void setFpath()
{
	if(channel=="#mu#mu")
	{
		sDir       = "plots/"+basedir+binning+"/"+gNbins+"/"+mutype+"_nominal/"+version;
		sDirSigUp  = "plots/"+basedir+binning+"/"+gNbins+"/"+mutype+"_sigmaup/"+version;
		if(doGrid)
		{
			fpath      = "template_nominal_";
			fpathSigUp = "template_oversmeared_";
		}
		else
		{
			fpath      = "2dtemplates_mc11c_"+mutype+gNbinning+interference+KKtemplates+overallEWkF+doEWkfactor+dotruth;
			fpathSigUp = "2dtemplates_mc11c_"+mutype+gNbinning+interference+KKtemplates+"_SmrSigUp"+overallEWkF+doEWkfactor+dotruth; // +1sigma smearing
		}
	}
	else if(channel=="ee")
	{
		////
	}
}


void setScale2Zpeak()
{
	if(channel=="#mu#mu")
	{
		scale2Zpeak = (mutype=="33st")   ? 0.9920123197 : 1.;    // For linear bins, see normtest.C
		scale2Zpeak = (mutype=="32st")   ? 0.8852545729 : 1.;    // For linear bins, see normtest.C
		scale2Zpeak = (mutype=="3332st") ? 0.9841360523 : 1.;    // For linear bins, see normtest.C
	}
	else if(channel=="ee")
	{
		////
	}
} 

TH2D* addDYtoPureSigTemplate(TH2D* h2, TH1D* hDY)
{
	TString h2name = (TString)h2->GetName();
	TH2D* h2sig = (TH2D*)h2->Clone(h2name+"_sumDY");
	unsigned int nbinsx = h2sig->GetNbinsX();
	unsigned int nbinsy = h2sig->GetNbinsY();
	for(unsigned int x=0 ; x<=nbinsx+1 ; x++)
	{
		Double_t nDYx = hDY->GetBinContent(x);
		Double_t eDYx = hDY->GetBinError(x);
		for(unsigned int y=0 ; y<=nbinsy+1 ; y++)
		{
			Double_t nSigx = h2sig->GetBinContent(x,y);
			Double_t eSigx = h2sig->GetBinError(x,y);
			
			h2sig->SetBinContent(x,y,nSigx+nDYx);
			h2sig->SetBinError(x,y,sqrt(eDYx*eDYx + eSigx*eSigx));
		}
	}
	
	return h2sig;
}

void combine()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	///////////////////////////////////////////
	//// to select the correct syst for the ///
	//// no interference case /////////////////
	setSystInrerference(doInterference); //////
	///////////////////////////////////////////
	
	///////////////////////////////////////////
	//// set globals //////////////////////////
	setFpath(); ///////////////////////////////
	setScale2Zpeak(); /////////////////////////
	///////////////////////////////////////////
	
	_INFO("working in -> "+(string)sDir);
	
	TFile* fOfficial = new TFile("DimuonHists_Feb05_3stC.root","READ");
	TH1D* hDYofficial = (TH1D*)fOfficial->Get("ZLogmass_DYmm")->Clone();
	
	_INFO("");

	version.ReplaceAll("/","");
	
	olddir->cd();
	TFile* fKK = NULL;
	TString outfNameKK = sDir+"KK_combined_"+fpath+".root";
	outfNameKK = (doGrid) ? sDir+"KK_combined_"+version+".root" : outfNameKK;
	if(model=="KK" || model=="ALL") fKK = new TFile(outfNameKK, "RECREATE");
	TObjArray* templates2d_KK                 = new TObjArray;
	TObjArray* templates2d_KK_syst_Zxs        = new TObjArray;
	TObjArray* templates2d_KK_syst_PDF        = new TObjArray;
	TObjArray* templates2d_KK_syst_EWkF       = new TObjArray;
	TObjArray* templates2d_KK_syst_QCDkF      = new TObjArray;
	TObjArray* templates2d_KK_syst_mmSlopeEff = new TObjArray;
	TObjArray* templates2d_KK_syst_eeIsoEff   = new TObjArray;
	TObjArray* templates2d_KK_syst_mmRes      = new TObjArray;
	// TObjArray* templates2d_KK_syst_eeRes      = new TObjArray;

	olddir->cd();
	TString outfNameZP = sDir+"ZP_combined_"+fpath+".root";
	outfNameZP = (doGrid) ? sDir+"ZP_combined_"+version+".root" : outfNameZP;
	TFile* fZP = new TFile(outfNameZP,"RECREATE");
	TObjArray* templates2d_ZP                 = new TObjArray;
	TObjArray* templates2d_ZP_syst_Zxs        = new TObjArray;
	TObjArray* templates2d_ZP_syst_PDF        = new TObjArray;
	TObjArray* templates2d_ZP_syst_EWkF       = new TObjArray;
	TObjArray* templates2d_ZP_syst_QCDkF      = new TObjArray;
	TObjArray* templates2d_ZP_syst_mmSlopeEff = new TObjArray;
	TObjArray* templates2d_ZP_syst_eeIsoEff   = new TObjArray;
	TObjArray* templates2d_ZP_syst_mmRes      = new TObjArray;
	// TObjArray* templates2d_ZP_syst_eeRes      = new TObjArray;

	olddir->cd();
	
	TH2D* h2tmp      = NULL;
	TH2D* h2tmpSigUp = NULL;
	
	// uncertainties
	TH2D* h2nominal        = NULL;
	TH2D* h2smearUp        = NULL;
	TH2D* h2sys_zXsec      = NULL;
	TH2D* h2sys_pdfZ       = NULL;    
	TH2D* h2sys_kEWK       = NULL;
	TH2D* h2sys_kQCD       = NULL;
	TH2D* h2sys_mmSlopeEff = NULL;
	TH2D* h2sys_eeIsoEff   = NULL;
	TH2D* h2sys_mmRes      = NULL;
	// TH2D* h2sys_eeRes      = NULL;
	
	for(double f=Mmin ; f<=Mmax ; f+=dM)
	{
		TString fname = (TString)_s(f);
		
		TString name = "";
		
		if(model=="KK" || model=="ALL")
		{
			// nominals
			olddir->cd();
			TString infNameKK = sDir+"KK_"+fpath+"_Xmass"+fname+".root";
			if(doGrid) infNameKK = sDir+fpath+fname+"GeV_"+version+".root";
			TFile* FKK = new TFile(infNameKK,"READ");
			FKK->cd();
			toarKKtmp = new TObjArray();
			toarKKtmp->Read("template2dKK");
			olddir->cd();
			h2tmp = (TH2D*)((TH2D*)(TObjArray*)toarKKtmp->At(0))->Clone();
			if(doScale2Zpeak) h2tmp->Scale(scale2Zpeak);
			if(!doInterference) h2tmp = (TH2D*)addDYtoPureSigTemplate(h2tmp, hDYofficial)->Clone();
			fKK->cd(); // important !
			templates2d_KK->Add( (TH2D*)h2tmp );
			templates2d_KK->SetOwner(kTRUE);
			
			if(channel=="#mu#mu")
			{
				olddir->cd();
				infNameKK = sDirSigUp+"KK_"+fpathSigUp+"_Xmass"+fname+".root";
				if(doGrid) infNameKK = sDirSigUp+fpathSigUp+fname+"GeV_"+version+".root";
				TFile* FKKsmearUp = new TFile(infNameKK,"READ");
				FKKsmearUp->cd();
				toarKKtmpSigUp = new TObjArray();
				toarKKtmpSigUp->Read("template2dKK");
				olddir->cd();
				h2tmpSigUp = (TH2D*)((TH2D*)(TObjArray*)toarKKtmpSigUp->At(0))->Clone();
				if(doScale2Zpeak) h2tmpSigUp->Scale(scale2Zpeak);
				if(!doInterference) h2tmpSigUp = (TH2D*)addDYtoPureSigTemplate(h2tmpSigUp, hDYofficial)->Clone();
				delete FKKsmearUp;
				delete toarKKtmpSigUp;
				fKK->cd(); // important !
			}
			
			/////////////////////
			// KK systematics ///
			/////////////////////
			olddir->cd();
			name = (TString)h2tmp->GetName();
			h2nominal = (TH2D*)h2tmp->Clone(name+"_syst");
			if(channel=="#mu#mu") h2smearUp = (TH2D*)h2tmpSigUp->Clone(name+"_smearUp");
			h2sys_zXsec      = (TH2D*)sysUpTemplate(h2nominal,channel,"Zxs")->Clone(name+"_sys_Zxs");          // Z cross section syst. only on the signal
			h2sys_pdfZ       = (TH2D*)sysUpTemplate(h2nominal,channel,"PDF")->Clone(name+"_sys_pdfZ");         // PDF systematic	      
			h2sys_kEWK       = (TH2D*)sysUpTemplate(h2nominal,channel,"EWkF")->Clone(name+"_sys_kEWK");	      // EWK K-factor
			// h2sys_kQCD    = (TH2D*)sysUpTemplate(h2nominal,channel,"QCDkF")->Clone(name+"_sys_kQCD");       // QCD K-factor; Now included in pdfZ
			h2sys_mmSlopeEff = (TH2D*)sysUpTemplate(h2nominal,channel,"mmEff")->Clone(name+"_sys_mmSlopeEff"); // const slope efficiency uncertainty
			h2sys_eeIsoEff   = (TH2D*)sysUpTemplate(h2nominal,channel,"eeEff")->Clone(name+"_sys_eeIsoEff");   // isolation in ee channel
			if(channel=="#mu#mu") h2sys_mmRes = (TH2D*)smearUpTemplate(h2nominal,h2smearUp)->Clone(name+"_sys_mmRes");    // resolution in the mm channel
			// h2sys_eeRes      = (TH2D*)smearUpTemplate(h2nominal,h2smearUp)->Clone(name+"_sys_eeRes");    // resolution in the ee channel
			
			fKK->cd(); // important !
			templates2d_KK_syst_Zxs->Add( (TH2D*)h2sys_zXsec );
			templates2d_KK_syst_PDF->Add( (TH2D*)h2sys_pdfZ );
			templates2d_KK_syst_EWkF->Add( (TH2D*)h2sys_kEWK );
			// templates2d_KK_syst_QCDkF->Add( (TH2D*)h2sys_kQCD );
			templates2d_KK_syst_mmSlopeEff->Add( (TH2D*)h2sys_mmSlopeEff );
			templates2d_KK_syst_eeIsoEff->Add( (TH2D*)h2sys_eeIsoEff );
			if(channel=="#mu#mu") templates2d_KK_syst_mmRes->Add( (TH2D*)h2sys_mmRes );
			// templates2d_KK_syst_eeRes->Add( (TH2D*)h2sys_eeRes );
			
			templates2d_KK_syst_Zxs->SetOwner(kTRUE);
			templates2d_KK_syst_PDF->SetOwner(kTRUE);
			templates2d_KK_syst_EWkF->SetOwner(kTRUE);
			// templates2d_KK_syst_QCDkF->SetOwner(kTRUE);
			templates2d_KK_syst_mmSlopeEff->SetOwner(kTRUE);
			templates2d_KK_syst_eeIsoEff->SetOwner(kTRUE);
			if(channel!="ee") templates2d_KK_syst_mmRes->SetOwner(kTRUE);
			// templates2d_KK_syst_eeRes->SetOwner(kTRUE);
			
			delete FKK;
			delete toarKKtmp;
			
			_INFO("done KK "+(string)fname);
		}
		
		////////////////////////////////////////
		
		
		
		olddir->cd();
		TString infNameZP = sDir+"ZP_"+fpath+"_Xmass"+fname+".root";
		if(doGrid) infNameZP = sDir+fpath+fname+"GeV_"+version+".root";
		TFile* FZP = new TFile(infNameZP,"READ");
		FZP->cd();
		toarZPtmp = new TObjArray();
		if(doGrid) toarZPtmp->Read("template2dZP");
		else       toarZPtmp->Read("template2d");
		olddir->cd();
		h2tmp = (TH2D*)((TH2D*)(TObjArray*)toarZPtmp->At(0))->Clone();
		if(doScale2Zpeak) h2tmp->Scale(scale2Zpeak);
		if(!doInterference) h2tmp = (TH2D*)addDYtoPureSigTemplate(h2tmp, hDYofficial)->Clone();
		fZP->cd(); // important !
		templates2d_ZP->Add( (TH2D*)h2tmp );
		templates2d_ZP->SetOwner(kTRUE);
		
		if(channel=="#mu#mu"  &&  doInterference)
		{
			olddir->cd();
			infNameZP = sDirSigUp+"ZP_"+fpathSigUp+"_Xmass"+fname+".root";
			if(doGrid) infNameZP = sDirSigUp+fpathSigUp+fname+"GeV_"+version+".root";
			TFile* FZPsmearUp = new TFile(infNameZP,"READ");
			FZPsmearUp->cd();
			toarZPtmpSigUp = new TObjArray();
			toarZPtmpSigUp->Read("template2dZP");
			olddir->cd();
			h2tmpSigUp = (TH2D*)((TH2D*)(TObjArray*)toarZPtmpSigUp->At(0))->Clone();
			if(doScale2Zpeak) h2tmpSigUp->Scale(scale2Zpeak);
			delete FZPsmearUp;
			delete toarZPtmpSigUp;
			fZP->cd(); // important !
		}
				
		/////////////////////
		// ZP systematics ///
		/////////////////////
		olddir->cd();
		name = (TString)h2tmp->GetName();
		h2nominal = (TH2D*)h2tmp->Clone(name+"_syst");
		if(channel=="#mu#mu" && doInterference) h2smearUp = (TH2D*)h2tmpSigUp->Clone(name+"_smearUp");
		h2sys_zXsec      = (TH2D*)sysUpTemplate(h2nominal,channel,"Zxs")->Clone(name+"_sys_Zxs");          // Z cross section syst. only on the signal
		h2sys_pdfZ       = (TH2D*)sysUpTemplate(h2nominal,channel,"PDF")->Clone(name+"_sys_pdfZ");         // PDF systematic	      
		h2sys_kEWK       = (TH2D*)sysUpTemplate(h2nominal,channel,"EWkF")->Clone(name+"_sys_kEWK");	       // EWK K-factor
		// h2sys_kQCD    = (TH2D*)sysUpTemplate(h2nominal,channel,"QCDkF")->Clone(name+"_sys_kQCD");       // QCD K-factor; Now included in pdfZ
		h2sys_mmSlopeEff = (TH2D*)sysUpTemplate(h2nominal,channel,"mmEff")->Clone(name+"_sys_mmSlopeEff"); // const slope efficiency uncertainty
		h2sys_eeIsoEff   = (TH2D*)sysUpTemplate(h2nominal,channel,"eeEff")->Clone(name+"_sys_eeIsoEff");   // isolation in ee channel
		if(channel=="#mu#mu" && doInterference) h2sys_mmRes = (TH2D*)smearUpTemplate(h2nominal,h2smearUp)->Clone(name+"_sys_mmRes");          // resolution in the mm channel
		// h2sys_eeRes      = (TH2D*)smearUpTemplate(h2nominal,h2smearUp)->Clone(name+"_sys_eeRes");          // resolution in the ee channel
		
		fZP->cd(); // important !
		templates2d_ZP_syst_Zxs->Add( (TH2D*)h2sys_zXsec );
		templates2d_ZP_syst_PDF->Add( (TH2D*)h2sys_pdfZ );
		templates2d_ZP_syst_EWkF->Add( (TH2D*)h2sys_kEWK );
		// templates2d_ZP_syst_QCDkF->Add( (TH2D*)h2sys_kQCD );
		templates2d_ZP_syst_mmSlopeEff->Add( (TH2D*)h2sys_mmSlopeEff );
		templates2d_ZP_syst_eeIsoEff->Add( (TH2D*)h2sys_eeIsoEff );
		if(channel=="#mu#mu" && doInterference) templates2d_ZP_syst_mmRes->Add( (TH2D*)h2sys_mmRes );
		// templates2d_ZP_syst_eeRes->Add( (TH2D*)h2sys_eeRes );
		
		templates2d_ZP_syst_Zxs->SetOwner(kTRUE);
		templates2d_ZP_syst_PDF->SetOwner(kTRUE);
		templates2d_ZP_syst_EWkF->SetOwner(kTRUE);
		// templates2d_ZP_syst_QCDkF->SetOwner(kTRUE);
		templates2d_ZP_syst_mmSlopeEff->SetOwner(kTRUE);
		templates2d_ZP_syst_eeIsoEff->SetOwner(kTRUE);
		if(channel=="#mu#mu" && doInterference) templates2d_ZP_syst_mmRes->SetOwner(kTRUE);
		// templates2d_ZP_syst_eeRes->SetOwner(kTRUE);
		
		delete FZP;
		delete toarZPtmp;
		
		_INFO("done ZP "+(string)fname);
		
	}
	
	_INFO("done loop");
	
	olddir->cd();
	
	if(model=="KK" || model=="ALL")
	{
		fKK->cd();
		templates2d_KK->SetOwner(kTRUE);
		templates2d_KK->Write("template2d", TObject::kSingleKey);
		
		templates2d_KK_syst_Zxs->SetOwner(kTRUE);
		templates2d_KK_syst_Zxs->Write("template2d_Zxs_syst", TObject::kSingleKey);
		templates2d_KK_syst_PDF->SetOwner(kTRUE);
		templates2d_KK_syst_PDF->Write("template2d_PDF_syst", TObject::kSingleKey);
		templates2d_KK_syst_EWkF->SetOwner(kTRUE);
		templates2d_KK_syst_EWkF->Write("template2d_EWkF_syst", TObject::kSingleKey);
		// templates2d_KK_syst_QCDkF->SetOwner(kTRUE);
		// templates2d_KK_syst_QCDkF->Write("template2d_QCDkF_syst", TObject::kSingleKey);
		if(channel=="ee")
		{
			templates2d_KK_syst_eeIsoEff->SetOwner(kTRUE);
			templates2d_KK_syst_eeIsoEff->Write("template2d_eeIsoEff_syst", TObject::kSingleKey);
			// templates2d_KK_syst_eeRes->SetOwner(kTRUE);
			// templates2d_KK_syst_eeRes->Write("template2d_eeRes_syst", TObject::kSingleKey);
		}
		if(channel=="#mu#mu")
		{
			templates2d_KK_syst_mmSlopeEff->SetOwner(kTRUE);
			templates2d_KK_syst_mmSlopeEff->Write("template2d_mmSlopeEff_syst", TObject::kSingleKey);
			templates2d_KK_syst_mmRes->SetOwner(kTRUE);
			templates2d_KK_syst_mmRes->Write("template2d_mmRes_syst", TObject::kSingleKey);
		}
		
		fKK->Write();
		fKK->Close();
	}
	
	_INFO("done KK");
	
	
	olddir->cd();
	
	fZP->cd();
	templates2d_ZP->SetOwner(kTRUE);
	templates2d_ZP->Write("template2d", TObject::kSingleKey);
	
	templates2d_ZP_syst_Zxs->SetOwner(kTRUE);
	templates2d_ZP_syst_Zxs->Write("template2d_Zxs_syst", TObject::kSingleKey);
	templates2d_ZP_syst_PDF->SetOwner(kTRUE);
	templates2d_ZP_syst_PDF->Write("template2d_PDF_syst", TObject::kSingleKey);
	templates2d_ZP_syst_EWkF->SetOwner(kTRUE);
	templates2d_ZP_syst_EWkF->Write("template2d_EWkF_syst", TObject::kSingleKey);
	// templates2d_ZP_syst_QCDkF->SetOwner(kTRUE);
	// templates2d_ZP_syst_QCDkF->Write("template2d_QCDkF_syst", TObject::kSingleKey);
	if(channel=="ee")
	{
		templates2d_ZP_syst_eeIsoEff->SetOwner(kTRUE);
		templates2d_ZP_syst_eeIsoEff->Write("template2d_eeIsoEff_syst", TObject::kSingleKey);
		// templates2d_ZP_syst_eeRes->SetOwner(kTRUE);
		// templates2d_ZP_syst_eeRes->Write("template2d_eeRes_syst", TObject::kSingleKey);
	}
	if(channel=="#mu#mu")
	{
		templates2d_ZP_syst_mmSlopeEff->SetOwner(kTRUE);
		templates2d_ZP_syst_mmSlopeEff->Write("template2d_mmSlopeEff_syst", TObject::kSingleKey);
		if(doInterference)
		{
			templates2d_ZP_syst_mmRes->SetOwner(kTRUE);
			templates2d_ZP_syst_mmRes->Write("template2d_mmRes_syst", TObject::kSingleKey);
		}
	}
	
	fZP->Write();
	fZP->Close();
	
	_INFO("done ZP");
	
	_INFO("see:");
	if(model=="KK" || model=="ALL") _INFO(" (1) "+(string)fKK->GetName());
	_INFO(" (2) "+(string)fZP->GetName());
	
}
