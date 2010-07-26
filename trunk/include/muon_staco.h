/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef MUON_STACO_H
#define MUON_STACO_H

class muon_staco : virtual public particleBase
{
	public:

	public:
		muon_staco();
		muon_staco(physics* phys);
		~muon_staco();
	
		virtual int  getNParticles();
		virtual void setParticle(int index); // mandatory to implement
		virtual void turnonBraches();
			void setMore(int index);     // user input, not mandatory

};
#endif

