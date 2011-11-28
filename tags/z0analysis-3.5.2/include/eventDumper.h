/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef EVENTDUMPER_H
#define EVENTDUMPER_H

class eventDumper
{
	public:
		ofstream* file;
		ofstream* singleEventFile;
	
		bool b_print;
		bool doEventDump;
		double m_massThreshold;
		double m_currentEventMass;

	public:
		eventDumper();
		~eventDumper();

		inline void setEventDumperFile(string sEventDumpFilePath);
		inline void setInterestingThreshold(double massThreshold);
		inline void setCurrentEventMass(double currentEventMass);
		inline void writeEventHeader(int RunNumber, int lbn, int eventNumber);
		inline void writeEventFooter();
		inline void writeProperty(string sProperty, double dPropertyMua, double dPropertyMub);
		inline void writeProperty(string sProperty, string sColor, double dProperty);
		inline void writeProperty(string sProperty, double dProperty);
		inline void printProperty(string sProperty, double dProperty);
		
		inline bool isInteresting(double invariantMass);
		inline void setSingleEventFile(string basedir, int RunNumber, int lbn, int EventNumber);
		inline void insertTableLine(string type, string line1, string line2="", bool isbreak=false, bool isLastLine=false);
		inline void closeSingleEventFile();

	private:

};
#endif

