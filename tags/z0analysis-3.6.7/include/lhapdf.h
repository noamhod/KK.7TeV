/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifndef LHAPDF_LOCAL_H
#define LHAPDF_LOCAL_H

#include "LHAPDF/LHAPDF.h" // ../../lhapdf_current/include/LHAPDF/LHAPDF.h ()
#include <iterator>
#include <iostream>
#include <cstdlib>

#include "logs.h"
#include "enums.h"
#include "integrals.h"

using namespace integrals;

namespace lhapdf
{

static const double sLHC = 7000.*7000.;
static bool issetpath = false;
static bool ispdfinit = false;
static const int quarks[] = {-PDTTOP,-PDTBOT,-PDTCHM,-PDTSTR,-PDTUP,-PDTDWN,0,PDTDWN,PDTUP,PDTSTR,PDTCHM,PDTBOT,PDTTOP};
static const string quarknames[] = {"tbar","bbar","cbar","sbar","ubar","dbar","g","d","u","s","c","b","t"};
static string pdfname = "";

inline string qname(int f)
{
	return quarknames[f+PDTTOP];
}

//////////////////////////////////////////////////////////
inline void setpdfpath(string path)
{
	LHAPDF::setPDFPath(path);
	issetpath = true;
}

inline void initset(string name, int subset, bool doprint=false)
{
	if(!issetpath) _FATAL("pdf sets path was not set");
	LHAPDF::initPDFSet(name, LHAPDF::LHGRID, subset);
	pdfname   = name;
	ispdfinit = true;
	if(doprint)
	{
		//const double Q = 10.0;
		cout << "alphas(mZ^0) = " << LHAPDF::alphasPDF(mZ0) << endl;
		cout << "qcdlam4      = " << LHAPDF::getLam4(subset) << endl;
		cout << "qcdlam5      = " << LHAPDF::getLam5(subset) << endl;
		cout << "orderPDF     = " << LHAPDF::getOrderPDF() << endl;
		cout << "xmin         = " << LHAPDF::getXmin(subset) << endl;
		cout << "xmax         = " << LHAPDF::getXmax(subset) << endl;
		cout << "q2min        = " << LHAPDF::getQ2min(subset) << endl;
		cout << "q2max        = " << LHAPDF::getQ2max(subset) << endl;
		cout << "orderalfas   = " << LHAPDF::getOrderAlphaS() << endl;
		cout << "num flav     = " << LHAPDF::getNf() << endl;
		cout << "name         = " << name << endl;
		cout << "number       = " << LHAPDF::numberPDF() << endl;
	}
	// Show initialisation banner only once
	LHAPDF::setVerbosity(LHAPDF::LOWKEY); // or LHAPDF::SILENT, for no banner at all
}

inline void initsubset(int subset)
{
	if(!ispdfinit) _FATAL("pdf was not initialized");
	if(subset<0 || subset>=LHAPDF::numberPDF()) _FATAL("set haven't got subset="+_s(subset));
	LHAPDF::initPDF(subset);
}

inline void initerrorsets()
{
	if(!ispdfinit) _FATAL("pdf was not initialized");
	LHAPDF::initPDFSetM(1,pdfname,LHAPDF::LHGRID); // central
	LHAPDF::initPDFSetM(2,pdfname,LHAPDF::LHGRID); // plus
	LHAPDF::initPDFSetM(3,pdfname,LHAPDF::LHGRID); // minus
}

inline int neigensets(int subset)
{
	if(!ispdfinit) _FATAL("pdf was not initialized");
	return (int)(LHAPDF::numberPDFM(subset)/2);
}

inline void initerrorset(int point, int eigenset)
{
	if(!ispdfinit) _FATAL("pdf was not initialized");
	if(point<1 || point>3) _FATAL("point can be 1,2 or 3");
	LHAPDF::initPDFM(point, eigenset);
}

inline double xpdf(int point, double x, double Q, int f)
{
	if(!ispdfinit) _FATAL("pdf was not initialized");
	if(f==PDTGLU)
	{
		_WARNING("flavor f="+_s(f)+" is probably gluon (changed to f=0)");
		f = 0;
	}
	if(f<-PDTTOP || f>PDTTOP) _FATAL("flavor f="+_s(f)+" is not supported");
	return LHAPDF::xfxM(point, x, Q, f);
}

inline int getpdfsetsize()
{
	if(!ispdfinit) _FATAL("pdf was not initialized");
	return LHAPDF::numberPDF();
}

inline double xpdf(double x, double Q, int f)
{
	if(!ispdfinit) _FATAL("pdf was not initialized");
	if(f==PDTGLU)
	{
		_WARNING("flavor f="+_s(f)+" is probably gluon (changed to f=0)");
		f = 0;
	}
	if(f<-PDTTOP || f>PDTTOP) _FATAL("flavor f="+_s(f)+" is not supported");
	return LHAPDF::xfx(x, Q, f);
}


//////////////////////////
double rapidityMax(double s)
{
	if(s<=0) _FATAL("s can not be zero or negative");
	return fabs(0.5*log(sLHC/s));
}

double rapidity2Bjorkenx(double s, double y, bool isAnti)
{
	if(s<=0) _FATAL("s can not be zero or negative");
	double x = (!isAnti) ? sqrt(s/sLHC)*exp(y) : sqrt(s/sLHC)*exp(-y);
	if(fabs(fabs(x)-1.)<1.e-6) return 1.;
	if(x<0. || x>1.) _FATAL("x<0 or x>1  -> in s="+_s(s)+", y="+_s(y,8)+", isAnti="+_s(isAnti)+" -> x="+_s(x,8));
	return x;
}

double rapidity(double x1, double x2)
{
	if (x1>1 || x1<0 || x2>1 ||x2<0) _FATAL("x1 or x2 is out of range");
	return(0.5*log(x1/x2));
}


//////////////////////////////////////////////////////////////////////////
inline double pdfintegrand(double y, double s, int f)
{
	if(s<=0.) _FATAL("s cannot be zero or negative");
	double Q        = sqrt(s);
	double xq       = rapidity2Bjorkenx(s,y,false);
	double xqbar    = rapidity2Bjorkenx(s,y,true);
	double xpdfq    = xpdf(xq,Q,f);
	double xpdfqbar = xpdf(xqbar,Q,-f);
	double integrand = (xpdfq*xpdfqbar)/s; // = ((xpdfq/xq)*(xpdfqbar/xqbar))/sLHC;
	return integrand;
}


class template_pdfintegrand
{
	double s;
	unsigned int f;
	public:
		template_pdfintegrand(double s0, unsigned int f0) : s(s0), f(f0) { }
		template<class X>
		X operator()(X y) const
		{
			return pdfintegrand(y,s,f);
		}
};

}
#endif

