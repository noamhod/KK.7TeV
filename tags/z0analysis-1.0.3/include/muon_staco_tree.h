/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#include "muon_staco.h"

#ifndef MUON_STACO_TREE_H
#define MUON_STACO_TREE_H

class muon_staco_tree : virtual public outputTreeBase
{
	public:	
		muon_staco* m_mustaco;
		
	public:
		muon_staco_tree();
		muon_staco_tree(muon_staco* mustaco, TDirectory* dir);
		~muon_staco_tree();

		virtual void setMoreBranches();
                virtual void fillVectors();

	private:

};
#endif

