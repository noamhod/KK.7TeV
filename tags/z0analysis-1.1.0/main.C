/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

#define analysisControl_cxx
#include "src/analysisControl.C"

void include(TString sGRLtag)
{
	gROOT->ProcessLine(".include .");
        gROOT->ProcessLine(".include include/");
        gROOT->ProcessLine(".include src/");

        gROOT->ProcessLine(".include GoodRunsLists-" + sGRLtag + "/");
        gROOT->ProcessLine(".include GoodRunsLists-" + sGRLtag + "/GoodRunsLists/");
}

void loadGRL(TString sGRLtag)
{
	include(sGRLtag);
	gROOT->ProcessLine(".L GoodRunsLists-" + sGRLtag + "/StandAlone/libGoodRunsLists.so");
}

void compile(TString sGRLtag)
{
	loadGRL(sGRLtag);
        gROOT->ProcessLine(".L src/analysisControl.C++");
}

void loadCompiled(TString sGRLtag)
{
	loadGRL(sGRLtag);
	gROOT->ProcessLine(".L src/analysisControl_C.so");
	gROOT->ProcessLine("analysisControl ac");
}

