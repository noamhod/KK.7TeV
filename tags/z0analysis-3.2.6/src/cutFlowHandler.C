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

	m_cutFlowOrdered     = new TMapds();
	m_cutFlowTypeOrdered = new TMapds();
	m_cutsFlowSkipMap    = new TMapsb();
	m_cutFlowNumbers     = new TMapsi();
	m_cutFlowMapSVD      = new TMapsvd();
	
	nAllEvents = 0;
	
	
	
	readCutFlow(sCutFlowFilePath);
}

cutFlowHandler::~cutFlowHandler()
{
	file->close();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void cutFlowHandler::setCutFlowFile(string sLogFilePath, string srunnumber)
{
	// file = new ofstream();
	// string sTime;
	// if(sRunNumber!="") sTime = "tmp/RunCutFlow." + sRunNumber + ".cuts"; // sRunNumber is static string from basicIncludes.h
	// else               sTime = "RunCutFlow_" + getDateHour() + ".cuts";
	// file->open( sTime.c_str() );
	
	string sLogFileName = sLogFilePath+"/RunCutFlow.run_"+srunnumber+".cuts";//".time_"+getDateHour()+".cuts";
	file = new ofstream( sLogFileName.c_str() );
}


void cutFlowHandler::incrementNallEvents()
{
	nAllEvents++;
}

void cutFlowHandler::parseKeyValLine(string sLine)
{
	/* * * * * * * * * * EXAMPLE * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	#TYPE#			#ORDER#		#SKIPFORT&P		#NAME#					#NVALUES#		#VALUE(S)
	#																					[1]		[2]		[3]#
	################
	# PRESELECTION #
	################
	preselection	0			0				GRL						1				 1.
	preselection	1			0				Trigger					1				 1.
	preselection	2			0				PV						3				 2.		 	1.		 200.
	#preselection	3			0				hipTmuon				2				 0.015	 	0.010
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	
	double tmpVal = 0.;

	if(m_dval.size()>0) m_dval.clear();

	// get the entire line:
	stringstream strm(sLine);
	
	// get the oreder of the cut:
	strm >> m_stype;
	
	// get the oreder of the cut:
	strm >> m_inum;
	
	// get the skip flag (0/1):
	strm >> m_iskip;
	
	// get the name of the cut:
	strm >> m_skey;
	
	// get the number of the cut parameters:
	strm >> m_nvals;
	
	// get the parameter(s) of the cut:
	while(!strm.eof())
	{
		strm >> tmpVal;
		m_dval.push_back(tmpVal);
	}
}

string cutFlowHandler::getType()
{
	return m_stype;
}

string cutFlowHandler::getKey()
{
	return m_skey;
}

int cutFlowHandler::getNum()
{
	return m_inum;
}

int cutFlowHandler::getSkip()
{
	return m_iskip;
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
	fstream f;
	f.open( sCutFlowFilePath.c_str() );

	string sLine = "";
	
	double dnum   = 0.;
	double dskip  = 0.;
	bool skipflag = false;
	string stype  = "";
	string skey   = "";
	double nvals  = 0.;
	vector<double> dval;

	vector<string> orderedVec;

	int nLinesRead = 0;

	if (!f)
	{
		cerr << "Unable to open file: " << sCutFlowFilePath << endl;
		exit(1);   // call system to stop
	}

	while(!f.eof())
	{
		getline(f,sLine);

		// skip empty lines and lines that begin with "#"
		if(sLine == "")              continue;
		if(sLine.substr(0,1) == "#") continue;

		// parse the line (ownership utilitis):
		parseKeyValLine(sLine);

		// get the cut type:
		stype = getType();
		
		// get the cut number:
		dnum = getNum();
		
		// get the cut skip flag (0/1):
		dskip    = getSkip();
		skipflag = (dskip==1.) ? true : false;
		
		// get the key = cut name (ownership utilitis):
		skey = getKey();
		
		// get the number of parameters
		nvals = getNVals();
		
		// get the cut parameters
		dval.clear();
		for(int i=0 ; i<(int)getNVals() ; i++) { dval.push_back( getVal(i) ); }

		nLinesRead++;

		cout << "type=" << stype << "\tnum=" << dnum << "\tkey=" << skey << "\tnvals=" << nvals << "\t";
		for(int i=0 ; i<(int)getNVals() ; i++)
		{
			cout << "   val[" << i << "]=" << dval[i];
		}
		cout << endl;

		// pair the maps:
		m_cutFlowMapSVD->insert( make_pair(skey,dval) );
		m_cutFlowTypeOrdered->insert( make_pair(dnum,stype) );
		m_cutsFlowSkipMap->insert( make_pair(skey,skipflag) );
		m_cutFlowOrdered->insert( make_pair(dnum,skey) );
		m_cutFlowNumbers->insert( make_pair(skey,0) );
	}
	cout << "\nread " << nLinesRead << " lines from " << sCutFlowFilePath << endl;
	
	f.close();
}

void cutFlowHandler::printCutFlowNumbers(Long64_t chainEntries)
{
	if(false) cout << "chainEntries = " << chainEntries << endl;
	cout << "+--------------------------------------------------------------------------" << endl;
	cout << "|                          print cut flow numbers                          " << endl;
	cout << "|.........................................................................." << endl;
	cout << "| processed: all " << nAllEvents << endl;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		double num = ii->first;
		string scutname = ii->second;
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") cout << "| PRESELECTION: " << scutname <<  " " << m_cutFlowNumbers->operator[](scutname) << endl;
		if(m_cutFlowTypeOrdered->operator[](num)=="selection")    cout << "| SELECTION: " << scutname <<  " " << m_cutFlowNumbers->operator[](scutname) << endl;
	}
	cout << "+--------------------------------------------------------------------------" << endl;
	
	
	// to file:
	(*file) << "+--------------------------------------------------------------------------" << endl;
	(*file) << "|                          print cut flow numbers                          " << endl;
	(*file) << "|.........................................................................." << endl;
	(*file) << "| processed: all " << nAllEvents << endl;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		double num = ii->first;
		string scutname = ii->second;
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") (*file) << "| PRESELECTION: " << scutname <<  " " << m_cutFlowNumbers->operator[](scutname) << endl;
		if(m_cutFlowTypeOrdered->operator[](num)=="selection")    (*file) << "| SELECTION: " << scutname <<  " " << m_cutFlowNumbers->operator[](scutname) << endl;
	}
	(*file) << "+--------------------------------------------------------------------------\n" << endl;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


TMapds* cutFlowHandler::getCutFlowOrderedMapPtr()
{
	return m_cutFlowOrdered;
}

TMapds* cutFlowHandler::getCutFlowTypeOrderedMapPtr()
{
	return m_cutFlowTypeOrdered;
}

TMapsi*  cutFlowHandler::getCutFlowNumbersMapPtr()
{
	return m_cutFlowNumbers;
}

TMapsvd* cutFlowHandler::getCutFlowMapSVDPtr()
{
	return m_cutFlowMapSVD;
}

TMapsb*	cutFlowHandler::getCutFlowToSkipMapPtr()
{
	return m_cutsFlowSkipMap;
}





////////////////////////////////////////////////////////////////////////////
bool cutflowXml::mask()
{
	for(TMapiP2cc::iterator ii=list->begin() ; ii!=list->end() ; ++ii)
	{
		int num    = ii->first;
		string str = (string)ii->second;
		_INFO("["+tostring(num)+"]="+str);
		
		if(str=="obj")
		{
			if(Next(ii)=="NAME")    name    = Next(ii); else {_ERROR("obj: failed to read NAME->"+PreviousStay(ii)); return false;}
			if(Next(ii)=="FLAG")    flag    = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read FLAG->"+PreviousStay(ii)); return false;}
			if(Next(ii)=="order")   order   = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read order->"+PreviousStay(ii)); return false;}
			if(Next(ii)=="phase")   phase   = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read phase->"+PreviousStay(ii)); return false;}
			if(Next(ii)=="skip")    skip    = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read skip->"+PreviousStay(ii)); return false;}
			if(Next(ii)=="nparameters") nparameters = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read nparameters->"+PreviousStay(ii)); return false;}
			_INFO("NAME="+name+", FLAG="+flag+", order="+order+", phase="+phase+", skip="+skip+", nparameters="+nparameters);

			if(Next(ii)=="parameters")
			{
				vdtmp.clear();
				for(int v=1 ; v<=validate_int(nparameters) ; ++v)
				{
					if(Next(ii)=="parameter") /* do nothing*/
					if(Next(ii)=="NAME")  attrname  = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read NAME->"+PreviousStay(ii)); return false;}
					if(Next(ii)=="ORDER") attrorder = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read ORDER->"+PreviousStay(ii)); return false;}
					if(Next(ii)=="TYPE")  attrtype  = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read TYPE->"+PreviousStay(ii)); return false;}
					val = Next(ii);
					_INFO("\tparameter["+tostring(v)+"] NAME="+attrname+", ORDER="+attrorder+", TYPE="+attrtype+", val="+val);
					// HAVE TO CHECK THE TYPE !!!!!
					vdtmp.push_back(validate_double(val));
				}
				if((int)vdtmp.size() != validate_int(nparameters)) {_ERROR("vector size doesn't match nparameters"); return false;}
			}
			else {_ERROR("obj NAME:"+name+" -> failed to read parameters->"+PreviousStay(ii)); return false;}
			
			if(Next(ii)=="description") description = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read description->"+PreviousStay(ii)); return false;}
			_INFO("description="+description);

			cutFlowOrdered->insert(     make_pair(validate_double(order),name) );
			cutFlowTypeOrdered->insert( make_pair(validate_double(order),phase) );
			cutFlowNumbers->insert(     make_pair(name,0) );
			cutFlowMapSVD->insert(      make_pair(name,vdtmp) );
			cutsFlowSkipMap->insert(    make_pair(name,validate_bool(skip)) );
		}
	}
	return true;
}


