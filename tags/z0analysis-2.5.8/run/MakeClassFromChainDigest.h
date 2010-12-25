/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include <TROOT.h>
#include <TCut.h>
#include <TChain.h>
#include <TCanvas.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>      // for the sprintf call
#include <string>
#include <sstream>      // for the int to string operation (stringstream call)
#include <cstring>      // for the string functions
#include <fstream>

using namespace std;

#ifndef MAKECLASSFROMCHAINDIGEST_H
#define MAKECLASSFROMCHAINDIGEST_H

class MakeClassFromChainDigest
{
	public:
		// pointers
		TChain* m_chain;

	public:
		MakeClassFromChainDigest();
		~MakeClassFromChainDigest();

		string checkANDsetFilepath(string envPath, string fileName);
	
		void makeChain(bool doList = false, string sListFilePath = "digest_dataset.list");
		void chain2class(string sClassName = "digestPhysics");
	
		void GetEntries();	
		void drawFromChain();

		void list2chain(string sListFilePath = "digest_dataset.list");
};
#endif

