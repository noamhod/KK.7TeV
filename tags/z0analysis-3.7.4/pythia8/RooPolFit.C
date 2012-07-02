#include "RooPolFit.h"
#include "RooAngularDistPdf.h"
#include "GlobalConstants.h"
#include "EffCalculator.h"

#include <RooConstVar.h>
#include <RooGaussian.h>
#include <RooChebychev.h>
#include <RooAbsPdf.h>
#include <RooHistPdf.h>
#include <RooAddPdf.h>
#include <RooProdPdf.h>
#include <RooEffProd.h>
#include <RooArgSet.h>
#include <RooPlot.h>
#include <RooPolynomial.h>
#include <RooGaussModel.h>
#include <RooGenericPdf.h>
#include <RooDataHist.h>
#include <RooChi2Var.h>
#include <RooDecay.h>
#include <RooDataSet.h>
#include <RooFitResult.h>
#include <TMinuit.h>
#include <TH2F.h>
#include <TF2.h>
#include <TTree.h>
#include <TRandom2.h>

using namespace RooFit;

inline void RooPolFit::initialize(string name, ModelType modelType, bool weightedEvents, bool tauSeparation) {
  MSG_INFO("RooPolFit::initialize()\n");

  // Initialize observables:
  // TODO: Check whether the range definition of muon pT affects this fit
  m_cosTh      = new RooRealVar("cosTh",  "cos(#theta^{*})", -1.0, 1.0);
  m_phi        = new RooRealVar("phi",    "#phi^{*}",        -M_PI, M_PI);
  m_muPts[0]   = new RooRealVar("muPt1",  "P_{T}(#mu1)",     0.,    100., "GeV");
  m_muPts[1]   = new RooRealVar("muPt2",  "P_{T}(#mu2)",     0.,    100., "GeV");
  m_muEtas[0]  = new RooRealVar("muEta1", "#eta(#mu1)",      -2.5,  2.5);
  m_muEtas[1]  = new RooRealVar("muEta2", "#eta(#mu2)",      -2.5,  2.5);
  m_tau        = new RooRealVar("tau",    "#tau",            -10.0, 10.0, "ps");
  m_weight     = new RooRealVar("weight", "Per-event weight", 0.0, 1000.0);

  // Initialize parameters:
  m_lamTh_prompt       = new RooRealVar("#lambda_{#theta} p",      "#lambda_{#theta} prompt",     -1., 1.);
  m_lamPhi_prompt      = new RooRealVar("#lambda_{#phi} p",        "#lambda_{#phi} prompt",       -1., 1.);
  m_lamThPhi_prompt    = new RooRealVar("#lambda_{#theta#phi} p",  "#lambda_{#theta#phi} prompt", -1., 1.);
  m_lamTh_nprompt      = new RooRealVar("#lambda_{#theta} np",     "#lambda_{#theta} prompt",     -1., 1.);
  m_lamPhi_nprompt     = new RooRealVar("#lambda_{#phi} np",       "#lambda_{#phi} prompt",       -1., 1.);
  m_lamThPhi_nprompt   = new RooRealVar("#lambda_{#theta#phi} np", "#lambda_{#theta#phi} prompt", -1., 1.);

  m_tau_promptSigma         = new RooRealVar("#sigma(#tau^{p})",   "#sigma(#tau^{prompt})",   1.0, 0.001, 10.);
  m_tau_npromptSigma        = new RooRealVar("#sigma(#tau^{np})",  "#sigma(#tau^{nprompt})",  1.0, 0.001, 10.);
  m_tau_npromptDecayConst   = new RooRealVar("#lambda(#tau^{np})", "#lambda(#tau^{nprompt})", 2.0, 0.1, 2.);
  m_tau_npromptFraction     = new RooRealVar("f_{np}",             "Non-prompt fraction",     0.5, 0.0, 1.0);

  m_ang_prompt         = NULL;
  m_ang_nprompt        = NULL;
  m_ang_condTau        = NULL;
  m_ang_eff_prompt     = NULL;
  m_ang_eff_nprompt    = NULL;
  m_ang_eff_condTau    = NULL;
  m_decay              = NULL;
  m_decay_prompt       = NULL;
  m_decay_nprompt      = NULL;

  m_maskJpsiPdf        = NULL;
  m_accJpsiPdf         = NULL;
  m_recoJpsiPdf        = NULL;
  m_trigJpsiPdf        = NULL;
  m_recoMuonPdf[1]     = NULL;
  m_recoMuonPdf[1]     = NULL;
  m_trigMuonPdf[0]     = NULL;
  m_trigMuonPdf[1]     = NULL;

  m_accJpsi_cosTh_phi  = NULL;
  m_recoJpsi_cosTh_phi = NULL;
  m_trigJpsi_cosTh_phi = NULL;
  m_accMuon_pt_eta     = NULL;
  m_recoMuon_pt_eta    = NULL;
  m_trigMuon_pt_eta    = NULL;

  m_fitResult          = NULL;
  m_bphysFitResult     = new FitResultWrapper();

  setFitName(name);
  setRangeCosTh( -1.0, 1.0 );
  setRangePhi  ( -M_PI, M_PI );
  setWeightedEvents(weightedEvents);
  setTauSeparation(tauSeparation);
  setModelType(modelType);
  setInitialGuessPrompt(0.0, 0.0, 0.0);
  setInitialGuessNprompt(0.0, 0.0, 0.0);
  setGenEvents(0);
}

inline void RooPolFit::finalize() {
  delete m_cosTh;
  delete m_phi;
  delete m_muPts[0];
  delete m_muPts[1];
  delete m_muEtas[0];
  delete m_muEtas[1];
  delete m_tau;
  delete m_weight;

  delete m_lamTh_prompt;
  delete m_lamPhi_prompt;
  delete m_lamThPhi_prompt;
  delete m_lamTh_nprompt;
  delete m_lamPhi_nprompt;
  delete m_lamThPhi_nprompt;

  delete m_tau_promptSigma;
  delete m_tau_npromptSigma;
  delete m_tau_npromptDecayConst;
  delete m_tau_npromptFraction;

  delete m_ang_prompt;
  delete m_ang_nprompt;
  delete m_ang_condTau;
  delete m_ang_eff_prompt;
  delete m_ang_eff_nprompt;
  delete m_ang_eff_condTau;
  delete m_decay_prompt;
  delete m_decay_nprompt;
  delete m_decay;

  delete m_dataSet;

  delete m_maskJpsiPdf;
  delete m_accJpsiPdf;
  delete m_recoJpsiPdf;
  delete m_trigJpsiPdf;
  delete m_recoMuonPdf[0];
  delete m_recoMuonPdf[1];
  delete m_trigMuonPdf[0];
  delete m_trigMuonPdf[1];

  delete m_fitResult;
  delete m_bphysFitResult;
}

RooAbsPdf* RooPolFit::getModel(ModelType modelType) {
  if (modelType == MODEL_UNDEFINED) modelType = m_modelType; // If model is undefined, use the defined fitter model
  switch (modelType) {
  case MODEL_PROMPT:      return getModelPrompt();
  case MODEL_NPROMPT:     return getModelNprompt();
  case MODEL_CONDTAU:     return getModelCondTau();
  case MODEL_PROMPT_EFF:  return getModelEffPrompt();
  case MODEL_NPROMPT_EFF: return getModelEffNprompt();
  case MODEL_CONDTAU_EFF: return getModelEffCondTau();
  default:
    MSG_WARNING("getModel: model type does not exist. Returning NULL\n");
    return NULL;
  }
}

inline void RooPolFit::setInitialGuessPrompt(float lamTh, float lamPhi, float lamThPhi) {
  m_init_lamTh_prompt    = lamTh;
  m_init_lamPhi_prompt   = lamPhi;
  m_init_lamThPhi_prompt = lamThPhi;

  if (m_lamTh_prompt)    { m_lamTh_prompt->setVal(m_init_lamTh_prompt);       } else { MSG_WARNING("setInitialGuessPrompt: m_lamTh_prompt is NULL\n"); }
  if (m_lamPhi_prompt)   { m_lamPhi_prompt->setVal(m_init_lamPhi_prompt);     } else { MSG_WARNING("setInitialGuessPrompt: m_lamPhi_prompt is NULL\n"); }
  if (m_lamThPhi_prompt) { m_lamThPhi_prompt->setVal(m_init_lamThPhi_prompt); } else { MSG_WARNING("setInitialGuessPrompt: m_lamThPhi_prompt is NULL\n"); }
}

inline void RooPolFit::setInitialGuessNprompt(float lamTh, float lamPhi, float lamThPhi) {
  m_init_lamTh_nprompt    = lamTh;
  m_init_lamPhi_nprompt   = lamPhi;
  m_init_lamThPhi_nprompt = lamThPhi;

  if (m_lamTh_nprompt)    { m_lamTh_nprompt->setVal(m_init_lamTh_nprompt);       } else { MSG_WARNING("setInitialGuessNprompt: m_lamTh_nprompt is NULL\n"); }
  if (m_lamPhi_nprompt)   { m_lamPhi_nprompt->setVal(m_init_lamPhi_nprompt);     } else { MSG_WARNING("setInitialGuessNprompt: m_lamPhi_nprompt is NULL\n"); }
  if (m_lamThPhi_nprompt) { m_lamThPhi_nprompt->setVal(m_init_lamThPhi_nprompt); } else { MSG_WARNING("setInitialGuessNprompt: m_lamThPhi_nprompt is NULL\n"); }
}

inline void RooPolFit::setMaps(TH2F* accJpsi_cosTh_phi,
                               TH2F* recoJpsi_cosTh_phi,
                               TH2F* trigJpsi_cosTh_phi,
                               TH2F* accMuon_pt_eta,
                               TH2F* recoMuon_pt_eta,
                               TH2F* trigMuon_pt_eta)  {
  if (not accJpsi_cosTh_phi)  MSG_WARNING("setMaps: accJpsi_cosTh_phi is NULL\n");
  if (not recoJpsi_cosTh_phi) MSG_WARNING("setMaps: recoJpsi_cosTh_phi is NULL\n");
  if (not trigJpsi_cosTh_phi) MSG_WARNING("setMaps: trigJpsi_cosTh_phi is NULL\n");
  if (not accMuon_pt_eta)     MSG_WARNING("setMaps: accMuon_pt_eta is NULL\n");
  if (not recoMuon_pt_eta)    MSG_WARNING("setMaps: recoMuon_pt_eta is NULL\n");
  if (not trigMuon_pt_eta)    MSG_WARNING("setMaps: trigMuon_pt_eta is NULL\n");
  m_accJpsi_cosTh_phi  = accJpsi_cosTh_phi;
  m_recoJpsi_cosTh_phi = recoJpsi_cosTh_phi;
  m_trigJpsi_cosTh_phi = trigJpsi_cosTh_phi;
  m_accMuon_pt_eta     = accMuon_pt_eta;
  m_recoMuon_pt_eta    = recoMuon_pt_eta;
  m_trigMuon_pt_eta    = trigMuon_pt_eta;
}

RooHistPdf* RooPolFit::mapToPdf(TH2F* map, const char* pdfName, RooArgSet argSet) {
  if (not map) { MSG_ERROR("mapToPdf: map is null\n"); }

  MSG_RED("mapToPdf \"%s\": %f\n", map->GetName(), map->GetEntries());

  // From RooDataHist constructor:
// Import(TH1&, Bool_t impDens) -- Import contents of the given TH1/2/3 into this binned dataset. The
//                                 ranges and binning of the binned dataset are automatically adjusted to
//                                 match those of the imported histogram.
//
//                                 Please note: for TH1& with unequal binning _only_,
//                                 you should decide if you want to import the absolute bin content,
//                                 or the bin content expressed as density. The latter is default and will
//                                 result in the same histogram as the original TH1. For certain type of
//                                 bin contents (containing efficiencies, asymmetries, or ratio is general)
//                                 you should import the absolute value and set impDens to kFALSE
  int  interpolationOrder = 1;     // TODO: Check the interpolation order
  bool impDens            = kTRUE; // TODO: Setting this to false screws up the maps (?!)
  RooDataHist* h = new RooDataHist("tmp",  "tmp",   argSet, Import(*map, impDens));

  // RooHistPdf neither owns or clone 'dhist' and the user must ensure the input histogram exists
  // for the entire life span of this PDF
  RooHistPdf*  pdf = new RooHistPdf(pdfName, pdfName, argSet, *h, interpolationOrder);

  return pdf;
}

bool RooPolFit::addEvent( float cosTh,  float cosThErr,
                          float phi,    float phiErr,
                          float muPt1,  float muPt1Err,
                          float muPt2,  float muPt2Err,
                          float muEta1, float muEta1Err,
                          float muEta2, float muEta2Err,
                          float tau,    float tauErr,
                          float weight, float weightErr) {
  if (cosThErr  <= 0.) { MSG_WARNING("Error uncertainty on cosTh is <= 0; Skipping event\n");     return false; }
  if (phiErr    <= 0.) { MSG_WARNING("Error uncertainty on phiErr is <= 0; Skipping event\n");    return false; }
  if (muPt1Err  <= 0.) { MSG_WARNING("Error uncertainty on muPt1Err is <= 0; Skipping event\n");  return false; }
  if (muPt2Err  <= 0.) { MSG_WARNING("Error uncertainty on muPt2Err is <= 0; Skipping event\n");  return false; }
  if (muEta1Err <= 0.) { MSG_WARNING("Error uncertainty on muEta1Err is <= 0; Skipping event\n"); return false; }
  if (muEta2Err <= 0.) { MSG_WARNING("Error uncertainty on muEta2Err is <= 0; Skipping event\n"); return false; }
  if (tauErr    <= 0.) { MSG_WARNING("Error uncertainty on tauErr is <= 0; Skipping event\n");    return false; }
  if (weightErr <  0.) { MSG_WARNING("Error uncertainty on weightErr is < 0; Skipping event\n");  return false; }

  if ((cosTh < -1.0)  || (cosTh > 1.0) ||
      (phi   < -M_PI) || (phi   > M_PI) ) { //YONATHAN:NEED TO FIT THE RANGE THAT IS DEFINED IN setRangeCosTh(), setRangePhi()??
    MSG_WARNING("addEvent: cosTh (%5.3f) / phi (%5.3f) outside boundaries. Skipping event\n", cosTh, phi);
    return false;
  }

  m_cosTh->setVal(cosTh);       m_cosTh->setError(cosThErr);
  m_phi->setVal(phi);           m_phi->setError(phiErr);
  m_muPts[0]->setVal(muPt1);    m_muPts[0]->setError(muPt1Err);
  m_muPts[1]->setVal(muPt2);    m_muPts[1]->setError(muPt2Err);
  m_muEtas[0]->setVal(muEta1);  m_muEtas[0]->setError(muEta1Err);
  m_muEtas[1]->setVal(muEta2);  m_muEtas[1]->setError(muEta2Err);
  m_tau->setVal(tau);           m_tau->setError(tauErr);
  m_weight->setVal(weight);     m_weight->setError(weightErr);
  //if (m_bWeightedEvents) { weight = 1.0; weightErr = 0.0; };
  m_dataSet->add(RooArgSet(*m_cosTh,
                           *m_phi,
                           *m_muPts[0],
                           *m_muPts[1],
                           *m_muEtas[0],
                           *m_muEtas[1],
                           *m_tau,
                           *m_weight),
                           weight,
                           weightErr);
  MSG_VERBOSE("Adding %8.3f, %8.3f (weight = %8.3f) to m_dataSet (entries = %d)\n", cosTh, phi, weight, m_dataSet->numEntries());

  return true;
}

void RooPolFit::createModels(bool useAccMaps, bool useRecoMaps, bool useTrigMaps) {
  // Angular distribution PDFs:
  const char* promptName      = Form("%s_prompt",  m_fitName.c_str());
  const char* npromptName     = Form("%s_nprompt", m_fitName.c_str());
  const char* condTauName     = Form("%s_condTau", m_fitName.c_str());
  const char* promptName_eff  = Form("%s_eff_prompt",  m_fitName.c_str());
  const char* npromptName_eff = Form("%s_eff_nprompt", m_fitName.c_str());
  const char* condTauName_eff = Form("%s_eff_condTau", m_fitName.c_str());

  // Pseudo proper-time PDFs:
  m_decay_prompt  = new RooGaussModel("decay_prompt",  "Prompt decay",     *m_tau, RooConst(0), *m_tau_promptSigma);
  m_decay_nprompt = new RooDecay("decay_nprompt",      "Non-prompt decay", *m_tau, *m_tau_npromptDecayConst, *m_decay_prompt, RooDecay::SingleSided);
  m_decay         = new RooAddPdf("decay",             "Total decay",      RooArgList(*m_decay_nprompt, *m_decay_prompt), *m_tau_npromptFraction);
//  t_sig_gauss_1 = new RooGaussModel("t_sig_gauss_1", "", *t, RooConst(0), *t_sig_gauss_sf_1, *t_err);
//  new RooDecay("t_sig_nprompt_decay_1", "", *t, *t_sig_nprompt_decay_tau, *t_sig_gauss_1, RooDecay::SingleSided);
//  RooAddPdf("t_sig", "", RooArgList(*t_sig_nprompt, *t_sig_prompt), *f_sig_nprompt);

  // Angular distribution PDFs:
  m_ang_prompt = new RooAngularDistPdf(promptName,
                                       "Angular distribution prompt",
                                       *m_cosTh,
                                       *m_phi,
                                       *m_lamTh_prompt,
                                       *m_lamPhi_prompt,
                                       *m_lamThPhi_prompt);
  m_ang_nprompt = new RooAngularDistPdf(npromptName,
                                        "Angular distribution non-prompt",
                                        *m_cosTh,
                                        *m_phi,
                                        *m_lamTh_nprompt,
                                        *m_lamPhi_nprompt,
                                        *m_lamThPhi_nprompt);

  RooAbsPdf* ang_promptDecay  = new RooProdPdf("ang_promptDecay",
                                               "Angular distribution prompt * prompt decay",
                                               RooArgSet(*m_decay_prompt, *m_decay_prompt));
  RooAbsPdf* ang_npromptDecay = new RooProdPdf("ang_npromptDecay",
                                               "Angular distribution non-prompt * non-prompt decay",
                                               RooArgSet(*m_decay_nprompt, *m_decay_nprompt));
  m_ang_condTau = new RooAddPdf(condTauName,
                                "Total conditional (prompt+nprompt) angular distribution x efficiencies",
                                RooArgSet(*ang_promptDecay,*ang_npromptDecay), // TODO: Should the decay be conditional as well?
                                *m_tau_npromptFraction); // TODO: Should there be a fraction here?

  // YONATHAN:IT MAY BE BETTER TO MULTIPLY THE MAPS AND GERNERATE LESS PDF'S???
  // Efficiency PDFs:
  m_accJpsiPdf   = mapToPdf(m_accJpsi_cosTh_phi,  "accJpsi_cosTh_phi",  RooArgSet(*m_cosTh, *m_phi));
  m_recoJpsiPdf  = mapToPdf(m_recoJpsi_cosTh_phi, "recoJpsi_cosTh_phi", RooArgSet(*m_cosTh, *m_phi));
  m_trigJpsiPdf  = mapToPdf(m_trigJpsi_cosTh_phi, "trigJpsi_cosTh_phi", RooArgSet(*m_cosTh, *m_phi));

  // TODO: Possibly need to merge the reco and trig muon PDFs
  m_recoMuonPdf[0] = mapToPdf(m_recoMuon_pt_eta, "recoMuon1_pt_eta", RooArgSet(*m_muEtas[0], *m_muPts[0]));
  m_recoMuonPdf[1] = mapToPdf(m_recoMuon_pt_eta, "recoMuon2_pt_eta", RooArgSet(*m_muEtas[1], *m_muPts[1]));
  m_trigMuonPdf[0] = mapToPdf(m_trigMuon_pt_eta, "trigMuon1_pt_eta", RooArgSet(*m_muEtas[0], *m_muPts[0]));
  m_trigMuonPdf[1] = mapToPdf(m_trigMuon_pt_eta, "trigMuon2_pt_eta", RooArgSet(*m_muEtas[1], *m_muPts[1]));


  // Full PDFs (including eff):
  // RooProdPdf is an efficient implementation of a product of PDFs of the form
  // PDF_1 * PDF_2 * ... * PDF_N PDFs may share observables. If that is the case any
  // irreducable subset of PDFS that share observables will be normalized with explicit
  // numeric integration as any built-in normalization will no longer be valid. Alternatively,
  // products using conditional PDFs can be defined,
  // e.g. F(x|y) * G(y) meaning a pdf F(x) _given_ y and a PDF G(y).
  // In this contruction F is only normalized w.r.t x and G is normalized w.r.t y.
  // The product in this construction is properly normalized.
  // If exactly one of the component PDFs supports extended likelihood fits,
  // the product will also be usable in extended mode, returning the number of expected
  // events from the extendable component PDF. The extendable component does not have
  // to appear in any specific place in the list

  int configuration = useAccMaps  << 0 |
                      useRecoMaps << 1 |
                      useTrigMaps << 2;
  MSG_PINK("Producing m_ang_eff_prompt configuration %d\n", configuration);

  switch (configuration) {
  case 0: // Run with no maps
    m_ang_eff_prompt  = m_ang_prompt;
    m_ang_eff_nprompt = m_ang_nprompt;
    m_ang_eff_condTau = m_ang_condTau;
    break;
  case 1: // Run with acc maps
    m_ang_eff_prompt = new RooProdPdf(promptName_eff,
                                      "Total prompt angular distribution x efficiencies",
                                      RooArgSet(*m_ang_prompt,
                                                *m_accJpsiPdf));
    m_ang_eff_nprompt = new RooProdPdf(npromptName_eff,
                                       "Total nprompt angular distribution x efficiencies",
                                       RooArgSet(*m_ang_nprompt,
                                                 *m_accJpsiPdf));
    // TODO: Add the conditional tau PDF to prompt and non prompt to separate them
    m_ang_eff_condTau = new RooProdPdf(condTauName_eff,
                                       "Total conditional (prompt+nprompt) angular distribution x efficiencies",
                                       RooArgSet(*m_ang_condTau,
                                                 *m_accJpsiPdf));
    break;
  case 3: // Run with acc + reco maps
    m_ang_eff_prompt = new RooProdPdf(promptName_eff,
                                      "Total prompt angular distribution x efficiencies",
                                      RooArgSet(*m_ang_prompt, *m_accJpsiPdf),
                                      Conditional(*m_recoMuonPdf[0], RooArgSet(*m_muEtas[0], *m_muPts[0])),
                                      Conditional(*m_recoMuonPdf[1], RooArgSet(*m_muEtas[1], *m_muPts[1])));
//    m_ang_eff_prompt = new RooProdPdf(promptName_eff,
//                                      "Total prompt angular distribution x efficiencies",
//                                      RooArgSet(*m_ang_prompt,
//                                                *m_accJpsiPdf,
//                                                *m_recoMuonPdf[0], *m_recoMuonPdf[1]));
    m_ang_eff_nprompt = new RooProdPdf(npromptName_eff,
                                       "Total nprompt angular distribution x efficiencies",
                                       RooArgSet(*m_ang_nprompt,
                                                 *m_accJpsiPdf,
                                                 *m_recoMuonPdf[0], *m_recoMuonPdf[1]));
    m_ang_eff_condTau = new RooProdPdf(condTauName_eff,
                                       "Total conditional (prompt+nprompt) angular distribution x efficiencies",
                                       RooArgSet(*m_ang_condTau,
                                                 *m_accJpsiPdf,
                                                 *m_recoMuonPdf[0], *m_recoMuonPdf[1]));
    break;
  case 7: // Run with all maps  
    m_ang_eff_prompt = new RooProdPdf(promptName_eff,
                                      "Total prompt angular distribution x efficiencies",
                                      RooArgSet(*m_ang_prompt,
                                                *m_accJpsiPdf,
                                                *m_recoMuonPdf[0], *m_recoMuonPdf[1],
                                                *m_trigMuonPdf[0], *m_trigMuonPdf[1]));
    m_ang_eff_nprompt = new RooProdPdf(npromptName_eff,
                                       "Total nprompt angular distribution x efficiencies",
                                       RooArgSet(*m_ang_nprompt,
                                                 *m_accJpsiPdf,
                                                 *m_recoMuonPdf[0], *m_recoMuonPdf[1],
                                                 *m_trigMuonPdf[0], *m_trigMuonPdf[1]));
    // TODO: Add the conditional tau PDF to prompt and non prompt to separate them
    m_ang_eff_condTau = new RooProdPdf(condTauName_eff,
                                       "Total conditional (prompt+nprompt) angular distribution x efficiencies",
                                       RooArgSet(*m_ang_condTau,
                                                 *m_accJpsiPdf,
                                                 *m_recoMuonPdf[0], *m_recoMuonPdf[1],
                                                 *m_trigMuonPdf[0], *m_trigMuonPdf[1]));
    break;
  } // End switch
}

// Generating a single onia event from a given set of onia pt, y, cosTh, phi and scenario
// Returns the TLorentzVectors of the dimuons, a polarization weight and whether onia is inside acceptance
void RooPolFit::generateOnia(double pt, double y, double cosTheta, double phi, PolScenario pol,
                             TLorentzVector* pos_tlv, TLorentzVector* neg_tlv, bool& inAcceptance) {
  double theta    = acos(cosTheta);
  double oniaMass = JPSIMASS*GeV;
  double muonMass = MUONMASS*GeV;

  //the vectors of the daughter muons in the rest frame of the Onium
  float muMo = sqrt((oniaMass*oniaMass/4.0) - muonMass*muonMass);

  pos_tlv->SetPxPyPzE(1.0*sin(theta)*cos(phi)*muMo,   1.0*sin(theta)*sin(phi)*muMo,  1.0*cos(theta)*muMo, oniaMass/2.0);
  neg_tlv->SetPxPyPzE(-pos_tlv->Px(), -pos_tlv->Py(), -pos_tlv->Pz(), pos_tlv->E());
  //which direction are we pointing in the lab?
  double pz = sqrt((pt*pt+oniaMass*oniaMass)*(sinh(y)*sinh(y)));
  double  p = sqrt(pt*pt+pz*pz);
  //different theta; the theta that the Onium is moving in.
  //the other theta above is the direction of the positve muon in the Onium rest frame
  double thetaLabFrame = asin(pt/p);
  //So notice the production plane is the xz plane BY CONSTRUCTION.
  //This is relevant when we need to know phi in the polarization weighting.
  pos_tlv->RotateY(thetaLabFrame);
  neg_tlv->RotateY(thetaLabFrame);
  //how fast are we going in the lab?
  double velocity = p / sqrt(p*p+oniaMass*oniaMass);
  pos_tlv->Boost(velocity*pt/p, 0.0, velocity*pz/p);
  neg_tlv->Boost(velocity*pt/p, 0.0, velocity*pz/p);

  //the big question: are both daughter muons in the detector's acceptance?
  double posEta = pos_tlv->Eta();
  double negEta = neg_tlv->Eta();

  Double_t muon1etaCut = 2.5;
  Double_t muon2etaCut = 2.5;
  Double_t muon1ptCut = 4.0;
  Double_t muon2ptCut = 4.0;
  inAcceptance = (muon1ptCut < pos_tlv->Perp() && muon2ptCut < neg_tlv->Perp() &&
                  fabs(pos_tlv->Eta()) < muon1etaCut && fabs(neg_tlv->Eta()) < muon2etaCut);
}

void RooPolFit::generator(long nEvents, bool accCut, EffCalculator* effCalc) {
  TRandom2 rndPt(1); // TODO: Each slice uses the same random generator values! Export randomizer
  TRandom2 rndY(2);
  TRandom2 rnd(3);
//  TRandom2 rndCosTh(3);
//  TRandom2 rndPhi(4);

  TF2 fAngDist("angDist", "(1.0 + [0]*x^2 + [1]*(1-x^2)*cos(2*y) + [2]*2*sqrt(1-x^2)*x*cos(y) ) / (4*TMath::Pi()*(1+[0]/3.0))",
               -1.0, 1.0, -TMath::Pi(), TMath::Pi());
  fAngDist.SetParameters(m_gen_lamTh_prompt, m_gen_lamPhi_prompt, m_gen_lamThPhi_prompt);

  RecoMapType recoMapType = RECOMAP_MC_MU_PT_ETA;
  TrigMapType trigMapType = TRIGMAP_MC_MU_PT_ETA;

  MSG_INFO("Generating for pt[%6.2f, %6.2f] rap[%6.2f, %6.2f]\n",
           m_rangePtMin, m_rangePtMax, m_rangeRapMin, m_rangeRapMax);
  m_dataSet = new RooDataSet("genDataSet", "Generated Dataset", RooArgSet(*m_cosTh,
                                                                          *m_phi,
                                                                          *m_muPts[0],
                                                                          *m_muPts[1],
                                                                          *m_muEtas[0],
                                                                          *m_muEtas[1],
                                                                          *m_tau,
                                                                          *m_weight),
                                                                          m_weight->GetName());
  for (long iEvent = 0; iEvent < nEvents; ++iEvent) {
    float  pt       = rndPt.Uniform(m_rangePtMin, m_rangePtMax);
    float  y        = rndY.Uniform(m_rangeRapMin, m_rangeRapMax);
    float  y_abs    = fabs(y);
    double cosTh    = 0.0; // rndCosTh.Uniform(-1.0, 1.0);
    double phi      = 0.0; // rndPhi.Uniform(-TMath::Pi(), TMath::Pi());
    fAngDist.GetRandom2(cosTh, phi);
    double cosThErr = 0.0001; // TODO: Add models for errors!
    double phiErr   = 0.0001;
    TLorentzVector muPos;
    TLorentzVector muNeg;
    bool   inAcceptance;
    PolScenario pol = POL_NONE;
    generateOnia(pt, y, cosTh, phi, pol, &muPos, &muNeg, inAcceptance);

    float muPtHi,       muPtLo;
    float muPtHiErr,    muPtLoErr;
    float muEtaChHi,    muEtaChLo;
    float muEtaChHiErr, muEtaChLoErr;
    float muPhiHi,      muPhiLo;
    if (muPos.Pt() > muNeg.Pt()) {
      muPtHi    = muPos.Pt();
      muPtLo    = muNeg.Pt();
      muEtaChHi = muPos.Eta();
      muEtaChLo = -muNeg.Eta(); // -1 is the charge (ch*eta)
      muPhiHi   = muPos.Phi();
      muPhiLo   = muNeg.Phi();
    } else {
      muPtHi    = muNeg.Pt();
      muPtLo    = muPos.Pt();
      muEtaChHi = -muNeg.Eta();  // -1 is the charge (ch*eta)
      muEtaChLo = muPos.Eta();
      muPhiHi   = muNeg.Phi();
      muPhiLo   = muPos.Phi();
    }
    muPtHiErr  = 0.05;
    muPtLoErr  = 0.05;
    muEtaChHiErr = 0.05;
    muEtaChLoErr = 0.05;

    float tau    = 0.0000; // TODO: Change this to represent PPT
    float tauErr = 0.0001; // TODO: Change this to represent PPT

    if ( accCut && not inAcceptance) continue;

    // Calculating reco / trig weight
    MapParams mPars(-1, -1, -1, -1, -1, -1,
                    y_abs, pt, (float) cosTh, (float) phi,
                    muPtHi, muEtaChHi, muPhiHi, COMBEFF,
                    muPtLo, muEtaChLo, muPhiLo, COMBEFF);
    float recoEff       = 1.0;
    float recoEffErr    = 0.0;
    float recoEffHi     = 1.0;
    float recoEffHiErr  = 0.0;
    float recoEffLo     = 1.0;
    float recoEffLoErr  = 0.0;
    float trigEff       = 1.0;
    float trigEffErr    = 0.0;
    float trigEffHi     = 1.0;
    float trigEffHiErr  = 0.0;
    float trigEffLo     = 1.0;
    float trigEffLoErr  = 0.0;
    if (inAcceptance) { // Cannot calculate efficiency outside of the acceptance range
      effCalc->getRecoEff(recoMapType, mPars, recoEff, recoEffErr, recoEffHi, recoEffHiErr, recoEffLo, recoEffLoErr);
      effCalc->getTrigEff(trigMapType, mPars, trigEff, trigEffErr, trigEffHi, trigEffHiErr, trigEffLo, trigEffLoErr);
    }
    trigEff = 1.0;

    float weight    = recoEff*trigEff;
    float weightErr = weight*sqrt(TMath::Power(recoEffErr/recoEff,2) + TMath::Power(trigEffErr/trigEff,2));
//    MSG_GREEN("genEvent %ld (%6.2f, %6.2f, %6.2f, %6.2f) => (%6.2f, %6.2f, %6.2f, %6.2f): (%6.4f, %d)\n",
//              iEvent, pt, y, cosTh, phi, muPos.Pt(), muPos.Eta(), muNeg.Pt(), muNeg.Eta(), weight, inAcceptance);

    addEvent(cosTh,     cosThErr,     phi,       phiErr,
             muPtHi,    muPtHiErr,    muPtLo,    muPtLoErr,
             muEtaChHi, muEtaChHiErr, muEtaChLo, muEtaChLoErr,
             tau,       tauErr,       weight,    weightErr);

    // TODO: This method only models the pure generation + acceptance
    // Think about how to implement the reco and trigger eff generators
    // Probably by multiplying by the eff values from appropriate eff maps
  }
}

void RooPolFit::generateToy(ModelType modelType) {
  if (modelType == MODEL_UNDEFINED) modelType = m_modelType; // If model is undefined, use the defined fitter model

  switch (modelType) {
  case MODEL_PROMPT:
    m_dataSet = m_ang_prompt->generate(RooArgSet(*m_cosTh, *m_phi), m_nGenEvents); // TODO: Add Proj for the mupt, eta?
    break;
  case MODEL_NPROMPT:
    m_dataSet = m_ang_nprompt->generate(RooArgSet(*m_cosTh, *m_phi), m_nGenEvents);
    break;
  case MODEL_CONDTAU:
    m_dataSet = m_ang_condTau->generate(RooArgSet(*m_cosTh, *m_phi, *m_tau), m_nGenEvents); // TODO: Should this have *m_tau or fraction? Should this be included with Conditional?
    break;
  // TODO: HOW DO I GENERATE FOR THE CONDITIONAL PDFs?
  case MODEL_PROMPT_EFF:
    m_dataSet = m_ang_eff_prompt->generate(RooArgSet(*m_cosTh, *m_phi), m_nGenEvents);
//    m_dataSet = m_ang_eff_prompt->generate(RooArgSet(*m_cosTh, *m_phi, *m_muPts[0], *m_muPts[1], *m_muEtas[0], *m_muEtas[1]), m_nGenEvents);
    break;
  case MODEL_NPROMPT_EFF:
    m_dataSet = m_ang_eff_nprompt->generate(RooArgSet(*m_cosTh, *m_phi), m_nGenEvents);
    break;
  case MODEL_CONDTAU_EFF:
    m_dataSet = m_ang_eff_condTau->generate(RooArgSet(*m_cosTh, *m_phi, *m_tau), m_nGenEvents); // TODO: Should this have *m_tau or fraction? Should this be included with Conditional?
    break;
  default:
    m_dataSet = NULL;
    MSG_FATAL("generateToy: Model undefined\n");
    break;
  }
}

bool RooPolFit::fit(ModelType modelType, int fitOutputLevel) {
  MSG_INFO("Start fit for %s\n", m_fitName.c_str());
  if (modelType == MODEL_UNDEFINED) modelType = m_modelType; // If model is undefined, use the defined fitter model

  if( !m_dataSet) {
    MSG_ERROR("No dataset has been created / define\n");
    return 0;
  }

  RooAbsPdf* model = getModel(modelType);
  // Perform the fit
  m_fitResult = model->fitTo( *m_dataSet,
                              ConditionalObservables(RooArgSet(*m_muPts[0],
                                                               *m_muPts[1],
                                                               *m_muEtas[0],
                                                               *m_muEtas[1],
                                                               *m_tau)), // TOOD: Add m_tau
                              PrintLevel(fitOutputLevel),
                              Strategy(2),
                              Save(kTRUE),
                              Timer(kTRUE),
                              SumW2Error(kTRUE),
                              NumCPU(8));

  // Storing results:
  TMinuit* gFit = gMinuit;
  bool fitStat = fitStatus(gFit);
  MSG_INFO("Fit %s\n", m_bphysFitResult->valid() ? "succeeded" : "failed");

  vector<std::string> parNames;
  vector<double>      parValues;
  vector<double>      parErrors;
  parNames.push_back("ENTRIES");
  parValues.push_back(m_dataSet->sumEntries());
  parErrors.push_back(0);
  const int nFitPars = 3;
  RooRealVar* fitPars[nFitPars] = { m_lamTh_prompt, m_lamPhi_prompt, m_lamThPhi_prompt };
  for (int iFitPar = 0; iFitPar < nFitPars; ++iFitPar) {
    parNames.push_back(fitPars[iFitPar]->GetName());
    parValues.push_back(fitPars[iFitPar]->getVal());
    parErrors.push_back(fitPars[iFitPar]->getError());
  }

  // Attaching results to bPhys wrapper for printing
  m_bphysFitResult->clear();
  m_bphysFitResult->setName(m_fitName);
  m_bphysFitResult->setParameters(parNames, parValues, parErrors);
  m_bphysFitResult->setValid(fitStat);
  m_bphysFitResult->setRoofitResult(m_fitResult);

  return fitStat;
}

bool RooPolFit::fitStatus(TMinuit* minuit) {
  if (!minuit) return false;

  TString stat = gMinuit->fCstatu;
  MSG_INFO("Minuit: %s\n", stat.Data());
  bool fitStat = stat.Contains("SUCCESSFUL")  ||
                 stat.Contains("CONVERGED")  ||
                 stat.Contains("OK");

  return fitStat;
}

// Print fit parameters:
void RooPolFit::print(TMinuit* minuit) {

}
