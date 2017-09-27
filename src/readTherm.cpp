#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
//using std::string;
//using std::cout;
//using std::endl;
//using std::ifstream;

using namespace::std;



class thermDat
{
	public:
	double *ah,*ac;
	int ns;
	string *sp;
	ifstream read;

	thermDat(string filename,int nSpecies,string *species)
	{
		cout<<"Loading Therm Data()"<<endl;
		ns=nSpecies;
		sp=species;
		ah=new double[7*ns];
		ac=new double[7*ns];
		loadData(filename,ns,sp);
		skipLines(2);

	}

	~thermDat(){};


	void loadData(string filename,int nSpecies,string *species)
	{
		read.open(filename.c_str());
		if(!read)
			cout<<"file not found"<<endl;

	}
	void skipLines(int n)
	{
		string str;
		for(int i=0;i<n;i++)
		{
		getline(read,str);
		cout<<str<<endl;
		}
	}

};
