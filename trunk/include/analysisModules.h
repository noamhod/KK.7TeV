/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define fit_cxx
#include "fit.C"

#define selection_cxx
#include "selection.C"

#define graphicObjects_cxx
#include "graphicObjects.C"

#define cutFlowHandler_cxx
#include "cutFlowHandler.C"

#define periodHandler_cxx
#include "periodHandler.C"

#define eventDumper_cxx
#include "eventDumper.C"


#ifndef ANALYSISMUDULES_H
#define ANALYSISMUDULES_H

class analysisModules : public cutFlowHandler,
						public periodHandler,
						public eventDumper,
						public graphicObjects,
						public fit
{
	public:
		// pointers to modules
	
	/*
		graphicObjects* m_graphicobjs;
	
		cutFlowHandler* m_cutFlowHandler;
		TMapsvd* m_cutFlowMapSVD;
		TMapds*  m_cutFlowOrdered;
		TMapds*  m_cutFlowTypeOrdered;
		TMapsi*  m_cutFlowNumbers;
		
		periodHandler* m_periodHandler;
		TMapis*  m_firstrun2periodMap;
		TMapis*  m_lastrun2periodMap;
		TMapsvs* m_period2triggerMap;
	
		eventDumper* m_eventDumper;

		fit* m_fitter;
	*/
		
	public:
		analysisModules();
		analysisModules(string sCutFlowFilePath, string sPeriodsFilePath, string sEventDumpFilePath) :
		cutFlowHandler(sCutFlowFilePath),
		periodHandler(sPeriodsFilePath),
		eventDumper(sEventDumpFilePath)
		{	
			if(sEventDumpFilePath != "")
			{
				setInterestingThreshold( 250.*GeV2TeV );
			}
			
			setCutFlowMapSVDPtr( m_cutFlowMapSVD );
			ginitialize();
		}
		~analysisModules();
		
		
	private:


};
#endif

