#include<iostream>
#include<fstream>
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
	//double y[4]={0,1,0,0};
	double y[4]={.25,.75,0.0,0.0};
	double x[4];
	double cp,R;
	/*cout<<"cp vals"<<endl;
	for(int i=0;i<5;i++)
		cout<<nE.tT->ac[1*7+i]<<endl;*/
	cout<<nE.tT->hf[3]<<endl;
	nE.massToMole(x,y);
	double T=1500;
	double gamma;
	nE.calcTherm(cp,R,gamma,T,y);
	for(int i=0;i<4;i++)
	{
		cout<<"Mass Fraction :"<<nE.cT->species[i]<<" "<< y[i]<<endl;
		cout<<"Mole Fraction :"<<nE.cT->species[i]<<" "<< x[i]<<endl;
	}
	cout<<"Cp of Mixture is : "<<cp<<endl;
	cout<<"R of Mixture is: "<<R<<endl;
	cout<<"Gamma of Mixture is: "<<gamma<<endl;
	int in=1;
	double p=101325;
	double rho=p/R/T;
	double *source;
	source=new double[4];
//	nE.calcSource(y,T,rho,source);
	//return 0;



	double dt=1.0e-10;
	nE.calcSource(y,T,rho,source);
	double y0[4];
	nE.calcTherm(cp,R,gamma,T,y);
	double h;
	nE.calcStateFT(y,T,h,R,cp,gamma);
	cout<<"INITIAL"<<endl;
        cout<<"Cp of Mixture is : "<<cp<<endl;
        cout<<"R of Mixture is: "<<R<<endl;
        cout<<"T="<< T<<endl;
	cout<<"rho="<<rho<<endl;
	cout<<"h="<<h<<endl;
	nE.calcStateFH(y,h,T);
        cout<<"Back"<<endl;
        cout<<"Cp of Mixture is : "<<cp<<endl;
        cout<<"R of Mixture is: "<<R<<endl;
        cout<<"T="<< T<<endl;
        cout<<"rho="<<rho<<endl;
        cout<<"h="<<h<<endl;





	for(int n=0;n<nE.ns;n++)
                        cout<<y[n]<<endl;
	//return 0;
	ofstream file;
	file.open("writeout.txt");
	for(int t=0;t<(1/dt);t++)
	{


		for(int n=0;n<nE.ns;n++)
			y0[n]=y[n];
		for(int rk=0;rk<4;rk++)
		{
			for(int n=0;n<nE.ns;n++)
				y[n]=y0[n]+dt/(4-rk)*source[n];
			nE.calcSource(y,T,rho,source);
		}
		file<<t*dt<<" ";
		for(int n=0;n<nE.ns;n++)
		{	//cout<<y[n]<<endl;
			file<<y[n]<<" ";
		}
		file<<T<<endl;
	        //cout<<"T="<< T<<endl;
		nE.calcTherm(cp,R,gamma,T,y);
		nE.calcStateFH(y,h,T);
		rho=p/R/T;
	        cout<<"Cp of Mixture is : "<<cp<<endl;
	        cout<<"R of Mixture is: "<<R<<endl;
		cout<<"T="<< T<<endl;
		cout<<"rho="<<rho<<endl;
	}

		for(int n=0;n<nE.ns;n++)
		{
                        cout<<y[n]<<endl;
		}
		cout<<"Cp of Mixture is : "<<cp<<endl;
                cout<<"R of Mixture is: "<<R<<endl;
                cout<<"T="<< T<<endl;
                cout<<"rho="<<rho<<endl;
	return 0;



}
