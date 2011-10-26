#include <iostream>
#include <stdlib.h>
#include <stdio.h>      // for the sprintf call
#include <string>
#include <sstream>      // for the int to string operation (stringstream call)
#include <cstring>      // for the string functions
#include <math.h>
#include <cmath>
#include <complex>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include <time.h>
#include <pthread.h>
#include <iomanip>

#include <TROOT.h>
#include <TSystem.h>
#include <TMatrix.h>
#include <TVector.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TCut.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <TF1.h>
#include <TF2.h>
#include <TF12.h>
#include <TAxis.h>
#include <TLine.h>
#include <TPaveText.h>
#include <TThread.h>
#include <TList.h>
#include <Riostream.h>
#include <TDOMParser.h>
#include <TXMLNode.h>
#include <TXMLAttr.h>
#include <TEventList.h>

using namespace std;

typedef map<TString, TH1*>     TMapTSP2TH1;
typedef map<TString, TCanvas*> TMapTSP2TC;
typedef map<TString, TFile*>   TMapTSP2TF;

void make_intime_pileup_muhistos()
{
	TString path = "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/conf/";

	TMapTSP2TF fMap;
	fMap.insert( make_pair("A",new TFile(path+"data11_7TeV.periodA.root","READ")) );
	fMap.insert( make_pair("B",new TFile(path+"data11_7TeV.periodB.root","READ")) );
	fMap.insert( make_pair("D",new TFile(path+"data11_7TeV.periodD.root","READ")) );
	fMap.insert( make_pair("E",new TFile(path+"data11_7TeV.periodE.root","READ")) );
	fMap.insert( make_pair("F",new TFile(path+"data11_7TeV.periodF.root","READ")) );
	fMap.insert( make_pair("G",new TFile(path+"data11_7TeV.periodG.root","READ")) );
	fMap.insert( make_pair("H",new TFile(path+"data11_7TeV.periodH.root","READ")) );
	fMap.insert( make_pair("I",new TFile(path+"data11_7TeV.periodI.root","READ")) );
	fMap.insert( make_pair("J",new TFile(path+"data11_7TeV.periodJ.root","READ")) );
	fMap.insert( make_pair("K",new TFile(path+"data11_7TeV.periodK.root","READ")) );
	fMap.insert( make_pair("L",new TFile(path+"data11_7TeV.periodL.root","READ")) );
	fMap.insert( make_pair("M1",new TFile(path+"data11_7TeV.periodM1.root","READ")) );
	fMap.insert( make_pair("M2",new TFile(path+"data11_7TeV.periodM2.root","READ")) );

	TMapTSP2TH1 hMap;
	for(TMapTSP2TF::iterator it=fMap.begin() ; it!=fMap.end() ; it++)
	{  
		TString hname = (it->first=="A") ? "readyMuDist" : "intperbx";
		hMap.insert( make_pair(it->first,(TH1*)it->second->Get(hname)->Clone("")) );
	}

	/*
	TMapTSP2TC cMap;
	for(TMapTSP2TH1::iterator it=hMap.begin() ; it!=hMap.end() ; it++)
	{
		TString name = "c"+it->first;
		cMap.insert( make_pair(it->first, new TCanvas(name,name,600,400)) );
	}
	
	for(TMapTSP2TC::iterator it=cMap.begin() ; it!=cMap.end() ; it++)
	{
		it->second->cd();
		hMap[it->first]->Draw();
		//it->second->SaveAs("plots/period"+it->first+".png");
	}
	*/

	// merge:
	TH1* hBtoD = (TH1*)hMap["B"]->Clone("");
	hBtoD->Reset();
	hBtoD->SetName("intperbx");
	hBtoD->Add(hMap["B"]);
	hBtoD->Add(hMap["D"]);
	TCanvas* cBtoD = new TCanvas("cBtoD","",600,400);
	cBtoD->cd();
	hBtoD->Draw();
	cBtoD->SaveAs("plots/intimepileup_periodBtoD.png");
	cBtoD->SaveAs("plots/intimepileup_periodBtoD.root");
	hBtoD->SaveAs("plots/intimepileup_periodBtoD.root");
	
	TH1* hEtoH = (TH1*)hMap["E"]->Clone("");
	hEtoH->Reset();
	hEtoH->SetName("intperbx");
	hEtoH->Add(hMap["E"]);
	hEtoH->Add(hMap["F"]);
	hEtoH->Add(hMap["G"]);
	hEtoH->Add(hMap["H"]);
	TCanvas* cEtoH = new TCanvas("cEtoH","",600,400);
	cEtoH->cd();
	hEtoH->Draw();
	cEtoH->SaveAs("plots/intimepileup_periodEtoH.png");
	cEtoH->SaveAs("plots/intimepileup_periodEtoH.root");
	hEtoH->SaveAs("plots/intimepileup_periodEtoH.root");

	TH1* hItoK = (TH1*)hMap["I"]->Clone("");	
	hItoK->Reset();
	hItoK->SetName("intperbx");
	hItoK->Add(hMap["I"]);
	hItoK->Add(hMap["J"]);
	hItoK->Add(hMap["K"]);
	TCanvas* cItoK = new TCanvas("cItoK","",600,400);
	cItoK->cd();
	hItoK->Draw();
	cItoK->SaveAs("plots/intimepileup_periodItoK.png");
	cItoK->SaveAs("plots/intimepileup_periodItoK.root");
	hItoK->SaveAs("plots/intimepileup_periodItoK.root");

	TH1* hKtoM = (TH1*)hMap["K"]->Clone("");
	hKtoM->Reset();
	hKtoM->SetName("intperbx");
	hKtoM->Add(hMap["K"]);
	hKtoM->Add(hMap["L"]);
	hKtoM->Add(hMap["M1"]);
	hKtoM->Add(hMap["M2"]);
	TCanvas* cKtoM = new TCanvas("cKtoM","",600,400);
	cKtoM->cd();
	hKtoM->Draw();
	cKtoM->SaveAs("plots/intimepileup_periodKtoM.png");
	cKtoM->SaveAs("plots/intimepileup_periodKtoM.root");
	hKtoM->SaveAs("plots/intimepileup_periodKtoM.root");

	//for(TMapTSP2TF::iterator it=fMap.begin() ; it!=fMap.end() ; it++) fMap[it->first]->Close();
}
