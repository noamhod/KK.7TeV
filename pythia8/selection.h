#include "basics.h"

#ifndef SELECTION_H
#define SELECTION_H

TLorentzVector p_tmp;

inline bool selection(TLorentzVector* pa, TLorentzVector* pb)
{
	// pa and pb are in GeV
	if(imass(pa,pb)<60.)                           return false;
	if(fabs(pa->Pt())<25.  || fabs(pb->Pt())<25.)  return false;
	if(fabs(pa->Eta())>2.4 || fabs(pb->Eta())>2.4) return false;
	return true;
}

#endif
