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

protected:
    virtual void wheelEvent(QWheelEvent* event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent* evt) override;
    virtual void mouseReleaseEvent(QMouseEvent* evt) override;

    AnnotatorScene::Region screenToRegion(const QPointF &pos) const;

public:
   boost::optional<AnnotatorScene::Region> m_current_region;
   boost::optional<Button> m_current_button_pressed;


signals:
   void mouseMoveSignal(boost::optional<AnnotatorScene::Region> m_current_region);
   void mousePressSignal(AnnotatorScene::Region mousePressPos);
   void mouseReleaseSignal(AnnotatorScene::Region mouseReleasePos);






};









#endif // ANNOTATORVIEW_H
