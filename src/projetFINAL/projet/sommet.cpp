#include "sommet.h"
#include <iostream>

Sommet::Sommet()
{
     _nom="NULL";        // nom du sommet
     _ids=nbSommet();    // identiiant general pour tous les graphes (qui sera modiffier par la variable static nbSommets)
     _degrPlus=0;	// degré sortant
     _degrMoins=0;		// degré entrant
     _degrTotal=0;
     _typeReel = true ;		// vrai ou faux
     _val[0]=0.0;
     _val[1]=0.0;
     _val[2]=0.0;
     _etat=false;         // etat
     _color[0]=240;		// couleur
     _color[1]=240;		// couleur
     _color[2]=0;		// couleur
     _p._abs=0.0;    //point x
     _p._ord=0.0;        // point y

     _nbSommet++; // nombre total de sommet
}

Sommet::Sommet(Point &p, int ids)
{
     _nom="NULL";        // nom du sommet
     _ids=ids;     // identiiant general pour tous les graphes (qui sera modiffier par la variable static nbSommets)
     _degrPlus=0;	// degré sortant
     _degrMoins=0;		// degré entrant
     _degrTotal=0;
     _typeReel = true ;		// vrai ou faux
     _val[0]=0.0;
     _val[1]=0.0;
     _val[2]=0.0;
     _etat=false;         // etat
     _color[0]=240;		// couleur
     _color[1]=240;		// couleur
     _color[2]=0;		// couleur
     _p._abs=p._abs;    //point x
     _p._ord=p._ord;        // point y

     _nbSommet++; // nombre total de sommet
}

Sommet::Sommet(string nom, int ids, bool typeReel, double val[3], Point p)
{
    _nom=nom;        // nom du sommet
    _ids=ids;    // identiiant general pour tous les graphes (qui sera modiffier par la variable static nbSommets)
    _degrPlus=0;	// degré sortant
    _degrMoins=0;		// degré entrant
    _degrTotal=0;
    _typeReel=typeReel;		// vrai ou faux
    if(_typeReel == false){
        _val[0]=static_cast<int>(val[0]);
        _val[1]=static_cast<int>(val[1]);
        _val[2]=static_cast<int>(val[2]);
    }
    else{
        _val[0]=val[0];
        _val[1]=val[1];
        _val[2]=val[2];
    }
    _etat=false;         // etat
    _color[0]=240;		// couleur
    _color[1]=240;		// couleur
    _color[2]=0;		// couleur
    _p._abs=p._abs;    //point x
    _p._ord=p._ord;        // point y

    _nbSommet++; // nombre total de sommet
}

Sommet::Sommet(const Sommet &s)
{
     _nom=s._nom;        // nom du sommet
     _ids=s._ids;		// identifiant source propre a un graphe (qui sera modiffier par compteur dans le graphe)
     _degrPlus=s._degrPlus;	// degré sortant
     _degrMoins=s._degrMoins;		// degré entrant
     _degrTotal=s._degrTotal;
     _typeReel=s._typeReel;		// vrai ou faux
     if(_typeReel == false){
        _val[0]=static_cast<int>(s._val[0]);
        _val[1]=static_cast<int>(s._val[1]);
        _val[2]=static_cast<int>(s._val[2]);
    }
    else{
        _val[0]=s._val[0];
        _val[1]=s._val[1];
        _val[2]=s._val[2];
    }
     _etat=s._etat;         // etat
     _color[0]=s._color[0];		// couleur
     _color[1]=s._color[1];		// couleur
     _color[2]=s._color[2];		// couleur
     _p=s._p;    //point

     _nbSommet++; // nombre total de sommet
}

double Sommet::getAbscisse()
{
    return _p._abs;
}

string Sommet::getNom()
{
    return _nom;
}

double Sommet::getOrdonnee()
{
    return _p._ord;
}
Point Sommet::getPoint(){
    return _p;
}

bool Sommet::getEtat()
{
    return _etat;
}

bool Sommet::getTypeReel()
{
    return _typeReel;
}

int Sommet::getIds()
{
    return _ids;
}

int Sommet:: getDegrPlus()
{
    return _degrPlus;
}
int Sommet::getDegrMoins()
{
    return _degrMoins;
}
int Sommet::getDegrTotal()
{
   return _degrTotal;
}

double Sommet::getVal1()
{
    return _val[0];
}

double Sommet::getVal2()
{
    return _val[1];
}

double Sommet::getVal3()
{
    return _val[2];
}

int Sommet::getColorR()
{
    return _color[0];
}

int Sommet::getColorG()
{
    return _color[1];
}

int Sommet::getColorB()
{
    return _color[2];
}

void Sommet::setAbscisse(double abs)
{
    _p._abs=abs;
}

void Sommet::setNom(string nom)
{
    _nom=nom;
}

void Sommet::setIds(int id)
{
    _ids=id;
}

void Sommet::DegrPlusPlus()
{
    _degrPlus++;
}

void Sommet::DegrMoinsPlus()
{
    _degrMoins++;
}

void Sommet::DegrPlusMoins()
{
    _degrPlus--;
}

void Sommet::DegrMoinsMoins()
{
    _degrMoins--;
}

void Sommet::DegrTotal()
{
    _degrTotal=_degrMoins+_degrPlus;
}

void Sommet::setOrdonnee(double ord)
{
    _p._ord=ord;
}

void Sommet::setEtat(bool etat)
{
    _etat=etat;
}

void Sommet::setTypeReel(bool typeReel)
{
     _typeReel=typeReel;
}

void Sommet::setPoint(Point& p)
{
    _p=p;
}

void Sommet::setColorR(int colorR)
{
    _color[0]=colorR;
}
void Sommet::setColorG(int colorG)
{
    _color[1]=colorG;
}
void Sommet::setColorB(int colorB)
{
    _color[2]=colorB;
}

void Sommet::setVal1(double val1)
{
    if(_typeReel ==false)
        _val[0]=static_cast<int>(val1);
    else
        _val[0]=val1;
}
void Sommet::setVal2(double val2)
{
    if(_typeReel == false)
        _val[1]=static_cast<int>(val2);
    else
        _val[1]=val2;
}
void Sommet::setVal3(double val3)
{
    if(_typeReel == false)
        _val[2]=static_cast<int>(val3);
    else
        _val[2]=val3;
}

void Sommet::decrisToi(){
    cout<<" SOMMET\nNom : "<<_nom<<
    "\nIds : "<<_ids<<
    "\nVals : { "<<_val[0]<<", "<<_val[1]<<", "<<_val[2]<<
    " }\nP.x : "<<_p._abs<<", P.y : "<<_p._ord<<endl;
}

ostream& operator<<(ostream& flux, Sommet&s)
{
    flux << " SOMMET\nNom : "<<s._nom<<
            "\nIds : "<<s._ids<<
            "\nVals : { "<<s._val[0]<<", "<<s._val[1]<<", "<<s._val[2]<<
            " }\nP.x : "<<s._p._abs<<", P.y : "<<s._p._ord<<endl;
    return flux;
}

Sommet& Sommet::operator=(Sommet& s)
{
    _nom=s._nom;        // nom du sommet
    _ids=s._ids;		// identifiant source propre a un graphe (qui sera modiffier par compteur dans le graphe)
    _degrPlus=s._degrPlus;	// degré sortant
    _degrMoins=s._degrMoins;		// degré entrant
    _degrTotal=s._degrTotal;
    _typeReel=s._typeReel;		// vrai ou faut
    if(_typeReel == false){
        _val[0]=static_cast<int>(s._val[0]);
        _val[1]=static_cast<int>(s._val[1]);
        _val[2]=static_cast<int>(s._val[2]);
    }
    else{
        _val[0]=s._val[0];
        _val[1]=s._val[1];
        _val[2]=s._val[2];
    }
    _etat=s._etat;         // etat
    _color[0]=s._color[0];		// couleur
    _color[1]=s._color[1];		// couleur
    _color[2]=s._color[2];		// couleur
    _p=s._p;    //point

    return *this;
}

int Sommet::nbSommet()
{
    return _nbSommet;
}

Sommet::~Sommet()
{
    cout <<"Destructeur Sommet"<<endl;
    _nbSommet--;
}

int Sommet::_nbSommet=0;//Variable statique

