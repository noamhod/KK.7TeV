/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef GRLinterface_cxx
#include "GRLinterface.h"

GRLinterface::GRLinterface() {}

GRLinterface::~GRLinterface() {}


void GRLinterface::glrinitialize(TString sxmlfile)
{
	//string sLine = ".L " + spath2lib + "libGoodRunsListsLib.so";
	//gROOT->ProcessLine( sLine.c_str() ); //somewhere in GoodRunsLists/....

	Root::TGoodRunsListReader GRLR( sxmlfile ); //<---- this is the GRL you have to downloaded
	GRLR.Interpret();

	//Root::TGoodRunsList grl( sxmlfile.c_str() )
	//m_grl.SetVersion("20")                 
	//m_grl.AddMetaData("Date","20091022")   
	//m_grl.AddRunLumiBlock(90210,18)
	//m_grl.AddRunLumiBlock(90210,19)
	//m_grl.AddRunLumiBlock(90210,20)
	//m_grl.Summary(true);

	m_grl = GRLR.GetMergedGoodRunsList();
	m_grl.Summary(kTRUE);
}

void GRLinterface::glrfinalize()
{

}

#endif

