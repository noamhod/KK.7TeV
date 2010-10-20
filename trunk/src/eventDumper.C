/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "eventDumper.h"

eventDumper::eventDumper()
{
	
}

eventDumper::eventDumper(string sEventDumpFilePath)
{
	b_print = false;

	file = new ofstream();
	
	file->open( sEventDumpFilePath.c_str() );
}

eventDumper::~eventDumper()
{
	file->close();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void eventDumper::setInterestingThreshold(double massThreshold)
{
	m_massThreshold = massThreshold;
}

void eventDumper::setCurrentEventMass(double currentEventMass)
{
	m_currentEventMass = currentEventMass;
}

void eventDumper::writeEventHeader(int RunNumber, int lbn, int eventNumber)
{
	if(m_currentEventMass >= m_massThreshold)
	{
		(*file) << "\n----------------------------------------------------------------" << endl;
		(*file) << "\\begin{tikzpicture}" << endl;
		(*file) << "\\node[scale=0.8]{" << endl;
		(*file) << "{\\scriptsize" << endl;
		(*file) << "\\begin{tabular}[t]{lcc}" << endl;
		(*file) << "\\toprule" << endl;
		(*file) << "run=" << RunNumber << "  &lbn=" << lbn << "  &evt=" << eventNumber << "\\\\" << endl;
		(*file) << "\\,  &$\\mu^-$  &$\\mu^+$\\\\" << endl;
	}
}

void eventDumper::writeEventFooter()
{
	if(m_currentEventMass >= m_massThreshold)
	{
		(*file) << "\\bottomrule" << endl;
		(*file) << "\\end{tabular}" << endl;
		(*file) << "}" << endl;
		(*file) << "};" << endl;
		(*file) << "\\end{tikzpicture}" << endl;
		(*file) << "----------------------------------------------------------------\n" << endl;
	}
}

void eventDumper::writeProperty(string sProperty, double dPropertyMua, double dPropertyMub)
{
	if(m_currentEventMass >= m_massThreshold)
	{
		(*file) << "\\midrule" << endl;
		(*file) << sProperty << "  &" << dPropertyMua << "  &" << dPropertyMub << "\\\\" << endl;
	}
}

void eventDumper::writeProperty(string sProperty, double dProperty)
{
	if(m_currentEventMass >= m_massThreshold)
	{
		(*file) << "\\midrule" << endl;
		(*file) << sProperty;
		(*file) << "  &\\multicolumn{2}{c}{" << dProperty << "}\\\\" << endl;
	}
}

void eventDumper::writeProperty(string sProperty, string sColor, double dProperty)
{
	if(m_currentEventMass >= m_massThreshold)
	{
		(*file) << "\\midrule" << endl;
		(*file) << sProperty;
		(*file) << "  &\\multicolumn{2}{c}{{\\color{" << sColor << "}{\\bf " << dProperty << "}}}\\\\" << endl;
	}
}

