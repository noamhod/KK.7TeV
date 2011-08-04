/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef CUTFLOWHANDLER_H
#define CUTFLOWHANDLER_H

class cutFlowHandler : public utilities
{
	public:
		bool b_print;
		ofstream* file;
		
		// variables
		string          m_skey;
		string          m_stype;
		int				m_iskip;
		int             m_inum;
		int             m_nvals;
		vector<double>  m_dval;
		
		TMapds*         m_cutFlowOrdered;     // the map between the order of the cut and its name
		TMapds*         m_cutFlowTypeOrdered; // the map between the order of the cut and its type
		TMapsi*         m_cutFlowNumbers;     // the map between the name of the cut and the events surviving it
		TMapsvd*		m_cutFlowMapSVD;      // the actual cut flow map between the cut's name and the vector of its values
		TMapsb*			m_cutsFlowSkipMap;    // cuts to skip in tag&probe analysis
		
	public:
		cutFlowHandler();
		cutFlowHandler(string sCutFlowFilePath);
		~cutFlowHandler();
		
		void setCutFlowFile(string sLogFilePath = "", string srunnumber = "");
		
		void   parseKeyValLine(string sLine);
		int    getNVals();
        string getType();
        string getKey();
		int    getSkip();
		int    getNum();
        double getVal(int valNum);
		void getVal(vector<double>& dvalVec);
		void readCutFlow(string sCutFlowFilePath);
		void printCutFlowNumbers(Long64_t chainEntries);
		void incrementNallEvents();

		TMapds*  getCutFlowOrderedMapPtr();
		TMapds*  getCutFlowTypeOrderedMapPtr();
		TMapsi*  getCutFlowNumbersMapPtr();
		TMapsvd* getCutFlowMapSVDPtr();
		TMapsb*	 getCutFlowToSkipMapPtr();

	private:
		int    nAllEvents;
};


/////////////////////////////////////////////////////
class cutflowXml : public XML
{
	public:
		cutflowXml()
		{
			cutFlowOrdered     = new TMapds;
			cutFlowTypeOrdered = new TMapds;
			cutFlowNumbers     = new TMapsi;
			cutFlowMapSVD      = new TMapsvd;
			cutsFlowSkipMap    = new TMapsb;
			
			ignoreString("obj");
			ignoreString("NAME");
			ignoreString("FLAG");
			ignoreString("ORDER");
			ignoreString("value");
		}
		virtual ~cutflowXml(){}
		bool mask();

		/*
		<obj NAME="imass" FLAG="on">
			<order>3</order>
			<type>selection</type>
			<skip>false</skip>
			<nvalues>2</nvalues>
			<values>
				<value NAME="imass_min" ORDER="1" FLAG="on">0.07</value>
				<value NAME="imass_max" ORDER="2" FLAG="on">0.4</value>
			</values>
			<description>
				This is the invariant mass cut.
				The upper boundary is for the blinded analysis.
				The values are in TeV.
			</description>
		</obj>
		*/

		// specific mask for cuts.xml
		string name;
		string flag;
		string order;
		string type;
		string skip;
		string nvalues;
		string attrname;
		string attrorder;
		string attrflag;
		string val;
		string description;
	
		TMapds*         cutFlowOrdered;     // the map between the order of the cut and its name
		TMapds*         cutFlowTypeOrdered; // the map between the order of the cut and its type
		TMapsi*         cutFlowNumbers;     // the map between the name of the cut and the events surviving it
		TMapsvd*        cutFlowMapSVD;      // the actual cut flow map between the cut's name and the vector of its values
		TMapsb*         cutsFlowSkipMap;    // cuts to skip in tag&probe analysis
		vector<double>  vdtmp;
	
	private:
};


#endif

