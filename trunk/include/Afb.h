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
		TMultimapff* m_mmap_Afb; // holds: mHat=key, cos(theta)_CS=val
		ofstream*    file;
		TTree*       m_Afb_tree;
		float mHat;
		float cosTh;
	
	public:
		Afb();
		~Afb();

		void fillAfbMap(float mHat, float cosTh);
		void calculateAfb(TH1D* h, TDirectory* tdir);
		
	private:
};
#endif


