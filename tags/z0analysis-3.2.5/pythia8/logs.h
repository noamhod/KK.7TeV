#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

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

#endif

