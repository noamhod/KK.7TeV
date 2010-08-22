/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef OFFLINEANALYSIS_H
#define OFFLINEANALYSIS_H


class offlineTree
{
	public:
		// pointers to classes
		physics*  m_phys;
		TFile*    m_treeFile;
		TTree*	  m_tree;
		
		// new branches
		Bool_t   isGRL;
		TBranch* b_isGRL;

	public:
		offlineTree();
		offlineTree(physics* phys, TFile* treeFile);
		~offlineTree();

		void setBranches();

		void fill(Bool_t isgrl);
		void write();

	private:

};
#endif


