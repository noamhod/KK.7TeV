#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/logs.h"

//////////////////////////////////////
// USAGE: broot funceval.C++\(49\) ///
//////////////////////////////////////

void funceval(float x)
{
	msglvl[INF] = VISUAL;
	TFile f("plots/ZP_functions_norm2Zpeak_interpolated.root", "READ");
	TF1* f1 = (TF1*)f.Get("19_nominal/fNominal_mX19_mll31");
	_INFO("f("+_s(x)+")="+_s(f1->Eval(x)));
}
