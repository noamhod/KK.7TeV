/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "cutFlowHandler.h"

cutFlowHandler::cutFlowHandler()
{

}

cutFlowHandler::cutFlowHandler(string sCutFlowFilePath)
{
	b_print = false;

	m_cutFlowOrdered = new TMapds();
	m_cutFlowNumbers = new TMapsi();
	m_cutFlowMapSVD  = new TMapsvd();
	
	nAllEvents = 0;
	
	readCutFlow(sCutFlowFilePath);
}

cutFlowHandler::~cutFlowHandler()
{

}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void cutFlowHandler::parseKeyValLine(string sLine)
{
	/* * * * * * * * * * EXAMPLE * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	#ORDER#			#NAME#					#NVALUES#		#VALUE(S)#
	0				oppositeCharcge			1				0.
	1				pT						1				20000.
	2				eta						1				2.4
	3				cosThetaDimu			1				-0.99
	4				PV						3				2.				1.			150.
	* * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	
	double tmpVal = 0.;

	if(m_dval.size()>0) m_dval.clear();

	// get the entire line:
	stringstream strm(sLine);
	
	// get the oreder of the cut:
	strm >> m_inum;
	
	// get the name of the cut:
	strm >> m_skey;
	
	// get the number of the cut values:
	strm >> m_nvals;
	
	// get the value(s) of the cut:
	while(!strm.eof())
	{
		strm >> tmpVal;
		m_dval.push_back(tmpVal);
	}
}

string cutFlowHandler::getKey()
{
	return m_skey;
}

int cutFlowHandler::getNum()
{
	return m_inum;
}

double cutFlowHandler::getVal(int valNum)
{
	if( valNum<0 || valNum>=getNVals() )
	{
		cerr << "ERROR: valNum=" << valNum << " is out of range" << endl; exit(-1);
	}
	return m_dval[valNum];
}

void cutFlowHandler::getVal(vector<double>& dvalVec)
{
	dvalVec = m_dval;
}

int cutFlowHandler::getNVals()
{
	return (int)m_dval.size();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void cutFlowHandler::readCutFlow(string sCutFlowFilePath)
{
	fstream file;
	file.open( sCutFlowFilePath.c_str() );

	string sLine = "";
	
	double dnum   = 0.;
	string skey   = "";
	double nvals  = 0.;
	vector<double> dval;

	vector<string> orderedVec;

	int nLinesRead = 0;

	if (!file)
	{
		cerr << "Unable to open file: " << sCutFlowFilePath << endl;
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

		// get the cut number:
		dnum = getNum();
		
		// get the key = cut name (ownership utilitis):
		skey = getKey();
		
		// get the number of values
		nvals = getNVals();
		
		// get the cut values
		dval.clear();
		for(int i=0 ; i<(int)getNVals() ; i++) { dval.push_back( getVal(i) ); }

		nLinesRead++;

		if(b_print)
		{
			cout << "num=" << dnum << "\tkey=" << skey << "\tnvals=" << nvals << endl;
			for(int i=0 ; i<(int)getNVals() ; i++)
			{
				cout << "\tval[" << i << "]=" << dval[i];
			}
			cout << "\n" << endl;
		}

		// pair the map
		m_cutFlowMapSVD->insert( make_pair(skey,dval) );
		m_cutFlowOrdered->insert( make_pair(dnum,skey) );
		m_cutFlowNumbers->insert( make_pair(skey,0) );
	}
	cout << "\nread " << nLinesRead << " lines from " << sCutFlowFilePath << endl;
	
	file.close();
}

void cutFlowHandler::printCutFlowNumbers(Long64_t chainEntries)
{
	cout << "+------------------------------------------------" << endl;
	cout << "|             print cut flow numbers             " << endl;
	cout << "|................................................" << endl;
	cout << "|    all events in chain, " << chainEntries << endl;
	cout << "|    all processed events, " << nAllEvents << endl;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		string scutname = ii->second;
		cout << "|    events remaining after " << scutname << " cut, " << m_cutFlowNumbers->operator[](scutname) << endl;
	}
	cout << "+------------------------------------------------" << endl;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


TMapds* cutFlowHandler::getCutFlowOrderedMapPtr()
{
	return m_cutFlowOrdered;
}

TMapsi*  cutFlowHandler::getCutFlowNumbersMapPtr()
{
	return m_cutFlowNumbers;
}

TMapsvd* cutFlowHandler::getCutFlowMapSVDPtr()
{
	return m_cutFlowMapSVD;
}