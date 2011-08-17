 /***************************************************************************** 
  * Project: RooFit                                                           * 
  *                                                                           * 
  * This code was autogenerated by RooClassFactory                            * 
  *****************************************************************************/ 

 // Your description goes here... 

 #include "Riostream.h" 
 #include "TROOT.h"
 #include "TMath.h"
 #include "RooAngular.h" 
 #include "RooAbsReal.h" 
 #include "RooAbsCategory.h" 

 ClassImp(RooAngular) 

 RooAngular::RooAngular(const char *name, const char *title, 
                        RooAbsReal& _costheta,
                        RooAbsReal& _A,
                        RooAbsReal& _B) :
   RooAbsPdf(name,title), 
   costheta("costheta","costheta",this,_costheta),
   A("A","A",this,_A),
   B("B","B",this,_B)
 { 
 } 


 RooAngular::RooAngular(const RooAngular& other, const char* name) :  
   RooAbsPdf(other,name), 
   costheta("costheta",this,other.costheta),
   A("A",this,other.A),
   B("B",this,other.B)
 { 
 } 



 Double_t RooAngular::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE
   Double_t dflt = 1.e-30;

   //Double_t Afb = (A>0.) ? (3.*B)/(8.*A) : 0.;
   //Double_t pdf = (A>0.  &&  (Afb>=-1. && Afb<=+1.)) ? A*(1. + costheta*costheta) + B*costheta : dflt;
   
   Double_t pdf = (A!=0.) ? (8./(3.*A))*(A*(1.+costheta*costheta)+B*costheta) : dflt;
   return (pdf>0.) ? pdf : dflt;
   
   //std::cout << "in RooAngular::evaluate()  ->   A=" << A << ", B=" << B << ", Afb=" << Afb << endl;
   //std::cout << "in RooAngular::evaluate()  ->   pdf returning 1." << endl;
   //return 1.;
 } 



