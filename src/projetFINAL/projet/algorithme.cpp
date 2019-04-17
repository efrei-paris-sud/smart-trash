#include "algorithme.h"

double Max(double s1, double s2){
    if(s1 >= s2) return s1;
    return s2;
}

double Min(double s1, double s2){
    if(s1 <= s2) return s1;
    else return s2;
}

double dijkstra(Sommet &depart, Sommet &arrivee, Graphe *graphe){
    Sommet *actuel = new Sommet();
    Sommet *fils = new Sommet();

    vector<int> idAVisiter;
    vector<Arc*> arcsuccess;
    double tmp = 0;
    graphe->initialiserVal2Sommet();
    graphe->initialiserVal2Arc();
    graphe->initialiserCouleurSommet();
    graphe->initialiserCouleurArc();
    graphe->initialiserEtatSommet();
    graphe->initialiserVal3Sommet();

    for(int i = 0; i < graphe->getTaille(); i++){
        graphe->getSommet(i)->setVal2(9999999);
    }


    int i = 0;
    int nbfoisvisiter = graphe->getTailleArc();
    idAVisiter.resize(1);
    depart.setVal2(0);
    depart.setEtat(true);
    actuel = graphe->getSommet(depart.getIds());

    while(i < (int)idAVisiter.size()){
        //on recupere les successeurs du sommet actuel
        arcsuccess = graphe->getSuccesseursArcs(actuel->getIds());
        for(int j = 0; j < (int)arcsuccess.size(); j++){
            //fils = 1 des successeurs du sommet actuel
            if(arcsuccess[j] == NULL) j = arcsuccess.size();
            fils = arcsuccess[j]->getDestination();
            //on ajoute a la liste des sommets a parcourir le fils (si celui ci n'est pas l'arrivee)
            idAVisiter.push_back(fils->getIds());

            tmp = fils->getVal2();

            fils->setVal2(min(actuel->getVal2() + arcsuccess[j]->getVal1(), fils->getVal2()));

            if(tmp != fils->getVal2()){
                fils->setVal3(actuel->getIds());
            }
            else if(tmp == 0){
                fils->setVal3(actuel->getIds());
            }
            nbfoisvisiter--;
        }
        //le sommet actuel et le sommet suivant a visiter dans la liste des sommets
        actuel = graphe->getSommet(idAVisiter[i]);
        i++;
    }
    //creer une liste de sommet du plus court chemin
    vector<Sommet *> chemin;
    actuel = graphe->getSommet(arrivee.getIds());

    chemin.emplace(chemin.begin(), actuel);
    while(actuel->getVal3() != depart.getIds()){
        actuel = graphe->getSommet(actuel->getVal3());
        chemin.emplace(chemin.begin(), actuel);
    }
    chemin.emplace(chemin.begin(), graphe->getSommet(depart.getIds()));

    //change la couleur des arcs et sommets du plus court chemin
    for(int i = 0; i < (int)chemin.size(); i++){
        chemin[i]->setColorR(0);
        chemin[i]->setColorG(0);
        chemin[i]->setColorB(255);
    }
    for(int i = 0; i < (int) chemin.size()-1; i++){
        graphe->getArc(chemin[i]->getIds(), chemin[i+1]->getIds())->setColorR(0);
        graphe->getArc(chemin[i]->getIds(), chemin[i+1]->getIds())->setColorG(0);
        graphe->getArc(chemin[i]->getIds(), chemin[i+1]->getIds())->setColorB(255);
    }
    double val = chemin.back()->getVal2();
//    cout<<val;
    //remet les valeurs du graphes au bonne valeurs
    graphe->initialiserEtatSommet();
    graphe->initialiserVal3Sommet();

    return val;
}

double fordBellman(Sommet &depart, Sommet &arrivee, Graphe *graphe){
   Sommet *actuel = new Sommet();
   Sommet *fils = new Sommet();

   vector<int> idAVisiter;
   vector<Arc*> arcsuccess;
   double tmp = 0;

   graphe->initialiserVal2Sommet();
   graphe->initialiserVal2Arc();
   graphe->initialiserCouleurSommet();
   graphe->initialiserCouleurArc();
   graphe->initialiserEtatSommet();
   graphe->initialiserVal3Sommet();
   int i = 0;

   int nbfoisvisiter = graphe->getTailleArc();
   idAVisiter.resize(1);

   depart.setEtat(true);
   actuel = graphe->getSommet(depart.getIds());
//   for(int i = 0; i < (int)graphe->getSuccesseursArcs(depart.getIds()).size(); i++)
//    if(graphe->getSuccesseursArcs(depart.getIds())[i]->getVal2() == 0) return 9999999999;
   while(i < (int)idAVisiter.size()){
       //on recupere les successeurs du sommet actuel

       arcsuccess = graphe->getSuccesseursArcs(actuel->getIds());
//       cout<<arcsuccess.size()<<endl;
       for(int j = 0; j < (int)arcsuccess.size(); j++){
           //fils = 1 des successeurs du sommet actuel

           if(arcsuccess[j] == NULL){
               break;
           }
           fils = arcsuccess[j]->getDestination();
           //on ajoute a la liste des sommets a parcourir le fils (si celui ci n'est pas l'arrivee)
           idAVisiter.push_back(fils->getIds());

           tmp = fils->getVal2();

           fils->setVal2(max(actuel->getVal2() + arcsuccess[j]->getVal1(), fils->getVal2()));

           if(tmp != fils->getVal2()){
               fils->setVal3(actuel->getIds());
           }
           else if(tmp == 0){
               fils->setVal3(actuel->getIds());
           }
           nbfoisvisiter--;
       }
       //le sommet actuel et le sommet suivant a visiter dans la liste des sommets
       actuel = graphe->getSommet(idAVisiter[i]);
       i++;
   }

   //creer une liste de sommet du plus court chemin
   vector<Sommet *> chemin;
   actuel = graphe->getSommet(arrivee.getIds());

   chemin.emplace(chemin.begin(), actuel);
   while(actuel->getVal3() != depart.getIds()){
       actuel = graphe->getSommet(actuel->getVal3());
       chemin.emplace(chemin.begin(), actuel);
   }
   chemin.emplace(chemin.begin(), graphe->getSommet(depart.getIds()));

   //change la couleur des arcs et sommets du plus court chemin
   for(int i = 0; i < (int)chemin.size(); i++){
       chemin[i]->setColorR(250);
       chemin[i]->setColorG(0);
       chemin[i]->setColorB(0);
   }
   for(int i = 0; i < (int) chemin.size()-1; i++){
       graphe->getArc(chemin[i]->getIds(), chemin[i+1]->getIds())->setColorR(250);
       graphe->getArc(chemin[i]->getIds(), chemin[i+1]->getIds())->setColorG(0);
       graphe->getArc(chemin[i]->getIds(), chemin[i+1]->getIds())->setColorB(0);
   }
   double val = chemin.back()->getVal2();
   //remet les valeurs du graphes au bonne valeurs
   graphe->initialiserEtatSommet();
   graphe->initialiserVal3Sommet();
   return val;
}

bool existeChemin(Sommet *depart, Sommet *arrivee, Graphe *graphe) {
    vector <vector<int> > matadj;
    vector <vector<int> > prodmat;

    bool chemin = false;

    matadj = graphe->getMatrice();
    prodmat = graphe->getMatrice();
    if(prodmat[depart->getIds()][arrivee->getIds()] == 1) return true;
    for (int i = 0; i < (int)matadj.size() && chemin == false; i++) {
        if (prodmat[depart->getIds()][arrivee->getIds()] == 1) {
                return true;
        }
        prodmat = getProduitMatriciel(matadj, prodmat);
    }
    return chemin;
}

 vector< vector<int> > getProduitMatriciel( vector< vector<int> > matrice, vector< vector<int> > matrice2 ) {
    vector< vector<int> > nouv;
    nouv.resize(matrice.size());
    for (int i = 0; i < (int)matrice.size(); i++)
    {
        nouv[i].resize(matrice.size());
        for (int j = 0; j < (int)matrice.size(); j++)
        {
            for (int k = 0; k < (int)matrice.size(); k++)
            {
                nouv[i][j] = matrice[i][k] * matrice2[k][j] + nouv[i][j];
            }
            if (nouv[i][j] > 0) nouv[i][j] = 1;
        }
    }
    return nouv;
 }

bool cycle(Graphe *g) {
   vector <vector<int> > matadj;
   vector <vector<int> > prodmat;

   bool circuit = false;

   matadj = g->getMatrice();
   prodmat = g->getMatrice();
   for(int j = 0; j < g->getCompteurS() && circuit == false; j++){
        for (int i = 0; i < g->getCompteurS() && circuit == false; i++) {
           if (prodmat[i][i] == 1) {
                   circuit  = true;
           }

        }

        prodmat = getProduitMatriciel(matadj, prodmat);
   }
   return circuit;

}

bool estSource(Sommet *s, Graphe *g){
    vector<Arc *> pred;

    pred = g->getPredecesseurArcs(*s);

    if((int)pred.size() == 0) return true;

    else return false;
}

bool estPuits(Sommet *s, Graphe *g){
    vector<Arc *> succ;

    succ = g->getSuccesseursArcs(*s);

    if((int)succ.size() == 0) return true;

    else return false;
}

bool conditionPertFlot(Sommet *source, Sommet *puits, Graphe *g){
    for(int i = 0; i < (int)g->getTaille(); i++){
        if(i != source->getIds())
            if(existeChemin(source, g->getSommet(i), g) == false) return false;
    }
    for(int i = 0; i < (int)g->getTaille(); i++){
        if(i != puits->getIds())
            if(existeChemin(g->getSommet(i), puits, g) == false) return false;
    }
    return true;
}

//***********************enlever comantaire ,Fonction inutile,gerer mieux les paramètres, inclure les modifs , ordonner les commentaires et le code ***********//

/*************problème :: les boucles for soit l'une soit l'autre pareil pour le vecteur***********/
bool Existe_chaine_ame(Graphe *g,Sommet &s,Sommet &p,int Ts[][2],int Ta[][4]){                 //1->marque positif //-1 sinon
    Ts[s.getIds()][0]=1 ;
    int modif = 1;
    int tmp =0;

    while(modif == 1){         //Tant que le sommet puit n'est pas marqué et que l'on peut marquer des sommets
        modif = 0;

        for (int i=0;i<g->getTaille();i++){                       //On parcour le tableaux ts
            if(Ts[i][0] == 0){                                    //si le sommet na pas deja été marqué
            tmp=0;
            if(s.getIds()!= i ){                                  //on ne traite pas le sommet source car deja marqué
            vector <Arc *> vsp = g->getPredecesseurArcs(i);         //on récupere une liste d'arcs avec le sommet(i) comme extrémite
            if(vsp.size()!=0){
                for (int j=0 ;j<(int)vsp.size();j++){
                    if(vsp[j] != NULL){
                        if (Ts[vsp[j]->getOrigine()->getIds()][0] == 1 ){           // initial value-> or Ts[vsp[j]->getOrigine()->getIds()][0] == 2on récupère l'id du sommet origine pour chaque arc de la liste puis on regarde si le sommet et marqué dans le tableau
                            if(vsp[j]->getVal1()-Ta[vsp[j]->getIda()][0] > 0){																	    //on vérifie que L'arc n'est pas saturé soit (capacité - flux > 0)
                                Ts[i][0]=1;                                                   //on met un marquage positif
                                Ts[i][1]=vsp[j]->getOrigine()->getIds();                          //on ajoute l'ids du sommet antécédant au sommet courant dans notre tableau de marquage
                                modif = 1;
                                tmp=1;
                                if(vsp[j] != NULL)
                                Ta[vsp[j]->getIda()][3]=1;                                        //on marque l'arc + pour signifier que ce n'est pas un arc inverse.
                            break;
                            }
                       }
                    }
                }
            }
              if(tmp==0){
                if(Ts[i][0]!=1 or Ts[i][0]!=2){     //si le sommet n'est pas encore marqué on va regarder les arcs inverses
                    vector <Arc *> vss = g->getSuccesseursArcs(i);
                    if(vss.size()!=0){
                    for (int j=0 ;j<(int)vss.size();j++){
                        if(vss[j] != NULL){
                           if (Ts[vss[j]->getDestination()->getIds()][0] == 1 or Ts[vss[j]->getDestination()->getIds()][0] == 2){           //on récupère l'id du sommet d'arrivé pour chaque arc de la liste puis on regarde si le sommet et marqué dans le tableau
                              if(Ta[vss[j]->getIda()][0]>0){																	    //on vérifie que le flux est supérieur à 0
                                  Ts[i][0]=2;                                                   //on met un marquage négatif
                                  Ts[i][1]=vss[j]->getDestination()->getIds();                          //on ajoute l'ids du sommet antécédant au sommet courant dans notre tableau de marquage
                                  modif = 1;					                                  //on indique que l'arc est inverse

                                  if(vsp[j] != NULL)
                                  Ta[vsp[j]->getIda()][3] = 2;
                                  break;
                              }
                           }
                        }
                    }
                  }
               }
            }
         }
         if(Ts[p.getIds()][0]== 1 ||Ts[p.getIds()][0] ==  2)
         {
             return true;}                 //  si le sommet puit est marquer on a trouver notre chaine améliorante
      }
  }//fermeture for
    } //fermeture while
    return false ;  // on retourne false car le sommet puit n'a pas été marqué .
 }

void init1(int Ta[][4],int Ts[0][2],Graphe *g,Sommet &s ,Sommet &p){

    for(int i = 0;i < g->getCompteurS() ; i++){
        if (i==s.getIds()){
        Ts[i][0] = 1;
    }
        else {
        Ts[i][0] = 0 ;
        }
        Ts[i][1] = -1;
     }
     for(int j = 0;j < g->getCompteurA() ; j++){
        Ta[j][0] = 0;                             //Premiere valeur du tableau les flux
        if(g->getArc(j) != NULL)
        Ta[j][1] = g->getArc(j)->getVal1();       //deuxieme capacités
        Ta[j][2] = 999999;							//troisième valeur pr calculer le flux améliorant
        Ta[j][3] = 0;                               //sens de l'arc dans le chemin améliorant (inverse ou directe)
     }
}

void init(int Ta[][4],int Ts[0][2],Graphe* g,Sommet &s){
  for(int i = 0;i < g->getCompteurS() ; i++){
     if (i==s.getIds()){
        Ts[i][0] = 1;
    }
     else {
         Ts[i][0] = 0 ;
         Ts[i][1] = -1;
     }
 }
  for(int j = 0;j < g->getCompteurA() ; j++){
     Ta[j][2] = 999999;							//troisième valeur pr calculer le flux améliorant
     Ta[j][3] = 0;                               //sens de l'arc dans le chemin améliorant (inverse ou directe)
     }


}

vector<int> getchaineameliorante(int Ts[][2],Graphe *g, Sommet &s, Sommet &p,int Ta[][4]){

    vector<int> vida;
    int i = p.getIds();
    while(i!=s.getIds()){
        if(g->existeArc(Ts[i][1],i) && g->getArc(Ts[i][1], i) != NULL){
        vida.push_back(g->getArc(Ts[i][1],i)->getIda());
        }
        else {
        vida.push_back(g->getArc(i,Ts[i][1])->getIda());              //si larc uv n'existe pas alors c'est forcément un arc inverse v et u if faut donc inverser les Id des sommets passés en prramètre de getArc.
        }
        i = Ts[i][1];
    }
    return vida;

}

int augmenterflux(int Ta[][4],vector<int> vida,int size_Ta,int flot_max){
    flot_max=flot_max+0;
for(int i=0;i<size_Ta;i++){                                     //On parcour le tableau d'arc Ta
    for(int j=0;j<(int)vida.size();j++){                                  //on recherche les arcs apartenant au chemin améliorant (vector vida)
        if(i==vida[j]){
            if(Ta[i][3]==1){
                Ta[i][2]=Ta[i][1]-Ta[i][0];                //on met a jour Epsilon
                }
            else{
                Ta[i][2]=Ta[i][0];          // ta[i][0] tj positif dans ce cas ci
                }
       }
   }
 }
/*******minimunEpsil***********/

int min = Ta[vida[0]][2] ;     //on atribue la  valeur  du premier chemin
for(int i=0;i<size_Ta;i++){
    for(int j=0;j<(int)vida.size();j++){
        if(i==vida[j]){
            if(Ta[i][2]< min ){
               min=Ta[i][2];
               }
          }
       }
}
  //On augmente le flux pour les arc + de min et on diminue de min pour les arcs -//

for(int i=0;i<size_Ta;i++){                                     //On parcour le tableau d'arc Ta
    for(int j=0;j<(int)vida.size();j++){                                  //on recherche les arcs apartenant au chemin améliorant (vector vida)
        if(i==vida[j]){
            if(Ta[i][3]==1){
                Ta[i][0]+=min;                  //on augmente le flux du minimun des flux de notre chaine améliorante
                }
            else{
                Ta[i][0]-=min;       // ta[i][0] tj positif dans ce cas ci
                }
       }
   }
}
return min;

}

void Actualiser_graphe(Graphe *g,int Ta[][4]){
        for(int i=0 ;i<g->getTailleArc();i++)
        {
            if(g->getArc(i) != NULL){
         g->getArc(i)->setVal2(Ta[i][0]);         //On recopie les flux ds les arcs du vraie graphe

         if(Ta[i][1]-Ta[i][0] == 0){           //on modifie la couleur des arcs saturés
            g->getArc(i)->setColorR(0);
            g->getArc(i)->setColorG(191);
            g->getArc(i)->setColorB(255);
         }
        }

   }
}

int Flot_Max(Graphe *g,Sommet &s ,Sommet &p){


/*******Verfifications*****************/
/*if(!Connexe(g)){}

if(Cycle(g)){}

if(!Spuit(p)||!Ssource(s)){}*/


/********Init***********/
 int Ts[g->getCompteurS()][2];
 int Ta[g->getCompteurA()][4];

 init1(Ta,Ts,g,s,p);
 g->initialiserCouleurArc();
 g->initialiserCouleurSommet();
 g->initialiserVal2Sommet();
 g->initialiserVal3Sommet();
 g->initialiserEtatArc();
 g->initialiserEtatSommet();
 g->initialiserVal2Arc();

// affiche_Ta(Ta,g);
// affiche_Ts(Ts,g);
 int flot_max = 0;
// std::cout<<"211"<<std::endl;
int  tailleTa = g->getCompteurA();
while(Existe_chaine_ame(g,s,p,Ts,Ta)){

//   std::cout<<"l215-on saprète à extraire la chaine améliorante"<<std::endl;
    vector<int> VIda = getchaineameliorante(Ts,g,s,p,Ta);
//    std::cout<<"la chaine améliorante est composé de "<<std::endl;
//    affichevector(VIda);
////    std::cout<<"on augmente le flux"<<std::endl;
    flot_max += augmenterflux(Ta,VIda,tailleTa,flot_max);
//    std::cout<<"Nouveau flot max = "<<flot_max<<std::endl;
    init(Ta,Ts,g,s);

   // affiche_Ts(Ts,g);

}
//affiche_Ta(Ta,g);
Actualiser_graphe(g,Ta);
return flot_max;
}

///* partie Parcours */ //*********************************************************
///* Parcours en profondeur */
void Profondeur (Graphe *g, stack<int>& pile, int Etat[], int Pred[]) {
    vector<int> vect;
    while ( !pile.empty() )
    {
        int i = pile.top(); 		  // récupère le sommet de la pile
        pile.pop(); 				  // depile
        //cout<<" " <<i<<endl;
        vect.push_back(i);
        vector<Arc*> ls = g->getSuccesseursArcs(i);
        for (vector<Arc*>::iterator it=ls.begin(); it!=ls.end(); ++it)
        {
            int j = (*it)->getDestination()->getIds();
            if (Etat[j] == 0) 	   	 // !g.visiter(j)
            {
                pile.push(j); 		//en cours de visite (enpile)
                Etat[j] = 1; 		// en cours
                Pred[j] = i; 		//i est pere de j
            }
        }
        Etat[i] = 2; 				// le sommet i a été visité
    }
    //int t=1;
    for(int a=0; a<(int)vect.size()-1; a++)
    {
        //int tmp = -1;
        if(g->existeArc(vect[a],vect[a+1]))
        {
            g->getSommet(vect[a+1])->setColorG(255); // la couleur
            g->getSommet(vect[a+1])->setColorR(0);
            g->getSommet(vect[a+1])->setColorB(0);
            g->getArc(vect[a],vect[a+1])->setColorB(255);
            g->getArc(vect[a],vect[a+1])->setColorG(0);
            g->getArc(vect[a],vect[a+1])->setColorR(0);
//            if(tmp != vect[a])
//            {g->getArc(vect[a],vect[a+1])->setVal2(t);}
//            t++;
//            tmp=vect[a];
        }

    }
    //int z;
    for(int w=0;(unsigned int )w<vect.size(); w++)
    {   //z=1;
        g->getSommet(vect[w])->setColorG(255); // la couleur
        g->getSommet(vect[w])->setColorR(0);
        g->getSommet(vect[w])->setColorB(0);
        for(int y=0;(unsigned int )y<vect.size();y++)
        {
            //cout<<"ici "<<vect[w];
            if(g->existeArc(vect[w],vect[y]) && g->getSommet(vect[y])->getColorG() == 0)
            {
                //cout<< "if ";
                g->getSommet(vect[y])->setColorG(255); // la couleur
                g->getSommet(vect[y])->setColorR(0);
                g->getSommet(vect[y])->setColorB(0);
                g->getArc(vect[w],vect[y])->setColorB(255);
                g->getArc(vect[w],vect[y])->setColorG(0);
                g->getArc(vect[w],vect[y])->setColorR(0);
                //g->getArc(vect[w],vect[y])->setVal2(z);
                //z++;
                //cout<<" "<<z;
            }

        }
    }
    //cout<<endl;
}

void Pprofondeur(Graphe* G)
{
    G->initialiserVal2Arc();
    G->initialiserEtatSommet();
    G->initialiserEtatArc();

    G->initialiserVal2Sommet();
    G->initialiserVal3Sommet();
    G->initialiserCouleurArc();
    G->initialiserCouleurSommet();

    int *Etat =  new int [G->getTaille()];// initialisé a 0  créer avec new

    int *Pred = new int [G->getTaille()]; // qui est pere de qui     créer avec new
    stack<int> pile;
    for(int i=0; i<G->getTaille(); i++){// initialise le tableau de père
        Pred[i] = -1;
        Etat[i]=0;
        G->getSommet(i)->setColorR(0);
        G->getSommet(i)->setColorG(0);
        G->getSommet(i)->setColorB(0);
    }
    for(int s=0; s<G->getTaille(); s++){// parcours en profondeur sur tous les sommets du graphe
        if(Etat[s] == 0){
            pile.push(s);
            Etat[s]=1;
            Profondeur (G, pile, Etat, Pred);
        }
    }
    delete[] Etat;
    delete[] Pred;
}

/* Parcours en largeur */
void Largeur (Graphe* g, queue<int>& file, int Etat[], int Pred[])
{
    vector<int> vect;
    while ( !file.empty() )
    {
        int i = file.front(); 		// récupère la tête de la file
        file.pop(); 				// defile
        //cout<<" " <<i;
        vect.push_back(i);
        vector<Arc*> ls = g->getSuccesseursArcs(i);
        for (vector<Arc*>::iterator it=ls.begin(); it!=ls.end(); ++it)
        {
            int j = (*it)->getDestination()->getIds();
            if (Etat[j] == 0) 		// !g.visiter(j))
            {
                file.push(j); 		//en cours de visite (enfile)
                Etat[j] = 1; 		// en cours
                Pred[j] = i; 		//i est pere de j
            }
        }
        Etat[i] = 2; 				// le sommet i a été visité
    }
    int z;
    for(int w=0;(unsigned int )w<vect.size(); w++)
    {   z=1;
        g->getSommet(vect[w])->setColorG(255); // la couleur
        g->getSommet(vect[w])->setColorR(0);
        g->getSommet(vect[w])->setColorB(0);
        for(int y=0;(unsigned int )y<vect.size();y++)
        {
            //cout<<"ici "<<vect[w];
            if(g->existeArc(vect[w],vect[y]) && g->getSommet(vect[y])->getColorG() == 0)
            {
                //cout<< "if ";
                g->getSommet(vect[y])->setColorG(255); // la couleur
                g->getSommet(vect[y])->setColorR(0);
                g->getSommet(vect[y])->setColorB(0);
                g->getArc(vect[w],vect[y])->setColorB(255);
                g->getArc(vect[w],vect[y])->setColorG(0);
                g->getArc(vect[w],vect[y])->setColorR(0);
                g->getArc(vect[w],vect[y])->setVal2(z);
                z++;
                //cout<<" "<<z;
            }

        }
    }
}

void Plargeur(Graphe* G)
{
    G->initialiserVal2Arc();
    G->initialiserEtatSommet();
    G->initialiserEtatArc();
    G->initialiserVal2Sommet();
    G->initialiserVal3Sommet();
    G->initialiserCouleurArc();
    G->initialiserCouleurSommet();

    int *Etat =  new int [G->getTaille()];// initialisé a 0  créer avec new

    int *Pred = new int [G->getTaille()]; // qui est pere de qui     créer avec new
    queue<int> file;
    for(int i=0; i<G->getTaille(); i++){// initialise le tableau de père
        Pred[i] = -1;
        Etat[i]=0;
        G->getSommet(i)->setColorR(0);
        G->getSommet(i)->setColorG(0);
        G->getSommet(i)->setColorB(0);
    }
    for(int s=0; s<G->getTaille(); s++){// parcours en profondeur sur tous les sommets du graphe
        if(Etat[s] == 0){
            file.push(s);
            Etat[s]=1;
            Largeur (G, file, Etat, Pred);
        }
    }
    delete[] Etat;
    delete[] Pred;
}


///* Graphe connexe */ //*****************************************************************
bool GrapheConnexe(Graphe* G)
{
    G->initialiserVal2Arc();
    G->initialiserEtatSommet();
    G->initialiserEtatArc();

    G->initialiserVal2Sommet();
    G->initialiserVal3Sommet();
    G->initialiserCouleurArc();
    G->initialiserCouleurSommet();

    int *Etat =  new int [G->getTaille()];// initialisé a 0  créer avec new

    int *Pred = new int [G->getTaille()]; // qui est pere de qui     créer avec new
    Graphe gtmp(*G);
    stack<int> pile;
    for(int i=0; i<G->getTaille(); i++){// initialise le tableau de père
        Pred[i] = -1;
        Etat[i]=0;
    }
    for(int s=0; s<G->getTaille(); s++){// parcours en profondeur sur tous les sommets du graphe
        if(Etat[s] == 0){
            pile.push(s);
            Etat[s]=1;
            Profondeur (&gtmp, pile, Etat, Pred);
        }
    }

    vector< vector<int> > compoConnex(G->getTaille()); // a modiffier

    //for(int i=0; i<G.getTaille; i++){ // initialisation
        //compoConnex[i] = NULL;
    //}

    for(int i=0; i<G->getTaille(); i++){ // trouve le père de chaque sommet
        int root = i;
        while(Pred [root] !=-1){
            root=Pred[root];
        }
        //int root = Pred[i]; // root = Pere de i
        compoConnex[root]= vector<int>();
        vector<int>::iterator it;
        it = compoConnex[root].begin();
        compoConnex[root].insert (it,i); // ajoute i dans la case de son père
    }
    int tmp;
    for(int i=0; i<G->getTaille(); i++){ // affiche chaque composante connexe
        //affichePile(compoConnex[i]);
        //cout<<" "<<i;
        int couleurR=(i*180+200)%255;
        int couleurG=(i*200+100)%255;
        int couleurB=(i*52+50)%255;

//        for(int j=0; j<(int)compoConnex[i].size();j++)
//        {    cout<<" "<<compoConnex[i][j];
//        }
        //cout<<endl;
            tmp = i;
            int j=0;
            if(j<(int)compoConnex[i].size()){
            while(tmp<= compoConnex[i][j])
            {
                //cout<<" "<<tmp<<" ok "<<i;
                G->getSommet(tmp)->setColorR(couleurR);
                G->getSommet(tmp)->setColorG(couleurG);
                G->getSommet(tmp)->setColorB(couleurB);
                //int sommet = compoConnex[i][j];
                //G.getSommet(sommet)->setColorR(i*couleur+23);
                //G.getSommet(sommet)->setColorG(i*couleur+23);
                //G.getSommet(sommet)->setColorB(i*couleur+23);
                //G.getArc(i,sommet)->setColorR(i*couleur+23);
                //G.getArc(i,sommet)->setColorG(i*couleur+23);
                //G.getArc(i,sommet)->setColorB(i*couleur+23);
                tmp++;
            }

                      }
//        cout<<endl;
    }

    int times = 0;
    for(int i=0; i<G->getTaille(); i++){ // trouvé une composante connexe
        if(compoConnex[i].size() != 0){
            times++;
        }
    }
    if(times != 1){ // s il y a une composante connexe
        //printf("ce graph n'est pas connexe\n");
        return false;
    }
    //for(int i=0; i<G.nombre_sommet; i++){
        //if(degre(G,i)%2){
            //printf("ce graph ne contient pas un circuit eulerien car il existe des/un sommet/s avec un degre impair\n");
        //}
    //}
    delete[] Etat;
    delete[] Pred;
    //printf("ce graph est connexe\n");
    return true;
}

///* Partie Euleurien */ //*****************************************************************

///*test de degré */
bool DegImpair (Graphe& g)
{
    for(int d=0; d<g.getTaille(); d++)
    {
        if(g.getSommet(d)->getDegrTotal() % 2 == 1)
        {
            return true;
        }
    }
    return false;
}

///*Graphe Eulerien */
bool euler(Graphe* G, Sommet& s)
{
    G->initialiserVal2Arc();
    G->initialiserEtatSommet();
    G->initialiserEtatArc();

    G->initialiserVal2Sommet();
    G->initialiserVal3Sommet();
    G->initialiserCouleurArc();
    G->initialiserCouleurSommet();
    Graphe gtmp(*G);
    if(!GrapheConnexe(&gtmp))		// vérifie que le graphe est connexe
    {
//        cout<<" Le graphe n'est pas connexe"<<endl;
        return false;
    }
    G->initialiserEtatSommet();
    if(DegImpair(*G))				// vérifie qu'il y à aucun sommet de degré impaire
    {
//        cout<<" Le graphe contient sommet de degré impaire"<<endl;
       return false;
    }

    int star = s.getIds();          // star = a = s
    int position;                   // pisition du sommet dans tour
    bool circuit = false;           // circuit = true si un circuit sinon false
    vector<int> tour;               // tour
    tour.push_back(star);           // tour = {a}
    while(!circuit)                 // tant que pas encore un circuit
    {
        star = -1;                  // si star = -1 dans la suite alors on a un circuit
                                    // pour la bloucle on va traiter seulement les sommets non visités
        for(int i=0; (unsigned int) i<tour.size(); i++)
        {
            if(!G->visiter(tour[i])) // si le sommet i n'a pas été visité
            {
                star = tour[i];     // star = id du sommet
                position = i;       // on recupère la position du sommet dans la tour
                break;              // on arrête la recherche sinon on continue
            }
        }
        if(star > -1)               // si star > -1 alors il reste des sommets non encore visité
        {
            int courant = star;     // courant = star
            vector<int> sous_tour;
            sous_tour.push_back(star); // sous-tour = {star}
            do
            {
                int u;                  // u = succ de courant
//                cout<<courant <<" ";
                vector<Arc*> ls = G->getSuccesseursArcs(courant);
                int nbArcTester = 1;
                for (vector<Arc*>::iterator it=ls.begin(); it!=ls.end(); ++it)
                {
                    if ( !(*it)->getEtat() ) // etat de mon arc. si non viter alors je visite
                    {
                        u = (*it)->getDestination()->getIds();
                        (*it)->setEtat(true); // marquer visité
                        break;                // on arrete sinon on continue la recherche
                    }
                    nbArcTester++;            // nombre d'arc traité
                }

                if((unsigned int) nbArcTester == ls.size()) // si tous les arcs de courant sont traité alors
                {
                    G->marquerSommet(courant);// le sommet courant est marquer comme traité
                }
                sous_tour.push_back(u);       // sous-tour = {star,u}
                courant = u;                  // courant = u
            }while(star != courant);          // tant que star != courant

            vector<int>::iterator it1;        // un itérateur
            it1 = tour.begin();               // on la positionne au début

            tour.insert (it1+position,sous_tour.begin(),sous_tour.end()); // inserer dans tour le sous circuit
            tour.erase (tour.begin()+position+sous_tour.size());          // supprime le surplus

            sous_tour.clear();                                            // vider sous_tour
        }
        else                                 // si star = -1 alors
        {
            circuit = true;                  // on a un circuit
        }
    }

    /* afficher le circuit dans interface */
    int suiv=0;
//    cout<<endl;
    int j;
    for(j=0; (unsigned int) j<tour.size()-1; j++)
    {
        suiv=j+1;
        G->getSommet(tour[j])->setColorB(255);
        //cout<<tour[j] <<" ";
        G->getArc(tour[j],tour[suiv])->setColorR(255);
        G->getArc(tour[j],tour[suiv])->setColorG(0);
        G->getArc(tour[j],tour[suiv])->setColorB(0);
        G->getArc(tour[j],tour[suiv])->setVal2(j+1);


        //cout<<"color arc"<<" "<<tour[j]<<" "<<tour[suiv]<< "= "<<G->getArc(tour[j],tour[suiv])->getColorR()<<" ";
    }//cout<<tour[suiv] ;
    //cout<<endl;

    /* afficher le circuit dans la console */
    /*cout<<endl;
    cout<<"Voici le circuit eulerien: ";
    for(int i=0; (unsigned int) i<tour.size(); i++)
    {
       cout<<tour[i] <<" ";
    }
    cout<<endl;*/

    return true;
}



void Date_plus_tot(Graphe *g, Sommet &s1,Sommet &s2)
{
    int i;

    for(i=0; i <g->getCompteurS();i++)
    {
        g->getSommet(i)->setVal1(-1);//S[i]=-1
    }

    g->getSommet(s1.getIds())->setVal1(0);//Date au plus tot sommet source=0
    double max = 0;

    for(i = 1;g->getSommet(s2.getIds())->getVal1()==-1; i++)
    {
        if( g->getSommet(i)->getVal1()==-1)
        {

            vector<Arc *> va= g->getPredecesseurArcs(i);
            max = 0;
            for(unsigned int j=0;j<va.size();j++)
            {

                if(va[j]->getOrigine()->getVal1()>-1)
                {
                    if(max == 0)
                    {
                        max = va[j]->getOrigine()->getVal1()+va[j]->getVal1();
                    }
                    else
                    {
                        max = Max(va[j]->getOrigine()->getVal1()+va[j]->getVal1(),max);
                    }
                }
            }
            g->getSommet(i)->setVal1(max);
        }
    }

}

void Date_plus_tard(Graphe *g, Sommet &s1,Sommet &s2)
{
    int i;

    for(i=g->getCompteurS()-1; i >=0 ;i--)
    {
        g->getSommet(i)->setVal2(10000000000000);//S[i]=+infini

    }

    g->getSommet(s2.getIds())->setVal2(g->getSommet(s2.getIds())->getVal1());//Date au plus tot sommet source=0

    double min = 0;

    for(i = g->getCompteurS()-2 ;g->getSommet(s1.getIds())->getVal2()==10000000000000; i--)
    {
        if( g->getSommet(i)->getVal2()==10000000000000)
        {

            vector<Arc *> va= g->getSuccesseursArcs(i);

            min = 10000000000000;

            for(unsigned int j=0;j<va.size();j++)
            {

                if(va[j]->getDestination()->getVal2()<10000000000000)
                {


                min = Min(va[j]->getDestination()->getVal2()-va[j]->getVal1(),min);


                }
            }
            g->getSommet(i)->setVal2(min);
        }
    }
}


void Marge_critique(Graphe *g, Sommet &s1, Sommet &s2)
{
    int i;
    double marge=0;
    int tmp=-1;
    for(i=g->getSommet(s1.getIds())->getIds();i<=g->getSommet(s2.getIds())->getIds();i++)
    {

        marge=g->getSommet(i)->getVal2()- g->getSommet(i)->getVal1();
        g->getSommet(i)->setVal3(marge);
        if(marge==0) {
            g->getSommet(i)->setColorR(169);
            g->getSommet(i)->setColorG(241);
            g->getSommet(i)->setColorB(23);
            if(tmp!=-1 && g->getArc(tmp,i)!=NULL) { g->getArc(tmp,i)->setColorR(169);
                         g->getArc(tmp,i)->setColorG(241);
                         g->getArc(tmp,i)->setColorB(23);
                       }
            tmp=i;
                            }
    }
}

void Pert(Graphe *g, Sommet &s1, Sommet &s2)
{
    g->initialiserCouleurArc();
    g->initialiserCouleurSommet();
    g->initialiserVal2Sommet();
    g->initialiserVal3Sommet();
    g->initialiserEtatArc();
    g->initialiserEtatSommet();
    g->initialiserVal2Arc();
    Date_plus_tot(g,s1,s2);
    Date_plus_tard(g,s1,s2);
    Marge_critique(g,s1,s2);
}

vector<int> parcours(Graphe* g, int v, bool visited[])
{
	vector<int> vect;// Marquer le sommet actuel comme visité et l'affiher
    vector<int> vect1;
    visited[v] = true;
    cout << v << " ";
    vect.push_back(v);
 
    //  récupère les sommets successeurs de v
    vector<Arc*> i = g->getSuccesseursArcs(v);
    for (vector<Arc*>::iterator it=i.begin(); it!=i.end(); ++it)
        if (!visited[(*it)->getDestination()->getIds()])
           vect1 = parcours(g, (*it)->getDestination()->getIds(), visited);
            

    vector<int>::iterator r;
    r= vect.begin();
    vect.insert(r+vect.size()-1,vect1.begin(),vect1.end());
    return vect;	
}

Graphe& ComposanteFortementConnexe(Graphe* G) //get inverse des arcs
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

void Tarjan(Graphe* g)
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
    Graphe gr = ComposanteFortementConnexe(g);
 
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
           vect =  parcours(&gr, v, visited);
           //cout << endl;
           for(int m=0;(unsigned int)m<vect.size(); m++)
           {
			   g->getSommet(vect[m])->setColorR((coul*180+200)%255);
			   g->getSommet(vect[m])->setColorG((coul*200+100)%255);
			   g->getSommet(vect[m])->setColorB((coul*52+50)%255);
	       //cout<<" "<<g->getSommet(vect[m])->getIds();
		   }
		   coul++; //incrémente couleur
        }
    }
}








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

    G->initialiserCouleurArc();
    G->initialiserCouleurSommet();
    G->initialiserVal2Sommet();
    G->initialiserVal3Sommet();
    G->initialiserEtatArc();
    G->initialiserEtatSommet();
    G->initialiserVal2Arc();

vector< vector< vector<int> > > feynman;
feynman.push_back(vector< vector<int> >());
feynman[0].push_back(vector<int>());
feynman[0][0].push_back(G->getTaille());
feynman[0][0].push_back(0);


for(int j=0; j<G->getTaille(); j++)
{
    //cout<<" 1er for et j "<<j<<endl;
    if(G->existeArc(0,j) && j != 0)
    {
        //cout<<" dans if j= "<<j<<endl;
        feynman.push_back(vector< vector<int> >());
        feynman[j].push_back(vector<int>());
       // cout<<" fin if1"<<endl;
        feynman[j][0].push_back(G->getTaille()-1);
        //cout<<" fin if2"<<endl;
        feynman[j][0].push_back(j);
        //cout<<" fin if3"<<endl;
        feynman[j][0].push_back(0);
        //cout<<" fin if4"<<endl;
    }
    else
    {
        //cout<<" dans else j= "<<j<<endl;
        feynman.push_back(vector< vector<int> >());
        feynman[j].push_back(vector<int>());
        feynman[j][0].push_back(0);
        feynman[j][0].push_back(j);
    }
}
cout<<"fin for"<<endl;  // ok


for(int k=0; k<pow(G->getTaille(),2); k++)
{
    //cout<<" 2em for"<<endl;
    for(int t=0; t<G->getTaille(); t++)
    {
        //cout<<" 3em for"<<endl;
        if(G->existeArc(k%G->getTaille(), t) && (k%G->getTaille()) != t)
        {
            for(int v=0; (unsigned int)v<feynman[k%G->getTaille()].size() && feynman[k%G->getTaille()][v].size() > 0; v++)
            {
                cout<<" taille "<<feynman[k%G->getTaille()].size();
                cout<<" 3em for et k "<<k<<" v "<<v<<" "<< feynman[k%G->getTaille()][v][0]<<endl;
                if(feynman[k%G->getTaille()][v][0] > 0)
                {
                    //cout<<" dans if"<<endl;
                    feynman[t].push_back(VecFeynman(t,feynman[k%G->getTaille()][v]));
                    //cout<<" fin if"<<endl;
                }
            }//cout<<" fin for4"<<endl;
        }
        if(!G->existeArc(k%G->getTaille(), t))
        {
            feynman[t]=feynman[t];
        }
    }//cout<<" fin for3"<<endl;

}//cout<<" fin for2"<<endl;  //ok

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
            //cout<<" if2 cycle 1"<<endl;
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
    if(!existe && l[j]<G->getTaille())
    {
        //cout<<" ok l[j] "<<l[j]<<endl;
        h.push_back(l[j]);
    }
}

if(h.size() != 0)
{
    //print h;
    cout<<" on a un circuit"<<endl;
    int tmp=-1;
    for(int r=h.size()-1;r>=0; r--)
    {
        //cout<<" "<<h[r];
        G->getSommet(h[r])->setColorR(255);
        G->getSommet(h[r])->setColorG(0);
        G->getSommet(h[r])->setColorB(0);

        if(tmp > -1 )
        {
            if(G->existeArc(tmp,h[r]))
            {
                G->getArc(tmp,h[r])->setColorR(255);
                G->getArc(tmp,h[r])->setColorG(0);
                G->getArc(tmp,h[r])->setColorB(0);
            }
            else
            {
                if(G->existeArc(h[r], tmp))
                {   G->getArc(h[r], tmp)->setColorR(255);
                    G->getArc(h[r], tmp)->setColorG(0);
                    G->getArc(h[r], tmp)->setColorB(0);
                }
            }
        }
        tmp=h[r];

    }//cout<<" tmp "<<tmp<<" h[r] "<<h[h.size()-1]<<endl;
    if(G->existeArc(tmp,h[h.size()-1]))
    {
        G->getArc(tmp,h[h.size()-1])->setColorR(255);
        G->getArc(tmp,h[h.size()-1])->setColorG(0);
        G->getArc(tmp,h[h.size()-1])->setColorB(0);
    }
    else if(G->existeArc(h[h.size()-1],tmp))
    {
        G->getArc(h[h.size()-1],tmp)->setColorR(255);
        G->getArc(h[h.size()-1],tmp)->setColorG(0);
        G->getArc(h[h.size()-1],tmp)->setColorB(0);
    }
}
else
{
    cout<<" on a pas de circuit"<<endl;
}

}









