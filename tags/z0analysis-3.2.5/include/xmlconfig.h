/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */


#define cutFlowHandler_cxx
#include "cutFlowHandler.C"

#define periodHandler_cxx
#include "periodHandler.C"

#define monteCarloHandler_cxx
#include "monteCarloHandler.C"

#ifndef XMLCONFIG_H
#define XMLCONFIG_H


//////////////////////////////////////////////////////////////////
////////////// NOTE !!! MULTIPLE INHERITANCE !!! /////////////////
class xmlconfig : public cutflowXml, 
				  public periodsXml,
				  public montecarloXml
{
	public:
		xmlconfig();
		virtual ~xmlconfig();
		void get(string xmldir);
		void reset();
		void header(string fileName);
		void footer(string fileName);
		void read(string readerName, string fileName);
		static xmlconfig* getInstance();
	public:
		TDOMParser* domParser;
		TXMLNode*   node;
	private:
		static xmlconfig* theInstance;
};

#endif
