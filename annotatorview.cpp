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
    emit mouseMoveSignal(m_current_region);

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

    QPointF posInScene =QGraphicsView::mapToScene(evt->pos());
    AnnotatorScene::Region mousePressPos = screenToRegion(posInScene);
    emit mousePressSignal(mousePressPos);

   // processClick(screenToRegion(evt->pos()));
    update();
}

void AnnotatorView::mouseReleaseEvent(QMouseEvent* evt)
{
    //if(!hasImagesLoaded()) return;
    QPointF posInScene =QGraphicsView::mapToScene(evt->pos());
    AnnotatorScene::Region mouseReleasePos = screenToRegion(posInScene);
    emit mousePressSignal(mouseReleasePos);
    //processClick(screenToRegion(evt->pos()));
    m_current_button_pressed.reset();
    update();
}


