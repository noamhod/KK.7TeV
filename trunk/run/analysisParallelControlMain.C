/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

#include <TROOT.h>

void prepare(TString sGRLtag) // do not use alone
{
	gROOT->Reset();
	
	gROOT->ProcessLine(".include ../include/");
	gROOT->ProcessLine(".include ../src/");
	gROOT->ProcessLine(".include ./");

	gSystem->Load( "libCintex.so" );
	Cintex::Cintex::Enable();
	gROOT->ProcessLine(".L Loader.C+");
	
	gROOT->ProcessLine(".include ../GoodRunsLists-" + sGRLtag + "/");
	gROOT->ProcessLine(".include ../GoodRunsLists-" + sGRLtag + "/GoodRunsLists/");

	gROOT->ProcessLine(".L ../GoodRunsLists-" + sGRLtag + "/StandAlone/libGoodRunsLists.so");
}

void compile(TString sGRLtag) // for re-compilation
{
	prepare(sGRLtag);
	
	gROOT->ProcessLine(".L analysisParallelControl.C++");
	gROOT->ProcessLine("analysisParallelControl apc");
}

void analysisParallelControlMain()
{
	prepare("00-00-91");
	gROOT->ProcessLine(".L analysisParallelControl_C.so");
	gROOT->ProcessLine("analysisParallelControl apc");
	gROOT->ProcessLine("apc.initialize()");
	gROOT->ProcessLine("apc.loop()");
}