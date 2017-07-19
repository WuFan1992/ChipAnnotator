#include "classes.hpp"

QList<Classes> Classes::s_classes
    = QList<Classes>()
      << Classes{QString("RAS"), QColor(0, 0, 0, 0)} << Classes{QString("Bulle"), QColor(255, 0, 0)}
      << Classes{QString("Tassement"), QColor(0, 255, 0)} << Classes{QString("Coalescence"), QColor(0, 0, 255)}
      << Classes{QString("Polydispersité"), QColor(0, 0, 0)} << Classes{QString("Région claire"), QColor(0, 0, 0)}
      << Classes{QString("Inhomogénéité d’amplification"), QColor(0, 0, 0)}
      << Classes{QString("Inhibition"), QColor(0, 0, 0)} << Classes{QString("Mouillage"), QColor(0, 0, 0)}
      << Classes{QString("Gouttes démouillées"), QColor(0, 0, 0)} << Classes{QString("Région sombre"), QColor(0, 0, 0)}
      << Classes{QString("Gouttes collées dans la pente"), QColor(0, 0, 0)}
      << Classes{QString("Muraille"), QColor(0, 0, 0)} << Classes{QString("Trace de TS"), QColor(0, 0, 0)}
      << Classes{QString("Injecteur bouché"), QColor(0, 0, 0)} << Classes{QString("Précipité"), QColor(0, 0, 0)}
      << Classes{QString("Dédoublement"), QColor(0, 0, 0)} << Classes{QString("Autres"), QColor(0, 0, 0)}
      << Classes{QString("Artefact général"), QColor(0, 0, 0)};

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
