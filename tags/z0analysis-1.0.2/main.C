/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 26/07/2010 12:36 */
/* * * * * * * * * * * */

void compileAll(TString sGRLtag)
{
	// add this software include paths
	gROOT->ProcessLine(".include include/");
	gROOT->ProcessLine(".include src/");

	// add the GRL include paths
	gROOT->ProcessLine(".include GoodRunsLists-" + sGRLtag + "/");
	gROOT->ProcessLine(".include GoodRunsLists-" + sGRLtag + "/GoodRunsLists/");

	// load the GRL lib
	gROOT->ProcessLine(".L GoodRunsLists-" + sGRLtag + "/StandAlone/libGoodRunsLists.so");

	// compile the analysisControl code and create an instance
	gROOT->ProcessLine(".L src/analysisControl.C++");
	gROOT->ProcessLine("analysisControl ac");
}

void loop(Long64_t startEvent=0, Long64_t stopEvent=0)
{
	ac.loop(startEvent, stopEvent);
}
