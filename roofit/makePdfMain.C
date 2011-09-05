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
	gROOT->ProcessLine(".include ./");
	gSystem->Load("libRooFit");
}

void compile() // for re-compilation
{
	prepare();

	gROOT->ProcessLine("RooRealVar x('x','x',  0., 7000000)");
	gROOT->ProcessLine("RooRealVar a('a','a', -1., -1.e-8)");
	gROOT->ProcessLine("RooRealVar b('b','b',  0., 10.)");
	gROOT->ProcessLine("RooClassFactory::makePdf('RooExtendedExponent','x,a,b')");

	gROOT->ProcessLine("RooRealVar x('costheta','costheta', -1., +1.)");
	gROOT->ProcessLine("RooRealVar A('A','A', +0.01, 20.)");
	gROOT->ProcessLine("RooRealVar B('B','B', -10., +10.)");
	gROOT->ProcessLine("RooClassFactory::makePdf('RooAngular','costheta,A,B')");
}

void load() // only for loading, if already compiled
{
	prepare();
}
