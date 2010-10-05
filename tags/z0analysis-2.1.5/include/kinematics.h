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
		
		void kinitialize();
		void kfinalize();
		
		double pT(   TLorentzVector* p );
		double eta(  TLorentzVector* p );
		double pAbs( TLorentzVector* p );
		double y(    TLorentzVector* p );

		double cosThetaDimu(         TLorentzVector* pa, TLorentzVector* pb );
		double dR(                   TLorentzVector* pa, TLorentzVector* pb );
		double imass(                TLorentzVector* pa, TLorentzVector* pb );
		double QT(                   TLorentzVector* pa, TLorentzVector* pb );
		double ySystem(              TLorentzVector* pa, TLorentzVector* pb );
		double cosThetaCollinsSoper( TLorentzVector* pa, double ca,
		TLorentzVector* pb, double cb );

	private:
		
};
#endif

