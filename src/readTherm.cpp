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
	double *ah,*ac,*hf;
	double *mw;
	int ns;
	bool *found;
	string *sp,str,str2;
	double d1,d2;
	ifstream read;
	
	thermDat(string filename,int nSpecies,string *species)
	{
		cout<<"Loading Therm Data()"<<endl;
		ns=nSpecies;
		sp=species;
		ah=new double[7*ns];
		ac=new double[7*ns];
		mw=new double[ns];
		hf=new double[ns];
		loadData(filename,ns,sp);
		cout<<"Therm Data Ready()"<<endl;
	}

	~thermDat(){};


	void loadData(string filename,int nSpecies,string *species)
	{
		read.open(filename.c_str());
		if(!read)
			cout<<"file not found"<<endl;

		found=new bool[ns];
		for(int i=0;i<ns;i++)
			found[i]=0;
		//skipLines(6);
		//read>>str>>d2;
		//cout<<str<<endl;
		//cout<<d2<<endl;
		skipLines(2);
		while(read)
		{
			read>>str;
			//cout<<str<<endl;
			for(int n=0;n<ns;n++)
			{
				if(found[n]==0)
				{
				//cout<<"Comparing "<<str<<" with "<<sp[n]<<endl;
					if(str.compare(sp[n])==0)
					{
						//cout<<"wo"<<endl;
						read.seekg(70-str.size(),ios::cur);
						read>>mw[n];
						skipLines(1);
						read>>ah[7*n]>>ah[7*n+1]>>ah[7*n+2]>>ah[7*n+3]>>ah[7*n+4];
						skipLines(1);
						read>>ah[7*n+5]>>ah[7*n+6]>>ac[7*n]>>ac[7*n+1]>>ac[7*n+2];
						skipLines(1);
						read>>ac[7*n+3]>>ac[7*n+4]>>ac[7*n+5]>>ac[7*n+6]>>hf[n];
						skipLines(1);
						cout<<sp[n]<<" Loaded"<<endl;
						cout<<"MW= "<<mw[n]<<endl;
						found[n]=1;
					}
				}
			}
			skipLines(4);
		}


	}
	void skipLines(int n)
	{
		string str;
		for(int i=0;i<n;i++)
		{
		getline(read,str);
		//cout<<str<<endl;
		}
	}

};
