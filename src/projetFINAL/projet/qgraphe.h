#ifndef QGRAPH_H
#define QGRAPH_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QList>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include "sommet.h"
#include "qsommet.h"
#include "qgraphe.h"
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLineEdit>
#include "qarc.h"
#include <QKeyEvent>
#include <QTime>
#include <QGraphicsLineItem>
#include "graphe.h"
#include <QDockWidget>
#include <QMessageBox>
#include <QAction>
#include <QGridLayout>

enum mode_m {aucun,dessin_arc,dessin_sommet,supression,deplacement,selection};

class QGraphe : public QGraphicsScene//Classe Visualisation
{
    Q_OBJECT
friend class Interface;

private:
    Graphe *graph;
    int idActuel;
    int idAvant;

    int mode=mode_m::aucun;
    QGraphicsLineItem *line;
    QLineEdit *nom_sommet_val;//Attribut nom_sommet_val
    QLineEdit *valeur_sommet_val;//Attribut valeur_sommet_val
    QLineEdit *pred_sommet_val;//Attribut pred_sommet_val
    QLineEdit *succ_sommet_val;//Attribut succ_sommet_val
    QLineEdit *id_sommet_val;//Attribut id_sommet_val
    QLineEdit *d_plus_sommet_val;//Attribut d_plus_sommet_val (Degré Sortant)
    QLineEdit *d_moins_sommet_val;//Attribut d_moins_sommet_val (Degré Entrant)
    QLineEdit *d_total_sommet_val;//Attribut d_total_sommet_val

    QLineEdit *nom_arc_val;//Attribut nom_arc_val
    QLineEdit *valeur_arc_val;//Attribut valeur_arc_val
    QLineEdit *sommet_origine_val;//Attribut sommet_origine_val
    QLineEdit *sommet_arrive_val;//Attribut sommet_arrive_val
    QLineEdit *id_arc_val;//Attribut id_arc_val

    QLineEdit *nombre_sommets_val;//Attribut nombre_sommets_val
    QLineEdit *nombre_arcs_val;//Attribut nombre_arcs_val
    QLineEdit *nom_graphe_val;//Attribut id_graphe_val
    QLineEdit *type_graphe_val;//Attribut type_graphe_val

    QDockWidget *f_sommet;//Attribut f_sommet (Fenêtre Infos Sommets)
    QDockWidget *f_arc;//Attribut f_arc (Fenêtre Infos Arcs)
    QDockWidget *f_graphe;//Attribut f_graphe (Fenêtre Infos Graphes)



    bool affiche_nom_sommet=false;
    bool affiche_val_sommet=false;
    bool affiche_nom_arc=false;
    bool affiche_val_arc=false;


public slots:
void arc_ajouter();
void deplacer();
void sommet_ajouter();
void supprimer();
void selectionner();
void setNomSommet(QString s);
void setValSommet(QString s);
void setNomGraphe(QString s);
void setNomArc(QString s);
void setValArc(QString s);
void setTypeGraphe(QString s);

void AfficherGrapheChargement(Graphe *g);
void supprimertout();
void setAffiche_nom_sommet(bool value);
void setAffiche_val_sommet(bool value);
void setAffiche_nom_arc(bool value);
void setAffiche_val_arc(bool value);

public:
explicit QGraphe(QObject *parent = 0);//Constructeur

Graphe* getGraph();
void setGraphe(Graphe *g);

virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent) override;//Fonction Double clique Souris
virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent) override;//Fonction Deplacer Souris
virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent) override;//Fonction Relacher Clique Souris
virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;//Fonction Clique Souris
void drawBackground(QPainter *painter, const QRectF &rect) override;
void AjouterQSommet(QPointF p);
void AjouterQArc(QSommet *a , QSommet *b);
void supprimerQObjet(QGraphicsItem *item);
QSommet *getQSommet(int id);
QArc *getQArc(int id);

QLineEdit *getNom_sommet_val() const;
void info_graphe();
void info_sommet(QSommet* sommet);
void info_arc(QArc *arc);
void setQ(QLineEdit * line, QString value);
~QGraphe();//Destructeur


};

#endif // VISUALISATION_H
