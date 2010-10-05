/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "combinedGraphicsControl.h"


combinedGraphicsControl::combinedGraphicsControl()
{
	string str = "";

	// read the cut flow (ownership: selection class which offlineAnalysis inherits from)
	str = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	m_cutFlowHandler = new cutFlowHandler(str);
	
	m_combinedGraphics = new combinedGraphics(m_cutFlowHandler);
}

combinedGraphicsControl::~combinedGraphicsControl()
{
	
}

void combinedGraphicsControl::execute()
{
	m_combinedGraphics->drawimass();
	m_combinedGraphics->drawpT();
	m_combinedGraphics->drawMCcutFlow();
	m_combinedGraphics->drawDataCutFlow();
}
