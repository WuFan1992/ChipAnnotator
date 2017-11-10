#ifndef ANNOTATORVIEW_H
#define ANNOTATORVIEW_H
#include <QGraphicsView>
#include <QWidget>
#include <QWheelEvent>
#include <boost/optional.hpp>
#include "annotatorscene.h"
#include "classes.hpp"



class QGraphicsScene;

class AnnotatorView : public QGraphicsView
{

      Q_OBJECT
public:
    explicit AnnotatorView(QGraphicsScene * scene, QWidget * parent = 0);

public:
    enum class Button
    {
        Left,
        Right,
        Wheel
    };

    bool _pan;
    int _panStartX;
    int _panStartY;

protected:
    virtual void wheelEvent(QWheelEvent* event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent* evt) override;
    virtual void mouseReleaseEvent(QMouseEvent* evt) override;
    virtual void leaveEvent(QEvent* evt) override;

    AnnotatorScene::Region screenToRegion(const QPointF &pos) const;

public:
   boost::optional<AnnotatorScene::Region> m_current_region;
   boost::optional<AnnotatorScene::Region> m_previous_region = AnnotatorScene::Region(0,0);
   boost::optional<Button> m_current_button_pressed;
   bool dragEnabled = false;




signals:
   void mouseMoveSignal(boost::optional<AnnotatorScene::Region> m_current_region);
   void mousePressSignal(AnnotatorScene::Region mousePressPos);
   void mouseReleaseSignal(AnnotatorScene::Region mouseReleasePos);
   void leaveView();

public:
   void DragFunction();
   bool isDragEnabled() const;

   void setDragEnabled(const bool enabled) ;




};









#endif // ANNOTATORVIEW_H
