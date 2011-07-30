#include "basics.h"

#ifndef STR_H
#define STR_H

string tostring(int x)
{
	stringstream strm;
	string str;
	strm << x;
	strm >> str;
	return str;
}

string tostring(double x)
{
        stringstream strm;
        string str;
        strm << x;
        strm >> str;
        return str;
}

string tostring(float x)
{
        stringstream strm;
        string str;
        strm << x;
        strm >> str;
        return str;
}

int toint(string str)
{
	stringstream strm;
	int x;
	strm << str;
	strm >> x;
	return x;
}

#endif
