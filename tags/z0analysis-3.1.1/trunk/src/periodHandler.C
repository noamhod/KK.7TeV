/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "periodHandler.h"

periodHandler::periodHandler()
{

}

periodHandler::periodHandler(string sPeriodFilePath)
{
	b_print = true;
	m_firstrun2periodMap = new TMapis();
	m_lastrun2periodMap  = new TMapis();
	m_period2triggerMap  = new TMapsP2vs();
	m_period2triggerperiodMap = new TMapss();
	m_period2pTthresholdMap = new TMapsd();
	m_period2pTminMap = new TMapsd();
	
	readPeriods(sPeriodFilePath);
}

periodHandler::~periodHandler()
{

}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void periodHandler::parseKeyValLine(string sLine)
{
	/* * * * * * * * * * EXAMPLE * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	#PERIODRANGE		#RUNNUMBERSTART		#RUNNUMBEREND	#PTMIN	#PTTHREHS	#NTRIGS		#TRIGGERS
	#--- monte carlo
	MC					100000				110000			1		10			1			L1_MU10
	#--- data
	A					152166				153200			1		10			1			L1_MU10
	B1-B2				153565				155160			1		10			1			L1_MU10
	E4					160899				160980			1		10			2			EF_mu10			EF_mu10_MG
	E5					161118				161379			1		10			2			EF_mu10			EF_mu10_MG
	G5					165821				166143			1		13			2			EF_mu13			EF_mu13_MG
	G6					166198				166383			1		13			2			EF_mu13			EF_mu13_MG
	I1					167575				167680			1		13			2			EF_mu13_tight	EF_mu13_MG_tight
	I2					167776				167844			1		13			2			EF_mu13_tight	EF_mu13_MG_tight
	* * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	//if(m_trigs->size()>0) m_trigs->clear();
	m_trigs = new vector<string>;

	// get the entire line:
	stringstream strm(sLine);
	
	// get the period name:
	strm >> m_speriod;
	
	// get the start range of runs:
	strm >> m_firstrun;
	
	// get the end range of runs:
	strm >> m_lastrun;
	
	// get the trigger pT min
	strm >> m_trig_pTmin;
	
	// get the trigger pT threshold
	strm >> m_trig_pTthreshold;
	
	// get the number of triggers:
	strm >> m_ntrigs;
	
	// get the triggers names:
	int i=1;
	while(i<=m_ntrigs  &&  !strm.eof())
	{
		string tmpSVal;
		strm >> tmpSVal;
		m_trigs->push_back(tmpSVal);
		i++;
	}
}


void periodHandler::readPeriods(string sPeriodFilePath)
{
	fstream file;
	file.open( sPeriodFilePath.c_str() );

	string sLine = "";
	
	string speriod;
	int    firstrun;
	int    lastrun;
	double pTmin;
	double pTthreshold;
	int    ntrigs;
	vector<string>* vtrigs;

	int nLinesRead = 0;

	if (!file)
	{
		cerr << "Unable to open file: " << sPeriodFilePath << endl;
		exit(1);   // call system to stop
	}

	while(!file.eof())
	{
		getline(file,sLine);

		// skip empty lines and lines that begin with "#"
		if(sLine == "")              continue;
		if(sLine.substr(0,1) == "#") continue;

		// parse the line (ownership utilitis):
		parseKeyValLine(sLine);

		// get the period:
		speriod = getPeriod();
		
		// get the start run:
		firstrun = getFirstRun();
		
		// get the end run:
		lastrun = getLastRun();
		
		// get the trigger pT min
		pTmin = getTrig_pTmin();
		
		// get the trigger pT threshold
		pTthreshold = getTrig_pTthreshold();
		
		// get the number of possible triggers
		ntrigs = getNtrigs();
		
		// get the triggers
		vtrigs = getTriggers();

		nLinesRead++;

		cout << "period=" << speriod
			 << "\trange=" << firstrun << "-" << lastrun
			 << "\ttriggers(pTmin=" << pTmin << " GeV, pTthreshold=" << pTthreshold << " GeV) = " << ntrigs;
		for(int i=0 ; i<(int)getNtrigs() ; i++)
		{
			cout << "\ttrig[" << i << "]=" << vtrigs->at(i);
		}
		cout << endl;
		
		string sTriggerPeriod = "";
		for(int i=0 ; i<(int)getNtrigs() ; i++)
		{
			if(i==0) sTriggerPeriod += vtrigs->at(i);
			if(i>0)  sTriggerPeriod += "||" + vtrigs->at(i);
		}
		
		// pair the maps:
		m_firstrun2periodMap->insert( make_pair(firstrun,speriod) );
		m_lastrun2periodMap->insert( make_pair(lastrun,speriod) );
		m_period2triggerMap->insert( make_pair(speriod,vtrigs) );
		m_period2triggerperiodMap->insert( make_pair(speriod,sTriggerPeriod) );
		m_period2pTminMap->insert( make_pair(speriod,pTmin) );
		m_period2pTthresholdMap->insert( make_pair(speriod,pTthreshold) );
	}
	cout << "\nread " << nLinesRead << " lines from " << sPeriodFilePath << "\n" << endl;
	
	file.close();
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


string periodHandler::getPeriod()
{
	return m_speriod;
}

int periodHandler::getFirstRun()
{
	return m_firstrun;
}

int periodHandler::getLastRun()
{
	return m_lastrun;
}

double periodHandler::getTrig_pTmin()
{
	return m_trig_pTmin;
}

double periodHandler::getTrig_pTthreshold()
{
	return m_trig_pTthreshold;
}

int periodHandler::getNtrigs()
{
	return m_ntrigs;
}

vector<string>* periodHandler::getTriggers()
{
	return m_trigs;
}

int periodHandler::getTrigsSize()
{
	return (int)m_trigs->size();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


TMapis* periodHandler::getFirstRun2PeriodMapPtr()
{
	return m_firstrun2periodMap;
}

TMapis* periodHandler::getLastRun2PeriodMapPtr()
{
	return m_lastrun2periodMap;
}

TMapsP2vs* periodHandler::getPeriod2TriggerMapPtr()
{
	return m_period2triggerMap;
}

TMapsd* periodHandler::getPeriod2pTthresholdMapPtr()
{
	return m_period2pTthresholdMap;
}

TMapsd* periodHandler::getPeriod2pTminMapPtr()
{
	return m_period2pTminMap;
}

TMapss* periodHandler::getPeriod2triggerperiodMapPtr()
{
	return m_period2triggerperiodMap;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


string periodHandler::getPeriod(int runNumber, TMapis* firstrun2periodMap, TMapis* lastrun2periodMap)
{	
	int fst = 0;
	int lst = 0;
	
	TMapis::iterator ifst = firstrun2periodMap->begin();
	TMapis::iterator ilst = lastrun2periodMap->begin();
		
	// find the run range
	while(ifst!=firstrun2periodMap->end()  &&  ilst!=lastrun2periodMap->end())
	{
		int tmpfst = ifst->first;
		int tmplst = ilst->first;
				
		if(runNumber>=tmpfst  &&  runNumber<=tmplst)
		{
			fst = tmpfst;
			lst = lst;
			break;
		}
		
		ifst++;
		ilst++;
	}
	
	// check the period name
	if(ifst->second != ilst->second)
	{
		cout << "Error: didn't find a period, exitting now..." << endl;
		exit(-1);
	}
		
	// get the period name
	string sPeriod = ifst->second;
		
	return sPeriod;
}

vector<string>* periodHandler::getTrigs(string sPeriod, TMapsP2vs* period2triggerMap)
{
	TMapsP2vs::iterator it = period2triggerMap->find(sPeriod);
	return it->second;
}
