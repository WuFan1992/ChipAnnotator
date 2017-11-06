#pragma once
#include "annotatorscene.h"
#include "annotatorview.h"
class QPainter;
class QRect;

class Classes;

namespace Utils
{

    void drawRectForClass(QPainter& painter, const Classes& c, const QRect& rect);
    void drawRectForClass(AnnotatorScene *annotatorscene,const Classes& c, const QRect& rect);
}
