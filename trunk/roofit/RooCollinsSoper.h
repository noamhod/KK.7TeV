/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ROOCOLLINSSOPER
#define ROOCOLLINSSOPER

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class RooCollinsSoper : public RooAbsPdf {
public:
  RooCollinsSoper() {} ; 
  RooCollinsSoper(const char *name, const char *title,
	RooAbsReal& _costheta,
	RooAbsReal& _A0,
	RooAbsReal& _A4);
  RooCollinsSoper(const RooCollinsSoper& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooCollinsSoper(*this,newname); }
  inline virtual ~RooCollinsSoper() { }

protected:

  RooRealProxy costheta ;
  RooRealProxy A0 ;
  RooRealProxy A4 ;
  
  Double_t evaluate() const ;

private:

  ClassDef(RooCollinsSoper,1) // Your description goes here...
};
 
#endif
