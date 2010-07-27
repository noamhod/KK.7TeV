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
