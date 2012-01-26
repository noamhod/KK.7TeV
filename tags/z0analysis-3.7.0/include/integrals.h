/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifndef INTEGRALS_H
#define INTEGRALS_H

namespace integrals
{

//////////////////////////////////////////////////////////////////
// http://homepage.mac.com/sigfpe/Computing/fobjects.html
template<class F>
double integrate(const F &f, double xMin, double xMax, unsigned int nsegments=100)
{
	double dx        = (xMax-xMin)/((double)nsegments);
	double h         = dx/3.;
	double integrand = 0.;
	double I         = 0.;
	double x         = xMin;
	unsigned int i   = 0;
	
	while(i<=nsegments) // i=0(1st point),...,i=nsegments(point nth+1)
	{
		// calculate the integrand 
		integrand = f(x);

		// simpson
		if      (i==0 || i==nsegments)           I+=integrand;
		else if (i%2==0 && i!=0 && i!=nsegments) I+=2.*integrand;
		else                                     I+=4.*integrand;

		// propagate x and i
		x += dx;
		i++;
	}
	return(h*I);
}


class F
{
	double y;
	double z;
	public:
		F(double y0, double z0) : y(y0), z(z0) { }
		template<class X>
		X operator()(X x) const
		{
			return x*y*z;
		}
};

/*
int main() {
	. . .
	. . .
	F f(2,3);
	integrate(f,0,1);
	. . .
}
*/


}
#endif

