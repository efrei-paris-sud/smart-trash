#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QAction>
#include <QIcon>
#include "qgraphe.h"
#include <QMdiArea>
#include <QMessageBox>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QtGui>
#include <QFileDialog>
#include <QPixmap>
#include "iostream"
#include "gestionnaire.h"
#include <QTabWidget>
#include "onglet.h"
#include "algorithme.h"
#include <QTableWidget>

class Interface : public QMainWindow//Classe Interface
{
    Q_OBJECT

private:
    QAction *actionNouveau;
    QAction *actionSauvegarde;
    QAction *actionExporter;
    QAction *actionOuvrir;
    QAction *actionQuitter;
    QAction *actionInfosAlgos;
    QAction *actionAide;
    QAction *actionTheme;

    QAction *actionNomSommets;
    QAction *actionValeurSommets;
    QAction *actionNomArcs;
    QAction *actionValeurArcs;

    QMessageBox *erreur;
    QPushButton *plus;//Attribut plus (Zoom)
    QPushButton *moins;//Attribut moins (Dezoom)

    QPushButton *supprimer_sommet;//Attribut supprimer_sommet
    QPushButton *supprimer_arc;//Attribut supprimer_arc

    QPushButton *extraire_sgp;//Attribut extraire_sgp
    QPushButton *supprimer_tout;//Attribut supprimer_tout
    QPushButton *mat_info;//Attribut mat_info
    QPushButton *definir_sgp;//Attribut definir_sgp

    QPushButton *centrer;//Attribut centrer
    QPushButton *bouton_selection_simple;//Attribut selection_simple
    QPushButton *bouton_selection_multiple;//Attribut selection_multiple
    QPushButton *bouton_suppression_multiple;//Attribut bouton_supprimer_arcs_ou_sommets

    QPushButton *add_sommets;//Attribut Ajout Sommets
    QPushButton *add_arcs;//Attribut Ajout Arcs
    QComboBox *liste_procedures;//Attribut liste_procedures
    QLabel *procedures;//Attribut procedures

    QTabWidget *tab;

    QWidget *bouton_algo_ajout_widget;//Attribut bouton_algo_ajout_widget
    QDockWidget *f_algo;//Attribut f_graphe (Fenêtre Algo)
    QGridLayout *bouton_algo_ajout;//Attribut bouton_algo_ajout

    QWidget *info_sommet_widget;//Attribut info_sommet_widget
    QGridLayout *info_sommet;//Attribut info_sommet

    QLabel *nom_sommet;//Attribut nom_sommet
    QLabel *valeur_sommet;//Attribut valeur_sommet
    QLabel *id_sommet;//Attribut id_sommet
    QLabel *d_plus_sommet;//Attribut d_plus_sommet (Degré Sortant)
    QLabel *d_moins_sommet;//Attribut d_moins_sommet (Degré Entrant)
    QLabel *d_total_sommet;//Attribut d_total

    QWidget *info_arc_widget;//Attribut info_arc_widget
    QGridLayout *info_arc;//Attribut info_arc

    QLabel *nom_arc;//Attribut nom_arc
    QLabel *valeur_arc;//Attribut valeur_arc
    QLabel *sommet_origine;//Attribut sommet_origine
    QLabel *sommet_arrive;//Attribut sommet_arrive
    QLabel *id_arc;//Attribut id_arc

    QWidget *info_graphe_widget;//Attribut info_graphe_widget
    QGridLayout *info_graphe;//Attribut info_graphe

    QLabel *nombre_sommets;//Attribut nombre_sommets
    QLabel *nombre_arcs;//Attribut nombre_arcs
    QLabel *nom_graphe;//Attribut nom_graphe
    QLabel *type_graphe;//Attribut id_graphe

    QTableWidget* tab_matrice=NULL;
    QStringList   tete_matrice;

private slots:

    void choix_new();//Fonction Nouveau Fichier A FAIRE
    QString chemin_ouverture();//Fonction pour choisir le chemin et le nom du fichier a ouvrir
    QString chemin_sauvegarde();//Fonction pour choisir le chemin et le nom du fichier a sauvegarder
    QString chemin_export();//Fonction pour choisir le chemin et le nom du fichier a exporter
    void choix_open();//Fonction Ouvrir Fichier A FAIRE
    void choix_save();//Fonction Sauvegarde Fichier A FAIRE
    void choix_export();//Fonction Exporter Fichier A FAIRE
    void affiche_noms_sommets();//Fonction Affiche Noms Sommets A FAIRE
    void affiche_noms_arcs();//Fonction Affiche Noms Arcs A FAIRE
    void affiche_valeurs_arcs();//Fonction Affiche Valeurs Arcs A FAIRE
    void affiche_matrice();
    void fenetre_infos_algos();//Fonction Affichage Des Infos Pour Les Algos
    void affiche_valeurs_sommets();
    void fenetre_aide();
    void cacher_fenetre();
    void fermer_onglet(int index);
    void deconnexion_boutton(int index);
    void zoom();//Fonction De Zoom +
    void dezoom();//Fonction De Zoom -
    void changer_nom_onglet(QString);
    void affichage_dijkstra(int i);
    void affichage_flot(int i);
    void affichage_connexe(int i);
    void affichage_euler(int i);
    void affichage_pert(int i);
    void affichage_ford(int i);
    void affichage_pronfondeur(int i);
    void affichage_largeur(int i);
    void affichage_fortement(int i);
    void affichage_hamiltonien(int i);
    void choix_definir_sgp();
    void choix_extraire_sgp();
    void choix_centrer();
    void theme();
    void reinitialise_graphe(int i);

public:

    Interface(QWidget *parent = 0,Qt::WindowFlags fl = Qt::Window);//Constructeur
    virtual ~Interface();//Destructeur
    void creerMenu();//Fonction Initialisation Du Menu
    void creerAction();//Fonction Initialisation Des Actions
    void creerOutils();//Fonction Initialisation Des Outils
    void fenetre_sommet();//Fonction Affichage De la Fenêtre Information Sommets
    void fenetre_arc();//Fonction Affichage De la Fenêtre Information Arcs
    void fenetre_graphe();//Fonction Affichage De la Fenêtre Information Graphes
    void fenetre_ajout_algo();//Fonction Affichage De la Fenêtre Ajout/Algo
    void fenetre_dessin();//Fonction Fenêtre De Visualisation
    void connexion_boutons();
    void debut_affichage_algo(int i);
    void fin_affichage_algo(int i);
    void message(QString titre, QString text);
    void fenetre_onglet();
};

#endif // INTERFACE_H
