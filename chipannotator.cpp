#include "chipannotator.h"

#include <QStatusBar>


#include <QCloseEvent>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPointF>
#include <QDebug>
#include <QString>
#include <QDataStream>
#include <QList>

#define TOTAL_TYPE 18



ChipAnnotator::ChipAnnotator(QWidget* parent)
{
   setAnnotatorScene();
   setAnnotatorView();
   layout = new QHBoxLayout;
   layout->addWidget(annotaview);


   colorlayout = new ColorLayout;
   Utils::preColorLayout(annotateur,colorlayout);

   mouseActionControle();


   //connect(annotateur, &MainWindow::modified, this, &MainWindow::onAnnotationModified);

   prePaintGrid();


   connect (annotateur,&AnnotatorScene::gridOn,this,&ChipAnnotator::PaintGrid);
   connect(annotateur,&AnnotatorScene::annotationSignal,this,&ChipAnnotator::showAnnotation);


}


void ChipAnnotator::setAnnotatorScene()
{
    annotateur = new AnnotatorScene;
    annotateur->setSceneRect(QRectF(0, 0, 800, 564));

}


void ChipAnnotator::setAnnotatorView()
{
    annotaview = new AnnotatorView(annotateur);
    annotaview->fitInView(0,0,800,564);
    annotaview->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

}

void ChipAnnotator::mouseActionControle()
{
    connect(annotaview,&AnnotatorView::mouseMoveSignal,this,&ChipAnnotator::mouseMoveFunction);
    connect(annotaview,&AnnotatorView::mousePressSignal,this,&ChipAnnotator::mousePressFunction);
    connect(annotaview,&AnnotatorView::mouseReleaseSignal,this,&ChipAnnotator::mouseReleaseFunction);
    connect(annotaview,&AnnotatorView::leaveView,this,&ChipAnnotator::leaveViewFunction);

}

void ChipAnnotator::mouseMoveFunction( boost::optional<AnnotatorScene::Region> m_current_region)
{

    if (annotateur->m_current_class ==0)
    {
        if((m_current_region->x()< AnnotatorScene::c_annotation_resolution.width())&&(m_current_region->x()>0)&& (m_current_region->y()> 0)&& (m_current_region->y()< AnnotatorScene::c_annotation_resolution.height()))
        {
            colorlayout->RAS.at(annotaview->m_previous_region->y()* annotateur->m_result->width()+annotaview->m_previous_region->x())->setVisible(false);
            colorlayout->RAS.at(m_current_region->y()* annotateur->m_result->width()+m_current_region->x())->setVisible(true);
            //showRectType(m_current_region);
            annotaview->m_previous_region = m_current_region;
        }
    }

     if(annotaview->m_current_button_pressed)
        processClick(*m_current_region);
    update();
}

void ChipAnnotator::mousePressFunction(AnnotatorScene::Region mousePressPos)
{
    processClick(mousePressPos);
}

void ChipAnnotator::mouseReleaseFunction(AnnotatorScene::Region mouseReleasePos)
{
    processClick(mouseReleasePos);
}

void ChipAnnotator::leaveViewFunction()
{
     colorlayout->RAS.at(annotaview->m_previous_region->y()* annotateur->m_result->width()+annotaview->m_previous_region->x())->setVisible(false);
}

void ChipAnnotator::processClick(const AnnotatorScene::Region& pos)
{

    colorlayout->RAS.at(annotaview->m_previous_region->y()* annotateur->m_result->width()+annotaview->m_previous_region->x())->setVisible(false);
    assert(annotaview->m_current_button_pressed);
    switch(*annotaview->m_current_button_pressed)
    {
    case AnnotatorView::Button::Left:
        tagRegion(pos);
        return;
    case AnnotatorView::Button::Right:
        tagRegion(pos, 0);
        return;
        /*
    case Button::Wheel:
        const auto class_id = classAtPosition(*m_current_region);
        emit selectClass(class_id);
        return;
        */
    }
}

void ChipAnnotator::tagRegion(const AnnotatorScene::Region& region, boost::optional<quint8> classes)
{
    if(!classes)
    {  classes = annotateur->m_current_class;
       if(region.x() >= 0 && region.x() < annotateur->m_result->width() && region.y() >= 0 && region.y() < annotateur->m_result->height())
       {
         if (*classes !=0)
         {for (int i= 0 ;i<*classes-1;i++)
              colorlayout->TotalList.at(i).at(region.y()* annotateur->m_result->width()+region.x())->setVisible(false);
         for (int j= *classes;j<TOTAL_TYPE;j++)
             colorlayout->TotalList.at(j).at(region.y()* annotateur->m_result->width()+region.x())->setVisible(false);

        colorlayout->TotalList.at(*classes-1).at(region.y()* annotateur->m_result->width()+region.x())->setVisible(true);
        emit modified();
         }
       }

    }
    else
    {
        if(region.x() >= 0 && region.x() < annotateur->m_result->width() && region.y() >= 0 && region.y() < annotateur->m_result->height())
       {
           for (int k = 0; k<TOTAL_TYPE;k++)
               colorlayout->TotalList.at(k).at(region.y()* annotateur->m_result->width()+region.x())->setVisible(false);
           emit modified();

        }
    }

}


void ChipAnnotator::showAnnotation(bool m_display_annotation)
{
    int RectIndex;
    if(m_display_annotation)
    {
    QFile file("temp.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    for(int y=0;y<AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for(int x=0;x<AnnotatorScene::c_annotation_resolution.width();x++)
        {
            RectIndex =0;
            for (int i = 0; i<TOTAL_TYPE; i++)
            {
                bool ifvisible=colorlayout->TotalList.at(i).at(y*annotateur->c_annotation_resolution.width()+x)->isVisible();
                if(ifvisible)
                {RectIndex = i+1;
                 colorlayout->TotalList.at(i).at(y*annotateur->c_annotation_resolution.width()+x)->setVisible(false);
                }
             }
            out <<QString("x");
            out<<(qint32)x;
            out<<QString("y");
            out<<(qint32)y;
            out<<QString("RectType");
            out<<RectIndex;
        }

    }

    file.close();

    }
    else
    {
        QFile file("temp.dat");
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        QString str_x,str_y,str_rectindex;
        qint32 rectindex;

        for(qint32 y=0;y<AnnotatorScene::c_annotation_resolution.height();y++)
        {
            for(qint32 x=0;x<AnnotatorScene::c_annotation_resolution.width();x++)
            {
                in>>str_x>>x>>str_y>>y>>str_rectindex>>rectindex;
                if(rectindex!=0)
                    colorlayout->TotalList.at(rectindex-1).at(y*annotateur->c_annotation_resolution.width()+x)->setVisible(true);

           }

        }
        file.close();
    }

}



void ChipAnnotator::displayGrid()
{
    for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        horizonLine_List.at(x)->setVisible(true);
    for (int y = 0; y < AnnotatorScene::c_annotation_resolution.height();y++)
        verticalLine_List.at(y)->setVisible(true);

}

void ChipAnnotator::prePaintGrid()
{
    int block_width = AnnotatorScene::c_image_resolution.width()/AnnotatorScene::c_annotation_resolution.width();
    int block_height = AnnotatorScene::c_image_resolution.height()/AnnotatorScene::c_annotation_resolution.height();


        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
              QGraphicsLineItem *horizon_line = annotateur->addLine((x+1)*block_width,0,(x+1)*block_width,AnnotatorScene::c_image_resolution.height(),QPen(QColor(255,0,0)));
              horizonLine_List.append(horizon_line);
              horizon_line->setVisible(false);

        }

        for (int y = 0; y < AnnotatorScene::c_annotation_resolution.height();y++)
        {
             QGraphicsLineItem *vertical_line = annotateur->addLine(0,(y+1)*block_height,AnnotatorScene::c_image_resolution.width(),(y+1)*block_height,QPen(QColor(255,0,0)));
             verticalLine_List.append(vertical_line);
             vertical_line->setVisible(false);

        }

}

void ChipAnnotator::Reset()
{

    for(int y=0;y<AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for(int x=0;x<AnnotatorScene::c_annotation_resolution.width();x++)
        {

            for (int i = 0; i<TOTAL_TYPE; i++)
            {
                 colorlayout->TotalList.at(i).at(y*annotateur->c_annotation_resolution.width()+x)->setVisible(false);
             }
        }
    }
}

bool ChipAnnotator::hasImagesLoaded() const
{
    return annotateur->m_images.size() == 3 && !annotateur->m_images.front().isNull();
}

quint8 ChipAnnotator::classAtPosition(const AnnotatorScene::Region& pos) const
{
    return qRed(annotateur->m_result->toImage().pixel(pos.x(), pos.y()));
    ;
}

void ChipAnnotator::PaintGrid(bool m_display_grid)
{

         for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
             horizonLine_List.at(x)->setVisible(!m_display_grid);
         for (int y = 0; y < AnnotatorScene::c_annotation_resolution.height();y++)
             verticalLine_List.at(y)->setVisible(!m_display_grid);

    update();
}


void ChipAnnotator::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = annotaview->matrix();
    annotaview->resetMatrix();
    annotaview->translate(oldMatrix.dx(), oldMatrix.dy());
    annotaview->scale(newScale, newScale);
}







