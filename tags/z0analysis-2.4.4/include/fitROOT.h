/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef FITROOT_H
#define FITROOT_H

class fitROOT
{
	public:
		TF1* fitFCN;
		TF1* guess;

	public:
		fitROOT();
		~fitROOT();
		
		void minimize(bool signal_only, TH1D* h, double* yields);
		
	private:
		
};
#endif

