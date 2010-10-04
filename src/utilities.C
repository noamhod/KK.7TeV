/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "utilities.h"

utilities::utilities()
{
	uinitialize();
}

utilities::~utilities()
{
	ufinalize();
}

void utilities::uinitialize()
{
	// other
	d_toGeV = 1000.;

}

void utilities::ufinalize()
{

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
