//File Loader.C
#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<vector<double> >+;
#pragma link C++ class vector<vector<float> >+;
#pragma link C++ class vector<vector<int> >+;
#pragma link C++ class vector<vector<unsigned int> >+;
#else
template class vector<vector<double> >;
template class vector<vector<float> >;
template class vector<vector<int> >;
template class vector<vector<unsigned int> >;
#endif
