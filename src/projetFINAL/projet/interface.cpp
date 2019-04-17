#include "interface.h"

Interface::Interface(QWidget *parent, Qt::WindowFlags fl): QMainWindow(parent,fl)//Constructeur
{
    fenetre_onglet();
    fenetre_dessin();//Fonction Fenetre Dessin
    creerAction();//Fonction Init Action
    creerMenu();//Fonction Init Menu
    creerOutils();//Fonction Init Outils

    fenetre_sommet();//Fonction Fenetre Sommet
    fenetre_arc();//Fonction Fenetre Arc
    fenetre_graphe();//Fonction Fenetre Graphe
    fenetre_ajout_algo();//Fonction Fenetre Algo

    connexion_boutons();
    setWindowTitle("Manipulation De Graphes Orientés Et De Sous Graphe Partiels");//Titre De La Fenêtre
//  setMinimumSize(QSize(900,700));//Taille Minimum
    connect(tab, SIGNAL(tabCloseRequested(int)), this, SLOT(fermer_onglet(int)));
    connect(tab, SIGNAL(currentChanged(int)),this,SLOT(cacher_fenetre()));
    showMaximized();//Plein Ecran
//    theme();
}

void Interface::creerAction()
{
    actionNouveau = new QAction(QIcon("../images/new.png"),"&Nouveau",this);
    actionOuvrir = new QAction(QIcon("../images/open.png"),"&Ouvrir",this);
    actionSauvegarde = new QAction(QIcon("../images/save.png"),"&Sauvegarder",this);
    actionExporter = new QAction(QIcon("../images/export.png"),"&Exporter",this);
    actionQuitter = new QAction(QIcon("../images/quit.png"),"&Quitter",this);

    actionNomSommets = new QAction("&Nom Sommets",this);
    actionValeurSommets = new QAction("&Valeur Sommets",this);
    actionNomArcs = new QAction("&Nom Arcs",this);
    actionValeurArcs = new QAction("&Valeur Arcs",this);
    actionInfosAlgos = new QAction("&Informations Algos",this);
    actionAide = new QAction("&Aide",this);
    actionTheme = new QAction("&Theme",this);


    actionNouveau->setShortcut(QKeySequence("Ctrl+N"));
    actionOuvrir->setShortcut(QKeySequence("Ctrl+O"));
    actionSauvegarde->setShortcut(QKeySequence("Ctrl+S"));
    actionExporter->setShortcut(QKeySequence("Ctrl+E"));
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

}

void Interface::creerMenu()
{
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");

    menuFichier->addAction(actionNouveau);//  Ajoute une option "Nouveau"
    menuFichier->addAction(actionOuvrir);//  Ajoute une option "Ouvrir"
    menuFichier->addAction(actionSauvegarde);// Ajoute une option "Sauvegarder"
    menuFichier->addAction(actionExporter);// Ajoute une option "Exporter"
    menuFichier->addSeparator();// Ajoute un séparateur
    menuFichier->addAction(actionQuitter);// Ajoute une Option "Quitter"

    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");

    menuAffichage->addAction(actionNomSommets);//  Ajoute une option "Nom Sommets"
    menuAffichage->addAction(actionValeurSommets);//  Ajoute une option "Valeur Sommets"
    menuAffichage->addAction(actionNomArcs);//  Ajoute une option "Nom Arcs"
    menuAffichage->addAction(actionValeurArcs);//  Ajoute une option "Valeur Arcs"
    menuAffichage->addAction(actionInfosAlgos);//  Ajoute une option "Valeur Arcs"
    menuAffichage->addAction(actionAide);//  Ajoute une option "Valeur Arcs"
    menuAffichage->addAction(actionTheme);//  Ajoute une option "Valeur Arcs"

    actionNomSommets->setCheckable(true);
    actionValeurSommets->setCheckable(true);
    actionNomArcs->setCheckable(true);
    actionValeurArcs->setCheckable(true);
    actionTheme->setCheckable(true);

    connect(actionAide, SIGNAL(triggered()),this, SLOT(fenetre_aide()));
    connect(actionInfosAlgos, SIGNAL(triggered()),this, SLOT(fenetre_infos_algos()));
    connect(actionQuitter, SIGNAL(triggered()),qApp, SLOT(quit()));
    connect(actionSauvegarde, SIGNAL(triggered()), this, SLOT(choix_save()));
    connect(actionOuvrir, SIGNAL(triggered()), this, SLOT(choix_open()));
    connect(actionExporter, SIGNAL(triggered()), this, SLOT(choix_export()));
    connect(actionNouveau, SIGNAL(triggered()), this, SLOT(choix_new()));
    connect(actionTheme, SIGNAL(triggered()), this, SLOT(theme()));


}

void Interface::creerOutils()//Fonction Initialisation Des Outils
{
      QToolBar* barre_outils;

      barre_outils = addToolBar("Barre D'outils"); // Creation de la barre de menu
      barre_outils->setMovable(false); // Ne peut etre deplacer
      barre_outils->addAction(actionNouveau); // Ajoute option "Nouveau"
      barre_outils->addAction(actionOuvrir); // Ajoute option "Ouvrir"
      barre_outils->addAction(actionSauvegarde); // Ajoute option "Sauvegarder"
      barre_outils->addAction(actionExporter); // Ajoute option "Exporter"

      plus=new QPushButton(QIcon("../images/plus.png"),"",barre_outils);//Création Du Bouton +
      plus->setGeometry(600,10,50,25);//Positionnement Et Taille Du Bouton +
      plus->setIconSize(QSize(50,20));//Taille Icone
      plus->setToolTip("Zoom +");
      plus->show();//Affichage Du Bouton +

      moins=new QPushButton(QIcon("../images/moins.png"),"",barre_outils);//Création Du Bouton -
      moins->setGeometry(650,10,50,25);//Positionnement Et Taille Du Bouton -
      moins->setIconSize(QSize(50,20));//Taille Icone
      moins->setToolTip("Zoom -");
      moins->show();//Affichage Du Bouton -

      centrer=new QPushButton(QIcon("../images/center.png"),"",barre_outils);//Création Du Bouton Centrer
      centrer->setGeometry(700,10,50,25);//Positionnement Et Taille Du Bouton Centrer
      centrer->setIconSize(QSize(50,20));//Taille Icone
      centrer->setToolTip("Centrer");
      centrer->show();//Affichage Du Bouton Centrer

      bouton_selection_simple=new QPushButton(QIcon("../images/select_simple.png"),"",barre_outils);//Création Du Bouton Selection Simple
      bouton_selection_simple->setGeometry(750,10,50,25);//Positionnement Et Taille Du Bouton Selection Simple
      bouton_selection_simple->setIconSize(QSize(50,20));//Taille Icone
      bouton_selection_simple->setToolTip("Selection Simple");
      bouton_selection_simple->show();//Affichage Du Bouton Selection Simple

      bouton_selection_multiple=new QPushButton(QIcon("../images/select_mult.png"),"",barre_outils);//Création Du Bouton Selection Multiple
      bouton_selection_multiple->setGeometry(800,10,50,25);//Positionnement Et Taille Du Bouton Selection Multiple
      bouton_selection_multiple->setIconSize(QSize(50,20));//Taille Icone
      bouton_selection_multiple->setToolTip("Selection Multiple");
      bouton_selection_multiple->show();//Affichage Du Bouton Selection Multiple

      bouton_suppression_multiple = new QPushButton(QIcon("../images/suppr.png"),"",barre_outils);//Création Du Bouton Suppression Multiple
      bouton_suppression_multiple->setGeometry(850,10,50,25);//Positionnement Et Taille Du Bouton Suppression Multiple
      bouton_suppression_multiple->setIconSize(QSize(50,20));//Taille Icone
      bouton_suppression_multiple->setToolTip("Suppression Multiple");
      bouton_suppression_multiple->show();//Affichage Du Bouton Suppression Multiple

      connect(plus, SIGNAL(released()), this, SLOT(zoom()));//Initialisation Bouton Zoom +
      connect(moins, SIGNAL(released()), this, SLOT(dezoom()));//Initialisation Bouton Zoom -
}

void Interface::fenetre_dessin()//Fonction Fenêtre De Visualisation
{
    onglet *graph=new onglet();
    graph->scene->f_graphe=new QDockWidget(tr("Informations Graphes"),this);//Creation De La Fenêtre en tant que Widget
    graph->scene->f_sommet=new QDockWidget(tr("Informations Graphes"),this);//Creation De La Fenêtre en tant que Widget
    graph->scene->f_arc=new QDockWidget(tr("Informations Graphes"),this);//Creation De La Fenêtre en tant que Widget
    tab->addTab(graph,QString::fromStdString(graph->scene->getGraph()->getNom()));
    tab->setCurrentWidget(graph);
}

void Interface::connexion_boutons()
{
    if(!tab->count()) {message("QGraph","Créer un nouveau graph"); return;}
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    connect(this->bouton_selection_simple, SIGNAL(released()),p->scene, SLOT(deplacer()));
    connect(this->bouton_selection_multiple, SIGNAL(released()), p->scene, SLOT(selectionner()));
    connect(this->add_arcs, SIGNAL(released()), p->scene, SLOT(arc_ajouter()));
    connect(this->bouton_suppression_multiple, SIGNAL(released()), p->scene, SLOT(supprimer()));
    connect(this->add_sommets, SIGNAL(released()), p->scene, SLOT(sommet_ajouter()));
    connect(this->supprimer_tout, SIGNAL(released()), p->scene, SLOT(supprimertout()));
    connect(p->scene->nom_sommet_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setNomSommet(QString)));

    connect(this->actionNomSommets, SIGNAL(triggered()), this, SLOT(affiche_noms_sommets()));
    connect(this->actionValeurSommets, SIGNAL(triggered()), this, SLOT(affiche_valeurs_sommets()));
    connect(this->actionNomArcs, SIGNAL(triggered()), this, SLOT(affiche_noms_arcs()));
    connect(this->actionValeurArcs, SIGNAL(triggered()), this, SLOT(affiche_valeurs_arcs()));

    connect(this->actionNomSommets, SIGNAL(triggered(bool)),p->scene, SLOT(setAffiche_nom_sommet(bool)));
    connect(this->actionValeurSommets, SIGNAL(triggered(bool)), p->scene, SLOT(setAffiche_val_sommet(bool)));
    connect(this->actionNomArcs, SIGNAL(triggered(bool)), p->scene, SLOT(setAffiche_nom_arc(bool)));
    connect(this->actionValeurArcs, SIGNAL(triggered(bool)), p->scene, SLOT(setAffiche_val_arc(bool)));

    connect(this->mat_info, SIGNAL(released()), this, SLOT(affiche_matrice()));
    connect(supprimer_sommet, SIGNAL(released()),p->scene, SLOT(supprimer()));
    connect(supprimer_arc, SIGNAL(released()),p->scene, SLOT(supprimer()));
    connect(p->scene->valeur_sommet_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setValSommet(QString)));
    connect(p->scene->nom_arc_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setNomArc(QString)));
    connect(p->scene->valeur_arc_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setValArc(QString)));
    connect(p->scene->nom_graphe_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setNomGraphe(QString)));
    connect(p->scene->nom_graphe_val, SIGNAL(textChanged(QString)),this, SLOT(changer_nom_onglet(QString)));
    connect(p->scene->type_graphe_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setTypeGraphe(QString)));
    connect(this->extraire_sgp, SIGNAL(released()),this,SLOT(choix_extraire_sgp()));
    connect(this->definir_sgp, SIGNAL(released()),this,SLOT(choix_definir_sgp()));
    connect(this->centrer, SIGNAL(released()),this,SLOT(choix_centrer()));

}


void Interface::cacher_fenetre()
{
    if(!tab->count()) {message("QGraph","Aucun graphe"); return;}
    onglet *p;
    for(int i=0;i <tab->count();i++){
    qDebug()<<"onglet actuel ="<<tab->currentIndex();
    p=  static_cast<onglet *> (tab->widget(i));
    p->scene->f_graphe->setVisible(0);
    p->scene-> f_sommet->setVisible(0);
    p->scene-> f_arc->setVisible(0);
    update();
    }
}


void Interface::choix_new()
{
    this->removeDockWidget(f_algo);
    fenetre_dessin();
    fenetre_sommet();//Fonction Fenetre Sommet
    fenetre_arc();//Fonction Fenetre Arc
    fenetre_graphe();//Fonction Fenetre Graphe
    this->addDockWidget(Qt::LeftDockWidgetArea,f_algo);
    f_algo->setVisible(1);
    connexion_boutons();
    cacher_fenetre();
    actionNomSommets->setChecked(false);
    actionValeurSommets->setChecked(false);
    actionNomArcs->setChecked(false);
    actionValeurArcs->setChecked(false);
    qDebug()<<"onglet crée avec id ="<<tab->currentIndex();
}

void Interface::fermer_onglet(int index)
{
    cacher_fenetre();
    deconnexion_boutton(index);
    qDebug()<<"detruire tab ="<<index;
    tab->removeTab(index);
}

void Interface::deconnexion_boutton(int index)
{
    qDebug()<<"deconnecter onglet id="<<index;
    onglet *p=  static_cast<onglet *> (tab->widget(index));
    QObject::disconnect(this->bouton_selection_simple, SIGNAL(released()),p->scene, SLOT(deplacer()));
    QObject::disconnect(this->bouton_selection_multiple, SIGNAL(released()), p->scene, SLOT(selectionner()));
    QObject::disconnect(this->add_arcs, SIGNAL(released()), p->scene, SLOT(arc_ajouter()));
    QObject::disconnect(this->bouton_suppression_multiple, SIGNAL(released()), p->scene, SLOT(supprimer()));
    QObject::disconnect(this->add_sommets, SIGNAL(released()), p->scene, SLOT(sommet_ajouter()));
    QObject::disconnect(this->supprimer_tout, SIGNAL(released()), p->scene, SLOT(supprimertout()));
    QObject::disconnect(p->scene->nom_sommet_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setNomSommet(QString)));
    disconnect(this->actionNomSommets, SIGNAL(triggered()), this, SLOT(affiche_noms_sommets()));
    disconnect(this->actionValeurSommets, SIGNAL(triggered()), this, SLOT(affiche_valeurs_sommets()));
    disconnect(this->actionNomArcs, SIGNAL(triggered()), this, SLOT(affiche_noms_arcs()));
    disconnect(this->actionValeurArcs, SIGNAL(triggered()), this, SLOT(affiche_valeurs_arcs()));
    disconnect(this->mat_info, SIGNAL(released()), this, SLOT(affiche_matrice()));
    QObject::disconnect(supprimer_sommet, SIGNAL(released()),p->scene, SLOT(supprimerQSommet()));
    QObject::disconnect(supprimer_arc, SIGNAL(released()),p->scene, SLOT(supprimerQSommet()));
    QObject::disconnect(p->scene->valeur_sommet_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setValSommet(QString)));
    QObject::disconnect(p->scene->nom_arc_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setNomArc(QString)));
    QObject::disconnect(p->scene->valeur_arc_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setValArc(QString)));

    disconnect(this->actionNomSommets, SIGNAL(triggered(bool)),p->scene, SLOT(setAffiche_nom_sommet(bool)));
    disconnect(this->actionValeurSommets, SIGNAL(triggered()), p->scene, SLOT(setAffiche_val_sommet(bool)));
    disconnect(this->actionNomArcs, SIGNAL(triggered()), p->scene, SLOT(setAffiche_nom_arc(bool)));
    disconnect(this->actionValeurArcs, SIGNAL(triggered()), p->scene, SLOT(setAffiche_val_arc(bool)));
    QObject::disconnect(p->scene->nom_graphe_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setNomGraphe(QString)));
    QObject::disconnect(p->scene->nom_graphe_val, SIGNAL(textChanged(QString)),this, SLOT(changer_nom_onglet(QString)));
    QObject::disconnect(p->scene->type_graphe_val, SIGNAL(textChanged(QString)),p->scene, SLOT(setTypeGraphe(QString)));
//    disconnect(tab, SIGNAL(currentChanged(int)),this,SLOT(cacher_fenetre()));

}

void Interface::fenetre_sommet()//Fonction Affichage De la Fenêtre Information Sommets
{
    if(!tab->count()) {message("QGraph","Créer un nouveau graphe"); return;}
    onglet *p=  static_cast<onglet *> (tab->currentWidget());

    p->scene->f_sommet=new QDockWidget(tr("Informations Sommets"),this);//Creation De La Fenêtre en tant que Widget
//    p->scene->f_sommet->setAllowedAreas(Qt::LeftDockWidgetArea);//Positionnement A Gauche De L'ecran
    p->scene->f_sommet->setMaximumWidth(400);//Taille Max X 400
    p->scene->f_sommet->setMaximumHeight(220);//Taille Max Y 220
    p->scene->f_sommet->setMinimumWidth(400);//Taille Max X 400
    p->scene->f_sommet->setMinimumHeight(220);//Taille Max Y 220
    p->scene->f_sommet->setVisible(0);//Fenetre Non Visible Par Defaut

    info_sommet_widget=new QWidget();//Creation Widget fenetre Information Sommets

    nom_sommet = new QLabel("Nom:"); // Creation Label Nom
    valeur_sommet = new QLabel("Valeur:");// Creation Label Valeur
    id_sommet = new QLabel("ID:");// Creation Label ID Sommet
    d_plus_sommet = new QLabel("Degré Sortant:");// Creation Label Degré Sortant
    d_moins_sommet = new QLabel("Degré Entrant:");// Creation Label Degré Entrant
    d_total_sommet = new QLabel("Degré Total:");// Creation Label Degré Total

    p->scene-> nom_sommet_val=new QLineEdit();// Creation Champs Nom
    p->scene-> valeur_sommet_val = new QLineEdit();// Creation Champs Valeur
    p->scene-> id_sommet_val = new QLineEdit();// Creation Champs ID Sommet
    p->scene-> id_sommet_val->setReadOnly(true);
    p->scene-> d_plus_sommet_val = new QLineEdit();// Creation Champs Degré Sortant
    p->scene-> d_plus_sommet_val->setReadOnly(true);
    p->scene-> d_moins_sommet_val = new QLineEdit();// Creation Champs Degré Entrant
    p->scene-> d_moins_sommet_val->setReadOnly(true);
    p->scene-> d_total_sommet_val = new QLineEdit();//Creation Champs Degré Total
    p->scene-> d_total_sommet_val->setReadOnly(true);

    supprimer_sommet = new QPushButton("Supprimer");// Creation Bouton Supprimer

    info_sommet = new QGridLayout;// Creation Grille Organisation
    info_sommet->addWidget(nom_sommet, 0, 0);// Ajout Label Nom
    info_sommet->addWidget(p->scene->nom_sommet_val, 0, 1);// Ajout Champs Nom
    info_sommet->addWidget(valeur_sommet, 1, 0);// Ajout Label Valeur
    info_sommet->addWidget(p->scene->valeur_sommet_val, 1, 1);// Ajout Champs Valeur
    info_sommet->addWidget(id_sommet, 2, 0);// Ajout Label ID
    info_sommet->addWidget(p->scene->id_sommet_val, 2, 1);// Ajout Champs ID
    info_sommet->addWidget(d_plus_sommet, 0, 2);// Ajout Label Degré Sortant
    info_sommet->addWidget(p->scene->d_plus_sommet_val, 0, 3);// Ajout Champs Degré Sortant
    info_sommet->addWidget(d_moins_sommet, 1, 2);// Ajout Label Degré Entrant
    info_sommet->addWidget(p->scene->d_moins_sommet_val, 1, 3);// Ajout Champs Degré Entrant
    info_sommet->addWidget(d_total_sommet, 2, 2);// Ajout Label Degré Total
    info_sommet->addWidget(p->scene->d_total_sommet_val, 2, 3);// Ajout Label Degré Total
    info_sommet->addWidget(supprimer_sommet, 3, 2);// Ajout Supprimer
    info_sommet_widget->setLayout(info_sommet);// Appliquer la grille a la fenêtre

    p->scene->f_sommet->setWidget(info_sommet_widget);//Appliquer l'eensemble a la fenêtre incrusté
    addDockWidget(Qt::LeftDockWidgetArea,  p->scene->f_sommet);//Ajout De la fenêtre
}

void Interface::fenetre_arc()//Fonction Affichage De la Fenêtre Information Arcs
{
    if(!tab->count()) {message("QGraph","Créer un nouveau graphe"); return;}
    onglet *p=  static_cast<onglet *> (tab->currentWidget());

     p->scene->f_arc=new QDockWidget(tr("Informations Arcs"),this);//Creation De La Fenêtre en tant que Widget
//    p->scene->f_arc->setAllowedAreas(Qt::LeftDockWidgetArea);//Positionnement A Gauche De L'ecran
    p->scene->f_arc->setMaximumWidth(400);//Taille Max X 400
     p->scene->f_arc->setMaximumHeight(220);//Taille Max Y 220
     p->scene->f_arc->setMinimumWidth(400);//Taille Max X 400
    p->scene->f_arc->setMinimumHeight(220);//Taille Max Y 220
     p->scene->f_arc->setVisible(0);//Fenetre Non Visible Par Defaut

    info_arc_widget=new QWidget();

    nom_arc = new QLabel("Nom:");
    valeur_arc = new QLabel("Valeur:");
    sommet_origine = new QLabel("Sommet Origine:");
    sommet_arrive = new QLabel("Sommet Arrivé:");
    id_arc = new QLabel("ID:");

    p->scene->nom_arc_val = new QLineEdit();
    p->scene->valeur_arc_val = new QLineEdit();
    p->scene->sommet_origine_val = new QLineEdit();
    p->scene->sommet_origine_val->setReadOnly(true);
    p->scene->sommet_arrive_val = new QLineEdit();
    p->scene->sommet_arrive_val->setReadOnly(true);
    p->scene->id_arc_val = new QLineEdit();
    p->scene->id_arc_val->setReadOnly(true);

    supprimer_arc = new QPushButton("Supprimer");

    info_arc = new QGridLayout;
    info_arc->addWidget(nom_arc, 0, 0);
    info_arc->addWidget(p->scene->nom_arc_val, 0, 1);
    info_arc->addWidget(valeur_arc, 1, 0);
    info_arc->addWidget(p->scene->valeur_arc_val, 1, 1);
    info_arc->addWidget(sommet_origine, 0, 2);
    info_arc->addWidget(p->scene->sommet_origine_val, 0, 3);
    info_arc->addWidget(sommet_arrive, 1, 2);
    info_arc->addWidget(p->scene->sommet_arrive_val, 1, 3);
    info_arc->addWidget(id_arc, 2, 0);
    info_arc->addWidget(p->scene->id_arc_val, 2, 1);
    info_arc->addWidget(supprimer_arc, 3, 2);
    info_arc_widget->setLayout(info_arc);

    p->scene->f_arc->setWidget(info_arc_widget);
    addDockWidget(Qt::LeftDockWidgetArea, p->scene->f_arc);
}

void Interface::fenetre_graphe()//Fonction Affichage De la Fenêtre Information Graphe
{
    if(!tab->count()) {message("QGraph","Créer un nouveau graphe"); return;}
    onglet *p=  static_cast<onglet *> (tab->currentWidget());

      p->scene->f_graphe=new QDockWidget(tr("Informations Graphes"),this);//Creation De La Fenêtre en tant que Widget
//        p->scene->f_graphe->setAllowedAreas(Qt::LeftDockWidgetArea);//Positionnement A Gauche De L'ecran
     p->scene-> f_graphe->setMaximumWidth(400);//Taille Max X 400
       p->scene-> f_graphe->setMaximumHeight(220);//Taille Max Y 220
       p->scene->f_graphe->setMinimumWidth(400);//Taille Max X 400
      p->scene-> f_graphe->setMinimumHeight(220);//Taille Max Y 220
     p->scene-> f_graphe->setVisible(0);//Fenetre Non Visible Par Defaut

    info_graphe_widget=new QWidget();

    nombre_sommets = new QLabel("Nombre Sommets:");
    nombre_arcs = new QLabel("Nombre Arcs:");
    nom_graphe = new QLabel("Nom:");
    type_graphe = new QLabel("Type:");

    extraire_sgp = new QPushButton("Extraire SGP");
    supprimer_tout = new QPushButton("Supprimer Tout");
    mat_info = new QPushButton("Matrice");
    definir_sgp = new QPushButton("Definir SGP");
    info_graphe = new QGridLayout;

    p->scene->nombre_sommets_val = new QLineEdit();
    p->scene->nombre_sommets_val->setReadOnly(true);
    p->scene->nombre_arcs_val = new QLineEdit();
    p->scene->nombre_arcs_val->setReadOnly(true);
    p->scene->nom_graphe_val = new QLineEdit();
    p->scene->type_graphe_val = new QLineEdit();

    info_graphe->addWidget(nom_graphe, 0, 0);
    info_graphe->addWidget(p->scene->nom_graphe_val, 0, 1);
    info_graphe->addWidget(type_graphe, 1, 0);
    info_graphe->addWidget(p->scene->type_graphe_val, 1, 1);
    info_graphe->addWidget(nombre_sommets, 0, 2);
    info_graphe->addWidget(p->scene->nombre_sommets_val, 0, 3);
    info_graphe->addWidget(nombre_arcs, 1, 2);
    info_graphe->addWidget(p->scene->nombre_arcs_val, 1, 3);
    info_graphe->addWidget(mat_info, 2, 0);
    info_graphe->addWidget(definir_sgp,2,1);
    info_graphe->addWidget(supprimer_tout, 2, 2);
    info_graphe->addWidget(extraire_sgp, 3, 1);
    info_graphe_widget->setLayout(info_graphe);

      p->scene->f_graphe->setWidget(info_graphe_widget);
    addDockWidget(Qt::LeftDockWidgetArea,  p->scene->f_graphe);
}

void Interface::fenetre_infos_algos()
{
    QTextEdit *infos_algos;

    infos_algos = new QTextEdit();
    infos_algos->setWindowTitle("Informations Sur Les Algorithmes");
    infos_algos->setGeometry(450,200,600,400);
    infos_algos->setText("Voici les Différentes informations concernant les différents Algorithmes:\n\n"
                             ": Plus court chemin entre deux sommets préalablement sélectionnés dans un graphe pondéré.\n\n"
                             "Ford-BellMan:Plus long chemin entre deux sommets préalablement sélectionnés dans un graphe pondéré.\n\n"
                             "Ford Fulkerson:Etant donné un graphe pondéré possédant une seule source et un seul puits, l'algorithme permet de trouver un flot réalisable maximal (valeur maximale) qui peut passer de la source au puits.\n\n"
                             "PERT:Permettre de gérer différentes tâches d'un projet en fonction du temps et d'aboutir à une date de réalisation le plus tôt possible.\n\n"
                             "Graphe Eulerien:Cet algorithme permet de trouver un circuit Eulérien dans un graphe c'est-à-dire un circuit qui passe par tous les arcs, une et une seule fois, à partir d'un point de départ.\n\n"
                             "Graphe Hamiltonien:Cet algorithme permet de trouver tous les circuits Hamiltoniens dans un graphe, c'est-à-dire des circuits qui passent une et une seule fois par chaque sommet.\n\n"
                             "Graphe Connexe: Cet algorithme permet de dire si un graphe est connexe (c'est-à-dire, quels que soient les sommets u et v de S il existe une chaîne entre u et v) et s'il ne l'est pas, de trouver chaque composante connexe.\n\n"
                             "Graphe Fortement Connexe:Cet algorithme prend en entrée un graphe orienté et renvoie une partition des sommets du graphe correspondant à ses composantes fortement connexes (c'est à dire, quels que soient les sommets u et v de S il existe un chemin de u à v et de v à u).\n\n"
                             "Parcours En Profondeur: Cet algorithme parcourt un graphe le plus loin possible en partant d'un sommet source.\n\n"
                             "Parcours En Largeur: Cet algorithme parcourt un graphe en partant d'un sommet source en explorant tous ses successeurs et ainsi de suite pour les autres sommets .\n\n");
    infos_algos->setReadOnly(true);
    infos_algos->show();
}

void Interface::fenetre_ajout_algo()//Fonction Affichage De la Fenêtre Ajout/Algo
{

    f_algo=new QDockWidget(tr("Outils"),this);//Creation De La Fenêtre en tant que Widget
//    f_algo->setAllowedAreas(Qt::LeftDockWidgetArea);//Positionnement A Gauche De L'ecran
    f_algo->setMaximumWidth(400);//Taille Max X 400
    f_algo->setMaximumHeight(150);//Taille Max Y 220
    f_algo->setMinimumWidth(400);//Taille Max X 400
//    f_algo->setMinimumHeight(220);//Taille Max Y 220
    f_algo->setVisible(1);//FenetreVisible Par Defaut
    f_algo->setFeatures(QDockWidget::NoDockWidgetFeatures);//Fenetre Non Modifiable Par L'utilisateur
    bouton_algo_ajout_widget = new QWidget();

    add_sommets=new QPushButton("Ajout Sommets");//Création Du Bouton Ajout Sommets
    add_arcs=new QPushButton("Ajout Arcs");//Création Du Bouton Ajout Arcs
    procedures = new QLabel("Algorithmes:");//Zone De Texte Algorithmes
    liste_procedures = new QComboBox(bouton_algo_ajout_widget);//Menu Déroulant avec la Liste Des Algos

    liste_procedures->addItem("None");//Element 1 par Defaut
    liste_procedures->addItem("Djikstra");//Element 2
    liste_procedures->addItem("Ford Fulkerson");//Element 3
    liste_procedures->addItem("Ford-Bellman");//Element 4
    liste_procedures->addItem("PERT");//Element 5
    liste_procedures->addItem("Graphe Eulerien");//Element 6
    liste_procedures->addItem("Graphe Hamiltonien");//Element 7
    liste_procedures->addItem("Graphe Connexe");//Element 8
    liste_procedures->addItem("Graphe Fortement Connexe");//Element 9
    liste_procedures->addItem("Parcours Profondeur");//Element 10
    liste_procedures->addItem("Parcours Largeur");//Element 11
    liste_procedures->addItem("Initialisation");//Element 11

    bouton_algo_ajout = new QGridLayout;
//    bouton_algo_ajout->setContentsMargins(0,0,0,200);
    bouton_algo_ajout->addWidget(add_sommets,0,1,Qt::AlignLeft);
    bouton_algo_ajout->addWidget(add_arcs,1,1,Qt::AlignLeft);
    bouton_algo_ajout->addWidget(procedures, 2, 0,Qt::AlignRight);
    bouton_algo_ajout->addWidget(liste_procedures, 2, 1);
    bouton_algo_ajout_widget->setLayout(bouton_algo_ajout);

    f_algo->setWidget(bouton_algo_ajout_widget);
    addDockWidget(Qt::LeftDockWidgetArea , f_algo);

    connect(liste_procedures, SIGNAL(currentIndexChanged(int)),this,SLOT(affichage_dijkstra(int)));
    connect(liste_procedures, SIGNAL(currentIndexChanged(int)),this,SLOT(affichage_connexe(int)));
    connect(liste_procedures, SIGNAL(currentIndexChanged(int)),this,SLOT(affichage_flot(int)));
    connect(liste_procedures, SIGNAL(currentIndexChanged(int)),this,SLOT(affichage_euler(int)));
    connect(liste_procedures, SIGNAL(currentIndexChanged(int)),this,SLOT(affichage_pert(int)));
    connect(liste_procedures, SIGNAL(currentIndexChanged(int)),this,SLOT(affichage_ford(int)));
    connect(liste_procedures, SIGNAL(currentIndexChanged(int)),this,SLOT(affichage_pronfondeur(int)));
    connect(liste_procedures, SIGNAL(currentIndexChanged(int)),this,SLOT(affichage_largeur(int)));
    connect(liste_procedures, SIGNAL(currentIndexChanged(int)),this,SLOT(affichage_fortement(int)));
    connect(liste_procedures, SIGNAL(currentIndexChanged(int)),this,SLOT(affichage_hamiltonien(int)));
    connect(liste_procedures, SIGNAL(currentIndexChanged(int)),this,SLOT(reinitialise_graphe(int)));

}


QString Interface::chemin_sauvegarde()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", "", "Texte (*.txt)");
    return fichier;
}

QString Interface::chemin_ouverture()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "", "Texte (*.txt)");
    return fichier;
}

QString Interface::chemin_export()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Exporter", "", "Image (*.png)");
    return fichier;
}

void Interface::choix_save()
{
    if(!tab->count()) {message("QGraph","Créer un nouveau graphe"); return;}
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    foreach(QGraphicsItem* item ,p->scene->items()){
     if(item->type()==QSommet::Type) {
         QSommet *sommet = qgraphicsitem_cast<QSommet *>(item);
         sommet->getPsommet()->setAbscisse(item->pos().x());
         sommet->getPsommet()->setOrdonnee(item->pos().y());
          }
    }
    string pathfile = chemin_sauvegarde().toStdString();
    if(pathfile.find(".txt") == std::string::npos){
        pathfile += ".txt";
    }
    if(sauvegarder(pathfile,p->scene->getGraph()))
        message("Sauvegarde", "Sauvegarde effectuée avec succés !");
    else message("Sauvegarde", "Echec de sauvegarde !");
}

void Interface::choix_open()
{
    if(tab->count()==0) choix_new();
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if(p->scene->items().size()!=0)
    choix_new();
    p=  static_cast<onglet *> (tab->currentWidget());
    string pathfile = chemin_ouverture().toStdString();
   p->scene-> setGraphe(charger(pathfile));
   p->scene->AfficherGrapheChargement(p->scene->getGraph());
   choix_centrer();
    update();
}

void Interface::choix_export()
{
    if(!tab->count()) {message("QGraph","Créer un nouveau graphe"); return;}
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    QPixmap pixmap = QPixmap();
    pixmap = QPixmap::grabWindow(p->vue->winId(), 0,0, -1,-1);
    QString pathfile = chemin_export() ;
    if(pathfile.toStdString().find(".png") == std::string::npos){
        pathfile += ".png";
    }
    pixmap.save(pathfile, 0, 100);
}

void Interface::affiche_noms_sommets()
{
    if(!tab->count()) {message("QGraph","Créer un nouveau graphe"); return;}
    qDebug()<<"état boutton "<<actionNomSommets->isChecked();
    onglet *p=  static_cast<onglet *> (tab->currentWidget());

    foreach (QGraphicsItem *item,p->scene->items()) {
        if(item->type()==QSommet::Type)  {
            QSommet* qsommet= qgraphicsitem_cast<QSommet *>(item);
            qsommet->setAffiche_nom(actionNomSommets->isChecked());
            qsommet->update();
    }
}

}

void Interface::affiche_valeurs_sommets()
{
    if(!tab->count()) {message("QGraph","Créer un nouveau graphe"); return;}
    onglet *p=  static_cast<onglet *> (tab->currentWidget());

    foreach (QGraphicsItem *item,p->scene->items()) {
        if(item->type()==QSommet::Type)  {
            QSommet* qsommet= qgraphicsitem_cast<QSommet *>(item);
            qsommet->setAffiche_val(actionValeurSommets->isChecked());
            qsommet->update();
    }
    }
}

void Interface::fenetre_aide()
{
    QTextEdit *infos_aide;

        infos_aide = new QTextEdit();
        infos_aide->setWindowTitle("Aide");
        infos_aide->setGeometry(450,200,600,400);
        infos_aide->setText("Voici les Différentes instructions à suivre concernant les différents Algorithmes:\n\n"
                                 "Dijkstra:L'utilisateur devra sélectionné le sommet de départ(colorié en bleu) puis le sommet d'arrivé (colorié en rouge).Le chemin le plus court sera affiché dans une fenêtre et il sera colorié en bleu.En cas d'erreur une fenêtre s'ouvrira et précisera de quelle type elle est.La valeur de l'arc représente la distance entre deux sommets et la seconde valeur du sommet représente la valeur la plus courte calculée précédemment jusqu'à ce sommet.\n\n"
                                 "Ford-BellMan:L'utilisateur devra sélectionné le sommet de départ(colorié en bleu) puis le sommet d'arrivé (colorié en rouge).Le chemin le plus long sera affiché dans une fenêtre et il sera colorié en rouge.En cas d'erreur une fenêtre s'ouvrira et précisera de quelle type elle est.La valeur de l'arc représente la distance entre deux sommets et la seconde valeur du sommet représente la valeur la plus longue calculée précédemment jusqu'à ce sommet.\n\n"
                                 "Ford Fulkerson:L'utilisateur devra sélectionné le sommet source(colorié en bleu) puis le sommet puits (colorié en rouge).Le résultat sera le flot maximal entre la source et le puit dans une fenêtre, un arc colorié en bleu représentera sa saturation et donc que le flux passant par celui-ci ne peut plus augmenter.La première valeur des arcs représente la quantité de flux maximal pouvant s'écouler sur celui-ci.La seconde valeur représente le flux qui pourra s'écouler dans l'arc.\n\n"
                                 "PERT:L'utilisateur devra sélectionné le sommet source(colorié en bleu) puis le sommet puits (colorié en rouge).Le résultat affichera le chemin critique colorié en vert.Les sommets qui sont sur ceux chemins ne peuvent pas prendre de retard en terme de durée.LA 1ere valeur représente la date au plus tôt,la seconde la date au plus tard et la derniere la marge critique.\n\n"
                                 "Graphe Eulerien:L'utilisateur devra sélectionné le sommet de départ.\n\n"
                                 "Graphe Hamiltonien:\n\n"
                                 "Graphe Connexe:Le graphe sera colorié d'une ou plusieurs couleur selon ses composantes fortement connexe\n\n"
                                 "Graphe Fortement Connexe:\n\n"
                                 "Parcours en profondeur:Les sommets seront coloriés en vert et le chemin parcouru par le parcours en profondeur en bleu.\n\n"
                                 "Parcours en largeur:Les sommets seront coloriés en vert et le chemin parcouru par le parcours en largeur en bleu.Pour chaque itération, un numéro sera attribué sur les arcs indiquant l'ordre sur lequel le sommet pointé est traité par l'algorithme de parcours en largeur\n\n");
        infos_aide->setReadOnly(true);
        infos_aide->show();
}


void Interface::affiche_noms_arcs()
{
    onglet *p=  static_cast<onglet *> (tab->currentWidget());

    foreach (QGraphicsItem *item,p->scene->items()) {
        if(item->type()==QArc::Type)  {
            QArc* qarc= qgraphicsitem_cast<QArc *>(item);
            qarc->setAffiche_nom(actionNomArcs->isChecked());
            qarc->update();
    }
    }
}

void Interface::affiche_valeurs_arcs()
{
    onglet *p=  static_cast<onglet *> (tab->currentWidget());

    foreach (QGraphicsItem *item,p->scene->items()) {
        if(item->type()==QArc::Type)  {
            QArc* qarc= qgraphicsitem_cast<QArc *>(item);
            qarc->setAffiche_val(actionValeurArcs->isChecked());
            qarc->update();
    }
    }
}

void Interface::affiche_matrice()
{
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    int taille=p->scene->graph->getCompteurS();
    QMessageBox message;

    if(tab_matrice!=NULL) tab_matrice->clear();
    tab_matrice = new QTableWidget(taille,taille);
    for(int i=0;i<taille;i++){
        tete_matrice<<QString::number(i);
    }
    tab_matrice->setHorizontalHeaderLabels(tete_matrice);
    tab_matrice->setVerticalHeaderLabels(tete_matrice);

    tab_matrice->setWindowTitle("Matrice d'adjacence");
    tab_matrice->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tab_matrice->setStyleSheet("QTableView {selection-background-color: red;}");
    tab_matrice->setGeometry(400,100,taille*30,taille*35);
//    tab_matrice->setMaximumSize(taille*28,taille*33);
    //insert data
    for(int i=0;i<taille;i++){
        for(int j=0;j<taille;j++){
     tab_matrice->setItem(i,j, new QTableWidgetItem(QString::number(p->scene->getGraph()->existeArc(i,j))));
     tab_matrice->setColumnWidth(i,25);
     tab_matrice->setRowHeight(i,30);
                                              }
                                    }
    tab_matrice->show();
    tete_matrice.clear();
}

void Interface::zoom()//Fonction De Zoom +
{
    if(!tab->count()) {message("QGraph","Créer un nouveau graphe"); return;}
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if(p->vue->matrix().m11()>5) return;
    p->vue->scale(1.5,1.5);//Echelle Du ZooM
}

void Interface::dezoom()//Fonction De Zoom -
{
//    if(!tab->count()) {message("QGraph","Créer un nouveau graphe"); return;}
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if(p->vue->matrix().m11()<0.6) return;
    p->vue->scale(0.66,0.66);//Echelle Du Zoom

}

void Interface::changer_nom_onglet(QString p)
{
    tab->setTabText(tab->currentIndex(),p);
}

void Interface::affichage_dijkstra(int i)
{
    if(i!=1) return;
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if(p->scene->selectedItems().size()==0) message("Dijkstra","Choisir sommet de départ et sommet d'arrivée");
    else if(p->scene->selectedItems().size()==1){
    QSommet *a = p->scene->getQSommet(p->scene->idAvant);
    if(a==NULL) return;
    if(p->scene->selectedItems().at(0)->type()!=QSommet::Type) {
        message("Dijkstra","Il faut choisir un sommet"); return;}
    debut_affichage_algo(i);
    QSommet *b = qgraphicsitem_cast<QSommet *>(p->scene->selectedItems().at(0));
    if( existeChemin(a->getPsommet(), b->getPsommet(), p->scene->getGraph()) ==true)
        {
        if(cycle(p->scene->getGraph()) == false)
        {
        double r=dijkstra(*a->getPsommet(),*b->getPsommet(), p->scene->getGraph());
    message("Dijkstra"
   ,"Résultat entre "+QString::number(a->getPsommet()->getIds())+" et "+QString::number(b->getPsommet()->getIds())+" = "+QString::number(r));
    fin_affichage_algo(i);

        }
        else message("Dijkstra" ,"Il y a un circuit");
        }
    else  message("Dijkstra" ,"Il n'y a pas de chemin");
    }
}

void Interface::affichage_flot(int i)
{
    if(i!=2) return;
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if(p->scene->selectedItems().size()!=1) { message("Flot","Choisir sommet source"); return;}
    if(p->scene->selectedItems().at(0)->type()!=QSommet::Type) return;
    QSommet *b = qgraphicsitem_cast<QSommet *>(p->scene->selectedItems().at(0));
    QSommet *a = p->scene->getQSommet(p->scene->idAvant);
    if(!estSource(a->getPsommet(),p->scene->getGraph())) {message("Flot","Le sommet de départ ce n'est pas une source"); return;}
    if(!estPuits(b->getPsommet(),p->scene->getGraph())) {message("Flot","Sommet d'arrivée ce n'est pas un puits"); return;}
    if(!existeChemin(a->getPsommet(),b->getPsommet(),p->scene->getGraph())) {message("Pert","Il n'y a pas de chemin entre A et B"); return;}
    if(cycle(p->scene->getGraph())) {message("Flot","Il y a une chaine"); return;}
    if(!conditionPertFlot(a->getPsommet(),b->getPsommet(),p->scene->getGraph())){message("Pert","Le graphe ne vérifie pas les conditions nécéssaires pour éxécuter l'algorithme !");return;}
    int flot=Flot_Max(p->scene->getGraph(),*a->getPsommet(),*b->getPsommet());
    message("Flot max","Le flot maximum réalisable = "+QString::number(flot));

    fin_affichage_algo(i);
}

void Interface::affichage_connexe(int i)
{
    if(i!=7) return;
    debut_affichage_algo(i);
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    GrapheConnexe(p->scene->getGraph());
    message("Connexe","Composantes connexes coloriées");
    fin_affichage_algo(i);
}

void Interface::affichage_euler(int i)
{
    if(i!=5) return;
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if( p->scene->selectedItems().size()==0) {
         fin_affichage_algo(i);
        message("Euler","Il faut choisir un sommet de départ");
        return;}
     if(p->scene->selectedItems().at(0)->type()!=QSommet::Type) {
          fin_affichage_algo(i);
        message("Euler","Il faut choisir un sommet d'arrivée"); return;}

    qDebug()<<"éxcution euler";
    debut_affichage_algo(i);
    QSommet *a = qgraphicsitem_cast<QSommet *>(p->scene->selectedItems().at(0));
    if(!cycle(p->scene->getGraph())) {message("Euler","Le graphe ne contient pas de circuit Eulerien"); return;}
    bool oui=euler(p->scene->getGraph(),*a->getPsommet());
    if(oui){     fin_affichage_algo(i);
                 message("Euler","Le graphe contient un circuit Eulerien");
            }
    else message("Euler","Le graphe ne contient pas de circuit Eulerien");
}

void Interface::affichage_pert(int i)
{
if(i!=4) return;
debut_affichage_algo(i);
onglet *p=  static_cast<onglet *> (tab->currentWidget());
if(p->scene->selectedItems().size()!=1) { message("Pert","Choisir sommet source"); return;}
if(p->scene->selectedItems().at(0)->type()!=QSommet::Type) return;
QSommet *b = qgraphicsitem_cast<QSommet *>(p->scene->selectedItems().at(0));
QSommet *a = p->scene->getQSommet(p->scene->idAvant);
if(!estSource(a->getPsommet(),p->scene->getGraph())) {message("Pert","Le sommet de départ n'est pas une source"); return;}
if(!estPuits(b->getPsommet(),p->scene->getGraph())) {message("Pert","Sommet d'arrivée n'est pas un puit"); return;}
if(!existeChemin(a->getPsommet(),b->getPsommet(),p->scene->getGraph())) {message("Pert","Il n'y a pas de chemin entre A et B"); return;}
if(cycle(p->scene->getGraph())) {message("Pert","Il y a une chaine"); return;}
if(!conditionPertFlot(a->getPsommet(),b->getPsommet(),p->scene->getGraph())){message("Pert","Le graphe ne vérifie pas les conditions nécéssaires pour éxécuter l'algorithme !");return;}
Pert(p->scene->getGraph(),*a->getPsommet(),*b->getPsommet());
fin_affichage_algo(i);
}

void Interface::affichage_ford(int i)
{
    if(i!=3) return;
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if(p->scene->selectedItems().size()==1){
    QSommet *a = p->scene->getQSommet(p->scene->idAvant);
    if(a==NULL) return;
    if(p->scene->selectedItems().at(0)->type()!=QSommet::Type) {
        message("Ford Bellman","Il faut choisir un sommet"); return;}

    QSommet *b = qgraphicsitem_cast<QSommet *>(p->scene->selectedItems().at(0));
    qDebug()<<"bellamn entre"<<a->getPsommet()->getIds()<<b->getPsommet()->getIds();
    debut_affichage_algo(i);
    if( existeChemin(a->getPsommet(), b->getPsommet(), p->scene->getGraph()) ==true)
        {
        if(cycle(p->scene->getGraph()) == false){
            double r =fordBellman(*a->getPsommet(),*b->getPsommet(), p->scene->getGraph());
                message("Ford-Bellman"
                ,"résultat entre "+QString::number(a->getPsommet()->getIds())+
                " et "+QString::number(b->getPsommet()->getIds())+" = "+QString::number(r));
                fin_affichage_algo(i);
        }
        else message("Ford Bellman" ,"Il y a un circuit");
        }
        else  message("Ford Bellman" ,"Il n'y a pas de chemin");
    }

}

void Interface::affichage_pronfondeur(int i)
{
    if(i!=9) return;
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if( p->scene->items().size()==0) return;

    qDebug()<<"éxcution parcours en prafondeurQ";
    debut_affichage_algo(i);
    /*QSommet *a = qgraphicsitem_cast<QSommet *>(p->scene->selectedItems().at(0));*/
    Pprofondeur(p->scene->getGraph());
        fin_affichage_algo(i);
        message("Parcours","Voici le parcours en profondeur");
}

void Interface::affichage_largeur(int i)
{
    if(i!=10) return;
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if( p->scene->items().size()==0) return;

    qDebug()<<"éxcution parcours en largeurQ";
    debut_affichage_algo(i);
    /*QSommet *a = qgraphicsitem_cast<QSommet *>(p->scene->selectedItems().at(0));*/
    Plargeur(p->scene->getGraph());
        fin_affichage_algo(i);
        message("Parcours","Voici le parcours en largeur");
}

void Interface::affichage_fortement(int i)
{
    if(i!=8) return;
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if( p->scene->items().size()==0) return;
    qDebug()<<"éxcution de fortement connexe";
    debut_affichage_algo(i);
    Tarjan(p->scene->graph);
    fin_affichage_algo(i);
    message("Fortement connexe","Voici fortement connexe");

}

void Interface::affichage_hamiltonien(int i)
{
    if(i!=6) return;
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    Feynmann(p->scene->getGraph());
    message("hamilton","Parcours hamiltonien coloré");
    foreach (QGraphicsItem *item, p->scene->items())
    item->update();


}

void Interface::choix_definir_sgp()
{
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    p->scene->selectionner();
}

void Interface::choix_extraire_sgp()
{
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if(!p->scene->selectedItems().size()) {
    message("Sous graphe partiel","Choisissez sommets");
    return;}
    vector <Sommet> list;
    QSommet *sommet;
    Graphe *ssgraphe;
        foreach(QGraphicsItem* item,p->scene->selectedItems()){
            if(item->type()==QSommet::Type) {
                sommet = qgraphicsitem_cast<QSommet *>(item);
                sommet->getPsommet()->setAbscisse(item->pos().x());
                sommet->getPsommet()->setOrdonnee(item->pos().y());
                list.push_back(*sommet->getPsommet());
        }
        }
        choix_new();
        ssgraphe=new Graphe(*p->scene->getGraph(),list);
        p=  static_cast<onglet *> (tab->currentWidget());
        p->scene->graph=ssgraphe;
        p->scene->AfficherGrapheChargement(ssgraphe);
}

void Interface::choix_centrer()
{
    double xmax=0,xmin=99999,ymin=99999,ymax=0;

    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    foreach(QGraphicsItem* item,p->scene->items()){
     if(item->type()!=QSommet::Type) continue;
    if(xmin>item->pos().x()) xmin=item->pos().x();
    if(xmax<item->pos().x()) xmax=item->pos().x();
    if(ymin>item->pos().y()) ymin=item->pos().y();
    if(ymax<item->pos().y()) ymax=item->pos().y();
    }
    p->vue->fitInView(xmin-40,ymin-40,xmax-xmin+50,ymax-ymin+100,Qt::KeepAspectRatio);

}

void Interface::debut_affichage_algo(int i){

  liste_procedures->setCurrentIndex(0);
  if(i==0) return ;
  onglet *p=  static_cast<onglet *> (tab->currentWidget());
  QArc *arc;
  QSommet *sommet;

          foreach (QGraphicsItem *item, p->scene->items())
          {
              if(item->type()==QArc::Type){
                  arc=qgraphicsitem_cast<QArc *> (item);
                  arc->setAffiche_val2(false);
                  arc->setAffiche_val(actionValeurArcs->isChecked());
              }
              else if(item->type()==QSommet::Type){
                sommet=qgraphicsitem_cast<QSommet *> (item);
                sommet->setAffiche_val(false);
              }
              item->update();
          }

}


void Interface::fin_affichage_algo(int i)
{
    onglet *p=  static_cast<onglet *> (tab->currentWidget());

    if(i==5 )//Euler
        {
        QArc *arc;
        QSommet *sommet;
            foreach (QGraphicsItem *item, p->scene->items())
            {
                if(item->type()==QArc::Type){
                arc=qgraphicsitem_cast<QArc *> (item);
                if(arc->getParc()->getVal2() != 0)
                {
                    arc->setAffiche_val2(true);
                }
                arc->setAffiche_val(false);}
                else if(item->type()==QSommet::Type){
                  sommet=qgraphicsitem_cast<QSommet *> (item);
                  sommet->setAffiche_val3(false);
                  sommet->setAffiche_val2(false);
                }
                item->update();
            }
        }

        if(i == 9 )//Parcours en profondeur
        {    QArc *arc;
            foreach (QGraphicsItem *item, p->scene->items())
            {
                if(item->type()!=QArc::Type)continue;
                arc=qgraphicsitem_cast<QArc *> (item);
                if(arc->getParc()->getVal2() != 0)
                {
                    arc->setAffiche_val2(true);
                }
                arc->setAffiche_val(false);
                item->update();
            }
        }

        if(i==10 )//Parcours en largeur
        {    QArc *arc;
            foreach (QGraphicsItem *item, p->scene->items())
            {
                if(item->type()!=QArc::Type)continue;
                arc=qgraphicsitem_cast<QArc *> (item);
                if(arc->getParc()->getVal2() != 0)
                {
                    arc->setAffiche_val2(true);
                }
                arc->setAffiche_val(false);
                item->update();
            }
        }

    if(i==2 )//flot
    {    QArc *arc;
        foreach (QGraphicsItem *item, p->scene->items())
        {
            if(item->type()!=QArc::Type)continue;
            arc=qgraphicsitem_cast<QArc *> (item);
            arc->setAffiche_val2(true);
            arc->setAffiche_val(true);
            item->update();
        }
    }

    if(i==1 || i==3)//Dijkstra ou bellman
    {    QArc *arc;
         QSommet *sommet;
        foreach (QGraphicsItem *item, p->scene->items())
        {
            if(item->type()==QArc::Type){
                arc=qgraphicsitem_cast<QArc *> (item);
//                arc->setAffiche_val2(false);
                arc->setAffiche_val(true);
            }
            else if(item->type()==QSommet::Type){
              sommet=qgraphicsitem_cast<QSommet *> (item);
              sommet->setAffiche_val3(false);
              sommet->setAffiche_val2(true);

            }
            item->update();
        }
    }

    if(i==4 )//pert
    {    QArc *arc;
         QSommet *sommet;
        foreach (QGraphicsItem *item, p->scene->items())
        {
            if(item->type()==QArc::Type){
                arc=qgraphicsitem_cast<QArc *> (item);
                arc->setAffiche_val(true);
            }
            else if(item->type()==QSommet::Type){
              sommet=qgraphicsitem_cast<QSommet *> (item);
              sommet->setAffiche_val3(true);
            }
            item->update();
        }
    }



    foreach (QGraphicsItem *item, p->scene->items())
     item->update();
    liste_procedures->setCurrentIndex(0);
}

void Interface::message(QString titre, QString text)
{
    QMessageBox m;
    m.setText(text);
    m.setWindowTitle(titre);
    m.exec();
}

void Interface::fenetre_onglet()
{
        tab=new QTabWidget();
        tab->showMaximized();
        tab->setTabsClosable(true);
        tab->setMovable(true);
        setCentralWidget(tab);
}

void Interface::theme()
{
    if(actionTheme->isChecked()){
        this->setStyleSheet("QLineEdit { background-color: white }");
        tab->setStyleSheet("background:QColor(200,100,150);");
        this->setStyleSheet("background:QColor(200,100,150);");
            add_sommets->setStyleSheet("QWidget { background-color:silver; }");
            add_arcs->setStyleSheet("QWidget { background-color:silver; }");
            liste_procedures->setStyleSheet("QWidget { background-color:silver; }");

            bouton_selection_multiple->setStyleSheet("QWidget { background-color:silver; }");
            bouton_selection_simple->setStyleSheet("QWidget { background-color:silver; }");
            plus->setStyleSheet("QWidget { background-color:silver; }");
            moins->setStyleSheet("QWidget { background-color:silver; }");
            centrer->setStyleSheet("QWidget { background-color:silver; }");
            bouton_suppression_multiple->setStyleSheet("QWidget { background-color:silver; }");
    }
    else {

        this->setStyleSheet("QLineEdit { background-color: white }");
        tab->setStyleSheet("background:QColor::white;");
        this->setStyleSheet("background:QColor::white);");
    }


}

void Interface::reinitialise_graphe(int i)
{
    liste_procedures->setCurrentIndex(0);
    if(i!=11) return;
    onglet *p=  static_cast<onglet *> (tab->currentWidget());
    if( p->scene->items().size()==0) return;
        p->scene->graph->initialiserCouleurArc();
        p->scene->graph->initialiserCouleurSommet();
        p->scene->graph->initialiserVal2Sommet();
        p->scene->graph->initialiserVal3Sommet();
        p->scene->graph->initialiserEtatSommet();
        p->scene->graph->initialiserEtatArc();
        p->scene->graph->initialiserVal2Arc();

        QArc *arc;
        QSommet *sommet;
        foreach (QGraphicsItem *item, p->scene->items())
        {
            if(item->type()==QArc::Type){
                arc=qgraphicsitem_cast<QArc *> (item);
                arc->setAffiche_val(false);
                arc->setAffiche_val2(false);
            }
            else if(item->type()==QSommet::Type){
              sommet=qgraphicsitem_cast<QSommet *> (item);
              sommet->setAffiche_val3(false);
              sommet->setAffiche_val2(false);
              sommet->setAffiche_val(false);

            }
            item->update();
        }
    qDebug()<<"Réinitialisation du graphe";
    message("Graphe","Le graphe est réinitialisé");
}

Interface::~Interface()
{

}
