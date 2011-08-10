/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef PERIODHANDLER_H
#define PERIODHANDLER_H

class periodHandler : public XML
{
	public:
		bool b_print;
		
		// variables
		string  m_speriod;
		int    	m_firstrun;
		int    	m_lastrun;
		double  m_trig_pTmin;
		double  m_trig_pTthreshold;
		int     m_ntrigs;
		vector<string>* m_trigs;
		
		TMapis*    m_firstrun2periodMap;
		TMapis*    m_lastrun2periodMap;
		TMapsP2vs* m_period2triggerMap;
		TMapss*    m_period2triggerperiodMap;
		TMapsP2vd* m_period2pTthresholdMap;
		TMapsP2vd* m_period2pTminMap;

	public:
		periodHandler()
		{
			ignoreString("obj");
			ignoreString("NAME");
			ignoreString("FLAG");
			ignoreString("MIN");
			ignoreString("PRIORITY");
			ignoreString("trigger");
			ignoreString("period");
			ignoreString("triggerperiod");
			
			b_print = true;
			m_firstrun2periodMap      = new TMapis;
			m_lastrun2periodMap       = new TMapis;
			m_period2triggerMap       = new TMapsP2vs;
			m_period2triggerperiodMap = new TMapss;
			m_period2pTthresholdMap   = new TMapsP2vd;
			m_period2pTminMap         = new TMapsP2vd;
		}
		virtual ~periodHandler() {}
		
		bool mask();

		void parseKeyValLine(string sLine);
		
		string          getPeriod(int runNumber, TMapis* firstrun2periodMap, TMapis* lastrun2periodMap);
		vector<string>* getTrigs(string sPeriod, TMapsP2vs* period2triggerMap);
		
		TMapis*    getFirstRun2PeriodMapPtr();
		TMapis*    getLastRun2PeriodMapPtr();
		TMapsP2vs* getPeriod2TriggerMapPtr();
		TMapsP2vd* getPeriod2pTthresholdMapPtr();
		TMapsP2vd* getPeriod2pTminMapPtr();
		TMapss*    getPeriod2triggerperiodMapPtr();

		string getPeriod();
		int getFirstRun();
		int getLastRun();
		double getTrig_pTmin();
		double getTrig_pTthreshold();
		int getNtrigs();
		vector<string>* getTriggers();
		int getTrigsSize();
	
	private:
		// specific mask for periodsXml.xml
		string name;
		string flag;
		string start;
		string end;
		string ntriggers;
		string attrname;
		string trigpriority;
		string attrflag;
		string trigpT;
		string nevents;
		string luminosity;
		string description;
		string number;
		vector<double>* vdtmp_ptmin;
		vector<double>* vdtmp_lumi;
		vector<double>* vdtmp_ptthresh;
		vector<string>* vstmp_name;
		vector<string>* vstmp_tname;
};


#endif

