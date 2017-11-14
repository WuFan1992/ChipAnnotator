#pragma once

#include"chipannotator.h"
#include"colorlayout.h"

#include "classes.hpp"

#include <QPainter>
#include <QRect>

class ChipAnnotator;

namespace Utils
{

    void drawRectForClass(QPainter& painter, const Classes& c, const QRect& rect);
    void drawRectForClass(AnnotatorScene *annotatorscene,const Classes& c, const QRect& rect);
    void preColorLayout(AnnotatorScene *annotateur,ColorLayout *colorlayout);


}

