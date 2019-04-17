#include "graphe.h"
#include <iostream>


bool Graphe::getTypeReel() const
{
    return _typeReel;
}

void Graphe::setTypeReel(bool typeReel)
{
    _typeReel = typeReel;
    changeType(typeReel);
}

int Graphe::getTailleArc() const
{
    return _tailleArc;
}

Graphe::Graphe()
{
    _idg=_nbGraphes;     // identifiant
    _compteurS=0;
    _compteurA=0;
    _taille=0;		    // taille du graphe		// le nombre total de graphe (vu comme un compteur de _id)
    _tailleArc=0;
    _nom="NULL";		// nom du graphe
    _typeReel=true;
    _nbGraphes++;
}

Graphe::Graphe(int idg, string nom)
{
    _idg=idg;     // identifiant
    _compteurS=0;
    _compteurA=0;
    _tailleArc=0;
    _taille=0;		    // taille du graphe		// le nombre total de graphe (vu comme un compteur de _id)
    _typeReel=true;
    _nom=nom;		// nom du graphe

    _nbGraphes++;
}

Graphe::Graphe(const Graphe &g)
{
    _idg=g._idg;     // identifiant
    _compteurS=g._compteurS;
    _compteurA=g._compteurA;
    _tailleArc=g._tailleArc;
    _taille=g._taille;		    // taille du graphe		// le nombre total de graphe (vu comme un compteur de _id)
    _nom=g._nom;		// nom du graphe
    for(int k=0; k<_taille; k++)
    {
        _Mgraphe.push_back(vector<Arc*>(_taille));
    }

    for(int i=0; i<g._taille; i++)
    {
        for(int j=0; j<g._taille; j++)
        {
            if(g._Mgraphe[i][j] != NULL)
            {
                _Mgraphe[i][j]=new Arc(*g._Mgraphe[i][j]);		// le graphe
            }
            else
            {
                _Mgraphe[i][j]=NULL;
            }
        }
        _LSommets.push_back(new Sommet(*g._LSommets[i]));		    // la liste des sommets avec clé int et objet sommet
    }

    _nbGraphes++;
}

Graphe::Graphe(vector<Sommet>& vs,vector<Arc>& va)
{
    int id1,id2;
    _idg=_nbGraphes;
    _compteurS=0;
    _compteurA=0;
    _taille=0;
    _nom="NULL";
    _typeReel=false;
    for(int i=0; (unsigned int)i<vs.size(); i++)
    {
        ajouterSommet(vs[i]);
    }
    for(int j=0; (unsigned int)j<va.size(); j++)
    {
        for(int k=0; (unsigned int)k<_LSommets.size(); k++)
        {
            if(_LSommets[k]->getIds() == va[j].getOrigine()->getIds())
            {
                id1=k;
            }
            if(_LSommets[k]->getIds() == va[j].getDestination()->getIds())
            {
                id2=k;
            }
        }
        ajouterArc(id1,id2);
    }
    for(int t=0; (unsigned int)t<_LSommets.size(); t++)
    {
        _LSommets[t]->setIds(t);
    }

    _nbGraphes++;
}

Graphe::Graphe(Graphe& g,vector<Sommet>& vs)
{
    _idg=_nbGraphes;
    _compteurS=0;
    _compteurA=0;
    _taille=0;
    _nom="NULL";
    _typeReel=false;
    for(int i=0; (unsigned int)i<vs.size(); i++)
    {
        ajouterSommet(vs[i]);
    }
    for(int j=0; (unsigned int)j<_LSommets.size(); j++)
    {
        for(int k=0; (unsigned int)k<_LSommets.size(); k++)
        {
            if(g.existeArc(_LSommets[j]->getIds(), _LSommets[k]->getIds()))
            {
               ajouterArc(j,k);
               getArc(j,k)->setVal1( g.getArc(_LSommets[j]->getIds(), _LSommets[k]->getIds())->getVal1());
               getArc(j,k)->setVal2( g.getArc(_LSommets[j]->getIds(), _LSommets[k]->getIds())->getVal2());
            }
        }

    }
    for(int t=0; (unsigned int)t<_LSommets.size(); t++)
    {
        _LSommets[t]->setIds(t);
    }

    _nbGraphes++;
}

void Graphe::ajouterSommet(Point& p)
{
    _Mgraphe.push_back(vector<Arc*>(_taille + 1,NULL));
    for(int i=0; i<_taille; i++)
    {
        _Mgraphe[i].push_back(NULL);
    }
    _LSommets.push_back(new Sommet(p, _compteurS));
    _compteurS++;
    _taille++;
}

void Graphe::ajouterSommet(string nom, int ids, bool typeReel, double val[3], Point p)
{
    _Mgraphe.push_back(vector<Arc*>(_taille + 1,NULL));
    for(int i=0; i<_taille; i++)
    {
        _Mgraphe[i].push_back(NULL);
    }
    _LSommets.push_back(new Sommet(nom, ids, typeReel, val, p));
    _compteurS++;
    _taille++;
}

void Graphe::ajouterSommet(Sommet& sommet)
{
    _Mgraphe.push_back(vector<Arc*>(_taille + 1,NULL));
    for(int i=0; i<_taille; i++)
    {
        _Mgraphe[i].push_back(NULL);
    }
    _LSommets.push_back(new Sommet(sommet));
    _compteurS++;
    _taille++;
}

void Graphe::ajouterArc(int ido, int idd)
{
    _Mgraphe[ido][idd]= new Arc(_LSommets[ido], _LSommets[idd], _compteurA);
    _LSommets[ido]->DegrPlusPlus();
    _LSommets[idd]->DegrMoinsPlus();
    _LSommets[ido]->DegrTotal();
    _LSommets[idd]->DegrTotal();
    _compteurA++;
    _tailleArc++;
}

void Graphe::ajouterArc(string nom, int ida, bool typeReel, double val[2], int ido, int idd)
{
    _Mgraphe[ido][idd]= new Arc(nom, ida, typeReel, val, _LSommets[ido], _LSommets[idd]);
    _LSommets[ido]->DegrPlusPlus();
    _LSommets[idd]->DegrMoinsPlus();
    _LSommets[ido]->DegrTotal();
    _LSommets[idd]->DegrTotal();
    _compteurA++;
    _tailleArc++;
}

void Graphe::suppSommet(int id)
{
    for(int k=0; k<_taille; k++)
    {
        if(existeArc(id,k))
        {
            suppArc(id,k);
        }
    }
    for(int t=0; t<_taille; t++)
    {
        if(existeArc(t,id))
        {
            suppArc(t,id);
        }
    }
    for(int i=0; i<_taille; i++)
    {
        _Mgraphe[i].erase(_Mgraphe[i].begin()+id);
    }
    _Mgraphe.erase(_Mgraphe.begin()+id);
    _LSommets.erase(_LSommets.begin()+id);

    for(int j=id; j<(int)_LSommets.size(); j++)
    {
        _LSommets[j]->setIds(j);
    }
    _compteurS--;
    _taille--;
}

void Graphe::suppSommet(Sommet &sommet)
{
    int id=sommet.getIds();
    for(int k=0; k<_taille; k++)
    {
        if(existeArc(id,k))
        {
            suppArc(id,k);
        }
    }
    for(int t=0; t<_taille; t++)
    {
        if(existeArc(t,id))
        {
            suppArc(t,id);
        }
    }
    for(int i=0; i<_taille; i++)
    {
        _Mgraphe[i].erase(_Mgraphe[i].begin()+id);
    }
    _Mgraphe.erase(_Mgraphe.begin()+id);
    _LSommets.erase(_LSommets.begin()+id);

    for(int j=id; j<(int)_LSommets.size(); j++)
    {
        _LSommets[j]->setIds(j);
    }
    _compteurS--;
    _taille--;
}

void Graphe::suppArc(Sommet &orig, Sommet &dest)
{
    int ido=orig.getIds();
    int idd=dest.getIds();
    delete _Mgraphe[ido][idd];
    _Mgraphe[ido][idd]=NULL;
    _LSommets[ido]->DegrPlusMoins();
    _LSommets[idd]->DegrMoinsMoins();
    _LSommets[ido]->DegrTotal();
    _LSommets[idd]->DegrTotal();
    //_compteurA--;
    _tailleArc--;
}

void Graphe::suppArc(int ido, int idd)
{
     delete _Mgraphe[ido][idd];
    _Mgraphe[ido][idd]=NULL;
    _LSommets[ido]->DegrPlusMoins();
    _LSommets[idd]->DegrMoinsMoins();
    _LSommets[ido]->DegrTotal();
    _LSommets[idd]->DegrTotal();
    //_compteurA--;
    _tailleArc--;
}

//void Graphe::suppArc(Sommet &orig, Sommet &dest)
//{
//    int ido=orig.getIds();
//    int idd=dest.getIds();
//    int id =_Mgraphe[ido][idd]->getIda();
//    delete _Mgraphe[ido][idd];
//    _Mgraphe[ido][idd]=NULL;
//    _LSommets[ido]->DegrPlusMoins();
//    _LSommets[idd]->DegrMoinsMoins();
//    _LSommets[ido]->DegrTotal();
//    _LSommets[idd]->DegrTotal();
//    for(int i=0; i<_taille; i++)
//    {
//        for(int j=0; j<_taille; j++)
//        {
//           if(existeArc(i,j))
//           {
//               int ida = _Mgraphe[i][j]->getIda();
//               if( ida > id)
//               {
//                   _Mgraphe[i][j]->setIda(ida-1);
//               }
//           }
//        }
//    }
//    _compteurA--;
//}

//void Graphe::suppArc(int ido, int idd)
//{
//    int id =_Mgraphe[ido][idd]->getIda();
//    delete _Mgraphe[ido][idd];
//    _Mgraphe[ido][idd]=NULL;
//    _LSommets[ido]->DegrPlusMoins();
//    _LSommets[idd]->DegrMoinsMoins();
//    _LSommets[ido]->DegrTotal();
//    _LSommets[idd]->DegrTotal();
//    for(int i=0; i<_taille; i++)
//    {
//        for(int j=0; j<_taille; j++)
//        {
//           if(existeArc(i,j))
//           {
//               int ida = _Mgraphe[i][j]->getIda();
//               if( ida > id)
//               {
//                   _Mgraphe[i][j]->setIda(ida-1);
//               }
//           }
//        }
//    }
//    _compteurA--;
//}

bool Graphe::existeArc(Sommet &s1, Sommet &s2)
{
    return _Mgraphe[s1.getIds()][s2.getIds()] != NULL;
}

bool Graphe::existeArc(int ids1, int ids2)
{
    return _Mgraphe[ids1][ids2] != NULL;
}

vector<Arc*> Graphe::getSuccesseursArcs(int id)
{
    vector<Arc*> la;
    for(int i=0; i<_taille; i++)
    {
        if(existeArc(id, i))
        {
            la.push_back(_Mgraphe[id][i]);
        }
    }
    return la;
}

vector<Arc*> Graphe::getSuccesseursArcs(Sommet &s)
{
    vector<Arc*> la;
    int id = s.getIds();
    for(int i=0; i<_taille; i++)
    {
        if(existeArc(id, i))
        {
            la.push_back(_Mgraphe[id][i]);
        }
    }
    return la;
}

vector<Arc *> Graphe::getPredecesseurArcs(int id)
{
    vector<Arc*> la;
    for(int i=0; i<_taille; i++)
    {
        if(existeArc(i,id ))
        {
            la.push_back(_Mgraphe[i][id]);
        }
    }
    return la;
}

vector<Arc *> Graphe::getPredecesseurArcs(Sommet &s)
{
    vector<Arc*> la;
    int id = s.getIds();
    for(int i=0; i<_taille; i++)
    {
        if(existeArc(i, id))
        {
            la.push_back(_Mgraphe[i][id]);
        }
    }
    return la;
}

vector<vector<int> > Graphe::getMatrice()
{
    vector< vector<int> > matrice;
    matrice.resize(_taille);
    for(int i=0; i<_taille; i++)
    {
        matrice[i].resize(_Mgraphe.size());
        for(int j=0; j<_taille; j++)
        { 
            if(_Mgraphe[i][j] != NULL)
            {
                matrice[i][j] = 1;
            }
            else
            {
                 matrice[i][j] = 0;
            }
        }
    }
    return matrice;
}


string Graphe::getNom()
{
    return _nom;
}

int Graphe::getCompteurS() const
{
    return _compteurS;
}

int Graphe::getCompteurA() const
{
    return _compteurA;
}

int Graphe::getTaille()
{
    return _taille;
}

int Graphe::getIdg()
{
    return _idg;
}

Sommet *Graphe::getSommet(int id)
{
    return _LSommets[id];
}

Arc *Graphe::getArc(int ido, int idd)
{
    return _Mgraphe[ido][idd];
}

Arc *Graphe::getArc(int ida)
{
    for(int i = 0; i< _taille; i++){
        for(int j = 0; j<_taille; j++){
            if(existeArc(i, j)){
                if(_Mgraphe[i][j]->getIda()==ida){
                    return _Mgraphe[i][j];
                }
            }
        }
    }
    return NULL;
}


int Graphe::nbGraphes()
{
    return _nbGraphes;
}

vector<Sommet*> Graphe::getLSommets() const
{
    return _LSommets;
}

void Graphe::setNom(string nom)
{
    _nom=nom;
}

void Graphe::setIdg(int idg)
{
    _idg = idg;
}

void Graphe::setTaille(int taille)
{
    _taille = taille;
}

void Graphe::marquerSommet(int id)
{
    _LSommets[id]->setEtat(true);
}

void Graphe::demarquerSommet(int id)
{
    _LSommets[id]->setEtat(false);
}

bool Graphe::visiter(int id)
{
    return _LSommets[id]->getEtat();
}

void Graphe::initialiserVal2Arc(){
    for(int i = 0; i < _taille; i++){
        for(int j = 0; j < _taille; j++){
            if(existeArc(i, j))
                if(this->getArc(i, j) != NULL)
                   this->getArc(i, j) ->setVal2(0);
        }
    }
}

void Graphe::initialiserVal2Sommet(){
    for(int i = 0; i < _taille; i++){
        _LSommets[i]->setVal2(0);
    }
}
void Graphe::initialiserVal3Sommet(){
    for(int i = 0; i < _taille; i++){
        _LSommets[i]->setVal3(0);
    }
}
void Graphe::initialiserEtatArc(){
    for(int i = 0; i < _taille; i++){
        for(int j = 0; j < _taille; j++){
            if(existeArc(i, j))
                if(this->getArc(i, j) != NULL)
                    this->getArc(i, j)->setEtat(false);
        }
    }
}
void Graphe::initialiserEtatSommet(){
    for(int i = 0; i < _taille; i++){
        _LSommets[i]->setEtat(false);
    }
}
void Graphe::initialiserCouleurArc(){
    for(int i = 0; i < _taille; i++){
        for(int j = 0; j < _taille; j++){
            if(existeArc(i, j))
                if(this->getArc(i, j) != NULL){
                    this->getArc(i, j)->setColorR(255);
                    this->getArc(i, j)->setColorG(255);
                    this->getArc(i, j)->setColorB(255);
                }
        }
    }
}
void Graphe::initialiserCouleurSommet(){
    for(int i = 0; i < _taille; i++){
         this->getSommet(i)->setColorR(240);
         this->getSommet(i)->setColorG(240);
         this->getSommet(i)->setColorB(0);
    }
}

void Graphe::decrisToi()
{
    cout<<" GRAPHE\nNom : "<<_nom<<
    "\nIdg : "<<_idg<<
    "\nTaille : "<<_taille<<endl;
}

void Graphe::changeType(bool type){
    for(int i = 0; i < _taille; i++){
        this->getSommet(i)->setTypeReel(type);
        this->getSommet(i)->setVal1(this->getSommet(i)->getVal1());
    }
    for(int i = 0; i < _taille; i++){
        for(int j = 0; j < _taille; j++){
            if(existeArc(i, j)){
                if(this->getArc(i, j)!= NULL){
                    this->getArc(i,j)->setTypeReel(type);
                    this->getArc(i,j)->setVal1(this->getArc(i,j)->getVal1());
                }
            }
        }
    }
}

ostream& operator<<(ostream& flux, Graphe& g)
{

    flux << " GRAPHE\nNom : "<<g._nom<<
            "\nIdg : "<<g._idg<<
            "\nTaille : "<<g._taille<<endl;
    return flux;
}

Graphe& Graphe::operator=(Graphe& g)
{
    _idg=g._idg;     // identifiant
    _compteurS=g._compteurS;
    _compteurA=g._compteurA;
    _taille=g._taille;		    // taille du graphe		// le nombre total de graphe (vu comme un compteur de _id)
    _nom=g._nom;		// nom du graphe
//*********************** liber la memoire ***************
    if(_taille > 0)
    {
        for(int i=0; i<_taille; i++)
        {
            for(int j=0; j<_taille; j++)
            {
                if(_Mgraphe[i][j] != NULL)
                {
                    delete _Mgraphe[i][j];
                    _Mgraphe[i][j]=NULL;
                }
            }
            delete _LSommets[i];
            _LSommets[i]=NULL;
        }

    }
//********************************************************
    for(int k=0; k<_taille; k++)
    {
        _Mgraphe.push_back(vector<Arc*>(_taille));
    }

    for(int i=0; i<g._taille; i++)
    {
        for(int j=0; j<g._taille; j++)
        {
            if(g._Mgraphe[i][j] != NULL)
            {
                _Mgraphe[i][j]=new Arc(*g._Mgraphe[i][j]);		// le graphe
            }
            else
            {
                _Mgraphe[i][j]=NULL;
            }
        }
        _LSommets.push_back(new Sommet(*g._LSommets[i]));		    // la liste des sommets avec clé int et objet sommet
    }
    return *this;
}


Graphe::~Graphe()
{
    if(_taille > 0)
    {
        for(int i=0; i<_taille; i++)
        {
            for(int j=0; j<_taille; j++)
            {
                if(_Mgraphe[i][j] != NULL)
                {
                    delete _Mgraphe[i][j];
                    _Mgraphe[i][j]=NULL;
                }
            }
            delete _LSommets[i];
            _LSommets[i]=NULL;
        }

    }

    //delete _Mgraphe;
    _nbGraphes--;
    cout<< "Destructeur Graphe"<<endl;
}

int Graphe::_nbGraphes=0;
