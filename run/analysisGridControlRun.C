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
string sRun;
string sRec;
string sMCorData;
bool   isMC;

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

void analysisGridControlRun()
{
	ifstream ifsel("runControl.txt");
	ifsel >> sRun >> sRec >> sMCorData;
	ifsel.close();
	
	if(sRun!="grid")
	{
		cout << "ERROR: YOU CHOSE RUN   [" << sRun << "], exitting now" << endl;
		exit(-1);
	}
	if(sRec!="staco"  &&  sRec!="muid")
	{
		cout << "ERROR: YOU CHOSE REC ALG   [" << sRec << "], exitting now" << endl;
		exit(-1);
	}
	if(sMCorData!="mc"  &&  sMCorData!="data")
	{
		cout << "ERROR: YOU CHOSE MC/DATA   [" << sMCorData << "], exitting now" << endl;
		exit(-1);
	}
	isMC = (sMCorData=="mc") ? true : false;
	
	// read a string via file since long string causes memory error in CINT when it is read via stdin
	string argStr;
	unsigned int delpos;
	string sFileName = (isMC) ? "inputMC.txt" : "input.txt";
	ifstream ifs(sFileName.c_str());
	cout << "#################################################################################################" << endl;
	string sLine = "";
	while(!ifs.eof())
	{
		getline(ifs,sLine);
		argStr += sLine;
		cout << "[1] sLine = " << sLine << endl;
	}
	cout << "#################################################################################################" << endl;
	cout << "[2] argStr = " << argStr << endl;
	cout << "#################################################################################################" << endl;
	// split by ','
	vector<string> fileList;
	string tmp;
	for (size_t i=0 ; i<argStr.length(); ++i)
	{
		if(argStr.substr(i,1)!=",") tmp += argStr.substr(i,1);
		else
		{
			fileList.push_back(tmp);
			cout << "tmp=" << tmp << endl;
			tmp.clear();
		}
		
		if(i==argStr.length()-1) 
		{
			fileList.push_back(tmp);
			cout << "tmp=" << tmp << endl;
			tmp.clear();
		}
	}
	cout << "#################################################################################################" << endl;

	TString chainName ="physics";
	fChain = new TChain(chainName);
	for (unsigned int iFile=0; iFile<fileList.size(); ++iFile)
	{
		//--------------- fix the last entry (a missing "t" at the end of the file name suffix) -------------
		if(iFile==fileList.size()-1)
		{
			int len = (int)fileList[iFile].length();
			string slast = fileList[iFile].substr(len-1,1);
			if( slast != "t" && slast != "1" )
			{
				cout << "slast=" << slast << endl;
				fileList[iFile]+="t";
				cout << "#################################################################" << endl;
				cout << "### fixed missing character at the end of the last input file ###" << endl;
				cout << "#################################################################" << endl;
			}
			else if( fileList[iFile].find("root.")!=string::npos  &&  slast=="." )
			{
				cout << "slast=" << slast << endl;
				fileList[iFile]+="1";
				cout << "#################################################################" << endl;
				cout << "### fixed missing character at the end of the last input file ###" << endl;
				cout << "#################################################################" << endl;
			}
		}
		//---------------------------------------------------------------------------------------------------
	
		cout << "open " << fileList[iFile].c_str() << endl;
	
		fChain->Add(fileList[iFile].c_str());
	}

	
	TString fileName;
	fileName = (isMC) ? "mcWZphys.root" : "WZphys.root";
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
	
	gROOT->ProcessLine(".L analysisGridControl.C++");
	gROOT->ProcessLine("analysisGridControl agc(fChain, fout, sRun, sRec, isMC);");
	gROOT->ProcessLine("agc.loop(0,0);");
}

