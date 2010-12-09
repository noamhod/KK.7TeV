/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include <TROOT.h>
#include <TObject.h>
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TVirtualPad.h>
#include <TPaveText.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>      // for the sprintf call
#include <string>
#include <sstream>      // for the int to string operation (stringstream call)
#include <cstring>      // for the string functions
#include <fstream>
#include <vector>

using namespace std;

TCanvas* c;

TCanvas* getCanvas(TFile* f, string dir, string cname)
{
	string path = dir + "/" +cname;
	TCanvas* c = (TCanvas*)f->Get( path.c_str() );
	return c;
}


void fixHisto(TFile* f, string dir, string hname)
{
	string path = dir + "/" +hname;
	TH1D* h = (TH1D*)f->Get( path.c_str() );
	h->SetTitle("");
	h->SetXTitle("#hat{m}_{#mu#mu} (MeV)");
	h->SetYTitle("Events");
	f->cd( dir.c_str() );
	h->Write();
	f->Write();
}

void drawCutFlow()
{
	string dir = "/srv01/tau/hod/z0analysis/data/";
	string path = "";
	
	// main canvas
	c = new TCanvas("c", "c", 1200, 800);
	c->Divide(2,3);
	c->Draw();
	c->cd();
	c->Update();
	
	// pads
	path = dir + "mcOfflineControl_Zmumu.root";
	TFile* fZmumu = new TFile( path.c_str(), "UPDATE" );
	//fixHisto(fZmumu, "cutFlow", "imass.oppositeCharcge");
	TCanvas* cZmumu = getCanvas(fZmumu, "cutFlow", "imass.cutFlow");
	cZmumu->SetTitle("");
	c->cd(1);
	TPaveText* pZmumu = new TPaveText(0.35, 0.78, 0.65, 0.9, "NDC");
	pZmumu->SetFillColor(kWhite);
	TText* tZmumu = pZmumu->AddText("Z #rightarrow #mu^{+}#mu^{-}");
	cZmumu->DrawClonePad();
	pZmumu->Draw("SMAE");
	
	path = dir + "mcOfflineControl_Wmunu.root";
	TFile* fWmunu = new TFile( path.c_str(), "UPDATE" );
	//fixHisto(fWmunu, "cutFlow", "imass.oppositeCharcge");
	TCanvas* cWmunu = getCanvas(fWmunu, "cutFlow", "imass.cutFlow");
	cWmunu->SetTitle("");
	c->cd(2);
	cWmunu->DrawClonePad();
	TPaveText* pWmunu = new TPaveText(0.35, 0.78, 0.65, 0.9, "NDC");
	pWmunu->SetFillColor(kWhite);
	TText* tWmunu = pWmunu->AddText("W #rightarrow #mu#nuX");
	pWmunu->Draw("SMAE");
	
	path = dir + "mcOfflineControl_Ztautau.root";
	TFile* fZtautau = new TFile( path.c_str(), "UPDATE" );
	//fixHisto(fZtautau, "cutFlow", "imass.oppositeCharcge");
	TCanvas* cZtautau = getCanvas(fZtautau, "cutFlow", "imass.cutFlow");
	cZtautau->SetTitle("");
	c->cd(3);
	cZtautau->DrawClonePad();
	TPaveText* pZtautau = new TPaveText(0.35, 0.78, 0.65, 0.9, "NDC");
	pZtautau->SetFillColor(kWhite);
	TText* tZtautau = pZtautau->AddText("Z #rightarrow #tau^{+}#tau^{-}");
	pZtautau->Draw("SMAE");
	
	path = dir + "mcOfflineControl_TTbar.root";
	TFile* fTTbar = new TFile( path.c_str(), "UPDATE" );
	//fixHisto(fTTbar, "cutFlow", "imass.oppositeCharcge");
	TCanvas* cTTbar = getCanvas(fTTbar, "cutFlow", "imass.cutFlow");
	cTTbar->SetTitle("");
	c->cd(4);
	cTTbar->DrawClonePad();
	TPaveText* pTTbar = new TPaveText(0.35, 0.78, 0.65, 0.9, "NDC");
	pTTbar->SetFillColor(kWhite);
	TText* tTTbar = pTTbar->AddText("t #bar{t} #rightarrow #mu^{+}#mu^{-}X");
	pTTbar->Draw("SMAE");
	
	path = dir + "mcOfflineControl_bbmuX15.root";
	TFile* fbbmuX15 = new TFile( path.c_str(), "UPDATE" );
	//fixHisto(fbbmuX15, "cutFlow", "imass.oppositeCharcge");
	TCanvas* cbbmuX15 = getCanvas(fbbmuX15, "cutFlow", "imass.cutFlow");
	cbbmuX15->SetTitle("");
	c->cd(5);
	cbbmuX15->DrawClonePad();
	TPaveText* pbbmuX15 = new TPaveText(0.35, 0.78, 0.65, 0.9, "NDC");
	pbbmuX15->SetFillColor(kWhite);
	TText* tbbmuX15 = pbbmuX15->AddText("b #bar{b} #rightarrow #mu^{+}#mu^{-}X");
	pbbmuX15->Draw("SMAE");
	
	path = dir + "mcOfflineControl_ccmuX15.root";
	TFile* fccmuX15 = new TFile( path.c_str(), "UPDATE" );
	//fixHisto(fccmuX15, "cutFlow", "imass.oppositeCharcge");
	TCanvas* cccmuX15 = getCanvas(fccmuX15, "cutFlow", "imass.cutFlow");
	cccmuX15->SetTitle("");
	c->cd(6);
	cccmuX15->DrawClonePad();
	TPaveText* pccmuX15 = new TPaveText(0.35, 0.78, 0.65, 0.9, "NDC");
	pccmuX15->SetFillColor(kWhite);
	TText* tccmuX15 = pccmuX15->AddText("c #bar{c} #rightarrow #mu^{+}#mu^{-}X");
	pccmuX15->Draw("SMAE");
}
