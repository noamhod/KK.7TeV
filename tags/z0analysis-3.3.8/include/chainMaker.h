/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef CHAINMAKER_H
#define CHAINMAKER_H

class chainMaker
{
	public:
		// pointers
		TChain* m_chain;
		
		// locals
		vector<string>* m_vStr2find;

	public:
		chainMaker();
		~chainMaker();
		
		void chainInit(vector<string>* vStr2find);
		void list2chain(string sListFilePath, string sListContentAbsolutePath = "", int runNumber = 0);
		void makeChain(bool doList = false, string sListFilePath = "dataset.list", string sListContentAbsolutePath = "", int runNumber = 0);
		void drawFromChain();	

	private:
};
#endif

