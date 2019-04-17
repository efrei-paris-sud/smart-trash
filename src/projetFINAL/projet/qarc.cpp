#include "qarc.h"
#include "qsommet.h"
#include <math.h>
#include <QPainter>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

//! [0]
QArc::QArc(QSommet *sourceNode, QSommet *destNode)
    : arrowSize(10)
{
    source = sourceNode;
    dest = destNode;
    source->ajouterQArc(this);
    dest->ajouterQArc(this);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setCacheMode(DeviceCoordinateCache);
    adjust();
    affiche_nom=false;
    affiche_val=false;
    affiche_val2=false;
}
//! [0]

//! [1]
QSommet *QArc::sourceNode() const
{
    return source;
}

QSommet *QArc::destNode() const
{
    return dest;
}
//! [1]

//! [2]
void QArc::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}
//! [2]

//! [3]
QRectF QArc::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 50;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}
//! [3

QPainterPath QArc::shape() const{

    QPainterPath path;
    QPolygonF polygon;
    QPointF p1,p2,p3,p4;
    int h=20;
    p1.setX(sourcePoint.x());
    p3.setX(destPoint.x());
    p4.setX(destPoint.x());
    p2.setX(sourcePoint.x());
    p1.setY(sourcePoint.y()-h);
    p2.setY(sourcePoint.y()+h);
    p3.setY(destPoint.y()-h);
    p4.setY(destPoint.y()+h);

    if(abs(sourcePoint.x()-destPoint.x())<30){
    p1.setX(sourcePoint.x()-h);
    p2.setX(sourcePoint.x()+h);
    p3.setX(destPoint.x()-h);
    p4.setX(destPoint.x()+h);

    p1.setY(sourcePoint.y());
    p2.setY(sourcePoint.y());
    p3.setY(destPoint.y());
    p4.setY(destPoint.y());
}
        polygon << p1;
        polygon << p2;
        polygon << p4;
        polygon << p3;
        path.addPolygon(polygon);
        return path;
}
//! [4]
void QArc::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;
//! [4]

//! [5]
    // Draw the line itself
    QColor couleur (parc->getColorR(),parc->getColorG(),parc->getColorB(),255);
    painter->setPen(QPen(couleur, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    if(this->isSelected()) {

        painter->setPen(Qt::green);
        painter->drawLine(line);
    }
//! [5]

//! [6]
    // Draw the arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;

    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                              cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                              cos(angle - Pi + Pi / 3) * arrowSize);

    painter->setBrush(couleur);
    QFont police;
    police.setPointSize(15);
    painter->setFont(police);
   painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
   QPointF p= destPoint+sourcePoint;
   p.setX(p.x()/2);
   p.setY(p.y()/2);

   QPointF v= destPoint+sourcePoint;
   v.setX(p.x());
   v.setY(p.y()+20);


 if(affiche_nom==true) painter->drawText(p,QString::fromStdString(this->getParc()->getNom()));

 if(affiche_val && affiche_val2)
     painter->drawText(v,QString::number(this->getParc()->getVal1())+"/"+QString::number(this->getParc()->getVal2()));
 else if(affiche_val)
      painter->drawText(v,QString::number(this->getParc()->getVal1()));
 else if(affiche_val2)
      painter->drawText(v,QString::number(this->getParc()->getVal2()));
}

bool QArc::getAffiche_val2() const
{
    return affiche_val2;
}

void QArc::setAffiche_val2(bool value)
{
    affiche_val2 = value;
}

bool QArc::getAffiche_val() const
{
    return affiche_val;
}

void QArc::setAffiche_val(bool value)
{
    affiche_val = value;
}

bool QArc::getAffiche_nom() const
{
    return affiche_nom;
}

void QArc::setAffiche_nom(bool value)
{
    affiche_nom = value;
}

void QArc::setParc(Arc *value)
{
    parc = value;
}

Arc *QArc::getParc() const
{
    return parc;
}
//! [6]

 QArc::~QArc()
{

}
