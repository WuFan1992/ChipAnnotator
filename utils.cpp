#include "utils.hpp"

#include "classes.hpp"

#include <QPainter>
#include <QColor>


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
