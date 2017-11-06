#include "annotatorview.h"
#include <QDebug>



AnnotatorView::AnnotatorView(QGraphicsScene * scene, QWidget * parent)
   : QGraphicsView(scene, parent)
{

}


AnnotatorScene::Region AnnotatorView::screenToRegion(const QPointF &pos) const
{
    double increment_x = AnnotatorScene::c_image_resolution.width()/AnnotatorScene::c_annotation_resolution.width();
    double increment_y = AnnotatorScene::c_image_resolution.height()/AnnotatorScene::c_annotation_resolution.height();

    return AnnotatorScene::Region(pos.x()/increment_x,pos.y()/increment_y);
}

void AnnotatorView::wheelEvent(QWheelEvent *event)
{
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        static double currentScale = 1.0;  // stores the current scale value.
        static const double scaleMin = 0.645; // defines the min scale limit.
        double scaleFactor = 1.05;
        if(event->delta()>0)
        {
            AnnotatorView::scale(scaleFactor,scaleFactor);
            currentScale *= scaleFactor;

        }else if (currentScale>scaleMin)
        {

             AnnotatorView::scale(1.0/scaleFactor,1.0/scaleFactor);
             currentScale /= scaleFactor;

        }

}


void AnnotatorView::mouseMoveEvent(QMouseEvent *evt)
{
    QPointF posInScene =QGraphicsView::mapToScene(evt->pos());
    m_current_region = screenToRegion(posInScene);
    if((m_current_region->x()< AnnotatorScene::c_annotation_resolution.width())&& (m_current_region->y()< AnnotatorScene::c_annotation_resolution.height()))
    {

        //emit newCurrentClass(Classes::classes()[ AnnotatorScene::classAtPosition(*m_current_region)].name());
    }
    //if(m_current_button_pressed) processClick(*m_current_region);

    /*
    if(m_result.rect().contains(m_current_region->x(), m_current_region->y()))
    {

        emit newCurrentClass(Classes::classes()[classAtPosition(*m_current_region)].name());
    }
    */
    if(m_current_button_pressed) processClick(*m_current_region);

    update();

}


void AnnotatorView::mousePressEvent(QMouseEvent* evt)
{
    //if(!hasImagesLoaded()) return;
    if(evt->button() == Qt::LeftButton)
        m_current_button_pressed = Button::Left;
    else if(evt->button() == Qt::RightButton)
        m_current_button_pressed = Button::Right;
    else if(evt->button() == Qt::MiddleButton)
        m_current_button_pressed = Button::Wheel;
    processClick(screenToRegion(evt->pos()));
    update();
}

void AnnotatorView::mouseReleaseEvent(QMouseEvent* evt)
{
    //if(!hasImagesLoaded()) return;
    processClick(screenToRegion(evt->pos()));
    m_current_button_pressed.reset();
    update();
}


/*
void AnnotatorView::tagRegion(const AnnotatorScene::Region& region, boost::optional<quint8> classes)
{
    if(!classes) classes = m_current_class;
    if(region.x() >= 0 && region.x() < m_result.width() && region.y() >= 0 && region.y() < m_result.height())
    {
        m_result.setPixel(region.x(), region.y(), qRgb(*classes, *classes, *classes));
        emit modified();
    }
}
*/
void AnnotatorView::processClick(const AnnotatorScene::Region& pos)
{
    assert(m_current_button_pressed);
    switch(*m_current_button_pressed)
    {
    case Button::Left:
        qDebug()<<"Left";
        //tagRegion(pos);
        return;
    case Button::Right:
        qDebug()<< "Right";
        //tagRegion(pos, 0);
        return;
    /*
    case Button::Wheel:
        const auto class_id = classAtPosition(*m_current_region);
        emit selectClass(class_id);
        return;
    */
    }
}




