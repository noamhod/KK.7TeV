/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef fit_cxx
#include "fit.h"

fit::fit()
{
	finitialize();
}

fit::~fit()
{
	ffinalize();
}

void fit::finitialize()
{
	m_fitROOT = new fitROOT();
	m_fitMinuit = new fitMinuit( xVecPtr );
	m_fitRooFit = new fitRooFit( xVecPtr );
	
	xVecPtr->clear();
}

void fit::ffinalize()
{

}

void fit::fillXvec(double x)
{
	//if(x>XMIN  &&  x<XMAX)
	//{
		xVecPtr->push_back(x);
	//}
}

void fit::minimize(bool signal_only, TH1D* h, double* yields, TDirectory* tdir)
{
	if(tdir!=NULL) tdir->cd();

	cout << "\n$$$$$$$$$$$$$$ start ROOT binned fit $$$$$$$$$$$$$$" << endl;
	m_fitROOT->minimize(signal_only, h, yields);
	//cout << "\n$$$$$$$$$$$$$$ start TMinuit unbinned fit $$$$$$$$$$$$$$" << endl;
	//m_fitMinuit->minimize(signal_only, h, yields);
	cout << "\n$$$$$$$$$$$$$$ start RooFit unbinned fit $$$$$$$$$$$$$$" << endl;
	m_fitRooFit->minimize(signal_only, h, yields);
}

#endif

