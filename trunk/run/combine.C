#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/bins.h"
#include "../include/histos.h"

TString fpath = "2dtemplates_fastDY_smallDY_noEWkFsig_noHighMbins_noTruth";
TObjArray* toarKKtmp;
TObjArray* toarZPtmp;

void combine()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	// remember old dir
	TDirectory* olddir = gDirectory;

	olddir->cd();
	TFile* fKK = new TFile("plots/KK_"+fpath+".root", "RECREATE");
	TObjArray* templates2d_KK = new TObjArray;

	olddir->cd();
	TFile* fZP = new TFile("plots/ZP_"+fpath+".root", "RECREATE");
	TObjArray* templates2d_ZP = new TObjArray;

	TH2D* h2tmp = NULL;
	for(double f=200 ; f<=2900 ; f+=300)
	{
		TString fname = (TString)_s(f);
		
		olddir->cd();
		TFile* FKK = new TFile("plots/KK_"+fpath+"_Xmass"+fname+".root","READ");
		FKK->cd();
		toarKKtmp = new TObjArray();
		toarKKtmp->Read("template2d");
		olddir->cd();
		h2tmp = (TH2D*)((TH2D*)(TObjArray*)toarKKtmp->At(0))->Clone();
		fKK->cd(); // important !
		templates2d_KK->Add( (TH2D*)h2tmp );
		templates2d_KK->SetOwner(kTRUE);
		delete FKK;
		delete toarKKtmp;
		
		_INFO("done KK "+(string)fname);
		
		olddir->cd();
		TFile* FZP = new TFile("plots/ZP_"+fpath+"_Xmass"+fname+".root","READ");
		FZP->cd();
		toarZPtmp = new TObjArray();
		toarZPtmp->Read("template2d");
		olddir->cd();
		h2tmp = (TH2D*)((TH2D*)(TObjArray*)toarZPtmp->At(0))->Clone();
		fZP->cd(); // important !
		templates2d_ZP->Add( (TH2D*)h2tmp );
		templates2d_ZP->SetOwner(kTRUE);
		delete FZP;
		delete toarZPtmp;
		
		_INFO("done ZP "+(string)fname);
	}
	
	_INFO("done loop");
	
	olddir->cd();
	
	fKK->cd();
	templates2d_KK->SetOwner(kTRUE);
	templates2d_KK->Write("template2d", TObject::kSingleKey);
	fKK->Write();
	fKK->Close();
	
	_INFO("done KK");
	
	
	olddir->cd();
	
	fZP->cd();
	templates2d_ZP->SetOwner(kTRUE);
	templates2d_ZP->Write("template2d", TObject::kSingleKey);
	fZP->Write();
	fZP->Close();
	
	_INFO("done ZP");
	
	_INFO("see:");
	_INFO(" (1) "+(string)fKK->GetName());
	_INFO(" (2) "+(string)fZP->GetName());
}
