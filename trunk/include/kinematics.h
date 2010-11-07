/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef KINEMATICS_H
#define KINEMATICS_H

class kinematics
{
	public:
		// utilities
		TLorentzVector m_pTmp;
		
	public:
		kinematics();
		~kinematics();
		
		float pT(   TLorentzVector* p );
		float pT(   float qOp, float theta);
		float eta(  TLorentzVector* p );
		float pAbs( TLorentzVector* p );
		float y(    TLorentzVector* p );

		float cosThetaDimu(         TLorentzVector* pa, TLorentzVector* pb );
		float dR(                   TLorentzVector* pa, TLorentzVector* pb );
		float imass(                TLorentzVector* pa, TLorentzVector* pb );
		float QT(                   TLorentzVector* pa, TLorentzVector* pb );
		float ySystem(              TLorentzVector* pa, TLorentzVector* pb );
		float cosThetaCollinsSoper( TLorentzVector* pa, float ca,
		TLorentzVector* pb, float cb );

	private:
		
};
#endif

