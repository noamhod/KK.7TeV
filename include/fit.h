/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#define fitParameters_cxx
#include "fitParameters.C"

#define fitFunctions_cxx
#include "fitFunctions.C"

#define fitROOT_cxx
#include "fitROOT.C"

#define fitMinuit_cxx
#include "fitMinuit.C"

#define fitRooFit_cxx
#include "fitRooFit.C"

#ifndef FIT_H
#define FIT_H

bool docout = true;
vector<double>* xVecPtr = new vector<double>();

class fit
{
	public:
		TF1* m_fGuess;
		TF1* m_fFitted;
		
		fitROOT*   m_fitROOT;
		fitMinuit* m_fitMinuit;
		fitRooFit* m_fitRooFit;
	
	public:
		fit();
		~fit();

		void finitialize();
		void ffinalize();

		void fillXvec(double x);
		
		void minimize(bool signal_only, TH1D* h, double* yields, TDirectory* tdir);
		
	private:
		
};
#endif

