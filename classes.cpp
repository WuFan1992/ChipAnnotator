#include "classes.hpp"

QList<Classes> Classes::s_classes = QList<Classes>() << Classes{QString("RAS"), QColor(0, 0, 0, 0)}
                                                     << Classes{QString("Large Coalescence"), QColor(0, 0, 255)}
                                                     << Classes{QString("Air Bubble"), QColor(255, 0, 0)}
                                                     << Classes{QString("Smears and Scratches"), QColor(0, 255, 0)};

const QList<Classes>& Classes::classes()
{
    return s_classes;
}

const QString& Classes::name() const
{
    return m_name;
}

const QColor& Classes::color() const
{
    return m_color;
}

Classes::Classes(const QString& name_, const QColor& color_)
    : m_name(name_)
    , m_color(color_)
{
}
