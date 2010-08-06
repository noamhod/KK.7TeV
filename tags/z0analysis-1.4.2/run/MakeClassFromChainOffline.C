/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 14:34 */
/* * * * * * * * * * * */

#include "MakeClassFromChainOffline.h"

MakeClassFromChainOffline::MakeClassFromChainOffline()
{
	m_chain = new TChain("offline");
}

MakeClassFromChainOffline::~MakeClassFromChainOffline()
{
	delete m_chain;
}

string MakeClassFromChainOffline::checkANDsetFilepath(string envPath, string fileName)
{
        char * tmpPath = getenv(envPath.c_str());
        if (!tmpPath) {
                cerr << "environment variable " << envPath  <<  " not defined" << endl;
                cerr << "\tdid you forget to 'source configure_bash or configure_tcsh' ?" << endl;
                exit(-1);
        }

        string fullPath = tmpPath;
        fullPath += fileName;

        //----------------- check if there are ".."-like parts in the fullPath
        int i=0;
        int pos=0;
        bool isDoubledot = false;
        while (i<(int)fullPath.size()-1) { // check if there's a ".." string in fullPath
                if (fullPath.substr(i,2) == "..") {
                        pos = i;
                        isDoubledot = true;
                }
                i++;
        }

        if (isDoubledot) {
                string oldPath = fullPath;
                string fin = fullPath.substr(pos+2,(int)fullPath.size()-(pos+2)); // remember everything from after ".."
                string newpath = fullPath.substr(0,pos-1); // remember everything before "/.."
                int newpos = pos-2;
                string isBackslash = newpath.substr(newpos,1);
                while (isBackslash != "/") { // remove the dir name before "/.."
                        newpos--;
                        isBackslash = newpath.substr(newpos,1);
                }
                fullPath = newpath.substr(0,newpos) + fin;
                cout << "file path: " << fullPath << endl;
        }

        if (!isDoubledot) {cout << "file path: " << fullPath << endl;}

        return(fullPath);
}


void MakeClassFromChainOffline::list2chain(string sListFilePath)
{
	sListFilePath = checkANDsetFilepath("PWD", "../conf/"+sListFilePath);

	ifstream file;
        file.open(sListFilePath.c_str());
	string sLine;
	size_t pos;
	size_t min = 32000;
	int nfound = 0;
	int nignored = 0;
	while(!file.eof())
	{
		getline(file,sLine);
		
		pos = sLine.find(".root");
		if (pos == string::npos)
		{
			nignored++;
			cout << "ignoring entry: " << sLine << endl;
			continue;
		} // if pattern ".root" is not found
		
		size_t fileSize = 0;
		ifstream infile(sLine.c_str());
		if(infile.is_open())
		{
			infile.seekg(0, ios::end ); // move to end of file
			fileSize = infile.tellg();
			if(fileSize < min)
			{
				nignored++;
				cout << "ignoring entry: " << sLine << endl;
				continue;
			} // if file is too small
		}
	
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
		sLine = "offline_datasetdir/" + sLine; // add the absolute path
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		m_chain->Add( sLine.c_str() );
		nfound++;
	}
	cout << "found "   << nfound   << " entries in " << sListFilePath << endl;
	cout << "ignored " << nignored << " entries in " << sListFilePath << endl;
}

void MakeClassFromChainOffline::makeChain(bool doList, string sListFilePath)
{
	list2chain(sListFilePath);
	if(doList) m_chain->ls();
}

void MakeClassFromChainOffline::GetEntries()
{
	long int nentries = (long int)m_chain->GetEntries();
        cout << "Entries in chain: N=" << nentries << endl;
}


void MakeClassFromChainOffline::chain2class(string sClassName)
{
	m_chain->MakeClass(sClassName.c_str());
}

void MakeClassFromChainOffline::drawFromChain()
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

