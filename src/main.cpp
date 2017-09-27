#include<iostream>
/*#include"readChem.cpp"
#include"readTherm.cpp"*/
#include"nEqComb.cpp"
using std::cout;
using std::string;
using std::endl;

int main()
{
	/*chemTab *cT;
	thermDat *tT;

	reactor *R;

	cT =new chemTab("global1.chem");
	cout<<"HI: Chem Table Initialized"<<endl;

	//cT->loadFromFile("global1.chem");
	cout<<cT->nSpecies<<endl;
	cout<<"Species 0 is: "<<cT->getSpecies(0)<<endl;
	cout<<"# of Reactions: "<<cT->mReactions<<endl;
	double set[3];
	cT->getReactionConst(0,set);
	cout<<"For Reaction 1 A="<<set[0]<<", b="<<set[1]<<" and Ea="<<set[2]<<endl;
	cout<<cT->species[0]<<endl;


	tT=new thermDat("NASAtherm.dat",cT->nSpecies,(cT->species));*/
	
	nEqComb nE= nEqComb("global1.chem","NASAtherm.dat");

	


	return 0;



}
