/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

#include <TROOT.h>

void prepare() // do not use alone
{
	gROOT->ProcessLine(".include ../include/");
        gROOT->ProcessLine(".include ../src/");
        gROOT->ProcessLine(".include ./");
}

void compile() // for re-compilation
{
	prepare();
	
	gROOT->ProcessLine(".L MakeClassFromChainOffline.C++");
	
	gROOT->ProcessLine("MakeClassFromChainOffline mcfco");
}

void load() // only for loading, if already compiled
{
	prepare();

	gROOT->ProcessLine(".L MakeClassFromChainOffline_C.so");

	gROOT->ProcessLine("MakeClassFromChainOffline mcfco");
}
