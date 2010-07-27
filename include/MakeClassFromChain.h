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

#ifndef MAKECLASSFROMCHAIN_H
#define MAKECLASSFROMCHAIN_H

class MakeClassFromChain
{
	public:
		// pointers
		TChain* m_chain;

	public:
		MakeClassFromChain();
		~MakeClassFromChain();
	
		void makeChain(bool doList = false, string sListFilePath = "dataset.list", string sListContentAbsolutePath = "/data/hod/D3PDs/");
		void chain2class(string sClassName = "physics");
	
		void GetEntries();	
		void drawFromChain();	

		void list2chain(string sListFilePath, string sListContentAbsolutePath = "/data/hod/D3PDs/");

};
#endif

