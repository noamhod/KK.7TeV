/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define kinematics_cxx
#include "kinematics.C"

#ifndef SELECTION_H
#define SELECTION_H

class selection : public kinematics
{
public:
	utilities* m_util;
	
	bool   b_print;
	
	TMapsd* m_cutFlowMap;
	TMapds* m_cutFlowOrdered;

public:
	selection();
	~selection();
	
	void sinitialize();
	void sfinalize();

	void initSelectionCuts(TMapsd* cutFlowMap, TMapds* cutFlowOrdered); // called by analysis.C
	
	bool pTCut(           double pTCutVal,           TLorentzVector* pa, TLorentzVector* pb );
	bool etaCut(          double etaCutVal,          TLorentzVector* pa, TLorentzVector* pb );
	bool cosThetaDimuCut( double cosThetaDimuCutVal, TLorentzVector* pa, TLorentzVector* pb );
	bool imassCut(        double imassCutVal,        TLorentzVector* pa, TLorentzVector* pb );

	bool d0Cut(          double d0CutVal, double d0a, double d0b );
	bool z0Cut(          double z0CutVal, double z0a, double z0b );
	bool oppositeCharge( double ca, double cb );

	void buildMuonPairMap(	TMapii& mupair,
							double ca, int ia,
							double cb, int ib);

	void buildMuonPairMap(	TMapii& mupair,
							TLorentzVector* pa, double ca, double d0a, double z0a, int ia,
							TLorentzVector* pb, double cb, double d0b, double z0b, int ib );

	bool removeOverlaps(	TMapii& mupair, int ia, int ib );
	void findBestMuonPair(	TMapii& mupair, int& ia, int& ib);

private:

};
#endif

