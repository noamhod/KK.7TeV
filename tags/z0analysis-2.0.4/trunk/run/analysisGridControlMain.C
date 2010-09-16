/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

#include <TROOT.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;


bool fileexists(string filename)
{
	ifstream ifile( filename.c_str() );
	return ifile;
}

void exitIfNotExist(string fullPath)
{
	if ( !fileexists(fullPath) )
	{
		cout << "Error: the mandatory file " << fullPath << " does not exist" << endl;
		cout << "Did you forget to copy it ?" << endl;
		cout << "Exit now" << endl;
		exit(-1);
	}
}

void prepare(TString sGRLtag) // do not use alone
{
	gROOT->Reset();
	
	gROOT->ProcessLine(".include ../include/");
	gROOT->ProcessLine(".include ../src/");
	gROOT->ProcessLine(".include ./");

	gROOT->ProcessLine(".include ../GoodRunsLists-" + sGRLtag + "/");
	gROOT->ProcessLine(".include ../GoodRunsLists-" + sGRLtag + "/GoodRunsLists/");

	exitIfNotExist("libGoodRunsLists.so");
	
	gROOT->ProcessLine(".L libGoodRunsLists.so");
}

void compile(TString sGRLtag) // for re-compilation
{
	prepare(sGRLtag);
	
	gROOT->ProcessLine(".L analysisGridControl.C++");
	
	gROOT->ProcessLine("analysisGridControl agc");
}

void load(TString sGRLtag) // only for loading, if already compiled
{
	prepare(sGRLtag);

	gROOT->ProcessLine(".L analysisGridControl_C.so");

	gROOT->ProcessLine("analysisGridControl agc");
}

