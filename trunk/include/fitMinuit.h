/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

using namespace fitparameters;

#ifndef FITMINUIT_H
#define FITMINUIT_H

vector<double>* m_xVecPtr;

TMinuit* minuit;

class fitMinuit
{
	public:
		TF1* fitFCN;
		TF1* guess;
		TF1* fScaled;

	public:
		fitMinuit();
		fitMinuit(vector<double>* x);
		~fitMinuit();

		void minimize(bool signal_only, TH1D* h, double* yields);
		
	private:
		
};
#endif

