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
		double  m_trig_pTmin;
		double  m_trig_pTthreshold;
		int     m_ntrigs;
		vector<string>* m_trigs;
		
		TMapis*    m_firstrun2periodMap;
		TMapis*    m_lastrun2periodMap;
		TMapsP2vs* m_period2triggerMap;
		TMapss*    m_period2triggerperiodMap;
		TMapsd*    m_period2pTthresholdMap;
		TMapsd*    m_period2pTminMap;

	public:
		periodHandler();
		periodHandler(string sPeriodFilePath);
		~periodHandler();

		void parseKeyValLine(string sLine);
		void readPeriods(string sPeriodFilePath);
		
		string          getPeriod(int runNumber, TMapis* firstrun2periodMap, TMapis* lastrun2periodMap);
		vector<string>* getTrigs(string sPeriod, TMapsP2vs* period2triggerMap);
		
		TMapis*    getFirstRun2PeriodMapPtr();
		TMapis*    getLastRun2PeriodMapPtr();
		TMapsP2vs* getPeriod2TriggerMapPtr();
		TMapsd*    getPeriod2pTthresholdMapPtr();
		TMapsd*    getPeriod2pTminMapPtr();
		TMapss*    getPeriod2triggerperiodMapPtr();

		string getPeriod();
		int getFirstRun();
		int getLastRun();
		double getTrig_pTmin();
		double getTrig_pTthreshold();
		int getNtrigs();
		vector<string>* getTriggers();
		int getTrigsSize();

};


////////////////////////////////////////////////////////////
class periodsXml : public XML
{
	public:
		periodsXml()
		{
			ignoreString("obj");
			ignoreString("NAME");
			ignoreString("FLAG");
			ignoreString("PRIORITY");
			ignoreString("trigger");
			ignoreString("period");
			ignoreString("triggerperiod");
		}
		virtual ~periodsXml(){}
		bool mask();

		/*
		<obj NAME="MC" FLAG="on">
			<start>100000</start>
			<end>150000</end>
			<pTmin>1.</pTmin>
			<ntriggers>1</ntriggers>
			<triggers>
				<trigger NAME="L1_MU10" PRIORITY="1" FLAG="on">10.</trigger>
			</triggers>
			<nevents>-1</nevents>
			<luminosity>-1</luminosity>
			<description>
				The values are in GeV and pb^-1.
			</description>
		</obj>
		*/
		
		/*
		<obj NAME="TRIGGERPERIODS" NUMBER="4">
			<triggerperiods>
				<triggerperiod NAME="L1_MU10" FLAG="on">0.272906894</triggerperiod>
				<triggerperiod NAME="EF_mu10" FLAG="on">3.03978</triggerperiod>
				<triggerperiod NAME="EF_mu13" FLAG="on">6.89501</triggerperiod>
				<triggerperiod NAME="EF_mu13_tight" FLAG="on">31.47316</triggerperiod>
			</triggerperiods>
			<description>
				The values are in pb^-1.
			</description>
		</obj>
		*/
	
		// specific mask for periodsXml.xml
		string name;
		string flag;
		string start;
		string end;
		string pTmin;
		string ntriggers;
		string attrname;
		string trigpriority;
		string attrflag;
		string trigpT;
		string nevents;
		string luminosity;
		string description;
		string number;
	private:
};



#endif

