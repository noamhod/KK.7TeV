/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

{
	TStyle *atlasStyle= new TStyle("ATLAS","Atlas style");

	//atlasStyle->SetErrorX(0.);

	// use plain black on white colors
	Int_t icol=0;
	atlasStyle->SetFrameBorderMode(icol);
	atlasStyle->SetCanvasBorderMode(icol);
	atlasStyle->SetPadBorderMode(icol);
	atlasStyle->SetPadColor(icol);
	atlasStyle->SetCanvasColor(icol);
	atlasStyle->SetStatColor(icol);
	//atlasStyle->SetFillColor(icol);
	atlasStyle->SetFrameFillColor(icol);
	atlasStyle->SetTitleFillColor(icol);


	// set the paper & margin sizes
	atlasStyle->SetPaperSize(20,26);
	atlasStyle->SetPadTopMargin(0.05);
	atlasStyle->SetPadRightMargin(0.05);
	atlasStyle->SetPadBottomMargin(0.16);
	atlasStyle->SetPadLeftMargin(0.12);

	// use large fonts
	//Int_t font=72;
	Int_t font=42;
	Double_t tsize=0.05;
	atlasStyle->SetTextFont(font);


	atlasStyle->SetTextSize(tsize);
	atlasStyle->SetLabelFont(font,"x");
	atlasStyle->SetTitleFont(font,"x");
	atlasStyle->SetLabelFont(font,"y");
	atlasStyle->SetTitleFont(font,"y");
	atlasStyle->SetLabelFont(font,"z");
	atlasStyle->SetTitleFont(font,"z");

	atlasStyle->SetLabelSize(tsize,"x");
	atlasStyle->SetTitleSize(tsize,"x");
	atlasStyle->SetLabelSize(tsize,"y");
	atlasStyle->SetTitleSize(tsize,"y");
	atlasStyle->SetLabelSize(tsize,"z");
	atlasStyle->SetTitleSize(tsize,"z");


	//use bold lines and markers
	atlasStyle->SetMarkerStyle(20);
	atlasStyle->SetMarkerSize(0.9); //1 //1.2
	atlasStyle->SetHistLineWidth(1.5);
	atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

	//get rid of X error bars and y error bar caps
	//atlasStyle->SetErrorX(0.001);

	//do not display any of the standard histogram decorations
	atlasStyle->SetOptTitle(0);
	//atlasStyle->SetOptStat(1111);
	atlasStyle->SetOptStat(0);
	//atlasStyle->SetOptFit(1111);
	atlasStyle->SetOptFit(0);

	// put tick marks on top and RHS of plots
	atlasStyle->SetPadTickX(1);
	atlasStyle->SetPadTickY(1);

	gROOT->SetStyle("Plain");

	// Stats

/*
	atlasStyle->SetStatBorderSize(0);
	atlasStyle->SetStatColor(0);
	atlasStyle->SetStatX(0.92);
	atlasStyle->SetStatY(0.90);
	atlasStyle->SetStatFont(42);
	atlasStyle->SetStatFontSize(0.03);
	atlasStyle->SetOptStat(111110);
	atlasStyle->SetStatW(0.16);
	atlasStyle->SetStatH(0.2);
	atlasStyle->SetStatFormat("7.4f");
	atlasStyle->SetFitFormat("7.4f");
	atlasStyle->SetStripDecimals(kFALSE);
*/
	atlasStyle->SetStatBorderSize(0);
	atlasStyle->SetStatColor(0);
	atlasStyle->SetStatX(0);
	atlasStyle->SetStatY(0);
	atlasStyle->SetStatFont(42);
	atlasStyle->SetStatFontSize(0);
	atlasStyle->SetOptStat(0);
	atlasStyle->SetStatW(0);
	atlasStyle->SetStatH(0);
	atlasStyle->SetStatFormat("7.4f");
	atlasStyle->SetFitFormat("7.4f");
	atlasStyle->SetStripDecimals(kFALSE);

	//gStyle->SetPadTickX(1);
	//gStyle->SetPadTickY(1);
}


