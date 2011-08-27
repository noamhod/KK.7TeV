/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef MONTECARLOHANDLER_H
#define MONTECARLOHANDLER_H

class montecarloXml : public XML
{
	public:
		montecarloXml()
		{
			ignoreString("obj");
			ignoreString("NAME");
			ignoreString("FLAG");
			ignoreString("file");
			ignoreString("kfactor");
			ignoreString("MINRANGE");
			ignoreString("MAXRANGE");
		}
		virtual ~montecarloXml(){}
		bool mask();

		/*
		  <obj NAME="DYmumu_75M120" FLAG="on">
			<number>150000</number>
			<internalnumber>1</internalnumber>
			<isbinned>true</isbinned>
			<dir>/data/hod/D3PDfin/rel16/DYmumu/muid/</dir>
			<nfiles>2</nfiles>
			<files>
				<file>mcLocalControl_DYmumu_75M120.1.root</file>
				<file>mcLocalControl_DYmumu_75M120.2.root</file>
			</files>
			<nevents>19996</nevents>
			<crosssection>817.05</crosssection>
			<crosssectionerr>0.05</crosssectionerr>
			<br>1</br>
			<geneff>1</geneff>
			<nkfactors>2</nkfactors>
			<kfactors>
			  <kfactor MINRANGE="0." MAXRANGE="100.">1.25</kfactor>
			  <kfactor MINRANGE="100." MAXRANGE="150.">1.25</kfactor>
			</kfactors>
			<mcweight>1</mcweight> <!--?????????????-->
			<pileup>1</pileup>     <!--?????????????-->
			<smearing>1</smearing> <!--?????????????-->
			<color>1</color>
			<linestyle>1</linestyle>
			<fillstyle>1</fillstyle>
			<description>
				The values are in pb
			</description>
		  </obj>
		*/
	
		// specific mask for montecarloXml.xml
		string name;
		string number;
		string flag;
		string dir;
		string nfiles;
		string file;
		string isbinned;
		string internalnumber;
		string crosssection;
		string crosssectionerr;
		string br;
		string geneff;
		string nkfactors;
		string minrange;
		string maxrange;
		string kfactor;
		string nevents;
		string color;
		string linestyle;
		string fillstyle;
		string mcweight;
		string pileup;
		string smearing;
		string description;
	private:
};



#endif

