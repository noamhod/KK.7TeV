//////////////////////////////////////////////////////////////////////////////
//
// ROOT implementation of a XML DOM Parser
//
// This is an example of how Dom Parser walks the DOM tree recursively.
// This example will parse any xml file.
// 
// To run this program
// .x cuts.C++
// 
// Requires: cuts.xml 
// 
//////////////////////////////////////////////////////////////////////////////

#include "XML.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class cutFlow : public XML
{
	public:
		cutFlow()
		{
			cutFlowOrdered     = new TMapds;
			cutFlowTypeOrdered = new TMapds;
			cutFlowNumbers     = new TMapsi;
			cutFlowMapSVD      = new TMapsvd;
			cutsFlowSkipMap    = new TMapsb;
		}
		virtual ~cutFlow(){}
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
		string valname;
		string valorder;
		string valflag;
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

bool cutFlow::mask()
{
	for(TMapiP2cc::iterator ii=list->begin() ; ii!=list->end() ; ++ii)
	{
		int num    = ii->first;
		string str = (string)ii->second;
		cout << "[" << num << "]=" << str << endl;
		
		if(str=="obj")
		{
			if(Next(ii)=="NAME")    name    = Next(ii); else return false;
			if(Next(ii)=="FLAG")    flag    = Next(ii); else return false;
			if(Next(ii)=="order")   order   = Next(ii); else return false;
			if(Next(ii)=="type")    type    = Next(ii); else return false;
			if(Next(ii)=="skip")    skip    = Next(ii); else return false;
			if(Next(ii)=="nvalues") nvalues = Next(ii); else return false;
			cout << "NAME="   << name << ", FLAG=" << flag << ", order="   << order
				 << ", type=" << type << ", skip=" << skip << ", nvalues=" << nvalues
				 << endl;

			if(Next(ii)=="values")
			{
				vdtmp.clear();
				for(int v=1 ; v<=toint(nvalues) ; ++v)
				{
					if(Next(ii)=="value") /* do nothing*/
					if(Next(ii)=="NAME")  valname  = Next(ii); else return false;
					if(Next(ii)=="ORDER") valorder = Next(ii); else return false;
					if(Next(ii)=="FLAG")  valflag  = Next(ii); else return false;
					val = Next(ii);
					cout << "\tvalue[" << v       << "] NAME=" << valname << ", ORDER=" << valorder
						 << ", FLAG="  << valflag << ", val="  << val
						 << endl;

					vdtmp.push_back(validate_double(val));

				}
			}
			else return false;
			
			if(Next(ii)=="description") description = Next(ii); else return false;
			cout << "description=" << description << endl;

			cutFlowOrdered->insert(     make_pair(validate_double(order),name) );
			cutFlowTypeOrdered->insert( make_pair(validate_double(order),type) );
			cutFlowNumbers->insert(     make_pair(name,0) );
			cutFlowMapSVD->insert(      make_pair(name,vdtmp) );
			cutsFlowSkipMap->insert(    make_pair(name,validate_bool(skip)) );

		}
	}
	return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class periods : public XML
{
	public:
		periods(){}
		virtual ~periods(){}
		bool mask();

		/*
		<obj NAME="MC" FLAG="on">
			<start>100000</start>
			<end>150000</end>
			<pTmin>1.</pTmin>
			<ntriggers>1</ntriggers>
			<triggers>
				<trigger NAME="L1_MU10" PRIORITY="1" FLAG="on">10.</trigger>
			</triggers>
			<nevents>-1</nevents>
			<luminosity>-1</luminosity>
			<description>
				The values are in GeV and pb^-1.
			</description>
		</obj>
		*/
	
	
		// specific mask for cuts.xml
		string name;
		string flag;
		string start;
		string end;
		string pTmin;
		string ntriggers;
		string trigname;
		string trigpriority;
		string trigflag;
		string trigpT;
		string nevents;
		string luminosity;
		string description;
	private:
};

bool periods::mask()
{
	for(TMapiP2cc::iterator ii=list->begin() ; ii!=list->end() ; ++ii)
	{
		int num    = ii->first;
		string str = (string)ii->second;
		cout << "[" << num << "]=" << str << endl;
		
		if(str=="obj")
		{
			if(Next(ii)=="NAME")      name      = Next(ii); else return false;
			if(Next(ii)=="FLAG")      flag      = Next(ii); else return false;
			if(Next(ii)=="start")     start     = Next(ii); else return false;
			if(Next(ii)=="end")       end       = Next(ii); else return false;
			if(Next(ii)=="pTmin")     pTmin     = Next(ii); else return false;
			if(Next(ii)=="ntriggers") ntriggers = Next(ii); else return false;
			cout << "NAME="   << name << ", FLAG=" << flag << ", start="   << start
				 << ", end=" << end << ", pTmin=" << pTmin << ", ntriggers=" << ntriggers
				 << endl;

			if(Next(ii)=="triggers")
			{
				for(int t=1 ; t<=toint(ntriggers) ; ++t)
				{
					if(Next(ii)=="trigger")  /* do nothing*/
					if(Next(ii)=="NAME")     trigname     = Next(ii); else return false;
					if(Next(ii)=="PRIORITY") trigpriority = Next(ii); else return false;
					if(Next(ii)=="FLAG")     trigflag     = Next(ii); else return false;
					trigpT = Next(ii);
					cout << "\ttrigger[" << t       << "] NAME=" << trigname << ", PRIORITY=" << trigpriority
						 << ", FLAG="  << trigflag << ", trigpT="  << trigpT
						 << endl;
				}
			}
			else return false;
			
			if(Next(ii)=="nevents")     nevents     = Next(ii); else return false;
			if(Next(ii)=="luminosity")  luminosity  = Next(ii); else return false;
			if(Next(ii)=="description") description = Next(ii); else return false;
			cout << "nevents=" << nevents << ", luminosity=" << luminosity << ", description=" << description << endl;

			//cutFlowOrdered->insert( make_pair(nodeName,nodeContent) );
		}
	}
	return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// NOTE !!! MULTIPLE INHERITANCE !!! /////////////////////////////////////////
class configure : public cutFlow,
		  public periods
{
	public:
		configure()
		{
			domParser = new TDOMParser();
			domParser->SetValidate(false); // do not validate with DTD
		}
		virtual ~configure(){}
		void read(string readerName, string fileName)
		{
			domParser->ParseFile(fileName.c_str());
			node = domParser->GetXMLDocument()->GetRootNode();
			if(readerName=="cuts")
			{
				cutFlow::ParseContext(node);
				if(!cutFlow::mask())
				{
					cout << "failed to mask the xml file. exitting now." << endl;
					exit(-1);
				}
			}
			if(readerName=="periods")
			{
				periods::ParseContext(node);
				if(!periods::mask())
				{
					cout << "failed to mask the xml file. exitting now." << endl;
					exit(-1);
				}
			}
		}
		
		TDOMParser *domParser;
		TXMLNode *node;

	private:
};





///////////////////////////////////////////////////////////////////////////////////////////////////////
void xml_reader()
{
	configure* config = new configure;

	config->read("cuts","cuts.xml");
	config->read("periods","periods.xml");


	cout << "configure::cutFlow::cutFlowOrdered.size()=" << config->cutFlow::cutFlowOrdered->size() << endl;
	cout << "configure::cutFlow::cutFlowTypeOrdered.size()=" << config->cutFlow::cutFlowTypeOrdered->size() << endl;
	cout << "configure::cutFlow::cutFlowNumbers.size()=" << config->cutFlow::cutFlowNumbers->size() << endl;
	cout << "configure::cutFlow::cutFlowMapSVD.size()=" << config->cutFlow::cutFlowMapSVD->size() << endl;
	cout << "configure::cutFlow::cutFlowMapSVD.size()=" << config->cutFlow::cutFlowMapSVD->size() << endl;
	cout << "configure::cutFlow::cutsFlowSkipMap.size()=" << config->cutFlow::cutsFlowSkipMap->size() << endl;
}
