#include "utils.hpp"

#include "classes.hpp"

#include <QPainter>

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
