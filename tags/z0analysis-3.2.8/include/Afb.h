/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef AFB_H
#define AFB_H

class Afb
{
	public:
		TMultimapff* m_mmap_Afb_CS; // holds: mHat=key, cos(theta)_CS=val
		TMultimapff* m_mmap_Afb_HE; // holds: mHat=key, cos(theta)_HE=val
		float mHat;
		float cosThCollinsSoper;
		float cosThBoost;
	
	public:
		Afb();
		~Afb();

		void fillAfbMap(float mhat, float cosThCS, float cosThHE);
		void calculateAfb(TH1D* h);
		
	private:
};
#endif


