//File Loader.C
#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<vector<double> >+;
#pragma link C++ class vector<vector<float> >+;
#pragma link C++ class vector<vector<int> >+;
#pragma link C++ class vector<vector<unsigned int> >+;
#pragma link C++ class vector<vector<unsigned short> >+;
#else
template class vector<vector<double> >;
template class vector<vector<float> >;
template class vector<vector<int> >;
template class vector<vector<unsigned int> >;
template class vector<vector<unsigned short> >;
#endif

typedef vector<vector<float> >          TVvf;
typedef vector<vector<double> >         TVvd;
typedef vector<vector<int> >            TVvi;
typedef vector<vector<unsigned int> >   TVvui;
typedef vector<vector<unsigned short> > TVvus;
