#include<iostream>
#include"readChem.cpp"

using std::cout;
using std::string;
using std::endl;

int main()
{
	chemTab *cT;

	cT =new chemTab("global1.chem");
	cout<<"HI: Chem Table Initialized"<<endl;

	//cT->loadFromFile("global1.chem");
	cout<<cT->nSpecies<<endl;
	cout<<"Species 0 is: "<<cT->getSpecies(0)<<endl;
	cout<<"# of Reactions: "<<cT->mReactions<<endl;
	double set[3];
	cT->getReactionConst(0,set);
	cout<<"For Reaction 1 A="<<set[0]<<", b="<<set[1]<<" and Ea="<<set[2]<<endl;

	return 0;



}
