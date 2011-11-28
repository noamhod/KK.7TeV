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
	
	mcSamplesMap.insert( make_pair( -1,"mcWZphys_localTests" ) ); 
	
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
	
	mcSamplesMap.insert( make_pair( 300,"AlpgenJimmyWmunuNp0_pt20" ) );
	mcSamplesMap.insert( make_pair( 301,"AlpgenJimmyWmunuNp1_pt20" ) );
	mcSamplesMap.insert( make_pair( 302,"AlpgenJimmyWmunuNp2_pt20" ) );
	mcSamplesMap.insert( make_pair( 303,"AlpgenJimmyWmunuNp3_pt20" ) );
	mcSamplesMap.insert( make_pair( 304,"AlpgenJimmyWmunuNp4_pt20" ) );
	mcSamplesMap.insert( make_pair( 305,"AlpgenJimmyWmunuNp5_pt20" ) );
	
	mcSamplesMap.insert( make_pair( 400,"Zprime_mumu_SSM250" ) );
	mcSamplesMap.insert( make_pair( 401,"Zprime_mumu_SSM750" ) );
	mcSamplesMap.insert( make_pair( 402,"Zprime_mumu_SSM1000" ) );
	mcSamplesMap.insert( make_pair( 403,"Zprime_mumu_SSM1250" ) );
	mcSamplesMap.insert( make_pair( 404,"Zprime_mumu_SSM1500" ) );
	mcSamplesMap.insert( make_pair( 405,"Zprime_mumu_SSM1750" ) );
	mcSamplesMap.insert( make_pair( 406,"Zprime_mumu_SSM2000" ) );
	
	mcSamplesMap.insert( make_pair( 500,"WW_Herwig" ) );
	mcSamplesMap.insert( make_pair( 501,"WZ_Herwig" ) );
	mcSamplesMap.insert( make_pair( 502,"ZZ_Herwig" ) );
	
	mcSamplesMap.insert( make_pair( 600,"T1_McAtNlo_Jimmy" ) );
	
	mcSamplesMap.insert( make_pair( 700,"TTbar_McAtNlo_Jimmy_2mu15_30M150" ) );
	mcSamplesMap.insert( make_pair( 701,"TTbar_McAtNlo_Jimmy_2mu15_150M300" ) );
	mcSamplesMap.insert( make_pair( 702,"TTbar_McAtNlo_Jimmy_2mu15_300M450" ) );
	mcSamplesMap.insert( make_pair( 703,"TTbar_McAtNlo_Jimmy_2mu15_M450" ) );

	mcSamplesMap.insert( make_pair( 800,"DYmumu_75M120_2011" ) );

	mcSamplesMap.insert( make_pair( 900,"Gmm_01_1750" ) );	
	mcSamplesMap.insert( make_pair( 901,"Gmm_01_2000" ) );	
	mcSamplesMap.insert( make_pair( 902,"Gmm_01_2250" ) );	
	
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
	if (!tmpPath)
	{
		_ERROR("environment variable "+envPath+" not defined, exitting now.");
		exit(-1);
	}

	string fullPath = tmpPath;
	fullPath += fileName;

	//----------------- check if there are ".."-like parts in the fullPath
	int i=0;
	int pos=0;
	bool isDoubledot = false;
	while (i<(int)fullPath.size()-1)
	{ // check if there's a ".." string in fullPath
		if (fullPath.substr(i,2) == "..")
		{
			pos = i;
			isDoubledot = true;
			//cout << "warning: this is a known problem with file paths, fixing it now..." << endl;
		}
		i++;
	}

	if(isDoubledot)
	{
		string oldPath = fullPath;
		string fin = fullPath.substr(pos+2,(int)fullPath.size()-(pos+2)); // remember everything from after ".."
		string newpath = fullPath.substr(0,pos-1); // remember everything before "/.."
		int newpos = pos-2;
		string isBackslash = newpath.substr(newpos,1);
		while (isBackslash != "/")
		{ // remove the dir name before "/.."
			newpos--;
			isBackslash = newpath.substr(newpos,1);
		}
		fullPath = newpath.substr(0,newpos) + fin;
		//cout << "\t file path was: " << oldPath << endl;
		//cout << "\t corrected to: " << fullPath << endl;
		_DEBUG("file path: "+fullPath);
	}

	if (!isDoubledot) {_DEBUG("file path: "+fullPath);}

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
		_ERROR("environment variable "+envPath+" not defined");
		isDefined = false;
	}
	else {isDefined = true;}
	return(isDefined);
}

