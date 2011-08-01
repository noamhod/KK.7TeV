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
			
			ignoreString("obj");
			ignoreString("NAME");
			ignoreString("FLAG");
			ignoreString("ORDER");
			ignoreString("value");
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
				for(int v=1 ; v<=validate_int(nvalues) ; ++v)
				{
					if(Next(ii)=="value") /* do nothing*/
					if(Next(ii)=="NAME")  attrname  = Next(ii); else return false;
					if(Next(ii)=="ORDER") attrorder = Next(ii); else return false;
					if(Next(ii)=="FLAG")  attrflag  = Next(ii); else return false;
					val = Next(ii);
					cout << "\tvalue[" << v       << "] NAME=" << attrname << ", ORDER=" << attrorder
						 << ", FLAG="  << attrflag << ", val="  << validate_double(val)/*val*/
						 << endl;

					vdtmp.push_back(validate_double(val));
				}
				if((int)vdtmp.size() != validate_int(nvalues)) {cout << LOG("vector size doesn't match nvalues") << endl; return false;}
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
		periods()
		{
			ignoreString("obj");
			ignoreString("NAME");
			ignoreString("FLAG");
			ignoreString("PRIORITY");
			ignoreString("trigger");
			ignoreString("period");
			ignoreString("triggerperiod");
		}
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
		
		/*
		<obj NAME="PERIODS" NUMBER="9">
			<periods>
				<period NAME="A" FLAG="on">0.0000157154</period>
				<period NAME="B" FLAG="on">0.00883395</period>
				<period NAME="C" FLAG="on">0.00871179</period>
				<period NAME="D" FLAG="on">0.255204</period>
				<period NAME="E" FLAG="on">1.08162</period>
				<period NAME="F" FLAG="on">1.95816</period>
				<period NAME="G" FLAG="on">6.89501</period>
				<period NAME="H" FLAG="on">8.52076</period>
				<period NAME="I" FLAG="on">22.9524</period>
			</periods>
			<description>
				The values are in  pb^-1.
			</description>
		</obj>
		*/
		
		/*
		<obj NAME="TRIGGERPERIODS" NUMBER="4">
			<triggerperiods>
				<triggerperiod NAME="L1_MU10" FLAG="on">0.272906894</triggerperiod>
				<triggerperiod NAME="EF_mu10" FLAG="on">3.03978</triggerperiod>
				<triggerperiod NAME="EF_mu13" FLAG="on">6.89501</triggerperiod>
				<triggerperiod NAME="EF_mu13_tight" FLAG="on">31.47316</triggerperiod>
			</triggerperiods>
			<description>
				The values are in pb^-1.
			</description>
		</obj>
		*/
	
		// specific mask for periods.xml
		string name;
		string flag;
		string start;
		string end;
		string pTmin;
		string ntriggers;
		string attrname;
		string trigpriority;
		string attrflag;
		string trigpT;
		string nevents;
		string luminosity;
		string description;
		string number;
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
			if(Next(ii)=="NAME") name = Next(ii); else return false;
			if(Next(ii)=="FLAG") flag = Next(ii); else return false;
			if(name=="PERIODS")
			{
				if(Next(ii)=="nperiods") number = Next(ii); else return false;
				cout << "NAME=" << name << ", nperiods=" << number << endl;
				if(Next(ii)=="periods")
				{
					for(int p=1 ; p<=validate_int(number) ; ++p)
					{
						if(Next(ii)=="period")  /* do nothing*/
						if(Next(ii)=="NAME")     attrname = Next(ii); else return false;
						if(Next(ii)=="FLAG")     attrflag = Next(ii); else return false;
						luminosity = Next(ii);
						cout << "\tperiod[" << p        << "] NAME="        << attrname
							 << ", FLAG="   << attrflag << ", luminosity="  << luminosity
							 << endl;
					}
					//if((int)vdtmp.size() != validate_int(number)) {cout << LOG("vector size doesn't match number") << endl; return false;}
				}
				if(Next(ii)=="description") description = Next(ii); else return false;
				cout << "description=" << description << endl;
			}
			else if(name=="TRIGGERPERIODS")
			{
				if(Next(ii)=="ntriggerperiods") number = Next(ii); else return false;
				cout << "NAME=" << name << ", ntriggerperiods=" << number << endl;
				if(Next(ii)=="triggerperiods")
				{
					for(int tp=1 ; tp<=validate_int(number) ; ++tp)
					{
						if(Next(ii)=="triggerperiod")  /* do nothing*/
						if(Next(ii)=="NAME")     attrname = Next(ii); else return false;
						if(Next(ii)=="FLAG")     attrflag = Next(ii); else return false;
						luminosity = Next(ii);
						cout << "\ttriggerperiod[" << tp       << "] NAME="        << attrname
							 << ", FLAG="          << attrflag << ", luminosity="  << luminosity
							 << endl;
					}
					//if((int)vdtmp.size() != validate_int(number)) {cout << LOG("vector size doesn't match number") << endl; return false;}
				}
				if(Next(ii)=="description") description = Next(ii); else return false;
				cout << "description=" << description << endl;
			}
			else
			{
				if(Next(ii)=="start")     start     = Next(ii); else return false;
				if(Next(ii)=="end")       end       = Next(ii); else return false;
				if(Next(ii)=="pTmin")     pTmin     = Next(ii); else return false;
				if(Next(ii)=="ntriggers") ntriggers = Next(ii); else return false;
				cout << "NAME="   << name << ", FLAG=" << flag << ", start="   << start
					 << ", end=" << end << ", pTmin=" << pTmin << ", ntriggers=" << ntriggers
					 << endl;

				if(Next(ii)=="triggers")
				{
					for(int t=1 ; t<=validate_int(ntriggers) ; ++t)
					{
						if(Next(ii)=="trigger")  /* do nothing*/
						if(Next(ii)=="NAME")     attrname     = Next(ii); else return false;
						if(Next(ii)=="PRIORITY") trigpriority = Next(ii); else return false;
						if(Next(ii)=="FLAG")     attrflag     = Next(ii); else return false;
						trigpT = Next(ii);
						cout << "\ttrigger[" << t       << "] NAME=" << attrname << ", PRIORITY=" << trigpriority
							 << ", FLAG="  << attrflag << ", trigpT="  << trigpT
							 << endl;
					}
					//if((int)vdtmp.size() != validate_int(ntriggers)) {cout << LOG("vector size doesn't match ntriggers") << endl; return false;}
				}
				else return false;
				
				if(Next(ii)=="nevents")     nevents     = Next(ii); else return false;
				if(Next(ii)=="luminosity")  luminosity  = Next(ii); else return false;
				if(Next(ii)=="description") description = Next(ii); else return false;
				cout << "nevents=" << nevents << ", luminosity=" << luminosity << ", description=" << description << endl;

				// fill the db
			}
		}
	}
	return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class montecarlo : public XML
{
	public:
		montecarlo()
		{
			ignoreString("obj");
			ignoreString("NAME");
			ignoreString("FLAG");
			ignoreString("file");
			ignoreString("kfactor");
			ignoreString("MINRANGE");
			ignoreString("MAXRANGE");
		}
		virtual ~montecarlo(){}
		bool mask();

		/*
		  <obj NAME="DYmumu_75M120" FLAG="on">
			<number>150000</number>
			<internalnumber>1</internalnumber>
			<isbinned>true</isbinned>
			<dir>/data/hod/D3PDfin/rel16/DYmumu/muid/</dir>
			<nfiles>2</nfiles>
			<files>
				<file>mcLocalControl_DYmumu_75M120.1.root</file>
				<file>mcLocalControl_DYmumu_75M120.2.root</file>
			</files>
			<nevents>19996</nevents>
			<crosssection>817.05</crosssection>
			<crosssectionerr>0.05</crosssectionerr>
			<br>1</br>
			<geneff>1</geneff>
			<nkfactors>2</nkfactors>
			<kfactors>
			  <kfactor MINRANGE="0." MAXRANGE="100.">1.25</kfactor>
			  <kfactor MINRANGE="100." MAXRANGE="150.">1.25</kfactor>
			</kfactors>
			<mcweight>1</mcweight> <!--?????????????-->
			<pileup>1</pileup>     <!--?????????????-->
			<smearing>1</smearing> <!--?????????????-->
			<color>1</color>
			<linestyle>1</linestyle>
			<fillstyle>1</fillstyle>
			<description>
				The values are in pb
			</description>
		  </obj>
		*/
	
		// specific mask for montecarlo.xml
		string name;
		string number;
		string flag;
		string dir;
		string nfiles;
		string file;
		string isbinned;
		string internalnumber;
		string crosssection;
		string crosssectionerr;
		string br;
		string geneff;
		string nkfactors;
		string minrange;
		string maxrange;
		string kfactor;
		string nevents;
		string color;
		string linestyle;
		string fillstyle;
		string mcweight;
		string pileup;
		string smearing;
		string description;
	private:
};

bool montecarlo::mask()
{
	for(TMapiP2cc::iterator ii=list->begin() ; ii!=list->end() ; ++ii)
	{
		int num    = ii->first;
		string str = (string)ii->second;
		cout << "[" << num << "]=" << str << endl;
		
		if(str=="obj")
		{
			if(Next(ii)=="NAME")            name            = Next(ii); else return false;
			if(Next(ii)=="FLAG")            flag            = Next(ii); else return false;
			if(Next(ii)=="number")          number          = Next(ii); else return false;
			if(Next(ii)=="internalnumber")  internalnumber  = Next(ii); else return false;
			if(Next(ii)=="isbinned")        isbinned        = Next(ii); else return false;
			if(Next(ii)=="dir")             dir             = Next(ii); else return false;
			if(Next(ii)=="nfiles")          nfiles          = Next(ii); else return false;
			cout << "NAME="   << name << ", NUMBER=" << number << ", ISBINNED="   << isbinned
				 << ", FLAG=" << flag << ", internalnumber=" << internalnumber
				 << ", dir="  << dir  << ", nfiles=" << nfiles
				 << endl;
			if(Next(ii)=="files")
			{
				for(int f=1 ; f<=validate_int(nfiles) ; ++f)
				{
					if(Next(ii)=="file")  /* do nothing*/
					file = Next(ii);
					cout << "\tfile[" << f << "] filename="  << file
						 << endl;
				}
				//if((int)vdtmp.size() != validate_int(nfiles)) {cout << LOG("vector size doesn't match nfiles") << endl; return false;}
			}
			else return false;
			
			if(Next(ii)=="nevents")         nevents         = Next(ii); else return false;
			if(Next(ii)=="crosssection")    crosssection    = Next(ii); else return false;
			if(Next(ii)=="crosssectionerr") crosssectionerr = Next(ii); else return false;
			if(Next(ii)=="br")              br              = Next(ii); else return false;
			if(Next(ii)=="geneff")          geneff          = Next(ii); else return false;
			if(Next(ii)=="nkfactors")       nkfactors       = Next(ii); else return false;
			cout << "nevents=" << nevents << ", crosssection=" << crosssection
				 << ", crosssectionerr=" << crosssectionerr << ", br=" << br
				 << ", geneff=" << geneff << ", nkfactors=" << nkfactors
				 << endl;

			if(Next(ii)=="kfactors")
			{
				for(int k=1 ; k<=validate_int(nkfactors) ; ++k)
				{
					if(Next(ii)=="kfactor")  /* do nothing*/
					if(Next(ii)=="MINRANGE") minrange = Next(ii); else return false;
					if(Next(ii)=="MAXRANGE") maxrange = Next(ii); else return false;
					kfactor = Next(ii);
					cout << "\tkfactor[" << k       << "] MINRANGE=" << minrange << ", MAXRANGE=" << maxrange
						 << ", kfactor="  << kfactor
						 << endl;
				}
				//if((int)vdtmp.size() != validate_int(nkfactors)) {cout << LOG("vector size doesn't match nkfactors") << endl; return false;}
			}
			else return false;
			
			cout << LOG("") << endl;
			
			if(Next(ii)=="mcweight")    mcweight    = Next(ii); else return false;
			if(Next(ii)=="pileup")      pileup      = Next(ii); else return false;
			if(Next(ii)=="smearing")    smearing    = Next(ii); else return false;
			if(Next(ii)=="color")       color       = Next(ii); else return false;
			if(Next(ii)=="linestyle")   linestyle   = Next(ii); else return false;
			if(Next(ii)=="fillstyle")   fillstyle   = Next(ii); else return false;
			if(Next(ii)=="description") description = Next(ii); else return false;
			cout << "mcweight=" << mcweight << ", pileup=" << pileup << ", smearing=" << smearing
				 << ", color=" << color << ", linestyle=" << linestyle << ", fillstyle=" << fillstyle
				 << ", description=" << description << endl;
			
			// fill the db
		}
	}
	return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// NOTE !!! MULTIPLE INHERITANCE !!! /////////////////////////////////////////
class configure : public cutFlow, 
				  public periods,
				  public montecarlo
{
	public:
		
		configure()
		{
			domParser = new TDOMParser();
			domParser->SetValidate(false); // do not validate with DTD
		}
		
		virtual ~configure()
		{
			delete domParser;
		}
		
		void reset()
		{
			if(domParser) delete domParser;
			domParser = new TDOMParser();
			domParser->SetValidate(false); // do not validate with DTD
		}
		
		void header(string fileName)
		{
			cout << "\n" << endl;
			cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
			for(unsigned int i=0 ; i<fileName.length()+4 ; i++) cout << "^";
			cout << "\n^^^ Start parisng the xml file: " << fileName << " ^^^" << endl;
		}
		
		void footer(string fileName)
		{
			cout << "^^^ Successfully parsed the xml file: " << fileName << " ^^^" << endl;
			cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
			for(unsigned int i=0 ; i<fileName.length()+4 ; i++) cout << "^";
			cout << "\n" << endl;
		}
		
		void read(string readerName, string fileName)
		{
			reset();
			
			domParser->ParseFile(fileName.c_str());
			node = domParser->GetXMLDocument()->GetRootNode();
			
			if(readerName=="cuts")
			{
				header(fileName);
				cutFlow::ParseContext(node);
				if(!cutFlow::mask())
				{
					cout << LOG("failed to mask the xml file (" + fileName + "). exitting now.") << endl;
					exit(-1);
				}
				footer(fileName);
			}
			
			if(readerName=="periods")
			{
				header(fileName);
				periods::ParseContext(node);
				if(!periods::mask())
				{
					cout << LOG("failed to mask the xml file (" + fileName + "). exitting now.") << endl;
					exit(-1);
				}
				footer(fileName);
			}
			
			if(readerName=="montecarlo")
			{
				header(fileName);
				montecarlo::ParseContext(node);
				if(!montecarlo::mask())
				{
					cout << LOG("failed to mask the xml file (" + fileName + "). exitting now.") << endl;
					exit(-1);
				}
				footer(fileName);
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
	config->read("montecarlo","montecarlo.xml");


	cout << "configure::cutFlow::cutFlowOrdered.size()=" << config->cutFlow::cutFlowOrdered->size() << endl;
	cout << "configure::cutFlow::cutFlowTypeOrdered.size()=" << config->cutFlow::cutFlowTypeOrdered->size() << endl;
	cout << "configure::cutFlow::cutFlowNumbers.size()=" << config->cutFlow::cutFlowNumbers->size() << endl;
	cout << "configure::cutFlow::cutFlowMapSVD.size()=" << config->cutFlow::cutFlowMapSVD->size() << endl;
	cout << "configure::cutFlow::cutFlowMapSVD.size()=" << config->cutFlow::cutFlowMapSVD->size() << endl;
	cout << "configure::cutFlow::cutsFlowSkipMap.size()=" << config->cutFlow::cutsFlowSkipMap->size() << endl;
}
