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
   layout->addWidget(m_annotaview);


   m_colorlayout = new ColorLayout;
   Utils::preColorLayout(m_annotateur,m_colorlayout);

   mouseActionControle();


   //connect(m_annotateur, &MainWindow::modified, this, &MainWindow::onAnnotationModified);

   prePaintGrid();

   connect (m_annotateur,&AnnotatorScene::gridOn,this,&ChipAnnotator::PaintGrid);
   connect(m_annotateur,&AnnotatorScene::annotationSignal,this,&ChipAnnotator::showAnnotation);


}


void ChipAnnotator::setAnnotatorScene()
{
    m_annotateur = new AnnotatorScene;
    m_annotateur->setSceneRect(QRectF(0, 0, 800, 564));

}


void ChipAnnotator::setAnnotatorView()
{
    m_annotaview = new AnnotatorView(m_annotateur);
    m_annotaview->fitInView(0,0,800,564);
    m_annotaview->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

}

void ChipAnnotator::mouseActionControle()
{
    connect(m_annotaview,&AnnotatorView::mouseMoveSignal,this,&ChipAnnotator::mouseMoveFunction);
    connect(m_annotaview,&AnnotatorView::mousePressSignal,this,&ChipAnnotator::mousePressFunction);
    connect(m_annotaview,&AnnotatorView::mouseReleaseSignal,this,&ChipAnnotator::mouseReleaseFunction);
    connect(m_annotaview,&AnnotatorView::leaveView,this,&ChipAnnotator::leaveViewFunction);

}

void ChipAnnotator::mouseMoveFunction( boost::optional<AnnotatorScene::Region> m_current_region)
{

    if (m_annotateur->m_current_class ==0)
    {
        if((m_current_region->x()< AnnotatorScene::c_annotation_resolution.width())&&(m_current_region->x()>0)&& (m_current_region->y()> 0)&& (m_current_region->y()< AnnotatorScene::c_annotation_resolution.height()))
        {
            m_colorlayout->RAS.at(m_annotaview->m_previous_region->y()* m_annotateur->m_result->width()+m_annotaview->m_previous_region->x())->setVisible(false);
            m_colorlayout->RAS.at(m_current_region->y()* m_annotateur->m_result->width()+m_current_region->x())->setVisible(true);
            showRectType(m_current_region);
            m_annotaview->m_previous_region = m_current_region;
        }
    }

     if(m_annotaview->m_current_button_pressed)
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
     m_colorlayout->RAS.at(m_annotaview->m_previous_region->y()* m_annotateur->m_result->width()+m_annotaview->m_previous_region->x())->setVisible(false);
}

void ChipAnnotator::processClick(const AnnotatorScene::Region& pos)
{

    m_colorlayout->RAS.at(m_annotaview->m_previous_region->y()* m_annotateur->m_result->width()+m_annotaview->m_previous_region->x())->setVisible(false);
    assert(m_annotaview->m_current_button_pressed);
    switch(*m_annotaview->m_current_button_pressed)
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
    {  classes = m_annotateur->m_current_class;
       if(region.x() >= 0 && region.x() < m_annotateur->m_result->width() && region.y() >= 0 && region.y() < m_annotateur->m_result->height())
       {
         if (*classes !=0)
         {for (int i= 0 ;i<*classes-1;i++)
              m_colorlayout->TotalList.at(i).at(region.y()* m_annotateur->m_result->width()+region.x())->setVisible(false);
         for (int j= *classes;j<TOTAL_TYPE;j++)
             m_colorlayout->TotalList.at(j).at(region.y()* m_annotateur->m_result->width()+region.x())->setVisible(false);

        m_colorlayout->TotalList.at(*classes-1).at(region.y()* m_annotateur->m_result->width()+region.x())->setVisible(true);
        emit modified();
         }
       }

    }
    else
    {
        if(region.x() >= 0 && region.x() < m_annotateur->m_result->width() && region.y() >= 0 && region.y() < m_annotateur->m_result->height())
       {
           for (int k = 0; k<TOTAL_TYPE;k++)
               m_colorlayout->TotalList.at(k).at(region.y()* m_annotateur->m_result->width()+region.x())->setVisible(false);
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
                bool ifvisible=m_colorlayout->TotalList.at(i).at(y*m_annotateur->c_annotation_resolution.width()+x)->isVisible();
                if(ifvisible)
                {RectIndex = i+1;
                 m_colorlayout->TotalList.at(i).at(y*m_annotateur->c_annotation_resolution.width()+x)->setVisible(false);
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
                    m_colorlayout->TotalList.at(rectindex-1).at(y*m_annotateur->c_annotation_resolution.width()+x)->setVisible(true);

           }

        }
        file.close();
    }

}

void ChipAnnotator::displayAnnotation(QString &annoation)
{

    if(!annoation.isEmpty())
    {
        auto output_file_path = annoation;
        QFile file(output_file_path);
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
                    m_colorlayout->TotalList.at(rectindex-1).at(y*m_annotateur->c_annotation_resolution.width()+x)->setVisible(true);

            }
        }

    }

}


void ChipAnnotator::displayGrid()
{
    for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        m_horizonline_list.at(x)->setVisible(true);
    for (int y = 0; y < AnnotatorScene::c_annotation_resolution.height();y++)
        m_verticalline_list.at(y)->setVisible(true);

}

void ChipAnnotator::prePaintGrid()
{
    int block_width = AnnotatorScene::c_image_resolution.width()/AnnotatorScene::c_annotation_resolution.width();
    int block_height = AnnotatorScene::c_image_resolution.height()/AnnotatorScene::c_annotation_resolution.height();


        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
              QGraphicsLineItem *horizon_line = m_annotateur->addLine((x+1)*block_width,0,(x+1)*block_width,AnnotatorScene::c_image_resolution.height(),QPen(QColor(255,0,0)));
              m_horizonline_list.append(horizon_line);
              horizon_line->setVisible(false);

        }

        for (int y = 0; y < AnnotatorScene::c_annotation_resolution.height();y++)
        {
             QGraphicsLineItem *vertical_line = m_annotateur->addLine(0,(y+1)*block_height,AnnotatorScene::c_image_resolution.width(),(y+1)*block_height,QPen(QColor(255,0,0)));
             m_verticalline_list.append(vertical_line);
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
                 m_colorlayout->TotalList.at(i).at(y*m_annotateur->c_annotation_resolution.width()+x)->setVisible(false);
             }
        }
    }
}

bool ChipAnnotator::hasImagesLoaded() const
{
    return m_annotateur->m_images.size() == 3 && !m_annotateur->m_images.front().isNull();
}

quint8 ChipAnnotator::classAtPosition(const AnnotatorScene::Region& pos) const
{
    return qRed(m_annotateur->m_result->toImage().pixel(pos.x(), pos.y()));
    ;
}

void ChipAnnotator::PaintGrid(bool m_display_grid)
{

         for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
             m_horizonline_list.at(x)->setVisible(!m_display_grid);
         for (int y = 0; y < AnnotatorScene::c_annotation_resolution.height();y++)
             m_verticalline_list.at(y)->setVisible(!m_display_grid);

    update();
}


void ChipAnnotator::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = m_annotaview->matrix();
    m_annotaview->resetMatrix();
    m_annotaview->translate(oldMatrix.dx(), oldMatrix.dy());
    m_annotaview->scale(newScale, newScale);
}

void ChipAnnotator::saveAnnotation(QString& output_file_path)
{
    int RectIndex;
    QFile file(output_file_path);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    for(int y=0;y<AnnotatorScene::c_annotation_resolution.height();y++)
    {
        for(int x=0;x<AnnotatorScene::c_annotation_resolution.width();x++)
        {
            RectIndex =0;
            for (int i = 0; i<TOTAL_TYPE; i++)
            {
                bool ifvisible=m_colorlayout->TotalList.at(i).at(y*m_annotateur->c_annotation_resolution.width()+x)->isVisible();
                if(ifvisible)
                {RectIndex = i+1;
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


void ChipAnnotator::showRectType(boost::optional<AnnotatorScene::Region> m_current_region)
 {
    //auto* b = statusBar();
     for (int k = 0;  k<TOTAL_TYPE;k++)
     {bool visible =m_colorlayout->TotalList.at(k).at(m_current_region->y()* m_annotateur->m_result->width()+m_current_region->x())->isVisible();
          if (visible)
          {
             // b->showMessage(Classes::s_classes.at(k+1).name());
              emit statusType(Classes::s_classes.at(k+1).name());
              return;
          }
     }
     //b->showMessage("RAS");
     emit statusType("RAS");
 }


