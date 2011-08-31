//////////////////////////////////////////////////////////////////////////////
// ROOT implementation of a XML DOM Parser
// This is an example of how Dom Parser walks the DOM tree recursively.
// This example will parse any xml file.
//////////////////////////////////////////////////////////////////////////////

#include "basicIncludes.h"

#ifndef XML_H
#define XML_H

class XML
{
	public:
		XML()
		{
			list = new TMapiP2cc;
			counter = 0;
			ignoredStrings.clear();
		}
		virtual ~XML()
		{
			delete list;
			ignoredStrings.clear();
		}
		void ParseContext(TXMLNode *node);
		bool isEmptyString(string str);
		virtual bool mask() = 0;
		
		void ignoreString(string str);
	
		string Next(TMapiP2cc::iterator& ii);
		string NextStay(TMapiP2cc::iterator& ii);
		string Previous(TMapiP2cc::iterator& ii);
		string PreviousStay(TMapiP2cc::iterator& ii);
		TMapiP2cc* list;
	private:
		void add2list(const char* cc);
		bool isIgnored(string str);
		bool isIgnored(bool isfound);
		
		int counter;
		string sTmp;
		TMapsb ignoredStrings;
};

#endif
