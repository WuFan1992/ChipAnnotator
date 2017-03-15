#pragma once

#include <QDockWidget>

class ClassSelector : public QDockWidget
{
    Q_OBJECT
public:
    explicit ClassSelector(QWidget* parent = 0);

signals:
    void classSelected(quint8 class_index);
};
