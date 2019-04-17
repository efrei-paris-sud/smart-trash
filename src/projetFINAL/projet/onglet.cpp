#include "onglet.h"

onglet::onglet()
{
    layout = new QGridLayout;
    scene=new QGraphe(this);//Initialisation D'une Scene Pour La Fenetre De Visualisation
    scene->setSceneRect(0,0,10000,10000);
    vue=new QGraphicsView(scene,this);//Initialisation De La Vue Pour La Fenetre De Visualisation
    vue->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//Barre De Defilement Horizontale
    vue->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//Barre De Defilement Verticale
    vue->setSceneRect(0,0,10000,10000);
    vue->setMouseTracking(true);
    vue->setRenderHints(QPainter::Antialiasing);
    layout->addWidget(vue);
    this->setLayout(layout);
//    vue->setDragMode(QGraphicsView::ScrollHandDrag);
}

onglet::~onglet()
{
    cout<<"dectruction onglet : Qgraph et vue\n";
    delete this->scene;
    delete this->vue;
}
