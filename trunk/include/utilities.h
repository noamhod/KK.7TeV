/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef UTILITIES_H
#define UTILITIES_H

static clock_t clockStart;
static clock_t clockEnd;

class utilities
{
	public:
		
	public:
		utilities();
		~utilities();
		
		static string getDateHour();
		
		static double getRunTime();
		static void   startTimer();
		static void   stopTimer(bool print);
		static string pickMCinputSampe();

		static string checkANDsetFilepath(string envPath, string fileName);
		string removeDoubleDot(string spath);
		bool   checkPath(string envPath);
};
#endif

