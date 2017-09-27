#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>

//using std::string;
//using std::cout;
//using std::endl;
//using std::ifstream;

using namespace::std;

class chemTab
{
	public:
	int nSpecies,mReactions;
	string *species;
	
	double *a, *b, *eA;
	double *nu1,*nu2,*nuT;
	chemTab(string filename)
	{
		loadFromFile(filename);
	}


	~chemTab(){}

	void loadFromFile(string filename)
	{
		ifstream read;
		read.open(filename.c_str());
		if(!read)
		{
			cout<<"Reaction File not found"<<endl;
			return;
		}
		string str="";
		while(read)
		{
			getline(read,str);
			//read>>str;
			str=str.substr(0,str.size()-1);
			cout<<str<<endl;
			/*cout<<str.size()<<endl;
			cout<<str.compare("REACTIONS")<<endl;
			cout<<str.compare("SPECIES")<<endl;*/
			if(str.compare("SPECIES")==0)
			{
				cout<<"Species_Load()"<<endl;
				loadSpecies(read);
			}
			if(str.compare("ELEMENTS")==0)
			{
				cout<<"ick"<<endl;
				loadElements(read);
			}
			if(str.compare("REACTIONS")==0)
                        {
                                cout<<"ugh"<<endl;
                                loadReactions(read);
                        }
		}
	}
	void loadElements(ifstream& fin)
	{
	}
	void loadReactions(ifstream& fin)
        {
		fin>>mReactions;
		cout<<"Number of Reactions: "<<mReactions<<endl;
		a=new double[mReactions];
		b=new double[mReactions];
		eA=new double[mReactions];

		string reaction;
		size_t loc,*plusLoc;
		string plus;
		string equals;
		size_t equalsPos;
		size_t plusPos;
		int numPlus=0,equalLoc;

		for(int i=0;i<mReactions;i++)
		{
			fin>>reaction>>a[i]>>b[i]>>eA[i];
			cout<<reaction<<endl<<a[i]<<endl<<b[i]<<endl<<eA[i]<<endl;
			
			equalsPos=reaction.find("=");
			cout<<"equals found at: "<<equalsPos<<endl;
			plusPos=reaction.find("+");
			cout<<"plus found at: "<<plusPos<<endl;
			while(plusPos!= string::npos)
			{
				numPlus++;
        	                plusPos=reaction.find("+",plusPos+1);
	                        cout<<"plus found at: "<<plusPos<<endl;
			}
			cout<<numPlus<<" pluses found"<<endl;
			size_t *plusLoc=new size_t[numPlus+3];
			cout<<"size of plusLoc should be "<<(numPlus+3)<<endl;
			cout<<"size of plusLoc is "<<sizeof(plusLoc)<<endl;
			plusLoc[0]=0;
			for(int j=1;j<(numPlus+3);j++)
			{	int ae=0;
				plusLoc[j+ae]=reaction.find("+",plusLoc[j-1]+1);
				if((plusLoc[j]>equalsPos)&&(ae==0))
				{
					plusLoc[j+1]=plusLoc[j];
					plusLoc[j]=equalsPos;
					cout<<plusLoc[j]<<endl;
					ae=1;
				}
				cout<<plusLoc[j]<<endl;
			}
			cout<<reaction.size()<<endl;
			plusLoc[numPlus+2]=reaction.size();
			for(int j=0;j<(numPlus+3);j++)
			{
				cout<<j<<" "<<plusLoc[j]<<endl;
			}
			//remove coefs
			cout<<"test: "<<species[1].at(0)<<endl;
			cout<<"char 1 cast to int "<<(int)('9')<<endl;


			for(int j=0;j<numPlus+2;j++)
			{	
				int ae=0;
				cout<<plusLoc[j]<<endl;
				if(j>0)
					ae=1;
				cout<<ae<<endl;



				for(int n=0;n<nSpecies;n++)
				{
					cout<<"comparing "<<species[n]<<" with "<<reaction.substr(plusLoc[j]+ae,plusLoc[j+1]-plusLoc[j]-ae)<<endl;
					
					for(int m=(plusLoc[j]+ae);m<(plusLoc[j+1]-plusLoc[j]-ae);m++)
					{	cout<<reaction.at(m)<<endl;
						if(((int)(reaction.at(m))>=(int)('0'))&&((int)(reaction.at(m))<=(int)('9')))
							cout<<"YO"<<endl;
					}

					cout<<species[n].compare(reaction.substr(plusLoc[j]+ae,plusLoc[j+1]-plusLoc[j]-ae))<<endl;
				}
			}

			for(int j=0;j<nSpecies;j++)
			{
				loc=reaction.find(species[j]);
				cout<<"Species: "<<species[j]<<" found at ps"<<loc<<endl;
			}
		}
        }

	void loadSpecies(ifstream& fin)
	{
		//getline(fin,sp,'\n');
		fin >> nSpecies;
		cout<<"Number of species: "<<nSpecies<<endl;
		species=new string[nSpecies];

		for(int i=0;i<nSpecies;i++)
		{
			fin>>species[i];
			cout<<"Species: "<<species[i] <<" Index: "<<i<<endl;
		}
		/*while(sp.compare("END")!=0)
		{
			cout<<sp<<endl;
			getline(fin,sp,' ');
			
		}*/
	}
	
	string getSpecies(int index)
	{
		return(species[index]);
	}
	void getReactionConst(int index,double (&rec)[3])
	{
		rec[0]=a[index];
		rec[1]=b[index];
		rec[2]=eA[index];
	}


};

class reaction
{
	public:
	


};



void readChem(string filename)
{

}



