/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "xmlconfig.h"

// xmlconfig* xmlconfig::getInstance()
// {
	// if(theInstance==0) theInstance = new xmlconfig();
	// return theInstance;
// }

xmlconfig::xmlconfig()
{
	domParser = new TDOMParser();
	domParser->SetValidate(false); // do not validate with DTD
}

xmlconfig::~xmlconfig()
{
	delete domParser;
}

void xmlconfig::reset()
{
	if(domParser) delete domParser;
	domParser = new TDOMParser();
	domParser->SetValidate(false); // do not validate with DTD
}

void xmlconfig::header(string fileName)
{
	cout << "\n" << endl;
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
	for(unsigned int i=0 ; i<fileName.length()+4 ; i++) cout << "^";
	cout << "\n^^^ Start parisng the xml file: " << fileName << " ^^^" << endl;
}

void xmlconfig::footer(string fileName)
{
	cout << "^^^ Successfully parsed the xml file: " << fileName << " ^^^" << endl;
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
	for(unsigned int i=0 ; i<fileName.length()+4 ; i++) cout << "^";
	cout << "\n" << endl;
}

void xmlconfig::read(string readerName, string fileName)
{
	reset();
	
	domParser->ParseFile(fileName.c_str());
	node = domParser->GetXMLDocument()->GetRootNode();
	
	if(readerName=="cutflowXml")
	{
		header(fileName);
		cutflowXml::ParseContext(node);
		if(!cutflowXml::mask())
		{
			_ERROR("failed to mask the xml file (" + fileName + "). exitting now.");
			exit(-1);
		}
		footer(fileName);
	}

	if(readerName=="periodsXml")
	{
		header(fileName);
		periodsXml::ParseContext(node);
		if(!periodsXml::mask())
		{
			_ERROR("failed to mask the xml file (" + fileName + "). exitting now.");
			exit(-1);
		}
		footer(fileName);
	}

	if(readerName=="montecarloXml")
	{
		header(fileName);
		montecarloXml::ParseContext(node);
		if(!montecarloXml::mask())
		{
			_ERROR("failed to mask the xml file (" + fileName + "). exitting now.");
			exit(-1);
		}
		footer(fileName);
	}
}

void xmlconfig::get(string xmldir)
{
	read("cutflowXml",xmldir+"/cutflow.xml");
	read("periodsXml",xmldir+"/periods.xml");
	read("montecarloXml",xmldir+"/montecarlo.xml");

	cout << "cutflowXml::cutFlowOrdered.size()=" << cutflowXml::cutFlowOrdered->size() << endl;
	cout << "cutflowXml::cutFlowTypeOrdered.size()=" << cutflowXml::cutFlowTypeOrdered->size() << endl;
	cout << "cutflowXml::cutFlowNumbers.size()=" << cutflowXml::cutFlowNumbers->size() << endl;
	cout << "cutflowXml::cutFlowMapSVD.size()=" << cutflowXml::cutFlowMapSVD->size() << endl;
	cout << "cutflowXml::cutFlowMapSVD.size()=" << cutflowXml::cutFlowMapSVD->size() << endl;
	cout << "cutflowXml::cutsFlowSkipMap.size()=" << cutflowXml::cutsFlowSkipMap->size() << endl;
}


