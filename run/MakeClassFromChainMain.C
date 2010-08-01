/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

void prepare() // do not use alone
{
	gROOT->ProcessLine(".include ../include/");
        gROOT->ProcessLine(".include ../src/");
        gROOT->ProcessLine(".include ./");
}

void compile() // for re-compilation
{
	prepare();
	
	gROOT->ProcessLine(".L MakeClassFromChain.C++");
	
	gROOT->ProcessLine("MakeClassFromChain mcfc");
}

void load() // only for loading, if already compiled
{
	prepare();

	gROOT->ProcessLine(".L MakeClassFromChain_C.so");

	gROOT->ProcessLine("MakeClassFromChain mcfc");
}
