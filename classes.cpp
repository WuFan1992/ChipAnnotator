#include "classes.hpp"

const QList<QColor> Classes::c_color
    = QList<QColor>() << QColor(255 * 0, 255 * 0, 255 * 1.0000,128) << QColor(255 * 1.0000, 255 * 0, 255 * 0,128)
                      << QColor(255 * 0, 255 * 1.0000, 255 * 0,128) << QColor(255 * 1.0000, 255 * 0.1034, 255 * 0.7241,128)
                      << QColor(255 * 1.0000, 255 * 0.8276, 255 * 0,128) << QColor(255 * 0, 255 * 0.3448, 255 * 0,128)
                      << QColor(255 * 0.5172, 255 * 0.5172, 255 * 1.0000,128)
                      << QColor(255 * 0.6207, 255 * 0.3103, 255 * 0.2759,128) << QColor(255 * 0, 255 * 1.0000, 255 * 0.7586,128)
                      << QColor(255 * 0, 255 * 0.5172, 255 * 0.5862,128) << QColor(255 * 0, 255 * 0, 255 * 0.4828,128)
                      << QColor(255 * 0.5862, 255 * 0.8276, 255 * 0.3103,128)
                      << QColor(255 * 0.9655, 255 * 0.6207, 255 * 0.8621,128)
                      << QColor(255 * 0.9655, 255 * 0.5172, 255 * 0.0345,128)
                      << QColor(255 * 0.4828, 255 * 0.1034, 255 * 0.4138,128)
                      << QColor(255 * 1.0000, 255 * 0.7586, 255 * 0.5172,128) << QColor(255, 255, 255,128)
                      << QColor(255 * 0.5517, 255 * 0.6552, 255 * 0.4828,128);

QList<Classes> Classes::s_classes
    = QList<Classes>() << Classes{QString("RAS"), QColor(0, 0, 0, 0)} << Classes{QString("Bulle"), Classes::c_color[0]}
                       << Classes{QString("Tassement"), Classes::c_color[1]}
                       << Classes{QString("Coalescence"), Classes::c_color[2]}
                       << Classes{QString("Polydispersité"), Classes::c_color[3]}
                       << Classes{QString("Région claire"), Classes::c_color[4]}
                       << Classes{QString("Inhomogénéité d’amplification"), Classes::c_color[5]}
                       << Classes{QString("Mouillage"), Classes::c_color[6]}
                       << Classes{QString("Gouttes démouillées"), Classes::c_color[7]}
                       << Classes{QString("Région sombre"), Classes::c_color[8]}
                       << Classes{QString("Gouttes collées dans la pente"), Classes::c_color[9]}
                       << Classes{QString("Muraille"), Classes::c_color[10]}
                       << Classes{QString("Trace de TS"), Classes::c_color[11]}
                       << Classes{QString("Injecteur bouché"), Classes::c_color[12]}
                       << Classes{QString("Précipité"), Classes::c_color[13]}
                       << Classes{QString("Dédoublement"), Classes::c_color[14]}
                       << Classes{QString("Out of Focus"), Classes::c_color[15]}
                       << Classes{QString("Autres"), Classes::c_color[16]}
                       << Classes{QString("Artefact général"), Classes::c_color[17]};

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
