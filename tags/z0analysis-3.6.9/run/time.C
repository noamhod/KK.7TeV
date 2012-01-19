#include <ctime>
#include <iostream>
using namespace std;

double round(double x)
{
	const double sd = 1000; //for accuracy to 3 decimal places
	return int(x*sd + (x<0? -0.5 : 0.5))/sd;
}


void time()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    cout << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << endl;

	double x = 1000.03;
	double xr = round(x);
	cout << "x:" << x << " -> xr:" << xr << endl;

}
