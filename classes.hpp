#pragma once

#include <QColor>

class Classes
{
public:
    static const QList<Classes>& classes();

    const QString& name() const;

    const QColor& color() const;

public:
    Classes(const QString& name_, const QColor& color_);

    QString m_name;
    QColor m_color;

    static QList<Classes> s_classes;
    static const QList<QColor> c_color;
};


