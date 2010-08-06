#include <TROOT.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>      // for the sprintf call
#include <string>
#include <sstream>      // for the int to string operation (stringstream call)
#include <cstring>      // for the string functions
#include <math.h>
#include <cmath>
#include <complex>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int entries = 0;

void removeCycles(int nFiles, string sFileName)
{
	if(sFileName!="")
	{
		remove(sFileName);
	}

	else
	{
		stringstream strm;
		string str = "";
		string sname = "";

		for(int i=1 ; i<=nFiles ; i++)
		{
			strm.clear();
			strm << i;
			strm >> str;
			sname = "analysisTrees_" + str + ".root";
			remove(sname);
		}
	}
}


void listCycles(int nFiles, string sFileName)
{
        if(sFileName!="")
        {
                list(sFileName);
        }

        else
        {
                stringstream strm;
                string str = "";
                string sname = "";

                for(int i=1 ; i<=nFiles ; i++)
                {
                        strm.clear();
                        strm << i;
                        strm >> str;
                        sname = "analysisTrees_" + str + ".root";
                        list(sname);
                }
        }
	cout << "all entries = " << entries << endl;
}


void list(string sname)
{
	TFile* file = new TFile( sname.c_str(), "UPDATE");
	file->ls();
	TTree* tree = (TTree*)file->Get("offline");
	int N = tree->GetEntries();
	cout << "N entries = " << N << endl;
	entries += N;
	file->Close();
	cout << endl;
}

void remove(string sname)
{
	TFile* file = new TFile( sname.c_str(), "UPDATE");
	cout << "before" << endl;
	file->ls();
	file->Delete("offline;2");
	cout << "after" << endl;
	file->ls();
	file->Close();
	delete file;
	cout << endl;
}

