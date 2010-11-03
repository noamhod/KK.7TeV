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
	
	//m_trigs = new vector<string>;
	
	readPeriods(sPeriodFilePath);
}

periodHandler::~periodHandler()
{

}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void periodHandler::parseKeyValLine(string sLine)
{
	/* * * * * * * * * * EXAMPLE * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	#PERIODRANGE		#RUNNUMBERSTART			#RUNNUMBEREND			#NTRIGS		#TRIGGERS
	A					152166					153200					1			L1_MU10
	B1-B2				153565					155160					1			L1_MU10 
	C1					155228					155697					1			L1_MU10
	C2					156682					156682					1			L1_MU10
	D1-D6				158045					159224					1			L1_MU10
	E1					160387					160479					1			L1_MU10
	E2					160530					160530					1			L1_MU10
	E3					160613					160879					1			L1_MU10
	E4					160899					160980					2			EF_mu10		EF_mu10_MG
	E5					161118					161379					2			EF_mu10		EF_mu10_MG
	E6					161407					161520					2			EF_mu10		EF_mu10_MG
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
		
		// get the number of possible triggers
		ntrigs = getNtrigs();
		
		// get the triggers
		vtrigs = getTriggers();

		nLinesRead++;

		if(b_print)
		{
			cout << "period=" << speriod << "\trange=" << firstrun << "-" << lastrun << "\ttriggers=" << ntrigs;
			for(int i=0 ; i<(int)getNtrigs() ; i++)
			{
				cout << "\ttrig[" << i << "]=" << vtrigs->at(i);
			}
		}
		cout << endl;
		
		// pair the maps:
		m_firstrun2periodMap->insert( make_pair(firstrun,speriod) );
		m_lastrun2periodMap->insert( make_pair(lastrun,speriod) );
		m_period2triggerMap->insert( make_pair(speriod,vtrigs) );
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
