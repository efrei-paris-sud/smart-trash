#ifndef ONGLET_H
#define ONGLET_H

#include <QObject>
#include <QWidget>
#include "qgraphe.h"
#include <QTabWidget>

class onglet : public QWidget
{
friend class Interface;
public:
    onglet();
    ~onglet();//Destructeur


private:
    QGraphicsView *vue;
    QGraphe *scene;
    QLayout *layout;

};

#endif // ONGLET_H
