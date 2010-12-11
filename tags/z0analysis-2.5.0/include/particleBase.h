/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef PARTICLEBASE_H
#define PARTICLEBASE_H

class particleBase : public physics
{
	public:
		// pointers
		physics* physPtr;
		
		TLorentzVector* pVec;
		TVector*        qVec;
		TVector3*       pvVec;

		double prtE;
		double prtPx;
		double prtPy;
		double prtPz;
		double prtM;
		double prtCh;
		double prtPt;
		double prtEta;
		double prtTheta;
		double prtPhi;
		double prtD0;
		double prtZ0;
		double prtQOP;
				
		unsigned short prtAllauthor;
		int prtAuthor;
		
	public:
		particleBase();
		virtual ~particleBase();
	
		virtual int  getNParticles() = 0;
		virtual void setParticle(int index) = 0;

		void setPvec();
		void setQvec();
		void setVertex();

};
#endif

