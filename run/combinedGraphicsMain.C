/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

#include <TROOT.h>

void prepare() // do not use alone
{
	gROOT->Reset();
	
	gROOT->ProcessLine(".include ../include/");
	gROOT->ProcessLine(".include ../src/");
	gROOT->ProcessLine(".include ./");

	/*
	gSystem->Load( "libCintex.so" );
	Cintex::Cintex::Enable();
	gROOT->ProcessLine(".L Loader.C+");
	*/
}

void compile() // for re-compilation
{
	prepare();
	
	gROOT->ProcessLine(".L combinedGraphicsControl.C++");
	
	gROOT->ProcessLine("combinedGraphicsControl cgc");
}

void load() // only for loading, if already compiled
{
	prepare();

	gROOT->ProcessLine(".L combinedGraphicsControl_C.so");

	gROOT->ProcessLine("combinedGraphicsControl cgc");
}
