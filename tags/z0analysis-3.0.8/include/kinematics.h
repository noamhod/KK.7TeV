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
		TLorentzVector m_pTmp;
		
	public:
		kinematics();
		~kinematics();
		
		inline float pT(   TLorentzVector* p );
		inline float pT(   float qOp, float theta);
		inline float eta(  TLorentzVector* p );
		inline float pAbs( TLorentzVector* p );
		inline float y(    TLorentzVector* p );

		inline float cosThetaDimu(         TLorentzVector* pa, TLorentzVector* pb );
		inline float dR(                   TLorentzVector* pa, TLorentzVector* pb );
		inline float imass(                TLorentzVector* pa, TLorentzVector* pb );
		inline float QT(                   TLorentzVector* pa, TLorentzVector* pb );
		inline float ySystem(              TLorentzVector* pa, TLorentzVector* pb );
		inline float cosThetaCollinsSoper( TLorentzVector* pa, float ca,
										   TLorentzVector* pb, float cb );
		inline float cosThetaBoost( TLorentzVector* pa, float ca,
									TLorentzVector* pb, float cb );

	private:
		
};
#endif

