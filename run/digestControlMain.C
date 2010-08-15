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
}

void compile() // for re-compilation
{
	prepare();
	
	gROOT->ProcessLine(".L digestControl.C++");
	
	gROOT->ProcessLine("digestControl dc");
}

void load() // only for loading, if already compiled
{
	prepare();

	gROOT->ProcessLine(".L digestControl_C.so");

	gROOT->ProcessLine("digestControl dc");
}
