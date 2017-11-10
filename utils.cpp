#include "utils.hpp"

#include "classes.hpp"

#include <QPainter>
#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsScene>

#define TOTAL_TYPE 18


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

     // RAS initialisation
    for (int y = 0; y< AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
           QGraphicsRectItem *rect = annotateur->addRect(x*block_width,y*block_height,block_width,block_height,QPen(QColor(255,0,0)),QBrush(QColor(255,255,255,100)));
           colorlayout->RAS.append(rect);
           rect->setVisible(false);

        }
    }

    //initialization
    for (int y = 0; y< AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {

            for(int i = 0; i<TOTAL_TYPE;i++)
            {
              QGraphicsRectItem *rect = annotateur->addRect(x*block_width,y*block_height,block_width,block_height,QPen(QColor(255,0,0)),QBrush((Classes::c_color).at(i)));
              switch (i) {
              case 0:
                  colorlayout->Bulle.append(rect);
                  break;
              case 1:
                  colorlayout->Tassement.append(rect);
                  break;
              case 2:
                  colorlayout->Coalescene.append(rect);
                  break;
              case 3:
                  colorlayout->Polydispersite.append(rect);
                  break;
              case 4:
                  colorlayout->RegionClaire.append(rect);
                  break;
              case 5:
                  colorlayout->Inhomogenite.append(rect);
                  break;
              case 6:
                  colorlayout->Mouillage.append(rect);
                  break;
              case 7:
                  colorlayout->GoutteDemouille.append(rect);
                  break;
              case 8:
                  colorlayout->RegionSombre.append(rect);
                  break;
              case 9:
                  colorlayout->GoutteColle.append(rect);
                  break;
              case 10:
                  colorlayout->Muraille.append(rect);
                  break;
              case 11:
                  colorlayout->TraceTs.append(rect);
                  break;
              case 12:
                  colorlayout->InjecteurBouche.append(rect);
                  break;
              case 13:
                  colorlayout->Precipite.append(rect);
                  break;
              case 14:
                  colorlayout->Dedoublement.append(rect);
                  break;
              case 15:
                  colorlayout->OutOfFocus.append(rect);
                  break;
              case 16:
                  colorlayout->Autres.append(rect);
                  break;
              case 17:
                  colorlayout->ArtefactGeneral.append(rect);
                  break;
              default:
                  break;
              }

              rect->setVisible(false);
            }
        }
    }

colorlayout->TotalList.append(colorlayout->Bulle);
colorlayout->TotalList.append(colorlayout->Tassement);
colorlayout->TotalList.append(colorlayout->Coalescene);
colorlayout->TotalList.append(colorlayout->Polydispersite);
colorlayout->TotalList.append(colorlayout->RegionClaire);
colorlayout->TotalList.append(colorlayout->Inhomogenite);
colorlayout->TotalList.append(colorlayout->Mouillage);
colorlayout->TotalList.append(colorlayout->GoutteDemouille);
colorlayout->TotalList.append(colorlayout->RegionSombre);
colorlayout->TotalList.append(colorlayout->GoutteColle);
colorlayout->TotalList.append(colorlayout->Muraille);
colorlayout->TotalList.append(colorlayout->TraceTs);
colorlayout->TotalList.append(colorlayout->InjecteurBouche);
colorlayout->TotalList.append(colorlayout->Precipite);
colorlayout->TotalList.append(colorlayout->Dedoublement);
colorlayout->TotalList.append(colorlayout->OutOfFocus);
colorlayout->TotalList.append(colorlayout->Autres);
colorlayout->TotalList.append(colorlayout->ArtefactGeneral);

}


