/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

void includeGRL(TString sGRLtag) // not to use directly
{
	gROOT->ProcessLine(".include ../GoodRunsLists-" + sGRLtag + "/");
        gROOT->ProcessLine(".include ../GoodRunsLists-" + sGRLtag + "/GoodRunsLists/");
}

void loadGRL(TString sGRLtag) // not to use directly
{
	includeGRL(sGRLtag);
        gROOT->ProcessLine(".L ../GoodRunsLists-" + sGRLtag + "/StandAlone/libGoodRunsLists.so");
}

void compile(TString sGRLtag) // to use for compilation
{
	loadGRL(sGRLtag);
	gROOT->ProcessLine(".L analysisControl.C++");
	gROOT->ProcessLine("analysisControl ac");
}

void load(TString sGRLtag) // to use in case of already compiled
{
        loadGRL(sGRLtag);
        gROOT->ProcessLine("analysisControl ac");
}

void run(Long64_t startEvent=0, Long64_t stopEvent=0) // to use for running
{
	ac.loop(startEvent, stopEvent);
}

