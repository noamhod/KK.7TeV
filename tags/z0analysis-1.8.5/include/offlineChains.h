/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef OFFLINECHAINS_H
#define OFFLINECHAINS_H

class offlineChains
{
	public:
		// pointers
		TChain* m_chain;

	public:
		offlineChains();
		~offlineChains();
	
		void cinitialize();
                void cfinalize();
	
		void list2chain(string sListFilePath, string sListContentAbsolutePath = "");
		void makeChain(bool doList = false, string sListFilePath = "dataset.list", string sListContentAbsolutePath = "");
		void drawFromChain();	

	private:

};
#endif

