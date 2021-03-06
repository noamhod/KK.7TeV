/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ROOFBFALSEIDENTIFYCS
#define ROOFBFALSEIDENTIFYCS

#include "TH1D.h"
#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class RooFBfalseIdentifyCS : public RooAbsPdf {
public:
  RooFBfalseIdentifyCS() {} ; 
  RooFBfalseIdentifyCS(const char *name, const char *title,
					   RooAbsReal& _costheta,
					   RooAbsReal& _yQ,
					   RooAbsReal& _A0,
					   RooAbsReal& _A4,
					   TH1D&       _hPyQ);
  RooFBfalseIdentifyCS(const RooFBfalseIdentifyCS& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooFBfalseIdentifyCS(*this,newname); }
  inline virtual ~RooFBfalseIdentifyCS() { }

protected:

  RooRealProxy costheta ;
  RooRealProxy yQ ;
  RooRealProxy A0 ;
  RooRealProxy A4 ;
  TH1D*        hPyQ;
  Double_t evaluate() const ;

private:
  ClassDef(RooFBfalseIdentifyCS,1) // Your description goes here...
};
 
#endif
