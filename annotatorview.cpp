#include "annotatorview.h"
#include <QDebug>
#include <QAbstractScrollArea>
#include <QScrollBar>



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
    if(_pan && dragEnabled)
    {
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (evt->y() - _panStartY));
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (evt->x() - _panStartX));
        _panStartX = evt->x();
        _panStartY = evt->y();

    }else
    {
    setMouseTracking(true);
    QPointF posInScene =QGraphicsView::mapToScene(evt->pos());
    m_current_region = screenToRegion(posInScene);
    emit mouseMoveSignal(m_current_region);
    }
    update();

}

void AnnotatorView::mousePressEvent(QMouseEvent* evt)
{
   if (dragEnabled)
    {
    _pan = true;
    setCursor(Qt::ClosedHandCursor);
    _panStartX = evt->x();
    _panStartY = evt->y();
   }else
    //if(!hasImagesLoaded()) return;
   { if(evt->button() == Qt::LeftButton)
        m_current_button_pressed = Button::Left;
    else if(evt->button() == Qt::RightButton)
        m_current_button_pressed = Button::Right;
    else if(evt->button() == Qt::MiddleButton)
        m_current_button_pressed = Button::Wheel;


   QPointF posInScene =QGraphicsView::mapToScene(evt->pos());
   AnnotatorScene::Region mousePressPos = screenToRegion(posInScene);
   emit mousePressSignal(mousePressPos);
  }
    update();
}

void AnnotatorView::mouseReleaseEvent(QMouseEvent* evt)
{
     setCursor(Qt::ArrowCursor);

     if(dragEnabled)
         _pan = false;
    //if(!hasImagesLoaded()) return;
    else
    {QPointF posInScene =QGraphicsView::mapToScene(evt->pos());
    AnnotatorScene::Region mouseReleasePos = screenToRegion(posInScene);
    emit mouseReleaseSignal(mouseReleasePos);
    m_current_button_pressed.reset();
    }
    update();
}


void AnnotatorView::leaveEvent(QEvent *evt)
{
    emit leaveView();
}


void AnnotatorView::DragFunction()
{
    setDragEnabled(!isDragEnabled());
}


bool AnnotatorView::isDragEnabled() const
{
    return dragEnabled;
}

void AnnotatorView::setDragEnabled(const bool enabled)
{
  dragEnabled = enabled;
}


