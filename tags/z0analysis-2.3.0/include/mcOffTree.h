/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef MCOFFTREE_H
#define MCOFFTREE_H

class mcOffTree
{
public:
	// pointers
	mcPhysics* m_mcPhys;
	TFile*     m_treeFile;
	TTree*     m_tree;
	
	// staco truth
	vector<float>*   mu_staco_truth_dr;
	vector<float>*   mu_staco_truth_E;
	vector<float>*   mu_staco_truth_pt;
	vector<float>*   mu_staco_truth_eta;
	vector<float>*   mu_staco_truth_phi;
	vector<int>*     mu_staco_truth_type;
	vector<int>*     mu_staco_truth_status;
	vector<int>*     mu_staco_truth_barcode;
	vector<int>*     mu_staco_truth_mothertype;
	vector<int>*     mu_staco_truth_motherbarcode;
	vector<int>*     mu_staco_truth_matched;

	// muid truth
	vector<float>*   mu_muid_truth_dr;
	vector<float>*   mu_muid_truth_E;
	vector<float>*   mu_muid_truth_pt;
	vector<float>*   mu_muid_truth_eta;
	vector<float>*   mu_muid_truth_phi;
	vector<int>*     mu_muid_truth_type;
	vector<int>*     mu_muid_truth_status;
	vector<int>*     mu_muid_truth_barcode;
	vector<int>*     mu_muid_truth_mothertype;
	vector<int>*     mu_muid_truth_motherbarcode;
	vector<int>*     mu_muid_truth_matched;
	
	// muonTruth
	Int_t            muonTruth_n;
	vector<float>*   muonTruth_pt;
	vector<float>*   muonTruth_m;
	vector<float>*   muonTruth_eta;
	vector<float>*   muonTruth_phi;
	vector<float>*   muonTruth_charge;
	vector<int>*     muonTruth_PDGID;
	vector<int>*     muonTruth_barcode;
	vector<int>*     muonTruth_type;
	vector<int>*     muonTruth_origin;
	
	// MC event
	Int_t            mcevt_n;
	vector<int>*     mcevt_signal_process_id;
	vector<int>*     mcevt_event_number;
	vector<double>*  mcevt_event_scale;
	vector<double>*  mcevt_alphaQCD;
	vector<double>*  mcevt_alphaQED;
	vector<int>*     mcevt_pdf_id1;
	vector<int>*     mcevt_pdf_id2;
	vector<double>*  mcevt_pdf_x1;
	vector<double>*  mcevt_pdf_x2;
	vector<double>*  mcevt_pdf_scale;
	vector<double>*  mcevt_pdf1;
	vector<double>*  mcevt_pdf2;
	vector<double>*  mcevt_weight;
	
public:
	mcOffTree();
	mcOffTree(mcPhysics* mcPhys, TFile* treeFile, TTree* tree);
	~mcOffTree();
	
	void setBranchesMC();
	void fillMC();
	void resetMC();

private:

};
#endif

