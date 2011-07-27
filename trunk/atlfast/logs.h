#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>


#ifndef __CINT__
#include <boost/lexical_cast.hpp>
#else
// If needed forward declare the boost entity as 'simply' as possible
template <typename T> class boost_ptr;
#endif
//#include <boost/lexical_cast.hpp>


using namespace std;

#ifndef LOGS_H
#define LOGS_H

enum DBG
{
	SILENT,
	VISUAL
};

enum MSG
{
	DBG,
	INF,
	WRN,
	ERR
};

static int global_dbg_lvl = VISUAL;

string log(const char* file, int line, int type, int level, string message)
{
	ostringstream os;
	
	string stype = "";
	switch(type)
	{
		case DBG: stype = "[DEBUG] ";   break;
		case INF: stype = "[INFO] ";    break;
		case WRN: stype = "[WARNING] "; break;
		case ERR: stype = "[ERROR] ";   break;
		default:  stype = "[???] ";     break;
	}
	
	os << stype << file << " +" << line << ": " << message;
	
	if(global_dbg_lvl!=SILENT)
	{
		if(level==VISUAL) cout << os.str() << endl;
	}
	
	return os.str();
}

#define LOG(x,y,z) log(__FILE__, __LINE__, (x),(y),(z))
//#define LOG_DEBUG(x)   log(__FILE__, __LINE__, DBG,(x))
//#define LOG_INFO(x)    log(__FILE__, __LINE__, INF,(x))
//#define LOG_WARNING(x) log(__FILE__, __LINE__, WRN,(x))
//#define LOG_ERROR(x)   log(__FILE__, __LINE__, ERR,(x))


static inline double validate_double(string str)
{
	if(str.substr(0,1)=="0")
	{
		size_t pos = str.find('.');
		if(pos==string::npos)
		{
			LOG(ERR,VISUAL,"cannot validate string=" + str + " (didn't find a decimal period). exit now.");
			exit(-1);
		}
	}

	double x;
	try
	{
		x = boost::lexical_cast<double>(str);
	}
	catch(boost::bad_lexical_cast&)
	{
		LOG(ERR,VISUAL,"cannot validate string=" + str + " (cannot cast it to double). exit now.");
		exit(-1);
	}
	return x;
}


static inline bool validate_bool(string str)
{
	if(str=="false" || str=="0") return false;
	else if(str=="true" || str=="1") return true;
	else
	{
		cout << "ERROR: cannot validate string=" << str << " (cannot be read as a boolean). exit now." << endl;
		exit(-1);
	}
	return true;
}

static inline string tostring(int x)
{
	stringstream strm;
	string str;
	strm << x;
	strm >> str;
	return str;
}

static inline string tostring(double x)
{
	stringstream strm;
	string str;
	strm << x;
	strm >> str;
	return str;
}

static inline int toint(string str)
{
	stringstream strm;
	int x;
	strm << str;
	strm >> x;
	return x;
}

static inline double todouble(string str)
{
	stringstream strm;
	double x;
	strm << str;
	strm >> x;
	return x;
}

static inline double validate_double(const char* cc) { return validate_double((string)cc); }
static inline int    validate_int(string str)        { return (int)validate_double(str); }
static inline int    validate_int(const char* cc)    { return validate_int((string)cc); }
static inline float  validate_float(string str)      { return (float)validate_double(str); }
static inline float  validate_float(const char* cc)  { return validate_float((string)cc); }
static inline bool   validate_bool(const char* cc)   { return validate_bool((string)cc); }		
static inline int    toint(const char* cc)           { return toint((string)cc); }
static inline double todouble(const char* cc)        { return todouble((string)cc); }

#endif

