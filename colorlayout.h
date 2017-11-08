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

    QList<QGraphicsItem *> Bulle;
    QList<QGraphicsItem *> Tassement;
    QList<QGraphicsItem *> Coalescene;
    QList<QGraphicsItem *> Polydispersite;
    QList<QGraphicsItem *> RegionClaire;
    QList<QGraphicsItem *> Inhomogenite;
    QList<QGraphicsItem *> Mouillage;
    QList<QGraphicsItem *> GoutteDemouille ;

    QList<QList<QGraphicsItem *>> TotalList;







};








#endif // COLORLAYOUT_H
