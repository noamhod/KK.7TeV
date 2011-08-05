//////////////////////////////////////////////////////////////////////////////
// ROOT implementation of a XML DOM Parser
// This is an example of how Dom Parser walks the DOM tree recursively.
// This example will parse any xml file.
//////////////////////////////////////////////////////////////////////////////

#ifdef XML_cxx
#include "XML.h"


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

string XML::NextStay(TMapiP2cc::iterator& ii)
{
	++ii;
	string str = ii->second;
	--ii;
	return str;
}

string XML::Previous(TMapiP2cc::iterator& ii)
{
	--ii;
	string str = ii->second;
	return str;
}

string XML::PreviousStay(TMapiP2cc::iterator& ii)
{
	--ii;
	string str = ii->second;
	++ii;
	return str;
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
