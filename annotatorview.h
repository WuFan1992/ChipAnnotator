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

public:
    explicit AnnotatorView(QGraphicsScene * scene, QWidget * parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* evt);
    virtual void mousePressEvent(QMouseEvent* evt) override;
    virtual void mouseReleaseEvent(QMouseEvent* evt) override;


private:
    enum class Button
    {
        Left,
        Right,
        Wheel
    };

signals:
    void newCurrentClass(QString name);


public:
   boost::optional<AnnotatorScene::Region> m_current_region;
   AnnotatorScene::Region screenToRegion(const QPointF& pos) const;
    boost::optional<Button> m_current_button_pressed;

    //void tagRegion(const Region& region, boost::optional<quint8> classes = {});
    void processClick(const AnnotatorScene::Region& pos);



};









#endif // ANNOTATORVIEW_H
