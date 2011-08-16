/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "periodHandler.h"

TMapis* periodHandler::getFirstRun2PeriodMapPtr()
{
	return m_firstrun2periodMap;
}

TMapis* periodHandler::getLastRun2PeriodMapPtr()
{
	return m_lastrun2periodMap;
}

TMapsP2vs* periodHandler::getPeriod2TriggerMapPtr()
{
	return m_period2triggerMap;
}

TMapsP2vd* periodHandler::getPeriod2pTthresholdMapPtr()
{
	return m_period2pTthresholdMap;
}

TMapsP2vd* periodHandler::getPeriod2pTminMapPtr()
{
	return m_period2pTminMap;
}

TMapss* periodHandler::getPeriod2triggerperiodMapPtr()
{
	return m_period2triggerperiodMap;
}


string periodHandler::getPeriod(int runNumber, TMapis* firstrun2periodMap, TMapis* lastrun2periodMap)
{	
	int fst = 0;
	int lst = 0;
	
	TMapis::iterator ifst = firstrun2periodMap->begin();
	TMapis::iterator ilst = lastrun2periodMap->begin();
		
	// find the run range
	while(ifst!=firstrun2periodMap->end()  &&  ilst!=lastrun2periodMap->end())
	{
		int tmpfst = ifst->first;
		int tmplst = ilst->first;
				
		if(runNumber>=tmpfst  &&  runNumber<=tmplst)
		{
			fst = tmpfst;
			lst = lst;
			break;
		}
		
		ifst++;
		ilst++;
	}
	
	// check the period name
	if(ifst->second != ilst->second)
	{
		_ERROR("[1] didn't find a period, exitting now...");
		exit(-1);
	}
	
	if(ifst==firstrun2periodMap->end())
	{
		_ERROR("[2] didn't find a period, exitting now...");
		exit(-1);
	}
	
	// get the period name
	string sPeriod = ifst->second;
		
	return sPeriod;
}

vector<string>* periodHandler::getTrigs(string sPeriod, TMapsP2vs* period2triggerMap)
{
	TMapsP2vs::iterator it = period2triggerMap->find(sPeriod);
	if(it==period2triggerMap->end())
	{
		_ERROR("didn't find a period, exitting now...");
		exit(-1);
	}
	return it->second;
}


bool periodHandler::mask()
{
	for(TMapiP2cc::iterator ii=list->begin() ; ii!=list->end() ; ++ii)
	{
		int num    = ii->first;
		string str = (string)ii->second;
		_INFO("["+tostring(num)+"]="+str);
		
		if(str=="obj")
		{
			if(Next(ii)=="NAME") name = Next(ii); else {_ERROR("obj: failed to read NAME->"+PreviousStay(ii)); return false;}
			if(Next(ii)=="FLAG") flag = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read FLAG->"+PreviousStay(ii)); return false;}
			if(name=="TRIGGERPERIODS")
			{
				if(Next(ii)=="ntriggerperiods") number = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read ntriggerperiods->"+PreviousStay(ii)); return false;}
				_INFO("NAME="+name+", ntriggerperiods="+number);
				if(Next(ii)=="triggerperiods")
				{	
					vdtmp_lumi = new vector<double>;
					vstmp_tname = new vector<string>;
					for(int tp=1 ; tp<=validate_int(number) ; ++tp)
					{
						if(Next(ii)=="triggerperiod")  /* do nothing*/
						if(Next(ii)=="NAME")     attrname = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read NAME->"+PreviousStay(ii)); return false;}
						if(Next(ii)=="FLAG")     attrflag = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read FLAG->"+PreviousStay(ii)); return false;}
						luminosity = Next(ii);
						_INFO("\ttriggerperiod["+tostring(tp)+"] NAME="+attrname+", FLAG="+attrflag+", luminosity="+luminosity);
						vdtmp_lumi->push_back(validate_double(luminosity));
						vstmp_tname->push_back(attrname);
					}
					if((int)vdtmp_lumi->size() != validate_int(number)) {_ERROR("vector size doesn't match number"); return false;}
				}
				if(Next(ii)=="description") description = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read description->"+PreviousStay(ii)); return false;}
				_INFO("description="+description);
			}
			else
			{
				if(Next(ii)=="start")     start     = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read start->"+PreviousStay(ii)); return false;}
				if(Next(ii)=="end")       end       = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read end->"+PreviousStay(ii)); return false;}
				if(Next(ii)=="ntriggers") ntriggers = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read ntriggers->"+PreviousStay(ii)); return false;}
				_INFO("NAME="+name+", FLAG="+flag+", start="+start+", end="+end+", ntriggers="+ntriggers);

				if(Next(ii)=="triggers")
				{
					vdtmp_ptmin = new vector<double>;
					vdtmp_ptthresh = new vector<double>;
					vstmp_name = new vector<string>;
					for(int t=1 ; t<=validate_int(ntriggers) ; ++t)
					{
						if(Next(ii)=="trigger")  /* do nothing*/
						if(Next(ii)=="NAME")     attrname     = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read NAME->"+PreviousStay(ii)); return false;}
						if(Next(ii)=="PRIORITY") trigpriority = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read PRIORITY->"+PreviousStay(ii)); return false;}
						if(Next(ii)=="MIN")      attrflag     = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read MIN->"+PreviousStay(ii)); return false;}
						trigpT = Next(ii);
						_INFO("\ttrigger["+tostring(t)+"] NAME="+attrname+", PRIORITY="+trigpriority+", MIN="+attrflag+", trigpT="+trigpT);
						vdtmp_ptmin->push_back(validate_double(attrflag));
						vdtmp_ptthresh->push_back(validate_double(trigpT));
						vstmp_name->push_back(attrname);
					}
					if((int)vdtmp_ptmin->size() != validate_int(ntriggers)) {_ERROR("vector(s) size doesn't match ntriggers"); return false;}
				}
				else {_ERROR("obj NAME:"+name+" -> failed to read triggers->"+PreviousStay(ii)); return false;}
				
				if(Next(ii)=="nevents")     nevents     = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read nevents->"+PreviousStay(ii)); return false;}
				if(Next(ii)=="luminosity")  luminosity  = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read luminosity->"+PreviousStay(ii)); return false;}
				if(Next(ii)=="description") description = Next(ii); else {_ERROR("obj NAME:"+name+" -> failed to read description->"+PreviousStay(ii)); return false;}
				_INFO("nevents="+nevents+", luminosity="+luminosity+", description="+description);

				string sTriggerPeriod = "";
				for(int i=0 ; i<(int)vstmp_name->size() ; i++)
				{
					if(i==0) sTriggerPeriod += vstmp_name->at(i);
					if(i>0)  sTriggerPeriod += "||" + vstmp_name->at(i);
				}
				
				// fill the db
				m_firstrun2periodMap->insert( make_pair(validate_int(start),name) );
				m_lastrun2periodMap->insert( make_pair(validate_int(end),name) );
				m_period2triggerMap->insert( make_pair(name,vstmp_name) );
				m_period2triggerperiodMap->insert( make_pair(name,sTriggerPeriod) );
				m_period2pTminMap->insert( make_pair(name,vdtmp_ptmin) );
				m_period2pTthresholdMap->insert( make_pair(name,vdtmp_ptthresh) );
			}
		}
	}
	return true;
}






