
/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "analysisSkeleton.h"

analysisSkeleton::~analysisSkeleton()
{
	fCand->close();
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// GENERAL INITIALIZER METHODS

void analysisSkeleton::setBaseDir(string sBaseDirPath)
{
	_DEBUG("analysisSkeleton::setBaseDir");
	
	base_dir_path = sBaseDirPath;
}
void analysisSkeleton::setEventDumpFile(string sEventDumpFilePath, float massThresholdInGeV)
{
	_DEBUG("analysisSkeleton::setEventDumpFile");
	
	setEventDumperFile(sEventDumpFilePath);
	if(sEventDumpFilePath != "") setInterestingThreshold( massThresholdInGeV*GeV2TeV );
}
void analysisSkeleton::setXmlFile(string sXmlPath)
{
	_DEBUG("analysisSkeleton::setXmlFile");
	
	xmlconfig::get(sXmlPath);
	setCutFlowMapSVDPtr( cutFlowHandler::m_cutFlowMapSVD );
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void analysisSkeleton::setMCPpTparameters(string sDataType, string sAlgo, string spTtype, string sRel, string sDataPath)
{
	_DEBUG("analysisSkeleton::setMCPpTparameters");
	if(sDataType!="Data11" && sDataType!="Data10") _FATAL("sDataType string is unrecognized");
	if(sDataPath=="")                              _FATAL("sDataPath string is empty");
	
	if(spTtype!="pT"  &&  spTtype!="q_pT") _FATAL("spTtype string is unrecognized");
	if(sAlgo!="staco"  &&  sAlgo!="muid")  _FATAL("sAlgo string is unrecognized");
	if(sRel!="Rel17")                      _FATAL("sRel string is unrecognized");

	MCPpTsmearing = new SmearingClass(sDataType,sAlgo,spTtype,sRel,sDataPath);
	MCPpTsmearing->UseScale(1);
	
	// Optional: enable advanced (charge-dependent) muon scale corrections that result in better data/MC agreement 
	MCPpTsmearing->UseImprovedCombine();
	MCPpTsmearing->RestrictCurvatureCorrections(2.5);
	MCPpTsmearing->FillScales("KC");
}
	
void analysisSkeleton::setSmearedMCPpT(int nMus)
{
	_DEBUG("analysisSkeleton::setSmearedMCPpT");

	if(mu_MCP_ptcb->size()!=0) mu_MCP_ptcb->clear(); // same as mu_pt
	if(mu_MCP_ptms->size()!=0) mu_MCP_ptms->clear();
	if(mu_MCP_ptid->size()!=0) mu_MCP_ptid->clear();

	_DEBUG("");
	
	_DEBUG("classify3332null.size()="+_s((int)classify3332null.size()));
	for(int j=0 ; j<nMus ; j++) _DEBUG("classify3332null["+_s(j)+"] = "+_s(classify3332null[j]));
	
	for(int j=0 ; j<nMus ; j++)
	{
		_DEBUG("j="+_s(j));
		if(classify3332null[j]==2 || classify3332null[j]==0) continue; // if 2st or null muon, go on
		_DEBUG("cleared j="+_s(j));
	
		// Retrieve Eta, PtCB, PtMS and PtID from ntuples 
		// Use the MC event number to set seed so that the
		// random numbers are reproducible by different analyzers
		MCPpTsmearing->SetSeed(EventNumber,j);
		
		_DEBUG("");
		
		double chrg  = (double)mu_charge->at(j);
		double ptcb  = (double)mu_pt->at(j);
		double ptid  = (double)pT(mu_id_qoverp->at(j),mu_id_theta->at(j));
		// double ptms  = (double)pT(mu_ms_qoverp->at(j),mu_ms_theta->at(j));
		// double ptie  = (double)pT(mu_ie_qoverp->at(j),mu_ie_theta->at(j));
		double ptme  = (double)pT(mu_me_qoverp->at(j),mu_me_theta->at(j));
		double etacb = (double)mu_eta->at(j);
		
		_DEBUG("");
		
		// MCPpTsmearing->Event(ptms, ptid, ptcb, etacb, chrg);
		// MCPpTsmearing->Event(ptme, ptie, ptcb, etacb, chrg);
		MCPpTsmearing->Event(ptme, ptid, ptcb, etacb, chrg);
		
		_DEBUG("");
		
		// float orig_ptcb = mu_pt->at(j);
		
		double pTCB_smeared = MCPpTsmearing->pTCB(); 
		double pTMS_smeared = MCPpTsmearing->pTMS(); 
		double pTID_smeared = MCPpTsmearing->pTID();
		
		_DEBUG("");
		
		// float cfms = MCPpTsmearing->ChargeFlipMS();
		// float cfid = MCPpTsmearing->ChargeFlipID();
		float cfcb = MCPpTsmearing->ChargeFlipCB();
		if(cfcb==-1.)
		{
			_INFO("CHARGE FLIP !");
			mu_charge->at(j)*=-1.;
		}
		
		_DEBUG("");
		
		if(AS_doSigmaUP)
		{
			// For Systematic Uncertainty studies:
			// Change the Pts UP or DOWN (ID or MS) 
			// Valid values for "THESTRING": {"MSLOW", "MSUP", "IDLOW", "IDUP"}
			string THESTRING = "MSUP";
			MCPpTsmearing->PTVar(pTMS_smeared, pTID_smeared, pTCB_smeared, THESTRING); 
		}
		
		///////////////////////////////////////////////
		// First, have to modify the original CB pT ///
		mu_pt->at(j) = pTCB_smeared; //////////////////
		///////////////////////////////////////////////
		
		mu_MCP_ptcb->push_back( pTCB_smeared ); 
		mu_MCP_ptid->push_back( pTID_smeared ); 
		mu_MCP_ptms->push_back( pTMS_smeared );
	}
}

void analysisSkeleton::set2stSmearing()
{
	_DEBUG("analysisSkeleton::set2stSmearing");
	TwoStationsSmearing = new SmearingClassTwoStations;
}

void analysisSkeleton::setSmeared2Stations(int nMus)
{
	_DEBUG("analysisSkeleton::setSmeared2Stations");
	for(int i=0 ; i<nMus ; i++)
	{
		if(classify3332null[i]==3 || classify3332null[i]==0) continue; // if 3st or null muon, go on
	
		if(!mu_isCombinedMuon->at(i)) continue;
	
		// Get the relative uncertainty on ID and MS track pT at IP
		float eptMS = fabs(sqrt(mu_me_cov_qoverp_exPV->at(i))/mu_me_qoverp_exPV->at(i));
		float eptID = fabs(sqrt(mu_id_cov_qoverp_exPV->at(i))/mu_id_qoverp_exPV->at(i));

		// Get the pT of the combined, ID and MS tracks at IP
		float ptcb = 1./fabs(mu_qoverp_exPV->at(i))*sin(mu_theta_exPV->at(i));
		float ptid = 1./fabs(mu_id_qoverp->at(i))*sin(mu_id_theta->at(i));
		float ptms = 1./fabs(mu_me_qoverp->at(i))*sin(mu_me_theta->at(i));
		
		// Initialize the random numbers, compute the smearing, and retrieve the smeared pT:
		TwoStationsSmearing->SetTheSeed(EventNumber, i, RunNumber);
		TwoStationsSmearing->Event(ptms, ptid, ptcb, mu_eta->at(i), eptMS*ptms, eptID*ptid);
		float ptCBsmeared = TwoStationsSmearing->pTCB();  // Returns a signed smeared pT
		
		///////////////////////////////////////////////////////////
		float orig_ptcb = mu_pt->at(i); ////////////////////////
		mu_pt->at(i) = fabs(ptCBsmeared); /////////////////////////
		// _INFO("pt="+_s(orig_ptcb)+" -> "+_s(mu_pt->at(i))); ///
		///////////////////////////////////////////////////////////
		
		if(ptCBsmeared<0.)
		{
			_INFO("CHARGE FLIP !");
			mu_charge->at(i)*=-1.;
		}
	}
}

void analysisSkeleton::setPileupParameters(TString dataRootFileName, TString dataRootHistName, TString mcRootFileName, TString mcRootHistName)
{
	_DEBUG("analysisSkeleton::setPileupParameters");
	
	m_dataRootFileName = dataRootFileName;
	m_dataRootHistName = dataRootHistName;
	m_mcRootFileName   = mcRootFileName;
	m_mcRootHistName   = mcRootHistName;
	
	pileuprw = new Root::TPileupReweighting( "PileupReweightingTool" );
	
	/* if(doMCPUwrite)
	{
		// pileuprw->AddPeriod(180164, 177986,180481); //associates mc runnumber 180164 with data period 177986 to 180481 (period B-D)
		// pileuprw->AddPeriod(183003, 180614,184169); //period E-H
		// pileuprw->AddPeriod(185649, 185353,186934); //period I-K1. For I-K you would change the last number to 187815
		// pileuprw->AddPeriod(185761, 186935,999999); //everything after K1. If you changed the previous line to I-K, change middle number of this line to 187816
		pileuprw->UsePeriodConfig("MC11a"); //for MC11b change the string to "MC11b"
		pileuprw->Initialize();
		_WARNING("!!! Generating own MC file !!!");
	}
	else
	{
		// pileuprw->AddMCDistribution(mcRootFileName,"MCPileupReweighting");
		// pileuprw->AddDataDistribution(dataRootFileName,"LumiMetaData");
		//// 1: to remove this data from the weight calculations. You should also veto such data events (using isUnrepresentedData(..,..) method)
		//// 2: to leave this data in the calculation. I hope you know what you're doing!!
		pileuprw->MergeMCRunNumbers(185649,185761); // MC11a
		pileuprw->AddConfigFile(mcRootFileName);
		pileuprw->AddLumiCalcFile(dataRootFileName); 
		pileuprw->SetUnrepresentedDataAction( (doRemoveData) ? 1 : 2 );
		pileuprw->Initialize();
		// correctedMClumi = (doRemoveData) ? pileuprw->getTotalLumiUsed() : -999.;
	} */
	
	pileuprw->AddConfigFile(mcRootFileName);
	pileuprw->AddLumiCalcFile(dataRootFileName); 
	pileuprw->SetDefaultChannel(0);
	pileuprw->SetUnrepresentedDataAction( 2 );
	pileuprw->Initialize();
	
}

void analysisSkeleton::writePileupMCfile()
{
	// pileuprw->WriteToFile((base_dir_path+"/"+sMCsampleName).c_str());
	pileuprw->WriteToFile(sMCPUName.c_str());
	_INFO("Wrote P.U. file -> "+sMCPUName);
}

float analysisSkeleton::getPileUpWeight(bool isIntime)
{
	_DEBUG("analysisSkeleton::getPileUpWeight");

	if(doMCPUwrite) pileuprw->Fill(RunNumber,mc_channel_number,mcevent_weight/* mcevt_weight[0][0] */,averageIntPerXing);
	
	// Get the mu value for this event
	
	// one should use the actualIntPerXing variable.
	// This should be the one describing the "in-time" pileup,
	// while averageIntPerXing describes the out-of-time pileup
	// The difference should be marginal, but I think we should still use the first one for the pileup re-weighting.
	
	// float mu = (float)lbn;
	// float mu = actualIntPerXing;     // in-time pileup
	// float mu = averageIntPerXing; // out-of-time pileup

	float mu = 0.;
	if(isIntime) mu = actualIntPerXing;
	else         mu = averageIntPerXing;
	
	// Get the pileup weight for this event
	float pileupEventWeight = 1.;
	if(!doMCPUwrite) pileupEventWeight = pileuprw->GetCombinedWeight(RunNumber,mc_channel_number,mu);
	
	return pileupEventWeight;
}

void analysisSkeleton::setPtCandidatesFile(string sCandFilePath, string srunnumber, string selector)
{
	_DEBUG("analysisSkeleton::setPtCandidatesFile");
	
	string sLogFileName = sCandFilePath+"/candidates_pT.run_"+srunnumber+selector+".cnd";//".time_"+getDateHour()+".cnd";
	fCand = new ofstream( sLogFileName.c_str() );
}

void analysisSkeleton::resetMuQAflags(int nMus)
{
	_DEBUG("analysisSkeleton::resetMuQAflags");
	if(muQAflags.size()>0)      muQAflags.clear();
	for(int j=0 ; j<nMus ; j++) muQAflags.push_back(true);
	
	if(muLooseQAflags.size()>0) muLooseQAflags.clear();
	for(int j=0 ; j<nMus ; j++) muLooseQAflags.push_back(true);
}

void analysisSkeleton::classifyMuons(int nMus)
{
	if(mu_sig_diff_qoverp.size()>0) mu_sig_diff_qoverp.clear();
	setMuonMomentumSignificance(mu_sig_diff_qoverp,
								mu_me_qoverp,mu_id_qoverp,
								mu_me_cov_qoverp_exPV,mu_id_cov_qoverp_exPV);

	if(classify3332null.size()>0) classify3332null.clear();
	for(int j=0 ; j<nMus ; j++) classify3332null.push_back(0);
	float cutval1  = (*m_cutFlowMapSVD)["MShitsPairFormation"][0];
	float cutval2  = (*m_cutFlowMapSVD)["MShitsPairFormation"][1];
	float cutval3  = (*m_cutFlowMapSVD)["MShitsPairFormation"][2];
	float cutval4  = (*m_cutFlowMapSVD)["MShitsPairFormation"][3];
	float cutval5  = (*m_cutFlowMapSVD)["MShitsPairFormation"][4];
	float cutval6  = (*m_cutFlowMapSVD)["MShitsPairFormation"][5];
	float cutval7  = (*m_cutFlowMapSVD)["MShitsPairFormation"][6];
	float cutval8  = (*m_cutFlowMapSVD)["MShitsPairFormation"][7];
	classify3233(cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,cutval7,cutval8,
				 mu_sig_diff_qoverp,
				 mu_eta, mu_phi, mu_charge,
				 mu_nMDTBIHits, mu_nMDTBMHits, mu_nMDTBOHits,
				 mu_nMDTEIHits, mu_nMDTEMHits, mu_nMDTEOHits,
				 mu_nMDTBEEHits, mu_nMDTEEHits, mu_nMDTBIS78Hits,
				 mu_nRPCLayer1PhiHits, mu_nRPCLayer2PhiHits, mu_nRPCLayer3PhiHits,
				 mu_nTGCLayer1PhiHits, mu_nTGCLayer2PhiHits, mu_nTGCLayer3PhiHits, mu_nTGCLayer4PhiHits,
				 mu_nCSCEtaHits, mu_nCSCPhiHits,
				 classify3332null);
}

string analysisSkeleton::getPeriodName()
{
	_DEBUG("analysisSkeleton::getPeriodName");
	string speriod = sCurrentPeriod;
	_DEBUG("speriod = "+speriod);
	if(RunNumber != currentRun)
	{
		_DEBUG("RunNumber="+_s(RunNumber));
		speriod = (AS_isMC) ? "MC" : getPeriod( RunNumber, m_firstrun2periodMap, m_lastrun2periodMap ); // ???????????????????????
		_INFO("switching to period: "+speriod+" (run "+_s(RunNumber)+")");
		currentRun     = RunNumber;
		sCurrentPeriod = speriod;
	}
	if(speriod=="")
	{
		_ERROR("in analysisSkeleton::getPeriodName -> (speriod==""), exitting now");
		exit(-1);
	}
	
	return speriod;
}

string analysisSkeleton::getPeriodName(int run)
{
	_DEBUG("analysisSkeleton::getPeriodName(int run)");
	return getPeriod( run, m_firstrun2periodMap, m_lastrun2periodMap );
}

vector<string>* analysisSkeleton::getPeriodTriggers()
{
	_DEBUG("analysisSkeleton::getPeriodTriggers");
	if(sPeriod==""  ||  m_period2triggerMap==NULL)
	{
		_ERROR("sPeriod==null || m_period2triggerMap==NULL, exitting now");
		exit(-1);
	}
	
	return getTrigs(sPeriod, m_period2triggerMap);
}

bool analysisSkeleton::isTrigger(string trigName)
{
	_DEBUG("analysisSkeleton::isTrigger");
	if(trigName=="")
	{
		_ERROR("trigName==null, exitting now");
		exit(-1);
	}
	
	bool isTrig = false;
	if     (trigName=="L1_MU10")                      isTrig = L1_MU10;
	else if(trigName=="EF_mu18")                      isTrig = EF_mu18;
	else if(trigName=="EF_mu18_MG")                   isTrig = EF_mu18_MG;
	else if(trigName=="EF_mu18_medium")               isTrig = EF_mu18_medium;
	else if(trigName=="EF_mu18_MG_medium")            isTrig = EF_mu18_MG_medium;
	else if(trigName=="EF_mu22")                      isTrig = EF_mu22;
	else if(trigName=="EF_mu22_MG")                   isTrig = EF_mu22_MG;
	else if(trigName=="EF_mu22_medium")               isTrig = EF_mu22_medium;
	else if(trigName=="EF_mu22_MG_medium")            isTrig = EF_mu22_MG_medium;
	else if(trigName=="EF_mu40_MSonly_barrel")        isTrig = EF_mu40_MSonly_barrel;
	else if(trigName=="EF_mu40_MSonly_barrel_medium") isTrig = EF_mu40_MSonly_barrel_medium;
	else _WARNING("in analysisSkeleton::isTrigger -> the trigger "+trigName+" was not found and the event is regected by default");
	
	return isTrig;
}

void analysisSkeleton::matchTrigger(string speriod, string sTrigType)
{
	_DEBUG("analysisSkeleton::matchTrigger");
	/*
	EFCB: the trig muon for the regular EF trigger
	EFME: the MSonly trig muons
	EFMG: trig mugirl (_MG type triggers)
	L2CB: combinedmuonfeature (mucomb)
	L1:   the level 1 RoI
	
	For the first two, the trigger block variables are the ones starting
	with trig_EF_trigmuonef_ while for mugirl the trigger variables are trig_EF_trigmugirl_
	The L2 information matches to the trig_L2_combmuonfeature_ blocks and L1 ->trig_L1_mu_
	*/

	if(speriod=="")
	{
		_ERROR("speriod==null, exitting now");
		exit(-1);
	}
	
	_DEBUG("speriod = "+speriod);
	
	// if(speriod=="MC")
	// {
		// mu_LLT_index = mu_L1_index;
		// mu_LLT_dr    = mu_L1_dr;
		// LLT_pt       = trig_L1_mu_pt;
		// LLT_phi      = trig_L1_mu_phi;
		// LLT_eta      = trig_L1_mu_eta;
	// }
	// else if
	if
	(
		speriod=="MC" ||
		speriod=="A"  || speriod=="B" || speriod=="D" || speriod=="E" ||
		speriod=="F"  || speriod=="G" || speriod=="H" || speriod=="I" ||
		speriod=="J"  || speriod=="K" || speriod=="L" || speriod=="M"
	)
	{
		_DEBUG("sTrigType = "+sTrigType);
		if(sTrigType=="CB")
		{
			_DEBUG("");
			mu_HLT_dr = mu_EFCB_dr;
			mu_HLT_index = mu_EFCB_index;
			HLT_pt = trig_EF_trigmuonef_track_CB_pt;
			HLT_phi = trig_EF_trigmuonef_track_CB_phi;
			HLT_eta = trig_EF_trigmuonef_track_CB_eta;
			HLT_has = trig_EF_trigmuonef_track_CB_hasCB;
			_DEBUG("");
		}
		else if(sTrigType=="MSonly"||sTrigType=="MS")
		{
			_DEBUG("");
			mu_HLT_dr = mu_EFME_dr;
			mu_HLT_index = mu_EFME_index;
			HLT_pt = trig_EF_trigmuonef_track_MS_pt;
			HLT_phi = trig_EF_trigmuonef_track_MS_phi;
			HLT_eta = trig_EF_trigmuonef_track_MS_eta;
			HLT_has = trig_EF_trigmuonef_track_MS_hasMS;
			_DEBUG("");
		}
		else if(sTrigType=="MG")
		{
			_DEBUG("");
			mu_HLT_dr = mu_EFMG_dr;
			mu_HLT_index = mu_EFMG_index;
			HLT_pt = trig_EF_trigmugirl_track_CB_pt;
			HLT_phi = trig_EF_trigmugirl_track_CB_phi;
			HLT_eta = trig_EF_trigmugirl_track_CB_eta;
			HLT_has = trig_EF_trigmugirl_track_CB_hasCB;
			_DEBUG("");
		}
		else
		{
			_ERROR("unknown sTrigType="+sTrigType+", exitting now");
			exit(-1);
		}
	}
	
	else _WARNING("the period name "+speriod+" was not found");
}

bool analysisSkeleton::checkTrigger(float trigThreshold)
{
	_DEBUG("analysisSkeleton::checkTrigger");
	if(trigThreshold<=0)
	{
		_ERROR("trigThreshold<=0, exitting now");
		exit(-1);
	}
	
	for(int iROI=0 ; iROI<(int)HLT_has->size() ; iROI++)
	{
		for(int iTrk=0 ; iTrk<(int)HLT_has->at(iROI).size() ; iTrk++)
		{
			if( !HLT_has->at(iROI)[iTrk] ) continue;
			float ptTrk = HLT_pt->at(iROI)[iTrk]*MeV2GeV;
			if(ptTrk<trigThreshold) continue;
			return true;
		}
	}
	
	return false;
}

void analysisSkeleton::runEventDumper()
{
	if(!isInteresting(current_imass)) return;
	
	setSingleEventFile(base_dir_path,RunNumber,lbn,EventNumber);
	
	insertTableLine("$m_{\\mu\\mu}$", _s(current_imass*TeV2GeV)+"~GeV");
	insertTableLine("$\\cos\\theta^*_{{\\rm HE}}$", _s(current_cosThetaHE));
	insertTableLine("$\\cos\\theta^*_{{\\rm CS}}$", _s(current_cosThetaCS));
	insertTableLine("$Q_T\\left(\\mu\\mu\\right)$", _s(current_QT*TeV2GeV)+"~GeV");
	insertTableLine("$y_Q\\left(\\mu\\mu\\right)$", _s(current_ySystem));
	insertTableLine("$\\beta_Q\\left(\\mu\\mu\\right)$", _s(current_betaQ));
	insertTableLine("$\\beta_Q^{z}\\left(\\mu\\mu\\right)$", _s(current_betazQ));
	insertTableLine("$\\beta_Q^{T}\\left(\\mu\\mu\\right)$", _s(current_betaTQ));
	insertTableLine("charge", _s(mu_charge->at(ai)), _s(mu_charge->at(bi)));
	insertTableLine("all author", _s(mu_allauthor->at(ai)), _s(mu_allauthor->at(bi)));
	insertTableLine("$\\mu$ author", _s(mu_author->at(ai)), _s(mu_author->at(bi)));
	insertTableLine("$\\beta$", _s(mu_beta->at(ai)), _s(mu_beta->at(bi)));
	insertTableLine("isMuonLikelihood", _s(mu_isMuonLikelihood->at(ai)), _s(mu_isMuonLikelihood->at(bi)));
	insertTableLine("match $\\chi^2$", _s(mu_matchchi2->at(ai)), _s(mu_matchchi2->at(bi)));
	insertTableLine("match $N_{{\\rm DOF}}$", _s(mu_matchndof->at(ai)), _s(mu_matchndof->at(bi)));
	insertTableLine("$\\eta$", _s(mu_eta->at(ai)), _s(mu_eta->at(bi)));
	insertTableLine("$\\phi$", _s(mu_phi->at(ai)), _s(mu_phi->at(bi)));
	insertTableLine("$E$", _s(mu_E->at(ai)*MeV2GeV)+"~GeV", _s(mu_E->at(bi)*MeV2GeV)+"~GeV");
	insertTableLine("$p_x$", _s(mu_px->at(ai)*MeV2GeV)+"~GeV", _s(mu_px->at(bi)*MeV2GeV)+"~GeV");
	insertTableLine("$p_y$", _s(mu_py->at(ai)*MeV2GeV)+"~GeV", _s(mu_py->at(bi)*MeV2GeV)+"~GeV");
	insertTableLine("$p_z$", _s(mu_pz->at(ai)*MeV2GeV)+"~GeV", _s(mu_pz->at(bi)*MeV2GeV)+"~GeV");
	insertTableLine("$p_T{\\rm (CB)}$", _s(mu_pt->at(ai)*MeV2GeV)+"~GeV", _s(mu_pt->at(bi)*MeV2GeV)+"~GeV");
	insertTableLine("$p_T{\\rm (MS)}$", _s(pT(mu_ms_qoverp->at(ai),mu_ms_theta->at(ai))*MeV2GeV)+"~GeV", _s(pT(mu_ms_qoverp->at(bi),mu_ms_theta->at(bi))*MeV2GeV)+"~GeV");
	insertTableLine("$p_T{\\rm (ME)}$", _s(pT(mu_me_qoverp->at(ai),mu_me_theta->at(ai))*MeV2GeV)+"~GeV", _s(pT(mu_me_qoverp->at(bi),mu_me_theta->at(bi))*MeV2GeV)+"~GeV");
	insertTableLine("$p_T{\\rm (ID)}$", _s(pT(mu_id_qoverp->at(ai),mu_id_theta->at(ai))*MeV2GeV)+"~GeV", _s(pT(mu_id_qoverp->at(bi),mu_id_theta->at(bi))*MeV2GeV)+"~GeV");
	insertTableLine("$p_T{\\rm (IE)}$", _s(pT(mu_ie_qoverp->at(ai),mu_ie_theta->at(ai))*MeV2GeV)+"~GeV", _s(pT(mu_ie_qoverp->at(bi),mu_ie_theta->at(bi))*MeV2GeV)+"~GeV");
	insertTableLine("$d_0$ exPV", _s(mu_d0_exPV->at(ai))+"~mm", _s(mu_d0_exPV->at(bi))+"~mm");
	insertTableLine("$z_0$ exPV", _s(mu_z0_exPV->at(ai))+"~mm", _s(mu_z0_exPV->at(bi))+"~mm");
	insertTableLine("$\\phi$ exPV", _s(mu_phi_exPV->at(ai)), _s(mu_phi_exPV->at(bi)));
	insertTableLine("$\\theta$ exPV", _s(mu_theta_exPV->at(ai)), _s(mu_theta_exPV->at(bi)));
	insertTableLine("$\\frac{Q}{p}$ exPV", _s(mu_qoverp_exPV->at(ai)), _s(mu_qoverp_exPV->at(bi)));
	insertTableLine("$p_T^{dR<0.2}/p_T{\\rm (CB)}$", _s(mu_ptcone20->at(ai)/mu_pt->at(ai),7), _s(mu_ptcone20->at(bi)/mu_pt->at(bi),7));
	insertTableLine("$p_T^{dR<0.3}/p_T{\\rm (CB)}$", _s(mu_ptcone30->at(ai)/mu_pt->at(ai),7), _s(mu_ptcone30->at(bi)/mu_pt->at(bi),7));
	insertTableLine("$p_T^{dR<0.4}/p_T{\\rm (CB)}$", _s(mu_ptcone40->at(ai)/mu_pt->at(ai),7), _s(mu_ptcone40->at(bi)/mu_pt->at(bi),7));
	insertTableLine("energyLossPar",_s(mu_energyLossPar->at(ai)), _s(mu_energyLossPar->at(bi)));
	insertTableLine("energyLossErr", _s(mu_energyLossErr->at(ai)), _s(mu_energyLossErr->at(bi)));
	insertTableLine("etCore", _s(mu_etCore->at(ai)), _s(mu_etCore->at(bi)));
	insertTableLine("energyLossType", _s(mu_energyLossType->at(ai)), _s(mu_energyLossType->at(bi)));
	insertTableLine("caloMuonIdTag", _s(mu_caloMuonIdTag->at(ai)), _s(mu_caloMuonIdTag->at(bi)));
	insertTableLine("caloLRLikelihood", _s(mu_caloLRLikelihood->at(ai)), _s(mu_caloLRLikelihood->at(bi)));
	insertTableLine("bestMatch", _s(mu_bestMatch->at(ai)), _s(mu_bestMatch->at(bi)));
	insertTableLine("isStandAloneMuon", _s(mu_isStandAloneMuon->at(ai)), _s(mu_isStandAloneMuon->at(bi)));
	insertTableLine("isCombinedMuon", _s(mu_isCombinedMuon->at(ai)), _s(mu_isCombinedMuon->at(bi)));
	insertTableLine("isLowPtReconstructedMuon", _s(mu_isLowPtReconstructedMuon->at(ai)), _s(mu_isLowPtReconstructedMuon->at(bi)));
	insertTableLine("loose", _s(mu_loose->at(ai)), _s(mu_loose->at(bi)));
	insertTableLine("medium", _s(mu_medium->at(ai)), _s(mu_medium->at(bi)));
	insertTableLine("tight", _s(mu_tight->at(ai)), _s(mu_tight->at(bi)));
	insertTableLine("nBLHits", _s(mu_nBLHits->at(ai)), _s(mu_nBLHits->at(bi)));
	insertTableLine("nPixHits", _s(mu_nPixHits->at(ai)), _s(mu_nPixHits->at(bi)));
	insertTableLine("nSCTHits", _s(mu_nSCTHits->at(ai)), _s(mu_nSCTHits->at(bi)));
	insertTableLine("nTRTHits", _s(mu_nTRTHits->at(ai)), _s(mu_nTRTHits->at(bi)));
	insertTableLine("nTRTHighTHits", _s(mu_nTRTHighTHits->at(ai)), _s(mu_nTRTHighTHits->at(bi)));
	insertTableLine("nBLSharedHits", _s(mu_nBLSharedHits->at(ai)), _s(mu_nBLSharedHits->at(bi)));
	insertTableLine("nPixSharedHits", _s(mu_nPixSharedHits->at(ai)), _s(mu_nPixSharedHits->at(bi)));
	insertTableLine("nPixHoles", _s(mu_nPixHoles->at(ai)), _s(mu_nPixHoles->at(bi)));
	insertTableLine("nSCTSharedHits", _s(mu_nSCTSharedHits->at(ai)), _s(mu_nSCTSharedHits->at(bi)));
	insertTableLine("nSCTHoles", _s(mu_nSCTHoles->at(ai)), _s(mu_nSCTHoles->at(bi)));
	insertTableLine("nTRTOutliers", _s(mu_nTRTOutliers->at(ai)), _s(mu_nTRTOutliers->at(bi)));
	insertTableLine("nTRTHighTOutliers", _s(mu_nTRTHighTOutliers->at(ai)), _s(mu_nTRTHighTOutliers->at(bi)));
	insertTableLine("nGangedPixels", _s(mu_nGangedPixels->at(ai)), _s(mu_nGangedPixels->at(bi)));
	insertTableLine("nPixelDeadSensors", _s(mu_nPixelDeadSensors->at(ai)), _s(mu_nPixelDeadSensors->at(bi)));
	insertTableLine("nSCTDeadSensors", _s(mu_nSCTDeadSensors->at(ai)), _s(mu_nSCTDeadSensors->at(bi)));
	insertTableLine("nTRTDeadStraws", _s(mu_nTRTDeadStraws->at(ai)), _s(mu_nTRTDeadStraws->at(bi)));
	insertTableLine("expectBLayerHit", _s(mu_expectBLayerHit->at(ai)), _s(mu_expectBLayerHit->at(bi)));
	insertTableLine("nMDTHits", _s(mu_nMDTHits->at(ai)), _s(mu_nMDTHits->at(bi)));
	insertTableLine("nMDTHoles", _s(mu_nMDTHoles->at(ai)), _s(mu_nMDTHoles->at(bi)));
	insertTableLine("nCSCEtaHits", _s(mu_nCSCEtaHits->at(ai)), _s(mu_nCSCEtaHits->at(bi)));
	insertTableLine("nCSCEtaHoles", _s(mu_nCSCEtaHoles->at(ai)), _s(mu_nCSCEtaHoles->at(bi)));
	insertTableLine("nCSCPhiHits", _s(mu_nCSCPhiHits->at(ai)), _s(mu_nCSCPhiHits->at(bi)));
	insertTableLine("nCSCPhiHoles", _s(mu_nCSCPhiHoles->at(ai)), _s(mu_nCSCPhiHoles->at(bi)));
	insertTableLine("nRPCEtaHits", _s(mu_nRPCEtaHits->at(ai)), _s(mu_nRPCEtaHits->at(bi)));
	insertTableLine("nRPCEtaHoles", _s(mu_nRPCEtaHoles->at(ai)), _s(mu_nRPCEtaHoles->at(bi)));
	insertTableLine("nRPCPhiHits", _s(mu_nRPCPhiHits->at(ai)), _s(mu_nRPCPhiHits->at(bi)));
	insertTableLine("nRPCPhiHoles", _s(mu_nRPCPhiHoles->at(ai)), _s(mu_nRPCPhiHoles->at(bi)));
	insertTableLine("nTGCEtaHits", _s(mu_nTGCEtaHits->at(ai)), _s(mu_nTGCEtaHits->at(bi)));
	insertTableLine("nTGCEtaHoles", _s(mu_nTGCEtaHoles->at(ai)), _s(mu_nTGCEtaHoles->at(bi)));
	insertTableLine("nTGCPhiHits", _s(mu_nTGCPhiHits->at(ai)), _s(mu_nTGCPhiHits->at(bi)));
	insertTableLine("nTGCPhiHoles", _s(mu_nTGCPhiHoles->at(ai)), _s(mu_nTGCPhiHoles->at(bi)));
	insertTableLine("nMDTBIHits", _s(mu_nMDTBIHits->at(ai)), _s(mu_nMDTBIHits->at(bi)));
	insertTableLine("nMDTBMHits", _s(mu_nMDTBMHits->at(ai)), _s(mu_nMDTBMHits->at(bi)));
	insertTableLine("nMDTBOHits", _s(mu_nMDTBOHits->at(ai)), _s(mu_nMDTBOHits->at(bi)));
	insertTableLine("nMDTBEEHits", _s(mu_nMDTBEEHits->at(ai)), _s(mu_nMDTBEEHits->at(bi)));
	insertTableLine("nMDTBIS78Hits", _s(mu_nMDTBIS78Hits->at(ai)), _s(mu_nMDTBIS78Hits->at(bi)));
	insertTableLine("nMDTEIHits", _s(mu_nMDTEIHits->at(ai)), _s(mu_nMDTEIHits->at(bi)));
	insertTableLine("nMDTEMHits", _s(mu_nMDTEMHits->at(ai)), _s(mu_nMDTEMHits->at(bi)));
	insertTableLine("nMDTEOHits", _s(mu_nMDTEOHits->at(ai)), _s(mu_nMDTEOHits->at(bi)));
	insertTableLine("nMDTEEHits", _s(mu_nMDTEEHits->at(ai)), _s(mu_nMDTEEHits->at(bi)));
	insertTableLine("nRPCLayer1EtaHits", _s(mu_nRPCLayer1EtaHits->at(ai)), _s(mu_nRPCLayer1EtaHits->at(bi)));
	insertTableLine("nRPCLayer2EtaHits", _s(mu_nRPCLayer2EtaHits->at(ai)), _s(mu_nRPCLayer2EtaHits->at(bi)));
	insertTableLine("nRPCLayer3EtaHits", _s(mu_nRPCLayer3EtaHits->at(ai)), _s(mu_nRPCLayer3EtaHits->at(bi)));
	insertTableLine("nRPCLayer1PhiHits", _s(mu_nRPCLayer1PhiHits->at(ai)), _s(mu_nRPCLayer1PhiHits->at(bi)));
	insertTableLine("nRPCLayer2PhiHits", _s(mu_nRPCLayer2PhiHits->at(ai)), _s(mu_nRPCLayer2PhiHits->at(bi)));
	insertTableLine("nRPCLayer3PhiHits", _s(mu_nRPCLayer3PhiHits->at(ai)), _s(mu_nRPCLayer3PhiHits->at(bi)));
	insertTableLine("nTGCLayer1EtaHits", _s(mu_nTGCLayer1EtaHits->at(ai)), _s(mu_nTGCLayer1EtaHits->at(bi)));
	insertTableLine("nTGCLayer2EtaHits", _s(mu_nTGCLayer2EtaHits->at(ai)), _s(mu_nTGCLayer2EtaHits->at(bi)));
	insertTableLine("nTGCLayer3EtaHits", _s(mu_nTGCLayer3EtaHits->at(ai)), _s(mu_nTGCLayer3EtaHits->at(bi)));
	insertTableLine("nTGCLayer4EtaHits", _s(mu_nTGCLayer4EtaHits->at(ai)), _s(mu_nTGCLayer4EtaHits->at(bi)));
	insertTableLine("nTGCLayer1PhiHits", _s(mu_nTGCLayer1PhiHits->at(ai)), _s(mu_nTGCLayer1PhiHits->at(bi)));
	insertTableLine("nTGCLayer2PhiHits", _s(mu_nTGCLayer2PhiHits->at(ai)), _s(mu_nTGCLayer2PhiHits->at(bi)));
	insertTableLine("nTGCLayer3PhiHits", _s(mu_nTGCLayer3PhiHits->at(ai)), _s(mu_nTGCLayer3PhiHits->at(bi)));
	insertTableLine("nTGCLayer4PhiHits", _s(mu_nTGCLayer4PhiHits->at(ai)), _s(mu_nTGCLayer4PhiHits->at(bi)));
	insertTableLine("track fit $\\chi^2$", _s(mu_trackfitchi2->at(ai)), _s(mu_trackfitchi2->at(bi)));
	insertTableLine("track fit $N_{{\\rm DOF}}$", _s(mu_trackfitndof->at(ai)), _s(mu_trackfitndof->at(bi)));
	insertTableLine("hastrack", _s(mu_hastrack->at(ai)), _s(mu_hastrack->at(bi)));
	insertTableLine("EFCB\\_dr", _s(mu_EFCB_dr->at(ai)), _s(mu_EFCB_dr->at(bi)));
	insertTableLine("EFMG\\_dr", _s(mu_EFMG_dr->at(ai)), _s(mu_EFMG_dr->at(bi)));
	insertTableLine("EFME\\_dr", _s(mu_EFME_dr->at(ai)), _s(mu_EFME_dr->at(bi)));
	insertTableLine("L2CB\\_dr", _s(mu_L2CB_dr->at(ai)), _s(mu_L2CB_dr->at(bi)));
	insertTableLine("L1\\_dr",_s(mu_L1_dr->at(ai)), _s(mu_L1_dr->at(bi)), false, true);
	
	///////////////////////////////////////
	closeSingleEventFile(); // end ////////
	///////////////////////////////////////
}


void analysisSkeleton::printAllProperties(int aii, int bii, int iv)
{
	_DEBUG("analysisSkeleton::printAllProperties");
	// event
	printProperty("RunNumber", RunNumber);
	printProperty("lbn", lbn);
	printProperty("EventNumber", EventNumber);
	printProperty("isGRL", isGRL);
	printProperty("imass", imass(pmu[aii],pmu[bii]));
   
	// vertexes (for the PV preselection)
	printProperty("vxp_n", vxp_n);
	printProperty("vxp_nTracks", vxp_nTracks->at(iv));
	printProperty("vxp_type", vxp_type->at(iv));
	printProperty("vxp_z", vxp_z->at(iv));
	
	// muon
	printProperty("mu_1_n",mu_n);
	printProperty("mu_1_m", mu_m->at(aii));
	printProperty("mu_1_px", mu_px->at(aii));
	printProperty("mu_1_py", mu_py->at(aii));
	printProperty("mu_1_pz", mu_pz->at(aii));
	printProperty("mu_1_E", mu_E->at(aii));
	printProperty("mu_1_eta", mu_eta->at(aii));
	printProperty("mu_1_phi", mu_phi->at(aii));
	printProperty("mu_1_pt", mu_pt->at(aii));
	printProperty("mu_1_charge", mu_charge->at(aii));
	
	// isolation
	printProperty("mu_1_ptcone20", mu_ptcone20->at(aii));
	printProperty("mu_1_ptcone30", mu_ptcone30->at(aii));
	printProperty("mu_1_ptcone40", mu_ptcone40->at(aii));
	
	// for pT
	printProperty("mu_1_me_qoverp", mu_me_qoverp->at(aii));
	printProperty("mu_1_id_qoverp", mu_id_qoverp->at(aii));
	printProperty("mu_1_me_theta", mu_me_theta->at(aii));
	printProperty("mu_1_id_theta", mu_id_theta->at(aii));
	
	// for impact parameter
	printProperty("mu_1_d0_exPV", mu_d0_exPV->at(aii));
	printProperty("mu_1_z0_exPV", mu_z0_exPV->at(aii));
	
	// combined muons
	printProperty("mu_1_isCombinedMuon", mu_isCombinedMuon->at(aii));
	
	// inner detector hits
	printProperty("mu_1_nSCTHits", mu_nSCTHits->at(aii));
	printProperty("mu_1_nPixHits", mu_nPixHits->at(aii)); 

	// muon spectrometer hits
	printProperty("mu_1_nMDTBIHits", mu_nMDTBIHits->at(aii));
	printProperty("mu_1_nMDTBMHits", mu_nMDTBMHits->at(aii));
	printProperty("mu_1_nMDTBOHits", mu_nMDTBOHits->at(aii));
	printProperty("mu_1_nMDTBEEHits", mu_nMDTBEEHits->at(aii));
	printProperty("mu_1_nMDTBIS78Hits", mu_nMDTBIS78Hits->at(aii));
	printProperty("mu_1_nMDTEIHits", mu_nMDTEIHits->at(aii));
	printProperty("mu_1_nMDTEMHits", mu_nMDTEMHits->at(aii));
	printProperty("mu_1_nMDTEOHits", mu_nMDTEOHits->at(aii));
	printProperty("mu_1_nMDTEEHits", mu_nMDTEEHits->at(aii));
	printProperty("mu_1_nRPCLayer1EtaHits", mu_nRPCLayer1EtaHits->at(aii));
	printProperty("mu_1_nRPCLayer2EtaHits", mu_nRPCLayer2EtaHits->at(aii));
	printProperty("mu_1_nRPCLayer3EtaHits", mu_nRPCLayer3EtaHits->at(aii));
	printProperty("mu_1_nRPCLayer1PhiHits", mu_nRPCLayer1PhiHits->at(aii));
	printProperty("mu_1_nRPCLayer2PhiHits", mu_nRPCLayer2PhiHits->at(aii));
	printProperty("mu_1_nRPCLayer3PhiHits", mu_nRPCLayer3PhiHits->at(aii));
	printProperty("mu_1_nTGCLayer1EtaHits", mu_nTGCLayer1EtaHits->at(aii));
	printProperty("mu_1_nTGCLayer2EtaHits", mu_nTGCLayer2EtaHits->at(aii));
	printProperty("mu_1_nTGCLayer3EtaHits", mu_nTGCLayer3EtaHits->at(aii));
	printProperty("mu_1_nTGCLayer4EtaHits", mu_nTGCLayer4EtaHits->at(aii));
	printProperty("mu_1_nTGCLayer1PhiHits", mu_nTGCLayer1PhiHits->at(aii));
	printProperty("mu_1_nTGCLayer2PhiHits", mu_nTGCLayer2PhiHits->at(aii));
	printProperty("mu_1_nTGCLayer3PhiHits", mu_nTGCLayer3PhiHits->at(aii));
	printProperty("mu_1_nTGCLayer4PhiHits", mu_nTGCLayer4PhiHits->at(aii));

	printProperty("mu_2_m", mu_m->at(bii));
	printProperty("mu_2_px", mu_px->at(bii));
	printProperty("mu_2_py", mu_py->at(bii));
	printProperty("mu_2_pz", mu_pz->at(bii));
	printProperty("mu_2_E", mu_E->at(bii));
	printProperty("mu_2_eta", mu_eta->at(bii));
	printProperty("mu_2_phi", mu_phi->at(bii));
	printProperty("mu_2_pt", mu_pt->at(bii));
	printProperty("mu_2_charge", mu_charge->at(bii));
	
	// isolation
	printProperty("mu_2_ptcone20", mu_ptcone20->at(bii));
	printProperty("mu_2_ptcone30", mu_ptcone30->at(bii));
	printProperty("mu_2_ptcone40", mu_ptcone40->at(bii));
	
	// for pT
	printProperty("mu_2_me_qoverp", mu_me_qoverp->at(bii));
	printProperty("mu_2_id_qoverp", mu_id_qoverp->at(bii));
	printProperty("mu_2_me_theta", mu_me_theta->at(bii));
	printProperty("mu_2_id_theta", mu_id_theta->at(bii));
	
	// for impact parameter
	printProperty("mu_2_d0_exPV", mu_d0_exPV->at(bii));
	printProperty("mu_2_z0_exPV", mu_z0_exPV->at(bii));
	
	// combined muons
	printProperty("mu_2_isCombinedMuon", mu_isCombinedMuon->at(bii));
	
	// inner detector hits
	printProperty("mu_2_nSCTHits", mu_nSCTHits->at(bii));
	printProperty("mu_2_nPixHits", mu_nPixHits->at(bii)); 

	// muon spectrometer hits
	printProperty("mu_2_nMDTBIHits", mu_nMDTBIHits->at(bii));
	printProperty("mu_2_nMDTBMHits", mu_nMDTBMHits->at(bii));
	printProperty("mu_2_nMDTBOHits", mu_nMDTBOHits->at(bii));
	printProperty("mu_2_nMDTBEEHits", mu_nMDTBEEHits->at(bii));
	printProperty("mu_2_nMDTBIS78Hits", mu_nMDTBIS78Hits->at(bii));
	printProperty("mu_2_nMDTEIHits", mu_nMDTEIHits->at(bii));
	printProperty("mu_2_nMDTEMHits", mu_nMDTEMHits->at(bii));
	printProperty("mu_2_nMDTEOHits", mu_nMDTEOHits->at(bii));
	printProperty("mu_2_nMDTEEHits", mu_nMDTEEHits->at(bii));
	printProperty("mu_2_nRPCLayer1EtaHits", mu_nRPCLayer1EtaHits->at(bii));
	printProperty("mu_2_nRPCLayer2EtaHits", mu_nRPCLayer2EtaHits->at(bii));
	printProperty("mu_2_nRPCLayer3EtaHits", mu_nRPCLayer3EtaHits->at(bii));
	printProperty("mu_2_nRPCLayer1PhiHits", mu_nRPCLayer1PhiHits->at(bii));
	printProperty("mu_2_nRPCLayer2PhiHits", mu_nRPCLayer2PhiHits->at(bii));
	printProperty("mu_2_nRPCLayer3PhiHits", mu_nRPCLayer3PhiHits->at(bii));
	printProperty("mu_2_nTGCLayer1EtaHits", mu_nTGCLayer1EtaHits->at(bii));
	printProperty("mu_2_nTGCLayer2EtaHits", mu_nTGCLayer2EtaHits->at(bii));
	printProperty("mu_2_nTGCLayer3EtaHits", mu_nTGCLayer3EtaHits->at(bii));
	printProperty("mu_2_nTGCLayer4EtaHits", mu_nTGCLayer4EtaHits->at(bii));
	printProperty("mu_2_nTGCLayer1PhiHits", mu_nTGCLayer1PhiHits->at(bii));
	printProperty("mu_2_nTGCLayer2PhiHits", mu_nTGCLayer2PhiHits->at(bii));
	printProperty("mu_2_nTGCLayer3PhiHits", mu_nTGCLayer3PhiHits->at(bii));
	printProperty("mu_2_nTGCLayer4PhiHits", mu_nTGCLayer4PhiHits->at(bii));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void analysisSkeleton::fillSingleAfterCuts()
{
	graphicObjects::RunNumber = RunNumber;
	graphicObjects::EventNumber = EventNumber;
	graphicObjects::timestamp = timestamp;
	graphicObjects::timestamp_ns = timestamp_ns;
	graphicObjects::lbn = lbn;
	graphicObjects::bcid = bcid;
	
	graphicObjects::actualIntPerXing  = actualIntPerXing;
	graphicObjects::averageIntPerXing = averageIntPerXing;
	if(AS_isMC)
	{
		graphicObjects::mc_channel_number = mc_channel_number;
		graphicObjects::mc_event_number   = mc_event_number;
		graphicObjects::mc_event_weight   = mc_event_weight;

		graphicObjects::pileup_weight      = pileup_weight;
		graphicObjects::intime_pileup_weight = intime_pileup_weight;
		graphicObjects::outoftime_pileup_weight = outoftime_pileup_weight;
		graphicObjects::lumi_pileup_weight = lumi_pileup_weight;
		graphicObjects::EW_kfactor_weight  = EW_kfactor_weight;
		graphicObjects::QCD_kfactor_weight = QCD_kfactor_weight;
		graphicObjects::mcevent_weight     = mcevent_weight;
		graphicObjects::total_weight       = total_weight;
		graphicObjects::randomized_decision = randomized_decision;
	}
	
	graphicObjects::ivxp            = current_ivertex;
	
	_DEBUG("");

	// all cuts - vectors
	graphicObjects::graphicObjects::vxp_n = vxp_n;
	graphicObjects::vxp_nTracks->push_back(vxp_nTracks->at(current_ivertex));
	graphicObjects::vxp_type->push_back(vxp_type->at(current_ivertex));
	graphicObjects::vxp_z->push_back(vxp_z->at(current_ivertex));
	
	_DEBUG("");
	
	int muSize = (int)mu_pt->size();
	for(int mu=0 ; mu<muSize ; mu++)
	{
		///////////////////////////////////
		if(!muQAflags[mu]) continue; //////
		///////////////////////////////////
		
		graphicObjects::n = mu_n;
		graphicObjects::E->push_back(mu_E->at(mu));
		graphicObjects::pt->push_back(mu_pt->at(mu));
		graphicObjects::m->push_back(mu_m->at(mu));
		graphicObjects::eta->push_back(mu_eta->at(mu));
		graphicObjects::phi->push_back(mu_phi->at(mu));
		graphicObjects::px->push_back(mu_px->at(mu));
		graphicObjects::py->push_back(mu_py->at(mu));
		graphicObjects::pz->push_back(mu_pz->at(mu));
		graphicObjects::charge->push_back(mu_charge->at(mu));
		graphicObjects::allauthor->push_back(mu_allauthor->at(mu));
		graphicObjects::author->push_back(mu_author->at(mu));
		graphicObjects::beta->push_back(mu_beta->at(mu));
		graphicObjects::isMuonLikelihood->push_back(mu_isMuonLikelihood->at(mu));
		
		_DEBUG("");

		graphicObjects::matchchi2->push_back(mu_matchchi2->at(mu));
		graphicObjects::matchndof->push_back(mu_matchndof->at(mu));
		graphicObjects::etcone20->push_back(mu_etcone20->at(mu));
		graphicObjects::etcone30->push_back(mu_etcone30->at(mu));
		graphicObjects::etcone40->push_back(mu_etcone40->at(mu));
		graphicObjects::nucone20->push_back(mu_nucone20->at(mu));
		graphicObjects::nucone30->push_back(mu_nucone30->at(mu));
		graphicObjects::nucone40->push_back(mu_nucone40->at(mu));
		graphicObjects::ptcone20->push_back(mu_ptcone20->at(mu));
		graphicObjects::ptcone30->push_back(mu_ptcone30->at(mu));
		graphicObjects::ptcone40->push_back(mu_ptcone40->at(mu));
		graphicObjects::energyLossPar->push_back(mu_energyLossPar->at(mu));
		graphicObjects::energyLossErr->push_back(mu_energyLossErr->at(mu));
		graphicObjects::etCore->push_back(mu_etCore->at(mu));

		_DEBUG("");

		graphicObjects::energyLossType->push_back(mu_energyLossType->at(mu));
		graphicObjects::caloMuonIdTag->push_back(mu_caloMuonIdTag->at(mu));
		graphicObjects::caloLRLikelihood->push_back(mu_caloLRLikelihood->at(mu));
		graphicObjects::bestMatch->push_back(mu_bestMatch->at(mu));
		graphicObjects::isStandAloneMuon->push_back(mu_isStandAloneMuon->at(mu));
		graphicObjects::isCombinedMuon->push_back(mu_isCombinedMuon->at(mu));
		graphicObjects::isLowPtReconstructedMuon->push_back(mu_isLowPtReconstructedMuon->at(mu));
		graphicObjects::loose->push_back(mu_loose->at(mu));
		graphicObjects::medium->push_back(mu_medium->at(mu));
		graphicObjects::tight->push_back(mu_tight->at(mu));
		graphicObjects::d0_exPV->push_back(mu_d0_exPV->at(mu));
		graphicObjects::z0_exPV->push_back(mu_z0_exPV->at(mu));
		graphicObjects::phi_exPV->push_back(mu_phi_exPV->at(mu));
		graphicObjects::theta_exPV->push_back(mu_theta_exPV->at(mu));
		graphicObjects::qoverp_exPV->push_back(mu_qoverp_exPV->at(mu));
		graphicObjects::cb_d0_exPV->push_back(mu_cb_d0_exPV->at(mu));
		graphicObjects::cb_z0_exPV->push_back(mu_cb_z0_exPV->at(mu));
		graphicObjects::cb_phi_exPV->push_back(mu_cb_phi_exPV->at(mu));
		graphicObjects::cb_theta_exPV->push_back(mu_cb_theta_exPV->at(mu));
		graphicObjects::cb_qoverp_exPV->push_back(mu_cb_qoverp_exPV->at(mu));
		graphicObjects::id_d0_exPV->push_back(mu_id_d0_exPV->at(mu));
		graphicObjects::id_z0_exPV->push_back(mu_id_z0_exPV->at(mu));

		_DEBUG("");

		graphicObjects::id_phi_exPV->push_back(mu_id_phi_exPV->at(mu));
		graphicObjects::id_theta_exPV->push_back(mu_id_theta_exPV->at(mu));
		graphicObjects::id_qoverp_exPV->push_back(mu_id_qoverp_exPV->at(mu));
		graphicObjects::me_d0_exPV->push_back(mu_me_d0_exPV->at(mu));
		graphicObjects::me_z0_exPV->push_back(mu_me_z0_exPV->at(mu));
		graphicObjects::me_phi_exPV->push_back(mu_me_phi_exPV->at(mu));
		graphicObjects::me_theta_exPV->push_back(mu_me_theta_exPV->at(mu));
		graphicObjects::me_qoverp_exPV->push_back(mu_me_qoverp_exPV->at(mu));
		graphicObjects::ie_d0_exPV->push_back(mu_ie_d0_exPV->at(mu));
		graphicObjects::ie_z0_exPV->push_back(mu_ie_z0_exPV->at(mu));
		graphicObjects::ie_phi_exPV->push_back(mu_ie_phi_exPV->at(mu));
		graphicObjects::ie_theta_exPV->push_back(mu_ie_theta_exPV->at(mu));
		graphicObjects::ie_qoverp_exPV->push_back(mu_ie_qoverp_exPV->at(mu));
		//graphicObjects::TileCellEnergyLayer1->push_back(mu_TileCellEnergyLayer1->at(mu));
		//graphicObjects::TileTimeLayer1->push_back(mu_TileTimeLayer1->at(mu));

		_DEBUG("");

		/*
		graphicObjects::TileCellRmsNoiseLayer1->push_back(mu_TileCellRmsNoiseLayer1->at(mu));
		graphicObjects::TileCellSignLayer1->push_back(mu_TileCellSignLayer1->at(mu));
		graphicObjects::TileCellEnergyLayer2->push_back(mu_TileCellEnergyLayer2->at(mu));
		graphicObjects::TileTimeLayer2->push_back(mu_TileTimeLayer2->at(mu));
		graphicObjects::TileCellRmsNoiseLayer2->push_back(mu_TileCellRmsNoiseLayer2->at(mu));
		graphicObjects::TileCellSignLayer2->push_back(mu_TileCellSignLayer2->at(mu));
		graphicObjects::TileCellEnergyLayer3->push_back(mu_TileCellEnergyLayer3->at(mu));
		graphicObjects::TileTimeLayer3->push_back(mu_TileTimeLayer3->at(mu));
		graphicObjects::TileCellRmsNoiseLayer3->push_back(mu_TileCellRmsNoiseLayer3->at(mu));
		graphicObjects::TileCellSignLayer3->push_back(mu_TileCellSignLayer3->at(mu));
		graphicObjects::MSTrkT0_1->push_back(mu_MSTrkT0_1->at(mu));
		graphicObjects::MSTrkT0_2->push_back(mu_MSTrkT0_2->at(mu));
		graphicObjects::MSTrkT0_3->push_back(mu_MSTrkT0_3->at(mu));
		*/
		graphicObjects::cov_d0_exPV->push_back(mu_cov_d0_exPV->at(mu));
		graphicObjects::cov_z0_exPV->push_back(mu_cov_z0_exPV->at(mu));
		graphicObjects::cov_phi_exPV->push_back(mu_cov_phi_exPV->at(mu));
		graphicObjects::cov_theta_exPV->push_back(mu_cov_theta_exPV->at(mu));

		_DEBUG("");

		graphicObjects::cov_qoverp_exPV->push_back(mu_cov_qoverp_exPV->at(mu));
		graphicObjects::cov_d0_z0_exPV->push_back(mu_cov_d0_z0_exPV->at(mu));
		graphicObjects::cov_d0_phi_exPV->push_back(mu_cov_d0_phi_exPV->at(mu));

		_DEBUG("");

		graphicObjects::cov_d0_theta_exPV->push_back(mu_cov_d0_theta_exPV->at(mu));
		graphicObjects::cov_d0_qoverp_exPV->push_back(mu_cov_d0_qoverp_exPV->at(mu));
		graphicObjects::cov_z0_phi_exPV->push_back(mu_cov_z0_phi_exPV->at(mu));
		graphicObjects::cov_z0_theta_exPV->push_back(mu_cov_z0_theta_exPV->at(mu));
		graphicObjects::cov_z0_qoverp_exPV->push_back(mu_cov_z0_qoverp_exPV->at(mu));
		graphicObjects::cov_phi_theta_exPV->push_back(mu_cov_phi_theta_exPV->at(mu));
		graphicObjects::cov_phi_qoverp_exPV->push_back(mu_cov_phi_qoverp_exPV->at(mu));
		graphicObjects::cov_theta_qoverp_exPV->push_back(mu_cov_theta_qoverp_exPV->at(mu));
		graphicObjects::id_cov_d0_exPV->push_back(mu_id_cov_d0_exPV->at(mu));
		graphicObjects::id_cov_z0_exPV->push_back(mu_id_cov_z0_exPV->at(mu));
		graphicObjects::id_cov_phi_exPV->push_back(mu_id_cov_phi_exPV->at(mu));
		graphicObjects::id_cov_theta_exPV->push_back(mu_id_cov_theta_exPV->at(mu));
		graphicObjects::id_cov_qoverp_exPV->push_back(mu_id_cov_qoverp_exPV->at(mu));
		graphicObjects::id_cov_d0_z0_exPV->push_back(mu_id_cov_d0_z0_exPV->at(mu));
		graphicObjects::id_cov_d0_phi_exPV->push_back(mu_id_cov_d0_phi_exPV->at(mu));
		graphicObjects::id_cov_d0_theta_exPV->push_back(mu_id_cov_d0_theta_exPV->at(mu));
		graphicObjects::id_cov_d0_qoverp_exPV->push_back(mu_id_cov_d0_qoverp_exPV->at(mu));
		graphicObjects::id_cov_z0_phi_exPV->push_back(mu_id_cov_z0_phi_exPV->at(mu));

		_DEBUG("");

		graphicObjects::id_cov_z0_theta_exPV->push_back(mu_id_cov_z0_theta_exPV->at(mu));
		graphicObjects::id_cov_z0_qoverp_exPV->push_back(mu_id_cov_z0_qoverp_exPV->at(mu));
		graphicObjects::id_cov_phi_theta_exPV->push_back(mu_id_cov_phi_theta_exPV->at(mu));
		graphicObjects::id_cov_phi_qoverp_exPV->push_back(mu_id_cov_phi_qoverp_exPV->at(mu));
		graphicObjects::id_cov_theta_qoverp_exPV->push_back(mu_id_cov_theta_qoverp_exPV->at(mu));
		graphicObjects::me_cov_d0_exPV->push_back(mu_me_cov_d0_exPV->at(mu));
		graphicObjects::me_cov_z0_exPV->push_back(mu_me_cov_z0_exPV->at(mu));
		graphicObjects::me_cov_phi_exPV->push_back(mu_me_cov_phi_exPV->at(mu));
		graphicObjects::me_cov_theta_exPV->push_back(mu_me_cov_theta_exPV->at(mu));
		graphicObjects::me_cov_qoverp_exPV->push_back(mu_me_cov_qoverp_exPV->at(mu));
		graphicObjects::me_cov_d0_z0_exPV->push_back(mu_me_cov_d0_z0_exPV->at(mu));
		graphicObjects::me_cov_d0_phi_exPV->push_back(mu_me_cov_d0_phi_exPV->at(mu));
		graphicObjects::me_cov_d0_theta_exPV->push_back(mu_me_cov_d0_theta_exPV->at(mu));
		graphicObjects::me_cov_d0_qoverp_exPV->push_back(mu_me_cov_d0_qoverp_exPV->at(mu));
		graphicObjects::me_cov_z0_phi_exPV->push_back(mu_me_cov_z0_phi_exPV->at(mu));
		graphicObjects::me_cov_z0_theta_exPV->push_back(mu_me_cov_z0_theta_exPV->at(mu));
		graphicObjects::me_cov_z0_qoverp_exPV->push_back(mu_me_cov_z0_qoverp_exPV->at(mu));
		graphicObjects::me_cov_phi_theta_exPV->push_back(mu_me_cov_phi_theta_exPV->at(mu));
		graphicObjects::me_cov_phi_qoverp_exPV->push_back(mu_me_cov_phi_qoverp_exPV->at(mu));
		graphicObjects::me_cov_theta_qoverp_exPV->push_back(mu_me_cov_theta_qoverp_exPV->at(mu));

		_DEBUG("");

		graphicObjects::ms_d0->push_back(mu_ms_d0->at(mu));
		graphicObjects::ms_z0->push_back(mu_ms_z0->at(mu));
		graphicObjects::ms_phi->push_back(mu_ms_phi->at(mu));
		graphicObjects::ms_theta->push_back(mu_ms_theta->at(mu));
		graphicObjects::ms_qoverp->push_back(mu_ms_qoverp->at(mu));
		graphicObjects::id_d0->push_back(mu_id_d0->at(mu));
		graphicObjects::id_z0->push_back(mu_id_z0->at(mu));
		graphicObjects::id_phi->push_back(mu_id_phi->at(mu));
		graphicObjects::id_theta->push_back(mu_id_theta->at(mu));
		graphicObjects::id_qoverp->push_back(mu_id_qoverp->at(mu));
		graphicObjects::me_d0->push_back(mu_me_d0->at(mu));
		graphicObjects::me_z0->push_back(mu_me_z0->at(mu));
		graphicObjects::me_phi->push_back(mu_me_phi->at(mu));
		graphicObjects::me_theta->push_back(mu_me_theta->at(mu));
		graphicObjects::me_qoverp->push_back(mu_me_qoverp->at(mu));
		graphicObjects::ie_d0->push_back(mu_ie_d0->at(mu));
		graphicObjects::ie_z0->push_back(mu_ie_z0->at(mu));

		_DEBUG("");

		graphicObjects::ie_phi->push_back(mu_ie_phi->at(mu));
		graphicObjects::ie_theta->push_back(mu_ie_theta->at(mu));
		graphicObjects::ie_qoverp->push_back(mu_ie_qoverp->at(mu));
		graphicObjects::nOutliersOnTrack->push_back(mu_nOutliersOnTrack->at(mu));
		graphicObjects::nBLHits->push_back(mu_nBLHits->at(mu));
		graphicObjects::nPixHits->push_back(mu_nPixHits->at(mu));
		graphicObjects::nSCTHits->push_back(mu_nSCTHits->at(mu));
		graphicObjects::nTRTHits->push_back(mu_nTRTHits->at(mu));
		graphicObjects::nTRTHighTHits->push_back(mu_nTRTHighTHits->at(mu));
		graphicObjects::nBLSharedHits->push_back(mu_nBLSharedHits->at(mu));
		graphicObjects::nPixSharedHits->push_back(mu_nPixSharedHits->at(mu));
		graphicObjects::nPixHoles->push_back(mu_nPixHoles->at(mu));
		graphicObjects::nSCTSharedHits->push_back(mu_nSCTSharedHits->at(mu));
		graphicObjects::nSCTHoles->push_back(mu_nSCTHoles->at(mu));
		graphicObjects::nTRTOutliers->push_back(mu_nTRTOutliers->at(mu));
		graphicObjects::nTRTHighTOutliers->push_back(mu_nTRTHighTOutliers->at(mu));
		graphicObjects::nGangedPixels->push_back(mu_nGangedPixels->at(mu));
		graphicObjects::nPixelDeadSensors->push_back(mu_nPixelDeadSensors->at(mu));

		_DEBUG("");

		graphicObjects::nSCTDeadSensors->push_back(mu_nSCTDeadSensors->at(mu));
		graphicObjects::nTRTDeadStraws->push_back(mu_nTRTDeadStraws->at(mu));
		graphicObjects::expectBLayerHit->push_back(mu_expectBLayerHit->at(mu));
		graphicObjects::nMDTHits->push_back(mu_nMDTHits->at(mu));
		graphicObjects::nMDTHoles->push_back(mu_nMDTHoles->at(mu));
		graphicObjects::nCSCEtaHits->push_back(mu_nCSCEtaHits->at(mu));
		graphicObjects::nCSCEtaHoles->push_back(mu_nCSCEtaHoles->at(mu));
		graphicObjects::nCSCPhiHits->push_back(mu_nCSCPhiHits->at(mu));
		graphicObjects::nCSCPhiHoles->push_back(mu_nCSCPhiHoles->at(mu));
		graphicObjects::nRPCEtaHits->push_back(mu_nRPCEtaHits->at(mu));
		graphicObjects::nRPCEtaHoles->push_back(mu_nRPCEtaHoles->at(mu));
		graphicObjects::nRPCPhiHits->push_back(mu_nRPCPhiHits->at(mu));
		graphicObjects::nRPCPhiHoles->push_back(mu_nRPCPhiHoles->at(mu));
		graphicObjects::nTGCEtaHits->push_back(mu_nTGCEtaHits->at(mu));
		graphicObjects::nTGCEtaHoles->push_back(mu_nTGCEtaHoles->at(mu));
		graphicObjects::nTGCPhiHits->push_back(mu_nTGCPhiHits->at(mu));
		graphicObjects::nTGCPhiHoles->push_back(mu_nTGCPhiHoles->at(mu));
		graphicObjects::nMDTBIHits->push_back(mu_nMDTBIHits->at(mu));
		graphicObjects::nMDTBMHits->push_back(mu_nMDTBMHits->at(mu));
		graphicObjects::nMDTBOHits->push_back(mu_nMDTBOHits->at(mu));

		_DEBUG("");

		graphicObjects::nMDTBEEHits->push_back(mu_nMDTBEEHits->at(mu));
		graphicObjects::nMDTBIS78Hits->push_back(mu_nMDTBIS78Hits->at(mu));
		graphicObjects::nMDTEIHits->push_back(mu_nMDTEIHits->at(mu));
		graphicObjects::nMDTEMHits->push_back(mu_nMDTEMHits->at(mu));
		graphicObjects::nMDTEOHits->push_back(mu_nMDTEOHits->at(mu));
		graphicObjects::nMDTEEHits->push_back(mu_nMDTEEHits->at(mu));
		graphicObjects::nRPCLayer1EtaHits->push_back(mu_nRPCLayer1EtaHits->at(mu));
		graphicObjects::nRPCLayer2EtaHits->push_back(mu_nRPCLayer2EtaHits->at(mu));
		graphicObjects::nRPCLayer3EtaHits->push_back(mu_nRPCLayer3EtaHits->at(mu));
		graphicObjects::nRPCLayer1PhiHits->push_back(mu_nRPCLayer1PhiHits->at(mu));
		graphicObjects::nRPCLayer2PhiHits->push_back(mu_nRPCLayer2PhiHits->at(mu));
		graphicObjects::nRPCLayer3PhiHits->push_back(mu_nRPCLayer3PhiHits->at(mu));
		graphicObjects::nTGCLayer1EtaHits->push_back(mu_nTGCLayer1EtaHits->at(mu));
		graphicObjects::nTGCLayer2EtaHits->push_back(mu_nTGCLayer2EtaHits->at(mu));
		graphicObjects::nTGCLayer3EtaHits->push_back(mu_nTGCLayer3EtaHits->at(mu));
		graphicObjects::nTGCLayer4EtaHits->push_back(mu_nTGCLayer4EtaHits->at(mu));
		graphicObjects::nTGCLayer1PhiHits->push_back(mu_nTGCLayer1PhiHits->at(mu));
		graphicObjects::nTGCLayer2PhiHits->push_back(mu_nTGCLayer2PhiHits->at(mu));
		graphicObjects::nTGCLayer3PhiHits->push_back(mu_nTGCLayer3PhiHits->at(mu));
		graphicObjects::nTGCLayer4PhiHits->push_back(mu_nTGCLayer4PhiHits->at(mu));

		_DEBUG("");

		graphicObjects::barrelSectors->push_back(mu_barrelSectors->at(mu));
		graphicObjects::endcapSectors->push_back(mu_endcapSectors->at(mu));
		graphicObjects::trackd0->push_back(mu_trackd0->at(mu));
		graphicObjects::trackz0->push_back(mu_trackz0->at(mu));
		graphicObjects::trackphi->push_back(mu_trackphi->at(mu));
		graphicObjects::tracktheta->push_back(mu_tracktheta->at(mu));
		graphicObjects::trackqoverp->push_back(mu_trackqoverp->at(mu));
		graphicObjects::trackcov_d0->push_back(mu_trackcov_d0->at(mu));
		graphicObjects::trackcov_z0->push_back(mu_trackcov_z0->at(mu));
		graphicObjects::trackcov_phi->push_back(mu_trackcov_phi->at(mu));
		graphicObjects::trackcov_theta->push_back(mu_trackcov_theta->at(mu));
		graphicObjects::trackcov_qoverp->push_back(mu_trackcov_qoverp->at(mu));
		graphicObjects::trackcov_d0_z0->push_back(mu_trackcov_d0_z0->at(mu));
		graphicObjects::trackcov_d0_phi->push_back(mu_trackcov_d0_phi->at(mu));
		graphicObjects::trackcov_d0_theta->push_back(mu_trackcov_d0_theta->at(mu));
		graphicObjects::trackcov_d0_qoverp->push_back(mu_trackcov_d0_qoverp->at(mu));
		graphicObjects::trackcov_z0_phi->push_back(mu_trackcov_z0_phi->at(mu));
		graphicObjects::trackcov_z0_theta->push_back(mu_trackcov_z0_theta->at(mu));
		graphicObjects::trackcov_z0_qoverp->push_back(mu_trackcov_z0_qoverp->at(mu));
		graphicObjects::trackcov_phi_theta->push_back(mu_trackcov_phi_theta->at(mu));
		graphicObjects::trackcov_phi_qoverp->push_back(mu_trackcov_phi_qoverp->at(mu));
		graphicObjects::trackcov_theta_qoverp->push_back(mu_trackcov_theta_qoverp->at(mu));
		graphicObjects::trackfitchi2->push_back(mu_trackfitchi2->at(mu));
		graphicObjects::trackfitndof->push_back(mu_trackfitndof->at(mu));
		graphicObjects::hastrack->push_back(mu_hastrack->at(mu));

		_DEBUG("");

		if(AS_isMC)
		{
			graphicObjects::truth_dr->push_back(mu_truth_dr->at(mu));
			graphicObjects::truth_E->push_back(mu_truth_E->at(mu));
			graphicObjects::truth_pt->push_back(mu_truth_pt->at(mu));
			graphicObjects::truth_eta->push_back(mu_truth_eta->at(mu));
			graphicObjects::truth_phi->push_back(mu_truth_phi->at(mu));
			graphicObjects::truth_type->push_back(mu_truth_type->at(mu));
			graphicObjects::truth_status->push_back(mu_truth_status->at(mu));
			graphicObjects::truth_barcode->push_back(mu_truth_barcode->at(mu));
			graphicObjects::truth_mothertype->push_back(mu_truth_mothertype->at(mu));
			graphicObjects::truth_motherbarcode->push_back(mu_truth_motherbarcode->at(mu));
			graphicObjects::truth_matched->push_back(mu_truth_matched->at(mu));
		}

		_DEBUG("");

		graphicObjects::EFCB_dr->push_back(mu_EFCB_dr->at(mu));
		graphicObjects::EFCB_index->push_back(mu_EFCB_index->at(mu));
		graphicObjects::EFMG_dr->push_back(mu_EFMG_dr->at(mu));
		graphicObjects::EFMG_index->push_back(mu_EFMG_index->at(mu));
		graphicObjects::EFME_dr->push_back(mu_EFME_dr->at(mu));
		graphicObjects::EFME_index->push_back(mu_EFME_index->at(mu));
		graphicObjects::L2CB_dr->push_back(mu_L2CB_dr->at(mu));
		graphicObjects::L2CB_index->push_back(mu_L2CB_index->at(mu));
		graphicObjects::L1_dr->push_back(mu_L1_dr->at(mu));
		graphicObjects::L1_index->push_back(mu_L1_index->at(mu));
	}
	
	_DEBUG("");

	/////////////////////////////////////////////////////
	// fill the all cuts tree ///////////////////////////
	tree_allCuts->Fill(); ///////////////////////////////
	if(m_allCuts_counter%m_trees_counter_mod==0) ////////
	{                             ///////////////////////
		tree_allCuts->FlushBaskets(); ///////////////////
		//tree_allCuts->Write("", TObject::kOverwrite); ///
	} ///////////////////////////////////////////////////
	m_allCuts_counter++; ////////////////////////////////
	/////////////////////////////////////////////////////
	
	_DEBUG("");
}


void analysisSkeleton::fillAfterCuts()
{
	_DEBUG("analysisSkeleton::fillAfterCuts");
	
	int lead_mu     = ai;
	int sublead_mu  = bi;
	if( mu_pt->at(ai) < mu_pt->at(bi) )
	{
		lead_mu     = bi;
		sublead_mu  = ai;
	}
	vi = getPVindex();

	_DEBUG("");

	current_mu_me_pT     = pT(mu_me_qoverp->at(lead_mu),mu_me_theta->at(lead_mu))*MeV2TeV;
	current_muplus_me_pT = pT(mu_me_qoverp->at(sublead_mu),mu_me_theta->at(sublead_mu))*MeV2TeV;
	current_mu_id_pT     = pT(mu_id_qoverp->at(lead_mu),mu_id_theta->at(lead_mu))*MeV2TeV;
	current_muplus_id_pT = pT(mu_id_qoverp->at(sublead_mu),mu_id_theta->at(sublead_mu))*MeV2TeV;
	current_mu_pT        = mu_pt->at(lead_mu)*MeV2TeV;
	current_muplus_pT    = mu_pt->at(sublead_mu)*MeV2TeV;
	current_mu_eta       = mu_eta->at(lead_mu);
	current_muplus_eta   = mu_eta->at(sublead_mu);
	current_mu_me_qop    = mu_me_qoverp->at(lead_mu)*MeV2TeV;
	current_muplus_me_qop = mu_me_qoverp->at(sublead_mu)*MeV2TeV;
	current_mu_id_qop     = mu_id_qoverp->at(lead_mu)*MeV2TeV;
	current_muplus_id_qop = mu_me_qoverp->at(sublead_mu)*MeV2TeV;
	current_mu_me_theta     = mu_me_theta->at(lead_mu);
	current_muplus_me_theta = mu_me_theta->at(sublead_mu);;
	current_mu_id_theta     = mu_id_theta->at(lead_mu);;
	current_muplus_id_theta = mu_id_theta->at(sublead_mu);;
	
	_DEBUG("");

	current_imass       = imass(pmu[lead_mu],pmu[sublead_mu]);
	current_cosTheta    = cosThetaCollinsSoper( pmu[lead_mu], mu_charge->at(lead_mu), pmu[sublead_mu], mu_charge->at(sublead_mu) );
	current_cosThetaCS  = cosThetaCollinsSoper( pmu[lead_mu], mu_charge->at(lead_mu), pmu[sublead_mu], mu_charge->at(sublead_mu) );
	current_cosThetaHE  = cosThetaBoost( pmu[lead_mu], mu_charge->at(lead_mu), pmu[sublead_mu], mu_charge->at(sublead_mu) );
	current_ySystem     = ySystem( pmu[lead_mu], pmu[sublead_mu] );
	current_QT          = QT( pmu[lead_mu], pmu[sublead_mu] );
	current_cosmicCosth = cosThetaDimu(pmu[lead_mu],pmu[sublead_mu]);
	current_ipTdiff     = (current_muplus_pT!=0.  &&  current_mu_pT!=0.) ? 1./current_muplus_pT-1./current_mu_pT : -999.;
	current_ivertex     = vi;
	current_etaSum      = current_muplus_eta + current_mu_eta;
	current_betaQ       = magBetaSystem(pmu[lead_mu],pmu[sublead_mu]);
	current_betazQ      = betaiSystem(pmu[lead_mu],pmu[sublead_mu],3);
	current_betaTQ      = betaTSystem(pmu[lead_mu],pmu[sublead_mu]);
	
	_DEBUG("");

	current_pTdiff      = current_mu_me_pT - current_mu_id_pT;
	current_pTdiff_muplus  = current_muplus_me_pT - current_muplus_id_pT;
	current_pTratio        = (current_mu_id_pT!=0.) ? fabs( current_mu_me_pT / current_mu_id_pT ) : -999.;
	current_pTres          = (current_mu_id_pT!=0.) ? (current_mu_me_pT-current_mu_id_pT)/current_mu_id_pT : -999.;
	current_pTratio_muplus = (current_muplus_id_pT!=0.) ? fabs( current_muplus_me_pT / current_muplus_id_pT ) : -999.;
	current_pTres_muplus   = (current_muplus_id_pT!=0.) ? (current_muplus_me_pT-current_muplus_id_pT)/current_muplus_id_pT : -999.;
	
	_DEBUG("");
	
	if(current_imass>=XMIN  &&  current_imass<=XMAX) { h1_costh->Fill( current_cosTheta ); }
	h1_cosmicCosthAllCuts->Fill( current_cosmicCosth );
	h1_eta->Fill(                current_mu_eta );
	h1_eta_muplus->Fill(         current_muplus_eta );
	h1_ipTdiff->Fill(            current_ipTdiff );
	h1_etaSum->Fill(             current_etaSum );
	h1_imass->Fill(              current_imass );
	h1_imassFit->Fill(           current_imass );
	h1_pT->Fill(                 current_mu_pT );
	h1_pT_muplus->Fill(          current_muplus_pT );
	h1_pTdiff->Fill( current_pTdiff );
	h1_pTdiff_muplus->Fill( current_pTdiff_muplus );
	h1_pTratio->Fill( current_pTratio );
	h1_pTratio_muplus->Fill( current_pTratio_muplus );
	h1_pTres->Fill( current_pTres );
	h1_pTres_muplus->Fill( current_pTres_muplus );
	h2_pTmevspTid->Fill( current_mu_me_pT, current_mu_id_pT );
	h2_pTmevspTid_muplus->Fill( current_muplus_me_pT, current_muplus_id_pT );
	
	_DEBUG("");
	
	/////////////////////////////////////////////////
	// fill the graphicObjects all cuts tree ////////
	graphicObjects::RunNumber = RunNumber;
	graphicObjects::EventNumber = EventNumber;
	graphicObjects::timestamp = timestamp;
	graphicObjects::timestamp_ns = timestamp_ns;
	graphicObjects::lbn = lbn;
	graphicObjects::bcid = bcid;
	
	graphicObjects::actualIntPerXing  = actualIntPerXing;
	graphicObjects::averageIntPerXing = averageIntPerXing;
	if(AS_isMC)
	{
		graphicObjects::mc_channel_number = mc_channel_number;
		graphicObjects::mc_event_number   = mc_event_number;
		graphicObjects::mc_event_weight   = mc_event_weight;

		graphicObjects::pileup_weight      = pileup_weight;
		graphicObjects::intime_pileup_weight = intime_pileup_weight;
		graphicObjects::outoftime_pileup_weight = outoftime_pileup_weight;
		graphicObjects::lumi_pileup_weight = lumi_pileup_weight;
		graphicObjects::EW_kfactor_weight  = EW_kfactor_weight;
		graphicObjects::QCD_kfactor_weight = QCD_kfactor_weight;
		graphicObjects::mcevent_weight     = mcevent_weight;
		graphicObjects::total_weight       = total_weight;
		graphicObjects::randomized_decision = randomized_decision;
	}
	
	graphicObjects::ivxp            = current_ivertex;
	graphicObjects::iLeadingMuon    = lead_mu;
	graphicObjects::iSubLeadingMuon = sublead_mu;
	
	_DEBUG("");

	// all cuts - vectors
	graphicObjects::graphicObjects::vxp_n = vxp_n;
	graphicObjects::vxp_nTracks->push_back(vxp_nTracks->at(current_ivertex));
	graphicObjects::vxp_type->push_back(vxp_type->at(current_ivertex));
	graphicObjects::vxp_z->push_back(vxp_z->at(current_ivertex));
	
	graphicObjects::Mhat         = current_imass;
	graphicObjects::CosThetaCS   = current_cosThetaCS;
	graphicObjects::CosThetaHE   = current_cosThetaHE;
	graphicObjects::Ysystem      = current_ySystem;
	graphicObjects::Q_T          = current_QT;
	graphicObjects::betaQ        = current_betaQ;
	graphicObjects::betazQ       = current_betazQ;
	graphicObjects::betaTQ       = current_betaTQ;
	graphicObjects::CosThetaDimu = current_cosmicCosth;
	graphicObjects::ipTDiff      = current_ipTdiff;
	graphicObjects::EtaSum       = current_etaSum;
	
	_DEBUG("");

	graphicObjects::n = mu_n;
	graphicObjects::mutype->push_back(classify3332null[lead_mu]);
	graphicObjects::E->push_back(mu_E->at(lead_mu));
	graphicObjects::pt->push_back(mu_pt->at(lead_mu));
	graphicObjects::m->push_back(mu_m->at(lead_mu));
	graphicObjects::eta->push_back(mu_eta->at(lead_mu));
	graphicObjects::phi->push_back(mu_phi->at(lead_mu));
	graphicObjects::px->push_back(mu_px->at(lead_mu));
	graphicObjects::py->push_back(mu_py->at(lead_mu));
	graphicObjects::pz->push_back(mu_pz->at(lead_mu));
	graphicObjects::charge->push_back(mu_charge->at(lead_mu));
	graphicObjects::allauthor->push_back(mu_allauthor->at(lead_mu));
	graphicObjects::author->push_back(mu_author->at(lead_mu));
	graphicObjects::beta->push_back(mu_beta->at(lead_mu));
	graphicObjects::isMuonLikelihood->push_back(mu_isMuonLikelihood->at(lead_mu));
	
	_DEBUG("");

	graphicObjects::matchchi2->push_back(mu_matchchi2->at(lead_mu));
	graphicObjects::matchndof->push_back(mu_matchndof->at(lead_mu));
	graphicObjects::etcone20->push_back(mu_etcone20->at(lead_mu));
	graphicObjects::etcone30->push_back(mu_etcone30->at(lead_mu));
	graphicObjects::etcone40->push_back(mu_etcone40->at(lead_mu));
	graphicObjects::nucone20->push_back(mu_nucone20->at(lead_mu));
	graphicObjects::nucone30->push_back(mu_nucone30->at(lead_mu));
	graphicObjects::nucone40->push_back(mu_nucone40->at(lead_mu));
	graphicObjects::ptcone20->push_back(mu_ptcone20->at(lead_mu));
	graphicObjects::ptcone30->push_back(mu_ptcone30->at(lead_mu));
	graphicObjects::ptcone40->push_back(mu_ptcone40->at(lead_mu));
	graphicObjects::energyLossPar->push_back(mu_energyLossPar->at(lead_mu));
	graphicObjects::energyLossErr->push_back(mu_energyLossErr->at(lead_mu));
	graphicObjects::etCore->push_back(mu_etCore->at(lead_mu));

	_DEBUG("");

	graphicObjects::energyLossType->push_back(mu_energyLossType->at(lead_mu));
	graphicObjects::caloMuonIdTag->push_back(mu_caloMuonIdTag->at(lead_mu));
	graphicObjects::caloLRLikelihood->push_back(mu_caloLRLikelihood->at(lead_mu));
	graphicObjects::bestMatch->push_back(mu_bestMatch->at(lead_mu));
	graphicObjects::isStandAloneMuon->push_back(mu_isStandAloneMuon->at(lead_mu));
	graphicObjects::isCombinedMuon->push_back(mu_isCombinedMuon->at(lead_mu));
	graphicObjects::isLowPtReconstructedMuon->push_back(mu_isLowPtReconstructedMuon->at(lead_mu));
	graphicObjects::loose->push_back(mu_loose->at(lead_mu));
	graphicObjects::medium->push_back(mu_medium->at(lead_mu));
	graphicObjects::tight->push_back(mu_tight->at(lead_mu));
	graphicObjects::d0_exPV->push_back(mu_d0_exPV->at(lead_mu));
	graphicObjects::z0_exPV->push_back(mu_z0_exPV->at(lead_mu));
	graphicObjects::phi_exPV->push_back(mu_phi_exPV->at(lead_mu));
	graphicObjects::theta_exPV->push_back(mu_theta_exPV->at(lead_mu));
	graphicObjects::qoverp_exPV->push_back(mu_qoverp_exPV->at(lead_mu));
	graphicObjects::cb_d0_exPV->push_back(mu_cb_d0_exPV->at(lead_mu));
	graphicObjects::cb_z0_exPV->push_back(mu_cb_z0_exPV->at(lead_mu));
	graphicObjects::cb_phi_exPV->push_back(mu_cb_phi_exPV->at(lead_mu));
	graphicObjects::cb_theta_exPV->push_back(mu_cb_theta_exPV->at(lead_mu));
	graphicObjects::cb_qoverp_exPV->push_back(mu_cb_qoverp_exPV->at(lead_mu));
	graphicObjects::id_d0_exPV->push_back(mu_id_d0_exPV->at(lead_mu));
	graphicObjects::id_z0_exPV->push_back(mu_id_z0_exPV->at(lead_mu));

	_DEBUG("");

	graphicObjects::id_phi_exPV->push_back(mu_id_phi_exPV->at(lead_mu));
	graphicObjects::id_theta_exPV->push_back(mu_id_theta_exPV->at(lead_mu));
	graphicObjects::id_qoverp_exPV->push_back(mu_id_qoverp_exPV->at(lead_mu));
	graphicObjects::me_d0_exPV->push_back(mu_me_d0_exPV->at(lead_mu));
	graphicObjects::me_z0_exPV->push_back(mu_me_z0_exPV->at(lead_mu));
	graphicObjects::me_phi_exPV->push_back(mu_me_phi_exPV->at(lead_mu));
	graphicObjects::me_theta_exPV->push_back(mu_me_theta_exPV->at(lead_mu));
	graphicObjects::me_qoverp_exPV->push_back(mu_me_qoverp_exPV->at(lead_mu));
	graphicObjects::ie_d0_exPV->push_back(mu_ie_d0_exPV->at(lead_mu));
	graphicObjects::ie_z0_exPV->push_back(mu_ie_z0_exPV->at(lead_mu));
	graphicObjects::ie_phi_exPV->push_back(mu_ie_phi_exPV->at(lead_mu));
	graphicObjects::ie_theta_exPV->push_back(mu_ie_theta_exPV->at(lead_mu));
	graphicObjects::ie_qoverp_exPV->push_back(mu_ie_qoverp_exPV->at(lead_mu));
	//graphicObjects::TileCellEnergyLayer1->push_back(mu_TileCellEnergyLayer1->at(lead_mu));
	//graphicObjects::TileTimeLayer1->push_back(mu_TileTimeLayer1->at(lead_mu));

	_DEBUG("");

	/*
	graphicObjects::TileCellRmsNoiseLayer1->push_back(mu_TileCellRmsNoiseLayer1->at(lead_mu));
	graphicObjects::TileCellSignLayer1->push_back(mu_TileCellSignLayer1->at(lead_mu));
	graphicObjects::TileCellEnergyLayer2->push_back(mu_TileCellEnergyLayer2->at(lead_mu));
	graphicObjects::TileTimeLayer2->push_back(mu_TileTimeLayer2->at(lead_mu));
	graphicObjects::TileCellRmsNoiseLayer2->push_back(mu_TileCellRmsNoiseLayer2->at(lead_mu));
	graphicObjects::TileCellSignLayer2->push_back(mu_TileCellSignLayer2->at(lead_mu));
	graphicObjects::TileCellEnergyLayer3->push_back(mu_TileCellEnergyLayer3->at(lead_mu));
	graphicObjects::TileTimeLayer3->push_back(mu_TileTimeLayer3->at(lead_mu));
	graphicObjects::TileCellRmsNoiseLayer3->push_back(mu_TileCellRmsNoiseLayer3->at(lead_mu));
	graphicObjects::TileCellSignLayer3->push_back(mu_TileCellSignLayer3->at(lead_mu));
	graphicObjects::MSTrkT0_1->push_back(mu_MSTrkT0_1->at(lead_mu));
	graphicObjects::MSTrkT0_2->push_back(mu_MSTrkT0_2->at(lead_mu));
	graphicObjects::MSTrkT0_3->push_back(mu_MSTrkT0_3->at(lead_mu));
	*/
	graphicObjects::cov_d0_exPV->push_back(mu_cov_d0_exPV->at(lead_mu));
	graphicObjects::cov_z0_exPV->push_back(mu_cov_z0_exPV->at(lead_mu));
	graphicObjects::cov_phi_exPV->push_back(mu_cov_phi_exPV->at(lead_mu));
	graphicObjects::cov_theta_exPV->push_back(mu_cov_theta_exPV->at(lead_mu));

	_DEBUG("");

	graphicObjects::cov_qoverp_exPV->push_back(mu_cov_qoverp_exPV->at(lead_mu));
	graphicObjects::cov_d0_z0_exPV->push_back(mu_cov_d0_z0_exPV->at(lead_mu));
	graphicObjects::cov_d0_phi_exPV->push_back(mu_cov_d0_phi_exPV->at(lead_mu));

	_DEBUG("");

	graphicObjects::cov_d0_theta_exPV->push_back(mu_cov_d0_theta_exPV->at(lead_mu));
	graphicObjects::cov_d0_qoverp_exPV->push_back(mu_cov_d0_qoverp_exPV->at(lead_mu));
	graphicObjects::cov_z0_phi_exPV->push_back(mu_cov_z0_phi_exPV->at(lead_mu));
	graphicObjects::cov_z0_theta_exPV->push_back(mu_cov_z0_theta_exPV->at(lead_mu));
	graphicObjects::cov_z0_qoverp_exPV->push_back(mu_cov_z0_qoverp_exPV->at(lead_mu));
	graphicObjects::cov_phi_theta_exPV->push_back(mu_cov_phi_theta_exPV->at(lead_mu));
	graphicObjects::cov_phi_qoverp_exPV->push_back(mu_cov_phi_qoverp_exPV->at(lead_mu));
	graphicObjects::cov_theta_qoverp_exPV->push_back(mu_cov_theta_qoverp_exPV->at(lead_mu));
	graphicObjects::id_cov_d0_exPV->push_back(mu_id_cov_d0_exPV->at(lead_mu));
	graphicObjects::id_cov_z0_exPV->push_back(mu_id_cov_z0_exPV->at(lead_mu));
	graphicObjects::id_cov_phi_exPV->push_back(mu_id_cov_phi_exPV->at(lead_mu));
	graphicObjects::id_cov_theta_exPV->push_back(mu_id_cov_theta_exPV->at(lead_mu));
	graphicObjects::id_cov_qoverp_exPV->push_back(mu_id_cov_qoverp_exPV->at(lead_mu));
	graphicObjects::id_cov_d0_z0_exPV->push_back(mu_id_cov_d0_z0_exPV->at(lead_mu));
	graphicObjects::id_cov_d0_phi_exPV->push_back(mu_id_cov_d0_phi_exPV->at(lead_mu));
	graphicObjects::id_cov_d0_theta_exPV->push_back(mu_id_cov_d0_theta_exPV->at(lead_mu));
	graphicObjects::id_cov_d0_qoverp_exPV->push_back(mu_id_cov_d0_qoverp_exPV->at(lead_mu));
	graphicObjects::id_cov_z0_phi_exPV->push_back(mu_id_cov_z0_phi_exPV->at(lead_mu));

	_DEBUG("");

	graphicObjects::id_cov_z0_theta_exPV->push_back(mu_id_cov_z0_theta_exPV->at(lead_mu));
	graphicObjects::id_cov_z0_qoverp_exPV->push_back(mu_id_cov_z0_qoverp_exPV->at(lead_mu));
	graphicObjects::id_cov_phi_theta_exPV->push_back(mu_id_cov_phi_theta_exPV->at(lead_mu));
	graphicObjects::id_cov_phi_qoverp_exPV->push_back(mu_id_cov_phi_qoverp_exPV->at(lead_mu));
	graphicObjects::id_cov_theta_qoverp_exPV->push_back(mu_id_cov_theta_qoverp_exPV->at(lead_mu));
	graphicObjects::me_cov_d0_exPV->push_back(mu_me_cov_d0_exPV->at(lead_mu));
	graphicObjects::me_cov_z0_exPV->push_back(mu_me_cov_z0_exPV->at(lead_mu));
	graphicObjects::me_cov_phi_exPV->push_back(mu_me_cov_phi_exPV->at(lead_mu));
	graphicObjects::me_cov_theta_exPV->push_back(mu_me_cov_theta_exPV->at(lead_mu));
	graphicObjects::me_cov_qoverp_exPV->push_back(mu_me_cov_qoverp_exPV->at(lead_mu));
	graphicObjects::me_cov_d0_z0_exPV->push_back(mu_me_cov_d0_z0_exPV->at(lead_mu));
	graphicObjects::me_cov_d0_phi_exPV->push_back(mu_me_cov_d0_phi_exPV->at(lead_mu));
	graphicObjects::me_cov_d0_theta_exPV->push_back(mu_me_cov_d0_theta_exPV->at(lead_mu));
	graphicObjects::me_cov_d0_qoverp_exPV->push_back(mu_me_cov_d0_qoverp_exPV->at(lead_mu));
	graphicObjects::me_cov_z0_phi_exPV->push_back(mu_me_cov_z0_phi_exPV->at(lead_mu));
	graphicObjects::me_cov_z0_theta_exPV->push_back(mu_me_cov_z0_theta_exPV->at(lead_mu));
	graphicObjects::me_cov_z0_qoverp_exPV->push_back(mu_me_cov_z0_qoverp_exPV->at(lead_mu));
	graphicObjects::me_cov_phi_theta_exPV->push_back(mu_me_cov_phi_theta_exPV->at(lead_mu));
	graphicObjects::me_cov_phi_qoverp_exPV->push_back(mu_me_cov_phi_qoverp_exPV->at(lead_mu));
	graphicObjects::me_cov_theta_qoverp_exPV->push_back(mu_me_cov_theta_qoverp_exPV->at(lead_mu));

	_DEBUG("");

	graphicObjects::ms_d0->push_back(mu_ms_d0->at(lead_mu));
	graphicObjects::ms_z0->push_back(mu_ms_z0->at(lead_mu));
	graphicObjects::ms_phi->push_back(mu_ms_phi->at(lead_mu));
	graphicObjects::ms_theta->push_back(mu_ms_theta->at(lead_mu));
	graphicObjects::ms_qoverp->push_back(mu_ms_qoverp->at(lead_mu));
	graphicObjects::id_d0->push_back(mu_id_d0->at(lead_mu));
	graphicObjects::id_z0->push_back(mu_id_z0->at(lead_mu));
	graphicObjects::id_phi->push_back(mu_id_phi->at(lead_mu));
	graphicObjects::id_theta->push_back(mu_id_theta->at(lead_mu));
	graphicObjects::id_qoverp->push_back(mu_id_qoverp->at(lead_mu));
	graphicObjects::me_d0->push_back(mu_me_d0->at(lead_mu));
	graphicObjects::me_z0->push_back(mu_me_z0->at(lead_mu));
	graphicObjects::me_phi->push_back(mu_me_phi->at(lead_mu));
	graphicObjects::me_theta->push_back(mu_me_theta->at(lead_mu));
	graphicObjects::me_qoverp->push_back(mu_me_qoverp->at(lead_mu));
	graphicObjects::ie_d0->push_back(mu_ie_d0->at(lead_mu));
	graphicObjects::ie_z0->push_back(mu_ie_z0->at(lead_mu));

	_DEBUG("");

	graphicObjects::ie_phi->push_back(mu_ie_phi->at(lead_mu));
	graphicObjects::ie_theta->push_back(mu_ie_theta->at(lead_mu));
	graphicObjects::ie_qoverp->push_back(mu_ie_qoverp->at(lead_mu));
	graphicObjects::nOutliersOnTrack->push_back(mu_nOutliersOnTrack->at(lead_mu));
	graphicObjects::nBLHits->push_back(mu_nBLHits->at(lead_mu));
	graphicObjects::nPixHits->push_back(mu_nPixHits->at(lead_mu));
	graphicObjects::nSCTHits->push_back(mu_nSCTHits->at(lead_mu));
	graphicObjects::nTRTHits->push_back(mu_nTRTHits->at(lead_mu));
	graphicObjects::nTRTHighTHits->push_back(mu_nTRTHighTHits->at(lead_mu));
	graphicObjects::nBLSharedHits->push_back(mu_nBLSharedHits->at(lead_mu));
	graphicObjects::nPixSharedHits->push_back(mu_nPixSharedHits->at(lead_mu));
	graphicObjects::nPixHoles->push_back(mu_nPixHoles->at(lead_mu));
	graphicObjects::nSCTSharedHits->push_back(mu_nSCTSharedHits->at(lead_mu));
	graphicObjects::nSCTHoles->push_back(mu_nSCTHoles->at(lead_mu));
	graphicObjects::nTRTOutliers->push_back(mu_nTRTOutliers->at(lead_mu));
	graphicObjects::nTRTHighTOutliers->push_back(mu_nTRTHighTOutliers->at(lead_mu));
	graphicObjects::nGangedPixels->push_back(mu_nGangedPixels->at(lead_mu));
	graphicObjects::nPixelDeadSensors->push_back(mu_nPixelDeadSensors->at(lead_mu));

	_DEBUG("");

	graphicObjects::nSCTDeadSensors->push_back(mu_nSCTDeadSensors->at(lead_mu));
	graphicObjects::nTRTDeadStraws->push_back(mu_nTRTDeadStraws->at(lead_mu));
	graphicObjects::expectBLayerHit->push_back(mu_expectBLayerHit->at(lead_mu));
	graphicObjects::nMDTHits->push_back(mu_nMDTHits->at(lead_mu));
	graphicObjects::nMDTHoles->push_back(mu_nMDTHoles->at(lead_mu));
	graphicObjects::nCSCEtaHits->push_back(mu_nCSCEtaHits->at(lead_mu));
	graphicObjects::nCSCEtaHoles->push_back(mu_nCSCEtaHoles->at(lead_mu));
	graphicObjects::nCSCPhiHits->push_back(mu_nCSCPhiHits->at(lead_mu));
	graphicObjects::nCSCPhiHoles->push_back(mu_nCSCPhiHoles->at(lead_mu));
	graphicObjects::nRPCEtaHits->push_back(mu_nRPCEtaHits->at(lead_mu));
	graphicObjects::nRPCEtaHoles->push_back(mu_nRPCEtaHoles->at(lead_mu));
	graphicObjects::nRPCPhiHits->push_back(mu_nRPCPhiHits->at(lead_mu));
	graphicObjects::nRPCPhiHoles->push_back(mu_nRPCPhiHoles->at(lead_mu));
	graphicObjects::nTGCEtaHits->push_back(mu_nTGCEtaHits->at(lead_mu));
	graphicObjects::nTGCEtaHoles->push_back(mu_nTGCEtaHoles->at(lead_mu));
	graphicObjects::nTGCPhiHits->push_back(mu_nTGCPhiHits->at(lead_mu));
	graphicObjects::nTGCPhiHoles->push_back(mu_nTGCPhiHoles->at(lead_mu));
	graphicObjects::nMDTBIHits->push_back(mu_nMDTBIHits->at(lead_mu));
	graphicObjects::nMDTBMHits->push_back(mu_nMDTBMHits->at(lead_mu));
	graphicObjects::nMDTBOHits->push_back(mu_nMDTBOHits->at(lead_mu));

	_DEBUG("");

	graphicObjects::nMDTBEEHits->push_back(mu_nMDTBEEHits->at(lead_mu));
	graphicObjects::nMDTBIS78Hits->push_back(mu_nMDTBIS78Hits->at(lead_mu));
	graphicObjects::nMDTEIHits->push_back(mu_nMDTEIHits->at(lead_mu));
	graphicObjects::nMDTEMHits->push_back(mu_nMDTEMHits->at(lead_mu));
	graphicObjects::nMDTEOHits->push_back(mu_nMDTEOHits->at(lead_mu));
	graphicObjects::nMDTEEHits->push_back(mu_nMDTEEHits->at(lead_mu));
	graphicObjects::nRPCLayer1EtaHits->push_back(mu_nRPCLayer1EtaHits->at(lead_mu));
	graphicObjects::nRPCLayer2EtaHits->push_back(mu_nRPCLayer2EtaHits->at(lead_mu));
	graphicObjects::nRPCLayer3EtaHits->push_back(mu_nRPCLayer3EtaHits->at(lead_mu));
	graphicObjects::nRPCLayer1PhiHits->push_back(mu_nRPCLayer1PhiHits->at(lead_mu));
	graphicObjects::nRPCLayer2PhiHits->push_back(mu_nRPCLayer2PhiHits->at(lead_mu));
	graphicObjects::nRPCLayer3PhiHits->push_back(mu_nRPCLayer3PhiHits->at(lead_mu));
	graphicObjects::nTGCLayer1EtaHits->push_back(mu_nTGCLayer1EtaHits->at(lead_mu));
	graphicObjects::nTGCLayer2EtaHits->push_back(mu_nTGCLayer2EtaHits->at(lead_mu));
	graphicObjects::nTGCLayer3EtaHits->push_back(mu_nTGCLayer3EtaHits->at(lead_mu));
	graphicObjects::nTGCLayer4EtaHits->push_back(mu_nTGCLayer4EtaHits->at(lead_mu));
	graphicObjects::nTGCLayer1PhiHits->push_back(mu_nTGCLayer1PhiHits->at(lead_mu));
	graphicObjects::nTGCLayer2PhiHits->push_back(mu_nTGCLayer2PhiHits->at(lead_mu));
	graphicObjects::nTGCLayer3PhiHits->push_back(mu_nTGCLayer3PhiHits->at(lead_mu));
	graphicObjects::nTGCLayer4PhiHits->push_back(mu_nTGCLayer4PhiHits->at(lead_mu));

	_DEBUG("");

	graphicObjects::barrelSectors->push_back(mu_barrelSectors->at(lead_mu));
	graphicObjects::endcapSectors->push_back(mu_endcapSectors->at(lead_mu));
	graphicObjects::trackd0->push_back(mu_trackd0->at(lead_mu));
	graphicObjects::trackz0->push_back(mu_trackz0->at(lead_mu));
	graphicObjects::trackphi->push_back(mu_trackphi->at(lead_mu));
	graphicObjects::tracktheta->push_back(mu_tracktheta->at(lead_mu));
	graphicObjects::trackqoverp->push_back(mu_trackqoverp->at(lead_mu));
	graphicObjects::trackcov_d0->push_back(mu_trackcov_d0->at(lead_mu));
	graphicObjects::trackcov_z0->push_back(mu_trackcov_z0->at(lead_mu));
	graphicObjects::trackcov_phi->push_back(mu_trackcov_phi->at(lead_mu));
	graphicObjects::trackcov_theta->push_back(mu_trackcov_theta->at(lead_mu));
	graphicObjects::trackcov_qoverp->push_back(mu_trackcov_qoverp->at(lead_mu));
	graphicObjects::trackcov_d0_z0->push_back(mu_trackcov_d0_z0->at(lead_mu));
	graphicObjects::trackcov_d0_phi->push_back(mu_trackcov_d0_phi->at(lead_mu));
	graphicObjects::trackcov_d0_theta->push_back(mu_trackcov_d0_theta->at(lead_mu));
	graphicObjects::trackcov_d0_qoverp->push_back(mu_trackcov_d0_qoverp->at(lead_mu));
	graphicObjects::trackcov_z0_phi->push_back(mu_trackcov_z0_phi->at(lead_mu));
	graphicObjects::trackcov_z0_theta->push_back(mu_trackcov_z0_theta->at(lead_mu));
	graphicObjects::trackcov_z0_qoverp->push_back(mu_trackcov_z0_qoverp->at(lead_mu));
	graphicObjects::trackcov_phi_theta->push_back(mu_trackcov_phi_theta->at(lead_mu));
	graphicObjects::trackcov_phi_qoverp->push_back(mu_trackcov_phi_qoverp->at(lead_mu));
	graphicObjects::trackcov_theta_qoverp->push_back(mu_trackcov_theta_qoverp->at(lead_mu));
	graphicObjects::trackfitchi2->push_back(mu_trackfitchi2->at(lead_mu));
	graphicObjects::trackfitndof->push_back(mu_trackfitndof->at(lead_mu));
	graphicObjects::hastrack->push_back(mu_hastrack->at(lead_mu));

	_DEBUG("");

	if(AS_isMC)
	{
		graphicObjects::truth_dr->push_back(mu_truth_dr->at(lead_mu));
		graphicObjects::truth_E->push_back(mu_truth_E->at(lead_mu));
		graphicObjects::truth_pt->push_back(mu_truth_pt->at(lead_mu));
		graphicObjects::truth_eta->push_back(mu_truth_eta->at(lead_mu));
		graphicObjects::truth_phi->push_back(mu_truth_phi->at(lead_mu));
		graphicObjects::truth_type->push_back(mu_truth_type->at(lead_mu));
		graphicObjects::truth_status->push_back(mu_truth_status->at(lead_mu));
		graphicObjects::truth_barcode->push_back(mu_truth_barcode->at(lead_mu));
		graphicObjects::truth_mothertype->push_back(mu_truth_mothertype->at(lead_mu));
		graphicObjects::truth_motherbarcode->push_back(mu_truth_motherbarcode->at(lead_mu));
		graphicObjects::truth_matched->push_back(mu_truth_matched->at(lead_mu));
	}

	_DEBUG("");

	graphicObjects::EFCB_dr->push_back(mu_EFCB_dr->at(lead_mu));
	graphicObjects::EFCB_index->push_back(mu_EFCB_index->at(lead_mu));
	graphicObjects::EFMG_dr->push_back(mu_EFMG_dr->at(lead_mu));
	graphicObjects::EFMG_index->push_back(mu_EFMG_index->at(lead_mu));
	graphicObjects::EFME_dr->push_back(mu_EFME_dr->at(lead_mu));
	graphicObjects::EFME_index->push_back(mu_EFME_index->at(lead_mu));
	graphicObjects::L2CB_dr->push_back(mu_L2CB_dr->at(lead_mu));
	graphicObjects::L2CB_index->push_back(mu_L2CB_index->at(lead_mu));
	graphicObjects::L1_dr->push_back(mu_L1_dr->at(lead_mu));
	graphicObjects::L1_index->push_back(mu_L1_index->at(lead_mu));
	
	graphicObjects::mutype->push_back(classify3332null[sublead_mu]);
	graphicObjects::E->push_back(mu_E->at(sublead_mu));
	graphicObjects::pt->push_back(mu_pt->at(sublead_mu));
	graphicObjects::m->push_back(mu_m->at(sublead_mu));
	graphicObjects::eta->push_back(mu_eta->at(sublead_mu));
	graphicObjects::phi->push_back(mu_phi->at(sublead_mu));
	graphicObjects::px->push_back(mu_px->at(sublead_mu));
	graphicObjects::py->push_back(mu_py->at(sublead_mu));
	graphicObjects::pz->push_back(mu_pz->at(sublead_mu));

	_DEBUG("");

	graphicObjects::charge->push_back(mu_charge->at(sublead_mu));
	graphicObjects::allauthor->push_back(mu_allauthor->at(sublead_mu));
	graphicObjects::author->push_back(mu_author->at(sublead_mu));
	graphicObjects::beta->push_back(mu_beta->at(sublead_mu));
	graphicObjects::isMuonLikelihood->push_back(mu_isMuonLikelihood->at(sublead_mu));
	graphicObjects::matchchi2->push_back(mu_matchchi2->at(sublead_mu));
	graphicObjects::matchndof->push_back(mu_matchndof->at(sublead_mu));
	graphicObjects::etcone20->push_back(mu_etcone20->at(sublead_mu));
	graphicObjects::etcone30->push_back(mu_etcone30->at(sublead_mu));
	graphicObjects::etcone40->push_back(mu_etcone40->at(sublead_mu));
	graphicObjects::nucone20->push_back(mu_nucone20->at(sublead_mu));
	graphicObjects::nucone30->push_back(mu_nucone30->at(sublead_mu));
	graphicObjects::nucone40->push_back(mu_nucone40->at(sublead_mu));
	graphicObjects::ptcone20->push_back(mu_ptcone20->at(sublead_mu));
	graphicObjects::ptcone30->push_back(mu_ptcone30->at(sublead_mu));
	graphicObjects::ptcone40->push_back(mu_ptcone40->at(sublead_mu));
	graphicObjects::energyLossPar->push_back(mu_energyLossPar->at(sublead_mu));
	graphicObjects::energyLossErr->push_back(mu_energyLossErr->at(sublead_mu));
	graphicObjects::etCore->push_back(mu_etCore->at(sublead_mu));

	_DEBUG("");

	graphicObjects::energyLossType->push_back(mu_energyLossType->at(sublead_mu));
	graphicObjects::caloMuonIdTag->push_back(mu_caloMuonIdTag->at(sublead_mu));
	graphicObjects::caloLRLikelihood->push_back(mu_caloLRLikelihood->at(sublead_mu));
	graphicObjects::bestMatch->push_back(mu_bestMatch->at(sublead_mu));
	graphicObjects::isStandAloneMuon->push_back(mu_isStandAloneMuon->at(sublead_mu));
	graphicObjects::isCombinedMuon->push_back(mu_isCombinedMuon->at(sublead_mu));
	graphicObjects::isLowPtReconstructedMuon->push_back(mu_isLowPtReconstructedMuon->at(sublead_mu));
	graphicObjects::loose->push_back(mu_loose->at(sublead_mu));
	graphicObjects::medium->push_back(mu_medium->at(sublead_mu));
	graphicObjects::tight->push_back(mu_tight->at(sublead_mu));
	graphicObjects::d0_exPV->push_back(mu_d0_exPV->at(sublead_mu));
	graphicObjects::z0_exPV->push_back(mu_z0_exPV->at(sublead_mu));
	graphicObjects::phi_exPV->push_back(mu_phi_exPV->at(sublead_mu));
	graphicObjects::theta_exPV->push_back(mu_theta_exPV->at(sublead_mu));
	graphicObjects::qoverp_exPV->push_back(mu_qoverp_exPV->at(sublead_mu));
	graphicObjects::cb_d0_exPV->push_back(mu_cb_d0_exPV->at(sublead_mu));
	graphicObjects::cb_z0_exPV->push_back(mu_cb_z0_exPV->at(sublead_mu));
	graphicObjects::cb_phi_exPV->push_back(mu_cb_phi_exPV->at(sublead_mu));
	graphicObjects::cb_theta_exPV->push_back(mu_cb_theta_exPV->at(sublead_mu));
	graphicObjects::cb_qoverp_exPV->push_back(mu_cb_qoverp_exPV->at(sublead_mu));
	graphicObjects::id_d0_exPV->push_back(mu_id_d0_exPV->at(sublead_mu));
	graphicObjects::id_z0_exPV->push_back(mu_id_z0_exPV->at(sublead_mu));
	graphicObjects::id_phi_exPV->push_back(mu_id_phi_exPV->at(sublead_mu));

	_DEBUG("");

	graphicObjects::id_theta_exPV->push_back(mu_id_theta_exPV->at(sublead_mu));
	graphicObjects::id_qoverp_exPV->push_back(mu_id_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_d0_exPV->push_back(mu_me_d0_exPV->at(sublead_mu));
	graphicObjects::me_z0_exPV->push_back(mu_me_z0_exPV->at(sublead_mu));
	graphicObjects::me_phi_exPV->push_back(mu_me_phi_exPV->at(sublead_mu));
	graphicObjects::me_theta_exPV->push_back(mu_me_theta_exPV->at(sublead_mu));
	graphicObjects::me_qoverp_exPV->push_back(mu_me_qoverp_exPV->at(sublead_mu));
	graphicObjects::ie_d0_exPV->push_back(mu_ie_d0_exPV->at(sublead_mu));
	graphicObjects::ie_z0_exPV->push_back(mu_ie_z0_exPV->at(sublead_mu));
	graphicObjects::ie_phi_exPV->push_back(mu_ie_phi_exPV->at(sublead_mu));
	graphicObjects::ie_theta_exPV->push_back(mu_ie_theta_exPV->at(sublead_mu));
	graphicObjects::ie_qoverp_exPV->push_back(mu_ie_qoverp_exPV->at(sublead_mu));
	/*
	graphicObjects::TileCellEnergyLayer1->push_back(mu_TileCellEnergyLayer1->at(sublead_mu));
	graphicObjects::TileTimeLayer1->push_back(mu_TileTimeLayer1->at(sublead_mu));
	graphicObjects::TileCellRmsNoiseLayer1->push_back(mu_TileCellRmsNoiseLayer1->at(sublead_mu));
	graphicObjects::TileCellSignLayer1->push_back(mu_TileCellSignLayer1->at(sublead_mu));
	graphicObjects::TileCellEnergyLayer2->push_back(mu_TileCellEnergyLayer2->at(sublead_mu));
	graphicObjects::TileTimeLayer2->push_back(mu_TileTimeLayer2->at(sublead_mu));
	graphicObjects::TileCellRmsNoiseLayer2->push_back(mu_TileCellRmsNoiseLayer2->at(sublead_mu));
	graphicObjects::TileCellSignLayer2->push_back(mu_TileCellSignLayer2->at(sublead_mu));
	graphicObjects::TileCellEnergyLayer3->push_back(mu_TileCellEnergyLayer3->at(sublead_mu));
	graphicObjects::TileTimeLayer3->push_back(mu_TileTimeLayer3->at(sublead_mu));
	graphicObjects::TileCellRmsNoiseLayer3->push_back(mu_TileCellRmsNoiseLayer3->at(sublead_mu));
	graphicObjects::TileCellSignLayer3->push_back(mu_TileCellSignLayer3->at(sublead_mu));
	graphicObjects::MSTrkT0_1->push_back(mu_MSTrkT0_1->at(sublead_mu));
	graphicObjects::MSTrkT0_2->push_back(mu_MSTrkT0_2->at(sublead_mu));
	graphicObjects::MSTrkT0_3->push_back(mu_MSTrkT0_3->at(sublead_mu));
	*/
	graphicObjects::cov_d0_exPV->push_back(mu_cov_d0_exPV->at(sublead_mu));
	graphicObjects::cov_z0_exPV->push_back(mu_cov_z0_exPV->at(sublead_mu));
	graphicObjects::cov_phi_exPV->push_back(mu_cov_phi_exPV->at(sublead_mu));
	graphicObjects::cov_theta_exPV->push_back(mu_cov_theta_exPV->at(sublead_mu));
	graphicObjects::cov_qoverp_exPV->push_back(mu_cov_qoverp_exPV->at(sublead_mu));
	graphicObjects::cov_d0_z0_exPV->push_back(mu_cov_d0_z0_exPV->at(sublead_mu));
	graphicObjects::cov_d0_phi_exPV->push_back(mu_cov_d0_phi_exPV->at(sublead_mu));
	graphicObjects::cov_d0_theta_exPV->push_back(mu_cov_d0_theta_exPV->at(sublead_mu));
	graphicObjects::cov_d0_qoverp_exPV->push_back(mu_cov_d0_qoverp_exPV->at(sublead_mu));
	graphicObjects::cov_z0_phi_exPV->push_back(mu_cov_z0_phi_exPV->at(sublead_mu));
	graphicObjects::cov_z0_theta_exPV->push_back(mu_cov_z0_theta_exPV->at(sublead_mu));
	graphicObjects::cov_z0_qoverp_exPV->push_back(mu_cov_z0_qoverp_exPV->at(sublead_mu));
	graphicObjects::cov_phi_theta_exPV->push_back(mu_cov_phi_theta_exPV->at(sublead_mu));
	graphicObjects::cov_phi_qoverp_exPV->push_back(mu_cov_phi_qoverp_exPV->at(sublead_mu));
	graphicObjects::cov_theta_qoverp_exPV->push_back(mu_cov_theta_qoverp_exPV->at(sublead_mu));

	_DEBUG("");

	graphicObjects::id_cov_d0_exPV->push_back(mu_id_cov_d0_exPV->at(sublead_mu));
	graphicObjects::id_cov_z0_exPV->push_back(mu_id_cov_z0_exPV->at(sublead_mu));
	graphicObjects::id_cov_phi_exPV->push_back(mu_id_cov_phi_exPV->at(sublead_mu));
	graphicObjects::id_cov_theta_exPV->push_back(mu_id_cov_theta_exPV->at(sublead_mu));
	graphicObjects::id_cov_qoverp_exPV->push_back(mu_id_cov_qoverp_exPV->at(sublead_mu));
	graphicObjects::id_cov_d0_z0_exPV->push_back(mu_id_cov_d0_z0_exPV->at(sublead_mu));
	graphicObjects::id_cov_d0_phi_exPV->push_back(mu_id_cov_d0_phi_exPV->at(sublead_mu));
	graphicObjects::id_cov_d0_theta_exPV->push_back(mu_id_cov_d0_theta_exPV->at(sublead_mu));
	graphicObjects::id_cov_d0_qoverp_exPV->push_back(mu_id_cov_d0_qoverp_exPV->at(sublead_mu));
	graphicObjects::id_cov_z0_phi_exPV->push_back(mu_id_cov_z0_phi_exPV->at(sublead_mu));
	graphicObjects::id_cov_z0_theta_exPV->push_back(mu_id_cov_z0_theta_exPV->at(sublead_mu));
	graphicObjects::id_cov_z0_qoverp_exPV->push_back(mu_id_cov_z0_qoverp_exPV->at(sublead_mu));
	graphicObjects::id_cov_phi_theta_exPV->push_back(mu_id_cov_phi_theta_exPV->at(sublead_mu));
	graphicObjects::id_cov_phi_qoverp_exPV->push_back(mu_id_cov_phi_qoverp_exPV->at(sublead_mu));
	graphicObjects::id_cov_theta_qoverp_exPV->push_back(mu_id_cov_theta_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_cov_d0_exPV->push_back(mu_me_cov_d0_exPV->at(sublead_mu));
	graphicObjects::me_cov_z0_exPV->push_back(mu_me_cov_z0_exPV->at(sublead_mu));

	_DEBUG("");

	graphicObjects::me_cov_phi_exPV->push_back(mu_me_cov_phi_exPV->at(sublead_mu));
	graphicObjects::me_cov_theta_exPV->push_back(mu_me_cov_theta_exPV->at(sublead_mu));
	graphicObjects::me_cov_qoverp_exPV->push_back(mu_me_cov_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_cov_d0_z0_exPV->push_back(mu_me_cov_d0_z0_exPV->at(sublead_mu));
	graphicObjects::me_cov_d0_phi_exPV->push_back(mu_me_cov_d0_phi_exPV->at(sublead_mu));
	graphicObjects::me_cov_d0_theta_exPV->push_back(mu_me_cov_d0_theta_exPV->at(sublead_mu));
	graphicObjects::me_cov_d0_qoverp_exPV->push_back(mu_me_cov_d0_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_cov_z0_phi_exPV->push_back(mu_me_cov_z0_phi_exPV->at(sublead_mu));
	graphicObjects::me_cov_z0_theta_exPV->push_back(mu_me_cov_z0_theta_exPV->at(sublead_mu));
	graphicObjects::me_cov_z0_qoverp_exPV->push_back(mu_me_cov_z0_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_cov_phi_theta_exPV->push_back(mu_me_cov_phi_theta_exPV->at(sublead_mu));
	graphicObjects::me_cov_phi_qoverp_exPV->push_back(mu_me_cov_phi_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_cov_theta_qoverp_exPV->push_back(mu_me_cov_theta_qoverp_exPV->at(sublead_mu));
	graphicObjects::ms_d0->push_back(mu_ms_d0->at(sublead_mu));
	graphicObjects::ms_z0->push_back(mu_ms_z0->at(sublead_mu));
	graphicObjects::ms_phi->push_back(mu_ms_phi->at(sublead_mu));
	graphicObjects::ms_theta->push_back(mu_ms_theta->at(sublead_mu));
	graphicObjects::ms_qoverp->push_back(mu_ms_qoverp->at(sublead_mu));
	graphicObjects::id_d0->push_back(mu_id_d0->at(sublead_mu));
	graphicObjects::id_z0->push_back(mu_id_z0->at(sublead_mu));
	graphicObjects::id_phi->push_back(mu_id_phi->at(sublead_mu));
	graphicObjects::id_theta->push_back(mu_id_theta->at(sublead_mu));

	_DEBUG("");

	graphicObjects::id_qoverp->push_back(mu_id_qoverp->at(sublead_mu));
	graphicObjects::me_d0->push_back(mu_me_d0->at(sublead_mu));
	graphicObjects::me_z0->push_back(mu_me_z0->at(sublead_mu));
	graphicObjects::me_phi->push_back(mu_me_phi->at(sublead_mu));
	graphicObjects::me_theta->push_back(mu_me_theta->at(sublead_mu));
	graphicObjects::me_qoverp->push_back(mu_me_qoverp->at(sublead_mu));
	graphicObjects::ie_d0->push_back(mu_ie_d0->at(sublead_mu));
	graphicObjects::ie_z0->push_back(mu_ie_z0->at(sublead_mu));
	graphicObjects::ie_phi->push_back(mu_ie_phi->at(sublead_mu));
	graphicObjects::ie_theta->push_back(mu_ie_theta->at(sublead_mu));
	graphicObjects::ie_qoverp->push_back(mu_ie_qoverp->at(sublead_mu));
	graphicObjects::nOutliersOnTrack->push_back(mu_nOutliersOnTrack->at(sublead_mu));
	graphicObjects::nBLHits->push_back(mu_nBLHits->at(sublead_mu));
	graphicObjects::nPixHits->push_back(mu_nPixHits->at(sublead_mu));
	graphicObjects::nSCTHits->push_back(mu_nSCTHits->at(sublead_mu));
	graphicObjects::nTRTHits->push_back(mu_nTRTHits->at(sublead_mu));
	graphicObjects::nTRTHighTHits->push_back(mu_nTRTHighTHits->at(sublead_mu));
	graphicObjects::nBLSharedHits->push_back(mu_nBLSharedHits->at(sublead_mu));
	graphicObjects::nPixSharedHits->push_back(mu_nPixSharedHits->at(sublead_mu));
	graphicObjects::nPixHoles->push_back(mu_nPixHoles->at(sublead_mu));
	graphicObjects::nSCTSharedHits->push_back(mu_nSCTSharedHits->at(sublead_mu));

	_DEBUG("");

	graphicObjects::nSCTHoles->push_back(mu_nSCTHoles->at(sublead_mu));
	graphicObjects::nTRTOutliers->push_back(mu_nTRTOutliers->at(sublead_mu));
	graphicObjects::nTRTHighTOutliers->push_back(mu_nTRTHighTOutliers->at(sublead_mu));
	graphicObjects::nGangedPixels->push_back(mu_nGangedPixels->at(sublead_mu));
	graphicObjects::nPixelDeadSensors->push_back(mu_nPixelDeadSensors->at(sublead_mu));
	graphicObjects::nSCTDeadSensors->push_back(mu_nSCTDeadSensors->at(sublead_mu));
	graphicObjects::nTRTDeadStraws->push_back(mu_nTRTDeadStraws->at(sublead_mu));
	graphicObjects::expectBLayerHit->push_back(mu_expectBLayerHit->at(sublead_mu));
	graphicObjects::nMDTHits->push_back(mu_nMDTHits->at(sublead_mu));
	graphicObjects::nMDTHoles->push_back(mu_nMDTHoles->at(sublead_mu));
	graphicObjects::nCSCEtaHits->push_back(mu_nCSCEtaHits->at(sublead_mu));
	graphicObjects::nCSCEtaHoles->push_back(mu_nCSCEtaHoles->at(sublead_mu));
	graphicObjects::nCSCPhiHits->push_back(mu_nCSCPhiHits->at(sublead_mu));
	graphicObjects::nCSCPhiHoles->push_back(mu_nCSCPhiHoles->at(sublead_mu));
	graphicObjects::nRPCEtaHits->push_back(mu_nRPCEtaHits->at(sublead_mu));
	graphicObjects::nRPCEtaHoles->push_back(mu_nRPCEtaHoles->at(sublead_mu));
	graphicObjects::nRPCPhiHits->push_back(mu_nRPCPhiHits->at(sublead_mu));
	graphicObjects::nRPCPhiHoles->push_back(mu_nRPCPhiHoles->at(sublead_mu));
	graphicObjects::nTGCEtaHits->push_back(mu_nTGCEtaHits->at(sublead_mu));
	graphicObjects::nTGCEtaHoles->push_back(mu_nTGCEtaHoles->at(sublead_mu));

	_DEBUG("");

	graphicObjects::nTGCPhiHits->push_back(mu_nTGCPhiHits->at(sublead_mu));
	graphicObjects::nTGCPhiHoles->push_back(mu_nTGCPhiHoles->at(sublead_mu));
	graphicObjects::nMDTBIHits->push_back(mu_nMDTBIHits->at(sublead_mu));
	graphicObjects::nMDTBMHits->push_back(mu_nMDTBMHits->at(sublead_mu));
	graphicObjects::nMDTBOHits->push_back(mu_nMDTBOHits->at(sublead_mu));
	graphicObjects::nMDTBEEHits->push_back(mu_nMDTBEEHits->at(sublead_mu));
	graphicObjects::nMDTBIS78Hits->push_back(mu_nMDTBIS78Hits->at(sublead_mu));
	graphicObjects::nMDTEIHits->push_back(mu_nMDTEIHits->at(sublead_mu));
	graphicObjects::nMDTEMHits->push_back(mu_nMDTEMHits->at(sublead_mu));
	graphicObjects::nMDTEOHits->push_back(mu_nMDTEOHits->at(sublead_mu));
	graphicObjects::nMDTEEHits->push_back(mu_nMDTEEHits->at(sublead_mu));
	graphicObjects::nRPCLayer1EtaHits->push_back(mu_nRPCLayer1EtaHits->at(sublead_mu));
	graphicObjects::nRPCLayer2EtaHits->push_back(mu_nRPCLayer2EtaHits->at(sublead_mu));
	graphicObjects::nRPCLayer3EtaHits->push_back(mu_nRPCLayer3EtaHits->at(sublead_mu));
	graphicObjects::nRPCLayer1PhiHits->push_back(mu_nRPCLayer1PhiHits->at(sublead_mu));
	graphicObjects::nRPCLayer2PhiHits->push_back(mu_nRPCLayer2PhiHits->at(sublead_mu));
	graphicObjects::nRPCLayer3PhiHits->push_back(mu_nRPCLayer3PhiHits->at(sublead_mu));
	graphicObjects::nTGCLayer1EtaHits->push_back(mu_nTGCLayer1EtaHits->at(sublead_mu));
	graphicObjects::nTGCLayer2EtaHits->push_back(mu_nTGCLayer2EtaHits->at(sublead_mu));
	graphicObjects::nTGCLayer3EtaHits->push_back(mu_nTGCLayer3EtaHits->at(sublead_mu));

	_DEBUG("");

	graphicObjects::nTGCLayer4EtaHits->push_back(mu_nTGCLayer4EtaHits->at(sublead_mu));
	graphicObjects::nTGCLayer1PhiHits->push_back(mu_nTGCLayer1PhiHits->at(sublead_mu));
	graphicObjects::nTGCLayer2PhiHits->push_back(mu_nTGCLayer2PhiHits->at(sublead_mu));
	graphicObjects::nTGCLayer3PhiHits->push_back(mu_nTGCLayer3PhiHits->at(sublead_mu));
	graphicObjects::nTGCLayer4PhiHits->push_back(mu_nTGCLayer4PhiHits->at(sublead_mu));
	graphicObjects::barrelSectors->push_back(mu_barrelSectors->at(sublead_mu));
	graphicObjects::endcapSectors->push_back(mu_endcapSectors->at(sublead_mu));
	graphicObjects::trackd0->push_back(mu_trackd0->at(sublead_mu));
	graphicObjects::trackz0->push_back(mu_trackz0->at(sublead_mu));
	graphicObjects::trackphi->push_back(mu_trackphi->at(sublead_mu));
	graphicObjects::tracktheta->push_back(mu_tracktheta->at(sublead_mu));
	graphicObjects::trackqoverp->push_back(mu_trackqoverp->at(sublead_mu));
	graphicObjects::trackcov_d0->push_back(mu_trackcov_d0->at(sublead_mu));
	graphicObjects::trackcov_z0->push_back(mu_trackcov_z0->at(sublead_mu));
	graphicObjects::trackcov_phi->push_back(mu_trackcov_phi->at(sublead_mu));
	graphicObjects::trackcov_theta->push_back(mu_trackcov_theta->at(sublead_mu));
	graphicObjects::trackcov_qoverp->push_back(mu_trackcov_qoverp->at(sublead_mu));
	graphicObjects::trackcov_d0_z0->push_back(mu_trackcov_d0_z0->at(sublead_mu));
	graphicObjects::trackcov_d0_phi->push_back(mu_trackcov_d0_phi->at(sublead_mu));
	graphicObjects::trackcov_d0_theta->push_back(mu_trackcov_d0_theta->at(sublead_mu));
	graphicObjects::trackcov_d0_qoverp->push_back(mu_trackcov_d0_qoverp->at(sublead_mu));

	_DEBUG("");

	graphicObjects::trackcov_z0_phi->push_back(mu_trackcov_z0_phi->at(sublead_mu));
	graphicObjects::trackcov_z0_theta->push_back(mu_trackcov_z0_theta->at(sublead_mu));
	graphicObjects::trackcov_z0_qoverp->push_back(mu_trackcov_z0_qoverp->at(sublead_mu));
	graphicObjects::trackcov_phi_theta->push_back(mu_trackcov_phi_theta->at(sublead_mu));
	graphicObjects::trackcov_phi_qoverp->push_back(mu_trackcov_phi_qoverp->at(sublead_mu));
	graphicObjects::trackcov_theta_qoverp->push_back(mu_trackcov_theta_qoverp->at(sublead_mu));
	graphicObjects::trackfitchi2->push_back(mu_trackfitchi2->at(sublead_mu));
	graphicObjects::trackfitndof->push_back(mu_trackfitndof->at(sublead_mu));
	graphicObjects::hastrack->push_back(mu_hastrack->at(sublead_mu));

	_DEBUG("");

	if(AS_isMC)
	{
		graphicObjects::truth_dr->push_back(mu_truth_dr->at(sublead_mu));
		graphicObjects::truth_E->push_back(mu_truth_E->at(sublead_mu));
		graphicObjects::truth_pt->push_back(mu_truth_pt->at(sublead_mu));
		graphicObjects::truth_eta->push_back(mu_truth_eta->at(sublead_mu));
		graphicObjects::truth_phi->push_back(mu_truth_phi->at(sublead_mu));
		graphicObjects::truth_type->push_back(mu_truth_type->at(sublead_mu));
		graphicObjects::truth_status->push_back(mu_truth_status->at(sublead_mu));
		graphicObjects::truth_barcode->push_back(mu_truth_barcode->at(sublead_mu));
		graphicObjects::truth_mothertype->push_back(mu_truth_mothertype->at(sublead_mu));
		graphicObjects::truth_motherbarcode->push_back(mu_truth_motherbarcode->at(sublead_mu));
		graphicObjects::truth_matched->push_back(mu_truth_matched->at(sublead_mu));
	}

	_DEBUG("");

	graphicObjects::EFCB_dr->push_back(mu_EFCB_dr->at(sublead_mu));
	graphicObjects::EFCB_index->push_back(mu_EFCB_index->at(sublead_mu));
	graphicObjects::EFMG_dr->push_back(mu_EFMG_dr->at(sublead_mu));
	graphicObjects::EFMG_index->push_back(mu_EFMG_index->at(sublead_mu));
	graphicObjects::EFME_dr->push_back(mu_EFME_dr->at(sublead_mu));
	graphicObjects::EFME_index->push_back(mu_EFME_index->at(sublead_mu));
	graphicObjects::L2CB_dr->push_back(mu_L2CB_dr->at(sublead_mu));
	graphicObjects::L2CB_index->push_back(mu_L2CB_index->at(sublead_mu));
	graphicObjects::L1_dr->push_back(mu_L1_dr->at(sublead_mu));
	graphicObjects::L1_index->push_back(mu_L1_index->at(sublead_mu));
	
	_DEBUG("");

	/////////////////////////////////////////////////////
	// fill the all cuts tree ///////////////////////////
	tree_allCuts->Fill(); ///////////////////////////////
	if(m_allCuts_counter%m_trees_counter_mod==0) ////////
	{                             ///////////////////////
		tree_allCuts->FlushBaskets(); ///////////////////
		//tree_allCuts->Write("", TObject::kOverwrite); ///
	} ///////////////////////////////////////////////////
	m_allCuts_counter++; ////////////////////////////////
	/////////////////////////////////////////////////////
	
	_DEBUG("");

	///////////////////////////////////////////////////////////////////////
	// for the Afb calculation ////////////////////////////////////////////
	fillAfbMap(current_imass,current_cosThetaCS,current_cosThetaHE); //////
	///////////////////////////////////////////////////////////////////////
	
	_DEBUG("");

	/////////////////////////////////////////////
	// fill the xVector for the ML fit: /////////
	fillXvec( current_imass ); //////////////////
	/////////////////////////////////////////////

	_DEBUG("");
}

void analysisSkeleton::fillBeforeCuts()
{
	_DEBUG("analysisSkeleton::fillBeforeCuts");
	int muSize = (int)mu_pt->size();

	if(muSize==2)
	{
		TLorentzVector* p1 = new TLorentzVector();
		TLorentzVector* p2 = new TLorentzVector();
		p1->SetPtEtaPhiM( mu_pt->at(0)*MeV2TeV, mu_eta->at(0), mu_phi->at(0), muonMass*GeV2TeV);
		p2->SetPtEtaPhiM( mu_pt->at(1)*MeV2TeV, mu_eta->at(1), mu_phi->at(1), muonMass*GeV2TeV);
		// p1->SetPtEtaPhiE( mu_pt->at(0)*MeV2TeV, mu_eta->at(0), mu_phi->at(0), mu_E->at(0)*MeV2TeV);
		// p2->SetPtEtaPhiE( mu_pt->at(1)*MeV2TeV, mu_eta->at(1), mu_phi->at(1), mu_E->at(1)*MeV2TeV);
		current_cosmicCosth = cosThetaDimu(p1,p2);
		h1_cosmicCosth->Fill( current_cosmicCosth );
		delete p1;
		delete p2;
		
		h1_d0exPV->Fill(mu_d0_exPV->at(0));
		h1_d0exPV->Fill(mu_d0_exPV->at(1));
		
		h1_z0exPV->Fill(mu_z0_exPV->at(0));
		h1_z0exPV->Fill(mu_z0_exPV->at(1));
		
		h2_xyVertex->Fill( mu_d0_exPV->at(0)*cos(mu_phi->at(0)), mu_d0_exPV->at(0)*sin(mu_phi->at(0)) );
		h2_xyVertex->Fill( mu_d0_exPV->at(1)*cos(mu_phi->at(1)), mu_d0_exPV->at(1)*sin(mu_phi->at(1)) );
	}
}

void analysisSkeleton::fillCutFlow(string sorderedcutname)
{
	_DEBUG("analysisSkeleton::fillCutFlow");
	/////////////////////////////////////////////////////////
	// count the cut flow numbers ///////////////////////////
	m_cutFlowNumbers->operator[](sorderedcutname)++; ////////
	/////////////////////////////////////////////////////////
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


int analysisSkeleton::countQAflags()
{
	_DEBUG("analysisSkeleton::countQAflags");
	int nGoodQAflags = 0;
	int muSize = (int)mu_pt->size();
	if(pTtoIndexMap.size()>0) pTtoIndexMap.clear();
	// count the good muons and find their id's
	for(int mu=0 ; mu<muSize ; mu++)
	{
		if(muQAflags[mu])
		{
			pTtoIndexMap.insert( make_pair( mu_pt->at(mu) , mu ) );
			nGoodQAflags++;
		}
	}
	
	return nGoodQAflags;
}

void analysisSkeleton::pTSort()
{
	_DEBUG("analysisSkeleton::pTSort");
	// the map is already sorted by the pT size but,
	// from the lowest to the highest, so there's
	// no need to convert values.
	// the following line defines the reversed iterator
	// so the "rbegin()" points the iterator to the entry
	// with the largest pT and so on.
	
	if(pTtoIndexMap.size()<2)
	{
		_ERROR("in pTSort(), trying to sort a <2 map. Exitting now !");
		exit(-1);
	}
	
	/////////////////////////////////////////////////////////////////////////////
	bool isloose = (iTight>=0 && iTight<(int)mu_pt->size()) ? true : false; /////
	/////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////////
	// no matter how many entries in the map, just take the ////////////////////////////////
	// two muons with highest pT that satisfy Q1*Q2<0 //////////////////////////////////////
	TMapdi::reverse_iterator rit=pTtoIndexMap.rbegin(); ////////////////////////////////////
	if(!isloose)
	{
		ai = rit->second; //////////////////////////////////////////////////////////////////
		rit++; /////////////////////////////////////////////////////////////////////////////
		bi = rit->second; //////////////////////////////////////////////////////////////////

		if(pTtoIndexMap.size()>2)                         //////////////////////////////////////
		{                                                ///////////////////////////////////////
			while(mu_charge->at(ai)*mu_charge->at(bi)>0  &&  rit!=pTtoIndexMap.rend()) /////////
			{                                            ///////////////////////////////////////
				rit++;                                   ///////////////////////////////////////
				bi = rit->second;                        ///////////////////////////////////////
			}                                            ///////////////////////////////////////
		}                                                ///////////////////////////////////////
	}
	else
	{
		ai = iTight;
		if(pTtoIndexMap.size()>=2)
		{
			while(rit!=pTtoIndexMap.rend())
			{
				if(rit->second!=iTight)
				{
					if(mu_charge->at(ai)*mu_charge->at(rit->second)<0.)
					{
						bi = rit->second;
						break;
					}
				}
				rit++;
			}
		} 
	}
	////////////////////////////////////////////////////////////////////////////////////////
	
	if(pTtoIndexMap.size()>2)
	{
		if((RunNumber+EventNumber+lbn)!=EventHash)
		{
			_INFO("MultiGoodMuon N{"
				  +_s((int)pTtoIndexMap.size())
				  +"}{run-lb-evt: "+_s(RunNumber)+"-"+_s(lbn)+"-"+_s(EventNumber)
				  +"} -> ai["+_s(mu_charge->at(ai))+"]="+_s(ai)
				  +", bi["+_s(mu_charge->at(bi))+"]="+_s(bi));
			EventHash = RunNumber+EventNumber+lbn;
			isMultiMuonPrint = true;
		}
	}
}

void analysisSkeleton::pTSort(TMapdi& pTtoIndex, int& index_a, int& index_b, vector<float>* Charge)
{
	_DEBUG("analysisSkeleton::pTSort(TMapdi& pTtoIndex, int& index_a, int& index_b, vector<float>* Charge)");
	// the map is already sorted by the pT size but,
	// from the lowest to the highest, so there's
	// no need to convert values.
	// the following line defines the reversed iterator
	// so the "rbegin()" points the iterator to the entry
	// with the largest pT and so on.
	
	if(pTtoIndex.size()<2) _FATAL("in pTSort(TMapdi& pTtoIndex, int& index_a, int& index_b, vector<float>* Charge), trying to sort a <2 map.");
	if(Charge->size()<2)   _FATAL("in pTSort(TMapdi& pTtoIndex, int& index_a, int& index_b, vector<float>* Charge), trying to sort a <2 map [Charge->size()<2].");
	
	/////////////////////////////////////////////////////////////////////////////
	bool isloose = (iTight>=0 && iTight<(int)mu_pt->size()) ? true : false; /////
	/////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	// no matter how many entries in the map, just take the ///////////////////////////////////////
	// two muons with highest pT that satisfy Q1*Q2<0 /////////////////////////////////////////////
	TMapdi::reverse_iterator rit=pTtoIndex.rbegin(); //////////////////////////////////////////////
	
	if(!isloose)
	{
		index_a = rit->second; ////////////////////////////////////////////////////////////////////////
		rit++; ////////////////////////////////////////////////////////////////////////////////////////
		index_b = rit->second; ////////////////////////////////////////////////////////////////////////

		if(pTtoIndex.size()>2)                           //////////////////////////////////////////////
		{                                                //////////////////////////////////////////////
			while(Charge->at(index_a)*Charge->at(index_b)>0  &&  rit!=pTtoIndex.rend()) ///////////////
			{                                            //////////////////////////////////////////////
				rit++;                                   //////////////////////////////////////////////
				index_b = rit->second;                   //////////////////////////////////////////////
			}                                            //////////////////////////////////////////////
		}                                                //////////////////////////////////////////////
	}
	else
	{
		index_a = iTight;
		if(pTtoIndex.size()>=2)
		{
			while(rit!=pTtoIndex.rend())
			{
				if(rit->second!=iTight)
				{
					if(Charge->at(index_a)*Charge->at(rit->second)<0.)
					{
						index_b = rit->second;
						break;
					}
				}
				rit++;
			}
		} 
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	if(pTtoIndex.size()>2)
	{
		if((RunNumber+EventNumber+lbn)!=EventHash)
		{
			_INFO("MultiGoodMuon N{"
				  +_s((int)pTtoIndex.size())
				  +"}{run-lb-evt: "+_s(RunNumber)+"-"+_s(lbn)+"-"+_s(EventNumber)
				  +"} -> ai["+_s(Charge->at(index_a))+"]="+_s(index_a)
				  +", bi["+_s(Charge->at(index_b))+"]="+_s(index_b));
			EventHash = RunNumber+EventNumber+lbn;
			isMultiMuonPrint = true;
		}
	}
}

void analysisSkeleton::imassSort()
{
	_DEBUG("analysisSkeleton::imassSort");
	float im   = 0.;
	float max  = 0.;
	int muSize = (int)mu_pt->size();
	for(int i=0 ; i<muSize ; i++)
	{
		for(int j=0 ; j<muSize && j!=i ; j++)
		{
			if(muQAflags[i]  &&  muQAflags[j])
			{
				im = imass(pmu[i], pmu[j]);
				if(im>max)
				{
					max = im;
					ai = i;
					bi = j;
				}
			}
		}
	}
}

void analysisSkeleton::buildMU4Vector(int nMus)
{
	_DEBUG("analysisSkeleton::buildMU4Vector");

	wipeMU4Vector();
	for(int j=0 ; j<nMus ; j++)
	{
		pmu.push_back( new TLorentzVector() );
		//if(AS_isMC) pmu[j]->SetPtEtaPhiM( fabs(mu_pt->at(j))*MeV2TeV, mu_eta->at(j), mu_phi->at(j), muonMass*GeV2TeV );
		//else        pmu[j]->SetPtEtaPhiM( mu_pt->at(j)*MeV2TeV, mu_eta->at(j), mu_phi->at(j), muonMass*GeV2TeV );
		pmu[j]->SetPtEtaPhiM( mu_pt->at(j)*MeV2TeV, mu_eta->at(j), mu_phi->at(j), muonMass*GeV2TeV );
		// pmu[j]->SetPtEtaPhiE( mu_pt->at(j)*MeV2TeV, mu_eta->at(j), mu_phi->at(j), mu_E->at(j)*MeV2TeV);
	}
}

void analysisSkeleton::wipeMU4Vector()
{
	_DEBUG("analysisSkeleton::wipeMU4Vector");
	int nMus = (int)pmu.size();
	if(nMus>0)
	{
		for(int j=0 ; j<nMus ; j++)
		{
			if(pmu[j]) delete pmu[j];
		}
		pmu.clear();
	}
}

bool analysisSkeleton::assignPairIndices()
{
	_DEBUG("analysisSkeleton::assignPairIndices");
	// select the final muon pair
	if     (pTtoIndexMap.size()==2) pTSort();
	else if(pTtoIndexMap.size()>2)
	{
		pTSort(); // assigns vallues to ai and bi
		//imassSort();
		nMultiMuonEvents++;
	}
	else
	{
		_WARNING("in analysisSkeleton::assignPairIndices, but there are <2 good single-muons");
		return false;
	}
	
	if(!muQAflags[ai] || !muQAflags[bi]) return false;
	
	return true;
}




// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


bool analysisSkeleton::applyPreselection()
{
	_DEBUG("analysisSkeleton::applyPreselection");
	///////////////////////////////////////////
	// do not skip this for correct counting //
	incrementNallEvents(); ////////////////////
	///////////////////////////////////////////

	TMapsb cutsToSkip; // dummy (empty)
	passCutFlow = preselection(cutsToSkip);
	
	return passCutFlow;
}

bool analysisSkeleton::applySingleMuonSelection(bool isloose)
{
	_DEBUG("analysisSkeleton::applySingleMuonSelection");
	
	////////////////////////////////////////
	// fill the NO CUTS items //////////////
	if(do2MUselection) fillBeforeCuts(); ///
	////////////////////////////////////////
	
	inApplySingleSelection = true;
	
	TMapsb cutsToSkip; // dummy (empty)
	passCutFlow = singleSelection(cutsToSkip,isloose);
	
	/////////////////////////////////////////////////////////
	if(!do2MUselection) /////////////////////////////////////
	{                   /////////////////////////////////////
		if(passCutFlow) fillSingleAfterCuts(); //////////////
		if(AS_isMC) fillSingleTruthAndRecon(passCutFlow); /// this will fill all events (truth_all_* and recon_all_*)
	} ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	
	iTight = -1;
	if(isloose)
	{
		if(!passCutFlow)
		{
			int nTight = 0;
			// find the tight muon
			for(int nQA=0 ; nQA<(int)muQAflags.size() ; nQA++)
			{
				if(muQAflags[nQA])
				{
					nTight++;
					iTight = nQA;
					muLooseQAflags[nQA] = false; // the tight muon cannot be one of the loose muons
					break; // there should be exactly one tight muon
				}
			}
			
			if(nTight!=1) passCutFlow = false;
			else
			{
				if(iTight>=0  &&  iTight<(int)muQAflags.size())
				{
					passCutFlow = singleLooseSelection(cutsToSkip); // if the event didn't pass tight-tight selection, but there's exactly one tight muon, try to selsct tight-loose
					
					for(int nQA=0 ; nQA<(int)muQAflags.size() ; nQA++)
					{
						// muQAflags is the main QA flags vector that
						// should be used outside of singleLooseSelection
						// and outside of this function.
						// the "trues" in muLooseQAflags are (loose && !tight) by definition
						if(nQA==iTight) continue;                             // do not touch the tight muon
						else            muQAflags[nQA] = muLooseQAflags[nQA]; // assign the loose QA flags to the tight QA flags because it is used afterwards
					}
				}
			}
		}
		else passCutFlow = false; // if passsd tight-tight then reject the event since we are looking for tihgt-loose
	}
	
	inApplySingleSelection = false;
	
	return passCutFlow;
}

bool analysisSkeleton::applyDoubleMuonSelection()
{
	_DEBUG("analysisSkeleton::applyDoubleMuonSelection");
	TMapsb cutsToSkip; // dummy (empty)
	passCutFlow = doubleSelection(cutsToSkip);
	
	if(passCutFlow)
	{
	
		// float mT = TMath::Sqrt(2.*mu_pt->at(ai)*MET_Final_et*(1.-cos(MET_Final_phi-mu_phi->at(ai))))*MeV2GeV;
		// cout << "MET_Final_et = " << MET_Final_et << endl;
		// cout << "mT = " << mT << endl;
		// if(mT<30.) return false; // ??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
	
		///////////////////////////////////////////////
		// fill the cutFlow and the allCuts items /////
		fillAfterCuts(); //////////////////////////////
		///////////////////////////////////////////////
		
		////////////////////////////////////////////////////
		// dump events. only if doEventDump==true //////////
		//runEventDumper(); ////////////////////////////////
		if(!AS_isMC) runEventDumper(); /////////////////////
		////////////////////////////////////////////////////
		
		
		// int ntight = 0;
		// for(int nQA=0 ; nQA<(int)muQAflags.size() ; nQA++) if(muQAflags[nQA]) ntight++;
		// cout << EventNumber << ": after: ai=" << ai << ", bi=" << bi << ", tight+loose=" << ntight;
		// cout << " -> ";
		// for(int nQA=0 ; nQA<(int)muQAflags.size() ; nQA++) if(muQAflags[nQA]) cout << nQA << "(iso=" << mu_ptcone30->at(nQA)/mu_pt->at(nQA) << "), ";
		// cout << endl;
	}
	
	return passCutFlow;
}

void analysisSkeleton::fill_tNp()
{
	_DEBUG("analysisSkeleton::fill_tNp");
	int mask = -1;
	string sTrigType = "";
	bool isLLT = false;
	bool isHLT = false;
	bool isCBpT = true;
	
	/////////////////////////////////////////////////////////////////////////////////////////
	//float trig_pTmin       = (float)m_period2pTminMap->operator[](sPeriod)->at(0); ////////  //???????????????????????????????????????????????????????????
	float trig_pTthreshold = (float)m_period2pTthresholdMap->operator[](sPeriod)->at(0); ////  //???????????????????????????????????????????????????????????
	string sTrigPeriod     = (*m_period2triggerperiodMap)[sPeriod]; /////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	if(      (size_t)sTrigPeriod.find("L1")!=string::npos ) sTrigType = "L1"; ///////////////
	else if( (size_t)sTrigPeriod.find("MG")!=string::npos ) sTrigType = "MG"; ///////////////
	else if( (size_t)sTrigPeriod.find("MS")!=string::npos ) sTrigType = "MS"; ///////////////
	else                                                    sTrigType = "CB"; ///////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	if     ( (size_t)sTrigPeriod.find("L1")!=string::npos ) isLLT = true; ///////////////////
	else if( (size_t)sTrigPeriod.find("EF")!=string::npos ) isHLT = true; ///////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	if     (sTrigType=="L1" || sTrigType=="MS") isCBpT = false; /////////////////////////////
	else if(sTrigType=="MG" || sTrigType=="CB") isCBpT = true;  /////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	matchTrigger(sPeriod, sTrigType); ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	
	float pTtmp;
	int previousTag;
	int muTag = -1;
	int ROITag;
	int trigTrkTag;
	int muProb;
	int ROIProb;
	int trigTrkProb;
	
	// tag&probe with respect to EFCB
	for(int mu=0 ; mu<(int)mu_pt->size() ; mu++)
	{
		previousTag = muTag;
	
		if(isHLT)
		{
		
			mask = tagMask
			(
				sTrigPeriod, sTrigType, trig_pTthreshold,
				muQAflags,
				previousTag,
				muTag, ROITag, trigTrkTag,
				mu_HLT_index, mu_HLT_dr,
				mu_phi, mu_eta, mu_pt, mu_me_qoverp, mu_me_theta,
				HLT_phi, HLT_eta, HLT_pt, HLT_has
			);
		}
		else if(isLLT)
		{
			mask = tagMask
			(
				sTrigPeriod, sTrigType, trig_pTthreshold,
				muQAflags,
				previousTag,
				muTag, ROITag,
				mu_LLT_index, mu_LLT_dr,
				mu_phi, mu_eta, mu_pt, mu_me_qoverp, mu_me_theta,
				LLT_phi, LLT_eta, LLT_pt
			);
		}
		if(mask!=12) continue;
		
		mask = probeCandMask
		(
			sTrigType,
			pmu, muQAflags,
			muTag,
			mu_phi, mu_eta, mu_pt, mu_me_qoverp, mu_me_theta, mu_d0_exPV, mu_z0_exPV, mu_charge
		);
		if(mask!=5) continue;
		
		for(int probs=0 ; probs<(int)m_viProbes.size() ; probs++)
		{
			int iprobeCand = m_viProbes[probs];
			if(!isCBpT) pTtmp = fabs(pT(mu_me_qoverp->at(iprobeCand)/MeV2TeV, mu_me_theta->at(iprobeCand)));
			else
			{
				pTtmp = mu_pt->at(iprobeCand)*MeV2TeV;
			}
			
			if(isHLT)
			{
				mask = probeMask
				(
					iprobeCand,
					sTrigPeriod, trig_pTthreshold,
					muQAflags,
					muTag, ROITag, trigTrkTag,
					muProb, ROIProb, trigTrkProb,
					mu_HLT_index, mu_HLT_dr,
					mu_phi, mu_eta,
					HLT_phi, HLT_eta, HLT_pt, HLT_has
				);
			}
			else if(isLLT)
			{
				mask = probeMask
				(
					iprobeCand,
					sTrigPeriod, trig_pTthreshold,
					muQAflags,
					muTag, ROITag,
					muProb, ROIProb,
					mu_LLT_index, mu_LLT_dr,
					mu_phi, mu_eta,
					LLT_phi, LLT_eta, LLT_pt
				);
			}
			if(mask!=12) // cannot probe the candidate, fill the denominator histos
			{
				(*h1map_tagNprobe_candidates_pT)[sTrigPeriod]->Fill( pTtmp );
				(*h1map_tagNprobe_candidates_eta)[sTrigPeriod]->Fill( mu_eta->at(iprobeCand) );
				(*h1map_tagNprobe_candidates_phi)[sTrigPeriod]->Fill( mu_phi->at(iprobeCand) );
				tNp_triggerName->push_back(sTrigPeriod);
				tNp_cand_pT->push_back( pTtmp );
				tNp_cand_eta->push_back( mu_eta->at(iprobeCand) );
				tNp_cand_phi->push_back( mu_phi->at(iprobeCand) );
				continue;
			}
			
			// mask=12 ==> fill both the denominator and the numerator histograms
			(*h1map_tagNprobe_candidates_pT)[sTrigPeriod]->Fill( pTtmp );
			(*h1map_tagNprobe_candidates_eta)[sTrigPeriod]->Fill( mu_eta->at(iprobeCand) );
			(*h1map_tagNprobe_candidates_phi)[sTrigPeriod]->Fill( mu_phi->at(iprobeCand) );
			(*h1map_tagNprobe_succeeded_pT)[sTrigPeriod]->Fill( pTtmp );
			(*h1map_tagNprobe_succeeded_eta)[sTrigPeriod]->Fill( mu_eta->at(iprobeCand) );
			(*h1map_tagNprobe_succeeded_phi)[sTrigPeriod]->Fill( mu_phi->at(iprobeCand) );
			tNp_triggerName->push_back(sTrigPeriod);
			tNp_cand_pT->push_back( pTtmp );
			tNp_cand_eta->push_back( mu_eta->at(iprobeCand) );
			tNp_cand_phi->push_back( mu_phi->at(iprobeCand) );
			tNp_succ_pT->push_back( pTtmp );
			tNp_succ_eta->push_back( mu_eta->at(iprobeCand) );
			tNp_succ_phi->push_back( mu_phi->at(iprobeCand) );
		}
	}
}

void analysisSkeleton::fillTruthEfficiency()
{
	_DEBUG("analysisSkeleton::fillTruthEfficiency");
	//mu_truth_matched    : True if muon is matched to the truth
	//mu_truth_status     : Status oMC status = 1 final particle, status = 3 intermediate particle (documentary)
	//mu_truth_mothertype : description: True mother PDG type
	
	bool isLLT  = false;
	bool isHLT  = false;
	bool isCBpT = true;
	
	if(mu_truth_pt==0)         return;
	if(mu_truth_status==0)     return;
	if(mu_truth_mothertype==0) return;
	if(mu_me_qoverp==0)        return;
	if(mu_me_theta==0)         return;
	
	/////////////////////////////////////////////////////////////////////////////////////////
	float trig_pTmin       = (float)m_period2pTminMap->operator[](sPeriod)->at(0); //////////  // ????????????????????????????????????????????????????????
	//float trig_pTthreshold = (float)m_period2pTthresholdMap->operator[](sPeriod)->at(0); //  // ????????????????????????????????????????????????????????
	string sTrigPeriod     = (*m_period2triggerperiodMap)[sPeriod]; /////////////////////////
	string sTrigType = ""; //////////////////////////////////////////////////////////////////
	if(      (size_t)sTrigPeriod.find("L1")!=string::npos ) sTrigType = "L1"; ///////////////
	else if( (size_t)sTrigPeriod.find("MG")!=string::npos ) sTrigType = "MG"; ///////////////
	else if( (size_t)sTrigPeriod.find("MS")!=string::npos ) sTrigType = "MS"; ///////////////
	else                                                    sTrigType = "CB"; ///////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	if     ( (size_t)sTrigPeriod.find("L1")!=string::npos ) isLLT = true; ///////////////////
	else if( (size_t)sTrigPeriod.find("EF")!=string::npos ) isHLT = true; ///////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	if     (sTrigType=="L1" || sTrigType=="MS") isCBpT = false; /////////////////////////////
	else if(sTrigType=="MG" || sTrigType=="CB") isCBpT = true;  /////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	matchTrigger(sPeriod, sTrigType); ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	
	_DEBUG("");
	
	//////////////////////////////////////
	if(mu_truth_pt->size()!=2) return; ///
	//////////////////////////////////////
	
	_DEBUG("");
	
	float pTreconstructed = 0.;
	for(int t=0 ; t<(int)mu_truth_pt->size() ; t++)
	{
		_DEBUG("Start: t="+_s(t));
	
		if(!isCBpT) pTreconstructed = fabs(pT(mu_me_qoverp->at(t), mu_me_theta->at(t))*MeV2GeV); 
		else        pTreconstructed = mu_pt->at(t)*MeV2GeV;
	
		if(!mu_truth_status->at(t))          continue; // has to be final particle
		if(mu_truth_mothertype->at(t)!=PDTZ) continue; // has to come out of Z^0
		if(pTreconstructed<=trig_pTmin)      continue; // has to be above pT min
	
		// fill the probe candidate histos
		(*h1map_truth_candidates_pT)[sTrigPeriod]->Fill( pTreconstructed*GeV2TeV );
		(*h1map_truth_candidates_eta)[sTrigPeriod]->Fill( mu_eta->at(t) );
		(*h1map_truth_candidates_phi)[sTrigPeriod]->Fill( mu_phi->at(t) );
		tru_triggerName->push_back( sTrigPeriod );
		tru_cand_pT->push_back( pTreconstructed*GeV2TeV );
		tru_cand_eta->push_back( mu_eta->at(t) );
		tru_cand_phi->push_back( mu_phi->at(t) );
		
		if(isLLT)
		{
			float dr = mu_LLT_dr->at(t);
			int iROI = mu_LLT_index->at(t); 
			if(dr<0.)          continue;
			if(dr>dRmax_mu_L1) continue;
			if(iROI<0)         continue;
		
			float dphi = LLT_phi->at(iROI) - mu_phi->at(t);
			float deta = LLT_eta->at(iROI) - mu_eta->at(t);
			dr = sqrt(dphi*dphi + deta*deta);
			if(dr>dRmax_mu_L1) continue;
			
			float pTprobTrig = LLT_pt->at(iROI)*MeV2GeV;
			//float pTtrigThreshold = 10.; // in GeV
			TMapsP2vd::iterator it = m_period2pTthresholdMap->find(sPeriod);
			if(it==m_period2pTthresholdMap->end())
			{
				_ERROR("couldn't find the trigger vector in period: "+sPeriod+", exitting now.");
				exit(-1);
			}
			float pTtrigThreshold = it->second->at(0); // take the lowest pT threshold of the possibilities
			if(pTprobTrig<pTtrigThreshold) continue;
		}
		else if(isHLT)
		{
			float dr = mu_HLT_dr->at(t);
			int iROI = mu_HLT_index->at(t); 
			if(dr<0.)          continue;
			if(dr>dRmax_mu_EF) continue;
			if(iROI<0)         continue;
		
			float dRmax = -1.;
			int iTrigTrk = 0;
			for(int j=0 ; j<(int)HLT_has->at(iROI).size() ; j++)
			{
				if( !HLT_has->at(iROI)[j] ) continue;
				float dphi = HLT_phi->at(iROI)[j] - mu_phi->at(t);
				float deta = HLT_eta->at(iROI)[j] - mu_eta->at(t);
				dr = sqrt(dphi*dphi + deta*deta);
				if(dr>dRmax_mu_EF) continue;
				if(dr>dRmax)       continue;
				dRmax    = dr;
				iTrigTrk = j;
			}
			if(iTrigTrk<0) continue;
			
			float pTprobTrig = HLT_pt->at(iROI)[iTrigTrk]*MeV2GeV;
			// float pTtrigThreshold = 22.; // in GeV
			TMapsP2vd::iterator it = m_period2pTthresholdMap->find(sPeriod);
			if(it==m_period2pTthresholdMap->end())
			{
				_ERROR("couldn't find the trigger vector in period: "+sPeriod+", exitting now.");
				exit(-1);
			}
			float pTtrigThreshold = it->second->at(0); // take the lowest pT threshold of the possibilities
			if(pTprobTrig<pTtrigThreshold) continue;
		}
		
		// fill the probe histos
		(*h1map_truth_succeeded_pT)[sTrigPeriod]->Fill( pTreconstructed*GeV2TeV );
		(*h1map_truth_succeeded_eta)[sTrigPeriod]->Fill( mu_eta->at(t) );
		(*h1map_truth_succeeded_phi)[sTrigPeriod]->Fill( mu_phi->at(t) );
		tru_succ_pT->push_back( pTreconstructed*GeV2TeV );
		tru_succ_eta->push_back( mu_eta->at(t) );
		tru_succ_phi->push_back( mu_phi->at(t) );
		
		_DEBUG("End: t="+_s(t));
	}
	
	_DEBUG("");
}

void analysisSkeleton::fillTruth()
{
	_DEBUG("analysisSkeleton::fillTruth");
	
	
	// fill this anyway, even if the event itself is not "valid"
	graphicObjects::all_actualIntPerXing  = actualIntPerXing;
	graphicObjects::all_averageIntPerXing = averageIntPerXing;
	graphicObjects::all_mc_channel_number = mc_channel_number;
	graphicObjects::all_mc_event_number   = mc_event_number;
	graphicObjects::all_mc_event_weight   = mc_event_weight;
	graphicObjects::all_RunNumber               = RunNumber;
	graphicObjects::all_pileup_weight           = pileup_weight;
	graphicObjects::all_intime_pileup_weight    = intime_pileup_weight;
	graphicObjects::all_outoftime_pileup_weight = outoftime_pileup_weight;
	graphicObjects::all_lumi_pileup_weight      = lumi_pileup_weight;
	graphicObjects::all_EW_kfactor_weight       = EW_kfactor_weight;
	graphicObjects::all_QCD_kfactor_weight      = QCD_kfactor_weight;
	graphicObjects::all_mcevent_weight          = mcevent_weight;
	graphicObjects::all_total_weight            = total_weight;
	graphicObjects::all_randomized_decision     = randomized_decision;
	
	
	// write an example of one event record
	if(!alreadyFilled)
	{
		int nfinalmuons = 0;
		for(int i=0 ; i<(int)mc_pdgId->size() ; i++)
		{
			if(mc_status->at(i)!=1)          continue; // has to be final particle
			if(fabs(mc_pdgId->at(i))!=PDTMU) continue; // has to be a muon
			
			nfinalmuons++;
		}
	
		if(nfinalmuons>3)
		{
			ofstream* tmpFile = new ofstream;
			tmpFile->open("mc_event.txt");
			for(int i=0 ; i<(int)mc_pdgId->size() ; i++)
			{
				(*tmpFile) << "index[" << i << "] \t status[" << mc_status->at(i) << "] \t id[" << mc_pdgId->at(i) << "]" << endl;
				for(int mom=0 ; mom<(int)mc_parent_index->at(i).size() ; mom++)
				{
					int imom = mc_parent_index->at(i)[mom];
					(*tmpFile) << "\tmother[" << mom+1 << "]  index[" << imom << "]  motherid[" << mc_pdgId->at(imom) << "]" << endl; 
				}
				(*tmpFile) << endl;
			}
			tmpFile->close();
			alreadyFilled = true;
		}
	}
	
	////////////////////////////////
	if(mc_pt==0)        return; ////
	if(mc_pt->size()<2) return; ////
	////////////////////////////////
	
	int truth_valid_index = 0;
	//////////////////////////////////////
	pTtoIndexMapTruth.clear(); ///////////
	//////////////////////////////////////
	
	vector<int> intermediate_index;
	for(int t=0 ; t<(int)mc_pt->size() ; t++)
	{
		if(mc_status->at(t)!=1)          continue; // has to be final particle
		if(fabs(mc_pdgId->at(t))!=PDTMU) continue; // has to be a muon
		
		// take the following information from the montecarlo xml !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
		bool isZ        = false; 
		bool isGamma    = false;
		bool isW        = false;
		bool isChm      = false;
		bool isBot      = false;
		bool isTop      = false;
		bool isZprime   = false;
		bool isGraviton = false;
		bool isKK       = false;
		for(int mom=0 ; mom<(int)mc_parent_index->at(t).size() ; mom++) // has to come out of Z^0 / Z' / W / gamma /...
		{
			int imom = mc_parent_index->at(t)[mom];
			if(mc_pdgId->at(imom)==PDTZ)
			{
				isZ = true;
				intermediate_index.push_back(imom);
				break;
			}
			if(mc_pdgId->at(imom)==PDTGAMMA)
			{
				isGamma = true;
				intermediate_index.push_back(imom);
				break;
			}
			if(mc_pdgId->at(imom)*mc_pdgId->at(imom)==PDTWPLUS*PDTWPLUS)
			{
				isW = true;
				intermediate_index.push_back(imom);
				break;
			}
			if(mc_pdgId->at(imom)*mc_pdgId->at(imom)==PDTCHM*PDTCHM)
			{
				isChm = true;
				intermediate_index.push_back(imom);
				break;
			}
			if(mc_pdgId->at(imom)*mc_pdgId->at(imom)==PDTBOT*PDTBOT)
			{
				isBot = true;
				intermediate_index.push_back(imom);
				break;
			}
			if(mc_pdgId->at(imom)*mc_pdgId->at(imom)==PDTTOP*PDTTOP)
			{
				isTop = true;
				intermediate_index.push_back(imom);
				break;
			}
			if(mc_pdgId->at(imom)==PDTZPRIME0)
			{
				isZprime = true;
				intermediate_index.push_back(imom);
				break;
			}
			if(mc_pdgId->at(imom)==PDTGRV)
			{
				isGraviton = true;
				intermediate_index.push_back(imom);
				break;
			}
			if(mc_pdgId->at(imom)==PDTKK)
			{
				isKK = true;
				intermediate_index.push_back(imom);
				break;
			}
			if(mc_pdgId->at(imom)*mc_pdgId->at(imom)==PDTMU*PDTMU  ||  mc_pdgId->at(imom)*mc_pdgId->at(imom)==PDTTAU*PDTTAU)
			{
				for(int mom1=0 ; mom1<(int)mc_parent_index->at(imom).size() ; mom1++)
				{
					int jmom = mc_parent_index->at(imom)[mom1];
					if(mc_pdgId->at(jmom)==PDTZ)
					{
						isZ = true;
						intermediate_index.push_back(jmom);
						break;
					}
					if(mc_pdgId->at(jmom)*mc_pdgId->at(jmom)==PDTWPLUS*PDTWPLUS)
					{
						isW = true;
						intermediate_index.push_back(jmom);
						break;
					}
				}
				if(isZ||isW) break;
			}
		}
		if(!isZ && !isGamma && !isW && !isChm && !isBot && !isTop && !isZprime && !isGraviton && !isKK) 
		{
			// for(int mom=0 ; mom<(int)mc_parent_index->at(t).size() ; mom++)
			// {
				// int imom = mc_parent_index->at(t)[mom];
				// cout<<"idmom1["<<mom<<"]="<<mc_pdgId->at(imom)<<", ";
				// if(fabs(mc_pdgId->at(imom))==(float)PDTMU  ||  fabs(mc_pdgId->at(imom))==(float)PDTTAU)
				// {
					// cout<<endl;
					// for(int mom1=0 ; mom1<(int)mc_parent_index->at(imom).size() ; mom1++)
					// {
						// int jmom = mc_parent_index->at(imom)[mom1];
						// cout<<"idmom2["<<mom<<"]="<<mc_pdgId->at(jmom)<<", ";
					// }
				// }
				// cout<<endl;
			// }
			continue;
		}
		
		truth_all_mc_m->push_back( mc_m->at(t)*MeV2GeV );
		truth_all_mc_pt->push_back( mc_pt->at(t)*MeV2GeV );
		truth_all_mc_eta->push_back( mc_eta->at(t) );
		truth_all_mc_phi->push_back( mc_phi->at(t) );
		truth_all_mc_pdgId->push_back( mc_pdgId->at(t) );
		truth_all_mc_status->push_back( mc_status->at(t) );
		truth_all_mc_barcode->push_back( mc_barcode->at(t) );
		truth_all_mc_charge->push_back( mc_charge->at(t) );
		
		/////////////////////////////////////////////////////////////////////////////////
		// FILL THE pTtoIndexMapTruth MAP WITH THE PT(KEY) AND INDEX(VALUE) /////////////
		pTtoIndexMapTruth.insert(make_pair(mc_pt->at(t)*MeV2GeV,truth_valid_index)); ////
		/////////////////////////////////////////////////////////////////////////////////
		truth_valid_index++;
	}

	// SORT BY PT AND FIND THE INDICES OF THE FIRST 2 MUONS (HIGHEST PT).
	ai_truth = -1;
	bi_truth = -1;
	TString tsmcname = (TString)sMCsampleName;
	if(truth_valid_index>=2  &&  pTtoIndexMapTruth.size()>=2) 
	{
		pTSort(pTtoIndexMapTruth, ai_truth, bi_truth, truth_all_mc_charge);
	}
	else if(truth_valid_index==1 && pTtoIndexMapTruth.size()==1  &&  tsmcname.Contains("AlpgenJimmy"))
	{
		TMapdi::iterator it = pTtoIndexMapTruth.begin();
		ai_truth = it->second;
		bi_truth = it->second; // fake so there won't be seg faults...
	}
	else
	{
		//_WARNING("truth_valid_index<2 -> "+_s(truth_valid_index)+"  ||  pTtoIndexMapTruth.size()<2 -> "+_s((int)pTtoIndexMapTruth.size())+", skipping event");
		truth_valid_index = 0;
		truth_all_isValid = false;
		return;
	}
	// if(intermediate_index.size()!=2)
	// {
		// _WARNING("intermediate_index.size()!=2  ->  "+_s((int)intermediate_index.size())+", skipping event");
		// return;
	// }
	// if(intermediate_index[0]!=intermediate_index[1])
	// {
		// _WARNING("intermediate_index[0]  ->  "+_s(intermediate_index[0])+"  !=  intermediate_index[1] -> "+_s(intermediate_index[1])+", skipping event");
		// return;
	// }
	// if(mc_pdgId->at(intermediate_index[0])!=mc_pdgId->at(4)) // the "Z" is always number 4 in the event
	// {
		// _WARNING("mc_pdgId->at(intermediate_index[0]) -> "+_s(mc_pdgId->at(intermediate_index[0]))+"  !=  mc_pdgId->at(4) -> "+_s(mc_pdgId->at(4))+", skipping event");
		// return;
	// }
	
	// the incoming quarks are always at the 2 and 3 places in the event
	// if(mc_pdgId->at(2) > PDTTOP || mc_pdgId->at(3) > PDTTOP) // both have to be quarks
	// {
		// _WARNING("mc_pdgId->at(2)>PDTTOP -> "+_s(mc_pdgId->at(2))+" ||  mc_pdgId->at(3)>PDTTOP -> "+_s(mc_pdgId->at(3))+", skipping event");
		// return;
	// }
	// if(mc_pdgId->at(2)!=(-1*mc_pdgId->at(3))) // to have opposite flavor
	// {
		// _WARNING("mc_pdgId->at(2)!=(-1*mc_pdgId->at(3))");
		// return;
	// }
	
	for(int q=0 ; q<11 ; q++)
	{
		truth_all_partons_mc_m->push_back( mc_m->at(q)*MeV2GeV );
		truth_all_partons_mc_pt->push_back( mc_pt->at(q)*MeV2GeV );
		truth_all_partons_mc_eta->push_back( mc_eta->at(q) );
		truth_all_partons_mc_phi->push_back( mc_phi->at(q) );
		truth_all_partons_mc_pdgId->push_back( mc_pdgId->at(q) );
		truth_all_partons_mc_status->push_back( mc_status->at(q) );
		truth_all_partons_mc_barcode->push_back( mc_barcode->at(q) );
		truth_all_partons_mc_charge->push_back( mc_charge->at(q) );
	}
	
	// CALCULATE ALL THE 'EVENT-LEVEL' VARIABLES (DI-MUON VARIABLES)
	if(truth_valid_index==1 && pTtoIndexMapTruth.size()==1  &&  tsmcname.Contains("AlpgenJimmy"))
	{
		truth_all_isValid = true;
		// _INFO("tsmcname="+(string)tsmcname+" -> 1mu event");
		return; // do not calculate the dimuon truth variables
	}
	else if( truth_valid_index>=2  &&  ai_truth>=0  &&  bi_truth>=0  &&  ai_truth!=bi_truth )
	{
		if( truth_all_mc_charge->at(ai_truth)*truth_all_mc_charge->at(bi_truth) >= 0. ) // now require opposite charge
		{
			truth_valid_index = 0;
			truth_all_isValid = false;
			return;
		}
		
		graphicObjects::all_vxp_n = -999;
		truth_all_mc_vxp_n = -999;
		
		truth_all_isValid = true;

		float c1 = truth_all_mc_charge->at(ai_truth);
		float c2 = truth_all_mc_charge->at(bi_truth);
		TLorentzVector* p1 = new TLorentzVector();
		TLorentzVector* p2 = new TLorentzVector();
		p1->SetPtEtaPhiM( truth_all_mc_pt->at(ai_truth), truth_all_mc_eta->at(ai_truth), truth_all_mc_phi->at(ai_truth), truth_all_mc_m->at(ai_truth));
		p2->SetPtEtaPhiM( truth_all_mc_pt->at(bi_truth), truth_all_mc_eta->at(bi_truth), truth_all_mc_phi->at(bi_truth), truth_all_mc_m->at(bi_truth));
		
		truth_all_Mhat       = imass(p1,p2);
		truth_all_CosThetaCS = cosThetaCollinsSoper(p1,c1, p2,c2);
		truth_all_CosThetaHE = cosThetaBoost(p1,c1, p2,c2);
		truth_all_ySystem    = ySystem(p1,p2);
		truth_all_QT         = QT(p1,p2);
		truth_all_betaQ      = magBetaSystem(p1,p2);
		truth_all_betazQ     = betaiSystem(p1,p2,3);
		truth_all_betaTQ     = betaTSystem(p1,p2);

		delete p1;
		delete p2;
	}
}


void analysisSkeleton::fillRecon()
{
	_DEBUG("analysisSkeleton::fillRecon");
	recon_all_mutype->push_back(classify3332null[ai]);
	recon_all_mutype->push_back(classify3332null[bi]);
	recon_all_E->push_back(mu_E->at(ai)*MeV2GeV);
	recon_all_E->push_back(mu_E->at(bi)*MeV2GeV);
	recon_all_pt->push_back(mu_pt->at(ai)*MeV2GeV);
	recon_all_pt->push_back(mu_pt->at(bi)*MeV2GeV);
	recon_all_m->push_back(mu_m->at(ai)*MeV2GeV);
	recon_all_m->push_back(mu_m->at(bi)*MeV2GeV);
	recon_all_eta->push_back(mu_eta->at(ai));
	recon_all_eta->push_back(mu_eta->at(bi));
	recon_all_phi->push_back(mu_phi->at(ai));
	recon_all_phi->push_back(mu_phi->at(bi));
	recon_all_px->push_back(mu_px->at(ai)*MeV2GeV);
	recon_all_px->push_back(mu_px->at(bi)*MeV2GeV);
	recon_all_py->push_back(mu_py->at(ai)*MeV2GeV);
	recon_all_py->push_back(mu_py->at(bi)*MeV2GeV);
	recon_all_pz->push_back(mu_pz->at(ai)*MeV2GeV);
	recon_all_pz->push_back(mu_pz->at(bi)*MeV2GeV);
	recon_all_charge->push_back(mu_charge->at(ai));
	recon_all_charge->push_back(mu_charge->at(bi));
	recon_all_ptcone20->push_back( mu_ptcone20->at(ai)*MeV2GeV );
	recon_all_ptcone20->push_back( mu_ptcone20->at(bi)*MeV2GeV );
	recon_all_ptcone30->push_back( mu_ptcone30->at(ai)*MeV2GeV );
	recon_all_ptcone30->push_back( mu_ptcone30->at(bi)*MeV2GeV );
	recon_all_ptcone40->push_back( mu_ptcone40->at(ai)*MeV2GeV );
	recon_all_ptcone40->push_back( mu_ptcone40->at(bi)*MeV2GeV );
	recon_all_etcone20->push_back( mu_etcone20->at(ai)*MeV2GeV );
	recon_all_etcone20->push_back( mu_etcone20->at(bi)*MeV2GeV );
	recon_all_etcone30->push_back( mu_etcone30->at(ai)*MeV2GeV );
	recon_all_etcone30->push_back( mu_etcone30->at(bi)*MeV2GeV );
	recon_all_etcone40->push_back( mu_etcone40->at(ai)*MeV2GeV );
	recon_all_etcone40->push_back( mu_etcone40->at(bi)*MeV2GeV );
	recon_all_nucone20->push_back( mu_nucone20->at(ai) );
	recon_all_nucone20->push_back( mu_nucone20->at(bi) );
	recon_all_nucone30->push_back( mu_nucone30->at(ai) );
	recon_all_nucone30->push_back( mu_nucone30->at(bi) );
	recon_all_nucone40->push_back( mu_nucone40->at(ai) );
	recon_all_nucone40->push_back( mu_nucone40->at(bi) );
	recon_all_allauthor->push_back( mu_allauthor->at(ai) );
	recon_all_allauthor->push_back( mu_allauthor->at(bi) );
	recon_all_author->push_back( mu_author->at(ai) );
	recon_all_author->push_back( mu_author->at(bi) );
	recon_all_beta->push_back( mu_beta->at(ai) );
	recon_all_beta->push_back( mu_beta->at(bi) );
	recon_all_isMuonLikelihood->push_back( mu_isMuonLikelihood->at(ai) );
	recon_all_isMuonLikelihood->push_back( mu_isMuonLikelihood->at(bi) );
	recon_all_matchchi2->push_back( mu_matchchi2->at(ai) );
	recon_all_matchchi2->push_back( mu_matchchi2->at(bi) );
	recon_all_matchndof->push_back( mu_matchndof->at(ai) );
	recon_all_matchndof->push_back( mu_matchndof->at(bi) );
	
	recon_all_y->push_back(y(pmu[ai]));
	recon_all_y->push_back(y(pmu[bi]));
	recon_all_id->push_back((mu_charge->at(ai)<0.) ? PDTMU : -1*PDTMU);
	recon_all_id->push_back((mu_charge->at(bi)<0.) ? PDTMU : -1*PDTMU);
	recon_all_theta->push_back( pmu[ai]->Theta() );
	recon_all_theta->push_back( pmu[bi]->Theta() );
	
	TLorentzVector* p1 = new TLorentzVector();
	TLorentzVector* p2 = new TLorentzVector();
	p1->SetPtEtaPhiE( mu_pt->at(ai)*MeV2GeV, mu_eta->at(ai), mu_phi->at(ai), mu_E->at(ai)*MeV2GeV);
	p2->SetPtEtaPhiE( mu_pt->at(bi)*MeV2GeV, mu_eta->at(bi), mu_phi->at(bi), mu_E->at(bi)*MeV2GeV);
	float c1 = mu_charge->at(ai);
	float c2 = mu_charge->at(bi);
	recon_all_Mhat = imass(p1,p2);
	recon_all_CosThetaCS = cosThetaCollinsSoper(p1,c1, p2,c2);
	recon_all_CosThetaHE = cosThetaBoost(p1,c1, p2,c2);
	recon_all_ySystem = ySystem(p1,p2);
	recon_all_QT = QT(p1,p2);
	recon_all_betaQ  = magBetaSystem(p1,p2);
	recon_all_betazQ = betaiSystem(p1,p2,3);
	recon_all_betaTQ = betaTSystem(p1,p2);
	delete p1;
	delete p2;
	
	recon_all_vxp_n = vxp_n;
	
	recon_all_isValid = true;
}

void analysisSkeleton::fillSingleTruthAndRecon(bool passRecon)
{
	_DEBUG("analysisSkeleton::fillSingleTruthAndRecon");
	
	//////////////////
	fillTruth(); /////
	//////////////////
	
	
	///////////////////////////////////////////////// recon part
	if(passRecon)
	{
		int muSize = (int)mu_pt->size();
		for(int mu=0 ; mu<muSize ; mu++)
		{
			///////////////////////////////////
			if(!muQAflags[mu]) continue; //////
			///////////////////////////////////
		
			recon_all_E->push_back(mu_E->at(mu)*MeV2GeV);
			recon_all_pt->push_back(mu_pt->at(mu)*MeV2GeV);
			recon_all_m->push_back(mu_m->at(mu)*MeV2GeV);
			recon_all_eta->push_back(mu_eta->at(mu));
			recon_all_phi->push_back(mu_phi->at(mu));
			recon_all_px->push_back(mu_px->at(mu)*MeV2GeV);
			recon_all_py->push_back(mu_py->at(mu)*MeV2GeV);
			recon_all_pz->push_back(mu_pz->at(mu)*MeV2GeV);
			recon_all_charge->push_back(mu_charge->at(mu));
			recon_all_ptcone20->push_back( mu_ptcone20->at(mu)*MeV2GeV );
			recon_all_ptcone30->push_back( mu_ptcone30->at(mu)*MeV2GeV );
			recon_all_ptcone40->push_back( mu_ptcone40->at(mu)*MeV2GeV );
			recon_all_etcone20->push_back( mu_etcone20->at(mu)*MeV2GeV );
			recon_all_etcone30->push_back( mu_etcone30->at(mu)*MeV2GeV );
			recon_all_etcone40->push_back( mu_etcone40->at(mu)*MeV2GeV );
			recon_all_nucone20->push_back( mu_nucone20->at(mu) );
			recon_all_nucone30->push_back( mu_nucone30->at(mu) );
			recon_all_nucone40->push_back( mu_nucone40->at(mu) );
			recon_all_allauthor->push_back( mu_allauthor->at(mu) );
			recon_all_author->push_back( mu_author->at(mu) );
			recon_all_beta->push_back( mu_beta->at(mu) );
			recon_all_isMuonLikelihood->push_back( mu_isMuonLikelihood->at(mu) );
			recon_all_matchchi2->push_back( mu_matchchi2->at(mu) );
			recon_all_matchndof->push_back( mu_matchndof->at(mu) );
			
			recon_all_y->push_back(y(pmu[mu]));
			recon_all_id->push_back((mu_charge->at(mu)<0.) ? PDTMU : -1*PDTMU);
			recon_all_theta->push_back( pmu[mu]->Theta() );
		}
		
		recon_all_vxp_n = vxp_n;
		recon_all_isValid = true;
	}
	
	tree_truth->Fill(); ///////////////////////////////
	if(m_truth_counter%m_trees_counter_mod==0) ////////
	{                               ////////////////////////
		tree_truth->FlushBaskets(); ///////////////////
		//tree_truth->Write("", TObject::kOverwrite); ///
	} //////////////////////////////////////////////////////
	m_truth_counter++;
}

void analysisSkeleton::applyTagNProbe(TMapsb& cutsToSkip)
{
	_DEBUG("analysisSkeleton::applyTagNProbe");
	bool pass;
	
	pass = true;
	pass = (pass && preselection(cutsToSkip))    ? true : false;
	pass = (pass && singleSelection(cutsToSkip)) ? true : false;
	if(pass)
	{
		/////////////////////////
		// Tag&Probe mask ///////
		//fillTagNProbe(); ////////
		fill_tNp(); /////////////
		/////////////////////////
		
		/////////////////////////////////////////
		// Truth efficiency mask ////////////////
		if(AS_isMC) fillTruthEfficiency(); /////////
		/////////////////////////////////////////
		
		////////////////////////////////////////////////////////
		// fill the efficiency tree ////////////////////////////
		tree_efficiency->Fill(); ///////////////////////////////
		if(m_efficiency_counter%m_trees_counter_mod==0) ////////
		{                               ////////////////////////
			tree_efficiency->FlushBaskets(); ///////////////////
			//tree_efficiency->Write("", TObject::kOverwrite); ///
		} //////////////////////////////////////////////////////
		m_efficiency_counter++; ////////////////////////////////
		////////////////////////////////////////////////////////
	}
}

void analysisSkeleton::applyTruth()
{
	_DEBUG("analysisSkeleton::applyTruth");
	///////////////////////////
	// fill all events ////////
	fillTruth(); //////////////
	///////////////////////////

	bool didItPass = true;
	// passing an empty string will deal with it as if there is a skipped cut
	// and therefore no fill will be done in the pre-/single-/double-selection calls:
	didItPass      = (didItPass && preselection("noFills"))    ? true : false;
	didItPass      = (didItPass && singleSelection("noFills")) ? true : false;
	if(do2MUselection)
	{
		didItPass      = (didItPass && doubleSelection("noFills")) ? true : false;
	}
	/////////////////////////////////////////////
	// fill the recon vars only if passed ///////
	// but fill the *tree* anyway, also if //////
	// these vars are empty so the matching /////
	// to truth will be easy ////////////////////
	if(didItPass) fillRecon(); //////////////////
	/////////////////////////////////////////////
	
	////////////////////////////////////////////////////////
	// fill the truth tree ////////////////////////////
	tree_truth->Fill(); ///////////////////////////////
	if(m_truth_counter%m_trees_counter_mod==0) ////////
	{                               ////////////////////////
		tree_truth->FlushBaskets(); ///////////////////
		//tree_truth->Write("", TObject::kOverwrite); ///
	} //////////////////////////////////////////////////////
	m_truth_counter++; ////////////////////////////////
	////////////////////////////////////////////////////////
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

bool analysisSkeleton::preselection(string sSkipCut)
{
	_DEBUG("analysisSkeleton::preselection(string sSkipCut)");
	TMapsb cutsToSkip;
	cutsToSkip.insert(make_pair(sSkipCut,true));
	return preselection(cutsToSkip);
}

bool analysisSkeleton::singleSelection(string sSkipCut)
{
	_DEBUG("analysisSkeleton::singleSelection(string sSkipCut)");
	TMapsb cutsToSkip;
	cutsToSkip.insert(make_pair(sSkipCut,true));
	return singleSelection(cutsToSkip);
}

bool analysisSkeleton::singleLooseSelection(string sSkipCut)
{
	_DEBUG("analysisSkeleton::singleLooseSelection(string sSkipCut)");
	TMapsb cutsToSkip;
	cutsToSkip.insert(make_pair(sSkipCut,true));
	return singleLooseSelection(cutsToSkip);
}

bool analysisSkeleton::doubleSelection(string sSkipCut)
{
	_DEBUG("analysisSkeleton::doubleSelection(string sSkipCut)");
	TMapsb cutsToSkip;
	cutsToSkip.insert(make_pair(sSkipCut,true));
	return doubleSelection(cutsToSkip);
}

inline bool analysisSkeleton::throwInfo(string cutName)
{
	bool show = false;
	if     (RunNumber==180124 && lbn==493 && EventNumber==68526315)  show = true;  
	else if(RunNumber==183003 && lbn==723 && EventNumber==121099951) show = true;
	else if(RunNumber==183054 && lbn==198 && EventNumber==21026988)  show = true;
	else if(RunNumber==183780 && lbn==434 && EventNumber==7827222)   show = true;
	else if(RunNumber==184169 && lbn==644 && EventNumber==104197129) show = true;
	else if(RunNumber==186169 && lbn==386 && EventNumber==47351357)  show = true;
	else if(RunNumber==186721 && lbn==643 && EventNumber==122815161) show = true;
	else if(RunNumber==187219 && lbn==589 && EventNumber==111010363) show = true;
	else if(RunNumber==180225 && lbn==300 && EventNumber==56266053)  show = true;
	else if(RunNumber==180225 && lbn==300 && EventNumber==56286764)  show = true;
	else if(RunNumber==180225 && lbn==300 && EventNumber==56310023)  show = true; 
	else if(RunNumber==180225 && lbn==300 && EventNumber==56415230)  show = true;
	else if(RunNumber==182454 && lbn==335 && EventNumber==35814784)  show = true;
	else if(RunNumber==182486 && lbn==282 && EventNumber==33852510)  show = true;
	else if(RunNumber==182766 && lbn==213 && EventNumber==5404925)   show = true;
	else if(RunNumber==183081 && lbn==634 && EventNumber==121479214) show = true;
	else if(RunNumber==183426 && lbn==145 && EventNumber==15925912)  show = true;
	else if(RunNumber==183462 && lbn==1251 && EventNumber==150376226)show = true;
	else if(RunNumber==183462 && lbn==1251 && EventNumber==150401710)show = true;
	else if(RunNumber==183462 && lbn==1251 && EventNumber==150474933)show = true;
	else if(RunNumber==183462 && lbn==1251 && EventNumber==150512192)show = true;
	else if(RunNumber==183602 && lbn==20 && EventNumber==282919)     show = true;
	else if(RunNumber==184022 && lbn==575 && EventNumber==68635084)  show = true;
	else if(RunNumber==184130 && lbn==1331 && EventNumber==198813439)show = true;  
	else if(RunNumber==184130 && lbn==1331 && EventNumber==198874411)show = true;  
	else if(RunNumber==184130 && lbn==1331 && EventNumber==198888828)show = true;  
	else if(RunNumber==184130 && lbn==1331 && EventNumber==198902925)show = true;  
	
	if(show) _INFO("Run-LB-Evt  "+_s(RunNumber)+" "+_s(lbn)+" "+_s(EventNumber)+" failed cut: "+cutName);
	return show;
}

inline bool analysisSkeleton::preselection(TMapsb& cutsToSkip)
{
	_DEBUG("analysisSkeleton::preselection(TMapsb& cutsToSkip)");
	bool isSkippedCut = (cutsToSkip.size()==0) ? false : true;
	TMapsb::iterator itrEnd = cutsToSkip.end();
	TMapsb::iterator itr;

	int nMus = (int)mu_pt->size();
	resetMuQAflags(nMus);
	
	passCutFlow    = true;
	passCurrentCut = true;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		////////////////////////////
		if(!passCutFlow) break; ////
		////////////////////////////
	
		///////////////////////////////////////////////////////////////////////////
		// ignore selection: //////////////////////////////////////////////////////
		float num = ii->first; ////////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="selection") continue; //////////
		///////////////////////////////////////////////////////////////////////////
		
		string sorderedcutname = ii->second;
		
		bool bSkipCut = false;
		bool bDoFill  = true;
		if(isSkippedCut)
		{
			itr = cutsToSkip.find(sorderedcutname);
			if(itr!=itrEnd) bSkipCut = itr->second;
			else
			{
				itr = cutsToSkip.find("noFills");
				if(itr!=itrEnd) bDoFill = false;
			}
		}

		if(sorderedcutname=="GRL"  &&  !bSkipCut)
		{
			passCurrentCut = ( isGRLCut((*m_cutFlowMapSVD)[sorderedcutname][0], isGRL) ) ? true : false;
		}
		
		else if(sorderedcutname=="Trigger"  &&  !bSkipCut)
		{
			string trigName;
			bool   trigVal;
			bool pass1Trig = false;
			for(int t=0 ; t<(int)vTriggers->size() ; t++)
			{
				trigName  = vTriggers->at(t);
				trigVal   = isTrigger( trigName );
				//pass1Trig = ( triggerCut((*m_cutFlowMapSVD)[sorderedcutname][0], trigVal, trigName) ) ? true : false;
				pass1Trig = isTrigger( vTriggers->at(t) );
				//if(throwInfo(sorderedcutname)) _INFO("Trigger="+trigName+":"+_s(trigVal));
				if(pass1Trig) break;
			}
			passCurrentCut = pass1Trig;
			//if(!passCurrentCut  &&  throwInfo(sorderedcutname)) _INFO("Trigger decision ="+_s(passCurrentCut));
		}
		
		else if(sorderedcutname=="PV"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			iVtx = getPVindex((int)cutval1, (int)cutval2, cutval3, vxp_type, vxp_nTracks, vxp_z);
			// passCurrentCut = ( findBestVertex((int)cutval1, (int)cutval2, cutval3,
							   // vxp_type, vxp_nTracks, vxp_z) ) ? true : false;
			passCurrentCut = (iVtx>=0) ? true : false;
			if(!passCurrentCut) iVtx = 0;
		}
		
		else
		{
			//_ERROR("unknown cut: "+sorderedcutname);
			continue;
		}
		
		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		
		////////////////////////////////////////////////////////////////////////////////////
		// cutFlow /////////////////////////////////////////////////////////////////////////
		if(passCutFlow  &&  !isSkippedCut  && bDoFill) fillCutFlow(sorderedcutname); ///////
		if(!passCutFlow && !isSkippedCut) throwInfo(sorderedcutname); //////////////////////
		////////////////////////////////////////////////////////////////////////////////////
	}
	
	return passCutFlow;
}

inline bool analysisSkeleton::singleSelection(TMapsb& cutsToSkip, bool isloose)
{
	_DEBUG("analysisSkeleton::singleSelection(TMapsb& cutsToSkip)");
	bool isSkippedCut = (cutsToSkip.size()==0) ? false : true;
	TMapsb::iterator itrEnd = cutsToSkip.end();
	TMapsb::iterator itr;
	
	int muSize  = (int)mu_charge->size();

	passCutFlow = true;
	
	_DEBUG("");
	
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		if(!isloose)
		{
			////////////////////////////
			if(!passCutFlow) break; ////
			////////////////////////////
		}
	
		///////////////////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////////////////
		float num = ii->first; ///////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; ///////
		///////////////////////////////////////////////////////////////////////////
		
		_DEBUG("");
		
		string sorderedcutname = ii->second;
		nMusPassed = 0;
		
		bool bSkipCut = false;
		bool bDoFill  = true;
		if(isSkippedCut)
		{
			itr = cutsToSkip.find(sorderedcutname);
			if(itr!=itrEnd) bSkipCut = itr->second;
			else
			{
				itr = cutsToSkip.find("noFills");
				if(itr!=itrEnd) bDoFill = false;
			}
		}
		
		_DEBUG("");
		
		
		if(sorderedcutname=="pT"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_pt->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
			_DEBUG("");
		}
		
		else if(sorderedcutname=="eta"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
			_DEBUG("");
		}
		
		else if(sorderedcutname=="d0"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( d0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_d0_exPV->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
			_DEBUG("");
		}
		
		else if(sorderedcutname=="z0"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( z0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_z0_exPV->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
			_DEBUG("");
		}
		
		else if(sorderedcutname=="isCombMu"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( isCombMuCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_isCombinedMuon->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
			_DEBUG("");
		}
		
		else if(sorderedcutname=="IDhits"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4 = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5 = (*m_cutFlowMapSVD)[sorderedcutname][4];
			float cutval6 = (*m_cutFlowMapSVD)[sorderedcutname][5];
			float cutval7 = (*m_cutFlowMapSVD)[sorderedcutname][6];
			float cutval8 = (*m_cutFlowMapSVD)[sorderedcutname][7];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( nIDhitsCut(cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,cutval7,cutval8,
											   mu_expectBLayerHit->at(mu),mu_nBLHits->at(mu),
											   mu_nPixHits->at(mu),mu_nPixelDeadSensors->at(mu),mu_nPixHoles->at(mu),
											   mu_nSCTHits->at(mu),mu_nSCTDeadSensors->at(mu),mu_nSCTHoles->at(mu),
											   mu_nTRTHits->at(mu),mu_nTRTOutliers->at(mu),
											   mu_eta->at(mu))) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
			_DEBUG("");
		}
		
		else if(sorderedcutname=="MShits"  &&  !bSkipCut)
		{
			float cutval1  = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2  = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3  = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4  = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5  = (*m_cutFlowMapSVD)[sorderedcutname][4];
			float cutval6  = (*m_cutFlowMapSVD)[sorderedcutname][5];
			float cutval7  = (*m_cutFlowMapSVD)[sorderedcutname][6];
			float cutval8  = (*m_cutFlowMapSVD)[sorderedcutname][7];
			float cutval9  = (*m_cutFlowMapSVD)[sorderedcutname][8];
			float cutval10 = (*m_cutFlowMapSVD)[sorderedcutname][9];
			float cutval11 = (*m_cutFlowMapSVD)[sorderedcutname][10];
			float cutval12 = (*m_cutFlowMapSVD)[sorderedcutname][11];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( nMShitsCut( cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,cutval7,cutval8,cutval9,cutval10,cutval11,cutval12,
											 mu_nMDTBIHits->at(mu), mu_nMDTBMHits->at(mu), mu_nMDTBOHits->at(mu),
											 mu_nMDTEIHits->at(mu), mu_nMDTEMHits->at(mu), mu_nMDTEOHits->at(mu),
											 mu_nMDTBEEHits->at(mu), mu_nMDTEEHits->at(mu), mu_nMDTBIS78Hits->at(mu),
											 mu_nRPCLayer1PhiHits->at(mu), mu_nRPCLayer2PhiHits->at(mu), mu_nRPCLayer3PhiHits->at(mu),
											 mu_nTGCLayer1PhiHits->at(mu), mu_nTGCLayer2PhiHits->at(mu), mu_nTGCLayer3PhiHits->at(mu), mu_nTGCLayer4PhiHits->at(mu),
											 mu_nCSCEtaHits->at(mu), mu_nCSCPhiHits->at(mu)
											)
							 ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
			_DEBUG("");
		}
		
		else if(sorderedcutname=="isolation30" && !AS_isQCD && doIsolation &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( isolationXXCut((*m_cutFlowMapSVD)[sorderedcutname][0],"isolation30",mu_pt->at(mu), mu_ptcone30->at(mu)) ) ? true : false;
				//thisMuPass = ( isolationXXCut((*m_cutFlowMapSVD)[sorderedcutname][0],"isolation30",
				//mu_me_qoverp->at(mu), mu_me_theta->at(mu), mu_ptcone30->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
			_DEBUG("");
		}
		
		else if(sorderedcutname=="constrainedAntiIsolation30" && AS_isQCD && doIsolation &&  !bSkipCut)
		{
			float cutval1  = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2  = (*m_cutFlowMapSVD)[sorderedcutname][1];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( constrainedAntiIsolationXXCut(cutval1,cutval2,"isolation30",mu_pt->at(mu), mu_ptcone30->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
			_DEBUG("");
		}
		
		else
		{
			//_ERROR("unknown cut: "+sorderedcutname);
			continue;
		}
		
		_DEBUG("");
		
		//////////////////////////////////////////////////////////////////////////
		// increment if passes the cut flow //////////////////////////////////////
		int nMinMuons = (do2MUselection) ? 2 : 1; ////////////////////////////////
		passCutFlow = (passCutFlow  &&  nMusPassed>=nMinMuons) ? true : false; ///
		if(!passCutFlow && inApplySingleSelection) throwInfo(sorderedcutname); ///
		//////////////////////////////////////////////////////////////////////////
		
		_DEBUG("");
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		// cutFlow ///////////////////////////////////////////////////////////////////////////////////////////
		if(passCutFlow  &&  !isSkippedCut
						&&  bDoFill
						&&  !isloose) fillCutFlow(sorderedcutname);
		
		_DEBUG("");
						
		if(passCutFlow  &&  !isSkippedCut 
						&&  sorderedcutname=="pT"
						&&  inApplySingleSelection
						&&  bDoFill)
		{
			(*fCand)	<< "Run-LB-Evt  "
						<< RunNumber  << " "
						<< lbn 		 << " "
						<< EventNumber
						<< endl;
		}
		
		_DEBUG("");
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		
	} // end for(m_cutFlowOrdered)
	
	_DEBUG("singleSelection="+_s(passCutFlow));
	
	return passCutFlow;
}

inline bool analysisSkeleton::singleLooseSelection(TMapsb& cutsToSkip)
{
	_DEBUG("analysisSkeleton::singleLooseSelection(TMapsb& cutsToSkip)");
	bool isSkippedCut = (cutsToSkip.size()==0) ? false : true;
	TMapsb::iterator itrEnd = cutsToSkip.end();
	TMapsb::iterator itr;
	
	int muSize  = (int)mu_charge->size();

	passCutFlow = true;
	
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		////////////////////////////
		if(!passCutFlow) break; ////
		////////////////////////////
	
		///////////////////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////////////////
		float num = ii->first; ///////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; ///////
		///////////////////////////////////////////////////////////////////////////
		
		string sorderedcutname = ii->second;
		nMusPassed = 0;
		
		bool bSkipCut = false;
		bool bDoFill  = true;
		if(isSkippedCut)
		{
			itr = cutsToSkip.find(sorderedcutname);
			if(itr!=itrEnd) bSkipCut = itr->second;
			else
			{
				itr = cutsToSkip.find("noFills");
				if(itr!=itrEnd) bDoFill = false;
			}
		}
		
		
		if(sorderedcutname=="pT"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_pt->at(mu)) ) ? true : false;
				muLooseQAflags[mu] = (!muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muLooseQAflags[mu]) nMusPassed++;
			}
		}
		
		// if(sorderedcutname=="pTloose"  &&  !bSkipCut)
		// {
			// for(int mu=0 ; mu<muSize ; mu++)
			// {
				// thisMuPass = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_pt->at(mu)) ) ? true : false;
				// muLooseQAflags[mu] = (!muQAflags[mu]  &&  thisMuPass) ? true : false;
				// if(thisMuPass  &&  muLooseQAflags[mu]) nMusPassed++;
			// }
		// }
		
		else if(sorderedcutname=="etaLoose"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muLooseQAflags[mu] = (!muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muLooseQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="antid0"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( antid0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_d0_exPV->at(mu)) ) ? true : false;
				muLooseQAflags[mu] = (!muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muLooseQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="antiz0"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( antiz0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_z0_exPV->at(mu)) ) ? true : false;
				muLooseQAflags[mu] = (!muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muLooseQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="isCombMu"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( isCombMuCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_isCombinedMuon->at(mu)) ) ? true : false;
				muLooseQAflags[mu] = (!muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muLooseQAflags[mu]) nMusPassed++;
			}
		}
		
/* 		else if(sorderedcutname=="antiIsolation30"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( antiIsolationXXCut((*m_cutFlowMapSVD)[sorderedcutname][0],"isolation30",mu_pt->at(mu), mu_ptcone30->at(mu)) ) ? true : false;
				muLooseQAflags[mu] = (!muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muLooseQAflags[mu]) nMusPassed++;
			}
		} */
		
		else if(sorderedcutname=="constrainedAntiIsolation30"  &&  !bSkipCut)
		{
			float cutval1  = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2  = (*m_cutFlowMapSVD)[sorderedcutname][1];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( constrainedAntiIsolationXXCut(cutval1,cutval2,"isolation30",mu_pt->at(mu), mu_ptcone30->at(mu)) ) ? true : false;
				muLooseQAflags[mu] = (!muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muLooseQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="eTantiIsolation30"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( eTantiIsolationXXCut((*m_cutFlowMapSVD)[sorderedcutname][0],"isolation30", mu_etcone30->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="didmuTrigger"  &&  !bSkipCut)
		{
			mu_HLT_dr    = mu_EFMG_dr;    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			mu_HLT_index = mu_EFMG_index; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = !didmuTriggerCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_HLT_dr->at(mu), mu_HLT_index->at(mu)); // it has to be NON triger object
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="isLooseNoTight"  &&  !bSkipCut)
		{
			float cutval1  = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2  = (*m_cutFlowMapSVD)[sorderedcutname][1];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( isLooseNoTightCut(cutval1,cutval2, mu_loose->at(mu), mu_tight->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else
		{
			//_ERROR("unknown cut: "+sorderedcutname);
			continue;
		}
		
		/////////////////////////////////////////////////////////////////////////////////
		// increment if passes the cut flow /////////////////////////////////////////////
		passCutFlow = (passCutFlow  &&  nMusPassed>0) ? true : false; ///////////////////
		if(passCutFlow  &&  !isSkippedCut  && bDoFill) fillCutFlow(sorderedcutname); ////
		/////////////////////////////////////////////////////////////////////////////////
	} // end for(m_cutFlowOrdered)
	
	return passCutFlow;
}

inline bool analysisSkeleton::doubleSelection(TMapsb& cutsToSkip)
{
	_DEBUG("analysisSkeleton::doubleSelection(TMapsb& cutsToSkip)");
	bool isSkippedCut = (cutsToSkip.size()==0) ? false : true;
	TMapsb::iterator itrEnd = cutsToSkip.end();
	TMapsb::iterator itr;
	
	//////////////////////////////////////////
	// need at least 2 muons...///////////////
	int muSize = (int)mu_pt->size(); /////////
	if(muSize<2) return false; ///////////////
	//////////////////////////////////////////
	
	/////////////////////////////////////////////////////
	// count the good muons and find their id's /////////
	int nQAflags = countQAflags(); //////////////////////
	if(nQAflags<2) return false; ////////////////////////
	/////////////////////////////////////////////////////
	
	passCutFlow    = true;
	passCurrentCut = true;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		////////////////////////////
		if(!passCutFlow) break; ////
		////////////////////////////
	
		///////////////////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////////////////
		float num = ii->first; ////////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; ///////
		///////////////////////////////////////////////////////////////////////////
		
		string sorderedcutname = ii->second;
		
		bool bSkipCut = false;
		bool bDoFill  = true;
		if(isSkippedCut)
		{
			itr = cutsToSkip.find(sorderedcutname);
			if(itr!=itrEnd) bSkipCut = itr->second;
			else
			{
				itr = cutsToSkip.find("noFills");
				if(itr!=itrEnd) bDoFill = false;
			}
		}

		if(sorderedcutname=="oppositeChargeCandidates"  &&  !bSkipCut)
		{
			passCurrentCut = ( oppositeChargeCandidatesCut(mu_charge, muQAflags) ) ? true : false;
			if(passCurrentCut)
			{
				/////////////////////////////////////////////////////
				// see if there's a good pair (pT or imass sorted) //
				// and assign the ai and bi indices /////////////////
				assignPairIndices(); ////////////////////////////////
				if(nQAflags>2  &&  isMultiMuonPrint)
				{
					_INFO("MultiGoodMuon N{"
						  +_s(nQAflags)
						  +"}{run-lb-evt: "+_s(RunNumber)+"-"+_s(lbn)+"-"+_s(EventNumber)
						  +"} -> Assigned indices: ai["+_s(mu_charge->at(ai))+"]="+_s(ai)
						  +", bi["+_s(mu_charge->at(bi))+"]="+_s(bi));
					isMultiMuonPrint = false;
				}
				/////////////////////////////////////////////////////
			}
		}
		
		else if(sorderedcutname=="MShitsPairFormation"  &&  !bSkipCut)
		{
			float cutval1  = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2  = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3  = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4  = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5  = (*m_cutFlowMapSVD)[sorderedcutname][4];
			float cutval6  = (*m_cutFlowMapSVD)[sorderedcutname][5];
			float cutval7  = (*m_cutFlowMapSVD)[sorderedcutname][6];
			float cutval8  = (*m_cutFlowMapSVD)[sorderedcutname][7];
			passCurrentCut = nMShitsCut3233(cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,cutval7,cutval8,
											allow3_3st, allow3_2st, muQAflags, mu_sig_diff_qoverp,
											mu_eta, mu_phi, mu_charge,
											mu_nMDTBIHits, mu_nMDTBMHits, mu_nMDTBOHits,
											mu_nMDTEIHits, mu_nMDTEMHits, mu_nMDTEOHits,
											mu_nMDTBEEHits, mu_nMDTEEHits, mu_nMDTBIS78Hits,
											mu_nRPCLayer1PhiHits, mu_nRPCLayer2PhiHits, mu_nRPCLayer3PhiHits,
											mu_nTGCLayer1PhiHits, mu_nTGCLayer2PhiHits, mu_nTGCLayer3PhiHits, mu_nTGCLayer4PhiHits,
											mu_nCSCEtaHits, mu_nCSCPhiHits,
											ai, bi); // this will set up the ai and bi indices
			_DEBUG("");
		}

		else if(sorderedcutname=="imass"  &&  !bSkipCut)
		{
			passCurrentCut = ( imassCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		else if(sorderedcutname=="imassMax"  &&  !bSkipCut)
		{
			passCurrentCut = ( imassMaxCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		else if(sorderedcutname=="etaSum"  &&  !bSkipCut)
		{
			passCurrentCut = ( etaSumCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		else
		{
			//_ERROR("unknown cut: "+sorderedcutname);
			continue;
		}
		
		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		
		//////////////////////////////////////////////////////////////////////////////////
		// cutFlow ///////////////////////////////////////////////////////////////////////
		if(passCutFlow   &&  !isSkippedCut  &&  bDoFill) fillCutFlow(sorderedcutname); ///
		if(!passCutFlow  &&  !isSkippedCut)              throwInfo(sorderedcutname); /////
		//////////////////////////////////////////////////////////////////////////////////
		
	} // end for(m_cutFlowOrdered)
	
	return passCutFlow;
}


