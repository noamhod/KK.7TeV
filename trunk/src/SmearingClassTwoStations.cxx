// #include <cstring>
// #include <iostream>
// #include <stdio.h>
// #include <TROOT.h>
// #include <math.h>
// #include "TRandom3.h"
#include "SmearingClassTwoStations.h"


//---------------------------------------------------------------------
  //// Smearing Parameters rel.17 2 stations (Muid)
  const double ID_MS[4]       = {0., 0., 0., 0.};
  const double ID_AL[4]       = {0., 0., 0., 0. };
  const double MS_MS[4]       = {0.02, 0., 0. ,0.};
  const double MS_AL[4]       = {0.00035, 0.00037, 0., 0.};

/*
 //// Over-Smearing Parameters rel.17 2 stations (Muid)
 const double ID_MS[4]       = {0., 0., 0., 0.};
 const double ID_AL[4]       = {0., 0., 0., 0. };
 const double MS_MS[4]       = {0.03, 0., 0. ,0.};
 const double MS_AL[4]       = {0.00039, 0.00055, 0., 0.};
*/
//--------------------------------------------------------------------- 
 
 

  /** MC Parameters rel.17 2 stations (Muid) **/
  const double MC_ID_MS[4]    = {0.01607,  0.02588,  0.03389,  0.05116};
  const double MC_ID_AL[4]    = {0.000307, 0.000331, 0.000436, 0.00094};
  const double MC_MS_MS[4]    = {0.02676,  0.04520,  0.03121,  0.02635};
  const double MC_MS_AL[4]    = {0.00043, 0.00047, 0.001, 0.001};



SmearingClassTwoStations::SmearingClassTwoStations(){

    detType="";
    GeV=1000;
    gRand = new TRandom3();
    ptms=0;
    ptid=0;
    ptcb=0;
    eta=0;
}


SmearingClassTwoStations::~SmearingClassTwoStations(){
  
}

  /** configure smearing **/
  
void SmearingClassTwoStations::SetTheSeed(int evtnum, int muon_index, int offset) { gRand->SetSeed(offset + evtnum + muon_index*100); }


void SmearingClassTwoStations::UseGeV() {
  /* if input momenta are in GeV */
  
  GeV=1;
}
  

  /* MS or ID smearing only. DetType="MS","ID"*/
void SmearingClassTwoStations::Event(double Pt, double Eta,std::string DetType) {        
    ptms=0;
    ptid=0;
    ptcb=0;
    eptms=1.;
    eptid=1.;
    
    if (DetType=="MS")      ptms = Pt;
    else if (DetType=="ID") ptid = Pt;
    else std::cout<<"SmearingClass ERROR: wrong DetType in input "<<DetType<<std::endl; 
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
    
    smearMS = Smearing("MS");
    smearID = Smearing("ID");
    if (detType=="All") smearCB = Combine( smearMS, smearID);
}
  

double SmearingClassTwoStations::Smearing(std::string DetType) {
    
    if (detRegion < 0 || detRegion > 1) return 0;
    
    if (DetType=="MS") {
      double qoverPtSmear = GeV/ptms;
      qoverPtSmear +=  qoverPtSmear * MS_MS[detRegion]*g1;
      qoverPtSmear +=  MS_AL[detRegion] * g2;

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
  

double SmearingClassTwoStations::Combine(double SmearMS, double SmearID) {
    /** do the average with the uncertainty on the pT measured **/
    
    if (detRegion <0 || detRegion >1 ) return 0;
    if ( ptcb==0 ) {std::cout<<"Warning: ptcb==0"<<std::endl;return 0;}
        
    // Here, I want to combined as 1/pt 

    wMS = eptms * eptms;
    wID = eptid * eptid;
    double wAvg = ( wMS/SmearMS + wID/SmearID ) / (wMS + wID);
    return (1./wAvg);
}

  
double SmearingClassTwoStations::pTMS() {return smearMS * GeV;} // Return results in MeV, unless UseGeV was called
double SmearingClassTwoStations::pTID() {return smearID * GeV;}  
double SmearingClassTwoStations::pTCB() {return smearCB * GeV;}
