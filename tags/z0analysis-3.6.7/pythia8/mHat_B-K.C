{
   #include "TCanvas.h"

//=========Macro generated from canvas: Canvas 1/Canvas 1
//=========  (Wed Aug 24 18:24:25 2011) by ROOT version5.28/00c
   //TCanvas *Canvas = new TCanvas("Canvas 1", "Canvas 1",288,105,538,321);
   TCanvas *Canvas = new TCanvas("Canvas 1", "Canvas 1",600,400);
   Canvas->Range(-0.2375,-1.071429,2.1375,6.632557);
   Canvas->SetBorderSize(2);
   Canvas->SetLogy();
   Canvas->SetFrameFillColor(0);
   Canvas->SetFillColor(0);
   
   TH1F *htemp__1 = new TH1F("Invariant mass","",100,0,1.9);
   htemp__1->SetBinContent(4,8145);
   htemp__1->SetBinContent(5,384246);
   htemp__1->SetBinContent(6,51627);
   htemp__1->SetBinContent(7,4439);
   htemp__1->SetBinContent(8,1842);
   htemp__1->SetBinContent(9,1006);
   htemp__1->SetBinContent(10,576);
   htemp__1->SetBinContent(11,354);
   htemp__1->SetBinContent(12,277);
   htemp__1->SetBinContent(13,161);
   htemp__1->SetBinContent(14,136);
   htemp__1->SetBinContent(15,107);
   htemp__1->SetBinContent(16,78);
   htemp__1->SetBinContent(17,48);
   htemp__1->SetBinContent(18,45);
   htemp__1->SetBinContent(19,30);
   htemp__1->SetBinContent(20,21);
   htemp__1->SetBinContent(21,13);
   htemp__1->SetBinContent(22,26);
   htemp__1->SetBinContent(23,18);
   htemp__1->SetBinContent(24,12);
   htemp__1->SetBinContent(25,7);
   htemp__1->SetBinContent(26,6);
   htemp__1->SetBinContent(27,3);
   htemp__1->SetBinContent(28,6);
   htemp__1->SetBinContent(29,6);
   htemp__1->SetBinContent(30,3);
   htemp__1->SetBinContent(31,2);
   htemp__1->SetBinContent(32,1);
   htemp__1->SetBinContent(33,2);
   htemp__1->SetBinContent(34,5);
   htemp__1->SetBinContent(35,1);
   htemp__1->SetBinContent(36,1);
   htemp__1->SetBinContent(38,2);
   htemp__1->SetBinContent(40,2);
   htemp__1->SetBinContent(43,2);
   htemp__1->SetBinContent(44,1);
   htemp__1->SetBinContent(45,1);
   htemp__1->SetBinContent(46,1);
   htemp__1->SetBinContent(51,2);
   htemp__1->SetBinContent(92,1);
   htemp__1->SetEntries(453262);
   htemp__1->SetDirectory(0);
   
   htemp__1->SetYTitle("Events");
   htemp__1->SetXTitle("m_{#mu#mu} GeV");

   TPaveStats *ptstats = new TPaveStats(0.78,0.835,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(2);
   ptstats->SetTextAlign(12);
   TText *text = ptstats->AddText("htemp");
   text->SetTextSize(0.0368);
   text = ptstats->AddText("Entries = 453262 ");
   text = ptstats->AddText("Mean  = 0.09185");
   text = ptstats->AddText("RMS   = 0.01379");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   htemp__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(htemp__1->GetListOfFunctions());
   htemp__1->SetMarkerStyle(20);
   htemp__1->SetMarkerSize(0.9);
   htemp__1->GetXaxis()->SetTitle("m_{#mu#mu} GeV");
   htemp__1->Draw("");
  
/* 
   TPaveText *pt = new TPaveText(0.01,0.945,0.09554307,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   text = pt->AddText("");
   pt->Draw();
*/ 
   Canvas->Modified();
   Canvas->cd();
   Canvas->SetSelected(Canvas);
}
