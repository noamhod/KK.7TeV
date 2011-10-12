////////////////////////////////////////////////////////////////////////////
//           SmearingClass.h -- ATLAS Experiment Software                 //
////////////////////////////////////////////////////////////////////////////
///
/// class providing corrections to the simulated muon pT to match pT in data.
/// Resolution smearing and scale shift numbers are preliminary
///
/// Version for simulation and data from
/// PLHC 2011 (1st round, preliminary numbers, an update will be provided).
///
/// responsible: atlas-perf-muons-conveners (at) cern.ch
///
#ifndef MuonMomentumCorrections_SmearingClass_H
#define MuonMomentumCorrections_SmearingClass_H

#include <cstring>
#include <iostream>
#include <TROOT.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "TRandom3.h"

class SmearingClass{
 public:
  /*Constructors*/
  SmearingClass(std::string Algo="muid", std::string SmearType="pT", std::string Dir="");
  SmearingClass(const SmearingClass&);
  virtual ~SmearingClass();
  
  /************/
  /* Methods */   
  /**********/
      
  /** configure smearing **/
  void SetSeed(int);
  void SetSeed(int, int, int offset=680049);
  void UseTan2(bool);
  void UseGeV();
  void UseScale(bool);
  void SetAlgoSmearDir(std::string, std::string SmearType="pT", std::string Dir="");
  void FillValues(std::string);
  void PrintValues();
  
  void Event(double, double, std::string);
  void Event(double, double, double, double);
  void Event();
  
  double Smearing(std::string);
  double Combine(double, double);
  double Combine2(double, double);
  void ErrorMatrix();
  
  double pTMS();
  double pTMS(double);
 
  double pTID();
  double pTID(double);
 
  double pTCB();
  double pTCB(double);
  
  double ChargeFlip(double);
  double ChargeFlipMS();
  double ChargeFlipID();
  double ChargeFlipCB();
  
  double SMS();
  double SID();
  double SCB();
 	      
  double VMS();
  double VID();
  double Corr();
 
 
  void MSUP(double&); 
  void MSUP(double&, double&, double&);
  
  void MSLOW(double&);
  void MSLOW(double&, double&, double&);
  
  void IDUP(double&);
  void IDUP(double&, double&, double&);

  void IDLOW(double&);
  void IDLOW(double&, double&, double&);
  
  void PTVar(double&, std::string);
  void PTVar(double&, double&, double&, std::string);
  
  double Sign(double);
  
  /** simple methods for retrieving input values (not needed since all members are public) **/
  double ptms_orig();
  double ptid_orig();
  double ptcb_orig();
  double ETA();
  int DetRegion();
  
  /*members*/
  TRandom3* gRand;
  double ptms,ptid,ptcb,eta;
  double vms,vid,corr;
  double smearMS,smearID,smearCB;
  bool   useTan2;
  std::string detType;
  int detRegion;
  double GeV;
  double g1,g2,g3,g4;
  double wMS,wID;
  bool useScale;
  ifstream InValues;
  
 protected:
  double pTmax;
  std::string Fdir;
  std::string Tsmear;
  std::string Algorithm;
  std::vector<double> scale_CB;
  std::vector<double> scaleSyst_CB;
  
  std::vector<double> p1_ID;
  std::vector<double> p2_ID;
  std::vector<double> p2_ID_TAN;
  std::vector<double> p1_MS;
  std::vector<double> p2_MS;
  
  std::vector<double> E_p1_ID;
  std::vector<double> E_p2_ID;   
  std::vector<double> E_p2_ID_TAN;   
  std::vector<double> E_p1_MS;
  std::vector<double> E_p2_MS;
  
  std::vector<double> S_p1_ID;
  std::vector<double> S_p2_ID;
  std::vector<double> S_p2_ID_TAN;   
  std::vector<double> S_p1_MS;   
  std::vector<double> S_p2_MS;   
  
  std::vector<double> MC_p1_ID;   
  std::vector<double> MC_p2_ID;   
  std::vector<double> MC_p2_ID_TAN;   
  std::vector<double> MC_p0_MS;   
  std::vector<double> MC_p1_MS;   
  std::vector<double> MC_p2_MS;   
  	
  std::vector<double> CorrMatC0;
  std::vector<double> CorrMatC1;
  std::vector<double> CorrMatC2;
  std::vector<double> CorrMatC3;
  std::vector<double> CorrMatC4;
  std::vector<double> CorrMatC5;
  
  std::vector<double> CorrMatTanC0;
  std::vector<double> CorrMatTanC1;
  std::vector<double> CorrMatTanC2;
  std::vector<double> CorrMatTanC3;
  std::vector<double> CorrMatTanC4;
  std::vector<double> CorrMatTanC5;
  
 private:
  void Initialize(std::string, std::string, std::string);
  void Finalize();
  void Clean();

};
#endif
