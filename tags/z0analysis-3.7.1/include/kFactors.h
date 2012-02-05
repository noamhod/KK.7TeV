// #include <basicIncludes.h>
#ifndef KFACTORS_H
#define KFACTORS_H

#include "logs.h"

namespace kFactors
{

/////////////////////////////////
static double maxEWkF = 3.; /////
/////////////////////////////////

static double EWkFactorEle(double mass)
{
	_DEBUG("kFactor::EWkFactorEle");

	// Valid up to 3 TeV
	double kF = 1.;
	if (93.09 < mass && mass <= 250)  kF *= 0.841 + 0.00258*mass - 1.08e-05*mass*mass + 1.54e-08*mass*mass*mass;
	else if (250 < mass && mass <= 1750)  kF *= 1.067 - 6.34e-05*mass;
	else if (1750 < mass)  kF *= 0.873 + 0.000183*mass - 7.97e-08*mass*mass;

	return kF;
}


static double QCD(double mass, string type="NNLO/LO**")
{
	_DEBUG("kFactor::QCD");
	double kF = 1.;
	
	if(type=="NNLO/LO**") // NNLO/MRST_LO** (MC11) -> Valid up to 4 TeV
	{
		double maxMass = 4000.;
		mass = (mass>maxMass) ? maxMass : mass;
		kF *= 1.15171 + 1.90741e-05*mass - 8.05291e-08*mass*mass + 6.42263e-12*mass*mass*mass;
	}
	else if(type=="NNLO/LO*") // NNLO/MRST2007LOmod (MC10 ?) -> Valid up to 3 TeV
	{
		double maxMass = 3000.;
		mass = (mass>maxMass) ? maxMass : mass;
		if (172 < mass) kF *= 1.16260 - 3.11495e-05*mass - 5.75063e-08*mass*mass;
		else  kF *= 1.1555;
	}
	else if(type=="NNLO/MSTW2008LO") // NNLO/MSTW2008LO (MC10 ?) -> Valid up to 3 TeV
	{
		double maxMass = 3000.;
		mass = (mass>maxMass) ? maxMass : mass;
		if(400 < mass) kF *= 1.34815 + 8.58823e-05*mass - 2.11201e-07*mass*mass + 1.11821e-10*mass*mass*mass - 1.76464e-14*mass*mass*mass*mass;
		else kF *= 1.21330e+00 + 8.17233e-04*mass - 1.17503e-06*mass*mass;
	}
	else _FATAL("type="+type+" is unknown.");
	
	if(isnaninf(kF)) _FATAL("QCD "+type+" is nan or inf -> "+_s(kF)+" in mass="+_s(mass));
	if(kF<0.)        _FATAL("QCD "+type+" is negative -> "+_s(kF)+" in mass="+_s(mass));
	
	return kF;
}

static double ElectroWeak(double mass)
{
	_DEBUG("kFactor::ElectroWeak");
	double kF = 1.;
	
	// Valid up to 3 TeV
	double maxMass = 3000.;
	mass = (mass>maxMass) ? maxMass : mass;
	
	if (96.65 < mass && mass <= 250)  kF *= 0.852 + 0.00233*mass - 0.953e-05*mass*mass + 1.31e-08*mass*mass*mass;
	else if (250 < mass && mass <= 1750)  kF *= 1.060 - 6.09e-05*mass;
	else if (1750 < mass)  kF *= 0.931 + 0.000114*mass - 5.71e-08*mass*mass;
	
	if(isnaninf(kF)) _FATAL("EW k-factor is nan or inf -> "+_s(kF)+" in mass="+_s(mass));
	if(kF<0.)        _FATAL("EW k-factor is negative -> "+_s(kF)+" in mass="+_s(mass));
	
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

