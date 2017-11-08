#include "utils.hpp"

#include "classes.hpp"

#include <QPainter>
#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsScene>


void Utils::drawRectForClass(QPainter& painter, const Classes& c, const QRect& rect)
{
    painter.save();
    painter.setPen(Qt::NoPen);
    auto color = c.color();
    // color.setAlpha(100);
    // painter.setBrush(QBrush(color, Qt::SolidPattern));
    // painter.drawRect(rect);
    // color.setAlpha(200);
    // painter.setBrush(QBrush(color, Qt::DiagCrossPattern));
    // painter.drawRect(rect);

    color.setAlpha(150);
    painter.setBrush(color);
    painter.drawRect(rect);

    painter.restore();
}


void Utils::drawRectForClass(AnnotatorScene *annotatorscene, const Classes &c, const QRect &rect)
{
       auto color = c.color();
       color.setAlpha(150);
       annotatorscene->addRect(rect,QPen(QColor(255,0,0)),QBrush(color));
}

void Utils::preColorLayout(AnnotatorScene *annotateur,ColorLayout *colorlayout)
{
    int block_width = AnnotatorScene::c_image_resolution.width()/AnnotatorScene::c_annotation_resolution.width();
    int block_height = AnnotatorScene::c_image_resolution.height()/AnnotatorScene::c_annotation_resolution.height();

    // Bulle initialization
    for (int y = 0; y< AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
           QGraphicsRectItem *rect = annotateur->addRect(x*block_width,y*block_height,block_width,block_height,QPen(QColor(255,0,0)),QBrush((Classes::c_color).at(0)));
           colorlayout->Bulle.append(rect);
           rect->setVisible(false);

        }
    }
    colorlayout->TotalList.append(colorlayout->Bulle);

    // Tassement initialization
    for (int y = 0; y< AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
           QGraphicsRectItem *rect = annotateur->addRect(x*block_width,y*block_height,block_width,block_height,QPen(QColor(255,0,0)),QBrush((Classes::c_color).at(1)));
           colorlayout->Tassement.append(rect);
           rect->setVisible(false);
        }
    }
    colorlayout->TotalList.append(colorlayout->Tassement);

    // Coalescence initialization
    for (int y = 0; y< AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
           QGraphicsRectItem *rect = annotateur->addRect(x*block_width,y*block_height,block_width,block_height,QPen(QColor(255,0,0)),QBrush((Classes::c_color).at(2)));
           colorlayout->Coalescene.append(rect);
           rect->setVisible(false);
        }
    }
    colorlayout->TotalList.append(colorlayout->Coalescene);

    // Polydispersite initialization
    for (int y = 0; y< AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
           QGraphicsRectItem *rect = annotateur->addRect(x*block_width,y*block_height,block_width,block_height,QPen(QColor(255,0,0)),QBrush((Classes::c_color).at(3)));
           colorlayout->Polydispersite.append(rect);
           rect->setVisible(false);
        }
    }
    colorlayout->TotalList.append(colorlayout->Polydispersite);

    // Region Claire initialisation
    for (int y = 0; y< AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
           QGraphicsRectItem *rect = annotateur->addRect(x*block_width,y*block_height,block_width,block_height,QPen(QColor(255,0,0)),QBrush((Classes::c_color).at(4)));
           colorlayout->RegionClaire.append(rect);
           rect->setVisible(false);
        }
    }
    colorlayout->TotalList.append(colorlayout->RegionClaire);

    // Inhomogenite initialisation
    for (int y = 0; y< AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
           QGraphicsRectItem *rect = annotateur->addRect(x*block_width,y*block_height,block_width,block_height,QPen(QColor(255,0,0)),QBrush((Classes::c_color).at(5)));
           colorlayout->Inhomogenite.append(rect);
           rect->setVisible(false);
        }
    }
    colorlayout->TotalList.append(colorlayout->Inhomogenite);

    //Mouillage initialisation
    for (int y = 0; y< AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
           QGraphicsRectItem *rect = annotateur->addRect(x*block_width,y*block_height,block_width,block_height,QPen(QColor(255,0,0)),QBrush((Classes::c_color).at(6)));
           colorlayout->Mouillage.append(rect);
           rect->setVisible(false);
        }
    }
    colorlayout->TotalList.append(colorlayout->Mouillage);



   // Goutte demouille initialization

    for (int y = 0; y< AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
           QGraphicsRectItem *rect = annotateur->addRect(x*block_width,y*block_height,block_width,block_height,QPen(QColor(255,0,0)),QBrush((Classes::c_color).at(7)));
           colorlayout->GoutteDemouille.append(rect);
           rect->setVisible(false);
        }
    }
    colorlayout->TotalList.append(colorlayout->GoutteDemouille);



}
