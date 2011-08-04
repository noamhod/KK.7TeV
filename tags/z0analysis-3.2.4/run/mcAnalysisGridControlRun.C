/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

TFile *fout;
TChain *fChain;

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

void mcAnalysisGridControlRun()
{
	// read a string via file since long string causes memory error in CINT when it is read via stdin
	string argStr;
	char buf[256+1];
	unsigned int delpos;
	ifstream ifs("input.txt");
	cout << "#################################################################################################" << endl;
	while (true)
	{
		ifs.read(buf,256);
		if (ifs.eof())
		{
			if (ifs.gcount() == 0) break;
			delpos = ifs.gcount()-1;
		}
		else
		{
			delpos = ifs.gcount();
		}
		buf[delpos] = 0x00;
		argStr += buf;
		
		cout << "buf=" << buf << endl;
	}
	cout << "#################################################################################################" << endl;


	// split by ','
	vector<string> fileList;
	for (size_t i=0,n; i <= argStr.length(); i=n+1)
	{
		n = argStr.find_first_of(',',i);
		if (n == string::npos)
		n = argStr.length();
		string tmp = argStr.substr(i,n-i);
		fileList.push_back(tmp);
	}

	TString chainName ="physics";
	fChain = new TChain(chainName);
	for (unsigned int iFile=0; iFile<fileList.size(); ++iFile)
	{
		//--------------- fix the last entry (a missing "t" at the end of the file name suffix) -------------
		if(iFile==fileList.size()-1)
		{
			int len = (int)fileList[iFile].length();
			string slast = fileList[iFile].substr(len-1,1);
			if( slast != "t" )
			{
				cout << "slast=" << slast << endl;
				fileList[iFile]+="t";
				cout << "#################################################################" << endl;
				cout << "### fixed missing character at the end of the last input file ###" << endl;
				cout << "#################################################################" << endl;
			}
		}
		//---------------------------------------------------------------------------------------------------
	
		cout << "open " << fileList[iFile].c_str() << endl;
	
		fChain->Add(fileList[iFile].c_str());
	}

	
	TString fileName ="mcWZphys.root";
	fout = new TFile(fileName, "RECREATE");
	
	// some includings and loadings

	gROOT->ProcessLine(".include ../include/");
	gROOT->ProcessLine(".include ../src/");
	gROOT->ProcessLine(".include ./");
	gROOT->ProcessLine(".include ../GoodRunsLists-00-00-91/");
	gROOT->ProcessLine(".include ../GoodRunsLists-00-00-91/GoodRunsLists/");
	
	exitIfNotExist("../GoodRunsLists-00-00-91/StandAlone/libGoodRunsLists.so");
	gROOT->ProcessLine(".L ../GoodRunsLists-00-00-91/StandAlone/libGoodRunsLists.so");
	
	gSystem->Load( "libCintex.so" );
	Cintex::Cintex::Enable();
	gROOT->ProcessLine(".L Loader.C+");
	
	gROOT->ProcessLine(".L mcAnalysisGridControl.C++");
	gROOT->ProcessLine("mcAnalysisGridControl mcagc(fChain, fout);");
	gROOT->ProcessLine("mcagc.loop(0,0);");
}

