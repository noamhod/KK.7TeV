#include <stdio.h>
#include <iostream>

using namespace std;

void test(string sName="mcLocalControl_DYmumu_75M120")
{
	//string sName  = "mcLocalControl_DYmumu_75M120";
	string prefix = "mcLocalControl_DYmumu_";
	string::size_type loc = sName.find("M");
	string high = sName.substr(loc+1);
	string low = "";
	string chr = "";
	for(int i=(int)prefix.length() ; i<(int)loc ; i++)
	{
		chr = sName[i];
		if(chr!="M") low+=chr;
	}
	cout << "low = "  << low  << endl;
	cout << "high = " << high << endl;
}
