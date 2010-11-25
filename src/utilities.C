/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "utilities.h"

utilities::utilities()
{

}

utilities::~utilities()
{

}

string utilities::getDateHour()
{
	time_t rawtime;
	struct tm* timeinfo;
	// get current timeinfo
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	mktime ( timeinfo );
	stringstream strm;
	string str;
	
	strm << "day" << timeinfo->tm_mday << "." << timeinfo->tm_mon+1 << "." << timeinfo->tm_year+1900 << "_hour" << timeinfo->tm_hour << "." << timeinfo->tm_min+1 << endl;
	strm >> str;
	/*
	Member	Meaning	Range
	tm_sec	seconds after the minute	0-61*
	tm_min	minutes after the hour	0-59
	tm_hour	hours since midnight	0-23
	tm_mday	day of the month	1-31
	tm_mon	months since January	0-11
	tm_year	years since 1900	
	tm_wday	days since Sunday	0-6
	tm_yday	days since January 1	0-365
	tm_isdst	Daylight Saving Time flag	
	*/
	
	return str;
}

void utilities::startTimer()
{
	clockStart = clock();
}

void utilities::stopTimer(bool print)
{
	clockEnd = clock();
	if(print) cout << "RUN TIME: " << getRunTime() << " seconds" << endl;
}

double utilities::getRunTime()
{
	return(double)(clockEnd-clockStart)/CLOCKS_PER_SEC;
}

string utilities::pickMCinputSampe()
{
	int n = 0;
	TMapis mcSamplesMap;
	
	mcSamplesMap.insert( make_pair( 0,"Zmumu" ) ); 
	
	mcSamplesMap.insert( make_pair( 1,"DYmumu_75M120" ) );
	mcSamplesMap.insert( make_pair( 2,"DYmumu_120M250" ) );
	mcSamplesMap.insert( make_pair( 3,"DYmumu_250M400" ) );
	mcSamplesMap.insert( make_pair( 4,"DYmumu_400M600" ) );
	mcSamplesMap.insert( make_pair( 5,"DYmumu_600M800" ) );
	mcSamplesMap.insert( make_pair( 6,"DYmumu_800M1000" ) );
	mcSamplesMap.insert( make_pair( 7,"DYmumu_1000M1250" ) );
	mcSamplesMap.insert( make_pair( 8,"DYmumu_1250M1500" ) );
	mcSamplesMap.insert( make_pair( 9,"DYmumu_1500M1750" ) );
	mcSamplesMap.insert( make_pair( 10,"DYmumu_1750M2000" ) );
	mcSamplesMap.insert( make_pair( 11,"DYmumu_M2000" ) );

	mcSamplesMap.insert( make_pair( 100,"DYtautau_75M120" ) );
	mcSamplesMap.insert( make_pair( 101,"DYtautau_120M250" ) );
	mcSamplesMap.insert( make_pair( 102,"DYtautau_250M400" ) );
	mcSamplesMap.insert( make_pair( 103,"DYtautau_400M600" ) );
	mcSamplesMap.insert( make_pair( 104,"DYtautau_600M800" ) );
	mcSamplesMap.insert( make_pair( 105,"DYtautau_800M1000" ) );
	mcSamplesMap.insert( make_pair( 106,"DYtautau_1000M1250" ) );
	mcSamplesMap.insert( make_pair( 107,"DYtautau_1250M1500" ) );
	mcSamplesMap.insert( make_pair( 108,"DYtautau_1500M1750" ) );
	mcSamplesMap.insert( make_pair( 109,"DYtautau_1750M2000" ) );
	mcSamplesMap.insert( make_pair( 110,"DYtautau_M2000" ) );

	mcSamplesMap.insert( make_pair( 200,"Ztautau" ) );
	mcSamplesMap.insert( make_pair( 201,"TTbar" ) );
	mcSamplesMap.insert( make_pair( 202,"Wmunu" ) );
	mcSamplesMap.insert( make_pair( 203,"bbmu15X" ) );
	mcSamplesMap.insert( make_pair( 204,"ccmu15X" ) );
	
	mcSamplesMap.insert( make_pair( 300,"AlpgenJimmyWWlnulnuNp0" ) );
	mcSamplesMap.insert( make_pair( 301,"AlpgenJimmyWWlnulnuNp1" ) );
	mcSamplesMap.insert( make_pair( 302,"AlpgenJimmyWWlnulnuNp2" ) );
	mcSamplesMap.insert( make_pair( 303,"AlpgenJimmyWWlnulnuNp3" ) );
	
	mcSamplesMap.insert( make_pair( 311,"gg2WW0240_JIMMY_WW_munumunu" ) );
	mcSamplesMap.insert( make_pair( 312,"gg2WW0240_JIMMY_WW_munutaunu" ) );
	mcSamplesMap.insert( make_pair( 313,"gg2WW0240_JIMMY_WW_taunumunu" ) );
	mcSamplesMap.insert( make_pair( 314,"gg2WW0240_JIMMY_WW_taunutaunu" ) );
	
	mcSamplesMap.insert( make_pair( 321,"McAtNlo_JIMMY_WpWm_munumunu" ) );
	mcSamplesMap.insert( make_pair( 322,"McAtNlo_JIMMY_WpWm_munutaunu" ) );
	mcSamplesMap.insert( make_pair( 323,"McAtNlo_JIMMY_WpWm_taunutaunu" ) );

	mcSamplesMap.insert( make_pair( 401,"PythiaH200zzllnunu" ) );
	mcSamplesMap.insert( make_pair( 402,"PythiaH300zzllnunu" ) );
	mcSamplesMap.insert( make_pair( 403,"PythiaH400zzllnunu" ) );
	mcSamplesMap.insert( make_pair( 404,"PythiaH500zzllnunu" ) );
	mcSamplesMap.insert( make_pair( 405,"PythiaH600zzllnunu" ) );
	
	mcSamplesMap.insert( make_pair( 410,"Pythiazz4l" ) );

	mcSamplesMap.insert( make_pair( 420,"McAtNlo_JIMMY_ZZ_llll" ) );
	mcSamplesMap.insert( make_pair( 421,"McAtNlo_JIMMY_ZZ_llnunu" ) );
	mcSamplesMap.insert( make_pair( 422,"McAtNlo_JIMMY_ZZ_2l2tau" ) );
	mcSamplesMap.insert( make_pair( 422,"McAtNlo_JIMMY_ZZ_llqq" ) );
	
	mcSamplesMap.insert( make_pair( 430,"AlpgenJimmyZZincllNp0" ) );
	mcSamplesMap.insert( make_pair( 431,"AlpgenJimmyZZincllNp1" ) );
	mcSamplesMap.insert( make_pair( 432,"AlpgenJimmyZZincllNp2" ) );
	mcSamplesMap.insert( make_pair( 433,"AlpgenJimmyZZincllNp3" ) );
	
	mcSamplesMap.insert( make_pair( 500,"Zprime_mumu_SSM1000" ) );
	mcSamplesMap.insert( make_pair( 501,"Zprime_mumu_SSM1250" ) );
	mcSamplesMap.insert( make_pair( 502,"Zprime_mumu_SSM1500" ) );
	mcSamplesMap.insert( make_pair( 503,"Zprime_mumu_SSM1750" ) );
	mcSamplesMap.insert( make_pair( 504,"Zprime_mumu_SSM2000" ) );
	
	
	cout << "PICK AN MC CHANNEL FORM THE LIST:" << endl;
	for(TMapis::iterator it=mcSamplesMap.begin() ; it!=mcSamplesMap.end() ; it++)
	{
		cout << "\t[" << it->first << "]\t" << it->second << endl;
	}
	cout << "...";
	cin >> n;
	TMapis::iterator it=mcSamplesMap.find(n);
	return it->second;
}

string utilities::checkANDsetFilepath(string envPath, string fileName)
{
	char * tmpPath = getenv(envPath.c_str());
	if (!tmpPath) {
		cerr << "environment variable " << envPath  <<  " not defined" << endl;
		cerr << "\tdid you forget to 'source configure_bash or configure_tcsh' ?" << endl;
		exit(-1);
	}

	string fullPath = tmpPath;
	fullPath += fileName;

	//----------------- check if there are ".."-like parts in the fullPath
	int i=0;
	int pos=0;
	bool isDoubledot = false;
	while (i<(int)fullPath.size()-1) { // check if there's a ".." string in fullPath
		if (fullPath.substr(i,2) == "..") {
			pos = i;
			isDoubledot = true;
			//cout << "warning: this is a known problem with file paths, fixing it now..." << endl;
		}
		i++;
	}

	if (isDoubledot) {
		string oldPath = fullPath;
		string fin = fullPath.substr(pos+2,(int)fullPath.size()-(pos+2)); // remember everything from after ".."
		string newpath = fullPath.substr(0,pos-1); // remember everything before "/.."
		int newpos = pos-2;
		string isBackslash = newpath.substr(newpos,1);
		while (isBackslash != "/") { // remove the dir name before "/.."
			newpos--;
			isBackslash = newpath.substr(newpos,1);
		}
		fullPath = newpath.substr(0,newpos) + fin;
		//cout << "\t file path was: " << oldPath << endl;
		//cout << "\t corrected to: " << fullPath << endl;
		cout << "file path: " << fullPath << endl;
	}

	if (!isDoubledot) {cout << "file path: " << fullPath << endl;}

	return(fullPath);
}

string utilities::removeDoubleDot(string spath)
{
	//----------------- check if there are ".."-like parts in the fullPath
	int i=0;
	int pos=0;
	bool isDoubledot = false;
	while (i<(int)spath.size()-1)
	{ // check if there's a ".." string in fullPath
		if (spath.substr(i,2) == "..")
		{
			pos = i;
			isDoubledot = true;
		}
		i++;
	}
	
	if (isDoubledot)
	{
		string oldPath = spath;
		string fin = spath.substr(pos+2,(int)spath.size()-(pos+2)); // remember everything from after ".."
		string newpath = spath.substr(0,pos-1); // remember everything before "/.."
		int newpos = pos-2;
		string isBackslash = newpath.substr(newpos,1);
		while (isBackslash != "/") { // remove the dir name before "/.."
			newpos--;
			isBackslash = newpath.substr(newpos,1);
		}
		spath = newpath.substr(0,newpos) + fin;
	}

	return spath;
}

// a method to chaeck is the environment veriable is defined or not
// will NOT exit if the environment variable is not defined.
bool utilities::checkPath(string envPath)
{
	bool isDefined = false;
	char * tmpPath = getenv(envPath.c_str());
	if (!tmpPath) {
		cerr << "environment variable " << envPath  <<  " not defined" << endl;
		cerr << "\tdid you forget to 'source configure_bash or configure_tcsh' ?" << endl;
		isDefined = false;
	}
	else {isDefined = true;}
	return(isDefined);
}

void utilities::parseKeyValLine(string sLine)
{

	double tmpVal = 0.;

	if(m_dval.size()>0) m_dval.clear();

	stringstream strm(sLine);
	strm >> m_skey;
	while(!strm.eof())
	{
		strm >> tmpVal;
		m_dval.push_back(tmpVal);
	}
}

string utilities::getKey()
{
	return m_skey;
}

double utilities::getVal(int valNum)
{
	if( valNum<0 || valNum>=getNVals() ) { cerr << "ERROR: valNum=" << valNum << " is out of range" << endl; exit(-1); }
	return m_dval[valNum];
}

int utilities::getNVals()
{
	return (int)m_dval.size();
}

void utilities::parseFile(string sFilePath)
{       
	fstream file;
	file.open( sFilePath.c_str() );

	string sLine = "";
	string skey  = "";
	double dval  = 0.;

	int nLinesRead = 0;

	while(!file.eof())
	{
		//cout << "reading line " << nLinesRead << endl;
		getline(file,sLine);

		if(sLine == "") continue;

		// parse the line:
		parseKeyValLine(sLine);

		// get the key:
		skey = getKey();
		cout << skey;

		// get the 1st val:
		for(int i=0 ; i<(int)getNVals() ; i++)
		{
			dval = getVal(i);
			cout << "\t" << dval;
		}

		cout << endl;

		nLinesRead++;
	}
	cout << "\nread " << nLinesRead << " lines from " << sFilePath << endl;
}
