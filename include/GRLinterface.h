/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

// gROOT.ProcessLine( " .include $PWD/GoodRunsLists-00-00-84/GoodRunsLists/  " );
// gROOT.ProcessLine( " .include $PWD/GoodRunsLists-00-00-84/  " );

#include "TUniqueGRLString.h"
//#include "TriggerRegistryTool.h"
#include "TMsgLogger.h"
//#include "TLumiBlockRange.h"
#include "TGRLCollection.h"
//#include "TGoodRunsListWriter.h"

#include "TGoodRunsListReader.h"
#include "TGoodRunsList.h"

#include "TGoodRun.h"
#include "StrUtil.h"
#include "RegularFormula.h"
//#include "ITriggerRegistryTool.h"
//#include "IGoodRunsListSelectorTool.h"
//#include "GoodRunsListSelectorTool.h"
//#include "DQHelperFunctions.h"

#ifndef GRLINTERFACE_H
#define GRLINTERFACE_H

class GRLinterface
{
	public:
		//Root::TGoodRunsListReader m_GRLR;
		Root::TGoodRunsList m_grl;
	public:
		GRLinterface();
		~GRLinterface();
	
		void glrinitialize(TString sxmlfile);
        void glrfinalize();
	
	private:

};
#endif

