#include <iostream>
#include <stdlib.h>
#include <stdio.h>      // for the sprintf call
#include <string>
#include <sstream>      // for the int to string operation (stringstream call)
#include <cstring>      // for the string functions
#include <fstream>
#include <vector>
#include <map>
#include <pthread.h>

#ifndef READ_H
#define READ_H

struct parameters
{
	int idF;
	int nEvents;
	double newMass; // GeV
	double mMin; // GeV
	double mMax; // GeV
	string sName;
};

parameters prm;

void readParameters()
{
	fstream f;
	f.open( "runParameters.run" );
	string sLine;
	string identifier;
	if(!f)
	{
		cerr << "Unable to open file runParameters.run" << endl;
		exit(1);   // call system to stop
	}
	while(!f.eof())
	{
		getline(f,sLine);
		if(sLine == "") continue;
		stringstream strm(sLine);
		
		identifier.clear();
		strm >> identifier;
		if     (identifier=="")        continue;
		else if(identifier=="fermion") strm >> prm.idF;
		else if(identifier=="mBSM")    strm >> prm.newMass;
		else if(identifier=="mMin")    strm >> prm.mMin;
		else if(identifier=="mMax")    strm >> prm.mMax;
		else if(identifier=="nEvents") strm >> prm.nEvents;
		else if(identifier=="name")    strm >> prm.sName;
		else
		{
			cout << "problem in identifier: " << identifier << endl;
			exit(-1);
		}
	}
	f.close();
}

#endif
