#ifndef SMEARINGCLASSTWO_H
#define SMEARINGCLASSTWO_H

#include <cstring>
#include <iostream>
#include <stdio.h>
#include <TROOT.h>
#include <math.h>
#include "TRandom3.h"


class SmearingClassTwoStations{

 public:

  SmearingClassTwoStations();
  ~SmearingClassTwoStations();  
    
  void Initialize();
  
  /** configure smearing **/

  bool UseScale( bool useScale);
  
  void SetTheSeed(int evtnum, int muon_index, int offset);
  void SetVarType(std::string VarType);
  void UseGeV();
  
  /* MS or ID smearing only. DetType="MS","ID" */
  void Event(double Pt, double Eta, std::string DetType);
  /* For full MS ID and CB smearing */
  void Event(double PtMS, double PtID, double PtCB, double Eta, double ePtMS, double ePtID);
  /* Main function */
  void Event();

  double Smearing(std::string DetType, std::string VarType);
  double Combine(double SmearMS,double SmearID);
  double pTMS();
  double pTID();
  double pTCB();
  double Eta();
  int DetRegion();

 private:
  TRandom3* gRand;
  double ptms, ptid, ptcb, eptid, eptms, eta;
  double smearMS,smearID,smearCB;
  std::string detType;
  std::string varType;
  int detRegion;
  double GeV;
  double g1,g2,g3,g4;
  double wMS,wID;
  bool useScale;
};
#endif
