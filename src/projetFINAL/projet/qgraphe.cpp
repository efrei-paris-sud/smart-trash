#include "qgraphe.h"
#include <QDebug>
#include <QGraphicsEllipseItem>
#include "qmath.h"
#include <QGraphicsItem>
#include "qarc.h"



QGraphe::QGraphe(QObject *parent):QGraphicsScene(parent)//Constructeur
{
    this->nom_sommet_val=new QLineEdit();
    line=0;
    graph=new Graphe(Graphe::nbGraphes(),"Graphe");
    idActuel=0;
    idAvant=0;

}

QLineEdit *QGraphe::getNom_sommet_val() const
{
    return nom_sommet_val;
}

void QGraphe::info_graphe()
{
    this->setQ(nom_graphe_val,QString::fromStdString(graph->getNom()));
    this->setQ(nombre_sommets_val,QString::number(graph->getTaille()));
    this->setQ(nombre_arcs_val,QString::number(graph->getTailleArc()));
    if(graph->getTypeReel())
        this->setQ(type_graphe_val,"Réel");
    else
      this->setQ(type_graphe_val,"Entier");
     f_sommet->setVisible(0);
     f_arc->setVisible(0);
     f_graphe->setVisible(1);
}

void QGraphe::info_sommet(QSommet* sommet)
{
    idActuel=sommet->getPsommet()->getIds();
    sommet->setId(idActuel);
    this->setQ(id_sommet_val,QString::number(idActuel));
    this->setQ(nom_sommet_val,QString::fromStdString(graph->getSommet(idActuel)->getNom()));
    this->setQ(valeur_sommet_val,QString::number(graph->getSommet(idActuel)->getVal1(),'.',2));
    this->setQ(d_plus_sommet_val,QString::number(graph->getSommet(idActuel)->getDegrPlus()));
    this->setQ(d_moins_sommet_val,QString::number(graph->getSommet(idActuel)->getDegrMoins()));
    this->setQ(d_total_sommet_val,QString::number(graph->getSommet(idActuel)->getDegrTotal()));
           f_arc->setVisible(0);
          f_sommet->setVisible(1);
          f_graphe->setVisible(0);

}

void QGraphe::info_arc(QArc* arc)
{
        idActuel=arc->getParc()->getIda();
        this->setQ(id_arc_val,QString::number(idActuel));
       this->setQ(nom_arc_val,QString::fromStdString(arc->getParc()->getNom()));
        this->setQ(valeur_arc_val,QString::number(arc->getParc()->getVal1(),'.',2));
        this->setQ(sommet_origine_val,QString::number(arc->getParc()->getOrigine()->getIds()));
        this->setQ(sommet_arrive_val,QString::number(arc->getParc()->getDestination()->getIds()));
    f_sommet->setVisible(0);
    f_arc->setVisible(1);
    f_graphe->setVisible(0);
}

void QGraphe::setQ(QLineEdit *line, QString value)
{
    line->setText(value);
}

QGraphe::~QGraphe()
{
    delete graph;
    delete nom_sommet_val;//Attribut nom_sommet_val
    delete valeur_sommet_val;//Attribut valeur_sommet_val
    delete pred_sommet_val;//Attribut pred_sommet_val
    delete succ_sommet_val;//Attribut succ_sommet_val
    delete id_sommet_val;//Attribut id_sommet_val
    delete d_plus_sommet_val;//Attribut d_plus_sommet_val (Degré Sortant)
    delete d_moins_sommet_val;//Attribut d_moins_sommet_val (Degré Entrant)
    delete d_total_sommet_val;//Attribut d_total_sommet_val

    delete nom_arc_val;//Attribut nom_arc_val
    delete valeur_arc_val;//Attribut valeur_arc_val
    delete sommet_origine_val;//Attribut sommet_origine_val
    delete sommet_arrive_val;//Attribut sommet_arrive_val
    delete id_arc_val;//Attribut id_arc_val

    delete nombre_sommets_val;//Attribut nombre_sommets_val
    delete nombre_arcs_val;//Attribut nombre_arcs_val
    delete nom_graphe_val;//Attribut id_graphe_val
    delete type_graphe_val;//Attribut type_graphe_val

    delete f_sommet;//Attribut f_sommet (Fenêtre Infos Sommets)
    delete f_arc;//Attribut f_arc (Fenêtre Infos Arcs)
    delete f_graphe;//Attribut f_graphe (Fenêtre Infos Graphes)
}

Graphe* QGraphe::getGraph(){
    return graph;
}
void QGraphe::setGraphe(Graphe *g){
    this->graph = g;
}


void QGraphe::setNomSommet(QString s)
{
if(mode==mode_m::supression) return ;
graph->getSommet(idActuel)->setNom(s.toStdString());
qDebug() << Q_FUNC_INFO << "J'initliasie nom sommet avec case id="<<idActuel;
for(int i=0;i<items().size();i++) items().at(i)->update();
}

void QGraphe::setValSommet(QString s)
{
if(mode==mode_m::supression) return ;
if ((s.toStdString()>="A" && s.toStdString()<="z") || s.toDouble()<0 ){
QMessageBox message;
message.setText("Entrez une valeur numérique positive");
message.setWindowTitle("Erreur");
message.exec();
return;}

if(s.toDouble()>=0) {
    graph->getSommet(idActuel)->setVal1(s.toDouble());
    qDebug() << Q_FUNC_INFO << "J'initliasie val sommet avec case id="<<s;
    for(int i=0;i<items().size();i++) items().at(i)->update();
    return;
   }

}

void QGraphe::setNomGraphe(QString s)
{
graph->setNom(s.toStdString());
}

void QGraphe::setNomArc(QString s)
{
getQArc(idActuel)->getParc()->setNom(s.toStdString());
qDebug() << Q_FUNC_INFO << "J'initliasie nom sommet avec case id="<<s;
for(int i=0;i<items().size();i++) items().at(i)->update();

}

void QGraphe::setValArc(QString s)
{
if ((s.toStdString()>="A" && s.toStdString()<="z") || s.toDouble()<0 ){
QMessageBox message;
message.setText("Entrez une valeur numérique positive");
message.setWindowTitle("Erreur");
message.exec();
return;}

if(s.toDouble()>=0) {
    getQArc(idActuel)->getParc()->setVal1(s.toDouble());
    qDebug() << Q_FUNC_INFO << "J'initliasie val sommet avec case id="<<s;
    for(int i=0;i<items().size();i++) items().at(i)->update();
    return;
}
}

void QGraphe::setTypeGraphe(QString s)
{
if(s=="Réel" || s=="Reel" || s=="reel" || s=="réel") graph->setTypeReel(true);
else if(s=="Entier" || s=="entier") graph->setTypeReel(false);
for(int i=0;i<items().size();i++) items().at(i)->update();
}


void QGraphe::setAffiche_nom_sommet(bool value)
{
    affiche_nom_sommet = value;
}

void QGraphe::setAffiche_val_sommet(bool value)
{
    affiche_val_sommet = value;
}

void QGraphe::setAffiche_nom_arc(bool value)
{
    affiche_nom_arc = value;
}

void QGraphe::setAffiche_val_arc(bool value)
{
    affiche_val_arc = value;
}

void QGraphe::arc_ajouter()
{
    mode=mode_m::dessin_arc;

}

void QGraphe::deplacer()
{
 mode=mode_m::deplacement;
 foreach (QGraphicsItem *item, items())
    {
    item->setSelected(false);
    }
}

void QGraphe::sommet_ajouter()
{
    mode=mode_m::dessin_sommet;
}

void QGraphe::supprimer()
{
    mode=mode_m::supression;
    if(this->selectedItems().size()==0) return ;
    foreach (QGraphicsItem *item, selectedItems()) {
        if(item->type()==QArc::Type)  {
        supprimerQObjet(item);
        idAvant=-1;
    }
    }
    foreach (QGraphicsItem *item, selectedItems()) {
        if(item->type()==QSommet::Type)  {
        supprimerQObjet(item);
    }
}

}

void QGraphe::selectionner()
{
    mode=mode_m::selection;

}

void QGraphe::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
   {
    if (line != 0 && mode == mode_m::dessin_arc) {

        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();
        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 &&
                 startItems.first() != endItems.first() &&
                startItems.first()->type()==QSommet::Type &&
                 endItems.first()->type()==QSommet::Type ) {
            QSommet *startItem = qgraphicsitem_cast<QSommet *>(startItems.first());
            QSommet *endItem = qgraphicsitem_cast<QSommet *>(endItems.first());
            AjouterQArc(startItem,endItem);
        }

        line=0;

    }

    else if(mouseEvent->button()==Qt::LeftButton && mode==mode_m::dessin_sommet){
        if(this->items(mouseEvent->scenePos()).size()==0){
            AjouterQSommet(mouseEvent->scenePos());
        }
     }
       update();
       QGraphicsScene::mouseReleaseEvent(mouseEvent);
    }


void QGraphe::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)//Fonction Double clique Souris
{
f_sommet->setVisible(0);
f_arc->setVisible(0);
f_graphe->setVisible(0);
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();//Action dans la Zone De la Scene
     update();
     QGraphicsScene::mouseDoubleClickEvent(mouseEvent);//Action De Double-Clique
}


void QGraphe::mousePressEvent(QGraphicsSceneMouseEvent * me)//Fonction Clique Souris
{
    if(me->button()==Qt::LeftButton && mode==mode_m::deplacement)
          {
        if(items(me->scenePos()).size()==0) {
           info_graphe();
           qDebug() << Q_FUNC_INFO << "information graphe";
           return;
                                            }
      QGraphicsItem *nouveau=items(me->scenePos()).first();

      if(nouveau->type()==QSommet::Type)
                        {
          qDebug()<<"sommet ancien"<<idAvant<<"  "<<idActuel;
          QSommet *sommet=  qgraphicsitem_cast<QSommet *>(nouveau) ;
          if(idAvant==-1){
            idAvant=sommet->getPsommet()->getIds();
            idActuel=sommet->getPsommet()->getIds();
                        }
          this->getQSommet(idAvant)->setAncien(false);
          this->getQSommet(idAvant)->update();
            idAvant=idActuel;
            this->getQSommet(idAvant)->setAncien(true);
            info_sommet(sommet);
          qDebug() << Q_FUNC_INFO << "information sommet="<<sommet->getId();

                         }

     else if(nouveau->type()==QArc::Type){
          QArc *p=  qgraphicsitem_cast<QArc *>(nouveau) ;
          if(idAvant!=-1){
            this->getQSommet(idAvant)->setAncien(false);
            this->getQSommet(idAvant)->update();
                        }
          idAvant=-1;

          qDebug() << Q_FUNC_INFO << "information arc";
          info_arc(p);
               }
            }

    else if (me->button()==Qt::LeftButton && mode==mode_m::dessin_arc)
    {
        line = new QGraphicsLineItem(QLineF(me->scenePos(),
                                    me->scenePos()));
        line->setPen(QPen(Qt::red, 2));
        addItem(line);
    }
   else  if(mode==mode_m::supression )
                  {
                  if(items(me->scenePos()).size())
                  supprimerQObjet(this->items(me->scenePos()).first());
                   }

    if( mode==mode_m::selection) {
        if(items(me->scenePos()).size()==0) return ;
           foreach (QGraphicsItem *item, items(me->scenePos()))
               item->setSelected(true);
    }

    update();
    QGraphicsScene::mousePressEvent(me);//Action De Clique
}


void QGraphe::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mode == mode_m::dessin_arc && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }

    else if (mode & mode_m::deplacement || mode & mode_m::selection   ){
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }

}

void QGraphe::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();


    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::black);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}


void QGraphe::supprimerQObjet(QGraphicsItem *item)
{    int id;
    if(item->type()==QSommet::Type)  {
      QSommet* qsommet= qgraphicsitem_cast<QSommet *>(item);
      id=qsommet->getPsommet()->getIds();
      if(id==idAvant) idAvant=-1;
      if(id==idActuel) idActuel=0;
      qsommet->supprimerQArcs();
      qsommet->setPsommet(NULL);
      this->removeItem(item);
      graph->suppSommet(id);
//      delete item;
       for(int i=0;i<items().size();i++) items().at(i)->update();
    }

     else if(item->type()==QArc::Type) {
        QArc* arc=qgraphicsitem_cast<QArc *>(item);
        idActuel=0;
        arc->source=NULL;
        arc->dest=NULL;
        graph->suppArc(arc->getParc()->getOrigine()->getIds(),arc->getParc()->getDestination()->getIds());
        this->removeItem(item);
        for(int i=0;i<items().size();i++) items().at(i)->update();
//       delete item;
    }
}

QSommet* QGraphe::getQSommet(int id)
{
    foreach(QGraphicsItem* item,items())
        {
        if(item->type()== QSommet::Type)
            {
             if(qgraphicsitem_cast<QSommet *>(item)->getPsommet()->getIds()==id)
                 return qgraphicsitem_cast<QSommet*>(item);
            }
        }
    return NULL;
}

QArc *QGraphe::getQArc(int id)
{
    for(int i=0;i<this->items().size();i++)
        {
        if(items().at(i)->type()== QArc::Type)
            {
             if(qgraphicsitem_cast<QArc *>(items().at(i))->getParc()->getIda()==id)
                 return qgraphicsitem_cast<QArc*>(items().at(i));
            }
        }
    return NULL;
}

void QGraphe::AjouterQArc(QSommet *a, QSommet *b)
{
   if( graph->existeArc(*a->getPsommet(),*b->getPsommet())) return;
    QArc *p=new QArc(a,b);
    p->setAffiche_nom(affiche_nom_arc);
    p->setAffiche_val(affiche_val_arc);
    p->setZValue(-100);
    this->addItem(p);
    graph->ajouterArc(a->getPsommet()->getIds(),b->getPsommet()->getIds());
    p->setParc(graph->getArc(a->getPsommet()->getIds(),b->getPsommet()->getIds()));
qDebug() << Q_FUNC_INFO << "Arc ajouter=" << graph->existeArc(a->getPsommet()->getIds(),b->getPsommet()->getIds());
}

void QGraphe::AjouterQSommet(QPointF p)
{
    QSommet* s=new QSommet(p) ;
    this->addItem(s);
    s->setAffiche_nom(affiche_nom_sommet);
    s->setAffiche_val(affiche_val_sommet);
    double tab[3];
    tab[0] = 0;
    tab[1] = 0;
    tab[2] = 0;
    Point p1;
    p1._abs = p.x();
    p1._ord = p.y();
    graph->ajouterSommet("SN",graph->getCompteurS(), true, tab, p1);
    s->setPsommet(graph->getSommet(graph->getCompteurS()-1));
    s->setId(graph->getCompteurS()-1);
    qDebug() << Q_FUNC_INFO << "matrice =" << Sommet::nbSommet();
}

void QGraphe::AfficherGrapheChargement(Graphe *g)
{
    QPointF p;
    int compteur =  g->getCompteurS();

    for(int i = 0; i < compteur; i++){
        p.setX(g->getSommet(i)->getAbscisse());
        p.setY(g->getSommet(i)->getOrdonnee());
                QSommet *s = new QSommet(p);
                s->setAffiche_nom(affiche_nom_sommet);
                s->setAffiche_val(affiche_val_sommet);
                s->setPsommet(g->getSommet(i));
                s->setId(g->getSommet(i)->getIds());
                this->addItem(s);
                qDebug() << Q_FUNC_INFO << "sommet ajoute  =" <<i;

    }
    for(int i = 0; i < compteur; i++){
        for(int j = i+1; j < compteur; j++){
            if(g->existeArc(i, j)){
                QArc *p=new QArc(this->getQSommet(i), this->getQSommet(j));
                p->setZValue(-100);
                this->addItem(p);
                p->setParc(graph->getArc(i,j));
                qDebug() << Q_FUNC_INFO << "arc de  =" <<i <<j;
            }
            if(g->existeArc(j, i)){
                QArc *p=new QArc(this->getQSommet(j), this->getQSommet(i));
                p->setZValue(-100);
                this->addItem(p);
                p->setParc(graph->getArc(j,i));
                qDebug() << Q_FUNC_INFO << "arc de  =" <<j<<i;

            }
        }
    }
}

void QGraphe::supprimertout()
{
    foreach (QGraphicsItem *item, items()) {
        if(item->type()==QArc::Type)  {
        supprimerQObjet(item);
    }
}
    foreach (QGraphicsItem *item, items()) {
        if(item->type()==QSommet::Type)  {
        supprimerQObjet(item);
    }
}

    foreach (QGraphicsItem *item, items()) {
       delete item;
    }

}
