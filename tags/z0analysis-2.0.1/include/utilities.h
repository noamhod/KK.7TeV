/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef UTILITIES_H
#define UTILITIES_H

class utilities
{
	public:
		// utilities
		Double_t d_toGeV;
	public:
		utilities();
		~utilities();
		void   uinitialize();
		void   ufinalize();

		string checkANDsetFilepath(string envPath, string fileName);
		string removeDoubleDot(string spath);
		bool   checkPath(string envPath);

		void   parseKeyValLine(string sLine);
		int    getNVals();
                string getKey();
                double getVal(int valNum);
		void   parseFile(string sFilePath);
		
	private:
		string          m_skey;
		vector<double>  m_dval;

};
#endif

