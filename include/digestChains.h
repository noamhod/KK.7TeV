/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef DIGESTCHAINS_H
#define DIGESTCHAINS_H

class digestChains
{
public:
	// pointers
	TChain* m_chain;

public:
	digestChains();
	~digestChains();
	
	void cinitialize();
	void cfinalize();
	
	void list2chain(string sListFilePath, string sListContentAbsolutePath = "";
	void makeChain(bool doList = false, string sListFilePath = "dataset.list", string sListContentAbsolutePath = "");
	void drawFromChain();	

private:

};
#endif

