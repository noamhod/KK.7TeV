//////////////////////////////////////////////////////////////////////////////
// ROOT implementation of a XML DOM Parser
// This is an example of how Dom Parser walks the DOM tree recursively.
// This example will parse any xml file.
//////////////////////////////////////////////////////////////////////////////

#include "basic.h"

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
		
		double validate_double(string str);
		double validate_double(const char* cc) { return validate_double((string)cc); }
		int    validate_int(string str)        { return (int)validate_double(str); }
		int    validate_int(const char* cc)    { return validate_int((string)cc); }
		float  validate_float(string str)      { return (float)validate_double(str); }
		float  validate_float(const char* cc)  { return validate_float((string)cc); }
		bool   validate_bool(string str);
		bool   validate_bool(const char* cc) { return validate_bool((string)cc); }		

		string tostring(int    x);
		string tostring(double x);
		int    toint(string str);
		double todouble(string str);
		int    toint(const char* cc)    { return toint((string)cc); }
		double todouble(const char* cc) { return todouble((string)cc); }
		
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

double XML::validate_double(string str)
{
	if(str.substr(0,1)=="0")
	{
		size_t pos = str.find('.');
		if(pos==string::npos)
		{
			//cout << "[" << LOG("xxx") << "] " << "ERROR: cannot validate string=" << str << " (didn't find a decimal period). exit now." << endl;
			cout << LOG("ERROR: cannot validate string=" + str + " (didn't find a decimal period). exit now.") << endl;
			exit(-1);
		}
	}

	double x;
	try
	{
		x = boost::lexical_cast<double>(str);
	}
	catch(boost::bad_lexical_cast&)
	{
		cout << "ERROR: cannot validate string=" << str << " (cannot cast it to double). exit now." << endl;
		exit(-1);
	}
	return x;
}

bool XML::validate_bool(string str)
{
	if(str=="false" || str=="0") return false;
	else if(str=="true" || str=="1") return true;
	else
	{
		cout << "ERROR: cannot validate string=" << str << " (cannot be read as a boolean). exit now." << endl;
		exit(-1);
	}
	return true;
}

bool XML::isEmptyString(string str)
{
	for(int i=0 ; i<(int)str.length() ; ++i)
	{
		if(str.substr(i,1)!=""  &&  str.substr(i,1)!=" "  &&  str.substr(i,1)!="\n") return false;
	}
	return true;
}

void XML::add2list(const char* cc)
{
	if(isEmptyString((string)cc)) return;
	counter++;
	list->insert( make_pair(counter,cc) );
}

string XML::Next(TMapiP2cc::iterator& ii)
{
	++ii;
	string str = ii->second;
	return str;
}

string XML::tostring(int x)
{
	stringstream strm;
	string str;
	strm << x;
	strm >> str;
	return str;
}

string XML::tostring(double x)
{
	stringstream strm;
	string str;
	strm << x;
	strm >> str;
	return str;
}

int XML::toint(string str)
{
	stringstream strm;
	int x;
	strm << str;
	strm >> x;
	return x;
}

double XML::todouble(string str)
{
	stringstream strm;
	double x;
	strm << str;
	strm >> x;
	return x;
}

void XML::ignoreString(string str)
{
	ignoredStrings.insert(make_pair(str,true));
}

bool XML::isIgnored(string str)
{
	TMapsb::iterator it = ignoredStrings.find(str);
	if(it==ignoredStrings.end()) return false;
	return true;
}

bool XML::isIgnored(bool isfound)
{
	return isfound;
}

void XML::ParseContext(TXMLNode *node)
{
	for( ; node; node = node->GetNextNode())
	{
		if(node->GetNodeType()==TXMLNode::kXMLElementNode) // Element Node
		{
			string nodeName = node->GetNodeName();
			if(isIgnored(nodeName)) cout << node->GetNodeName() << " ";
			else                    cout << node->GetNodeName();
			add2list(node->GetNodeName());
			if(node->HasAttributes())
			{
				TList* attrList = node->GetAttributes();
				TIter next(attrList);
				TXMLAttr *attr;
				while((attr =(TXMLAttr*)next()))
				{
					string attrName = attr->GetName();
					if(isIgnored(attrName)) cout << " ";				
					cout << attr->GetName() << ":" << attr->GetValue();
					add2list(attr->GetName());
					add2list(attr->GetValue());
				}
			}
		}

		if(node->GetNodeType() == TXMLNode::kXMLTextNode) // Text node
		{
			string str = node->GetContent();
			if(isEmptyString(str)) cout << node->GetContent();
			else                   cout << " -> " << node->GetContent();
			add2list(node->GetContent());
		}

		if(node->GetNodeType() == TXMLNode::kXMLCommentNode) // Comment node
		{
			cout << "Comment: " << node->GetContent();
			add2list(node->GetContent());
		}

		ParseContext(node->GetChildren());
	}
}

#endif
