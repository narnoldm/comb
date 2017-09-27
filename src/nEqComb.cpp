#include<iostream>
#include"readChem.cpp"
#include"readTherm.cpp"


using namespace::std;

class nEqComb
{
	public:
	chemTab *cT;
	thermDat *tT;

	nEqComb(string chemfile,string thermfile)
	{
		cT=new chemTab(chemfile);
		tT=new thermDat(thermfile,cT->nSpecies,(cT->species));
	}


};
