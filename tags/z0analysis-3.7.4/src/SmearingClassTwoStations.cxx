#include <cstring>
#include <iostream>
#include <stdio.h>
#include <TROOT.h>
#include <math.h>
#include "TRandom3.h"
#include "SmearingClassTwoStations.h"


  /** Smearing Parameters rel.17 (Muid) **/
  const double ID_MS[4]        = {0., 0., 0., 0.};
  const double ID_AL[4]        = {0.0001933, 0.0002445, 0.000498, 0.00033};
  const double MS_MS[4]        = {0.0195,  0.03966,  0.02875,  0.01822};
  const double MS_AL_3st[4]    = {0.0001001, 0.0004727, 0.0002006, 0.0001503};
  const double MS_AL_2st[4]    = {0.00035, 0.00037, 0., 0.};

  /** MC Parameters rel.17 2 stations (Muid) **/
  const double MC_ID_MS[4]     = {0.01607,  0.02588,  0.03389,  0.05116};
  const double MC_ID_AL[4]     = {0.000307, 0.000331, 0.000436, 0.00094};
  const double MC_MS_MS[4]     = {0.02676,  0.04520,  0.03121,  0.02635};
  const double MC_MS_AL_3st[4] = {0.000103, 0.000192, 0.000080, 0.000051};
  const double MC_MS_AL_2st[4] = {0.00043, 0.00047, 0.001, 0.001};

  /** Data Parameters rel.17 2 stations (Muid) **/
  const double DA_ID_MS[4]    = {0., 0., 0., 0.};
  const double DA_ID_AL[4]    = {0.0001933, 0.0002445, 0.000498, 0.00033};
  const double DA_MS_MS[4]    = {0.0195,  0.03966,  0.02875,  0.01822};
  const double DA_MS_AL_3st[4]    = {0.0001001, 0.0004727, 0.0002006, 0.0001503};
  const double DA_MS_AL_2st[4]    = {0.00055, 0.00060, 0.001, 0.001};

  /** Uncertainty Parameters rel.17 2 stations (Muid) **/
  const double UN_ID_MS[4]     = {0., 0., 0., 0.};
  const double UN_ID_AL[4]     = {9.3695e-06, 4.34e-05, 1.98e-05, 8.59e-05 };
  const double UN_MS_MS[4]     = {0.000414935, 0.00134, 0.00139, 0.0020467};
  const double UN_MS_AL_3st[4] = {1.51251e-05, 8.39e-05, 9e-06, 4.84245e-05};
  const double UN_MS_AL_2st[4] = {0.00004, 0.00018, 0., 0.};


SmearingClassTwoStations::SmearingClassTwoStations(){

    detType="";
    varType="";
    GeV=1000;
    gRand = new TRandom3();
    ptms=0;
    ptid=0;
    ptcb=0;
    eta=0;
}


SmearingClassTwoStations::~SmearingClassTwoStations(){
  
}


void SmearingClassTwoStations::SetTheSeed(int evtnum, int muon_index, int offset) { gRand->SetSeed(offset + evtnum + muon_index*100); }

void SmearingClassTwoStations::SetVarType(std::string VarType) { 
    if (VarType=="UP" || VarType=="LOW") {
       varType=VarType;
       //std::cout << "SmearingClassTwoStations DEBUG:: smearing " << VarType << " by 1 sigma" << std::endl;
    }
    else if (VarType=="") {
       varType=VarType;
       //std::cout << "SmearingClassTwoStations DEBUG:: using nominal 2-station muon smearing constants " << std::endl;
    }
    else std::cout << "SmearingClassTwoStations ERROR:: wrong VarType in input " << VarType << std::endl;
}

void SmearingClassTwoStations::UseGeV() {
    /* if input momenta are in GeV */
  
    GeV=1;
}
  

  /* MS or ID smearing only. DetType="MS","ID"*/
void SmearingClassTwoStations::Event(double Pt, double Eta, std::string DetType) {        
    ptms=0;
    ptid=0;
    ptcb=0;
    eptms=1.;
    eptid=1.;
    
    if (DetType=="MS")      ptms = Pt;
    else if (DetType=="ID") ptid = Pt;
    else std::cout<<"SmearingClassTwoStations ERROR:: wrong DetType in input "<<DetType<<std::endl; 
    eta=Eta;    
    detType=DetType;
    Event();
}
    
  /* For full MS ID and CB smearing */
void SmearingClassTwoStations::Event(double PtMS, double PtID, double PtCB, double Eta, double ePtMS, double ePtID) {
    detType="All";
    ptms   = PtMS;
    ptid   = PtID;
    ptcb   = PtCB;
    eptms  = ePtMS;
    eptid  = ePtID;
    eta    = Eta;
    Event();
}

void SmearingClassTwoStations::Event()  {
    smearMS=0;
    smearID=0;
    smearCB=0;
    
    /* Detector Region */
    if (fabs(eta)<1.05)     detRegion=0;
    else if (fabs(eta)<1.7) detRegion=1;
    else if (fabs(eta)<2.0) detRegion=2;
    else if (fabs(eta)<2.5) detRegion=3;
    else detRegion=-1;
    
    g1 = gRand->Gaus(0,1);  
    g2 = gRand->Gaus(0,1); 
    g3 = gRand->Gaus(0,1); 
    g4 = gRand->Gaus(0,1); 
    
    smearMS = Smearing("MS",varType);
    smearID = Smearing("ID",varType);
    if (detType=="All") smearCB = Combine( smearMS, smearID);
}
  
/*
double SmearingClassTwoStations::Smearing(std::string DetType) {
    
    if (detRegion < 0 || detRegion > 1) return 0;
    
    if (DetType=="MS") {
      double qoverPtSmear = GeV/ptms;
      qoverPtSmear +=  qoverPtSmear * MS_MS[detRegion]*g1;
      qoverPtSmear +=  MS_AL_2st[detRegion] * g2;

      return ( 1./qoverPtSmear );
    }
    else if(DetType=="ID") {
      double qoverPtSmear = GeV/ptid;
      qoverPtSmear +=  qoverPtSmear * ID_MS[detRegion]*g3;
      qoverPtSmear +=  ID_AL[detRegion] * g4;

      return ( 1./qoverPtSmear );
    } 
    else std::cout << "Error:: DetType not defined "<<DetType<<std::endl;

    return 0;
}
*/

double SmearingClassTwoStations::Smearing(std::string DetType, std::string VarType) {
    
    if (detRegion < 0 || detRegion > 1) return 0;
    
    if (DetType=="MS") {
      double qoverPtSmear = GeV/ptms;
        if(VarType=="") {
          qoverPtSmear +=  qoverPtSmear * MS_MS[detRegion]*g1;
          qoverPtSmear +=  MS_AL_2st[detRegion] * g2;
        }
        else if(VarType=="UP") {
          qoverPtSmear +=  qoverPtSmear * (MS_MS[detRegion] + UN_MS_MS[detRegion])*g1;
          qoverPtSmear +=  (MS_AL_2st[detRegion] + UN_MS_AL_2st[detRegion]) * g2;
        }
        else if(VarType=="LOW") {
          qoverPtSmear +=  qoverPtSmear * (MS_MS[detRegion] - UN_MS_MS[detRegion])*g1;
          qoverPtSmear +=  (MS_AL_2st[detRegion] - UN_MS_AL_2st[detRegion]) * g2;
        }
	else {
	  std::cout << "SmearingClassTwoStations ERROR:: VarType not defined "<<VarType<<std::endl;
	  return 0;
	}
	
      return ( 1./qoverPtSmear );
    }
    
    else if(DetType=="ID") {
      double qoverPtSmear = GeV/ptid;
        if(VarType=="") {
          qoverPtSmear +=  qoverPtSmear * ID_MS[detRegion]*g3;
          qoverPtSmear +=  ID_AL[detRegion] * g4;
	}
        else if(VarType=="UP") {
          qoverPtSmear +=  qoverPtSmear * (ID_MS[detRegion] + UN_ID_MS[detRegion])*g3;
          qoverPtSmear +=  (ID_AL[detRegion] + UN_ID_AL[detRegion]) * g4;
	}
        else if(VarType=="LOW") {
          qoverPtSmear +=  qoverPtSmear * (ID_MS[detRegion] - UN_ID_MS[detRegion])*g3;
          qoverPtSmear +=  (ID_AL[detRegion] - UN_ID_AL[detRegion]) * g4;
	}
	else {
	  std::cout << "SmearingClassTwoStations ERROR:: VarType not defined "<<VarType<<std::endl;
	  return 0;
	}

      return ( 1./qoverPtSmear );
    } 
    else std::cout << "SmearingClassTwoStations ERROR:: DetType not defined "<<DetType<<std::endl;

    return 0;
}
  

double SmearingClassTwoStations::Combine(double SmearMS, double SmearID) {
    /** do the average with the uncertainty on the pT measured **/
    
    if (detRegion <0 || detRegion >1 ) return 0;
    if ( ptcb==0 ) {std::cout<<"SmearingClassTwoStations WARNING: ptcb==0"<<std::endl;return 0;}
        
    // Here, I want to combined as 1/pt 

    wMS = eptms * eptms;
    wID = eptid * eptid;
    double wAvg = ( wMS/SmearMS + wID/SmearID ) / (wMS + wID);
    return (1./wAvg);
}

  
double SmearingClassTwoStations::pTMS() {return smearMS * GeV;} // Return results in MeV, unless UseGeV was called
double SmearingClassTwoStations::pTID() {return smearID * GeV;}  
double SmearingClassTwoStations::pTCB() {return smearCB * GeV;}
