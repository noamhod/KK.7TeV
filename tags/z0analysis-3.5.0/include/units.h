/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifndef UNITS_H
#define UNITS_H

/*//////////////////////////////////////////////////////////////////////
------------------------------------------------------------------------------------------------------------------------------------
B->D:     [178044->180481]:   L1_MU10+EF_mu22        187.91   pb-1  wL=0.0423497425  https://atlas-lumicalc.cern.ch/results/25ef16/
E->H:     [180614->184169]:   L1_MU10+EF_mu22        1015.2   pb-1  wL=0.22879814    https://atlas-lumicalc.cern.ch/results/8ccfda/
I->K1_1:  [185353->186493]:   L1_MU10+EF_mu22        390.364  pb-1  wL=0.0879773023  https://atlas-lumicalc.cern.ch/results/8076cb/
I->K1_2:  [186516->186934]:   L1_MU11+EF_mu22_medium 470.015  pb-1  wL=0.105928446   https://atlas-lumicalc.cern.ch/results/391636/
Future:   [186965->191139]:   L1_MU11+EF_mu22_medium 2373.61  pb-1  wL=0.534946369   https://atlas-lumicalc.cern.ch/results/a6a915/
Total:    [178044->191139]:                          4437.099 pb-1
------------------------------------------------------------------------------------------------------------------------------------
*///////////////////////////////////////////////////////////////////////
static const double luminosity = 4.437099;  // 4.44414; // 3.562719; // 1/fb

static const float MeV2TeV = 1.e-6;
static const float MeV2GeV = 1.e-3;
static const float GeV2TeV = 1.e-3;
static const float GeV2MeV = 1.e+3;
static const float TeV2MeV = 1.e+6;
static const float TeV2GeV = 1.e+3;

static const double mb2fb = 1.e12;
static const double nb2fb = 1.e+6;
static const double nb2mb = 1.e-6;

static const float muonMass = 0.105658367; // GeV

static const float pi = 3.14159265;

static const float mZ0 = 91.1876; // GeV

#endif

