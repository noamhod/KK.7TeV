/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 14:34 */
/* * * * * * * * * * * */

#ifdef digestChains_cxx
#include "digestChains.h"

digestChains::digestChains()
{
	cinitialize();
}

digestChains::~digestChains()
{
	cfinalize();
}

void digestChains::cinitialize()
{
	m_chain = new TChain("digest");
}

void digestChains::cfinalize()
{
	//	delete m_chain;
}

void digestChains::list2chain(string sListFilePath, string sListContentAbsolutePath)
{
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
		if (pos == string::npos) { nignored++; continue; } // if pattern ".root" is not found
		
		size_t fileSize = 0;
		ifstream infile(sLine.c_str());
		if(infile.is_open())
		{
			infile.seekg(0, ios::end ); // move to end of file
			fileSize = infile.tellg();
			if(fileSize < min) { nignored++; continue; } // if file is too small
		}
		
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
		sLine = sListContentAbsolutePath + sLine; // add the absolute path
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		m_chain->Add( sLine.c_str() );
		nfound++;
	}
	cout << "found "   << nfound   << " entries in " << sListFilePath << endl;
	cout << "ignored " << nignored << " entries in " << sListFilePath << endl; 
}

void digestChains::makeChain(bool doList, string sListFilePath, string sListContentAbsolutePath, int runNumber)
{
	list2chain(sListFilePath, sListContentAbsolutePath, runNumber);
	if(doList) m_chain->ls();
}


void digestChains::drawFromChain()
{

}
#endif

