#ifndef QSOMMET_H
#define QSOMMET_H
#include "qgraphe.h"
#include "qarc.h"
#include <QPainter>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QList>
#include <QPoint>

class QSommet : public QGraphicsItem
{
public:
    QSommet();
    QSommet(QPointF p);

    void ajouterQArc(QArc *edge);
    QVector<QArc *> arc() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }
    void supprimerQArcs();
    void supprimerQArc(QArc *arrow);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int getId() const;
    void setId(int value);

    Sommet *getPsommet() const;
    void setPsommet(Sommet *value);

    bool getAffiche_nom() const;
    void setAffiche_nom(bool value);

    bool getAffiche_val() const;
    void setAffiche_val(bool value);

    bool getAffiche_val2() const;
    void setAffiche_val2(bool value);

    bool getAncien() const;
    void setAncien(bool value);

    bool getAffiche_val3() const;
    void setAffiche_val3(bool value);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    QVector<QArc *> QArcList;
    int id;
    Sommet *psommet;
    bool affiche_nom;
    bool affiche_val;
    bool affiche_val2=false;
    bool affiche_val3=false;
    bool ancien=false;

};

#endif // QSOMMET_H
