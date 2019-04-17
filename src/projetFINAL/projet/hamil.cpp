#include "graphe.h"
 #include <math.h>








vector<int> VecFeynman  (int j, vector<int>& LSommet)         //ok
{
	//vector<int> tmp(LSommet.size()+1,0); // creer un vector initialisé 0
	//tmp[0]=LSommet[0]-1;
	//for(int i=1; (unsigned int)i<=LSommet.size(); i++)
	//{
		//tmp[i+1]=LSommet[i];
	//}
	//tmp[1]=j;

	vector<int> tmp;
	tmp=LSommet;
	vector<int>::iterator it1;        // un itérateur
    it1 = tmp.begin();
    tmp.insert(it1,j);
    //return tmp;
 return tmp;
}
// On construit le Grpahe G de particules :

// On construit la matrice de Feynman au point 0...

void Feynmann(Graphe* G)
{
vector< vector< vector<int> > > feynman;
feynman.push_back(vector< vector<int> >());
feynman[0].push_back(vector<int>());
feynman[0][0].push_back(G->getTaille());
feynman[0][0].push_back(0);


for(int j=0; j<G->getTaille(); j++)
{
	cout<<" 1er for et j "<<j<<endl;
	if(G->existeArc(0,j) && j != 0)
	{
		cout<<" dans if j= "<<j<<endl; 
		feynman.push_back(vector< vector<int> >());
		feynman[j].push_back(vector<int>());
		cout<<" fin if1"<<endl;
		feynman[j][0].push_back(G->getTaille()-1);
		cout<<" fin if2"<<endl;
		feynman[j][0].push_back(j);
		cout<<" fin if3"<<endl;
		feynman[j][0].push_back(0);
		cout<<" fin if4"<<endl;
	}
	else
	{
		cout<<" dans else j= "<<j<<endl; 
		feynman.push_back(vector< vector<int> >());
		feynman[j].push_back(vector<int>());
		feynman[j][0].push_back(0);
		feynman[j][0].push_back(j);
	}
}
cout<<"fin for"<<endl;  // ok


for(int k=0; k<pow(G->getTaille(),2); k++)
{
	cout<<" 2em for"<<endl;
	for(int t=0; t<G->getTaille(); t++)
	{
		cout<<" 3em for"<<endl;
		if(G->existeArc(k%G->getTaille(), t) && (k%G->getTaille()) != t)
		{
			for(int v=0; (unsigned int)v<feynman[k%G->getTaille()].size() && feynman[k%G->getTaille()][v].size() > 0; v++)
			{
				cout<<" taille "<<feynman[k%G->getTaille()].size();
				cout<<" 4em for et k "<<k<<" v "<<v<<" "<< feynman[k%G->getTaille()][v][0]<<endl;
				if(feynman[k%G->getTaille()][v][0] > 0)
				{
					cout<<" dans if"<<endl;
					feynman[t].push_back(VecFeynman(t,feynman[k%G->getTaille()][v]));
					cout<<" fin if"<<endl;
				}
			}cout<<" fin for4"<<endl;
		}
		if(!G->existeArc(k%G->getTaille(), t))
		{
			feynman[t]=feynman[t];
		}
	}cout<<" fin for3"<<endl;
	
}cout<<" fin for2"<<endl;  //ok

//print ( " Matrice de Feynman au point 0 : " )

for(int a=0; (unsigned int)a<feynman[0].size(); a++)
{
	//cout<<" matrice au point 0"<<endl;
	if(feynman[0][a].size() == (unsigned int) G->getTaille()+2 && feynman[0][a][0] == 0 && feynman[0][a][1] == 0 && feynman[0][a][G->getTaille()+1] == 0)
	{
		//cout<< feynman[0][a];
		//cout<<" print feynman[0][a]";
	}
}

// Cycles Hamiltoniens :

//print ( " Cycles Hamiltoniens : " )

vector<int> l;

for(int i=0; (unsigned int)i<feynman[0].size(); i++)
{
	cout<<"Cycles Hamiltoniens "<<feynman[0][i].size()<<endl;
	//if(feynman[0][i].size() == (unsigned int)G->getTaille()+3 && feynman[0][i][0] == 0 && feynman[0][i][1] == 0 && feynman[0][i][G->getTaille()+1] == 0)
	//{
		//cout<<" if1"<<endl;
		if(feynman[0][i].size() == (unsigned int)G->getTaille()+2)
		{
			cout<<" if2 cycle 1"<<endl;
			feynman[0][i].erase(feynman[0][i].begin());
			vector<int>::iterator it;
			it = l.end();
  			l.insert (it,feynman[0][i].begin(),feynman[0][i].end());
		}
	//}
}
cout<<" taille de l = "<<l.size();
//for(int m=0; m<l.size(); m++)
//{
	//cout<<" "<<l[m];
//}cout<<endl;

vector<int> h;

for(int j=0; (unsigned int)j<l.size(); j++)
{
	int k;
	bool existe=false;
	for(k=0;(unsigned int)k<h.size(); k++)
	{
		//cout<<" l[j] "<<l[j]<<endl;;
		if(l[j] == h[k])
		{
			//cout<<" dans if"<<endl;
			existe=true;
			break;
		}
	}
	if(!existe)
	{
		cout<<" ok l[j] "<<l[j]<<endl;
		h.push_back(l[j]);
	}
	//if((unsigned int)l[j]<h.size())
	//{
		//h.push_back(j);
	//}
}

if(h.size() != 0)
{
	//print h;
	cout<<" on a un circuit"<<endl;
	int tmp=-1;
	for(int r=h.size()-1;r>=0; r--)
	{
		cout<<" "<<h[r];
		G->getSommet(h[r])->setColorR(255);
		G->getSommet(h[r])->setColorG(0);
		G->getSommet(h[r])->setColorB(0);
		if(tmp > -1)
		{
			G->getArc(tmp,h[r])->setColorR(255);
			G->getArc(tmp,h[r])->setColorG(0);
			G->getArc(tmp,h[r])->setColorB(0);
		}
		tmp=h[r];
		
	}cout<<endl;
}
else
{
	cout<<" on a pas de circuit"<<endl;
}

}



int main()
{
	Point p;
	p._abs=25;
	p._ord=54;
	
	Graphe ggg;
    //ggg.ajouterSommet(p);
    //ggg.ajouterSommet(p);
    //ggg.ajouterSommet(p);
    //ggg.ajouterSommet(p);
    //ggg.ajouterSommet(p);
    //ggg.ajouterSommet(p);
    //ggg.ajouterSommet(p);
    //ggg.ajouterSommet(p);
    //ggg.ajouterSommet(p); // 9
    //ggg.ajouterArc(0,1);
    //ggg.ajouterArc(1,2);
    //ggg.ajouterArc(2,0);
    //ggg.ajouterArc(1,3);
    //ggg.ajouterArc(3,4);
    //ggg.ajouterArc(4,1);
    //ggg.ajouterArc(1,5);
    //ggg.ajouterArc(5,6);
    //ggg.ajouterArc(6,1);
    //ggg.ajouterArc(1,7);
    //ggg.ajouterArc(7,8);
    //ggg.ajouterArc(8,1);
    
    ggg.ajouterSommet(p);
    ggg.ajouterSommet(p);
    ggg.ajouterSommet(p);
    ggg.ajouterSommet(p);
    ggg.ajouterSommet(p);
    //ggg.ajouterSommet(p);
    //ggg.ajouterSommet(p);
    //ggg.ajouterSommet(p);//7
    ggg.ajouterArc(0,1);
    ggg.ajouterArc(1,2);
    ggg.ajouterArc(2,3);
    ggg.ajouterArc(3,4);
    ggg.ajouterArc(4,0);
    //ggg.ajouterArc(1,3);
    //ggg.ajouterArc(4,2);
    //ggg.ajouterArc(2,0);
    //ggg.ajouterArc(7,2);
	
	Feynmann(&ggg);
	
	//vector<int> vect(5,2);
	//vector<int> vect1;
	//vect1 = VecFeynman(3, vect);
	//for(int i=0; (unsigned int)i<vect1.size(); i++)
	//{
		//cout<<" "<<vect1[i];
	//}cout<<endl;
	
	//vector< vector< vector<int> > > vect;
	//vect.push_back(vector< vector<int> >());
	//vect[0].push_back(vector<int>());
	//vect[0][0].push_back(25);
	
	
	return 0;
}








