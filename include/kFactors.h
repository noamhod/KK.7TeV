// #include <basicIncludes.h>
#ifndef KFACTORS_H
#define KFACTORS_H

#include "logs.h"

namespace kFactors
{

static double QCD(double mass, string type="NNLO/LO*")
{
	_DEBUG("kFactor::QCD");
	double kF = 1.;
	
	if(type=="NNLO/LO*") // NNLO/2007LOmod
	{
		if(172 < mass) kF *= 1.16260 - 3.11495e-05*mass - 5.75063e-08*mass*mass;
		else           kF *= 1.1555;
	}
	else if(type=="NNLO/LO") // NNLO/2008LO
	{
		if(400 < mass) kF *= 1.34815 + 8.58823e-05*mass - 2.11201e-07*mass*mass + 1.11821e-10*mass*mass*mass - 1.76464e-14*mass*mass*mass*mass;
		else           kF *= 1.21330e+00 + 8.17233e-04*mass - 1.17503e-06*mass*mass;
	}
	else
	{
		_ERROR("type="+type+" is unknown, exitting now");
		exit(-1);
	}
	
	return kF;
}

static double ElectroWeak(double mass, string type="NNLO/LO*")
{
	_DEBUG("kFactor::ElectroWeak");
	double kF = 1.;
	
	if(type=="NNLO/LO*") // NNLO/2007LOmod
	{
		if     (110  < mass && mass <= 250)  kF *= 0.852 + 0.00233*mass - 0.953e-05*mass*mass + 1.31e-08*mass*mass*mass;
		else if(250  < mass && mass <= 1750) kF *= 1.060 - 6.09e-05*mass;
		else if(1750 < mass)                 kF *= 0.931 + 0.000114*mass - 5.71e-08*mass*mass;
	}
	else if(type=="NNLO/LO") // NNLO/2008LO
	{
		if     (110  < mass && mass <= 250)  kF *= 0.852 + 0.00233*mass - 0.953e-05*mass*mass + 1.31e-08*mass*mass*mass;
		else if(250  < mass && mass <= 1750) kF *= 1.060 - 6.09e-05*mass;
		else if(1750 < mass)                 kF *= 0.931 + 0.000114*mass - 5.71e-08*mass*mass;
	}
	else
	{
		_ERROR("type="+type+" is unknown, exitting now");
		exit(-1);
	}
	return kF;
}

bool iskFactor(string mcname)
{
	size_t found;
	string sDY      = "DYmumu";
	string sZ       = "Zmumu";
	string sZprime  = "Zprime_mumu";
	
	found = mcname.find(sDY);
	if(found!=string::npos) return true;
	
	found = mcname.find(sZ);
	if(found!=string::npos) return true;
	
	found = mcname.find(sZprime);
	if(found!=string::npos) return true;
	
	return false;
}

double getTruthMass(vector<int>* pdgId, vector<float>* mass, int idZ=23)
{
	double truth_mass = 0.;
	unsigned int N = pdgId->size();
	for(unsigned int i=0 ; i<N ; i++)
	{
		int idi = pdgId->at(i);
		if(idi==idZ)
		{ 
			truth_mass = mass->at(i);
			break;
		}
	}
	return truth_mass;
}

}

#endif

