/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define fit_cxx
#include "fit.C"

#define Afb_cxx
#include "Afb.C"

#define tagNprobe_cxx
#include "tagNprobe.C"

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

class analysisModules : public selection,
						public cutFlowHandler,
						public periodHandler,
						public eventDumper,
						public graphicObjects,
						public fit,
						public tagNprobe,
						public Afb
{
	public:

		
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
			
			setCutFlowMapSVDPtr( cutFlowHandler::m_cutFlowMapSVD );
			ginitialize();
			setStyle();
		}
		~analysisModules();
		
		
	private:


};
#endif

