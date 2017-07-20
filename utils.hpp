#pragma once

class QPainter;
class QRect;

class Classes;

namespace Utils
{

    void drawRectForClass(QPainter& painter, const Classes& c, const QRect& rect);
}
