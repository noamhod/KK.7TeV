/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "eventDumper.h"

inline eventDumper::eventDumper()
{
	
}

inline eventDumper::~eventDumper()
{
	if(file) file->close();
}

inline void eventDumper::setEventDumperFile(string sEventDumpFilePath)
{
	b_print = false;
	doEventDump = false;
	
	if(sEventDumpFilePath != "")
	{
		doEventDump = true;
		file = new ofstream();
		file->open( sEventDumpFilePath.c_str() );
	}
	else
	{
		doEventDump = false;
	}	
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline void eventDumper::setInterestingThreshold(double massThreshold)
{
	m_massThreshold = massThreshold;
}

inline void eventDumper::setCurrentEventMass(double currentEventMass)
{
	m_currentEventMass = currentEventMass;
}

inline void eventDumper::writeEventHeader(int RunNumber, int lbn, int eventNumber)
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

inline void eventDumper::writeEventFooter()
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

inline void eventDumper::writeProperty(string sProperty, double dPropertyMua, double dPropertyMub)
{
	if(m_currentEventMass >= m_massThreshold)
	{
		(*file) << "\\midrule" << endl;
		(*file) << sProperty << "  &" << dPropertyMua << "  &" << dPropertyMub << "\\\\" << endl;
	}
}

inline void eventDumper::writeProperty(string sProperty, double dProperty)
{
	if(m_currentEventMass >= m_massThreshold)
	{
		(*file) << "\\midrule" << endl;
		(*file) << sProperty;
		(*file) << "  &\\multicolumn{2}{c}{" << dProperty << "}\\\\" << endl;
	}
}

inline void eventDumper::writeProperty(string sProperty, string sColor, double dProperty)
{
	if(m_currentEventMass >= m_massThreshold)
	{
		(*file) << "\\midrule" << endl;
		(*file) << sProperty;
		(*file) << "  &\\multicolumn{2}{c}{{\\color{" << sColor << "}{\\bf " << dProperty << "}}}\\\\" << endl;
	}
}

inline void eventDumper::printProperty(string sProperty, double dProperty)
{
	cout << sProperty << "\t" << dProperty << endl;
}

inline bool eventDumper::isInteresting(double invariantMass)
{
	return (invariantMass>=m_massThreshold) ? true : false;
}


inline void eventDumper::setSingleEventFile(int RunNumber, int lbn, int EventNumber)
{
	string name = "/srv01/tau/hod/z0analysis-tests/z0analysis-tmp_qsub/tex/Event_"+_s(RunNumber)+"_"+_s(lbn)+"_"+_s(EventNumber)+".tex";
	singleEventFile = new ofstream();
	singleEventFile->open( name.c_str() );
	
	(*singleEventFile) << "\\documentclass[a4paper,12pt]{article}" << endl;
	(*singleEventFile) << "\\pagestyle{plain}" << endl;
	(*singleEventFile) << "\\usepackage{booktabs,longtable,rotating}" << endl;
	
	(*singleEventFile) << "\\addtolength{\\oddsidemargin}{-1.5cm}" << endl;
	(*singleEventFile) << "\\addtolength{\\textwidth}{2.5cm}" << endl;
	(*singleEventFile) << "\\addtolength{\\textheight}{3cm}" << endl;
	(*singleEventFile) << "\\addtolength{\\topmargin}{-1.5cm}" << endl;
	
	(*singleEventFile) << "\\begin{document}" << endl;
	(*singleEventFile) << "\t{\\scriptsize" << endl;
	(*singleEventFile) << "\t\t\\begin{longtable}[t]{ccc}" << endl;
	(*singleEventFile) << "\t\t\t\\toprule[1pt]" << endl;
	(*singleEventFile) << "\t\t\t\\multicolumn{3}{c}{Run-Lbn-Evt " << RunNumber << "-" << lbn << "-" << EventNumber << "} \\\\" << endl;
	(*singleEventFile) << "\t\t\t\\midrule[1pt]" << endl;
}

inline void eventDumper::insertTableLine(string type, string line1, string line2, bool isbreak, bool isLastLine)
{
	(*singleEventFile) << "\t\t\t" << type << " &" << line1;
	if(line2!="")   (*singleEventFile)     << " &" << line2;
	(*singleEventFile) << " \\\\";
	if(!isLastLine)
	{
		(*singleEventFile) << " \\midrule[0.5pt]";
		if(isbreak) (*singleEventFile) << "\\pagebreak" << endl;
		else        (*singleEventFile) << "" << endl;
	}
	else
	{
		(*singleEventFile) << endl;
	}	
}

inline void eventDumper::closeSingleEventFile()
{
	(*singleEventFile) << "\t\t\t\\bottomrule[1pt]" << endl;
	(*singleEventFile) << "\t\t\\end{longtable}" << endl;
	(*singleEventFile) << "\t}" << endl;
	(*singleEventFile) << "\\end{document}" << endl;

	singleEventFile->close();
	delete singleEventFile;
}


