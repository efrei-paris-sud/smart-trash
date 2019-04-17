#ifndef ALGORITHME_H
#define ALGORITHME_H

#include <stdlib.h>
#include <string>
#include "arc.h"
#include "graphe.h"
#include "sommet.h"
#include <iostream>
#include <stack>
#include <queue>
#include  <math.h>
using namespace std;

double dijkstra(Sommet &depart, Sommet &arrivee, Graphe *graphe);
vector< vector<int> > getProduitMatriciel( vector< vector<int> > matrice, vector< vector<int> > matrice2 );
bool cycle(Graphe *g);
bool existeChemin(Sommet *depart, Sommet *arrivee, Graphe *graphe);
bool conditionPertFlot(Sommet *source, Sommet *puits, Graphe *g);
bool Existe_chaine_ame(Graphe *g,Sommet &s,int Ts[][2],int Ta[][4]);
void init1(int Ta[][4],int Ts[0][2],Graphe *g,Sommet &s);
void init(int Ta[][4],int Ts[0][2],Graphe* g,Sommet &s);
vector<int> getchaineameliorante(int Ts[][2],Graphe *g, Sommet &s, Sommet &p);
int augmenterflux(int Ta[][4],vector<int> vida,int size_Ta);
void Actualiser_graphe(Graphe *g,int Ta[][4]);
double fordBellman(Sommet &depart, Sommet &arrivee, Graphe *graphe);
int Flot_Max(Graphe *g,Sommet &s ,Sommet &p);
void Profondeur (Graphe *g, stack<int>& pile, int Etat[], int Pred[]);
void Pprofondeur(Graphe* g);
void Largeur (Graphe* g, queue<int>& file, int Etat[], int Pred[]);
void Plargeur(Graphe* G);
bool GrapheConnexe(Graphe *G);
bool DegImpair (Graphe& g);
bool euler(Graphe* G, Sommet& s);
double Max(double a, double b);
double Min(double a, double b);
void Pert(Graphe *g, Sommet &s1, Sommet &s2);
void Date_plus_tot(Graphe *g, Sommet &s1,Sommet &s2);
void Date_plus_tard(Graphe *g, Sommet &s1,Sommet &s2);
void Marge_critique(Graphe *g,Sommet &s1,Sommet &s2);
bool estSource(Sommet *s, Graphe *g);
bool estPuits(Sommet *s, Graphe *g);
void Tarjan(Graphe* g);
void executer(Graphe g, int v, bool visited[], stack<int> &Stack);
Graphe& ComposanteFortementConnexe(Graphe* G);
vector<int> parcours(Graphe* g, int v, bool visited[]);
vector<int> VecFeynman  (int j, vector<int>& LSommet);
void Feynmann(Graphe* G);

#endif // ALGORITHME_H
