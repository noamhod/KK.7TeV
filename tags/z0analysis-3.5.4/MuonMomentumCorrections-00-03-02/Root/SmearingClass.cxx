/////////////////////////////////////////////////////////////////////////////
//           SmearingClass.cxx -- ATLAS Experiment Software               //
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
#include <cstdlib>
#include "MuonMomentumCorrections/SmearingClass.h"

SmearingClass::SmearingClass(std::string Algo,
			     std::string SmearType,
			     std::string Dir) {
  
  Initialize(Algo,SmearType,Dir);
}


SmearingClass::SmearingClass(const SmearingClass& _rhs){
  
  Initialize(_rhs.Algorithm,_rhs.Tsmear,_rhs.Fdir);
}


SmearingClass::~SmearingClass(){
  Finalize();
}


void SmearingClass::Initialize(std::string algo,
			       std::string smearType,
			       std::string dir) {
  detType="";
  GeV=1000;
  pTmax=100000000;
  gRand = new TRandom3();
  gRand->SetSeed(0);
  useTan2=true;
  useScale=false;
  ptms=0;
  ptid=0;
  ptcb=0;
  eta=0;
  
  SetAlgoSmearDir(algo,smearType,dir);
}


void SmearingClass::Finalize(){
  gRand->Delete();
  scale_CB.clear();
  scaleSyst_CB.clear();
  p1_ID.clear();
  p2_ID.clear();
  p2_ID_TAN.clear();
  p1_MS.clear();
  p2_MS.clear();
  E_p1_ID.clear();
  E_p2_ID.clear();
  E_p2_ID_TAN.clear();
  E_p1_MS.clear();
  E_p2_MS.clear();
  S_p1_ID.clear();
  S_p2_ID.clear();
  S_p2_ID_TAN.clear();
  S_p1_MS.clear();
  S_p2_MS.clear();
  MC_p1_ID.clear();
  MC_p2_ID.clear();
  MC_p2_ID_TAN.clear();
  MC_p0_MS.clear();
  MC_p1_MS.clear();
  MC_p2_MS.clear();
  CorrMatC0.clear();
  CorrMatC1.clear();
  CorrMatC2.clear();
  CorrMatC3.clear();
  CorrMatC4.clear();
  CorrMatC5.clear();
  CorrMatTanC0.clear();
  CorrMatTanC1.clear();
  CorrMatTanC2.clear();
  CorrMatTanC3.clear();
  CorrMatTanC4.clear();
  CorrMatTanC5.clear();
  InValues.clear();
}

void SmearingClass::Clean(){
  
  scale_CB.clear();
  scaleSyst_CB.clear();
  p1_ID.clear();
  p2_ID.clear();
  p2_ID_TAN.clear();
  p1_MS.clear();
  p2_MS.clear();
  E_p1_ID.clear();
  E_p2_ID.clear();
  E_p2_ID_TAN.clear();
  E_p1_MS.clear();
  E_p2_MS.clear();
  S_p1_ID.clear();
  S_p2_ID.clear();
  S_p2_ID_TAN.clear();
  S_p1_MS.clear();
  S_p2_MS.clear();
  MC_p1_ID.clear();
  MC_p2_ID.clear();
  MC_p2_ID_TAN.clear();
  MC_p0_MS.clear();
  MC_p1_MS.clear();
  MC_p2_MS.clear();
  CorrMatC0.clear();
  CorrMatC1.clear();
  CorrMatC2.clear();
  CorrMatC3.clear();
  CorrMatC4.clear();
  CorrMatC5.clear();
  CorrMatTanC0.clear();
  CorrMatTanC1.clear();
  CorrMatTanC2.clear();
  CorrMatTanC3.clear();
  CorrMatTanC4.clear();
  CorrMatTanC5.clear();
  InValues.clear();
 
}

void SmearingClass::SetAlgoSmearDir(std::string Algo,
				    std::string SmearType,
				    std::string Dir){
  /*Checking algorithm*/
  if(Algo=="muid" || Algo=="staco"){
    Algorithm=Algo;
    std::cout<<"SmearingClass INFO:: using " << Algorithm << " Algorithm "<<std::endl;
  }
  else{
    std::cout<<"SmearingClass ERROR:: wrong Algorithm in input "<<Algo<<std::endl;
    std::cout<<"                      possible values are: muid or staco "<<std::endl;
    return;
  }
  
  /*Checking smearing type*/
  if(SmearType=="pT" || SmearType=="q_pT"){
    Tsmear=SmearType;
    std::cout<<"SmearingClass INFO:: using " << Tsmear << " Smearing "<<std::endl;
  }
  else{
    std::cout<<"SmearingClass ERROR:: wrong Smear Type in input "<<SmearType<<std::endl;
    std::cout<<"                      possible values are: pT ot q_pT "<<std::endl;
    return;
  }
  
  /*Checking path*/
  if(Dir!=""){
    Fdir=Dir;
    std::cout<<"SmearingClass INFO:: Using user defined path!"<<std::endl;
    std::cout<<"                     "<<Fdir<<std::endl;
  }
  else{
    char *tmparea=getenv("TestArea");
    std::string testarea="";
    if(tmparea!=NULL){
      testarea=tmparea;
    }
    Fdir=testarea+"/InstallArea/share/";
    std::cout<<"SmearingClass INFO:: Using default path!"<<std::endl;
    std::cout<<"                     "<<Fdir<<std::endl;
  }

  /*Filling Corrections Values*/
  FillValues(Algorithm);
  
}

void SmearingClass::FillValues(std::string Algo){
  /* Choose MuID or Staco Algorithm Values */
  
  Clean();
  double tmpval;
  int i=0;
  std::string tmpname;
  std::string scale_val = Fdir+"scale_values_"+Algo+".dat";
  std::string data_val  = Fdir+"data_values_"+Algo+".dat";
  std::string mc_val    = Fdir+"mc_values_"+Algo+".dat";
  std::string corr_val  = Fdir+"corr_values_"+Algo+".dat";
  
  /* filling scale vectors*/
  InValues.open(scale_val.c_str());
  i=0;
  if(!InValues.good()){
    std::cout<<"SmearingClass ERROR:: File "<<scale_val<<" NOT FOUND!!"<<std::endl;
    std::cout<<"                      Please provide a correct path!"<<std::endl;
    return;
  }
  else{
    while(InValues.good() && i<4){
      tmpval=0;
      if(i==0){
	getline(InValues,tmpname);
      }
      InValues>>tmpval;
      scale_CB.push_back(tmpval);
      InValues>>tmpval;
      scaleSyst_CB.push_back(tmpval);
      i++;
    }
  }
  InValues.close();
  InValues.clear();
  
  /* filling data vectors*/
  InValues.open(data_val.c_str());
  i=0;
  if(!InValues.good()){
    std::cout<<"SmearingClass ERROR:: File "<<data_val<<" NOT FOUND!!"<<std::endl;
    std::cout<<"                      Please provide a correct path!"<<std::endl;
    return;
  }
  else{
    while(InValues.good()&& i<4){
      /*main values*/
      tmpval=0;
      if(i==0){
	getline(InValues,tmpname);
      }
      InValues>>tmpval;
      p1_ID.push_back(tmpval);
      InValues>>tmpval;
      p2_ID.push_back(tmpval);
      InValues>>tmpval;
      p2_ID_TAN.push_back(tmpval);
      InValues>>tmpval;
      p1_MS.push_back(tmpval);
      InValues>>tmpval;
      p2_MS.push_back(tmpval);
      /*errors*/
      InValues>>tmpval;
      E_p1_ID.push_back(tmpval);
      InValues>>tmpval;
      E_p2_ID.push_back(tmpval);
      InValues>>tmpval;
      E_p2_ID_TAN.push_back(tmpval);
      InValues>>tmpval;
      E_p1_MS.push_back(tmpval);
      InValues>>tmpval;
      E_p2_MS.push_back(tmpval);
      /*systematic*/
      InValues>>tmpval;
      S_p1_ID.push_back(tmpval);
      InValues>>tmpval;
      S_p2_ID.push_back(tmpval);
      InValues>>tmpval;
      S_p2_ID_TAN.push_back(tmpval);
      InValues>>tmpval;
      S_p1_MS.push_back(tmpval);
      InValues>>tmpval;
      S_p2_MS.push_back(tmpval);
    }
  }
  InValues.close();
  InValues.clear();
  
  /* filling mc vectors*/
  InValues.open(mc_val.c_str());
  i=0;
  if(!InValues.good()){
    std::cout<<"SmearingClass ERROR:: File "<<mc_val<<" NOT FOUND!!"<<std::endl;
    std::cout<<"                      Please provide a correct path!"<<std::endl;
    return;
  }
  else{
    while(InValues.good() && i<4){
      tmpval=0;
      if(i==0){
	getline(InValues,tmpname);
      }
      InValues>>tmpval;
      MC_p1_ID.push_back(tmpval);
      InValues>>tmpval;
      MC_p2_ID.push_back(tmpval);
      InValues>>tmpval;
      MC_p2_ID_TAN.push_back(tmpval);
      InValues>>tmpval;
      MC_p0_MS.push_back(tmpval);
      InValues>>tmpval;
      MC_p1_MS.push_back(tmpval);
      InValues>>tmpval;
      MC_p2_MS.push_back(tmpval);
    }
  }
  InValues.close();
  InValues.clear();
  
  /* filling correlation vectors*/
  InValues.open(corr_val.c_str());
  i=0;
  if(!InValues.good()){
    std::cout<<"SmearingClass ERROR:: File "<<corr_val<<" NOT FOUND!!"<<std::endl;
    std::cout<<"                      Please provide a correct path!"<<std::endl;
    return;
  }
  else{
    while(InValues.good() && i<4){
      tmpval=0;
      if(i==0){
	getline(InValues,tmpname);
      }
      InValues>>tmpval;
      CorrMatC0.push_back(tmpval);
      CorrMatTanC0.push_back(tmpval);
      
      InValues>>tmpval;
      CorrMatC1.push_back(tmpval);
      CorrMatTanC1.push_back(tmpval);
      
      InValues>>tmpval;
      CorrMatC2.push_back(tmpval);
      CorrMatTanC2.push_back(tmpval);
    
      InValues>>tmpval;
      CorrMatC3.push_back(tmpval);
      CorrMatTanC3.push_back(tmpval);
    
      InValues>>tmpval;
      CorrMatC4.push_back(tmpval);
      CorrMatTanC4.push_back(tmpval);
      
      InValues>>tmpval;
      CorrMatC5.push_back(tmpval);
      CorrMatTanC5.push_back(tmpval);
    }
  }
  InValues.close();
  InValues.clear();
  
}


void SmearingClass::PrintValues(){
  
  std::cout<<"SmearingClass INFO:: Checking if all variables are filled ... "<<std::endl;
  for(UInt_t i=0; i<scale_CB.size(); i++){
    std::cout<<std::endl;
    
    std::cout<<"  scale_CB["<<i<<"] "<<scale_CB[i]<<std::endl;
    std::cout<<"  scaleSyst_CB["<<i<<"] "<< scaleSyst_CB[i]<<std::endl;
    
    std::cout<<std::endl;
    
    std::cout<<"  p1_ID["<<i<<"] "<<p1_ID[i]<<std::endl;
    std::cout<<"  p2_ID["<<i<<"] "<<p2_ID[i]<<std::endl;
    std::cout<<"  p2_ID_TAN["<<i<<"] "<<p2_ID_TAN[i]<<std::endl;
    std::cout<<"  p1_MS["<<i<<"] " <<p1_MS[i]<<std::endl;
    std::cout<<"  p2_MS["<<i<<"] " <<p2_MS[i]<<std::endl;
    
    std::cout<<std::endl;
    
    std::cout<<"  E_p1_ID["<<i<<"] "<<E_p1_ID[i]<<std::endl;
    std::cout<<"  E_p2_ID["<<i<<"] "<<E_p2_ID[i]<<std::endl;
    std::cout<<"  E_p2_ID_TAN["<<i<<"] "<<E_p2_ID_TAN[i]<<std::endl;
    std::cout<<"  E_p1_MS["<<i<<"] "<<E_p1_MS[i]<<std::endl;
    std::cout<<"  E_p2_MS["<<i<<"] "<<E_p2_MS[i]<<std::endl;
    
    std::cout<<std::endl;
    
    std::cout<<"  S_p1_ID["<<i<<"] "<<S_p1_ID[i]<<std::endl;
    std::cout<<"  S_p2_ID["<<i<<"] "<<S_p2_ID[i]<<std::endl;
    std::cout<<"  S_p2_ID_TAN["<<i<<"] "<<S_p2_ID_TAN[i]<<std::endl;
    std::cout<<"  S_p1_MS["<<i<<"] "<<S_p1_MS[i]<<std::endl;
    std::cout<<"  S_p2_MS["<<i<<"] "<<S_p2_MS[i]<<std::endl;
    
    std::cout<<std::endl;
    
    std::cout<<"  MC_p1_ID["<<i<<"] "<<MC_p1_ID[i]<<std::endl;
    std::cout<<"  MC_p2_ID["<<i<<"] "<<MC_p2_ID[i]<<std::endl;
    std::cout<<"  MC_p2_ID_TAN["<<i<<"] "<<MC_p2_ID_TAN[i] << std::endl;
    std::cout<<"  MC_p0_MS["<<i<<"] "<<MC_p0_MS[i]<<std::endl;
    std::cout<<"  MC_p1_MS["<<i<<"] "<<MC_p1_MS[i]<<std::endl;
    std::cout<<"  MC_p2_MS["<<i<<"] "<<MC_p2_MS[i]<<std::endl;
    
    std::cout<<std::endl;
    
    std::cout<<"  CorrMatC0["<<i<<"] "<<CorrMatC0[i]<<std::endl;
    std::cout<<"  CorrMatC1["<<i<<"] "<<CorrMatC1[i]<<std::endl;
    std::cout<<"  CorrMatC2["<<i<<"] "<<CorrMatC2[i]<<std::endl;
    std::cout<<"  CorrMatC3["<<i<<"] "<<CorrMatC3[i]<<std::endl;
    std::cout<<"  CorrMatC4["<<i<<"] "<<CorrMatC4[i]<<std::endl;
    std::cout<<"  CorrMatC5["<<i<<"] "<<CorrMatC5[i]<<std::endl;

    std::cout<<""<<std::endl;
    
    std::cout<<"  CorrMatTanC0["<<i<<"] "<<CorrMatTanC0[i]<<std::endl;
    std::cout<<"  CorrMatTanC1["<<i<<"] "<<CorrMatTanC1[i]<<std::endl;
    std::cout<<"  CorrMatTanC2["<<i<<"] "<<CorrMatTanC2[i]<<std::endl;
    std::cout<<"  CorrMatTanC3["<<i<<"] "<<CorrMatTanC3[i]<<std::endl;
    std::cout<<"  CorrMatTanC4["<<i<<"] "<<CorrMatTanC4[i]<<std::endl;
    std::cout<<"  CorrMatTanC5["<<i<<"] "<<CorrMatTanC5[i]<<std::endl;

  }
}


void SmearingClass::SetSeed(int seed) {
  gRand->SetSeed(seed);
}


void SmearingClass::SetSeed(int evtnum,
			    int muon_index,
			    int offset) {
  
  gRand->SetSeed(offset + evtnum + muon_index*100);
}


void SmearingClass::UseTan2(bool U) {
  /* use pT/tan(theta)^2 parameterization for CSC region */ 
  
  useTan2=U;
}


void SmearingClass::UseGeV() {
  /* if input momenta are in GeV */
  
  GeV=1;
}


void SmearingClass::UseScale(bool applyScale) {
  /* also use momentum scale, set as default */
  
  useScale=applyScale;
}


void SmearingClass::Event(double Pt,
			  double Eta,
			  std::string DetType) {
  /* MS or ID smearing only. DetType="MS","ID"*/
  
  ptms=0;
  ptid=0;
  ptcb=0;
  
  if (DetType=="MS") { ptms = Pt; }
  else if (DetType=="ID") { ptid = Pt; }
  else std::cout<<"SmearingClass ERROR: wrong DetType in input "<<DetType<<std::endl;
  
  eta=Eta;   
  detType=DetType;
  Event();
}


void SmearingClass::Event(double PtMS,
			  double PtID,
			  double PtCB,
			  double Eta) {
  /* For full MS ID and CB smearing */
  
  detType="All";
  ptms=PtMS;
  ptid=PtID;
  ptcb=PtCB;
  eta=Eta;
  Event();
}


void SmearingClass::Event() {
  
  smearMS=0;
  smearID=0;
  smearCB=0;

  /* Detector Region */
  if (fabs(eta)<1.05) { detRegion=0; }
  else if (fabs(eta)<1.7) { detRegion=1; }
  else if (fabs(eta)<2.0) { detRegion=2; }
  else if (fabs(eta)<2.7) { detRegion=3; }
  else { detRegion=-1; }
  
  g1 = gRand->Gaus(0,1); 
  g2 = gRand->Gaus(0,1);
  g3 = gRand->Gaus(0,1);
  g4 = gRand->Gaus(0,1);
  
  /** Definition: pT'=pT(1+smear) **/
  smearMS=Smearing("MS");
  smearID=Smearing("ID");
  if (detType=="All") { smearCB=Combine(smearMS,smearID); }
  ErrorMatrix();
}


double SmearingClass::Smearing(std::string DetType) {
  
  if (detRegion<0 || detRegion>3) { 
    return 0; 
  }
  
  if (DetType=="MS"){
    return (p1_MS[detRegion]*g1+p2_MS[detRegion]*g2*ptms/GeV);
  }
  else if(DetType=="ID"){
    if (useTan2&&detRegion==3){
      return (p1_ID[detRegion]*g3+p2_ID_TAN[detRegion]*g4*ptid/GeV*sinh(eta)*sinh(eta));
    }
    else{
      return (p1_ID[detRegion]*g3+p2_ID[detRegion]*g4*ptid/GeV);
    }
  }
  else{ 
    std::cout<<"SmearingClass ERROR:: DetType not defined "<<DetType<<std::endl;
  }
  return 0;
}


double SmearingClass::Combine(double SmearMS, 
			      double SmearID) {

  /** do the average with the EXPECTED resolutions **/
  
  if (detRegion<0||detRegion>3) {return 0; }
  if (ptcb==0) { 
    std::cout<<"SmearingClass WARNING:: ptcb==0"<<std::endl;
    return 0; 
  }
   
  double SigmaMS=pow(
		     pow(MC_p0_MS[detRegion]/ptcb*GeV,2)+
		     pow(MC_p1_MS[detRegion],2)+
		     pow(MC_p2_MS[detRegion]*ptcb/GeV,2),0.5);
  
  double SigmaID=pow(
		     pow(MC_p1_ID[detRegion],2)+
		     pow(MC_p2_ID[detRegion]*ptcb/GeV,2),0.5);
  
  if (detRegion==3&&useTan2) {
    SigmaID=pow(
		pow(MC_p1_ID[detRegion],2)+
		pow(MC_p2_ID_TAN[detRegion]*ptcb/GeV*sinh(eta)*sinh(eta),2),0.5);
  }
  
  wMS=1./SigmaMS/SigmaMS;
  wID=1./SigmaID/SigmaID;
  return (SmearMS*wMS+SmearID*wID)/(wMS+wID);
}

double SmearingClass::Combine2(double SmearMS, 
			       double SmearID) {
  
  /** do the average with the EXPECTED resolutions **/
  
  if (detRegion<0||detRegion>3) {return 0; }
  if (ptcb==0) { 
    std::cout<<"SmearingClass WARNING:: ptcb==0"<<std::endl;
    return 0; 
  }
  
  double SmearCB=0;
  double R=1;
  
  if (fabs(ptcb-ptms)>0&&fabs(ptcb-ptms)>fabs(ptcb-ptid)) {
    R=(ptid-ptcb)/(ptcb-ptms);//R~wID/wMS
    double rplus=1+R;
    if (rplus!=0) SmearCB=(SmearID+R*SmearMS)/rplus;    
    else SmearCB=Combine(SmearMS,SmearID);
  }
  else if (fabs(ptcb-ptid)>0&&fabs(ptcb-ptms)<fabs(ptcb-ptid)){
    R=(ptms-ptcb)/(ptid-ptms);//R~wMS/wID
    double rplus=1+R;
    if (rplus!=0) SmearCB=(SmearMS+R*SmearID)/rplus;    
    else SmearCB=Combine(SmearMS,SmearID);
  } else {
    SmearCB=Combine(SmearMS,SmearID);
  }
  
  if (R<0){
    std::cout<<"SmearingClass WARNING:: R<0"<<std::endl;
    SmearCB=Combine(SmearMS,SmearID); 
  }
  
  return SmearCB;
}



void SmearingClass::ErrorMatrix() {
  
  vms=0;
  vid=0;
  corr=0;
  
  if (detRegion<0||detRegion>3) return;

  if (!useTan2||detRegion!=3) {
    double s1=pow(E_p1_MS[detRegion]*E_p1_MS[detRegion]+S_p1_MS[detRegion]*S_p1_MS[detRegion],0.5);
    double s2=pow(E_p2_MS[detRegion]*E_p2_MS[detRegion]+S_p2_MS[detRegion]*S_p2_MS[detRegion],0.5);
    double s3=pow(E_p1_ID[detRegion]*E_p1_ID[detRegion]+S_p1_ID[detRegion]*S_p1_ID[detRegion],0.5);
    double s4=pow(E_p2_ID[detRegion]*E_p2_ID[detRegion]+S_p2_ID[detRegion]*S_p2_ID[detRegion],0.5);
    
    vms=g1*g1*s1*s1+
      g2*g2*s2*s2*ptms/GeV*ptms/GeV+
      2.0*g1*g2*ptms/GeV*s1*s2*CorrMatC0[detRegion];
    
    vms=pow(fabs(vms),0.5);
    
    vid=g3*g3*s3*s3+g4*g4*s4*s4*ptid/GeV*ptid/GeV+2.0*g3*g4*s3*s4*ptid/GeV*CorrMatC5[detRegion];
    
    vid=pow(fabs(vid),0.5);
    
    if (vms*vid!=0) {
      corr=(g1*s1*(g3*s3*CorrMatC1[detRegion]+g4*s4*ptid/GeV*CorrMatC2[detRegion])+
	    g2*s2*ptms/GeV*(g3*s3*CorrMatC3[detRegion]+g4*s4*ptid/GeV*CorrMatC4[detRegion]))/vms/vid;
    }
  }
  else {
    double s1=pow(E_p1_MS[detRegion]*E_p1_MS[detRegion]+S_p1_MS[detRegion]*S_p1_MS[detRegion],0.5);
    double s2=pow(E_p2_MS[detRegion]*E_p2_MS[detRegion]+S_p2_MS[detRegion]*S_p2_MS[detRegion],0.5);
    double s3=pow(E_p1_ID[detRegion]*E_p1_ID[detRegion]+S_p1_ID[detRegion]*S_p1_ID[detRegion],0.5);
    double s4=pow(E_p2_ID_TAN[detRegion]*E_p2_ID_TAN[detRegion]+S_p2_ID_TAN[detRegion]*S_p2_ID_TAN[detRegion],0.5);
      
    vms=g1*g1*s1*s1+
      g2*g2*s2*s2*ptms/GeV*ptms/GeV+
      2.0*g1*g2*ptms/GeV*s1*s2*CorrMatTanC0[detRegion];
    
    vms=pow(fabs(vms),0.5);
    
    vid=g3*g3*s3*s3+g4*g4*s4*s4*ptid/GeV*ptid/GeV*sinh(eta)*sinh(eta)*sinh(eta)*sinh(eta)
      +2.0*g3*g4*s3*s4*ptid/GeV*sinh(eta)*sinh(eta)*CorrMatTanC5[detRegion];
    
    vid=pow(fabs(vid),0.5);
    
    if (vms*vid!=0) {
      corr=(g1*s1*(g3*s3*CorrMatTanC1[detRegion]+g4*s4*ptid/GeV*sinh(eta)*sinh(eta)*CorrMatTanC2[detRegion])+
	    g2*s2*ptms/GeV*(g3*s3*CorrMatTanC3[detRegion]+g4*s4*ptid/GeV*sinh(eta)*sinh(eta)*CorrMatTanC4[detRegion]))/vms/vid;
    }
  }
}


double SmearingClass::pTMS() {
  /* smeared muon spectrometer pT */
  
  return pTMS(smearMS);
}


double SmearingClass::pTMS(double SmearMS) {
  /* smeared muon spectrometer pT */
  
  if(Tsmear=="pT"){
    return ptms*(1+SmearMS); 
  }
  else if(Tsmear=="q_pT"){
    double tmp=1-SmearMS;
    if(tmp!=0) return fabs(ptms/tmp); 
    else return pTmax;
  }
  return ptms;
}


double SmearingClass::pTID() {
  /* smeared inner detector pT */
  
  return pTID(smearID);
}


double SmearingClass::pTID(double SmearID) {
  /* smeared inner detector pT */
  
  if(Tsmear=="pT"){
    return ptid*(1+SmearID);
  }
  else if(Tsmear=="q_pT"){
    double tmp=1-SmearID;
    if(tmp!=0) return fabs(ptid/tmp);
    else return pTmax;
  }
  return ptid;
}


double SmearingClass::pTCB() {
  /* smeared combined pT*/
  
  return pTCB(smearCB);
}


double SmearingClass::pTCB(double SmearCB) {
  /* smeared combined pT*/
  
  double tmpscale=1;
  if (useScale && detRegion>-1 && detRegion<4){
    tmpscale=scale_CB[detRegion];
  }
  if(Tsmear=="pT"){
    return tmpscale*ptcb*(1+SmearCB);
  }
  else if(Tsmear=="q_pT"){
    double tmp=1-SmearCB;
    if(tmp!=0) return fabs(tmpscale*ptcb/tmp);
    else return pTmax;
  }
  return tmpscale*ptcb;
}


double SmearingClass::ChargeFlip(double Smear){
  
  if(Tsmear=="pT"){
    return 1;
  }
  else if (Tsmear=="q_pT"){
    return Sign(1-Smear);
  }
  return 1;
}


double SmearingClass::ChargeFlipMS(){
  
  return ChargeFlip(smearMS);
}


double SmearingClass::ChargeFlipID(){
  
  return ChargeFlip(smearID);
}


double SmearingClass::ChargeFlipCB(){
  
  return ChargeFlip(smearCB);
}


double SmearingClass::SMS() {
  return smearMS;
}


double SmearingClass::SID() {
  return smearID;
}


double SmearingClass::SCB() {
  return smearCB;
}


double SmearingClass::VMS() {
  /* error smearMS */
  
  return vms;  
}


double SmearingClass::VID() {
  /* error smearID */
  
  return vid;
}


double SmearingClass::Corr() {
  /* correlation between smearMS and smearID */
  
  return corr;
}


void SmearingClass::MSUP(double &PtMS) {
  double SmearMS=smearMS+Sign(smearMS)*vms;
  PtMS=pTMS(SmearMS);
}


void SmearingClass::MSUP(double &PtMS,
			 double &PtID,
			 double &PtCB) {
  
  double SmearMS=smearMS+Sign(smearMS)*vms;
  double SmearID=smearID+Sign(smearMS)*vid*corr;
  
  PtMS=pTMS(SmearMS);
  PtID=pTID(SmearID);
  if (detType=="All") {
    double SmearCB=Combine(SmearMS,SmearID);
    PtCB=pTCB(SmearCB);
  }
}


void SmearingClass::MSLOW(double &PtMS) {
  
  double SmearMS=smearMS-Sign(smearMS)*vms;
  PtMS=pTMS(SmearMS);
}


void SmearingClass::MSLOW(double &PtMS,
			  double &PtID,
			  double &PtCB) {
  
  double SmearMS=smearMS-Sign(smearMS)*vms;
  double SmearID=smearID-Sign(smearMS)*vid*corr;
  
  PtMS=pTMS(SmearMS);
  PtID=pTID(SmearID);
  if (detType=="All") {
    double SmearCB=Combine(SmearMS,SmearID);
    PtCB=pTCB(SmearCB);
  }
}


void SmearingClass::IDUP(double &PtID) {
  
  double SmearID=smearID+Sign(smearID)*vid;
  PtID=pTID(SmearID);
}


void SmearingClass::IDUP(double &PtMS,
			 double &PtID,
			 double &PtCB) {
  
  double SmearMS=smearMS+Sign(smearID)*vms*corr;
  double SmearID=smearID+Sign(smearID)*vid;
  
  PtMS=pTMS(SmearMS);
  PtID=pTID(SmearID);
  if (detType=="All") {
    double SmearCB=Combine(SmearMS,SmearID);
    PtCB=pTCB(SmearCB);
  }
}


void SmearingClass::IDLOW(double &PtID) {
  
  double SmearID=smearID-Sign(smearID)*vid;
  PtID=pTID(SmearID);
}


void SmearingClass::IDLOW(double &PtMS,
			  double &PtID,
			  double &PtCB) {
  
  double SmearMS=smearMS-Sign(smearID)*vms*corr;
  double SmearID=smearID-Sign(smearID)*vid;
  
  PtMS=pTMS(SmearMS);
  PtID=pTID(SmearID);
  if (detType=="All") {
    double SmearCB=Combine(SmearMS,SmearID);
    PtCB=pTCB(SmearCB);
  }
}


void SmearingClass::PTVar(double &Pt,
			  std::string fun) {
  
  if (fun=="IDUP") { IDUP(Pt); }
  else if (fun=="IDLOW") { IDLOW(Pt); }
  else if (fun=="MSUP") { MSUP(Pt); }
  else if (fun=="MSLOW") { MSLOW(Pt); }
}


void SmearingClass::PTVar(double &PtMS,
			  double &PtID,
			  double &PtCB,
			  std::string fun) {
  
  if (fun=="IDUP") { IDUP(PtMS,PtID,PtCB); }
  else if (fun=="IDLOW") { IDLOW(PtMS,PtID,PtCB); }
  else if (fun=="MSUP") { MSUP(PtMS,PtID,PtCB); }
  else if (fun=="MSLOW") { MSLOW(PtMS,PtID,PtCB); }
}


double SmearingClass::Sign(double x){
  
  return (x<0? -1 : 1);
}


double SmearingClass::ptms_orig() {
  return ptms;
}


double SmearingClass::ptid_orig() {
  return ptid;
}


double SmearingClass::ptcb_orig() {
  return ptcb;
}


double SmearingClass::ETA() {
  return eta;
}


int SmearingClass::DetRegion() {
  return detRegion;
}
