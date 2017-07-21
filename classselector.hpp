#pragma once

#include <QDockWidget>

class QButtonGroup;

class ClassSelector : public QDockWidget
{
    Q_OBJECT
public:
    explicit ClassSelector(QWidget* parent = nullptr);

signals:
    void classSelected(quint8 class_index);

    void channelSelected(quint8 channel_index);

public slots:
    void selectClass(quint8 class_index);

private:
    QButtonGroup* m_classes_button_group;
    QButtonGroup* m_channels_button_group;

    QWidget* buildButtonWidget();

    void setupShortcuts();

    QWidget* createChannelSelectionWidget();
};
