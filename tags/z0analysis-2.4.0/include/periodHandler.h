/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef PERIODHANDLER_H
#define PERIODHANDLER_H

class periodHandler
{
	public:
		bool b_print;
		
		// variables
		string  m_speriod;
		int    	m_firstrun;
		int    	m_lastrun;
		int     m_ntrigs;
		vector<string>* m_trigs;
		
		TMapis*  m_firstrun2periodMap;
		TMapis*  m_lastrun2periodMap;
		TMapsP2vs* m_period2triggerMap;

	public:
		periodHandler();
		periodHandler(string sPeriodFilePath);
		~periodHandler();

		void parseKeyValLine(string sLine);
		void readPeriods(string sPeriodFilePath);
		
		string          getPeriod(int runNumber, TMapis* firstrun2periodMap, TMapis* lastrun2periodMap);
		vector<string>* getTrigs(string sPeriod, TMapsP2vs* period2triggerMap);
		
		TMapis*  getFirstRun2PeriodMapPtr();
		TMapis*  getLastRun2PeriodMapPtr();
		TMapsP2vs* getPeriod2TriggerMapPtr();

		string getPeriod();
		int getFirstRun();
		int getLastRun();
		int getNtrigs();
		vector<string>* getTriggers();
		int getTrigsSize();

};
#endif

