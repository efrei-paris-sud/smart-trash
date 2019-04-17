#include "graphe.h"
#include <vector>
#include <stack>

using namespace std;

vector<int> Pprofondeur(Graphe* g, int v, bool visited[])
{
	vector<int> vect;
    // Marquer le sommet actuel comme visité et l'affiher
    visited[v] = true;
    cout << v << " ";
    vect.push_back(v);
 
    //  récupère les sommets successeurs de v
    vector<Arc*> i = g->getSuccesseursArcs(v);
    i= g->getSuccesseursArcs(v);
    for (vector<Arc*>::iterator it=i.begin(); it!=i.end(); ++it)
        if (!visited[(*it)->getDestination()->getIds()])
            Pprofondeur(g, (*it)->getDestination()->getIds(), visited);
            
    return vect;	
}

Graphe& echange(Graphe* G) //get inverse des arcs
{
    Graphe* g = new Graphe(*G);	//on déclare un nouveau graphe
    
    for(int t=0; t<g->getTaille(); t++) //on parcours la taille du graphe
    {
		for(int m=0; m<g->getTaille(); m++)
		{
			if(g->existeArc(t,m)) //si il existe un arc entre t et m
			{
				g->suppArc(t,m);	//supprimer cet arc
			}
		}
	}
    
    for (int v = 0; v < G->getTaille(); v++)//on parcours la taille du graphe
    {
        
        for(int r=0; r<G->getTaille(); r++)
        {
			if(G->existeArc(v,r))	//si il existe un arc entre v et r
			{
				g->ajouterArc(r,v);	//ajouter un arc entre t et m 
			}
		}
    }
    return *g;
}

void executer(Graphe g, int v, bool visited[], stack<int> &Stack)
{
    // Marquer le sommet actuel comme visité et l'affiher
    visited[v] = true;
 
    // récupère les sommets successeurs de v
    vector<Arc*> i = g.getSuccesseursArcs(v);
	i= g.getSuccesseursArcs(v);
    for(vector<Arc*>::iterator it=i.begin(); it!=i.end(); ++it)
        if(!visited[(*it)->getDestination()->getIds()])
            executer(g, (*it)->getDestination()->getIds(), visited, Stack);
 
    // Tous les sommets accessibles à partir de v sont ajoutés à la pile 
    Stack.push(v);
}

void afficherCFCs(Graphe* g)
{
    stack<int> Stack;	//pile
    int coul=1;			//couleur
    vector<int> vect;
 
    // Marquer tous les sommets comme non visités (Premier parcours en profondeur)
    bool *visited = new bool[g->getTaille()];
    for(int i = 0; i < g->getTaille(); i++)
        visited[i] = false;
 
    //On remplit la pile de sommets dans l'ordre avec lequel on les visite
    for(int i = 0; i < g->getTaille(); i++)
        if(visited[i] == false)
            executer(*g, i, visited, Stack);
 
    // On crée un graphe réservé
    Graphe gr = echange(g);
 
    // Marquer tous les sommets comme étants non visités (For second DFS)
    for(int i = 0; i < g->getTaille(); i++)
        visited[i] = false;
 
    // On traîte les sommets définis dans l'ordre dans la pile
    while (Stack.empty() == false)
    {
        // retirer sommet de la pile
        int v = Stack.top();
        Stack.pop();
 
        // afficher Composante Fortement Connexe du sommet retiré
        if (visited[v] == false)
        {
           vect =  Pprofondeur(&gr, v, visited);
           cout << endl;
           for(int m=0;(unsigned int)m<vect.size(); m++)
           {
			   g->getSommet(vect[m])->setColorR((coul*180+200)%255);
			   g->getSommet(vect[m])->setColorG((coul*200+100)%255);
			   g->getSommet(vect[m])->setColorB((coul*52+50)%255);
		   }
		   coul++; //incrémente couleur
        }
    }
}

int main()
{
	Graphe* g = new Graphe();
	Point p;
	p._abs=25;
	p._ord=54;
	g->ajouterSommet(p);
	g->ajouterSommet(p);
	g->ajouterSommet(p);
	g->ajouterSommet(p);
	g->ajouterSommet(p);
	g->ajouterSommet(p);
	g->ajouterSommet(p);
	g->ajouterSommet(p);
	g->ajouterArc(0,1);
	g->ajouterArc(1,2);
	g->ajouterArc(1,5);
	g->ajouterArc(1,3);
	g->ajouterArc(2,3);
	g->ajouterArc(2,0);
	g->ajouterArc(3,4);
	g->ajouterArc(4,3);
	g->ajouterArc(5,4);
	g->ajouterArc(5,6);
	g->ajouterArc(6,5);
	g->ajouterArc(6,7);
	g->ajouterArc(7,6);
	g->ajouterArc(7,4);

	afficherCFC(g);	
	
	return 0;
}


