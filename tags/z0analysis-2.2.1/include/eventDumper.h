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
	
		bool b_print;
		double m_massThreshold;
		double m_currentEventMass;

	public:
		eventDumper();
		eventDumper(string sEventDumpFilePath);
		~eventDumper();

		void setInterestingThreshold(double massThreshold);
		void setCurrentEventMass(double currentEventMass);
		void writeEventHeader(int RunNumber, int lbn, int eventNumber);
		void writeEventFooter();
		void writeProperty(string sProperty, double dPropertyMua, double dPropertyMub);
		void writeProperty(string sProperty, string sColor, double dProperty);
		void writeProperty(string sProperty, double dProperty);

	private:

};
#endif

