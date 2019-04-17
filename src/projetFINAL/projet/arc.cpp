#include "arc.h"
#include <iostream>

Arc::Arc()
{
    _nom="NULL";
    _ida=nbArc();
    _typeReel = true;
    _val[0]=0.0;
    _val[1]=0.0;
    _etat=false;
    _color[0]=255;
    _color[1]=255;
    _color[2]=255;
    _origine=NULL;
    _destination=NULL;

    _nbArc++;
}

Arc::Arc(Sommet *orig, Sommet *dest, int compteurA)
{
     _nom="NULL";
     _ida=compteurA;
     _typeReel = true;
     _val[0]=0.0;
     _val[1]=0.0;
     _etat=false;
     _color[0]=255;
     _color[1]=255;
     _color[2]=255;
     _origine=orig;
     _destination=dest;

     _nbArc++;
}

Arc::Arc(string nom, int ida, bool typeReel, double val[2], Sommet *orig, Sommet *dest)
{
    _nom=nom;
    _ida=ida;
    _typeReel=typeReel;
    if(typeReel == false){
        _val[0]=static_cast<int>(val[0]);
        _val[1]=static_cast<int>(val[1]);
    }
    else{
        _val[0]=val[0];
        _val[1]=val[1];
    }
    _etat=false;
    _color[0]=255;
    _color[1]=255;
    _color[2]=255;
    _origine=orig;
    _destination=dest;

    _nbArc++;
}

Arc::Arc(const Arc &a)
{
    _nom=a._nom;
    _ida=a._ida;
    _typeReel=a._typeReel;
    if(_typeReel == false){
        _val[0]=static_cast<int>(a._val[0]);
        _val[1]=static_cast<int>(a._val[1]);
    }
    else{
        _val[0]=a._val[0];
        _val[1]=a._val[1];
    }
    _etat=a._etat;
    _color[0]=a._color[0];
    _color[1]=a._color[1];
    _color[2]=a._color[2];
    _origine=a._origine;
    _destination=a._destination;

    _nbArc++;
}

string Arc::getNom()
{
    return _nom;
}

int Arc::getIda()
{
    return _ida;
}

bool Arc::getTypeReel()
{
    return _typeReel;
}

double Arc::getVal1()
{
    return _val[0];
}

double Arc::getVal2()
{
    return _val[1];
}

bool Arc::getEtat()
{
    return _etat;
}

int Arc::getColorR()
{
    return _color[0];
}

int Arc::getColorG()
{
    return _color[1];
}

int Arc::getColorB()
{
    return _color[2];
}

Sommet* Arc::getOrigine()
{
    return _origine;
}
Sommet* Arc::getDestination()
{
    return _destination;
}

void Arc::setNom(string nom)
{
    _nom=nom;
}

void Arc::setIda(int ida)
{
    _ida = ida;
}

void Arc::setTypeReel(bool typeReel)
{
    _typeReel=typeReel;
}

void Arc::setVal1(double val)
{
    if(_typeReel == false)
        _val[0]=static_cast<int>(val);
    else _val[0]=val;
}

void Arc::setVal2(double val)
{
    if(_typeReel == false)
        _val[1]=static_cast<int>(val);
    else _val[1]=val;
}

void Arc::setEtat(bool etat)
{
    _etat=etat;
}

void Arc::setColorR(int colorR)
{
    _color[0]=colorR;
}

void Arc::setColorG(int colorG)
{
    _color[1]=colorG;
}

void Arc::setColorB(int colorB)
{
    _color[2]=colorB;
}

void Arc::setOrigine(const Sommet &orig)
{
    _origine=new Sommet(orig);
}
void Arc::setDestination(const Sommet &dest)
{
    _destination=new Sommet(dest);
}

void Arc::decrisToi(){
    cout<<" ARC\nNom : "<<_nom<<
    "\nIda : "<<_ida<<
    "\nVals : { "<<_val[0]<<
    " "<<_val[1]<<" }"<<
       "\nId source "<<_origine->getIds()<<
       "\nId dest "<<_destination->getIds()<<endl;
}

ostream& operator<<(ostream& flux, Arc& a)
{
    flux << " ARC\nNom : "<<a._nom<<
            "\nIda : "<<a._ida<<
            "\nVals : { "<<a._val[0]<<
            ", "<<a._val[1]<<" }"<<endl;
    return flux;
}

Arc& Arc::operator=(Arc& a)
{
    _nom=a._nom;
    _ida=a._ida;
    _typeReel=a._typeReel;
    if(_typeReel == false){
        _val[0]=static_cast<int>(a._val[0]);
        _val[1]=static_cast<int>(a._val[1]);
    }
    else{
        _val[0]=a._val[0];
        _val[1]=a._val[1];
    }
    _etat=a._etat;
    _color[0]=a._color[0];
    _color[1]=a._color[1];
    _color[2]=a._color[2];
    _origine=a._origine;
    _destination=a._destination;

    return *this;
}

int Arc::nbArc()
{
    return _nbArc;
}

Arc::~Arc()
{
    cout<<"\nDestructeur Arc "<<endl;
    _nbArc--;
}

int Arc::_nbArc=0;//Variable statique
