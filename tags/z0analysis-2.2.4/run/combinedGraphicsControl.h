/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define offlineChains_cxx
#include "offlineChains.C"

#define combinedGraphics_cxx
#include "combinedGraphics.C"

#ifndef COMBINEDGRAPHICSCONTROL_H
#define COMBINEDGRAPHICSCONTROL_H

class combinedGraphicsControl : public offlineChains, public combinedGraphics
{
	public:
		cutFlowHandler*   m_cutFlowHandler;
		combinedGraphics* m_combinedGraphics;
	
	public:
		combinedGraphicsControl();
		~combinedGraphicsControl();
		void execute();

	private:
};
#endif

