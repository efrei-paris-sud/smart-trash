#ifndef GRAPHE_H
#define GRAPHE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "arc.h"

using namespace std;

class Graphe
{

private:
        int _idg;                       	// identifiant
        int _taille;				// taille du graphe
        int _compteurS;
        int _compteurA;
        int _tailleArc;
        static int _nbGraphes;			// le nombre total de graphe (vu comme un compteur de _id)
        string _nom;				// nom du graphe
        vector< vector<Arc*> > _Mgraphe;		// le graphe
        vector<Sommet*> _LSommets;		// la liste des sommets avec clé int et objet sommet
        bool _typeReel ;		// vrai ou faux

public:
        Graphe();//Constructeur par defaut
        Graphe(int idg ,string nom); // Constructeur chargement
        Graphe(const Graphe &g); // Constructeur par copie
        Graphe(vector<Sommet>& vs,vector<Arc>& va);  //Construit un graphe à partir d’un graphe partiel (extraire un sous graphe partiel)
        Graphe(Graphe& g,vector<Sommet>& vs);



    // Ajouter
        void ajouterSommet(Point& p);
        void ajouterSommet(string nom, int ids, bool typeReel, double val[3], Point p);
        void ajouterSommet(Sommet& s);
        void ajouterArc(int ido, int idd);
        void ajouterArc(string nom, int ida, bool typeReel, double val[2], int ido, int idd);

    // Supprimer
        void suppSommet(int id);	// un seul
        void suppSommet(Sommet& sommet);
        void suppArc(Sommet& orig, Sommet& dest);// un seul
        void suppArc(int ido, int idd);

    // Existance



    bool existeArc(Sommet &s1, Sommet &s2);
    bool existeArc(int ids1, int ids2);
    vector<Arc*> getSuccesseursArcs(int id);// Successeurs d'un sommet
    vector<Arc*> getSuccesseursArcs(Sommet &s);// Successeurs d'un sommet
    vector<Arc*> getPredecesseurArcs(int id);// Successeurs d'un sommet
    vector<Arc*> getPredecesseurArcs(Sommet &s);// Successeurs d'un sommet


    // Getter
    vector< vector<int> > getMatrice();
    string getNom();
    int getCompteurS()const;
    int getCompteurA()const;
    int getTaille();
    int getIdg();
    Sommet* getSommet(int id);
    Arc* getArc(int ido, int idd);
    Arc* getArc(int ida);
    static int nbGraphes();
    vector<Sommet *> getLSommets() const;

    //Setter
    void setNom(string nom);
    void setIdg(int idg);
    void setTaille(int taille);

    // Marquage
    void marquerSommet(int id);
    void demarquerSommet(int id);

    // visiter ?
    bool visiter(int id);

    // initialiser les valeurs
    void initialiserVal2Arc();
    void initialiserVal2Sommet();
    void initialiserVal3Sommet();
    void initialiserEtatArc();
    void initialiserEtatSommet();
    void initialiserCouleurArc();
    void initialiserCouleurSommet();
    void changeType(bool type);

    void decrisToi();
    friend ostream& operator<<(ostream& flux, Graphe& g);
    Graphe& operator=(Graphe& g);

    ~Graphe();//Destructeur

    bool getTypeReel() const;
    void setTypeReel(bool typeReel);
    int getTailleArc() const;
};

#endif // GRAPHE_H
