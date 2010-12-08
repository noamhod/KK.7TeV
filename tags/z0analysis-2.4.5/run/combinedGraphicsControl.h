/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define combinedGraphics_cxx
#include "combinedGraphics.C"

#ifndef COMBINEDGRAPHICSCONTROL_H
#define COMBINEDGRAPHICSCONTROL_H

class combinedGraphicsControl : public utilities
{
	public:
		combinedGraphics* m_combinedGraphics;
		TFile* m_histfile;
		
	
	public:
		combinedGraphicsControl();
		~combinedGraphicsControl();
		void initialize(string sAnalysisSelector);
		void finalize();
		void execute();

	private:
};
#endif

