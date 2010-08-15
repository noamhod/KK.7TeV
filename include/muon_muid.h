/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef MUON_MUID_H
#define MUON_MUID_H

class muon_muid : virtual public particleBase
{
	public:

	public:
		muon_muid();
		muon_muid(physics* phys);
		~muon_muid();

		virtual int  getNParticles();
		virtual void setParticle(int index); // mandatory to implement
		void setMore(int index);     // user input, not mandatory

};
#endif

