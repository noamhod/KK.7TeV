/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "cutFlowHandler.h"

void cutFlowHandler::setCutFlowFile(string sLogFilePath, string srunnumber)
{	
	string sLogFileName = sLogFilePath+"/RunCutFlow.run_"+srunnumber+".cuts";//".time_"+getDateHour()+".cuts";
	file = new ofstream( sLogFileName.c_str() );
}

void cutFlowHandler::incrementNallEvents()
{
	nAllEvents++;
}

void cutFlowHandler::printCutFlowNumbers(Long64_t chainEntries, string name)
{
	if(false) cout << "chainEntries = " << chainEntries << endl;
	cout << "+--------------------------------------------------------------------------" << endl;
	cout << "|                 " << name << " cut flow numbers                          " << endl;
	cout << "|.........................................................................." << endl;
	cout << "| processed: all " << nAllEvents << endl;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		double num = ii->first;
		string scutname = ii->second;
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") cout << "| PRESELECTION: " << scutname <<  " " << m_cutFlowNumbers->operator[](scutname) << endl;
		if(m_cutFlowTypeOrdered->operator[](num)=="selection")    cout << "| SELECTION: " << scutname <<  " " << m_cutFlowNumbers->operator[](scutname) << endl;
	}
	cout << "+--------------------------------------------------------------------------" << endl;
	
	
	// to file:
	(*file) << "+--------------------------------------------------------------------------" << endl;
	(*file) << "|                 " << name << " cut flow numbers                          " << endl;
	(*file) << "|.........................................................................." << endl;
	(*file) << "| processed: all " << nAllEvents << endl;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		double num = ii->first;
		string scutname = ii->second;
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") (*file) << "| PRESELECTION: " << scutname <<  " " << m_cutFlowNumbers->operator[](scutname) << endl;
		if(m_cutFlowTypeOrdered->operator[](num)=="selection")    (*file) << "| SELECTION: " << scutname <<  " " << m_cutFlowNumbers->operator[](scutname) << endl;
	}
	(*file) << "+--------------------------------------------------------------------------\n" << endl;
}

TMapds* cutFlowHandler::getCutFlowOrderedMapPtr()
{
	return m_cutFlowOrdered;
}

TMapds* cutFlowHandler::getCutFlowTypeOrderedMapPtr()
{
	return m_cutFlowTypeOrdered;
}

TMapsi*  cutFlowHandler::getCutFlowNumbersMapPtr()
{
	return m_cutFlowNumbers;
}

TMapsvd* cutFlowHandler::getCutFlowMapSVDPtr()
{
	return m_cutFlowMapSVD;
}

TMapsb*	cutFlowHandler::getCutFlowToSkipMapPtr()
{
	return m_cutsFlowSkipMap;
}

bool cutFlowHandler::mask()
{
	for(TMapiP2cc::iterator ii=list->begin() ; ii!=list->end() ; ++ii)
	{
		int num    = ii->first;
		string str = (string)ii->second;
		_INFO("["+tostring(num)+"]="+str);
		
		if(str=="obj")
		{
			if(Next(ii)=="NAME")    name    = Next(ii); else {_ERROR("obj: failed to read NAME->"+PreviousStay(ii)); return false;}
			if(Next(ii)=="FLAG")    flag    = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read FLAG->"+PreviousStay(ii)); return false;}
			if(Next(ii)=="order")   order   = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read order->"+PreviousStay(ii)); return false;}
			if(Next(ii)=="phase")   phase   = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read phase->"+PreviousStay(ii)); return false;}
			if(Next(ii)=="skip")    skip    = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read skip->"+PreviousStay(ii)); return false;}
			if(Next(ii)=="nparameters") nparameters = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read nparameters->"+PreviousStay(ii)); return false;}
			_INFO("NAME="+name+", FLAG="+flag+", order="+order+", phase="+phase+", skip="+skip+", nparameters="+nparameters);

			if(Next(ii)=="parameters")
			{
				vdtmp.clear();
				for(int v=1 ; v<=validate_int(nparameters) ; ++v)
				{
					if(Next(ii)=="parameter") /* do nothing*/
					if(Next(ii)=="NAME")  attrname  = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read NAME->"+PreviousStay(ii)); return false;}
					if(Next(ii)=="ORDER") attrorder = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read ORDER->"+PreviousStay(ii)); return false;}
					if(Next(ii)=="TYPE")  attrtype  = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read TYPE->"+PreviousStay(ii)); return false;}
					val = Next(ii);
					_INFO("\tparameter["+tostring(v)+"] NAME="+attrname+", ORDER="+attrorder+", TYPE="+attrtype+", val="+val);
					// HAVE TO CHECK THE TYPE !!!!!
					vdtmp.push_back(validate_double(val));
				}
				if((int)vdtmp.size() != validate_int(nparameters)) {_ERROR("vector size doesn't match nparameters"); return false;}
			}
			else {_ERROR("obj NAME:"+name+" -> failed to read parameters->"+PreviousStay(ii)); return false;}
			
			if(Next(ii)=="description") description = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read description->"+PreviousStay(ii)); return false;}
			_INFO("description="+description);

			m_cutFlowOrdered->insert(     make_pair(validate_double(order),name) );
			m_cutFlowTypeOrdered->insert( make_pair(validate_double(order),phase) );
			m_cutFlowNumbers->insert(     make_pair(name,0) );
			m_cutFlowMapSVD->insert(      make_pair(name,vdtmp) );
			m_cutsFlowSkipMap->insert(    make_pair(name,validate_bool(skip)) );
		}
	}
	return true;
}


