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
		
		// double validate_double(string str);
		// double validate_double(const char* cc) { return validate_double((string)cc); }
		// int    validate_int(string str)        { return (int)validate_double(str); }
		// int    validate_int(const char* cc)    { return validate_int((string)cc); }
		// float  validate_float(string str)      { return (float)validate_double(str); }
		// float  validate_float(const char* cc)  { return validate_float((string)cc); }
		// bool   validate_bool(string str);
		// bool   validate_bool(const char* cc) { return validate_bool((string)cc); }		

		// string tostring(int    x);
		// string tostring(double x);
		// int    toint(string str);
		// double todouble(string str);
		// int    toint(const char* cc)    { return toint((string)cc); }
		// double todouble(const char* cc) { return todouble((string)cc); }
		
		void ignoreString(string str);
	
		string Next(TMapiP2cc::iterator& ii);
		TMapiP2cc* list;
	private:
		void add2list(const char* cc);
		bool isIgnored(string str);
		bool isIgnored(bool isfound);
		
		//TMapiP2cc* list;
		int counter;
		string sTmp;
		TMapsb ignoredStrings;
};

#endif
