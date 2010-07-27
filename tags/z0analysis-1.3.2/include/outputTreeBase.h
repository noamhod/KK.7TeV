/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef OUTPUTTREEBASE_H
#define OUTPUTTREEBASE_H

class outputTreeBase
{
	public:
		// pointers
		TTree* m_tree;
		TDirectory* m_dir;

		// tree branches
		vector<double>* vd_E;
		vector<double>* vd_Px;
		vector<double>* vd_Py;
		vector<double>* vd_Pz;
		vector<double>* vd_M;
		vector<double>* vd_Ch;
		vector<double>* vd_Pt;
		vector<double>* vd_Eta;
		vector<double>* vd_Theta;
		vector<double>* vd_Phi;
		vector<double>* vd_D0;
		vector<double>* vd_Z0;
		vector<double>* vd_QOP;
				
		vector<unsigned short>* vus_Allauthor;
		vector<int>* vi_Author;

		int nParticles;
		
	public:
		outputTreeBase();
		virtual ~outputTreeBase();	
		
		void setTree(string sname, TDirectory* dir);
		void setBranches();

		void clearVectors();
		void fillTree();
		void writeTree();

		virtual void setMoreBranches() = 0;
		virtual void fillVectors() = 0;
};
#endif

