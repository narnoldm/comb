#include<iostream>
#include<cmath>
#include"readChem.cpp"
#include"readTherm.cpp"


using namespace::std;

class nEqComb
{
	public:
	chemTab *cT;
	thermDat *tT;
	int ns,mr;

	nEqComb(string chemfile,string thermfile)
	{
		cT=new chemTab(chemfile);
		ns=cT->nSpecies;
		mr=cT->mReactions;
		tT=new thermDat(thermfile,ns,(cT->species));
	}

	void calcStateFT(double *Y,double &T,double &h, double &R, double &cp,double &gamma)
	{
		double x[ns];
		massToMole(x,Y);
		double MWm=moleWeightMix(Y);
		calcTherm(cp,R,gamma,T,Y);
		//Sensible enthalpy
		h=0;
		h=cp*T;
		
		for(int n=0;n<ns;n++)
			h=h+ x[n]/(MWm)*(tT->hf[n]*8314);

	}
	void calcStateFH(double *Y,double &h,double &T)
	{
		double hf=0.0,Mwm,hs;
		double x[ns];
		double Tguess=T;
		massToMole(x,Y);
		Mwm= moleWeightMix(Y);
		for(int n=0;n<ns;n++)
			hf=hf+(tT->hf[n]*8314)*x[n]/Mwm;
		hs=h-hf;
		T=solveT(Y,hs,300);
		

	}
	double solveT(double *Y,double &hs,double Tguess)
	{
		int itermax=50,iter;
		double error,errormax=1e-7;
		double Tres,h,cp,R,gamma;
		iter=0;

		do{
		iter++;
		calcTherm(cp,R,gamma,Tguess,Y);
		h=cp*Tguess;

		Tres= Tguess - (h-hs)/cp;
		error=Tguess-Tres;
		if(fabs(error)<=errormax)
		{
			return Tres;
		}
		Tguess=Tres;
		/*
		cout<<"Tguess="<<Tguess<<endl;
		cout<<"h="<<h<<endl;
		cout<<"error="<<error;
		*/
		}
		while(iter<itermax);
		cerr<<"TEMP no converg"<<endl;
		throw(-1);
	}



	void calcSource(double *Y,double &T,double &rho,double *w)
	{
		double concen[ns];
		double reaction=0;
		double kf[mr];
		
		calcAr(kf,T,reaction);

		for(int n=0;n<ns;n++)
		{	
			w[n]=0.0;
			concen[n]=Y[n]*rho/(tT->mw[n]);
			//cout<<"concentration of "<<cT->species[n]<<"="<<concen[n]<<endl;
		}
		for(int n=0;n<ns;n++)
		{
			for(int m=0;m<mr;m++)
			{
				double csc=1;
				for(int b=0;b<ns;b++)
				{
					//cout<<"csc=csc*"<<concen[b]<<"^"<<cT->mn[m*ns+b]<<endl;
					csc=csc*pow(concen[b],cT->mn[m*ns+b]);
					//cout<<csc<<endl;
				}
				w[n]= w[n]+ (cT->nuT[m*ns+n])*kf[m]*csc;
			}
			w[n]=w[n]/rho*(tT->mw[n]);
			//cout<<"w[n]"<<w[n]<<endl;
		}
		
		


	}
	void calcAr(double *kf,double &T,double &m)
	{
		for(int m=0;m<mr;m++)
		{
			//cout<<"A= "<<cT->a[m]<<endl<<"b= "<<cT->b[m]<<endl<<"eA="<<cT->eA[m]<<endl;
			kf[m]=(cT->a[m])*pow(T,cT->b[m])*exp((cT->eA[m])/T);
			//cout<<"kf["<<m<<"]= "<<kf[m]<<"="<<(cT->a[m])<<"*"<<pow(T,cT->b[m])<<"*exp("<<-(cT->eA[m])/(1.987*T)<<")"<<endl;
		}
	}

	void calcTherm(double &cp,double &R,double &gamma,double &T,double *Y)
	{
		cpRMix(T,Y,cp,R);
		gamma=cp/(cp-R);
	}
	double moleWeightMix(double *y)
	{
		double MWm=0.0;
		double x[ns];
		massToMole(x,y);
		for(int n=0;n<ns;n++)
			MWm=MWm+(x[n]*tT->mw[n]);
		//cout<<MWm;
		return MWm;
	}

	void massToMole(double *x,double *y)
	{
		double den=0.0;

		for(int n=0;n<ns;n++)
			den=den+(y[n]/tT->mw[n]);
		for(int n=0;n<ns;n++)
			x[n]= (y[n]/tT->mw[n])/den;
	}

	double cpRMix(double &T, double *y,double &cp, double &R)
	{
		double MWm=moleWeightMix(y);
		double X[ns];
		double tmp=0;
		double t[5];
		cp=0;
		t[0]=1;
		t[1]=T;
		t[2]=t[1]*T;
		t[3]=t[2]*T;
		t[4]=t[3]*T;
		R=8314/MWm;
		for(int n=0;n<ns;n++)
		{
			tmp=0.0;
			for(int i=0;i<5;i++)
			{
				if(t[1]>1000)
					tmp=tmp+(tT->ah[n*7+i])*t[i];
				else
					tmp=tmp+(tT->ac[n*7+i])*t[i];
			}
			//cout<<"tmp "<<tmp<<endl;
			tmp= tmp*(8314/tT->mw[n]);
			//cout<<"tmp*8314/mw "<<tmp<<endl;
			//cout<<"Mw: "<<tT->mw[n]<<endl;
			cp=cp+tmp*y[n];
			//cout<<"cp"<<endl;
			//cout<<cp<<endl;
		}
		
		//return cp; //J/(kgK)

	}


};

