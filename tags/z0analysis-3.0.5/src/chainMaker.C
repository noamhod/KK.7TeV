/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 14:34 */
/* * * * * * * * * * * */

#ifdef chainMaker_cxx
#include "chainMaker.h"

chainMaker::chainMaker()
{
	m_vStr2find = NULL;
}

chainMaker::~chainMaker()
{
	
}

void chainMaker::chainInit(vector<string>* vStr2find)
{
	m_chain = new TChain("physics");
	m_vStr2find = vStr2find;
}

void chainMaker::list2chain(string sListFilePath, string sListContentAbsolutePath, int runNumber)
{
	ifstream file;
	file.open(sListFilePath.c_str());
	string sLine;
	size_t pos;
	size_t min = 32000;
	int nfound = 0;
	int nignored = 0;
	bool strFound = true;
	while(!file.eof())
	{
		getline(file,sLine);
		
		pos = sLine.find(".root");
		if (pos == string::npos) { nignored++; continue; } // if pattern ".root" is not found
		
		if(m_vStr2find!=NULL)
		{
			for(int s=0 ; s<(int)m_vStr2find->size() ; s++)
			{
				pos = sLine.find( m_vStr2find->at(s) );
				if (pos == string::npos) strFound = false;
			}
			if(!strFound) { nignored++; continue; } // if 1 pattern from all the patterns stored in m_vStr2find is not found
		}
		
		if (runNumber != 0)
		{
			stringstream strm;
			strm << runNumber;
			string str = "";
			strm >> str;
			pos = sLine.find( str.c_str() );
			if (pos == string::npos) { nignored++; continue; } // if pattern ".root" is not found
		}
		
		size_t fileSize = 0;
		ifstream infile(sLine.c_str());
		if(infile.is_open())
		{
			infile.seekg(0, ios::end ); // move to end of file
			fileSize = infile.tellg();
			if(fileSize < min) { nignored++; continue; } // if file is too small
		}
		
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
		sLine = sListContentAbsolutePath + sLine; // add the absolute path
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		m_chain->Add( sLine.c_str() );
		nfound++;
	}
	cout << "found "   << nfound   << " entries in " << sListFilePath << endl;
	cout << "ignored " << nignored << " entries in " << sListFilePath << endl; 
}

void chainMaker::makeChain(bool doList, string sListFilePath, string sListContentAbsolutePath, int runNumber)
{
	list2chain(sListFilePath, sListContentAbsolutePath, runNumber);
	if(doList) m_chain->ls();
}


void chainMaker::drawFromChain()
{
	//TCut cut0  = "mu_muid_charge->size()==2";
	TCut cut1  = "mu_muid_charge[0]+mu_muid_charge[1]==0";
	const char* formula1 = "sqrt(mu_muid_m[0]*mu_muid_m[0] + mu_muid_m[1]*mu_muid_m[1] + 2*mu_muid_E[0]*mu_muid_E[1] - 2*(mu_muid_px[0]*mu_muid_px[1] + mu_muid_py[0]*mu_muid_py[1] + mu_muid_pz[0]*mu_muid_pz[1]))";

	TCut cut2  = "mu_muid_charge[0]<0";
	TCut cut3  = "mu_muid_charge[1]<0";
	const char* formula2 = "sqrt( mu_muid_px[0]*mu_muid_px[0] + mu_muid_py[0]*mu_muid_py[0] )";
	const char* formula3 = "sqrt( mu_muid_px[1]*mu_muid_px[1] + mu_muid_py[1]*mu_muid_py[1] )";

	TCanvas* c1 = new TCanvas("imass from m_chain","imass from m_chain",600,400);
	c1->SetLogy();
	c1->Draw();
	c1->cd();
	m_chain->Draw(formula1, cut1);

	TCanvas* c2 = new TCanvas("pT mu^- from m_chain","pT mu^- from m_chain",600,400);
	c2->SetLogy();
	c2->Draw();
	c2->cd();
	m_chain->Draw(formula2, cut1+cut2);
	m_chain->Draw(formula3, cut1+cut3, "sames");

	TCanvas* c3 = new TCanvas("L1_MU6 from m_chain","L1_MU6 from m_chain",600,400);
	//c3->SetLogy();
	c3->Draw();
	c3->cd();
	m_chain->Draw("L1_MU6");
}
#endif

