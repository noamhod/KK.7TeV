/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

#include <TROOT.h>

void prepare(TString sGRLtag, TString sRunDir="", TString sGdb="") // do not use alone
{
	gROOT->Reset();

	TString sMCPtag = "00-05-00";
	TString sPRWtag = "00-02-01";
	
	gROOT->ProcessLine(".include "+sRunDir+"../include/");
	gROOT->ProcessLine(".include "+sRunDir+"../src/");
	gROOT->ProcessLine(".include "+sRunDir+"./");

	gSystem->Load( "libCintex.so" );
	Cintex::Cintex::Enable();
	gROOT->ProcessLine(".L "+sRunDir+"Loader.C+"+sGdb);
	
	gROOT->ProcessLine(".include "+sRunDir+"../GoodRunsLists-" + sGRLtag + "/");
	gROOT->ProcessLine(".include "+sRunDir+"../GoodRunsLists-" + sGRLtag + "/GoodRunsLists/");
	gROOT->ProcessLine(".L "+sRunDir+"../GoodRunsLists-" + sGRLtag + "/StandAlone/libGoodRunsLists.so");
	
	gROOT->ProcessLine(".include "+sRunDir+"../MuonMomentumCorrections-"+sMCPtag+"/");
	gROOT->ProcessLine(".include "+sRunDir+"../MuonMomentumCorrections-"+sMCPtag+"/MuonMomentumCorrections/");
	gROOT->ProcessLine(".include "+sRunDir+"../MuonMomentumCorrections-"+sMCPtag+"/Root/");
	gROOT->ProcessLine(".L "+sRunDir+"../MuonMomentumCorrections-"+sMCPtag+"/StandAlone/libMuonMomentumCorrections.so");

	gROOT->ProcessLine(".include "+sRunDir+"../PileupReweighting-"+sPRWtag+"/");
    gROOT->ProcessLine(".include "+sRunDir+"../PileupReweighting-"+sPRWtag+"/PileupReweighting/");
    gROOT->ProcessLine(".include "+sRunDir+"../PileupReweighting-"+sPRWtag+"/Root/");
    gROOT->ProcessLine(".L "+sRunDir+"../PileupReweighting-"+sPRWtag+"/StandAlone/libPileupReweighting.so");:
}

void compile(TString sGRLtag, TString sRunDir="", TString sGdb="") // for re-compilation
{
	prepare(sGRLtag,sRunDir);
	
	gROOT->ProcessLine(".L "+sRunDir+"analysisLocalControl.C++"+sGdb);
	gROOT->ProcessLine("analysisLocalControl alc");
}

void load(TString sGRLtag, TString sRunDir="") // only for loading, if already compiled
{
	prepare(sGRLtag,sRunDir);
	gROOT->ProcessLine(".L "+sRunDir+"analysisLocalControl_C.so");
	gROOT->ProcessLine("analysisLocalControl alc");
}
