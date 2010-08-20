/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef particleBase_cxx
#include "particleBase.h"

particleBase::particleBase()
{
	pVec  = new TLorentzVector();
	qVec  = new TVector(5);
	pvVec = new TVector3();
}

particleBase::~particleBase()
{
	delete pVec;
	delete qVec;
	delete pvVec;
}

void particleBase::setPvec()
{
	pVec->SetE( prtE );
	pVec->SetPx( prtPx );
	pVec->SetPy( prtPy );
	pVec->SetPz( prtPz );
}

void particleBase::setQvec()
{
	/*
	qVec[0] = prtQOP;
	qVec[1] = prtD0;
	qVec[2] = prtZ0;
	qVec[3] = prtPhi;
	qVec[4] = prtTheta;
	*/
}

void particleBase::setVertex()
{
	pvVec->SetX( prtD0*cos(prtPhi) );
	pvVec->SetY( prtD0*sin(prtPhi) );
	pvVec->SetZ( prtZ0 );
}

#endif

