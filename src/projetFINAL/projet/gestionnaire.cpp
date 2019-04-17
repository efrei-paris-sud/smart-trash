#include "gestionnaire.h"

string supprimerEspace(string nom){
    while(nom.find(" ") != std::string::npos){
        size_t found = nom.find(" ");
        nom.replace(found,1, "%");
    }
    return nom;
}

string ajouterEspace(string nom){
    while(nom.find("%") != std::string::npos){
        size_t found = nom.find("%");
        nom.replace(found,1, " ");
    }
    return nom;
}


//fonction pour sauvegarder un travail
bool sauvegarder(string fichier, Graphe *gr){
//necessite en entrée le nom du fichier ou l'on va sauvegarder et la liste des Graphes instancies
    //int i, j;
    ofstream fic(fichier.c_str(), ios::out | ios::trunc); //ouverture du fichier en mode ecriture

    if(fic){ //si le fichier est ouvert correctement

        vector<Sommet*> ls = gr->getLSommets();

        fic<<"gr "<<gr->getIdg()<<" "<<supprimerEspace(gr->getNom()); //ecrit "gr" puis les attributs d'un Graphe (id, nom).

        for(int nbSommets = 0; nbSommets < (int)ls.size(); nbSommets++){

            fic<<"\nsm "<<ls[nbSommets]->getIds()<<" "<<supprimerEspace(ls[nbSommets]->getNom())<<" "<<//ecrit "sm" puis les attributs d'un Sommet
            ls[nbSommets]->getTypeReel()<<" "<<ls[nbSommets]->getVal1()<<" "<<ls[nbSommets]->getVal2()<<" "<<//(id, nom, type, valeurs
            ls[nbSommets]->getVal3()<<" "<<ls[nbSommets]->getAbscisse()<<" "<<ls[nbSommets]->getOrdonnee();//et coordonnees du centre du Sommet).
        }
        for(int i = 0; i < (int)ls.size(); i++){
            for(int j = 0; j < (int)ls.size(); j++){
                if(gr->existeArc(i, j) && gr->getArc(i, j) != NULL){
                    fic<<"\nar "<<gr->getArc(i, j)->getIda()<<" "<<supprimerEspace(gr->getArc(i, j)->getNom())<<" "<<
                    gr->getArc(i, j)->getTypeReel()<<" "<<gr->getArc(i, j)->getVal1()<<" "<<gr->getArc(i, j)->getVal2()<<
                    " "<<gr->getArc(i, j)->getOrigine()->getIds()<<" "<<gr->getArc(i, j)->getDestination()->getIds();
                }
            }
        }

        fic.close(); //fermeture du fichier
        return true;
    }

    else{ //si le fichier ne s'est pas ouvert correctement
        cerr<<"Impossible d'ouvrir le fichier "<<fichier<<" !"<<endl;
        fic.close(); //fermeture du fichier
        return  false;
    }
}

Graphe* charger(string fichier){

    ifstream fic(fichier.c_str(), ios::in); //ouverture du fichier en mode lecture

    string mot;

    if(fic){ //si le fichier est ouvert correctement

        int idgr, idsm, idar, ido, ida;
        string nomgr, nomsm, nomar;
        bool typesm, typear;
        double valsm[3], valar[2], x, y;

        Point p;

        fic >> mot >> idgr >> nomgr;
        //instanciation du nouveau Graphe et ajout a la liste des Graphes
        Graphe *tmpgr = new Graphe(idgr, ajouterEspace(nomgr));
        while(fic >> mot){
            if(mot == "sm"){
                fic >> idsm >> nomsm >> typesm >> valsm[0] >> valsm[1] >> valsm[2] >> x >> y;
                //instancition du nouveau Sommet et ajout du Sommet au Graphe correspondant
                p._abs = x;
                p._ord = y;
                tmpgr->ajouterSommet(ajouterEspace(nomsm), idsm, typesm, valsm, p);
            }
            if(mot == "ar"){
                fic >> idar >> nomar >> typear >> valar[0] >> valar[1] >> ido >> ida;
                //instanciation du nouvel Arc et ajout de l'Arc a la liste des Graphes
                tmpgr->ajouterArc(ajouterEspace(nomar), idar, typear, valar, ido, ida);
            }
        }

        fic.close(); //fermeture du fichier
        return tmpgr;
    }
    cerr<<"Impossible d'ouvrir le fichier "<<fichier<<" !"<<endl;
    Graphe *gr = new Graphe();
    return gr;
}
