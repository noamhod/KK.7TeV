/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef CUTFLOWHANDLER_H
#define CUTFLOWHANDLER_H

class cutFlowHandler : public XML
{		
	public:
		cutFlowHandler()
		{
			b_print = false;

			m_cutFlowOrdered     = new TMapds;
			m_cutFlowTypeOrdered = new TMapds;
			m_cutsFlowSkipMap    = new TMapsb;
			m_cutFlowNumbers     = new TMapsi;
			m_cutFlowMapSVD      = new TMapsvd;
			
			nAllEvents = 0;
			
			ignoreString("obj");
			ignoreString("NAME");
			ignoreString("FLAG");
			ignoreString("TYPE");
			ignoreString("ORDER");
			ignoreString("parameter");
		}
		virtual ~cutFlowHandler() {file->close();}
		bool mask();
		
		void setCutFlowFile(string sLogFilePath = "", string srunnumber = "");
		void printCutFlowNumbers(Long64_t chainEntries, string Name="");
		void incrementNallEvents();

		TMapds*  getCutFlowOrderedMapPtr();
		TMapds*  getCutFlowTypeOrderedMapPtr();
		TMapsi*  getCutFlowNumbersMapPtr();
		TMapsvd* getCutFlowMapSVDPtr();
		TMapsb*	 getCutFlowToSkipMapPtr();

	public:
		bool b_print;
		ofstream* file;
		
		TMapds*  m_cutFlowOrdered;     // the map between the order of the cut and its name
		TMapds*  m_cutFlowTypeOrdered; // the map between the order of the cut and its type
		TMapsi*  m_cutFlowNumbers;     // the map between the name of the cut and the events surviving it
		TMapsvd* m_cutFlowMapSVD;      // the actual cut flow map between the cut's name and the vector of its parameters
		TMapsb*  m_cutsFlowSkipMap;    // cuts to skip in tag&probe analysis
	private:
		int nAllEvents;
		
	private:
		// specific mask for cuts.xml
		string name;
		string flag;
		string order;
		string phase;
		string skip;
		string nparameters;
		string attrname;
		string attrorder;
		string attrflag;
		string attrtype;
		string val;
		string description;
		vector<double>  vdtmp;
};


#endif

