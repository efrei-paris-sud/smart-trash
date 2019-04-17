#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "arc.h"
#include "sommet.h"
#include "graphe.h"

using namespace std;

string supprimerEspace(string nom);

string ajouterEspace(string nom);

bool sauvegarder(string fichier, Graphe *gr);//fonction pour sauvegarder un travail
//necessite en entrée l'emplacement du fichier ou l'on va sauvegarder et la liste des graphes instancies.

Graphe* charger(string fichier);//fonction pour lire toutes les lignes du fichier
//et instancier les sommets, arcs et/ou graphes ecrit.

#endif
