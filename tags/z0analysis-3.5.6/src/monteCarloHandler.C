/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "monteCarloHandler.h"

bool montecarloXml::mask()
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
				//if((int)vdtmp.size() != validate_int(nfiles)) {_ERROR("vector size doesn't match nfiles"); return false;}
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
				//if((int)vdtmp.size() != validate_int(nkfactors)) {_ERROR("vector size doesn't match nkfactors"); return false;}
			}
			else return false;
			
			//_ERROR("");
			
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



