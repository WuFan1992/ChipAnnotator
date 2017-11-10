#ifndef COLORLAYOUT_H
#define COLORLAYOUT_H

#include <QList>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "annotatorscene.h"


class AnnotatorScene;

class ColorLayout
{

public:
    ColorLayout();

    QList<QGraphicsItem *> RAS;
    QList<QGraphicsItem *> Bulle;
    QList<QGraphicsItem *> Tassement;
    QList<QGraphicsItem *> Coalescene;
    QList<QGraphicsItem *> Polydispersite;
    QList<QGraphicsItem *> RegionClaire;
    QList<QGraphicsItem *> Inhomogenite;
    QList<QGraphicsItem *> Mouillage;
    QList<QGraphicsItem *> GoutteDemouille ;
    QList<QGraphicsItem *> RegionSombre;
    QList<QGraphicsItem *> GoutteColle;
    QList<QGraphicsItem *> Muraille;
    QList<QGraphicsItem *> TraceTs;
    QList<QGraphicsItem *> InjecteurBouche;
    QList<QGraphicsItem *> Precipite;
    QList<QGraphicsItem *> Dedoublement;
    QList<QGraphicsItem *> OutOfFocus;
    QList<QGraphicsItem *> Autres ;
    QList<QGraphicsItem *> ArtefactGeneral ;


    QList<QList<QGraphicsItem *>> TotalList;







};








#endif // COLORLAYOUT_H
