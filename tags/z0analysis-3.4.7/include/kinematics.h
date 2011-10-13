/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

// #define SmearingClass_cxx
// #include "SmearingClass.h"


#ifndef KINEMATICS_H
#define KINEMATICS_H

class kinematics
{
	public:
		
		
	public:
		kinematics();
		~kinematics();
		
		static kinematics* getInstance();
		
		inline float pT(   TLorentzVector* p );
		inline float pT(   float qOp, float theta);
		inline float eta(  TLorentzVector* p );
		inline float pAbs( TLorentzVector* p );
		inline float y(    TLorentzVector* p );

		inline TVector3 systemBoostVector( TLorentzVector* pa, TLorentzVector* pb );
		inline TLorentzVector* Boost(      TLorentzVector* pBoost, TLorentzVector* p );
		inline TLorentzVector* Boost(      TLorentzVector* pa, TLorentzVector* pb, TLorentzVector* p );
		inline float chi(                  TLorentzVector* pa, TLorentzVector* pb );
		inline float yStar(                TLorentzVector* pa, TLorentzVector* pb );
		inline float yB(                   TLorentzVector* pa, TLorentzVector* pb );
		inline float cosThetaDimu(         TLorentzVector* pa, TLorentzVector* pb );
		inline float dR(                   TLorentzVector* pa, TLorentzVector* pb );
		inline float imass(                TLorentzVector* pa, TLorentzVector* pb );
		inline float QT(                   TLorentzVector* pa, TLorentzVector* pb );
		inline float ySystem(              TLorentzVector* pa, TLorentzVector* pb );
		inline float magBetaSystem(        TLorentzVector* pa, TLorentzVector* pb);
		inline float betaiSystem(          TLorentzVector* pa, TLorentzVector* pb, int i);
		inline float betaTSystem(          TLorentzVector* pa, TLorentzVector* pb);
		inline float magBetaSystem(        float pa, float pb, float ea, float eb);
		inline float cosThetaCollinsSoper( TLorentzVector* pa, float ca,
										   TLorentzVector* pb, float cb );
		inline float cosThetaBoost( TLorentzVector* pa, float ca,
									TLorentzVector* pb, float cb );

	private:
		TLorentzVector m_pTmp;
		static kinematics* theInstance;
		
};
#endif

