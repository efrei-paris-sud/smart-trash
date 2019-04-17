#include "qsommet.h"
#include "qarc.h"

QSommet::QSommet()
{
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
//    setZValue(-1);
    setFlags(QGraphicsItem::ItemIsSelectable|
                 QGraphicsItem::ItemIsMovable);
    affiche_nom=false;
    affiche_val=false;

}


QSommet::QSommet(QPointF p)
{
    setFlags(QGraphicsItem::ItemIsSelectable|
                 QGraphicsItem::ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
//    setZValue(-1);
    setPos(p);
    affiche_nom=false;
    affiche_val=false;

}

void QSommet::ajouterQArc(QArc *edge)
{
    QArcList << edge;
    edge->adjust();
}

QVector<QArc *> QSommet::arc() const
{
    return QArcList;
}


//! [8]
QRectF QSommet::boundingRect() const
{
    return QRectF( -30, -20, 200 ,50);

}
//! [8]

//! [9]
QPainterPath QSommet::shape() const
{
    QPainterPath path;
        path.addEllipse(-10, -10, 20, 20);
        return path;
}
//! [9]

//! [10]
void QSommet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    QColor couleur(psommet->getColorR(),psommet->getColorG(),psommet->getColorB(),255);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);

    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, couleur.light(120));
        gradient.setColorAt(0, couleur.light(100));

    } else {

  gradient.setColorAt(1, couleur);
  gradient.setColorAt(0, couleur);
    }


    if(this->isSelected()){
        gradient.setColorAt(1, QColor(Qt::red).light(120));
        gradient.setColorAt(0, QColor(Qt::darkRed).light(120));
    }

    if(ancien==true){
        gradient.setColorAt(1, QColor(Qt::blue).light(120));
        gradient.setColorAt(0, QColor(Qt::darkBlue).light(120));
    }

    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::white, 0));
    painter->drawEllipse(-10, -10, 20, 20);
    painter->setPen(QPen(Qt::black, 10/* épaisseur */));
    painter->drawText(-6,6, QString::number(this->getPsommet()->getIds()));
    painter->setPen(QPen(Qt::white, 10/* épaisseur */));

 if(affiche_nom==true) painter->drawText(-28,24, QString::fromStdString(this->getPsommet()->getNom()));
 if(affiche_val==true) painter->drawText(-28,-10, QString::number(this->getPsommet()->getVal1()));
 if(affiche_val2==true) painter->drawText(-28,-10, QString::number(this->getPsommet()->getVal2()));
 else if(affiche_val2==true && affiche_val==true) painter->drawText(-28,-10, QString::number(this->getPsommet()->getVal1())+" "+ QString::number(this->getPsommet()->getVal2()));
 if(affiche_val3==true) painter->drawText(-28,-10, QString::number(this->getPsommet()->getVal1())+"/"+QString::number(this->getPsommet()->getVal2())+"/"+QString::number(this->getPsommet()->getVal3()));

}
//! [10]

//! [11]
QVariant QSommet::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
         foreach (QArc *qarc, QArcList){
            qarc->adjust();
       }
        break;

    default:
        break;
    };
    return QGraphicsItem::itemChange(change, value);
}

bool QSommet::getAffiche_val3() const
{
    return affiche_val3;
}

void QSommet::setAffiche_val3(bool value)
{
    affiche_val3 = value;
}

bool QSommet::getAncien() const
{
    return ancien;
}

void QSommet::setAncien(bool value)
{
    ancien = value;
}

bool QSommet::getAffiche_val2() const
{
    return affiche_val2;
}

void QSommet::setAffiche_val2(bool value)
{
    affiche_val2 = value;
}

bool QSommet::getAffiche_val() const
{
    return affiche_val;
}

void QSommet::setAffiche_val(bool value)
{
    affiche_val = value;
}

bool QSommet::getAffiche_nom() const
{
    return affiche_nom;
}

void QSommet::setAffiche_nom(bool value)
{
    affiche_nom = value;
}

Sommet *QSommet::getPsommet() const
{
    return psommet;
}

void QSommet::setPsommet(Sommet *value)
{
    psommet = value;
}

int QSommet::getId() const
{
    return id;
}

void QSommet::setId(int value)
{
    id = value;
}
//! [12]

void QSommet::supprimerQArcs()
{
    qDebug() << "supprimer QArc sommet "<< this->getPsommet()->getIds();

    foreach (QArc *arrow, QArcList) {
        if(arrow->sourceNode()!=NULL) arrow->sourceNode()->supprimerQArc(arrow);
        if(arrow->destNode()!=NULL)   arrow->destNode()->supprimerQArc(arrow);
        scene()->removeItem(arrow);
//        delete arrow;
    }
}

void QSommet::supprimerQArc(QArc *arrow)
{

    int index = QArcList.indexOf(arrow);
    if (index != -1)
        QArcList.remove(index);
}

