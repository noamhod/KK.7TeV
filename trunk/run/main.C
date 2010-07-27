/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

void prepare(TString sGRLtag) // do not use alone
{
	gROOT->ProcessLine(".include ../include/");
        gROOT->ProcessLine(".include ../src/");
        gROOT->ProcessLine(".include ./");

        gROOT->ProcessLine(".include ../GoodRunsLists-" + sGRLtag + "/");
        gROOT->ProcessLine(".include ../GoodRunsLists-" + sGRLtag + "/GoodRunsLists/");

        gROOT->ProcessLine(".L ../GoodRunsLists-" + sGRLtag + "/StandAlone/libGoodRunsLists.so");
}

void compile(TString sGRLtag) // for re-compilation
{
	prepare(sGRLtag);
	
	gROOT->ProcessLine(".L analysisControl.C++");
	
	gROOT->ProcessLine("analysisControl ac");
}

void load(TString sGRLtag) // only for loading, if already compiled
{
	prepare(sGRLtag);

	gROOT->ProcessLine(".L src/analysisControl_C.so");

	gROOT->ProcessLine("analysisControl ac");
}
