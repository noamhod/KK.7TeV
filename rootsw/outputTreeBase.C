/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef outputTreeBase_cxx
#include "outputTreeBase.h"

outputTreeBase::outputTreeBase()
{
	vd_E = new vector<double>;
	vd_Px = new vector<double>;
	vd_Py = new vector<double>;
	vd_Pz = new vector<double>;
	vd_M = new vector<double>;
	vd_Ch = new vector<double>;
	vd_Pt = new vector<double>;
	vd_Eta = new vector<double>;
	vd_Theta = new vector<double>;
	vd_Phi = new vector<double>;
	vd_D0 = new vector<double>;
	vd_Z0 = new vector<double>;
	vd_QOP = new vector<double>;

	vus_Allauthor = new vector<unsigned short>;
	vi_Author = new vector<int>;
}

outputTreeBase::~outputTreeBase() 
{
	delete vd_E;
	delete vd_Px;
	delete vd_Py;
	delete vd_Pz;
	delete vd_M;
	delete vd_Ch;
	delete vd_Pt;
	delete vd_Eta;
	delete vd_Theta;
	delete vd_Phi;
	delete vd_D0;
	delete vd_Z0;
	delete vd_QOP;
	delete vus_Allauthor;
	delete vi_Author;
}

void outputTreeBase::setTree(string sname, TDirectory* dir)
{
	m_dir = dir;
	m_dir->cd();
	
	m_tree = new TTree(sname.c_str(), sname.c_str());

	setBranches();
}

void outputTreeBase::setBranches()
{
	m_tree->Branch( "E", &vd_E );
        m_tree->Branch( "px", &vd_Px );
        m_tree->Branch( "py", &vd_Py );
        m_tree->Branch( "pz", &vd_Pz );
        m_tree->Branch( "m", &vd_M );
        m_tree->Branch( "charge", &vd_Ch );
        m_tree->Branch( "pT", &vd_Pt );
        m_tree->Branch( "eta", &vd_Eta );
        m_tree->Branch( "thetaexPV", &vd_Theta );
        m_tree->Branch( "phi", &vd_Phi );
        m_tree->Branch( "d0exPV", &vd_D0 );
        m_tree->Branch( "z0exPV", &vd_Z0 );
        m_tree->Branch( "qOverpexPV", &vd_QOP );
        m_tree->Branch( "allauthor", &vus_Allauthor );
        m_tree->Branch( "Author", &vi_Author );
        m_tree->Branch( "n", &nParticles );
}

void outputTreeBase::clearVectors()
{
	if(vd_E->size()>0) vd_E->clear();
        if(vd_Px->size()>0) vd_Px->clear();
        if(vd_Py->size()>0) vd_Py->clear();
        if(vd_Pz->size()>0) vd_Pz->clear();
        if(vd_M->size()>0) vd_M->clear();
        if(vd_Ch->size()>0) vd_Ch->clear();
        if(vd_Pt->size()>0) vd_Pt->clear();
        if(vd_Eta->size()>0) vd_Eta->clear();
        if(vd_Theta->size()>0) vd_Theta->clear();
        if(vd_Phi->size()>0) vd_Phi->clear();
        if(vd_D0->size()>0) vd_D0->clear();
        if(vd_Z0->size()>0) vd_Z0->clear();
        if(vd_QOP->size()>0) vd_QOP->clear();
        if(vus_Allauthor->size()>0) vus_Allauthor->clear();	
        if(vi_Author->size()>0) vi_Author->clear();	
}

void outputTreeBase::fillTree()
{
	m_tree->Fill();
}

void outputTreeBase::writeTree()
{
	m_dir->cd();
	m_tree->Write();
}

#endif

