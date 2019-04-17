#ifndef ARC_H
#define ARC_H

#include <iostream>
#include <string>
#include <vector>
#include "sommet.h"

using namespace std;

class Arc
{

private:
    string _nom;        // nom du sommet
    int _ida;
    bool _typeReel ;		// vrai ou faut
    double _val[2]; // valeur stocké
    bool _etat;         // etat
    int _color[3];		// couleur
    Sommet *_origine;	// origine de l'arc
    Sommet *_destination; // destination de l'arc
    static int _nbArc; // nombre total de d'arc

public:
    Arc();//Constructeur par defaut
    Arc(Sommet *orig, Sommet *dest, int compteurA);//Constructeur Dessin
    Arc(string nom, int ida, bool typeReel, double val[2], Sommet *orig, Sommet *dest);//Constructeur Chargement
    Arc(const Arc &a);//Constructeur copie

    // getter
    string getNom();
    int getIda();
    bool getTypeReel();
    double getVal1();
    double getVal2();
    bool getEtat();
    int getColorR();
    int getColorG();
    int getColorB();
    Sommet* getOrigine();
    Sommet* getDestination();
    static int nbArc();

    //setter
    void setNom(string nom);
    void setIda(int ida);
    void setTypeReel(bool typeEntier);
    void setVal1(double val);
    void setVal2(double val);
    void setEtat(bool etat);
    void setColorR(int colorR);
    void setColorG(int colorG);
    void setColorB(int colorB);
    void setOrigine(const Sommet& orig);
    void setDestination(const Sommet& dest);
    void decrisToi();
    friend ostream& operator<<(ostream& flux, Arc& a);
    Arc& operator=(Arc& a);

    ~Arc();//Destructeur
};

#endif // ARC_H
