/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include <TROOT.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>      // for the sprintf call
#include <string>
#include <sstream>      // for the int to string operation (stringstream call)
#include <cstring>      // for the string functions
#include <fstream>
#include <vector>

using namespace std;


string          m_key;
vector<double>  m_val;



void parseKeyValLine(string sLine)
{
	double tmpVal = 0.;

        if(m_val.size()>0) m_val.clear();

        stringstream strm(sLine);
        strm >> m_key;
	while(!strm.eof())
        {
                strm >> tmpVal;
                m_val.push_back(tmpVal);
        }
}

string getKey()
{
        return m_key;
}

double getVal(int valNum)
{
        if( valNum<0 || valNum>=(int)m_val.size() ) { cerr << "ERROR: valNum=" << valNum << " is out of range" << endl; exit(-1); }
        return m_val[valNum];
}

int getNVals()
{
	return (int)m_val.size();
}

void readCutFlow(string sCutFlowFilePath)
{
        fstream file;
        file.open( sCutFlowFilePath.c_str() );

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
        cout << "\nread " << nLinesRead << " lines from " << sCutFlowFilePath << endl;
}

