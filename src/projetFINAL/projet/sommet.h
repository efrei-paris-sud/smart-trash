#ifndef SOMMET_H
#define SOMMET_H

#include <iostream>
#include <string>
#include <vector>
#include "point.h"

using namespace std;

// Classe Sommet
class Sommet
{

private:
    string _nom;        // nom du sommet
    int _ids;		// identifiant source propre a un graphe (qui sera modiffier par compteur dans le graphe)
    int _degrPlus;	// degré sortant
    int _degrMoins;		// degré entrant
    int _degrTotal; //degré total
    bool _typeReel ;		// vrai ou faux
    double _val[3]; // valeur stocké
    bool _etat;         // etat
    int _color[3];		// couleur
    Point _p;			// point
    static int _nbSommet; // nombre total de sommet

public:
    Sommet();//Constructeur par defaut
    Sommet(Point &p, int ids);//Constructeur Dessin
    Sommet(string nom, int ids, bool typeReel, double val[3], Point p);//Constructeur Chargement
    Sommet(const Sommet &s);//Constructeur Copie


    string getNom();
    double getAbscisse();
    double getOrdonnee();
    bool getEtat();
    bool getTypeReel();
    int getIds();
    int getDegrPlus();
    int getDegrMoins();
    int getDegrTotal();
    double getVal1();
    double getVal2();
    double getVal3();
    int getColorR();
    int getColorG();
    int getColorB();
    static int nbSommet();
    Point getPoint();

    void setNom(string nom);
    void setIds(int ids);
    void setAbscisse(double abs);
    void setOrdonnee(double ord);
    void setEtat(bool etat);
    void setTypeReel(bool typeReel);
    void setPoint(Point& p);
    void setColorR(int colorR);
    void setColorG(int colorG);
    void setColorB(int colorB);
    void setVal1(double val1);
    void setVal2(double val2);
    void setVal3(double val3);

    //incremmentation
    void DegrPlusPlus();
    void DegrMoinsPlus();
    void DegrPlusMoins();
    void DegrMoinsMoins();


    // calule le degré du sonnet
    void DegrTotal();
    //description
    void decrisToi();
     friend ostream& operator<<(ostream& flux, Sommet& s);
     Sommet& operator=(Sommet& s);

    ~Sommet();//Destructeur
};

#endif // SOMMET_H
