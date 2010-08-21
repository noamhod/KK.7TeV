/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 14:34 */
/* * * * * * * * * * * */

#include "MakeClassFromChainDigest.h"

MakeClassFromChainDigest::MakeClassFromChainDigest()
{
	m_chain = new TChain("digest");
}

MakeClassFromChainDigest::~MakeClassFromChainDigest()
{
	delete m_chain;
}

string MakeClassFromChainDigest::checkANDsetFilepath(string envPath, string fileName)
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
		cout << "file path: " << fullPath << endl;
	}

	if (!isDoubledot) {cout << "file path: " << fullPath << endl;}

	return(fullPath);
}


void MakeClassFromChainDigest::list2chain(string sListFilePath)
{
	sListFilePath = checkANDsetFilepath("PWD", "../conf/"+sListFilePath);

	ifstream file;
	file.open(sListFilePath.c_str());
	string sLine;
	size_t pos;
	size_t min = 32000;
	int nfound = 0;
	int nignored = 0;
	while(!file.eof())
	{
		getline(file,sLine);
		
		pos = sLine.find(".root");
		if (pos == string::npos)
		{
			nignored++;
			cout << "ignoring entry: " << sLine << endl;
			continue;
		} // if pattern ".root" is not found
		
		size_t fileSize = 0;
		ifstream infile(sLine.c_str());
		if(infile.is_open())
		{
			infile.seekg(0, ios::end ); // move to end of file
			fileSize = infile.tellg();
			if(fileSize < min)
			{
				nignored++;
				cout << "ignoring entry: " << sLine << endl;
				continue;
			} // if file is too small
		}
		
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
		sLine = "digest_datasetdir/" + sLine; // add the absolute path
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		m_chain->Add( sLine.c_str() );
		nfound++;
	}
	cout << "found "   << nfound   << " entries in " << sListFilePath << endl;
	cout << "ignored " << nignored << " entries in " << sListFilePath << endl;
}

void MakeClassFromChainDigest::makeChain(bool doList, string sListFilePath)
{
	list2chain(sListFilePath);
	if(doList) m_chain->ls();
}

void MakeClassFromChainDigest::GetEntries()
{
	long int nentries = (long int)m_chain->GetEntries();
	cout << "Entries in chain: N=" << nentries << endl;
}


void MakeClassFromChainDigest::chain2class(string sClassName)
{
	m_chain->MakeClass(sClassName.c_str());
}

void MakeClassFromChainDigest::drawFromChain()
{
	
}

