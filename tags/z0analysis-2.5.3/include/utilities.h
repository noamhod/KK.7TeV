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
		clock_t clockStart;
		clock_t clockEnd;
		ProcInfo_t pi;
		
	public:
		utilities();
		~utilities();
		
		string getDateHour();
		
		double getRunTime();
		void   startTimer();
		void   stopTimer(bool print);
		string pickMCinputSampe();

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
