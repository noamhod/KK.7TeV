#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/histos.h"

void weights()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;
	
	style();

	float pileup_weight;
	float EW_kfactor_weight;
	float QCD_kfactor_weight;

	bool isDY = true;

	TFile* fLoose = NULL;
	if(isDY) fLoose = new TFile("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_75M120.root","READ");
	else     fLoose = new TFile("/data/hod/2011/NTUPLE/mcLocalControl_Zprime_mumu_SSM2000.root","READ");
	TTree* t = (TTree*)fLoose->Get("allCuts/allCuts_tree");
	t->SetBranchAddress("pileup_weight",      &pileup_weight);
	t->SetBranchAddress("EW_kfactor_weight",  &EW_kfactor_weight);
	t->SetBranchAddress("QCD_kfactor_weight", &QCD_kfactor_weight);

	Int_t n = t->GetEntries();	
	float tot_sumofweights = 0.;
	float pu_sumofweights  = 0.;
	float kf_sumofweights  = 0.;
	for(Int_t i=0 ; i<n ; i++)
	{
		t->GetEntry(i);
	
		pu_sumofweights  += pileup_weight;
		kf_sumofweights  += (isDY) ? EW_kfactor_weight*QCD_kfactor_weight : QCD_kfactor_weight;
		tot_sumofweights += (isDY) ? pileup_weight*EW_kfactor_weight*QCD_kfactor_weight : pileup_weight*QCD_kfactor_weight;
	}
	_INFO("events passsing all cuts: "+_s(n));
	_INFO("total   sum of weights = "+_s(tot_sumofweights,4));
	_INFO("kfactor sum of weights = "+_s(kf_sumofweights,4));
	_INFO("pileup  sum of weights = "+_s(pu_sumofweights,4));
}
