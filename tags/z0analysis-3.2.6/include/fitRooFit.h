/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

using namespace fitparameters;

#ifndef FITROOFIT_H
#define FITROOFIT_H

TTree* m_imassTree;

class fitRooFit
{
	public:
		TF1* fitFCN;
		TF1* guess;
		TF1* fScaled;
		
		double m_imass;
		vector<double>* m_xVecPtr;

	public:
		fitRooFit();
		fitRooFit(vector<double>* x);
		~fitRooFit();

		void minimize(bool signal_only, TH1D* h, double* yields);
		
	private:
		
};
#endif

