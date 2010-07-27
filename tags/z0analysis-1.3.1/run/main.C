/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

void compile(TString sGRLtag)
{
	gROOT->ProcessLine(".include ../include/");
	gROOT->ProcessLine(".include ../src/");
	gROOT->ProcessLine(".include ./");

	gROOT->ProcessLine(".include ../GoodRunsLists-" + sGRLtag + "/");
	gROOT->ProcessLine(".include ../GoodRunsLists-" + sGRLtag + "/GoodRunsLists/");

	gROOT->ProcessLine(".L ../GoodRunsLists-" + sGRLtag + "/StandAlone/libGoodRunsLists.so");
	
	gROOT->ProcessLine(".L analysisControl.C++");
}

void run(Long64_t startEvent=0, Long64_t stopEvent=0)
{
	//gROOT->ProcessLine(".L src/analysisControl_C.so");
	analysisControl ac;
	ac.loop(startEvent, stopEvent);
}
