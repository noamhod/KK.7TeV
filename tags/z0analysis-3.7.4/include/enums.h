/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifndef ENUMS_H
#define ENUMS_H

enum pdtEnum { // *** note that this is not a complete list of pdt's particles ***
	PDTDWN=1, PDTUP=2, PDTSTR=3, PDTCHM=4, PDTBOT=5, PDTTOP=6,
	PDTBOTPRIME=7, PDTTOPPRIME=8,
	PDTE=11, PDTNUE=12, PDTMU=13, PDTNUMU=14, PDTTAU=15, PDTNUTAU=16,
	PDTTAUPRIME=17, PDTNUTAUPRIME=18,
	PDTGLU=21, PDTGAMMA=22, PDTZ=23, PDTWPLUS=24, PDTZPRIME0=32,PDTGRV=5000039,PDTKK=5000023,
	PDTFIRSTMESON=111, PDTLASTMESON=555,
	PDTFIRSTBARYON=1103, PDTLASTBARYON=5554
};

enum models
{
	ZPd3pd=-2,
	Z0d3pd=-1,
	Z0,ZP,KK,
	DT
};

enum enumMCs
{
	DYmumu=0,
	Diboson
};

#endif

